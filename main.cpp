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
    v.reserve(14796021);
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
    auto three = std::async(std::launch::async, [&v]{ return AlwaysTaken(v).predict(); });
    auto four = std::async(std::launch::async, [&v]{ return AlwaysNotTaken(v).predict(); });
    auto five = std::async(std::launch::async, [&v]{ return AlwaysTaken(v).predict(); });
    auto six = std::async(std::launch::async, [&v]{ return AlwaysNotTaken(v).predict(); });
    auto out = one.get();
    auto out2 = two.get();
    /*
    auto pair = at.predict();
    auto pair2 = ant.predict();
    */
    cout << out;
    cout << out2;
    return 0;
}
