.PHONY: clean

bfi: bfi.c
	${CC} bfi.c -o bfi -static -fPIC -O2 ${CFLAGS} ${LDFLAGS}
	strip -s bfi

clean:
	rm -rf bfi
