#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <future>

#include "predictor.hpp"

using std::string;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Cyka blyat!" << std::endl;
        return 1;
    }
    unsigned long long addr;
    string behavior, line;
    std::ifstream infile(argv[1]);
    std::vector<std::pair<unsigned long long, bool> > v;
    v.reserve(23532922);
    while (std::getline(infile, line)) {
        std::stringstream s(line);
        s >> std::hex >> addr >> behavior;
        v.push_back(std::pair<unsigned long long, bool>(addr, behavior == "T"));
    }
    std::future<std::string> res[6];
    res[0] = std::async(std::launch::async, [&v]{ return AlwaysTaken(v).predict(); });
    res[1] = std::async(std::launch::async, [&v]{ return AlwaysNotTaken(v).predict(); });
    res[2] = std::async(std::launch::async, [&v]{ return BimodalSingle(v).predict(); });
    res[3] = std::async(std::launch::async, [&v]{ return BimodalSaturating(v).predict(); });
    res[4] = std::async(std::launch::async, [&v]{ return Gshare(v).predict(); });
    res[5] = std::async(std::launch::async, [&v]{ return Tournament(v).predict(); });
    std::ofstream os;
    os.open(argv[2]);
    for (size_t i = 0; i < 6; i++) {
        os << res[i].get();
    }
    return 0;
}
