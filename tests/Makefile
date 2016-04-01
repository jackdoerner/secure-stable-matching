OBLIVC_PATH=../obliv-c/
OBLIVCC = $(OBLIVC_PATH)/bin/oblivcc
OBLIVCH = $(OBLIVC_PATH)/src/ext/oblivc
OBLIVCA = $(OBLIVC_PATH)/_build/libobliv.a
SRC_PATH=../src/
DEPS=test_main.o $(SRC_PATH)/util.o $(SRC_PATH)/copy.o $(SRC_PATH)/copy.oo $(SRC_PATH)/uint128.o
SQRT_ORAM_DEPS=$(SRC_PATH)/oram_sqrt/decoder.oo $(SRC_PATH)/oram_sqrt/shuffle.oo $(SRC_PATH)/oram_sqrt/sqrtoram.oo $(SRC_PATH)/oram_sqrt/waksman.o
CKT_ORAM_DEPS=$(SRC_PATH)/oram_ckt/block.oo $(SRC_PATH)/oram_ckt/circuit_oram.oo $(SRC_PATH)/oram_ckt/linear_scan_oram.oo $(SRC_PATH)/oram_ckt/nonrecursive_oram.oo $(SRC_PATH)/oram_ckt/utils.oo
ORAM_DEPS = $(SQRT_ORAM_DEPS) $(CKT_ORAM_DEPS) $(SRC_PATH)/oram.oo
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3 -I/usr/include -I . -I $(SRC_PATH)
BINS = test_obig test_osha256 test_osha512 test_osalsa test_ochacha test_oqueue test_oram test_oscrypt test_ograph test_omatch test_osearch

default: $(OBLIVCC) $(BINS)

$(BINS): $(OBLIVCA)
	$(OBLIVCC) -o $@ $^ -lm -lssl -lcrypto

$(OBLIVCA):
	cd $(OBLIVC_PATH) && ./configure && make RELEASE=1

test_obig: $(DEPS) test_obig.oo $(SRC_PATH)/obig.oo

test_osha256: $(DEPS) test_osha256.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/endian.oo

test_osha512: $(DEPS) test_osha512.oo $(SRC_PATH)/osha512.oo $(SRC_PATH)/endian.oo

test_osalsa: $(DEPS) test_osalsa.oo $(SRC_PATH)/osalsa.oo

test_ochacha: $(DEPS) test_ochacha.oo $(SRC_PATH)/ochacha.oo

test_oram: $(DEPS) test_oram.oo $(ORAM_DEPS)

test_oscrypt: $(DEPS) test_oscrypt.oo $(SRC_PATH)/oscrypt.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/osalsa.oo $(SRC_PATH)/endian.oo $(ORAM_DEPS)

test_oqueue: $(DEPS) test_oqueue.oo $(SRC_PATH)/oqueue.oo

test_ograph: $(DEPS) test_ograph.oo $(SRC_PATH)/ograph.oo $(SRC_PATH)/oqueue.oo $(ORAM_DEPS)

test_omatch: $(DEPS) test_omatch.oo $(SRC_PATH)/omatch.oo $(SRC_PATH)/oqueue.oo $(SRC_PATH)/osort.oo $(ORAM_DEPS)

test_osearch: $(DEPS) test_osearch.oo $(SRC_PATH)/osearch.oo $(ORAM_DEPS)

bench_oscrypt: $(DEPS) bench_oscrypt.oo $(SRC_PATH)/oscrypt.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/osalsa.oo $(SRC_PATH)/endian.oo $(ORAM_DEPS)

bench_bfs: $(DEPS) bench_bfs.oo $(SRC_PATH)/ograph.oo $(SRC_PATH)/oqueue.oo $(ORAM_DEPS)

bench_omatch: $(DEPS) bench_omatch.oo $(SRC_PATH)/omatch.oo $(SRC_PATH)/oqueue.oo $(ORAM_DEPS)

bench_bst: $(DEPS) bench_bst.oo $(SRC_PATH)/osearch.oo $(ORAM_DEPS)

bench_oram: $(DEPS) bench_oram.oo $(ORAM_DEPS)

bench_oram_init: $(DEPS) bench_oram_init.oo $(ORAM_DEPS)

-include $(patsubst %.oo,%.od,$(OBJS:.o=.d))

%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o -I $(OBLIVCH)
	cpp -MM $(CFLAGS) $*.c -I $(OBLIVCH) > $*.d

%.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) $*.oc -o $*.oo
	cpp -MM $(CFLAGS) $*.oc -MT $*.oo > $*.od

clean:
	rm -f $(BINS) *.oo *.o *.d *.dd $(SRC_PATH)/*.oo $(SRC_PATH)/*.o $(SRC_PATH)/*.dd $(SRC_PATH)/*.d $(SRC_PATH)/oram_sqrt/*.oo $(SRC_PATH)/oram_sqrt/*.o $(SRC_PATH)/oram_sqrt/*.dd $(SRC_PATH)/oram_sqrt/*.d $(SRC_PATH)/oram_ckt/*.oo $(SRC_PATH)/oram_ckt/*.o $(SRC_PATH)/oram_ckt/*.dd $(SRC_PATH)/oram_ckt/*.d
