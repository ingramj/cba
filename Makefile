CFLAGS=-fPIC -I include -ansi -Wall -Wextra -Werror -pedantic -g -O0
LDFLAGS=-fPIC -Wall -Wextra -Werror -g

LIBS=lib/libcba.so lib/libcba.a

.PHONY: all
all: $(LIBS)

lib/libcba.so: src/cba.o
	$(CC) $(LDFLAGS) -shared -o $@ $<

lib/libcba.a: src/cba.o
	ar rc -o $@ $<

src/cba.o: src/cba.c include/cba.h
test/test_cba.o: test/test_cba.c include/cba.h
test/test_cba: test/test_cba.o lib/libcba.a

.PHONY: test
test: test/test_cba
	@test/test_cba

.PHONY: clean
clean:
	rm -f src/cba.o test/test_cba.o test/test_cba $(LIBS)