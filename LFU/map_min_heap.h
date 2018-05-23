#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "page.h"

#ifndef MAP_MIN_HEAP_H
#define MAP_MIN_HEAP_H


class MAP_MIN_HEAP {
private:
	static int LEFT(int);
	static int RIGHT(int);
	static int PARENT(int);
	void SWAP(int, int);
	void HEAPIFY(int);
	PAGE minimum();

public:
	std::vector<PAGE> v;
	std::map<int, int> m;

	MAP_MIN_HEAP();
	~MAP_MIN_HEAP();

	// inserts into both the vector and the map
	int insert(int, int);
	int insert(int);
	// removes the least referenced element from both map and vector
	PAGE pop_min();
	// removes the element from the vector, then re-adds it with an incremented value
	int increase_key(int);
	// returns true if the element is in the heap
	bool exists(int);

	PAGE extract_min();
	void print();

	int size();

};

#endif
