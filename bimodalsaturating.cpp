#include <cmath>
#include <algorithm>

#include "predictor.hpp"

std::string BimodalSaturating::predict() {
    std::vector<respair> results;
    for (int i = 4; i < 12; i++) {
        if  (i == 6) continue;
        size_t s = static_cast<int>(std::pow(2, i));
        results.push_back(execute(s));
    }
    return results_to_string(results);
}

respair BimodalSaturating::execute(size_t s) {
    char predictor[s];
    /*
     * TT = 2, T = 1
     * NT = 0, NNT = -1
     */
    std::fill_n(predictor, s, 2);
    respair pair;
    for (auto e : this->v) {
        bimodalsaturating(predictor, pair, s, e);
    }
    return pair;
}

void BimodalSaturating::bimodalsaturating(char* predictor, respair& pair, const int& s, std::pair<unsigned long, bool> e) {
        if (predictor[e.first % s] > 0) {
            if (e.second)
                pair.first++;
        } else {
            if (e.second < 1)
                pair.first++;
        }
        if (e.second) {
            if (predictor[e.first % s] < 2)
                predictor[e.first % s]++;
        } else {
            if (predictor[e.first % s] > -1)
                predictor[e.first % s]--;
        }
        pair.second++;
}
