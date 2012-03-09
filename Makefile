CFLAGS=-fPIC -I include -ansi -Wall -Wextra -Werror -pedantic
LDFLAGS=-fPIC -Wall -Wextra -Werror
DBFLAGS=-g -O0 -DDEBUG

LIBS=lib/libcba.so lib/libcba.a

.PHONY: all debug
all: $(LIBS)
debug: CFLAGS += $(DBFLAGS)
debug: all

lib/libcba.so: src/cba.o
	$(CC) $(LDFLAGS) -shared -o $@ $<

lib/libcba.a: src/cba.o
	ar rc -o $@ $<

src/cba.o: src/cba.c include/cba.h
test/test_cba.o: test/test_cba.c include/cba.h test/test_cba.h
test/test_cba: test/test_cba.o lib/libcba.a

.PHONY: test debug_test
test: test/test_cba
	@$<
debug_test: CFLAGS += $(DBFLAGS)
debug_test: test/test_cba debug
	@gdb -batch -ex run $<

.PHONY: clean
clean:
	rm -f src/cba.o test/test_cba.o test/test_cba $(LIBS)