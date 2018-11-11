#
# Makefile for CS 70 TreeSet Assignment
# 

###############################################################################
# MAKEFILE VARIABLES
###############################################################################

# CXX is the name of the compiler we are using (clang++)

CXX = g++

# CXXFLAGS are the flags we will be passing each compile

CXXFLAGS = -g -std=c++11 -Wall -Wextra -pedantic 

# TARGETS is the list of all programs created when we do "make all"
#   (and which should be deleted when we do "make clean")

TARGETS = Test

###############################################################################
# "PHONY" (BUT USEFUL) MAKEFILE TARGETS
###############################################################################


# "make all" brings all programs up-to-date (recursively)
#     and then runs no commands.

all: $(TARGETS)

# "make clean" brings nothing up to date, but always
#      runs commands to delete all created files

clean:
	rm -f $(TARGETS)
	rm -rf *.o

# "make test" brings all the testing programs up-to-date (recursively)
#       and then runs them.
# You should probably use a more realistic number of buckets than 10
#       for stringhash-test, but the exact number is up to you.

Test: WBBST-test
	./WBBST-test


###############################################################################
# CREATING PROGRAMS
###############################################################################

# "make stringhash-test" brings the relevant .o files up-to-date (recursively)
#      and then links them.
 
# In a command run by the makefile, $^ stands for the things the target
#      depends on (in this case, the list stringhash-test.o stringhash.o")
#      This is useful so that we don't have to duplicate this list
#      both in the dependency list and in the linking command, and we
#      don't have to define a STRINGHASH_TEST_OBJS variable that is
#      used only for these two lines.


# "make hashset-cow-test" brings the relevant .o files up-to-date (recursively)
#      and then links them.

WBBST-test: WBBST-test.o  weightBalancedBST.o testing-logger.o
	$(CXX) $(CXXFLAGS) -o WBBST-test $^


###############################################################################
# GENERATING OBJECT FILES
###############################################################################

# The .o files depend on the corresponding .cpp file and the .hpp
#      files that C++ code includes.
#      In each case, the command to generate the .o file uses
#      our C++ compiler to compile the .cpp file, with the -c flag.
WBBST-test.o: WBBST-test.cpp weightBalancedBST.hpp
	$(CXX) $(CXXFLAGS) -c WBBST-test.cpp

testing-logger.o: testing-logger.cpp testing-logger.hpp
	$(CXX) $(CXXFLAGS) -c testing-logger.cpp

# When/if you need more .o files, their dependencies and the
#    compilation commands would go here.

weightBalancedBST.o: weightBalancedBST.hpp weightBalancedBST.cpp
	$(CXX) $(CXXFLAGS) -c weightBalancedBST.cpp



