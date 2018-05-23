#include <iostream>
#include <cstdint>
#include <fstream>
#include "map_min_heap.h"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc <= 1)
	{
		cout << endl << "Usage: ./lfu cache_size file_name" << endl << endl;
		return -1;
	}
	ifstream file;
	int c, start_block, n_blocks, ignore, req_n, loop_its;
	string filename;
	uintmax_t hits, misses, total;

	MAP_MIN_HEAP heap;

	c = start_block = n_blocks = ignore = req_n = loop_its = 0;
	hits = misses = total = 0;

	c = atoi(argv[1]);

	file.open(argv[2]);

	if (!file)
	{
		cout << endl << "File not found. " << endl << endl;
		cout << "Usage: ./lfu 1000 OLTP.lis" << endl << endl;
		return -1;
	}

	while (file >> start_block >> n_blocks >> ignore >> req_n)
	{
		loop_its++;

		for (int block = start_block; block < start_block + n_blocks; block++)
		{
			if (heap.exists(block) == true)
			{
				// it's in the list
				hits ++;
				heap.insert(block);
			}
			else
			{
				// it's not in the list
				misses ++;

				if (heap.size() == c)
				{
					// delete least frequently used element (min)
					// add new element
					heap.extract_min();
				}

				heap.insert(block);

			}

			total++;
		}
	}

	file.close();

	double hit_rate;
	hit_rate = (double) hits / (double) total;
	hit_rate *= 100;

	cout << endl << "Misses: " << misses << endl;
	cout << "Hits: " << hits << endl;
	cout << "Total: " << total << endl;
	cout << endl << "Hit rate: " << hit_rate << endl << endl;

	return 0;


	// MAP_MIN_HEAP heap;
	//
	// for (int i = 1; i < 11; i ++)
	// 	heap.insert(i);
	//
	// for (int i = 1; i < 5; i++)
	// 	heap.insert(i);
	//
	// heap.print();
	// return 0;
}
