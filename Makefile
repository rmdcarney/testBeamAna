######
##  Default configuration
##
## Modify this configuration by creating a local.config file and resetting the
## variables there. See local.config.sample for an example and a description
## of all used variables.

MODE = DEBUG
AR = ar

CPP = g++
CPPFLAGS += -Wall -Wextra -Wno-unused-variable -Wno-unused-function\
	     $(shell root-config --cflags) -I$(BOOSTINC)\
	    -I./ana -I./tools 
CPPFLAGS_DEBUG += -g -O0
CPPFLAGS_RELEASE += -O2 -DNDEBUG

LD = g++
LDFLAGS += `root-config --ldflags` -L$(BOOSTLIB)
LDFLAGS_DEBUG +=
LDFLAGS_RELEASE += 
LIBS =  -lboost_thread$(BOOSTLDADD) -lboost_system$(BOOSTLDADD) -lboost_filesystem$(BOOSTLDADD) $(shell root-config --libs)

BIN = bin
SRC = src
ANA = ana
BUILD = build

# Set build mode specific variables
CPPFLAGS += $(CPPFLAGS_$(MODE))
LDFLAGS += $(LDFLAGS_$(MODE))

######
##  File lists

SRC_FILES = $(wildcard $(SRC)/*.cxx)
ANA_FILES = $(wildcard $(ANA)/*.cpp)

SRC_DEPS = $(patsubst $(SRC)/%.cxx,$(BUILD)/%.d,$(SRC_FILES))
ANA_DEPS = $(patsubst $(ANA)/%.cpp,$(BUILD)/%.d,$(ANA_FILES))

ALL_DEPS = $(SRC_DEPS) $(ANA_DEPS)

SRC_OBJS = $(patsubst $(SRC)/%.cxx,$(BUILD)/%.o,$(SRC_FILES))
ANA_OBJS = $(patsubst $(ANA)/%.cpp,$(BUILD)/%.o,$(ANA_FILES))
ALL_OBJS = $(SRC_OBJS) $(ANA_OBJS) histoViewerDict.cpp

TARGETS = $(patsubst $(SRC)/%.cxx,$(BIN)/%,$(SRC_FILES))

######
##  Targets

all: analysis $(TARGETS)

analysis: $(BUILD)/libTB_ana.a

help:
	@echo # Use 'make' to create all programs
	@echo # Use 'make analysis' to create the libTB_ana.a
	@echo # Special targets:
	@echo "#   list           - List all targets"
	@echo "#   mkinfo         - List makefile internals"
	@echo "#   help           - Show this help message"

# Dependency file creation
$(BUILD)/%.d: $(SRC)/%.cxx
	@$(CPP) $(CPPFLAGS) -MM -MT $(patsubst $(SRC)/%.cxx,$(BUILD)/%.o,$<) $< > $@


$(BUILD)/%.d: $(ANA)/%.cpp
	@$(CPP) $(CPPFLAGS) -MM -MT $(patsubst $(ANA)/%.cpp,$(BUILD)/%.o,$<) $< > $@

# Object creation
$(BUILD)/%.o:
	@echo [Compiling] $@
	@$(CPP) $(CPPFLAGS) -c $< -o $@
        
# Target
$(BIN)/%: $(BUILD)/%.o  $(ANA_OBJS)
	@echo [Linking] $@
	@$(LD) $(LDFLAGS) $<  $(ANA_OBJS) $(LIBS) -o $@

$(BUILD)/libTB_ana.a: $(ANA_OBJS)
	@echo [Creating] $@
	@$(AR) rcs $@ $(ANA_OBJS)

-include $(ALL_DEPS)

clean:
	@$(RM) $(ALL_OBJS) $(ALL_DEPS) $(TARGETS) $(BUILD)/libTB_ana.a 
	@echo "[Clean] … done!"

list:
	@echo Target List
	@echo ===========
	@echo $(TARGETS)

mkinfo:
	@echo Make Variables
	@echo ==============
	@echo MODE = $(MODE)
	@echo
	@echo CPP = $(CPP)
	@echo CPPFLAGS = $(CPPFLAGS)
	@echo LD = $(LD)
	@echo LDFLAGS = $(LDFLAGS)
	@echo
	@echo Program Files
	@echo =============
	@echo Source files:
	@echo "    $(SRC_FILES)"
	@echo Dependency files:
	@echo "    $(SRC_DEPS)"
	@echo Object files:
	@echo "    $(SRC_OBJS)"
	@echo 
	@echo Analysis Files
	@echo =============
	@echo Source files:
	@echo "    $(ANA_FILES)"
	@echo Dependency files:
	@echo "    $(ANA_DEPS)"
	@echo Object files:
	@echo "    $(ANA_OBJS)"
	@echo 
        
.PHONY: clean distclean mkinfo help
