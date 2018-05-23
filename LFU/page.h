
#ifndef PAGE_H
#define PAGE_H

class PAGE {
public:
	int page_number;
	int ref_count;

	PAGE(int, int);
	int increment_ref_count();

	bool operator<(const PAGE &a)
	{
		return this->ref_count < a.ref_count;
	}
};

#endif /* PAGE_H */
