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
# instead of .a
#EXT := so
#EXT := dylib

EXT := a

OBJECTS	:= $(csrc)/CharmDictZR.o $(csrc)/CharmListInt.o $(csrc)/CharmListStr.o $(csrc)/CharmListZR.o \
           $(csrc)/CharmListG1.o $(csrc)/CharmListG2.o $(csrc)/CharmListGT.o $(csrc)/CharmList.o $(csrc)/Element.o

RELIC_OBJECTS := $(rsrc)/Builtin.o $(rsrc)/relic_api.o $(rsrc)/common.o
MIRACL_OBJECTS := $(msrc)/MiraclAPI.o

COMMON_OBJECTS := $(util)/util.o $(util)/policy.tab.o $(util)/SecretUtil.o $(util)/DFA.o $(util)/Benchmark.o

CHARM := charm
CHARM_LIB1 := libCharmRelic.$(EXT)
CHARM_LIB2 := libCharmMiracl$(CURVE).$(EXT)
CHARM_LIB := $(CHARM_LIB).$(EXT)

# for Linux
#LDFLAGS = -shared
# for OS X
LDFLAGS = -dynamiclib -current_version 0.1 -install_name ./$(CHARM_LIB_DYN)

RLIB    := -lrelic
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

$(CHARM_LIB1): sub $(OBJECTS) $(RELIC_OBJECTS)
	$(CXX) $(LDFLAGS) -o $(CHARM_LIB1) $(OBJECTS) $(RELIC_OBJECTS) $(COMMON_OBJECTS) $(RLIB)

$(CHARM_LIB2): sub $(OBJECTS) $(MIRACL_OBJECTS)
	cp $(MLIB) $(CHARM_LIB2)
	$(AR) rc $(CHARM_LIB2) $(OBJECTS) $(MIRACL_OBJECTS) $(COMMON_OBJECTS)
	#$(CXX) $(LDFLAGS) -o $(CHARM_LIB2) $(OBJECTS) $(MIRACL_OBJECTS) $(COMMON_OBJECTS) $(MLIB)

.PHONY: install
install: $(CHARM_LIB)
	$(INSTALL_PROG) $(CHARM_LIB) $(libdir)
        #$(INSTALL_PROG) *.h $(incdir)

distclean:
	rm -f *.o *.log $(subdir) $(NAME) $(CHARM_LIB) $(CONFIG)
clean:
	rm -f *.o $(subdir) $(NAME) $(CHARM_LIB) 

