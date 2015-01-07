ifeq ($(OS), Windows_NT)
	program := poker.exe
else
	program := poker.elf
endif

CXX			= g++
CXXFLAGS	+= -std=c++11 -Wall -Wextra -Werror -pipe
CXXRELEASE	+= -O2 -fomit-frame-pointer #default
CXXDEBUG	+= -O0 -fno-inline -ggdb
LDFLAGS		+= -lncursesw
LDSTATIC	+= -static

SRCS := $(shell find . -iregex ".*\.cpp")
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.deps)

.PHONY:	all debug run clean

.DEFAULT: all

all: CXXFLAGS += $(CXXRELEASE)
all: LDFLAGS += $(LDSTATIC)
all: $(program)

debug: CXXFLAGS += $(CXXDEBUG)
debug: $(program)

run: debug
	./$(program)

clean:
	find . -regextype posix-extended -iregex '.*\.(o|deps)'|xargs $(RM) -v

$(program): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS)

%.deps: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< | sed $(addprefix "$(addprefix s/.*:/,$(subst .deps,.o,$(subst /,\/,$@:))),/)" > $@

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
