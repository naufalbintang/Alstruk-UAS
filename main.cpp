#include <iostream>
using namespace std;

// hash function
struct Node{
    string username{};
    string password{};
    Node* next;

    Node(string usn, string pass){
        username = usn;
        password = pass;
        next = nullptr;
    }
};

const int TABLESIZE = 10;
Node* hashTable[TABLESIZE] = {};

int hashFuction(string password){
    return tolower(password[0]) % TABLESIZE;
}

void insertHash(string username, string password){
    int index = hashFuction(password);
    Node* newNode = new Node(username, password);

    for(int i{}; i < TABLESIZE; i++){
        Node* travel = hashTable[i];
        while(travel != nullptr){
            if(username == travel->username){
                cout << "Username sudah terdaftar" << endl;
                return;
            }
            travel = travel->next;
        }
    }

    if(hashTable[index] == nullptr){
        hashTable[index] = newNode;
    }else{
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

void printHash(){
    cout << endl;
    for(int i{}; i < TABLESIZE; i++){
        cout << "[" << i << "]";
        Node* travel = hashTable[i];
        while(travel != nullptr){
            cout << " (" << travel->username << ", " << travel->password << ") ->";
            travel = travel->next;
        }
        cout << "nullptr" << endl;
    }
    cout << endl;
}

void login(){
    string username{};
    string password{};
    int index{};

    cout << "Masukkan username: "; cin >> username;
    cout << "Masukkan password: "; cin >> password;


    // login sebagai admin
    if(username == "admin" && password == "admin123"){
        cout << "Login sebagai admin" << endl;
        return;
    }

    // login sebagai nasabah
    index = hashFuction(password);
    Node* travel = hashTable[index];
    while(travel != nullptr){
        if(username == travel->username && password == travel->password){
            cout << "Berhasil login sebagai " << travel->username << endl;
            return;
        }
        travel = travel->next;
    }
    cout << "Akun tidak ditemukan" << endl;

}

void registrasi(){
    string username{};
    string password{};

    cout << "===================" << endl;
    cout << "  MENU REGISTRASI" << endl;
    cout << "===================" << endl;
    cout << "Masukkan username: "; cin >> username;
    cout << "Masukkan password: "; cin >> password;

    insertHash(username, password);
}

int main(){
    // variabel
    char pilihan;
    bool exit = false;

    // akun dummy
    insertHash("admin", "admin123");
    insertHash("nasabah", "nasabah123");

    // clear console
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif

    // main program
    while(!exit){
        cout << "============" << endl;
        cout << "    BANK" << endl;
        cout << "============" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Tampilkan hash table" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan: "; cin >> pilihan;
        switch(pilihan){
        case '0':
            exit = true;
            break;
        case '1':
            login();
            break;
        case '2':
            registrasi();
            break;
        case '3':
            printHash();
            break;
        default:
            cout << "Input tidak valid" << endl;
            break;
        }
    }
}