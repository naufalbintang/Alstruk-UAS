#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

// Global counter
inline int globalNasabahCounter = 1;

inline string generateIdNasabah() {
    stringstream ss;
    ss << "NSB" << setw(3) << setfill('0') << globalNasabahCounter++;
    return ss.str();
}

inline string generateNoRekening() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10000000, 99999999);
    return to_string(dis(gen));
}
