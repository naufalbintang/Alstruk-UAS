#pragma once

#include "../ds/Hash.h"
#include <iostream>
using namespace std;

class LoginController {
private:
    Hash* hashTable;

public:
    LoginController(Hash* hashTable) {
        this->hashTable = hashTable;
    }

    bool loginUser() {
        string username, pin;

        cout << endl << "=== LOGIN NASABAH ===" << endl;
        cout << "Masukkan username : ";
        cin >> username;

        cout << "Masukkan PIN      : ";
        cin >> pin;

        if (hashTable->isNodeFound(username, pin)) {
            cout << "Login berhasil!" << endl;
            cout << "Selamat datang, " << username << "!" << endl;
            return true;
        } else {
            cout << "Login gagal! Username atau PIN salah." << endl;
            return false;
        }
    }
};