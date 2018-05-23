run: main

main: main.o map_min_heap.o page.o
	g++ -o lfu main.o map_min_heap.o page.o

main.o: main.cpp map_min_heap.h page.h
	g++ -c main.cpp

map_min_heap.o: map_min_heap.cpp map_min_heap.h page.h
	g++ -c map_min_heap.cpp

page.o: page.cpp page.h
	g++ -c page.cpp

clean:
	rm *.o

cleanAll:
	rm *.o lfu
