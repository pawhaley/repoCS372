// fa2_test.cpp
// Glenn G. Chappell
// 12 Feb 2016
//
// For CS 372 Spring 2016
// Unit tests for Assignment 2, Exercises A, B, C
// Uses the "Catch" C++ Unit-Testing Framework

#define CATCH_CONFIG_MAIN  // We want Catch to write function main
#include "catch.hpp"       // For the "Catch" unit-testing framework

#include "fa2.h"           // For Assignment 2 functions
#include "fa2.h"           // Double inclusion test

#include <vector>
using std::vector;
#include <algorithm>
using std::equal;
#include <cstddef>
using std::size_t;
#include <functional>
using std::function;
using std::bind;
using namespace std::placeholders;
                           // For _1, used with std::bind


// ***** Helper Functions ****


// countInRange
// Given valid data range [first, last), return number of items that lie
// in numeric range [lo, hi].
template<typename FDIter, typename Val>
size_t countInRange(FDIter first, FDIter last,
                    Val lo, Val hi)
{
    size_t count = 0;
    for (auto it = first; it != last; ++it)
    {
        if (lo <= *it && *it <= hi)
        {
            ++count;
        }
    }
    return count;
}


// f1
// Simple int computation: k -> 2k-1.
int f1(int k)
{
    return 2*k-1;
}


// ***** Test Cases *****


TEST_CASE("Exercise A: Returned vectors have correct size", "[ex a]")
{
    vector<double> v;

    v = normRand(1000);
    REQUIRE(v.size() == 1000);

    v = normRand(0);
    REQUIRE(v.size() == 0);

    v = normRand(13);
    REQUIRE(v.size() == 13);

    v = normRand(1);
    REQUIRE(v.size() == 1);
}


TEST_CASE("Exercise A: Returned vectors have same initial values", "[ex a]")
{
    vector<double> v1 = normRand(1000);
    REQUIRE(v1.size() == 1000);
    vector<double> v2;

    v2 = normRand(100);
    REQUIRE(v2.size() == 100);
    REQUIRE(equal(v2.begin(), v2.end(), v1.begin()));

    v2 = normRand(1);
    REQUIRE(v2.size() == 1);
    REQUIRE(equal(v2.begin(), v2.end(), v1.begin()));

    v2 = normRand(10000);
    REQUIRE(v2.size() == 10000);
    REQUIRE(equal(v1.begin(), v1.end(), v2.begin()));
}


TEST_CASE("Exercise A: Distribution of returned values", "[ex a]")
{
    const size_t size = 200000;
    vector<double> v = normRand(size);
    REQUIRE(countInRange(v.begin(), v.end(), 100.-15., 100.+15.)
              > size*0.67);
    REQUIRE(countInRange(v.begin(), v.end(), 100.-15., 100.+15.)
              < size*0.695);
    REQUIRE(countInRange(v.begin(), v.end(), 100., 100000.)
              > size*0.49);
    REQUIRE(countInRange(v.begin(), v.end(), 100., 100000.)
              < size*0.51);
}


TEST_CASE("Exercise B: Returned vectors have correct size", "[ex b]")
{
    vector<int> v;

    v = asyncSquares(100);
    REQUIRE(v.size() == 100);

    v = asyncSquares(0);
    REQUIRE(v.size() == 0);

    v = asyncSquares(23);
    REQUIRE(v.size() == 23);

    v = asyncSquares(1);
    REQUIRE(v.size() == 1);
}


TEST_CASE("Exercise B: Returned vectors have correct values", "[ex b]")
{
    const size_t size = 100;

    vector<int> v = asyncSquares(size);

    vector<int> vv;
    for (size_t i = 0; i != size; ++i)
    {
        vv.push_back(i*i);
    }

    REQUIRE(v == vv);
}


TEST_CASE("Exercise C: Works with function", "[ex c]")
{
    auto g = repeatFunction(f1, 2);

    REQUIRE(g(1) == 1);

    REQUIRE(g(100) == 397);
}


TEST_CASE("Exercise C: Works with lambda", "[ex c]")
{
    auto g = repeatFunction([](int k){ return k-2; }, 5);

    REQUIRE(g(1) == -9);

    REQUIRE(g(100) == 90);
}


TEST_CASE("Exercise C: Works with bind expression", "[ex c]")
{
    auto ff = [](int k, int m) { return k+m; };
    auto f3 = bind(ff, _1, 5);
    auto g = repeatFunction(f3, 4);

    REQUIRE(g(1) == 21);

    REQUIRE(g(100) == 120);
}


TEST_CASE("Exercise C: Works with std::function", "[ex c]")
{
    function<int(int)> f4 = [](int k) { return 3*k; };
    auto g = repeatFunction(f4, 2);

    REQUIRE(g(1) == 9);

    REQUIRE(g(100) == 900);
}


TEST_CASE("Exercise C: Varying 'n' parameter", "[ex c]")
{
    auto f5 = [](int k) { return k+1; };

    auto g1 = repeatFunction(f5, 1);

    REQUIRE(g1(1) == 2);
    REQUIRE(g1(100) == 101);

    auto g10 = repeatFunction(f5, 10);

    REQUIRE(g10(1) == 11);
    REQUIRE(g10(100) == 110);

    auto g100 = repeatFunction(f5, 100);

    REQUIRE(g100(1) == 101);
    REQUIRE(g100(100) == 200);
}

