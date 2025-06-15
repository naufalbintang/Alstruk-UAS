#pragma once
#include <iostream>
using namespace std;

class MainView {
public:
    static void tampilkanMenuUtama() {
        cout << "\n===== E-BANKING APP =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Print Hashtable and Tree" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan: ";
    }

    static void tampilkanPesanTidakValid() {
        cout << "Pilihan tidak valid. Coba lagi." << endl;
    }

    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #elif __linux__
            system("clear");
        #endif
    }
};