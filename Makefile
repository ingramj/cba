CFLAGS=-fPIC -I include -ansi -Wall -Wextra -Werror -pedantic -g -O1
LDFLAGS=-fPIC -Wall -Wextra -Werror -g

LIBS=lib/libcba.so lib/libcba.a

.PHONY: all
all: $(LIBS) test examples

lib/libcba.so: src/cba.o
	$(CC) $(LDFLAGS) -shared -o $@ $<

lib/libcba.a: src/cba.o
	ar rc -o $@ $<

src/cba.o: src/cba.c include/cba.h

.PHONY: test
test: test/test_cba
	@$<

test/test_cba.o: test/test_cba.c include/cba.h test/test_cba.h
test/test_cba: test/test_cba.o lib/libcba.a

.PHONY: examples
examples: examples/bloom

examples/bloom: examples/bloom.o lib/libcba.a
examples/bloom.o: examples/bloom.c include/cba.h

.PHONY: clean
clean:
	rm -f src/*.o test/*.o examples/*.o test/test_cba examples/bloom $(LIBS)
