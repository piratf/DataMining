targets=general.o kmeans.o kmediods.o Node.o Group.o Distance.o Matrix.o knn.o knnopenmp.o id3.o
structs=$(VPATH)/Node.h $(VPATH)/Group.h $(VPATH)/Distance.h
VPATH=headers
CC = g++
# override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
# cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH)))
# cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH))) -std=c++11
cppFlags = $(patsubst %,-I%,$(subst :, ,$(VPATH))) -std=c++11 -pedantic -Wall
openmpFlags = -fopenmp -DOPENMP

.PHONY: all
all: $(targets)
	ar -cr libFunctions.a $(targets)

general.o: $(VPATH)/general.h $(VPATH)/Node.h $(VPATH)/Group.h $(VPATH)/Distance.h general.cpp
	$(CC) general.cpp $(cppFlags) -c -o general.o

kmeans.o: $(structs) general.o kmeans.h kmeans.cpp
	$(CC) kmeans.cpp $(cppFlags) -c -o kmeans.o

kmediods.o: general.o kmediods.h kmediods.cpp
	$(CC) kmediods.cpp $(cppFlags) -c -o kmediods.o

Node.o: Node.h Node.cpp
	$(CC) Node.cpp $(cppFlags) -c -o Node.o

Group.o: Group.h Group.cpp
	$(CC) Group.cpp $(cppFlags) -c -o Group.o

Distance.o: Distance.h Matrix.h Node.h Group.h Distance.cpp
	$(CC) Distance.cpp $(cppFlags) -c -o Distance.o

Matrix.o: Matrix.h Matrix.cpp
	$(CC) Matrix.cpp $(cppFlags) -c -o Matrix.o

knn.o: knn.h knn.cpp
	$(CC) knn.cpp $(cppFlags) -c -o knn.o

knnopenmp.o: knnopenmp.h knnopenmp.cpp
	$(CC) knnopenmp.cpp $(cppFlags) $(openmpFlags) -c -o knnopenmp.o

id3.o: id3.h id3.cpp
	$(CC) id3.cpp $(cppFlags) $(openmpFlags) -c -o id3.o

.PHONY: clean cleanall
cleanall:
	-rm *.a
clean:
	-rm $(targets)
