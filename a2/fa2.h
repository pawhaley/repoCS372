#ifndef FA2_h
#define FA2_h
#include <vector>
#include <random>
#include <future>
#include <functional>



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


std::function<int(int)> repeatFunction(std::function<int(int)> fin, int n){
	return fin;
	auto lam=[fin](int n){fin(n);};
	std::function<int(int)> ret=std::bind(fin,1);
}













#endif
