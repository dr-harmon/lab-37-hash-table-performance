#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include "hashtable.h"

using namespace std;

TEST_CASE("Put/Exists")
{
	OpenHashMap<int,string> hashtable(10);
	hashtable.put(1, "one");
	hashtable.put(2, "two");
	hashtable.put(3, "three");
	hashtable.put(4, "four");
	hashtable.put(5, "five");
	REQUIRE(hashtable.exists(1));
	REQUIRE(hashtable.exists(2));
	REQUIRE(hashtable.exists(3));
	REQUIRE(hashtable.exists(4));
	REQUIRE(hashtable.exists(5));
	REQUIRE_FALSE(hashtable.exists(0));
	REQUIRE_FALSE(hashtable.exists(6));
}

TEST_CASE("Replace/Size")
{
	OpenHashMap<int,string> hashtable(10);
	REQUIRE(hashtable.getSize() == 0);
	hashtable.put(1, "one");
	REQUIRE(hashtable.getSize() == 1);
	hashtable.put(2, "two");
	REQUIRE(hashtable.getSize() == 2);
	hashtable.put(3, "three");
	REQUIRE(hashtable.getSize() == 3);
	hashtable.put(2, "dos");
	REQUIRE(hashtable.getSize() == 3);
	REQUIRE(hashtable.exists(1));
	REQUIRE(hashtable.exists(2));
	REQUIRE(hashtable.exists(3));
	REQUIRE_FALSE(hashtable.exists(0));
	REQUIRE_FALSE(hashtable.exists(4));
	REQUIRE(hashtable.find(1) == "one");
	REQUIRE(hashtable.find(2) == "dos");
	REQUIRE(hashtable.find(3) == "three");
}

TEST_CASE("Find")
{
	OpenHashMap<int,string> hashtable(10);
	hashtable.put(1, "one");
	hashtable.put(2, "two");
	hashtable.put(3, "three");
	hashtable.put(4, "four");
	hashtable.put(5, "five");
	REQUIRE(hashtable.find(1) == "one");
	REQUIRE(hashtable.find(2) == "two");
	REQUIRE(hashtable.find(3) == "three");
	REQUIRE(hashtable.find(4) == "four");
	REQUIRE(hashtable.find(5) == "five");
	REQUIRE_THROWS(hashtable.find(0));
	REQUIRE_THROWS(hashtable.find(6));
}

TEST_CASE("Erase/Size")
{
	OpenHashMap<int,string> hashtable(10);
	hashtable.put(1, "one");
	hashtable.put(2, "two");
	hashtable.put(3, "three");
	REQUIRE(hashtable.getSize() == 3);
	hashtable.erase(2);
	REQUIRE(hashtable.getSize() == 2);
	REQUIRE_FALSE(hashtable.exists(2));
	REQUIRE_THROWS(hashtable.find(2));
}

TEST_CASE("Chaining")
{
	OpenHashMap<int,string> hashtable(2);
	hashtable.put(1, "one");
	hashtable.put(2, "two");
	hashtable.put(3, "three");
	hashtable.put(4, "four");
	REQUIRE(hashtable.exists(1));
	REQUIRE(hashtable.exists(2));
	REQUIRE(hashtable.exists(3));
	REQUIRE(hashtable.exists(4));
	REQUIRE(hashtable.find(1) == "one");
	REQUIRE(hashtable.find(2) == "two");
	REQUIRE(hashtable.find(3) == "three");
	REQUIRE(hashtable.find(4) == "four");
	REQUIRE(hashtable.getSize() == 4);
}
