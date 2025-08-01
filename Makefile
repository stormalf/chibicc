CC=gcc
CFLAGS =-std=c11 -g -fno-common -Wall -Wno-switch 
CFLAGS_DIAG=-dotfile 
OBJECT=chibicc
OBJECTLIB=libchibicc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

TEST_SRCS=$(wildcard test/*.c)
TESTS=$(TEST_SRCS:.c=.exe)
ISSUES_SRCS=$(wildcard issues/*.c)
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
	for i in $^; do echo $$i; ./$$i || exit 1; echo; done
	test/driver.sh ./$(OBJECT)


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
	for i in $^; do echo $$i; ./$$i || exit 1; echo; done
	test/driver.sh ./stage2/$(OBJECT)

projects-all: projects projects-oth git

projects-oth: openssl vim nmap curl 

projects: zlib util-linux nginx


curl:
	cd ../curl && make clean && CC=chibicc ./configure && make && make test

zlib:
	cd ../zlib && make clean && CC=chibicc ./configure && make && make test

nmap:
	cd ../nmap && make clean && CC=chibicc LDFLAGS="-ldbus-1" LIBS="-ldbus-1" ./configure --with-dbus && make && make check

openssl:
	cd ../openssl && make clean && CC=chibicc ./configure && make 

util-linux:
	cd ../util-linux && make clean && CC=chibicc CFLAGS=-fPIC ./configure && make && make check-programs && cd tests && ./run.sh

nginx:
	cd ../nginx && make clean && CC=chibicc CFLAGS=-fPIC ./auto/configure --with-http_ssl_module && make && make check

vim:
	cd ../vim && make clean && CC=chibicc CFLAGS=-fPIC ./configure && make && make test

lxc:
	cd ../lxc && rm -rf build && CC=gcc \
	CFLAGS="-fpic" 	meson build && cd build && cp /usr/bin/gcc /usr/bin/gcc_old && \
	cp /usr/local/bin/chibicc /usr/local/gcc && meson compile && cp /usr/bin/gcc_old /usr/bin/gcc

git: 
	cd ../git && CC=chibicc CFLAGS=-fPIC ./configure && make && make test

memcached:
	cd ../memcached && make clean && CC=chibicc CFLAGS=-fPIC ./configure && make && make test

# Misc.

libchibicc:  $(OBJECT) $(OBJECTLIB).so
CFLAGS +=-fPIC


libchibicc.so: $(OBJS)
	gcc $(CFLAGS) -o $@ $^ -shared

clean:
	rm -rf $(OBJECT) tmp* $(TESTS) issues/*.s issues/*.exe issues/*.dot test/*.s test/*.exe stage2 diagram/*.png test/*.dot $(OBJECTLIB)
	find * -type f '(' -name '*~' -o -name '*.o' ')' -exec rm {} ';'

install:
	sudo rm -rf	/usr/local/include/x86_64-linux-gnu/chibicc && sudo rm -rf /usr/local/bin/chibicc
	test -d /usr/local/include/x86_64-linux-gnu/chibicc || \
		sudo mkdir -p /usr/local/include/x86_64-linux-gnu/chibicc
	sudo cp -r include/* /usr/local/include/x86_64-linux-gnu/chibicc/
	sudo cp ./chibicc /usr/local/bin/chibicc

uninstall:
	sudo rm -rf	/usr/local/include/x86_64-linux-gnu/chibicc && sudo rm /usr/local/bin/chibicc

.PHONY: test clean test-stage2 libchibicc projects projects-all test-all install uninstall
