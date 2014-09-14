# Copyright (c) 2014, 임경현 (dlarudgus20)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## @file makefile
## @author dlarudgus20
## @copyright The BSD (2-Clause) License

# EatStar makefile
# copied&modified from Clubcos makefile (https://github.com/dlarudgus20/Clubcos)

# config
ifeq ($(CONFIG), Release)
	# ok
else ifeq ($(CONFIG), Debug)
	# ok
else ifeq ($(CONFIG), )
	# default to Debug
	CONFIG := Debug
else
	$(error [CONFIG] '$(CONFIG)': unknown configuration.)
endif

# directories
DIR_BIN := bin/$(CONFIG)
DIR_DEP := dep/$(CONFIG)
DIR_OBJ := obj/$(CONFIG)
DIR_SRC := src

DIR_DEPENS := $(DIR_IMG) $(DIR_BIN) $(DIR_DEP) $(DIR_OBJ) $(DIR_GEN)

# tools
GDB := gdb

# flags
CXXFLAGS += -std=c++11 -I$(DIR_SRC) -Wall -Wextra -Werror -pedantic -Wno-unused-parameter

ifeq ($(CONFIG), Release)
CXXFLAGS += -DNDEBUG -O3 -flto
else
CXXFLAGS += -DDEBUG -ggdb
endif

LIB_FLAGS := -lncursesw

# files
OUTPUT_FILE := $(DIR_BIN)/EatStar

CXX_SOURCES := $(wildcard $(DIR_SRC)/*.cpp)
CXX_OBJECTS := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.cpp.o, $(CXX_SOURCES))

DEPENDENCIES := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_DEP)/%.cpp.d, $(CXX_SOURCES))

# phony targets
.PHONY: all rebuild run rerun run-dbg distclean clean mostlyclean dep-clean save-clean

NODEPEN_TARGETS := rebuild rerun distclean clean mostlyclean dep-clean save-clean

all: $(OUTPUT_FILE)

rebuild:
	make clean
	make

run:
	make all
	$(OUTPUT_FILE)

rerun:
	make clean
	make run

run-dbg:
	$(GDB) $(OUTPUT_FILE)

distclean: clean save-clean
	-rmdir $(DIR_OBJ)
	-rmdir obj
	-rmdir $(DIR_DEP)
	-rmdir dep
	-rmdir $(DIR_BIN)
	-rmdir bin

clean: mostlyclean dep-clean
	-$(RM) $(DIR_BIN)/*
	-$(RM) $(OUTPUT_FILE)

mostlyclean:
	-$(RM) $(DIR_OBJ)/*

dep-clean:
	-$(RM) $(DIR_DEP)/*

save-clean:
	-$(RM) SCORE.NSIII SETTINGS.NSIII

# rules
$(OUTPUT_FILE): $(CXX_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT_FILE) $^ $(LIB_FLAGS) -Xlinker -Map=$(DIR_OBJ)/EatStar.map

$(DIR_OBJ)/%.cpp.o: $(DIR_SRC)/%.cpp | $(DIR_DEPENS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(DIR_DEP)/%.cpp.d: $(DIR_SRC)/%.cpp | $(DIR_DEPENS)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(DIR_OBJ)/$*.cpp.o \
		| sed 's@\($(DIR_OBJ)/$*.cpp.o\)[ :]*@\1 $@ : @g' > $@

$(DIR_DEPENS):
	mkdir -p bin
	mkdir -p $(DIR_BIN)
	mkdir -p dep
	mkdir -p $(DIR_DEP)
	mkdir -p obj
	mkdir -p $(DIR_OBJ)

# include dependencies
ifeq ($(filter $(NODEPEN_TARGETS), $(MAKECMDGOALS)), )
include $(DEPENDENCIES)
endif

