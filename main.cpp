#include <iostream>
using namespace std;

void login(){
    string username;
    string password;
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    if(username == "admin" && password == "admin123"){
        cout << "Login sebagai admin" << endl;
    }
}

void registrasi(){
    cout << "Registrasi" << endl;
}

int main(){
    // variabel
    char pilihan;
    
    // clear console
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif

    // main program
    cout << "============" << endl;
    cout << "    BANK" << endl;
    cout << "============" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Masukkan pilihan: "; cin >> pilihan;
    switch(pilihan){
    case '1':
        login();
        break;
    case '2':
        registrasi();
        break;
    default:
        break;
    }
}