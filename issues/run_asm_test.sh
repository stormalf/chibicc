#!/bin/bash
CHIBICC=../chibicc

failed=0

run_test() {
    local c_file=$1
    local s_pattern=$2
    local name=$(basename "$c_file" .c)
    
    local s_file=$(ls $s_pattern 2>/dev/null | head -n 1)
    
    if [ -z "$s_file" ]; then
        echo "Skipping $name: no assembly file found matching $s_pattern"
        return
    fi

    echo -n "Testing $name with $s_file..."
    $CHIBICC -o "$name" "$c_file" "$s_file" 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "  COMPILATION FAILED"
        failed=1
        return
    fi
    ./"$name" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "  FAILED"
        failed=1
    else
        echo "  PASSED"
    fi
    rm -f "$name"
}

# Map C drivers to their required assembly files
run_test "test_aes.c" "aes-x86_64.s"
run_test "test_aes_decrypt.c" "aes-x86_64.s"
run_test "test_ghash.c" "ghash-x86_64.s"
run_test "test_ghash_gmult.c" "ghash-x86_64.s"
run_test "test_keccak.c" "keccak1600-x86_64.s"
run_test "test_nistz256_double.c" "ecp_nistz256-x86_64.s"
run_test "test_nistz256_add.c" "ecp_nistz256-x86_64.s"
run_test "test_poly1305.c" "poly1305-x86_64.s"
run_test "openssl_crash6.c" "poly1305-x86_64.s"
run_test "test_sha1.c" "sha1-x86_64.s"
run_test "test_sha256.c" "sha256-x86_64.s"
run_test "test_sha512.c" "sha512-x86_64.s"
run_test "test_vpaes.c" "vpaes-x86_64.s"
run_test "test_vpaes_decrypt.c" "vpaes-x86_64.s"

exit $failed