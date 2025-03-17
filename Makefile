
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -g -fsanitize=address -fsanitize=undefined

SRCDIR    := src
GTESTDIR  := gtest
OBJDIR    := obj

EXE_DIJK  := dijkstras
EXE_LADDER:= ladder
EXE_TEST  := tests

GTEST_LIB := -lgtest -lgtest_main -pthread -fsanitize=address -fsanitize=undefined

$(shell mkdir -p $(OBJDIR))

# Dijkstra’s
DIJKSTRAS_SRC  := $(SRCDIR)/dijkstras.cpp
DIJKSTRAS_MAIN := $(SRCDIR)/dijkstras_main.cpp
DIJKSTRAS_OBJS := $(OBJDIR)/dijkstras.o $(OBJDIR)/dijkstras_main.o

# Ladder
LADDER_SRC  := $(SRCDIR)/ladder.cpp
LADDER_MAIN := $(SRCDIR)/ladder_main.cpp
LADDER_OBJS := $(OBJDIR)/ladder.o $(OBJDIR)/ladder_main.o

# GTest
GTEST_SRC   := $(GTESTDIR)/student_gtests.cpp
GTEST_MAIN  := $(GTESTDIR)/gtestmain.cpp
GTEST_OBJS  := $(OBJDIR)/student_gtests.o $(OBJDIR)/gtestmain.o


all: $(EXE_DIJK) $(EXE_LADDER) $(EXE_TEST)


$(EXE_DIJK): $(DIJKSTRAS_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/dijkstras.o: $(DIJKSTRAS_SRC) $(SRCDIR)/dijkstras.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/dijkstras_main.o: $(DIJKSTRAS_MAIN) $(SRCDIR)/dijkstras.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXE_LADDER): $(LADDER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/ladder.o: $(LADDER_SRC) $(SRCDIR)/ladder.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/ladder_main.o: $(LADDER_MAIN) $(SRCDIR)/ladder.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXE_TEST): $(GTEST_OBJS) $(OBJDIR)/dijkstras.o $(OBJDIR)/ladder.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

$(OBJDIR)/student_gtests.o: $(GTEST_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/gtestmain.o: $(GTEST_MAIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXE_DIJK) $(EXE_LADDER) $(EXE_TEST)

.PHONY: all clean
