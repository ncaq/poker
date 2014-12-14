programname = poker

CXX			= clang++
CXXFLAGS	= -Wall -Wextra -std=c++11 -stdlib=libc++ -ggdb
LDFLAGS		= -lncursesw

SRCS := $(shell ./findcpp.sh)
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.d)

.PHONY:	all run clean

all: program

run: all
	./poker

clean:
	$(RM) $(OBJS) $(DEPS) $(programname)

program: $(DEPS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(programname) $(OBJS)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< | sed $(addprefix "$(addprefix s/.*:/,$(subst .d,.o,$(subst /,\/,$@:))),/)" > $@
-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
