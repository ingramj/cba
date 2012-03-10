CFLAGS=-fPIC -I include -ansi -Wall -Wextra -Werror -pedantic
LDFLAGS=-fPIC -Wall -Wextra -Werror

LIBS=lib/libcba.so lib/libcba.a

# Regular build
.PHONY: all
all: $(LIBS)
lib/libcba.so: src/cba.o
	$(CC) $(LDFLAGS) -shared -o $@ $<
lib/libcba.a: src/cba.o
	ar rc -o $@ $<

src/cba.o: src/cba.c include/cba.h

.PHONY: test
test: test/test_cba all
	@$<

test/test_cba.o: test/test_cba.c include/cba.h test/test_cba.h
test/test_cba: test/test_cba.o lib/libcba.a


# Debug build
DBFLAGS=-g -O0 -DDEBUG
DBLIBS=lib/libcba-debug.so lib/libcba-debug.a

.PHONY: debug
debug: $(DBLIBS)
lib/libcba-debug.so: src/cba-debug.o
	$(CC) $(LDFLAGS) -shared -o $@ $<
lib/libcba-debug.a: src/cba-debug.o
	ar rc -o $@ $<

src/cba-debug.o: CFLAGS += $(DBFLAGS)
src/cba-debug.o: src/cba.c include/cba.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: debug_test
debug_test: CFLAGS += $(DBFLAGS)
debug_test: test/test_cba-debug debug
	@gdb -batch -ex run $<

test/test_cba-debug.o: CFLAGS += $(DBFLAGS)
test/test_cba-debug.o: test/test_cba.c include/cba.h test/test_cba.h
	$(CC) $(CFLAGS) -c -o $@ $<
test/test_cba-debug: test/test_cba-debug.o lib/libcba-debug.a


# Examples
.PHONY: examples
examples: examples/bloom

examples/bloom: examples/bloom.o lib/libcba.a
examples/bloom.o: examples/bloom.c include/cba.h

.PHONY: clean
clean:
	rm -f src/*.o test/*.o examples/*.o test/test_cba test/test_cba-debug examples/bloom $(LIBS) $(DBLIBS)