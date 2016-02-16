//fa2.h
//Parker Whaley
//feb,2016
//a function to compleate assignment 2

#ifndef FA2_h
#define FA2_h
#include <vector>
#include <random>
#include <future>
#include <functional>


//generates a normal distribution using s mercend twister.
inline std::vector<double> normRand(size_t n){
	std::normal_distribution<double> normdist(100,15);
	std::mt19937 generator(123);
	std::vector<double> retval;
	for(int i=0;i<n;i++){
		retval.push_back(normdist(generator));
	}
    return retval;
}

int squre(int i){return i*i;}

//computes squares asyncronusly
inline std::vector<int> asyncSquares(size_t n){
    std::vector< std::future<int> > runners;
    for(int i=0;i<n;i++){
        runners.push_back(std::async(std::launch::async,squre,i));
    }
    std::vector<int> retval;
    for(int i=0;i<n;i++){
        retval.push_back(runners[i].get());
    }
    return retval;
}

int RF(std::function<int(int)> fin,int n,int input){
	for(int i=0;i<n;i++){
		input=fin(input);
	}
	return input;
}


//tried to return a bind to the RF function but that failed this code doesn't work...
auto repeatFunction(std::function<int(int)> fin, int n){
	return fin;
}















#endif
