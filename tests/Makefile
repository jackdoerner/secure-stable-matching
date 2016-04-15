BIN_OUT_PATH=../build/tests/
LIB_OUT_PATH=../build/lib/
OBLIVC_PATH=../obliv-c/
OBLIVCC = $(OBLIVC_PATH)/bin/oblivcc
OBLIVCH = $(OBLIVC_PATH)/src/ext/oblivc
OBLIVCA = $(OBLIVC_PATH)/_build/libobliv.a
ACKLIB = $(LIB_OUT_PATH)/liback.a
SRC_PATH=../src/
DEPS=test_main.o
REMOTE_HOST=localhost
CFLAGS+=-DREMOTE_HOST=$(REMOTE_HOST) -O3 -I/usr/include -I . -I $(SRC_PATH)
BINS = test_obig test_osha256 test_osha512 test_osalsa test_ochacha test_oqueue test_oram test_oscrypt test_ograph test_omatch test_osearch\
		bench_oram.sqrt bench_oram.linear bench_oram.circuit bench_oram_init.sqrt bench_oram_init.linear bench_oram_init.circuit\
		bench_oscrypt.sqrt bench_oscrypt.linear bench_oscrypt.circuit bench_bfs.sqrt bench_bfs.linear bench_bfs.circuit\
		bench_bst.sqrt bench_bst.linear bench_bst.circuit bench_omatch.sqrt bench_omatch.linear bench_omatch.circuit


default: $(OBLIVCC) $(BINS:%=$(BIN_OUT_PATH)/%)

$(BINS:%=$(BIN_OUT_PATH)/%): $(BIN_OUT_PATH)/%: %.oo $(DEPS) $(ACKLIB) $(OBLIVCA)
	mkdir -p $(BIN_OUT_PATH)
	$(OBLIVCC) -o $@ $^ -lm -lssl -lcrypto

$(OBLIVCA):
	cd $(OBLIVC_PATH) && ./configure && make RELEASE=1

$(ACKLIB):
	cd $(SRC_PATH) && make

-include $(patsubst %.oo,%.od,$(OBJS:.o=.d))

%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o -I $(OBLIVCH)
	cpp -MM $(CFLAGS) $*.c -I $(OBLIVCH) > $*.d

%.sqrt.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) -DORAM_OVERRIDE=ORAM_TYPE_SQRT $*.oc -o $*.sqrt.oo
	cpp -MM $(CFLAGS) -DORAM_OVERRIDE=ORAM_TYPE_SQRT $*.oc -MT $*.sqrt.oo > $*.sqrt.od

%.circuit.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) -DORAM_OVERRIDE=ORAM_TYPE_CIRCUIT $*.oc -o $*.circuit.oo
	cpp -MM $(CFLAGS) -DORAM_OVERRIDE=ORAM_TYPE_CIRCUIT $*.oc -MT $*.circuit.oo > $*.circuit.od

%.linear.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) -DORAM_OVERRIDE=ORAM_TYPE_LINEAR $*.oc -o $*.linear.oo
	cpp -MM $(CFLAGS) -DORAM_OVERRIDE=ORAM_TYPE_LINEAR $*.oc -MT $*.linear.oo > $*.linear.od

%.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) $*.oc -o $*.oo
	cpp -MM $(CFLAGS) $*.oc -MT $*.oo > $*.od

clean:
	rm -f $(BINS:%=$(BIN_OUT_PATH)/%) *.oo *.o *.d *.od
	cd $(SRC_PATH) && make clean
