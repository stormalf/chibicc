# The installation prefix
PREFIX=/usr/local

GCC_VERSION!=gcc -dumpversion
CC=gcc
CFLAGS =-std=c11 -g -fno-common -Wall -Wno-switch -DPREFIX=\"$(PREFIX)\" -DGCC_VERSION=\"$(GCC_VERSION)\"
CFLAGS_DIAG= -std=c11 
CFLAGS_SPE = -fomit-frame-pointer -O3
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
	$(CC) -pthread -o $@ test/$*.o -xc test/common -lm
#	dot -Tpng test/$*.dot -o diagram/$*.png || echo $*.dot failed
	

test: $(TESTS) 
	TEST_JOBS="$(TEST_JOBS)" TEST_TIMEOUT="$(TEST_TIMEOUT)" ./test/run_tests.sh $(addprefix ./,$^)
	test/driver.sh ./$(OBJECT)

test_spe/%.exe: $(OBJECT) test/%.c
	mkdir -p test_spe
	./$(OBJECT) $(CFLAGS_DIAG) $(CFLAGS_SPE) -Iinclude -Itest \
		-c -o test_spe/$*.o test/$*.c
	$(CC) -pthread -o $@ test_spe/$*.o -xc test/common -lm

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
	$(CC) -pthread -o $@ stage2/test/$*.o -xc test/common

test-stage2: $(TESTS:test/%=stage2/test/%)
	TEST_JOBS="$(TEST_JOBS)" TEST_TIMEOUT="$(TEST_TIMEOUT)" ./test/run_tests.sh $(addprefix ./,$^)
	test/driver.sh ./stage2/$(OBJECT)

projects-all: projects projects-oth lxc vlc git memcached cpython openssl

projects-oth: sqlite vim nmap curl 

projects: zlib util-linux nginx


curl:
	cd ../curl && make clean && CC=chibicc  CFLAGS="-std=c11" ./configure --with-openssl && make -j$(nproc) && make -j$(nproc) test

zlib:
	cd ../zlib && make clean && CC=chibicc CFLAGS="-fPIC -std=c11" ./configure && make && make test

nmap:
	cd ../nmap && make clean && CC=chibicc  CFLAGS="-fPIC -std=c11" LIBS="-ldbus-1 -latomic -libverbs -lrdmacm" ./configure --with-dbus && make -j$(nproc) && make check

openssl:
	cd ../openssl && make clean && CC=chibicc CFLAGS="-std=c11" ./Configure enable-fips && make && make test

util-linux:
	cd ../util-linux && make clean && CC=chibicc CFLAGS="-fPIC -std=c11" ./configure && make -j$(nproc) && make check-programs && cd tests && ./run.sh

nginx:
	cd ../nginx && make clean && CC=chibicc CFLAGS="-fPIC -std=c11" ./auto/configure --with-http_ssl_module && make

vim:
	cd ../vim && make clean && CC=chibicc CFLAGS="-fPIC -std=c11" ./configure && make &&  make test 

lxc:
	cd ../lxc && rm -rf build && CC=gcc \
	meson setup build && cd build && sudo cp /usr/bin/gcc /usr/bin/gcc_backup  && \
	sudo cp /usr/local/bin/chibicc /usr/bin/gcc && meson compile && sudo cp /usr/bin/gcc_backup /usr/bin/gcc

vlc:
	cd ../vlc && make clean && CC=chibicc CFLAGS="-fPIC -std=c11"  ./configure  \
	--disable-lua --disable-xcb --disable-qt --disable-alsa --disable-sse --host x86_64-linux-gnu && \
    make all

cpython:
	cd ../cpython &&  CC=chibicc CFLAGS="-std=c11 -O3" ./configure  \
	 --build=x86_64-pc-linux-gnu && make clean && make && make -j$(nproc) test

# vlc2:
# 	cd ../vlc && rm -rf build && mymeson setup build && cd build && mymeson compile


git: 
	cd ../git && CC=chibicc CFLAGS="-fPIC -std=c11" ./configure && make && make test

memcached:
	cd ../memcached && make clean && CC=chibicc CFLAGS="-fPIC -std=c11" ./configure && make -j$$(nproc) && make test

openssh-portable:
	cd ../openssh-portable && make clean && CC=chibicc CFLAGS="-std=c11" ./configure && make && make tests

sqlite:
	cd ../sqlite && CC=chibicc CFLAGS="-fPIC -std=c11" ./configure && make clean && make && make test

php-src:
	cd ../php-src && CC=chibicc CFLAGS="-fPIC -std=c11" ./buildconf && ./configure && make clean && make && make test

# Misc.

libchibicc:  $(OBJECT) $(OBJECTLIB).so
CFLAGS +=-fPIC


libchibicc.so: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -shared

clean:
	rm -rf $(OBJECT) tmp* *.zend $(TESTS) issues/*.s issues/*.exe issues/*.dot test/*.s test/*.exe test_spe/*.exe stage2 diagram/*.png test/*.dot $(OBJECTLIB)
	find * -type f '(' -name '*~' -o -name '*.o' ')' -exec rm {} ';'

install: $(OBJECT)
	install -v -D -m 755 -t $(PREFIX)/bin/ $(OBJECT)
	install -v -D -m 644 -t $(PREFIX)/include/x86_64-linux-gnu/chibicc/ include/*

uninstall:
	rm -f $(PREFIX)/bin/chibicc
	rm -f $(PREFIX)/include/x86_64-linux-gnu/chibicc/*

.PHONY: test clean test-stage2 libchibicc projects projects-all  projects-oth test-all install uninstall test_spe
