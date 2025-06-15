#pragma once

#include "../model/Akun.h"
#include "../model/Nasabah.h"
#include "../ds/Hash.h"
#include "../ds/Tree.h"
#include "../utils/utility.h"
#include <iostream>

using namespace std;

void loadDummyData(Hash& hash, BinaryTreeNasabah& tree) {
    // Dummy 1
    string id1 = generateIdNasabah();
    string rek1 = generateNoRekening();
    Akun akun1("admin", "234567", "1234567890", id1);
    Nasabah nasabah1(id1, "1234567890", 500000, rek1);

    // Dummy 2
    string id2 = generateIdNasabah();
    string rek2 = generateNoRekening();
    Akun akun2("adelio", "123456", "1112223334", id2);
    Nasabah nasabah2(id2, "1112223334", 2500000, rek2);

    string id3 = generateIdNasabah();
    string rek3 = generateNoRekening();
    Akun akun3("boy", "909080", "2223334445", id3);
    Nasabah nasabah3(id3, "2223334445", 3000000, rek3);

    string id4 = generateIdNasabah();
    string rek4 = generateNoRekening();
    Akun akun4("rizki", "808070", "3334445556", id4);
    Nasabah nasabah4(id4, "3334445556", 3500000, rek4);

    string id5 = generateIdNasabah();
    string rek5 = generateNoRekening();
    Akun akun5("naufal", "707060", "4445556667", id5);
    Nasabah nasabah5(id5, "4445556667", 4000000, rek5);

    // Masukkan ke struktur data
    hash.insertAkun(akun1);
    hash.insertAkun(akun2);
    hash.insertAkun(akun3);
    hash.insertAkun(akun4);
    hash.insertAkun(akun5);

    tree.insertTree(nasabah1);
    tree.insertTree(nasabah2);
    tree.insertTree(nasabah3);
    tree.insertTree(nasabah4);
    tree.insertTree(nasabah5);

    cout << "Dummy data berhasil dibuat!\n";
}