# The installation prefix
PREFIX=/usr/local

GCC_VERSION!=gcc -dumpversion
CC=gcc
CFLAGS =-std=c11 -g -fno-common -Wall -Wno-switch -DPREFIX=\"$(PREFIX)\" -DGCC_VERSION=\"$(GCC_VERSION)\"
CFLAGS_DIAG= -std=c11 -g -mavx2 
CFLAGS_SPE = -g -fomit-frame-pointer -O3 -mavx2 -DOMIT_FRAME_POINTER
CFLAGS_LLVM = --backend-llvm
LDFLAGS = -lcrypto
TEST_JOBS ?=
TEST_TIMEOUT ?= 30
OBJECT=chibicc
OBJECTLIB=libchibicc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

TEST_SRCS=$(wildcard test/*.c)
TESTS=$(TEST_SRCS:.c=.exe)
ISSUES_SRCS=$(wildcard issues/*.c)
TESTS_SPE = $(TESTS:test/%=test_spe/%)
#PNG=$(TEST_SRCS:.c=.tmp)
#PNG2=$(ISSUES_SRCS:.c=.tmp)

# Stage 1

$(OBJECT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJS): $(OBJECT).h

test/%.exe: $(OBJECT) test/%.c 
	./$(OBJECT) $(CFLAGS_DIAG) -Iinclude -Itest -c -o test/$*.o test/$*.c 
	$(CC) -pthread -o $@ test/$*.o -xc test/common -lm $(LDFLAGS) 
#	dot -Tpng test/$*.dot -o diagram/$*.png || echo $*.dot failed
	

test: $(TESTS) 
	TEST_JOBS="$(TEST_JOBS)" TEST_TIMEOUT="$(TEST_TIMEOUT)" ./test/run_tests.sh $(addprefix ./,$^)
	test/driver.sh ./$(OBJECT)

# Tests that exercise the LLVM backend (--backend-llvm).
# Each test/*.c is compiled through the IR emitter and assembled with clang.
# Tests that fail to compile or fail at runtime are listed at the end; this
# allows tracking progress toward running the whole test suite through the
# LLVM backend (a long-term goal).
LLVM_TEST_SRCS=$(wildcard test/*.c)
LLVM_TESTS=$(LLVM_TEST_SRCS:test/%.c=test/%.llvm.exe)

test/%.llvm.exe: $(OBJECT) test/%.c
	@if timeout 30 ./$(OBJECT) $(CFLAGS_LLVM) -Iinclude -Itest -o $@ test/$*.c -xc test/common 2>/tmp/chibicc-llvm-$*.log; then \
	  echo "  BUILD    $@"; \
	else \
	  echo "  BUILD FAIL $@"; \
	  rm -f $@; \
	fi

test_llvm: $(LLVM_TESTS)
	@pass=0; fail=0; missing=0; \
	for t in $(LLVM_TESTS); do \
	  if [ -x "$$t" ]; then \
	    if timeout "${TEST_TIMEOUT}s" "$$t" >/tmp/chibicc-llvm-run.log 2>&1; then \
	      pass=$$((pass+1)); \
	    else \
	      fail=$$((fail+1)); \
	      echo "  RUN FAIL  $$t"; \
	    fi; \
	  else \
	    missing=$$((missing+1)); \
	    echo "  NOEXE     $$t"; \
	  fi; \
	done; \
	echo ""; \
	echo "LLVM backend test summary: $$pass passed, $$fail failed, $$missing not built"; \
	if [ $$fail -gt 0 ]; then exit 1; fi

test_spe/%.exe: $(OBJECT) test/%.c
	mkdir -p test_spe
	./$(OBJECT) $(CFLAGS_DIAG) $(CFLAGS_SPE) -Iinclude -Itest \
		-c -o test_spe/$*.o test/$*.c
	$(CC) -pthread -o $@ test_spe/$*.o -xc test/common -lm $(LDFLAGS) 

test_spe: $(TESTS_SPE)
	TEST_JOBS="$(TEST_JOBS)" TEST_TIMEOUT="$(TEST_TIMEOUT)" ./test/run_tests.sh $(addprefix ./,$^)

# #for managing dot diagram
# test-png: $(TESTS)
	
test-all: test test-stage2 

# Stage 2

stage2/$(OBJECT): $(OBJS:%=stage2/%)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

stage2/%.o: $(OBJECT) %.c
	mkdir -p stage2/test
	./chibicc -c -o $(@D)/$*.o $*.c 

stage2/test/%.exe: stage2/$(OBJECT) test/%.c
	mkdir -p stage2/test
	./stage2/$(OBJECT) -Iinclude -Itest -c -o stage2/test/$*.o test/$*.c 
	$(CC)  -pthread -o $@ stage2/test/$*.o -xc test/common $(LDFLAGS) 

test-stage2: $(TESTS:test/%=stage2/test/%)
	TEST_JOBS="$(TEST_JOBS)" TEST_TIMEOUT="$(TEST_TIMEOUT)" ./test/run_tests.sh $(addprefix ./,$^)
	test/driver.sh ./stage2/$(OBJECT)

projects-all: projects projects-oth lxc cpython openssl php-src

projects-oth: openssh-portable sqlite vim nmap memcached git curl 

projects: zlib util-linux nginx vlc 


curl:
	cd ../curl && make clean && CC=chibicc  CFLAGS="-std=c11 -g" ./configure --with-openssl && make -j4 && make -j4 test

zlib:
	cd ../zlib && make clean && CC=chibicc CFLAGS="-fPIC -std=c11 -g" ./configure && make && make test

nmap:
	cd ../nmap && make clean && CC=chibicc  CFLAGS="-fPIC -std=c11 -g" LIBS="-ldbus-1 -latomic -libverbs -lrdmacm" ./configure --with-dbus && make -j4 && make check

openssl:
	cd ../openssl && make clean && CC=chibicc CFLAGS="-std=c11 -g -O0" ./Configure linux-x86_64 --debug enable-fips enable-legacy && make -j4 && HARNESS_JOBS=1 make test

util-linux:
	cd ../util-linux && make clean && CC=chibicc CFLAGS="-fPIC -std=c11 -g" ./configure && make -j4 && make check-programs && cd tests && ./run.sh

nginx:
	cd ../nginx && make clean && CC=chibicc CFLAGS="-fPIC -std=c11" ./auto/configure --with-http_ssl_module && make -j4

vim:
	cd ../vim && make clean && CC=chibicc CFLAGS="-fPIC -std=c11 -g" ./configure && make -j2 &&  make test 

lxc:
	cd ../lxc && rm -rf build && CC=gcc \
	meson setup build && cd build && sudo cp /usr/bin/gcc /usr/bin/gcc_backup  && \
	sudo cp /usr/local/bin/chibicc /usr/bin/gcc && meson compile && sudo cp /usr/bin/gcc_backup /usr/bin/gcc

vlc:
	cd ../vlc && make clean && CC=chibicc CFLAGS="-fPIC -std=c11 -g"  ./configure  \
	--disable-lua --disable-xcb --disable-qt --disable-alsa --disable-sse --host x86_64-linux-gnu && \
    make -j4 all

cpython:
	cd ../cpython &&  CC=chibicc CFLAGS="-std=c11 -O3 -g" ./configure  \
	 --build=x86_64-pc-linux-gnu && make clean && make -j4 && make test


git: 
	cd ../git && CC=chibicc CFLAGS="-fPIC -std=c11 -g" ./configure && make && make test

memcached:
	cd ../memcached && make clean && CC=chibicc CFLAGS="-fPIC -std=c11 -g" ./configure && make -j2 && make test

openssh-portable:
	cd ../openssh-portable && make clean && CC=chibicc CFLAGS="-std=c11 -g" ./configure && make -j2 && make tests

sqlite:
	cd ../sqlite && CC=chibicc CFLAGS="-fPIC -std=c11 -g" ./configure && make clean && make -j2 && make test

php-src:
	cd ../php-src && CC=chibicc CFLAGS="-fPIC -std=c11 -g" ./buildconf && ./configure && make clean && make -j2 && make test

# Misc.

libchibicc:  $(OBJECT) $(OBJECTLIB).so
CFLAGS +=-fPIC


libchibicc.so: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -shared

clean:
	rm -rf $(OBJECT) tmp* *.zend $(TESTS) *.ll issues/*.s issues/*.exe issues/*.dot issues/*.ll test/*.s test/*.exe test_spe/*.exe test/*.ll test_spe/*.ll stage2 diagram/*.png test/*.dot $(OBJECTLIB) $(LLVM_TESTS)
	find * -type f '(' -name '*~' -o -name '*.o' ')' -exec rm {} ';'

install: $(OBJECT)
	install -v -D -m 755 -t $(PREFIX)/bin/ $(OBJECT)
	install -v -D -m 644 -t $(PREFIX)/include/x86_64-linux-gnu/chibicc/ include/*

uninstall:
	rm -f $(PREFIX)/bin/chibicc
	rm -f $(PREFIX)/include/x86_64-linux-gnu/chibicc/*

.PHONY: test clean test-stage2 libchibicc projects projects-all  projects-oth test-all install uninstall test_spe
