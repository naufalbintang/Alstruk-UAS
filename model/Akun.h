#pragma once

#include <iostream>

using namespace std;

struct Akun {
    string username;
    string pin;
    string nik;
    string IdNasabah;

    Akun() = default;

    Akun(string username, string pin, string nik, string IdNasabah) 
        : username(username), pin(pin), nik(nik), IdNasabah(IdNasabah) {}
};