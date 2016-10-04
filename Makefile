OBLIVCC = $(OBLIVC_PATH)/bin/oblivcc
OBLIVCH = $(OBLIVC_PATH)/src/ext/oblivc
OBLIVCA = $(OBLIVC_PATH)/_build/libobliv.a
CFLAGS+= -O3 -I/usr/include -I . -I $(SRC_PATH) -DOMATCH_EXTENDED_BENCHMARK

SRC_PATH=src/
LIB_OUT_PATH=build/lib/
ACKLIB = $(LIB_OUT_PATH)/liback.a
DEPS=ackutil.o copy.o copy.oo
SQRT_ORAM_DEPS=decoder.oo shuffle.oo sqrtoram.oo waksman.o
CKT_ORAM_DEPS=block.oo circuit_oram.oo linear_scan_oram.oo nonrecursive_oram.oo utils.oo
ORAM_DEPS = $(SQRT_ORAM_DEPS:%=oram_sqrt/%)  $(CKT_ORAM_DEPS:%=oram_ckt/%) oram.oo
OBJS=$(DEPS) $(ORAM_DEPS) omatch.oo omatch_textbook.oo oqueue.oo osort.oo

TEST_PATH=tests/
TEST_OUT_PATH=build/tests/
TEST_DEPS=test_main.o
TEST_BINS = test_omatch test_omatch_textbook bench_gs bench_rp bench_gs_textbook

default: $(ACKLIB) tests

tests: $(TEST_BINS:%=$(TEST_OUT_PATH)/%)

$(TEST_BINS:%=$(TEST_OUT_PATH)/%): $(TEST_OUT_PATH)/%: $(TEST_PATH)/%.oo $(TEST_DEPS:%=$(TEST_PATH)/%) $(ACKLIB)
	mkdir -p $(TEST_OUT_PATH)
	$(OBLIVCC) -o $@ $(OBLIVCA) $^ -lm

$(ACKLIB): $(OBJS:%=$(SRC_PATH)/%)
	mkdir -p $(LIB_OUT_PATH)
	ar rcs $@ $^

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
	rm -f $(OBJS:%=$(SRC_PATH)/%) $(patsubst %.oo,$(SRC_PATH)/%.od,$(patsubst %.o,$(SRC_PATH)/%.d,$(OBJS))) $(ACKLIB)
	rm -f $(TEST_BINS:%=$(TEST_OUT_PATH)/%) $(TEST_DEPS:%=$(TEST_PATH)/%) $($(pasubst %.oo, %.od, $(TEST_DEPS)):%=$(TEST_PATH)/%) $(TEST_BINS:%=$(TEST_PATH)/%.oo) $(TEST_BINS:%=$(TEST_PATH)/%.od)
