targets = demo.exe
subdir = function
objects = subdir/libFunctions.a
# cppFlags = -std=c++11
cppFlags = -std=c++11 -pedantic -Wall
CC = g++

$(targets): $(objects)
	g++ demo.cpp -I$(subdir)/headers -L$(subdir) -lFunctions $(cppFlags) -o a.out

subdir/libFunctions.a:
	cd $(subdir) && $(MAKE)

.PHONY: clean cleanall
cleanall: clean
	-cd $(subdir) && $(MAKE) cleanall
	-rm $(targets)
clean:
	-rm $(targets:.exe=.o)
	-cd $(subdir) && $(MAKE) clean
