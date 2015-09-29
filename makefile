targets = demo.exe
objects = $(targets:.exe=.o) general.o kmeans.o kmedoids.o
cppFlags = -std=c++11 -pedantic -Wall
CC = g++

$(targets): $(objects)
	$(CC) $(cppFlags) $(objects) -o $(targets)

test.o: kmeans.h
general.o: general.h
kmeans.o: structs.h general.o kmeans.h
kmedoids.o: kmedoids.h
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
