README

These traces are released under the condition that the "ARC" paper must be cited:

Nimrod Megiddo and Dharmendra S. Modha, "ARC: A Self-Tuning, Low Overhead Replacement Cache," USENIX Conference on File and Storage Technologies (FAST 03), San Francisco, CA, pp. 115-130, March 31-April 2, 2003. 

File Format: 
	Every line in every file has four fields. 

	First field: 	starting_block
	Second field: 	number_of_blocks (each block is 512 bytes)
	Third field: 	ignore
	Fourth field: 	request_number (starts at 0)

	Example: first line in P6.lis is
	110765 64 0 0

	110765	starting block
	64		64 blocks each of 512 bytes
			so this represents 64 requests (each of a 512 byte page) from 110765 to 110828
	0		ignore
	0		request number (goes from 0 to n-1)