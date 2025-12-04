bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

clean:
bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -std=c++17 -Wall -Wextra -O2 -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: testHashTable.cpp HashTable.h Dict.h TableEntry.h
	mkdir -p bin
	g++ -std=c++17 -Wall -Wextra -O2 -o bin/testHashTable testHashTable.cpp

bin/testBSTree: testBSTree.cpp BSTree.h BSNode.h
	mkdir -p bin
	g++ -std=c++17 -Wall -Wextra -O2 -o bin/testBSTree testBSTree.cpp

clean:
	rm -rf *.o *.gch bin
	rm -rf *.o *.gch bin
