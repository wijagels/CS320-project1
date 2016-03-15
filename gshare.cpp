#include "predictor.hpp"

std::string Gshare::predict() {
    std::vector<respair> results;
    for(int i = 3;i < 12;i++) {
        results.push_back(execute(i));
    }
    return results_to_string(results);
}

respair Gshare::execute(int i) {
    const int s = 2048;
    char predictor[s];
    /*
     * TT = 2, T = 1
     * NT = 0, NNT = -1
     */
    std::fill_n(predictor, s, 2);
    respair pair;
    int mask = (1 << i) -1;
    int ghr = 0;
    for(auto e : this->v) {
        gshare(predictor, pair, s, mask, ghr, e);
    }
    return pair;
}

void Gshare::gshare(char* predictor, respair& pair, const int& s, const int& mask, int& ghr, std::pair<unsigned long, bool> e) {
        if(predictor[(e.first^ghr)%s] > 0) {
            if(e.second)
                pair.first++;
        }
        else {
            if(e.second < 1)
                pair.first++;
        }
        if(e.second) {
            if(predictor[(e.first^ghr) % s] < 2)
                predictor[(e.first^ghr) % s]++;
        }
        else {
            if(predictor[(e.first^ghr) % s] > -1)
                predictor[(e.first^ghr) % s]--;
        }
        pair.second++;
        ghr = (ghr << 1) + e.second;
        ghr = mask & ghr;
}
