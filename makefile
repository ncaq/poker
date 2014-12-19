ifeq ($(OS), Windows_NT)
	program := poker.exe
else
	program := poker.elf
endif

CXX			= clang++
CXXFLAGS	+= -std=c++11 -stdlib=libc++ -Wall -Wextra -Werror -pipe
CXXRELEASE	+= -O2 -fomit-frame-pointer #default
CXXDEBUG	+= -ggdb
LDFLAGS		+= -lncursesw

SRCS := $(shell find . -iregex ".*\.cpp")
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.deps)

.PHONY:	all debug run clean

.DEFAULT: all

all: CXXFLAGS += $(CXXRELEASE)
all: $(program)

debug: CXXFLAGS += $(CXXDEBUG)
debug: $(program)

run: debug
	./$(program)

clean:
	find . -regextype posix-extended -iregex '.*\.(o|deps)'|xargs $(RM)

$(program): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS)

%.deps: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< | sed $(addprefix "$(addprefix s/.*:/,$(subst .deps,.o,$(subst /,\/,$@:))),/)" > $@

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
