# Cache Algorithm Implementations
These implementations were done as part of project 3 of my CSE330 class at ASU Spring 2018 for Dr. Violet Syrotiuk.
The traces files used to test are included in the traces folder.

Least Recently Used (LRU) was implemented using the STL list combined with the STL map to provide constant time lookups.

Adaptive Replacement Cache (ARC) is described in [1]. It keeps track of both frequency and recency, and is implemented similarly to LRU using a list and a map.

Least Frequently Used (LFU) was implemented using a custom mapped heap data structure, to provide constant time lookups with heap structure.

[1] N. Megiddo and D. S. Modha, "Outperforming LRU with an adaptive replacement cache algorithm," in Computer, vol. 37, no. 4, pp. 58-65, April 2004.
doi: 10.1109/MC.2004.1297303
