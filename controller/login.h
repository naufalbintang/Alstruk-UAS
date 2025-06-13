#pragma once
#include <iostream>
using namespace std;

//import dari folder controller
#include "register.h"

//import dari folder model
#include "../model/Hash.h"

void login(Hash &h){
    string username{};
    string pin{};

    cout << "==============" << endl;
    cout << "  MENU LOGIN" << endl;
    cout << "==============" << endl;
    cout << "Masukkan username: "; cin >> username;
    cout << "Masukkan pin: "; cin >> pin;
    if(h.isNodeFound(username, pin)){
        if(username == "admin" && pin == "admin123"){
            cout << "Login sebagai admin" << endl; // menu admin ada di sini
        }else{
            cout << "Login sebagai nasabah dengan username " << username << endl; // menu nasabah ada di sini
        }
    }else{
        cout << "Username atau pin salah" << endl;
    }
}
