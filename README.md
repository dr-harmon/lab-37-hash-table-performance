# Lab 37: Hash Table Performance

In this lab, we will run some experiments to learn about hash table performance and the impact of changing hash codes and table sizes.

In `hashtable.h` you will find the `OpenHashMap` class. It is identical to the previous lab except for some enhancements for performance analysis:

* The size of each bucket is tracked in `HashtableEntry`. (The `std::forward_list` class has no `size()` method so we must keep track of it ourselves.)
* The hash code is customizable. By default, it uses the `std::hash` functor but you can provide your own hash code as a lambda in the constructor.
* There are new functions to print hash table statistics (`printStats`) and a visualization of the bucket sizes (`printGraph`).

Also included is a real-world data set from the [UCI Machine Learning Repository](https://archive.ics.uci.edu/dataset/332/online+news+popularity). It maps a list of URLs from the news website [Mashable](https://mashable.com) to their popularity, as measured by the number of times each URL is shared on social media. You can load this data set into an instance of `OpenHashMap<string,int>` by calling `addPopularityData`. (See `main` for an example.)

## Performance Comparison

To begin, study the tests in `performance_test.cpp`. They include the following benchmarks:

* Linear search of 100k keys
* Binary search of 100k keys
* Hash table search of 100k keys with table sizes of 1k, 5k, 10k, 50k, and 100k

Before you run them, what are your predictions? For example, which data structure will have the best performance? How will changing the hash table size affect its performance?

Run the benchmarks and see if your predictions were correct.

## Load Factor and Collisions

A key indicator of hash table performance is its _load factor_, or λ, which is defined as the number of elements in the hash table divided by the number of its buckets. In other words, it is the average number of elements per bucket.

To explore load factor, run the following code in `main`:

	OpenHashMap<string,int> hashtable(1000);
	addPopularityData(hashtable);
	hashtable.printGraph(50);
	hashtable.printStats();

This will print a visualization of the hash table's buckets followed by some vital statistics such as load factor and total number of collisions.

What would happen to the load factor and number of collisions if the hash table bucket size were to go up or down?

Try changing the bucket size to 500, 2000, and 20,000 (or any number that you like) and see how it affects the statistics. Were your predictions correct?

## An Evil Hash Code

The `std::hash<string>` functor is a "good" hash code for strings because it distributes the keys into buckets evenly. This can be observed in the graph, as all buckets are rougly the same size.

What if the hash code were _not_ good? How would that impact the load factor and performance?

Devise an "evil" hash code that gives the hash table poor performance, then run the previous experiment using your evil function and a large bucket size of 40,000. Verify the "evilness" of your hash code by printing the hash table's graph and statistics. (Note: Each bar in the graph shows the _average_ size for a particular set of buckets and therefore may appear smaller than expected.)

With the "evil" hash code, what did you notice about the performance of `addPopularityData`? Why did the performance change?

## Polynomial Hash Codes

In section 9.2.3, the textbook describes polynomial hash codes and their importance for strings and other variable-length objects. For example, one way to hash the string `s` is with the following summation:

    31 * s[0] + 31 * s[1] + ... + 31 * s[n-1]

Run the previous experiment using this polynomial hash code. Would you say this is a "good" hash code or an "evil" hash code? What type of hash code do you think the `std::hash<string>` functor uses?

Also, what is significant about the number 31? (Hint: Try different numbers close to 31 and observe how the number of collisions and the maximum bucket size are affected.)
