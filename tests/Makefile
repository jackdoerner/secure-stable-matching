CILPATH=../obliv-c/
OCC=$(CILPATH)/bin/oblivcc
SRCPATH=../src/
TSTDEPS=test_main.c $(CILPATH)/_build/libobliv.a
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3 -I/usr/include

default: test_obig test_osha256 test_osha512 test_osalsa20 test_oscrypt

$(CILPATH)/_build/libobliv.a:
	cd $(CILPATH) && ./configure && make RELEASE=1

test_obig: $(TSTDEPS) test_obig.oc test_obig_components/* $(SRCPATH)/obig.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_obig.oc $(SRCPATH)/obig.oc -o $@

test_osha256: $(TSTDEPS) test_osha256.oc test_osha256_components/* $(SRCPATH)/osha256.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) -lssl -lcrypto test_main.c $(SRCPATH)/util.c test_osha256.oc $(SRCPATH)/osha256.oc -o $@

test_osha512: $(TSTDEPS) test_osha512.oc $(SRCPATH)/osha512.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) -lssl -lcrypto test_main.c $(SRCPATH)/util.c test_osha512.oc $(SRCPATH)/osha512.oc -o $@

test_osalsa20: $(TSTDEPS) test_osalsa20.oc $(SRCPATH)/osalsa20.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_osalsa20.oc $(SRCPATH)/osalsa20.oc -o $@

test_oscrypt: $(TSTDEPS) test_oscrypt.oc $(SRCPATH)/oscrypt.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_oscrypt.oc $(SRCPATH)/oscrypt.oc -o $@

clean:
	rm -f test_obig
