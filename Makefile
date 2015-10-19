CONFIG=config.mk
include ./$(CONFIG)

#CXX	:= g++
#CXXFLAGS := -fno-strict-aliasing -fno-common -g -m64 -O2 -fwrapv -O3 -Wall
#CXXFLAGS += -g -m64 -O2 -O3 -Wall -fPIC -DBUILD_RELIC=1 -DBUILD_MIRACL=0
CXXFLAGS += -fPIC

# should be set by codegen
csrc := src
rsrc := relic
msrc := miracl
util := builtin
subdir := $(util)/*.o $(rsrc)/*.o $(msrc)/*.o $(csrc)/*.o
INCLUDES += -I$(csrc) -I$(incdir) -I$(util)
EXT := a
ifeq ($(OS), Linux)
    LDFLAGS = -shared
    SHLIB := so
else ifeq ($(OS), Darwin)
    SHLIB := dylib
    LDFLAGS = -dynamiclib
endif

OBJECTS	:= $(csrc)/CharmDictZR.o $(csrc)/CharmListInt.o $(csrc)/CharmListStr.o $(csrc)/CharmListZR.o \
           $(csrc)/CharmListG1.o $(csrc)/CharmListG2.o $(csrc)/CharmListGT.o $(csrc)/CharmList.o $(csrc)/Element.o

RELIC_OBJECTS := $(rsrc)/Builtin.o $(rsrc)/relic_api.o $(rsrc)/common.o
MIRACL_OBJECTS := $(msrc)/MiraclAPI.o

COMMON_OBJECTS := $(util)/util.o $(util)/policy.tab.o $(util)/SecretUtil.o $(util)/DFA.o $(util)/Benchmark.o

CHARM := charm
LIB_RELIC := libCharmRelic.$(EXT)
LIB_MIRACL := libCharmMiracl$(CURVE).$(EXT)
SHLIB_MIRACL := libCharmMiracl$(CURVE).$(SHLIB)
CHARM_LIB := $(CHARM_LIB).$(EXT)

RLIB    := -lrelic_s
# TODO: add a better build Makefile for MIRACL
MLIB	:= $(libdir)/miracl-$(CURVE).a
 
# link SDL object file with miracl lib 
#.PHONY: $(NAME)
#$(NAME): $(OBJECTS)
#	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) $(LIB) -o $(NAME)

# compile sourcefiles
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all
all: $(CHARM_LIB)

.PHONY: sub
sub:
	$(MAKE) -C $(util)/

$(LIB_RELIC): sub $(OBJECTS) $(RELIC_OBJECTS)
	$(CXX) $(LDFLAGS) -o $(LIB_RELIC) $(OBJECTS) $(RELIC_OBJECTS) $(COMMON_OBJECTS) $(RLIB)

$(LIB_MIRACL): sub $(OBJECTS) $(MIRACL_OBJECTS)
	cp $(MLIB) $(LIB_MIRACL)
	$(AR) rc $(LIB_MIRACL) $(OBJECTS) $(MIRACL_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -m64 $(LDFLAGS) -o $(SHLIB_MIRACL) $(OBJECTS) $(MIRACL_OBJECTS) $(COMMON_OBJECTS) $(MLIB)

# TODO: write a test.cpp that links to the CHARM_LIB
test: $(LIB_MIRACL)
	$(CXX)

.PHONY: install
install: $(CHARM_LIB)
	$(INSTALL_PROG) $(CHARM_LIB) $(libdir)
        #$(INSTALL_PROG) *.h $(incdir)

distclean:
	rm -f *.o *.log *.a *.$(SHLIB) $(subdir) $(NAME) $(CONFIG)
clean:
	rm -f *.o *.a *.$(SHLIB) $(subdir) $(NAME)

