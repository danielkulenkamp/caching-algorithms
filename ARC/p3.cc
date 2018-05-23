#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <cstdlib>

using namespace std;

bool debug = false;

// we need four lists and four maps
list<int> T1, T2, B1, B2;
map<int, list<int>::iterator> m_t1, m_t2, m_b1, m_b2;

// state variables for the algorithm
int c, p, T1_size, T2_size, B1_size, B2_size;

// input variables;
ifstream file;
string filename;




int print_list(list<int> &);
int move_front(list<int> &to, list<int> &from, list<int>::iterator from_it);
int REPLACE(int);
int adapt_recent();
int adapt_freq();



int main(int argc, char *argv[])
{
	if (argc <=1)
		{
			cout << endl << "Usage: ./arc cache_size file_name" << endl << endl;
			return -1;
		}

		int start_block, n_blocks, ignore, req_n, loop_its;

	c = start_block = n_blocks = ignore = req_n = loop_its = 0;

	// statistic variables
	uintmax_t hits, misses, total;
	hits = misses = total = 0;


	c = atoi(argv[1]);

	file.open(argv[2]);

	if (!file)
	{
		cout << endl << "File not found. " << endl << endl;
		cout << "Usage: ./arc 1000 OLTP.lis" << endl << endl;
		return -1;
	}

	while (file >> start_block >> n_blocks >> ignore >> req_n)
	{
		loop_its++;
		if (debug)
			cout << "inside while loop " << endl;


		for (int block = start_block; block < start_block + n_blocks; block++)
		{

			// print four lists
			// print size vars
			// print block
			// print p
			if (debug)
			{
				cout << endl << "Before process of request" << endl;
				cout << "Request block: " << block << endl;
				cout << "B1: " ;
				print_list(B1);
				cout << "T1: " ;
				print_list(T1);
				cout << "B2: ";
				print_list(B2);
				cout << "T2: ";
				print_list(T2);
				cout << "p: " << p << endl;
				cout << "T1_size: " << T1_size << endl;
				cout << "T2_size: " << T2_size << endl;
				cout << "B1_size: " << B1_size << endl;
				cout << "B2_size: " << B2_size << endl;

			}

			if (debug)
				cout << "inside for loop" << endl;
			// case 1: x_t is in T1 or T2, HIT
			if (m_t1.find(block) != m_t1.end())
			{
				if (debug)
					cout << "case 1, t1" << endl;
				hits++;
				list<int>::iterator it = m_t1[block];
				move_front(T2, T1, it);
				// need to erase from m_t1 and add to m_t2
				m_t1.erase(block);
				m_t2[block] = T2.begin();
				T2_size++;
				T1_size--;
			} else if (m_t2.find(block) != m_t2.end())
			{
				if (debug)
					cout << "case 1, t2" << endl;
				hits++;
				list<int>::iterator it = m_t2[block];
				move_front(T2, T2, it);

			}
			// case 2: x_t is in B1, MISS
			else if (m_b1.find(block) != m_b1.end())
			{
				if (debug)
					cout << "case 2" << endl;
				misses++;
				// ADAPT for recency
				adapt_recent();
				REPLACE(block);
				list<int>::iterator it = m_b1[block];
				move_front(T2, B1, it);
				m_b1.erase(block);
				m_t2[block] = T2.begin();
				T2_size ++;
				B1_size --;
			}
			// case 3: x_t is in B2, MISS
			else if (m_b2.find(block) != m_b2.end())
			{
				if (debug)
					cout << "case 3 " << endl;
				misses++;
				// ADAPT for frequency
				adapt_freq();
				REPLACE(block);
				list<int>::iterator it = m_b2[block];
				move_front(T2, B2, it);
				m_b2.erase(block);
				m_t2[block] = T2.begin();
				T2_size ++;
				B2_size--;
			}
			// case 4: x_t is not in any list MISS
			else
			{
				if (debug)
					cout << "case 4" << endl;
				misses ++;

				// Case a: L1 = T1 union B1 has exactly c pages
				if (T1_size + B1_size == c)
				{
					if (debug)
						cout << "\tcase a" << endl;
					if (T1_size < c)
					{
						// delete LRU page in B1 and remove from map
						m_b1.erase(B1.back());
						B1.pop_back();
						B1_size --;
						REPLACE(block);
					} else
					{
						// This means that B1 is empty
						// Delete LRU page in T1
						m_t1.erase(T1.back());
						T1.pop_back();
						T1_size --;
					}
				}
				// case b: L1 = T1 union B1 has less than c pages
				else if (T1_size + B1_size < c)
				{
					if (debug)
						cout << "\tcase b" << endl;
					if (T1_size + T2_size + B1_size + B2_size >= c)
					{
						// delete LRU page in B2 if The size of all lists is 2c
						if (T1_size + T2_size + B1_size + B2_size == 2 * c)
						{
							// delete LRU page in B2
							m_b2.erase(B2.back());
							B2.pop_back();
							B2_size --;
						}
						if (debug)
							cout << "Just before replace" << endl;
						REPLACE(block);
					}
				}

				// finally put x_t into the MRU position of T1
				T1.push_front(block);
				m_t1[block] = T1.begin();
				T1_size ++;
			}

			total++;

			if (debug)
			{
				cout << "After process of request" << endl;
				cout << "Request block: " << block << endl;
				cout << "B1: " ;
				print_list(B1);
				cout << "T1: " ;
				print_list(T1);
				cout << "B2: ";
				print_list(B2);
				cout << "T2: ";
				print_list(T2);
				cout << "p: " << p << endl;
				cout << "T1_size: " << T1_size << endl;
				cout << "T2_size: " << T2_size << endl;
				cout << "B1_size: " << B1_size << endl;
				cout << "B2_size: " << B2_size << endl;
				cout << endl;

			}

		} // end for loop
	} // end while loop

	file.close();


	// cout << "B1: " ;
	// print_list(B1);
	// cout << "T1: " ;
	// print_list(T1);
	// cout << "B2: ";
	// print_list(B2);
	// cout << "T2: ";
	// print_list(T2);
	//

	double hit_rate;
	hit_rate = (double) hits / (double) total;
	hit_rate *= 100;

	cout << endl;
	if (debug)
	{
		cout << "cache size: " << c << endl;
		cout << "filename: " << argv[2] << endl;
		cout << "Hits: " << hits << endl;
		cout << "Misses: " << misses << endl;
		cout << "Total: " << total << endl;
	}

	cout << "Hit rate: " << hit_rate << endl << endl;

}

int print_list(list<int> &lst)
{
	for (list<int>::iterator i = lst.begin(); i != lst.end(); i++)
		cout << *i << " ";

	cout << endl;

	return 0;

}

int move_front(list<int> &to, list<int> &from, list<int>::iterator from_it)
{
	if (from_it != to.begin())
		to.splice(to.begin(), from, from_it);

	return 0;
}

int REPLACE(int x_t)
{
	list<int>::iterator it1, it2;
	if ( (T1_size > 0) && ( (T1_size > p) || (m_b2.find(x_t) != m_b2.end() && T1_size == p) ) )
	{
		// delete the LRU page in T1 and move it to MRU position in B1
		if (debug)
			cout << "Entered Replace with x_t: " << x_t << endl;
		it1= T1.end();
		it1 --;
		move_front(B1, T1, it1);
		it2 = B1.begin();
		m_t1.erase(*it2);
		m_b1[*it2] = B1.begin();
		B1_size++;
		T1_size--;
	} else
	{
		if (debug)
			cout << "Inside else block in REPLACE" << endl;
		// delete the LRU page in T2 and move it to MRU position in B2
		it1 = T2.end();
		it1 --;
		move_front(B2, T2, it1);
		it2 = B2.begin();
		m_t2.erase(*it2);
		m_b2[*it2] = B2.begin();
		B2_size++;
		T2_size--;
	}
	return 0;
}

int adapt_recent()
{
	int d1;

	if (B1_size >= B2_size)
		d1 = 1;
	else
	{
		if (B1_size > 0)
			d1 = B2_size / B1_size;
		else
			d1 = B2_size; // making B1_size 1
	}

	if (p + d1 > c)
		p = c;
	else
		p += d1;

	return p;
}

int adapt_freq()
{
	int d2;

	if (B2_size >= B1_size)
		d2 = 1;
	else
	{
		if (B2_size > 0)
			d2 = B1_size / B2_size;
		else
			d2 = B1_size;
	}

	if (p - d2 > 0)
		p -= d2;
	else
		p = 0;

	return p;
}
