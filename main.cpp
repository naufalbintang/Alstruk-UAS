#include <iostream>
#include <algorithm>

// import dari folder model
#include "controller/login.h"
#include "controller/register.h"
#include "model/Hash.h"
using namespace std;

int main(){
    char pilihan{};
    bool exit = false;
    Hash h{};
    
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif

    while(!exit){
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan: "; cin >> pilihan;
        
        switch (pilihan){
            case '1':
                registrasi(h);
                break;
            case '2':
                login(h);
                break;
            case '0':
                exit = true;
                break;
            default:
            cout << "Pilihan tidak valid" << endl;
        }
    }
    return 0;
}