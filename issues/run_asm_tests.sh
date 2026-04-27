#!/bin/bash
set -u

CHIBICC=./chibicc
ISSUES_DIR=issues

tests=(
    "sha1:sha1-x86_64.s"
    "sha256:sha256-x86_64.s"
    "sha512:sha512-x86_64.s"
    "aes:aes-x86_64.s"
    "nistz256_double:ecp_nistz256-x86_64.s"
    "ghash:ghash-x86_64.s"
    "keccak:keccak1600-x86_64.s"
    "poly1305:poly1305-x86_64.s"
    "vpaes:vpaes-x86_64.s"
)

failed=0

for t in "${tests[@]}"; do
    name="${t%%:*}"
    asm="${t#*:}"
    
    echo "=== Testing $name with $asm ==="
    
    # Compile assembly
    $CHIBICC -c "$ISSUES_DIR/$asm" -o "$ISSUES_DIR/$name.asm.o"
    if [ $? -ne 0 ]; then
        echo "Failed to compile $asm"
        failed=$((failed + 1))
        continue
    fi
    
    # Compile C test
    $CHIBICC -Iinclude -c "$ISSUES_DIR/test_$name.c" -o "$ISSUES_DIR/test_$name.o"
    if [ $? -ne 0 ]; then
        echo "Failed to compile test_$name.c"
        failed=$((failed + 1))
        continue
    fi
    
    # Link
    rm -f "$ISSUES_DIR/test_$name.exe"
    $CHIBICC "$ISSUES_DIR/test_$name.o" "$ISSUES_DIR/$name.asm.o" -o "$ISSUES_DIR/test_$name.exe"
    if [ $? -ne 0 ]; then
        echo "Failed to link test_$name.exe"
        failed=$((failed + 1))
        continue
    fi
    
    # Run
    echo "Running test_$name.exe..."
    ./"$ISSUES_DIR/test_$name.exe"
    if [ $? -ne 0 ]; then
        echo "test_$name.exe FAILED"
        failed=$((failed + 1))
    fi
    
    # Try with -fomit-frame-pointer
    echo "Running test_$name.exe (-fomit-frame-pointer)..."
    rm -f "$ISSUES_DIR/test_$name.omit.exe"
    $CHIBICC -fomit-frame-pointer -Iinclude -c "$ISSUES_DIR/test_$name.c" -o "$ISSUES_DIR/test_$name.omit.o"
    $CHIBICC "$ISSUES_DIR/test_$name.omit.o" "$ISSUES_DIR/$name.asm.o" -o "$ISSUES_DIR/test_$name.omit.exe"
    ./"$ISSUES_DIR/test_$name.omit.exe"
    if [ $? -ne 0 ]; then
        echo "test_$name.omit.exe FAILED"
        failed=$((failed + 1))
    fi
    
    echo ""
done

if [ $failed -eq 0 ]; then
    echo "ALL TESTS PASSED"
else
    echo "$failed TESTS FAILED"
fi

exit $failed
