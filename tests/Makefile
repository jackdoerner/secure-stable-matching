OBLIVC_PATH=../obliv-c/
OBLIVCC = $(OBLIVC_PATH)/bin/oblivcc
OBLIVCH = $(OBLIVC_PATH)/src/ext/oblivc
OBLIVCA = $(OBLIVC_PATH)/_build/libobliv.a
SRC_PATH=../src/
TST_DEPS=test_main.o $(SRC_PATH)/util.o
SQRT_ORAM_DEPS=$(SRC_PATH)/oram/copy.o $(SRC_PATH)/oram/copy.oo $(SRC_PATH)/oram/decoder.oo $(SRC_PATH)/oram/shuffle.oo $(SRC_PATH)/oram/sqrtoram.oo $(SRC_PATH)/oram/waksman.o
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3 -I/usr/include -I . -I $(SRC_PATH)
BINS = test_obig test_osha256 test_osha512 test_osalsa test_ochacha test_oram test_oscrypt test_oscrypt_linear test_oram_linear test_oqueue test_ograph test_omatch\
		test_oram_ckt bench_oscrypt bench_oscrypt_linear bench_oram bench_oram_linear bench_oram_init bench_oram_init_linear bench_bfs

default: $(OBLIVCC) $(BINS)

$(BINS): $(OBLIVCA)
	$(OBLIVCC) -o $@ $^ -lm -lssl -lcrypto

$(OBLIVCA):
	cd $(OBLIVC_PATH) && ./configure && make RELEASE=1

test_obig: $(TST_DEPS) test_obig.oo $(SRC_PATH)/obig.oo

test_osha256: $(TST_DEPS) test_osha256.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/endian.oo

test_osha512: $(TST_DEPS) test_osha512.oo $(SRC_PATH)/osha512.oo $(SRC_PATH)/endian.oo

test_osalsa: $(TST_DEPS) test_osalsa.oo $(SRC_PATH)/osalsa.oo

test_ochacha: $(TST_DEPS) test_ochacha.oo $(SRC_PATH)/ochacha.oo

test_oram: $(TST_DEPS) test_oram.oo $(SRC_PATH)/oram.oo $(SQRT_ORAM_DEPS)

test_oram_linear: $(TST_DEPS) test_oram.oo $(SRC_PATH)/oram_linear.oo

test_oscrypt: $(TST_DEPS) test_oscrypt.oo $(SRC_PATH)/oscrypt.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/osalsa.oo $(SRC_PATH)/endian.oo $(SRC_PATH)/oram.oo $(SQRT_ORAM_DEPS)

test_oscrypt_linear: $(TST_DEPS) test_oscrypt.oo $(SRC_PATH)/oscrypt.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/osalsa.oo $(SRC_PATH)/endian.oo $(SRC_PATH)/oram_linear.oo

test_oqueue: $(TST_DEPS) test_oqueue.oo $(SRC_PATH)/oqueue.oo $(SRC_PATH)/oram.oo $(SQRT_ORAM_DEPS)

test_ograph: $(TST_DEPS) test_ograph.oo $(SRC_PATH)/ograph.oo $(SRC_PATH)/oqueue.oo $(SRC_PATH)/oram.oo $(SQRT_ORAM_DEPS)

bench_oscrypt: $(TST_DEPS) bench_oscrypt.oo $(SRC_PATH)/uint128.o $(SRC_PATH)/oscrypt.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/osalsa.oo $(SRC_PATH)/endian.oo $(SRC_PATH)/oram.oo $(SQRT_ORAM_DEPS)

bench_oscrypt_linear: $(TST_DEPS) bench_oscrypt.oo $(SRC_PATH)/uint128.o $(SRC_PATH)/oscrypt.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/osalsa.oo $(SRC_PATH)/endian.oo $(SRC_PATH)/oram_linear.oo

test_omatch: $(TST_DEPS) test_omatch.oo $(SRC_PATH)/omatch.oo $(SRC_PATH)/oqueue.oo $(SRC_PATH)/oram_sqrt.oo $(SQRT_ORAM_DEPS)

bench_bfs: $(TST_DEPS) bench_bfs.oo $(SRC_PATH)/oram.oo $(SRC_PATH)/ograph.oo $(SRC_PATH)/oqueue.oo $(SQRT_ORAM_DEPS)

bench_oram: $(TST_DEPS) bench_oram.oo $(SRC_PATH)/oram.oo $(SQRT_ORAM_DEPS)

bench_oram_linear: $(TST_DEPS) bench_oram.oo $(SRC_PATH)/oram_linear.oo

bench_oram_init: $(TST_DEPS) bench_oram_init.oo $(SRC_PATH)/oram.oo $(SQRT_ORAM_DEPS)

bench_oram_init_linear: $(TST_DEPS) bench_oram_init.oo $(SRC_PATH)/oram_linear.oo

-include $(patsubst %.oo,%.od,$(OBJS:.o=.d))

%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o -I $(OBLIVCH)
	cpp -MM $(CFLAGS) $*.c -I $(OBLIVCH) > $*.d

%.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) $*.oc -o $*.oo
	cpp -MM $(CFLAGS) $*.oc -MT $*.oo > $*.od

clean:
	rm -f $(BINS) *.oo *.o *.d *.dd $(SRC_PATH)/*.oo $(SRC_PATH)/*.o $(SRC_PATH)/*.dd $(SRC_PATH)/*.d $(SRC_PATH)/oram/*.oo $(SRC_PATH)/oram/*.o $(SRC_PATH)/oram/*.dd $(SRC_PATH)/oram/*.d
