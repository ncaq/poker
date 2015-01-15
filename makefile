ifeq ($(OS), Windows_NT)
	CXX		:= i686-pc-cygwin-g++.exe
	program := poker.exe
else
	CXX		:= g++
	program := poker.elf
endif

CXXFLAGS	+= -std=c++11 -Wall -Wextra -pipe
CXXRELEASE	+= -O2
CXXDEBUG	+= -O0 -fno-inline -ggdb
LDFLAGS		+= 
LDSTATIC	+= -static

SRCS := $(shell find . -iregex ".*\.cpp")
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.deps)

.PHONY:	all static debug run clean

.DEFAULT: all

all: CXXFLAGS += $(CXXRELEASE)
all: $(program)

static: LDFLAGS += $(LDSTATIC)
static: CXXFLAGS += $(CXXRELEASE)
static: $(program)

debug: CXXFLAGS += $(CXXDEBUG)
debug: $(program)

run: debug
	./$(program)

clean:
	find . -regextype posix-extended -iregex '.*\.(o|deps)'|xargs $(RM) -v

$(program): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.deps: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< | sed $(addprefix "$(addprefix s/.*:/,$(subst .deps,.o,$(subst /,\/,$@:))),/)" > $@

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
