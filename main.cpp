#include "hashtable.h"
#include "hashtable_builder.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
	// OpenHashMap<string,int> hashtable(1000);
	// addPopularityData(hashtable);
	// hashtable.printGraph(50);
	// hashtable.printStats();

	// OpenHashMap<string,int> hashtable(40000, [](string key) { return 20000; });
	// addPopularityData(hashtable);
	// hashtable.printGraph(50);
	// hashtable.printStats();

	// OpenHashMap<string,int> hashtable(1000, [](string key) {
	// 	int hashcode = 0;
	// 	for (int i = 0; i < key.length(); i++) {
    //         hashcode += 31 * key[i];
    //     }
	// 	return hashcode;
	// });
	// addPopularityData(hashtable);
	// hashtable.printGraph(50);
	// hashtable.printStats();

	return EXIT_SUCCESS;
}
