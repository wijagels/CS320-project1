#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <future>

#include "predictor.hpp"

using std::string;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cerr << "Cyka blyat!" << endl;
        return 1;
    }
    unsigned long long addr;
    string behavior, line;
    ifstream infile(argv[1]);
    vector<std::pair<unsigned long long, bool> > v;
    v.reserve(23532922);
    while(getline(infile, line)) {
        stringstream s(line);
        s >> std::hex >> addr >> behavior;
        v.push_back(std::pair<unsigned long long, bool>(addr, behavior == "T"));
    }
    /*
    unsigned long long t, nt;
    t = nt = 0;
    for(auto e : v) {
        if(e.second) ++t;
        else ++nt;
    }
    */
    /*
    AlwaysTaken at(v);
    AlwaysNotTaken ant(v);
    */
    /*
    auto one = std::async(std::launch::async, [&at]{ return at.predict(); });
    auto two = std::async(std::launch::async, [&ant]{ return ant.predict(); });
    auto pair =  one.get();
    auto pair2 = two.get();
    */
    auto one = std::async(std::launch::async, [&v]{ return AlwaysTaken(v).predict(); });
    auto two = std::async(std::launch::async, [&v]{ return AlwaysNotTaken(v).predict(); });
    auto three = std::async(std::launch::async, [&v]{ return BimodalSingle(v).predict(); });
    auto four = std::async(std::launch::async, [&v]{ return BimodalSaturating(v).predict(); });
    auto five = std::async(std::launch::async, [&v]{ return Gshare(v).predict(); });
    auto six = std::async(std::launch::async, [&v]{ return Tournament(v).predict(); });
    auto out = one.get();
    auto out2 = two.get();
    auto out3 = three.get();
    auto out4 = four.get();
    auto out5 = five.get();
    auto out6 = six.get();
    /*
    auto pair = at.predict();
    auto pair2 = ant.predict();
    */
    std::ofstream os;
    os.open(argv[2]);
    os << out;
    os << out2;
    os << out3;
    os << out4;
    os << out5;
    os << out6;
    return 0;
}
