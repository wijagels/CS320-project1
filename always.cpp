#include "predictor.hpp"

std::string AlwaysTaken::predict() {
    std::pair<unsigned long long, unsigned long long> p;
    for(auto e : this->v) {
        if(e.second)
            p.first++;
        p.second++;
    }
    std::ostringstream oss;
    oss << p.first << "," << p.second << ";" << std::endl;
    return oss.str();
}


std::string AlwaysNotTaken::predict() {
    std::pair<unsigned long long, unsigned long long> p;
    for(auto e : this->v) {
        if(!e.second)
            p.first++;
        p.second++;
    }
    std::ostringstream oss;
    oss << p.first << "," << p.second << ";" << std::endl;
    return oss.str();
}
