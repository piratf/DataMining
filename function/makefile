targets=general kmeans kmedoids Node Group Distance Matrix
structs=$(VPATH)/Node.h $(VPATH)/Group.h $(VPATH)/Distance.h
VPATH=headers
CC = g++
# override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
# cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH)))
cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH))) -std=c++11
# cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH))) -std=c++11 -pedantic -Wall

.PHONY: all
all: Node.o Group.o Distance.o general.o kmeans.o kmedoids.o Matrix.o
	ar -cr libFunctions.a $(foreach n, $(targets), $(n).o)

general.o: $(VPATH)/general.h $(VPATH)/Node.h $(VPATH)/Group.h $(VPATH)/Distance.h
	$(CC) general.cpp $(cppFlags) -c -o general.o

kmeans.o: $(structs) general.o kmeans.h
	$(CC) kmeans.cpp $(cppFlags) -c -o kmeans.o

kmedoids.o: general.o kmedoids.h
	$(CC) kmedoids.cpp $(cppFlags) -c -o kmedoids.o

Node.o: Node.h
	$(CC) Node.cpp $(cppFlags) -c -o Node.o

Group.o: Group.h
	$(CC) Group.cpp $(cppFlags) -c -o Group.o

Distance.o: Distance.h Matrix.h
	$(CC) Distance.cpp $(cppFlags) -c -o Distance.o

Matrix.o: Matrix.h
	$(CC) Matrix.cpp $(cppFlags) -c -o Matrix.o

.PHONY: clean cleanall
cleanall:
	-rm *.a
clean:
	-rm $(foreach n, $(targets), $(n).o)
