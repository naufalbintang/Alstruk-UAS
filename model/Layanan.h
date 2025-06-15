#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Layanan {
    string idLayanan;
    string namaLayanan;
    string deskripsi;

    Layanan() = default;

    Layanan(string idLayanan, string namaLayanan, string deskripsi)
        : idLayanan(idLayanan), namaLayanan(namaLayanan), deskripsi(deskripsi) {}
};