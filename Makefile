bin/testTableEntry:	testTableEntry.cpp TableEntry.h HashTable.h testHashTable.cpp testBSTree.cpp BSTREE.h BSTreeDict.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp
	g++ -o bin/testHashTable testHashTable.cpp
	g++ -o bin/testBSTree testBSTree.cpp

clean:
	rm -rf *.o *.gch bin
	
	