#pragma once
#include <vector>
#include <string>
#include <sstream>

typedef std::vector<std::pair<unsigned long long, bool> > brancharr;

class Predictor {
    public:
        Predictor(const brancharr& vec) : v(vec) {}
        virtual std::string predict() = 0;
        const std::vector<std::pair<unsigned long long, bool> >& v;
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
