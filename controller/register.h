#pragma once
#include <iostream>
using namespace std;

//import dari folder controller
#include "login.h"

//import dari folder model
#include "../model/Hash.h"

void registrasi(Hash &h){
    string username{};
    string pin{};
    string nik{};

    cout << "=================" << endl;
    cout << "  MENU REGISTER" << endl;
    cout << "=================" << endl;
    cout << "Masukkan username: "; cin >> username;

    // verifikasi username apakah sudah ada di hash table atau belum
    if(h.isUsernameExist(username)){
        cout << "Username sudah terdaftar" << endl;
        return;
    }

    // verifikasi pin harus berupa digit dan harus 6 digit
    while(true){
        cout << "Masukkan pin: "; cin >> pin;
        if(pin.length() == 6 && all_of(pin.begin(), pin.end(), ::isdigit)){
            break;
        }else{
            cout << "Pin harus berupa angka dan berjumlah 6 digit" << endl;
        }
    }

    cout << "Masukkan nik: "; cin >> nik;
    h.insertHash(username, pin, nik);
}