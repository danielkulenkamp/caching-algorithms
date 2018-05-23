#include "map_min_heap.h"


MAP_MIN_HEAP::MAP_MIN_HEAP() {
	std::cout << "Testing heap constructor" << std::endl;
}

MAP_MIN_HEAP::~MAP_MIN_HEAP() {
	std::cout << "Testing Destructor" << std::endl;
}


// private Functions

int MAP_MIN_HEAP::LEFT(int i)
{
	return 2 * i;
}

int MAP_MIN_HEAP::RIGHT(int i)
{
	return 2 * i + 1;
}

int MAP_MIN_HEAP::PARENT(int i)
{
	return i / 2;
}

void MAP_MIN_HEAP::SWAP(int a, int b)
{
	// here we need to swap the two elements, and update them in the map
//	print();
	// swap the values
	int temp_ref, temp_num;
	temp_ref = v[a].ref_count;
	temp_num = v[a].page_number;
	v[a].ref_count = v[b].ref_count;
	v[a].page_number = v[b].page_number;
	v[b].ref_count = temp_ref;
	v[b].page_number = temp_num;

	// swap the location in the map
	m[v[a].page_number] = a;
	m[v[b].page_number] = b;
	//std::cout << "SWAP" << std::endl;
//	print();
}

void MAP_MIN_HEAP::HEAPIFY(int i) {
	int l, r, smallest;

	l = LEFT(i);
	r = RIGHT(i);

	if (l <= v.size() && v[l-1].ref_count < v[i-1].ref_count)
	{
//		std::cout << "smallest = l = " << l << std::endl;
		smallest = l;
	} else
	{
//		std::cout << "smallest = i = " << i << std::endl;
		smallest = i;
	}

	if (r <= v.size() && v[r - 1].ref_count < v[smallest - 1].ref_count)
	{
//		std::cout << "smallest = r = " << r << std::endl;
		smallest = r;
	}

	if (smallest != i)
	{
	//	std::cout << "smallest != i" << std::endl;
		SWAP(smallest - 1, i - 1);
		HEAPIFY(smallest);
	}

}

PAGE MAP_MIN_HEAP::minimum()
{
	return v[0];
}


// public functions

int MAP_MIN_HEAP::insert(int page_num, int ref_count)
{
	// check if the page is in the vector (using map)
	// if it is, then INCREASE KEY it
	// if it isn't, push it back, and then heapify at that point

	if (exists(page_num))
	{
		//std::cout << page_num << " exists" << std::endl;
		increase_key(page_num);
		return 1;
	}
	else
	{
		//std::cout << "before inserting" << std::endl;
		//print();
		v.push_back(PAGE(page_num, ref_count));
		int i = v.size();
		m[page_num] = i - 1;


		while (i > 1 && v[PARENT(i) - 1].ref_count > ref_count)
		{
			SWAP(i - 1, PARENT(i) - 1);
			i = PARENT(i);
		}




		return 2;
	}

	return -1;
}

int MAP_MIN_HEAP::insert(int page_num)
{
	return insert(page_num, 1);
}

bool MAP_MIN_HEAP::exists(int page_num)
{
		if (m.find(page_num) != m.end())
		{
			// it is in the heap
			return true;
		}
		else
		{
			return false;
		}
}

int MAP_MIN_HEAP::increase_key(int page)
{
	// the page has been used again, so we need to increment its ref ref_count

	// we need to first remove the item, and then re-add it with the incremented value
	if (exists(page))
	{
		int loc = m[page];
	//	std::cout << "loc: " << loc << std::endl;

		int temp_ref_count = v[loc].ref_count;
		int temp_page_num = v[loc].page_number;

		v[loc].ref_count = -1;
	//	std::cout << "moving item to min spot: loc - " << loc << std::endl;
	//	print();

		// here we shouldn't do heapify, we should just move them up

		int current_location = loc + 1;

		while (current_location > 1 && v[PARENT(current_location) - 1].ref_count > v[current_location - 1].ref_count)
		{
			SWAP(current_location - 1, PARENT(current_location)-1);
			current_location = PARENT(current_location);
		}
		//HEAPIFY(PARENT(loc+1));

		// extract min
		extract_min();

		//v.erase(v.begin(), v.begin() + 1);
		m.erase(page);

		if (m.find(page) != m.end())
		{
			std::cout << "IT STILL EXISTS AND SHOULDN't" << std::endl;
		}

		// add back in

		insert(page, temp_ref_count + 1);
		//std::cout << "after inserting " << std::endl;
	//	print();
		return 1;


	}
	else
	{
		return -1;
	}
}

PAGE MAP_MIN_HEAP::extract_min()
{
	if (v.size() == 0)
	{
		std::cout << "No elements to delete" << std::endl;
		return PAGE(0,0);
	}
	else
	{
		int r, n;
		r = v[0].ref_count;
		n = v[0].page_number;
		PAGE p(v[0].ref_count, v[0].page_number);
		v[0].page_number = v[v.size() - 1].page_number;
		v[0].ref_count = v[v.size() - 1].ref_count;
		v.pop_back();
		m.erase(n);
	//	std::cout << "p: " << n << std::endl;

		if (m.find(n) != m.end())
		{
			std::cout << "ExtractMin: IT STILL EXISTS AND SHOULDN't" << std::endl;
		}

		HEAPIFY(1);
		return p;
	}
}

void MAP_MIN_HEAP::print()
{
	std::cout << "heap: ";
	for (int i = 0; i < v.size(); i++)
		std::cout << "(" << v[i].page_number << "," << v[i].ref_count << "), ";
	std::cout << std::endl;

	std::cout << "map: ";
	for (std::map<int, int>::const_iterator it = m.begin(); it != m.end(); ++it)
	{
		std::cout << "(" << it->first << "," << it->second << "), ";
	}
	std::cout << std::endl;

}

int MAP_MIN_HEAP::size()
{
	return v.size();
}
