CFLAGS = -O
CC = g++

DecisionTree: DecisionTree.o class.o
	$(CC) $(CFLAGS) -o DecisionTree DecisionTree.o class.o
DecisionTree.o: DecisionTree.cpp
	$(CC) $(CFLAGS) -c DecisionTree.cpp
class.o: class.cpp
	$(CC) $(CFLAGS) -c class.cpp
clean:
	rm -f core *.o

