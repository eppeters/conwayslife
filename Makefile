CXX = g++
CXXFLAGS = --std=c++0x 
CXXFLAGS += -Wall 
#CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3

OBJS = ./libs/life.o

SRCS = ./libs/life.cpp

HEADERS = ./libs/life.h

MAIN = main.cpp

#target: dependencies
#	rule to build
#

main: ${OBJS} ${HEADERS} ${MAIN}
	${CXX} ${CXXFLAGS} ${OBJS} ${MAIN} -o life

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp) -o ${@}
