targets = demo.exe
subdir = function
objects = subdir/libFunctions.a
cppFlags = -std=c++11
# cppFlags = -std=c++11 -pedantic -Wall
CC = g++

$(targets): $(objects)
	g++ demo.cpp -Ifunction/headers -Lfunction -lfunctions $(cppFlags) -o demo.exe

subdir/libFunctions.a:
	cd $(subdir) && $(MAKE)

.PHONY: clean cleanall
cleanall: clean
	-cd $(subdir) && $(MAKE) cleanall
	-rm $(targets)
clean:
	-rm $(targets:.exe=.o)
	-cd $(subdir) && $(MAKE) clean
