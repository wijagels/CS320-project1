#include "predictor.hpp"

std::string Tournament::predict() {
    std::vector<respair> results;
    results.push_back(execute(2048, 11));
    return results_to_string(results);
}

respair Tournament::execute(const size_t s, const int bits) {
    respair pair;
    char gpredictor[s];
    char bpredictor[s];
    /*
     * TT = 2, T = 1
     * NT = 0, NNT = -1
     */
    std::fill_n(gpredictor, s, 2);
    std::fill_n(bpredictor, s, 2);

    char tour[s];
    std::fill_n(tour, s, 0);

    int mask = (1 << bits) -1;
    int ghr = 0;
    for (auto e : this->v) {
        pair.second++;
        respair gr, br;
        Gshare::gshare(gpredictor, gr, s, mask, ghr, e);
        BimodalSaturating::bimodalsaturating(bpredictor, br, s, e);
        if (gr.first == br.first) {
            if (gr.first)
                pair.first++;
        } else {
            if (tour[e.first % s] < 0b10) {
                // Use Gshare, 00, 01
                if (gr.first) {
                    // I was correct
                    pair.first++;
                    if (tour[e.first % s] > 0b00)
                        tour[e.first % s]--;
                } else {
                    // I was wrong
                    if (tour[e.first % s] < 0b11)
                        tour[e.first % s]++;
                }
            } else {
                // Use bimodal, 10, 11
                if (br.first) {
                    // I was correct
                    pair.first++;
                    if (tour[e.first % s] < 0b11)
                        tour[e.first % s]++;
                } else {
                    // I was wrong
                    if (tour[e.first % s] > 0b00)
                        tour[e.first % s]--;
                }
            }
        }
    }
    return pair;
}
