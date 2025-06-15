#pragma once

#include <iostream>
#include "Rekening.h"
#include "Layanan.h"

using namespace std;

struct Nasabah {
    string IdNasabah;
    string nik;
    double saldo;
    string NoRekening;
    bool aktif;

    Nasabah() = default;

    Nasabah(string IdNasabah, string nik, double saldo, string NoRekening, bool aktif = true)
        : IdNasabah(IdNasabah), nik(nik), saldo(saldo), NoRekening(NoRekening), aktif(aktif) {}
};
