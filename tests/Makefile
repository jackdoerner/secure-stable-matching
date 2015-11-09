OBLIVC_PATH=../obliv-c/
OBLIVCC = $(OBLIVC_PATH)/bin/oblivcc
OBLIVCH = $(OBLIVC_PATH)/src/ext/oblivc
OBLIVCA = $(OBLIVC_PATH)/_build/libobliv.a
SRCPATH=../src/
TSTDEPS=test_main.o $(SRCPATH)/util.o
ORAMDEPS=$(SRCPATH)/oram/copy.o $(SRCPATH)/oram/copy.oo $(SRCPATH)/oram/decoder.oo $(SRCPATH)/oram/shuffle.oo $(SRCPATH)/oram/sqrtoram.oo $(SRCPATH)/oram/waksman.o
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3 -I/usr/include -I . -I $(SRCPATH)
BINS = test_obig test_osha256 test_osha512 test_osalsa test_ochacha test_oram test_oscrypt bench_oscrypt

default: $(OBLIVCC) $(BINS)

$(BINS): $(OBLIVCA)
	$(OBLIVCC) -o $@ $^ -lm -lssl -lcrypto

$(OBLIVCA):
	cd $(OBLIVC_PATH) && ./configure && make RELEASE=1

test_obig: $(TSTDEPS) test_obig.oo $(SRCPATH)/obig.oo

test_osha256: $(TSTDEPS) test_osha256.oo $(SRCPATH)/osha256.oo $(SRCPATH)/endian.oo

test_osha512: $(TSTDEPS) test_osha512.oo $(SRCPATH)/osha512.oo $(SRCPATH)/endian.oo

test_osalsa: $(TSTDEPS) test_osalsa.oo $(SRCPATH)/osalsa.oo

test_ochacha: $(TSTDEPS) test_ochacha.oo $(SRCPATH)/ochacha.oo

test_oram: $(TSTDEPS) test_oram.oo $(SRCPATH)/oram.oo $(ORAMDEPS)

test_oscrypt: $(TSTDEPS) test_oscrypt.oo $(SRCPATH)/oscrypt.oo $(SRCPATH)/osha256.oo $(SRCPATH)/osalsa.oo $(SRCPATH)/oram.oo $(SRCPATH)/endian.oo $(ORAMDEPS)

bench_oscrypt: $(TSTDEPS) bench_oscrypt.oo $(SRCPATH)/oscrypt.oo $(SRCPATH)/osha256.oo $(SRCPATH)/osalsa.oo $(SRCPATH)/oram.oo $(SRCPATH)/endian.oo $(ORAMDEPS)

-include $(patsubst %.oo,%.od,$(OBJS:.o=.d))

%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o -I $(OBLIVCH)
	cpp -MM $(CFLAGS) $*.c -I $(OBLIVCH) > $*.d

%.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) $*.oc -o $*.oo
	cpp -MM $(CFLAGS) $*.oc -MT $*.oo > $*.od

clean:
	rm -f $(BINS) *.oo *.o *.d *.dd $(SRCPATH)/*.oo $(SRCPATH)/*.o $(SRCPATH)/*.dd $(SRCPATH)/*.d $(SRCPATH)/oram/*.oo $(SRCPATH)/oram/*.o $(SRCPATH)/oram/*.dd $(SRCPATH)/oram/*.d
