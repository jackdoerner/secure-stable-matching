LIB_OUT_PATH=../build/lib/
SRC_PATH=./
OBLIVC_PATH=../obliv-c/
OBLIVCC = $(OBLIVC_PATH)/bin/oblivcc
OBLIVCH = $(OBLIVC_PATH)/src/ext/oblivc
OBLIVCA = $(OBLIVC_PATH)/_build/libobliv.a
ACKLIB = $(LIB_OUT_PATH)/liback.a
DEPS=$(SRC_PATH)/util.o $(SRC_PATH)/copy.o $(SRC_PATH)/copy.oo $(SRC_PATH)/endian.oo
SQRT_ORAM_DEPS=$(SRC_PATH)/oram_sqrt/decoder.oo $(SRC_PATH)/oram_sqrt/shuffle.oo $(SRC_PATH)/oram_sqrt/sqrtoram.oo $(SRC_PATH)/oram_sqrt/waksman.o
CKT_ORAM_DEPS=$(SRC_PATH)/oram_ckt/block.oo $(SRC_PATH)/oram_ckt/circuit_oram.oo $(SRC_PATH)/oram_ckt/linear_scan_oram.oo $(SRC_PATH)/oram_ckt/nonrecursive_oram.oo $(SRC_PATH)/oram_ckt/utils.oo
ORAM_DEPS = $(SQRT_ORAM_DEPS) $(CKT_ORAM_DEPS) $(SRC_PATH)/oram.oo
CFLAGS+=-O3 -I/usr/include -I . -I $(SRC_PATH)
OBJS=$(DEPS) $(ORAM_DEPS) $(SRC_PATH)/obig.oo $(SRC_PATH)/ochacha.oo $(SRC_PATH)/ograph.oo $(SRC_PATH)/omatch.oo $(SRC_PATH)/oqueue.oo\
		$(SRC_PATH)/osalsa.oo $(SRC_PATH)/oscrypt.oo $(SRC_PATH)/osearch.oo $(SRC_PATH)/osha256.oo $(SRC_PATH)/osha512.oo $(SRC_PATH)/osort.oo


default: $(OBLIVCA) $(ACKLIB)

$(OBLIVCA):
	cd $(OBLIVC_PATH) && ./configure && make RELEASE=1

$(ACKLIB): $(OBJS)
	mkdir -p $(LIB_OUT_PATH)
	ar rcs $@ $^

-include $(patsubst %.oo,%.od,$(OBJS:.o=.d))

%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o -I $(OBLIVCH)
	cpp -MM $(CFLAGS) $*.c -I $(OBLIVCH) > $*.d

%.oo: %.oc
	$(OBLIVCC) -c $(CFLAGS) $*.oc -o $*.oo
	cpp -MM $(CFLAGS) $*.oc -MT $*.oo > $*.od

clean:
	rm -f $(ACKLIB) $(SRC_PATH)/*.oo $(SRC_PATH)/*.o $(SRC_PATH)/*.d $(SRC_PATH)/*.od $(SRC_PATH)/oram_sqrt/*.oo $(SRC_PATH)/oram_sqrt/*.o $(SRC_PATH)/oram_sqrt/*.od $(SRC_PATH)/oram_sqrt/*.d $(SRC_PATH)/oram_ckt/*.oo $(SRC_PATH)/oram_ckt/*.o $(SRC_PATH)/oram_ckt/*.od $(SRC_PATH)/oram_ckt/*.d