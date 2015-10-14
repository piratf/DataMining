targets=general kmeans kmedoids
VPATH=headers
CC = g++
# override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
# cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH)))
cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH))) -std=c++11
# cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH))) -std=c++11 -pedantic -Wall

.PHONY: all
all: general.o kmeans.o kmedoids.o
	ar -cr libFunctions.a $(foreach n, $(targets), $(n).o)

general.o: $(VPATH)/general.h $(VPATH)/structs.h
	$(CC) general.cpp $(cppFlags) -c -o general.o

kmeans.o: structs.h general.o kmeans.h
	$(CC) kmeans.cpp $(cppFlags) -c -o kmeans.o

kmedoids.o: general.o kmedoids.h
	$(CC) kmedoids.cpp $(cppFlags) -c -o kmedoids.o

.PHONY: clean cleanall
cleanall:
	-rm *.a
clean:
	-rm $(foreach n, $(targets), $(n).o)
