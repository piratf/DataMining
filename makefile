objects = test.o KMeans.o
targets = test.exe
cppFlags = -std=c++11 -pedantic -Wall
CC = g++

$(targets): $(objects)
	$(CC) $(cppFlags) $(objects) -o $(targets)

test.o: KMeans.h
KMeans.o: KMeans.h

# %.d: %.c
# 	@set -e; rm -f $@; \
#          $(CC) -MM $(cppFlags) $< > $@.$$$$; \
#          sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
#          rm -f $@.$$$$

.PHONY: clean cleanall
cleanall: clean
	-rm $(targets)
clean:
	-rm $(filter %.o, $(objects))
