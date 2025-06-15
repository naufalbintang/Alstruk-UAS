#pragma once

#include "../model/Akun.h"
#include "../model/Nasabah.h"
#include "../ds/Hash.h"
#include "../ds/Tree.h"
#include "../utils/utility.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;

class RegisterController {
    private:
        Hash* hashTable;
        BinaryTreeNasabah* treeNasabah;
    
    public:
        RegisterController(Hash* hashTable, BinaryTreeNasabah* treeNasabah) {
            this->hashTable = hashTable;
            this->treeNasabah = treeNasabah;
        }

        void RegisterUser() {
        string username, pin, nik, norekening;
        double saldo;

        cout << endl << "=== REGISTRASI NASABAH ===" << endl;

        // Validasi Username
        while (true) {
            cout << "Masukkan username: ";
            cin >> username;
            if (hashTable->isUsernameExist(username)) {
                cout << "Username sudah terdaftar, coba lagi.\n";
            } else break;
        }

        // Validasi PIN
        while (true) {
            cout << "Masukkan PIN (6 digit): ";
            cin >> pin;
            if (!hashTable->isValidPin(pin)) {
                cout << "PIN harus 6 digit angka.\n";
            } else break;
        }

        // Validasi NIK
        while (true) {
            cout << "Masukkan NIK: ";
            cin >> nik;
            if (hashTable->isNIKExist(nik)) {
                cout << "NIK sudah terdaftar, coba lagi.\n";
            } else break;
        }

        // Input Saldo Awal
        cout << "Masukkan saldo awal: ";
        cin >> saldo;

        // Generate otomatis
        string idNasabah = generateIdNasabah();
        norekening = generateNoRekening();

        // Buat objek Akun dan Nasabah
        Akun akun(username, pin, nik, idNasabah);
        Nasabah nasabah(idNasabah, nik, saldo, norekening, true);

        // Masukkan ke Hash dan Tree
        hashTable->insertAkun(akun);
        treeNasabah->insertTree(nasabah);

        // Konfirmasi
        cout << "\n Registrasi berhasil!" << endl;
        cout << "ID Nasabah   : " << idNasabah << endl;
        cout << "No Rekening  : " << norekening << endl;
        cout << "==============================" << endl;
    }
};
