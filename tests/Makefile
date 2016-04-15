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
		bench_oram bench_oram_init bench_oscrypt bench_bfs bench_bst bench_omatch


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

%.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) $*.oc -o $*.oo
	cpp -MM $(CFLAGS) $*.oc -MT $*.oo > $*.od

clean:
	rm -f $(BINS:%=$(BIN_OUT_PATH)/%) *.oo *.o *.d *.od
	cd $(SRC_PATH) && make clean
