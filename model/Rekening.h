#pragma once

#include <iostream>

using namespace std;

struct Rekening {
    string noRekening;
    double saldo;
    
    Rekening() = default;
    Rekening(string noRekening, double saldo) 
        : noRekening(noRekening), saldo(saldo) {}
};