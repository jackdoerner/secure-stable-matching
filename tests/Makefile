CILPATH=../obliv-c/
OCC=$(CILPATH)/bin/oblivcc
SRCPATH=../src/
TSTDEPS=test_main.c $(CILPATH)/_build/libobliv.a
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3 -I/usr/include

default: test_obig test_osha256 test_osha512 test_osalsa test_ochacha test_oram test_oscrypt

$(CILPATH)/_build/libobliv.a:
	cd $(CILPATH) && ./configure && make RELEASE=1

test_obig: $(TSTDEPS) test_obig.oc test_obig_components/* $(SRCPATH)/obig.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_obig.oc $(SRCPATH)/obig.oc -o $@

test_osha256: $(TSTDEPS) test_osha256.oc test_osha256_components/* $(SRCPATH)/osha256.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) -lssl -lcrypto test_main.c $(SRCPATH)/util.c test_osha256.oc $(SRCPATH)/osha256.oc -o $@

test_osha512: $(TSTDEPS) test_osha512.oc $(SRCPATH)/osha512.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) -lssl -lcrypto test_main.c $(SRCPATH)/util.c test_osha512.oc $(SRCPATH)/osha512.oc -o $@

test_osalsa: $(TSTDEPS) test_osalsa.oc $(SRCPATH)/osalsa.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_osalsa.oc $(SRCPATH)/osalsa.oc -o $@

test_ochacha: $(TSTDEPS) test_ochacha.oc $(SRCPATH)/ochacha.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_ochacha.oc $(SRCPATH)/ochacha.oc -o $@

test_oram: $(TSTDEPS) test_oram.oc $(SRCPATH)/oram.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_oram.oc $(SRCPATH)/oram.oc -o $@

test_oscrypt: $(TSTDEPS) test_oscrypt.oc $(SRCPATH)/oscrypt.oc $(SRCPATH)/osalsa.oc
	$(OCC) $(CFLAGS) -I . -I $(SRCPATH) test_main.c $(SRCPATH)/util.c test_oscrypt.oc $(SRCPATH)/osalsa.oc $(SRCPATH)/oscrypt.oc -o $@

clean:
	rm -f test_obig test_osha256 test_osha512 test_osalsa test_ochacha test_oram test_oscrypt
