CILPATH=../obliv-c/
OCC=$(CILPATH)/bin/oblivcc
SRCPATH=../src/
TSTDEPS=test_main.c $(CILPATH)/_build/libobliv.a
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3

default: test_obig

$(CILPATH)/_build/libobliv.a:
	cd $(CILPATH) && ./configure && make RELEASE=1

test_obig: $(TSTDEPS) test_obig.oc test_obig_components/* $(SRCPATH)/obig.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_obig.oc $(SRCPATH)/obig.oc -o $@

clean:
	rm -f test_obig
