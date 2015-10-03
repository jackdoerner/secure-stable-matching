CILPATH=../obliv-c/
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3

default: ./a.out

$(CILPATH)/_build/libobliv.a:
	cd $(CILPATH) && ./configure && make RELEASE=1

./a.out: montgomery.oc montgomery.c util.c $(CILPATH)/_build/libobliv.a
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . montgomery.oc montgomery.c util.c

clean:
	rm -f a.out
