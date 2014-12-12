CXX			=	g++
CXXFLAGS	=	-std=c++11 -ggdb -Wall -Wextra
LDFLAGS		=	-lcurses

SRCS := $(shell ./findcpp.sh)
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.d)

.PHONY:	all clean

all: main

clean:
	$(RM) $(OBJS) $(DEPS)

main: $(DEPS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o main $(OBJS)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< | sed $(addprefix "$(addprefix s/.*:/,$(subst .d,.o,$(subst /,\/,$@:))),/)" > $@
-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
