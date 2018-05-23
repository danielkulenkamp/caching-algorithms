
#include "page.h"

PAGE::PAGE(int n, int r) {
	page_number = n;
	ref_count = r;
}

int PAGE::increment_ref_count() {
	ref_count += 1;
	return ref_count;
}
