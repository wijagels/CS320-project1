#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

typedef std::vector<std::pair<unsigned long long, bool> > brancharr;
typedef std::pair<unsigned long, unsigned long> respair;

class Predictor {
    public:
        Predictor(const brancharr& vec) : v(vec) {}
        virtual std::string predict() = 0;
        const std::vector<std::pair<unsigned long long, bool> >& v;
        std::string results_to_string(std::vector<respair> results) {
            std::ostringstream oss;
            std::for_each(results.begin(), --results.end(), [&oss](respair &p){
                oss << p.first << "," << p.second << "; ";
            });
            oss << results.back().first << "," << results.back().second << ";";
            oss << std::endl;
            return oss.str();
        }
};

class AlwaysTaken : public Predictor {
    public:
        AlwaysTaken(const brancharr& vec) : Predictor(vec) {}
        std::string predict() override;
};

class AlwaysNotTaken : public Predictor {
    public:
        AlwaysNotTaken(const brancharr& vec) : Predictor(vec) {}
        std::string predict() override;
};

class BimodalSingle : public Predictor {
    public:
        BimodalSingle(const brancharr& vec) : Predictor(vec) {}
        std::string predict() override;
};

class BimodalSaturating : public Predictor {
    public:
        BimodalSaturating(const brancharr& vec) : Predictor(vec) {}
        static void bimodalsaturating(char*, respair&, const int&, std::pair<unsigned long, bool>);
        respair execute(size_t);
        std::string predict() override;
};

class Gshare : public Predictor {
    public:
        Gshare(const brancharr& vec) : Predictor(vec) {}
        static void gshare(char*, respair&, const int&, const int&, int&, std::pair<unsigned long, bool>);
        respair execute(int);
        std::string predict() override;
};


class Tournament : public Predictor {
    public:
        Tournament(const brancharr& vec) : Predictor(vec) {}
        respair execute(const size_t, const int);
        std::string predict() override;
};
