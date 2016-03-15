#include <cmath>
#include <algorithm>

#include "predictor.hpp"

std::string BimodalSingle::predict() {
    std::vector<respair> results;
    for(int i = 4;i < 12;i++) {
        if(i == 6) continue; // This makes me angry
        size_t s = int(std::pow(2, i));
        bool predictor[s];
        std::fill_n(predictor, s, true);
        respair pair;
        for(auto e : v) {
            if(predictor[e.first % s]) {
                if(e.second)
                    pair.first++;
            }
            else {
                if(!e.second)
                    pair.first++;
            }
            predictor[e.first % s] = e.second;
            pair.second++;
        }
        results.push_back(pair);
    }
    return results_to_string(results);
}
