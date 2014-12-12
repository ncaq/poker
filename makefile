CXX			=	g++
CXXFLAGS	=	-std=c++11 -ggdb -Wall -Wextra
LDFLAGS		=	-lcurses

.PHONY:	all clean
.SUFFIXES:	.cpp .o

all:	main

clean:
	$(RM) $(OBJS) $(DEPS)

SRCS := $(shell ./findcpp.sh)
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.d)

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o main

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c -MMD $<

# %.d: %.cpp
# 	$(CXX) -MM $<  >  $@
