#include <cmath>
#include <algorithm>

#include "predictor.hpp"

std::string BimodalSingle::predict() {
    std::vector<std::pair<unsigned long long, unsigned long long> > results;
    for(int i = 4;i < 12;i++) {
        size_t s = int(std::pow(2, i));
        bool predictor[2];
        std::fill_n(predictor, 2, true);
        for(auto e : v) {
        }
    }
    std::ostringstream oss;
    for(auto p : results) {
        oss << p.first << "," << p.second << "; ";
    }
    oss << std::endl;
    return oss.str();
}
