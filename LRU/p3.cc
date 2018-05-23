#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <cstdint>

using namespace std;

int print_list(list<int> &lst)
{
	for (list<int>::iterator i = lst.begin(); i != lst.end(); i++)
		cout << *i << " ";

	cout << endl;

	return 0;

}
int move_front(list<int> &lst, list<int>::iterator i)
{
	if (i != lst.begin())
		lst.splice(lst.begin(), lst, i, next(i));

	return 0;
}


int main(int argc, char *argv[])
{
	ifstream file;
	int c, start_block, n_blocks, ignore, req_n, loop_its;
	c = start_block = n_blocks = ignore = req_n = loop_its = 0;
	string filename;

	uintmax_t hits, misses, total;
	hits = misses = total = 0;

	map<int, list<int>::iterator> m;
	list<int> l;

	map<int, list<int>::iterator>::iterator map_it;

	c = atoi(argv[1]);

	file.open(argv[2]);

	if (!file)
		return-1;

	while (file >> start_block >> n_blocks >> ignore >> req_n)
	{
		loop_its++;

		for (int block = start_block; block < start_block + n_blocks; block++)
		{
			// check each request

			// if block is in the list
			if (m.find(block) != m.end())
			{
				// it is in the list
				hits ++;
				list<int>::iterator it = m[block];
				move_front(l, it);
				//move to first position
			} else
			{
				// it's not in the list
				misses++;
				if (l.size() == c)
				{
					// delete last element
					m.erase(l.back());
					l.pop_back();

				}
				// add number to list at first position,
				// add to hash map
				l.push_front(block);
				m[block] = l.begin();
			}


			total++;
		}
	}

	file.close();

	double hit_rate;
	hit_rate = (double) hits / (double) total;
	hit_rate *= 100;


	// cout << "Hits: " << hits << endl;
	// cout << "Misses: " << misses << endl;
	// cout << "Total: " << total << endl;
	cout << endl << "Hit rate: " << hit_rate  << endl <<  endl;
	// cout << "Loop iterations: " << loop_its << endl;

	return 0;
}
