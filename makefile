programname = poker

CXX			= clang++
CXXFLAGS	= -Wall -Wextra -std=c++11 -stdlib=libc++ -ggdb
LDFLAGS		= -lncursesw

SRCS := $(shell find . -iregex ".*\.cpp")
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.deps)

.PHONY:	all run clean

all: program

run: all
	./poker

clean:
	find . -regextype posix-extended -iregex '.*\.(o|deps)'|xargs $(RM) $(programname)

program: $(DEPS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(programname) $(OBJS)

%.deps: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< | sed $(addprefix "$(addprefix s/.*:/,$(subst .deps,.o,$(subst /,\/,$@:))),/)" > $@
-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
