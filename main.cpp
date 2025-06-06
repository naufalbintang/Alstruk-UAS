#include <iostream>
#include <string>
#include <iomanip> // Biar saldoawal ga 1+e06 di output kalau 1 juta. - Rizki
#include <algorithm> // Karena pin gw malas buat ubah dari string ke int, jadi gw tanya AI dan bisa pake algortihm all_off bakal masalah gasi? - Rizki
using namespace std;

// Note: Gua sesuain alurnya dengan yang ada di word. - Rizki
// BINGUNG MAU DI PUSH ATAU KAGAK.

// hash function
struct Node{
    // Ganti password ke pin, added nik, norekening, saldo - Rizki
    string username{};
    string PIN{}; 
    string NIK{};
    string noRekening{};
    double SaldoAwal{};
    Node* next;

    Node(string usn, string pin, string nik, string norek, double saldo ){
        username = usn;
        PIN = pin;
        NIK = nik;
        noRekening = norek;
        SaldoAwal = saldo;
        next = nullptr;
    }
};

// Implementasi TREE YAY ANJ-
struct TreeNode {
    string username;
    string PIN;
    string NIK;
    string noRekening;
    double SaldoAwal;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(Node* node) {
        username = node->username;
        PIN = node->PIN;
        NIK = node->NIK;
        noRekening = node->noRekening;
        SaldoAwal = node->SaldoAwal;
    }
};

// Hmm, OH ini buat ukuran hash table-nya ya? - Rizki
const int TABLESIZE = 10;
Node* hashTable[TABLESIZE] = {};

// int hashFuction(string username){
//     return tolower(username[0]) % TABLESIZE;
// }

// Improved i guess - Rizki
int hashFunction(string username) {
    int hash = 0;
    for (int i = 0; i < username.length(); i++) {
        hash = (hash * 31 + username[i]) % TABLESIZE;
    }
    return hash;
}

void insertHash(string username, string pin, string nik, string norek, double saldo){

    int index = hashFunction(username);
    Node* newNode = new Node(username, pin, nik, norek, saldo);

    // I assume this function is used to check if account already exists? Right Nopal? - Rizki
    
    // Moved this function to registrasi so it check for existing accounts AFTER user input any duplications. So NOT AFTER inputting everything. - Rizki

    // for(int i{}; i < TABLESIZE; i++){
    //     Node* travel = hashTable[i];
    //     while(travel != nullptr){
    //         if(username == travel->username){
    //             cout << "Username sudah terdaftar" << endl;
    //             return;
    //         }
    //         // Cek nik juga atau ini ga perlu? Hmm. Hapus aja kalau ga perlu - Rizki
    //         if(nik == travel->NIK){
    //             cout << "NIK sudah terdaftar" << endl;
    //             return;
    //         }
    //         travel = travel->next;
    //     }
    // }

    // Insert node ke hash table bukan? - Rizki
    if(hashTable[index] == nullptr){
        hashTable[index] = newNode;
    }else{
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

TreeNode* cariNIKdiHashTable(string NIK, Node* hashTable[], int TABLESIZE) {
    for (int i = 0; i < TABLESIZE; i++) {
        Node* travel = hashTable[i];
        while (travel != nullptr) {
            if (travel->NIK == NIK) {
                return new TreeNode(travel); // ketemu, bungkus jadi TreeNode buat ditampilkan
            }
            travel = travel->next;
        }
    }
    return nullptr; // NIK tidak ditemukan
}

void TampilkanNode(TreeNode* node) {
    if (node == nullptr) {
        cout << "Data dengan NIK tersebut tidak ditemukan.\n";
        return;
    }

    cout << "\n=== Data Ditemukan ===\n";
    cout << "Username     : " << node->username << endl;
    cout << "PIN          : " << node->PIN << endl;
    cout << "NIK          : " << node->NIK << endl;
    cout << "No Rekening  : " << node->noRekening << endl;
    cout << "Saldo        : " << fixed << setprecision(0) << node->SaldoAwal << endl;
    cout << "Status       : " << (node->SaldoAwal >= 0 ? "Aktif" : "Blokir") << endl << endl; // Hmm. Karena blom ada fitur status trus gw malas implementasi, gw asumsikan kalau saldo >= 0 itu aktif, kalau < 0 itu blokir. - Rizki
}

// Added this for admin, so it only display nasabah data, not admin - Rizki
void DataNasabah(){
    cout << endl;

    cout << "===================" << endl;  
    cout << "  DATA NASABAH" << endl;
    cout << "===================" << endl;

    cout << endl;
    bool ketemu = false;
    for (int i = 0; i < TABLESIZE; i++) {
        Node* travel = hashTable[i];
        while (travel != nullptr) {
            // Lewati jika admin 
            if (travel->username != "admin") {
                ketemu = true;
                cout << "Username       : " << travel->username << endl;
                cout << "NIK            : " << travel->NIK << endl;
                cout << "No Rekening    : " << travel->noRekening << endl;
                cout << "Saldo          : " << fixed << setprecision(0) << travel->SaldoAwal << endl;
                cout << "Status         : " << (travel->SaldoAwal >= 0 ? "Aktif" : "Blokir") << endl << endl; // Hmm. Karena blom ada fitur status trus gw malas implementasi, gw asumsikan kalau saldo >= 0 itu aktif, kalau < 0 itu blokir. - Rizki
            }
            travel = travel->next;
        }
    }
    if (!ketemu) {
        cout << "Tidak ada nasabah yang terdaftar.\n";
    }
}

void printHash() {
    cout << endl;
    for(int i{}; i < TABLESIZE; i++){
        cout << "[" << i << "]";
        Node* travel = hashTable[i];
        while (travel != nullptr) {
            // Added some of the data to be outputted - Rizki
             cout << 
             "(" << travel->username << ", " 
             << travel->PIN  << ", " 
             << travel->NIK << ", " << travel->noRekening << ", " 
             << fixed << setprecision(0) << travel->SaldoAwal << ") -> "; 
            travel = travel->next;
        }
        cout << "nullptr" << endl;
    }
    cout << endl;
}

void Admin() {
    string nik;
    char pilihan;
    bool exit = false;

    while (!exit) {
        cout << "===================\n";
        cout << "    MENU ADMIN\n";
        cout << "===================\n";
        cout << "1. Lihat Semua Data Nasabah\n";
        cout << "2. Buka Status Blokir Nasabah\n";
        cout << "3. Cari Nasabah (Implementasi Tree)\n";
        cout << "4. Log out\n";
        cout << "Masukkan pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case '1':
                DataNasabah();
                break;
            case '2':
                cout << "Fitur buka status blokir nasabah belum tersedia\n";
                break;
            case '3':
                cout << "Masukkan NIK yang ingin dicari: ";
                cin >> nik;
                TampilkanNode(cariNIKdiHashTable(nik, hashTable, TABLESIZE));
                break;
            case '4':
                cout << "Log out berhasil\n";
                exit = true;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    }
}

void Nasabah() {
    cout << "Fitur nasabah belum tersedia" << endl;
    // Implementasi fitur nasabah di sini
}

void login() {
    string username, pin;
    cout << "Masukkan username: "; cin >> username;
    cout << "Masukkan pin: "; cin >> pin;

    // Simplified the login function - Rizki
    int index = hashFunction(username);
    Node* travel = hashTable[index];
    while (travel != nullptr) {
        if (username == travel->username && pin == travel->PIN) {
            cout << "Berhasil login sebagai " << travel->username << endl << endl;
            if (username == "admin") {
                // Fitur admin
                Admin();
            } else {
                // Fitur nasabah
                Nasabah();
            }
            return;
        }
        travel = travel->next;
    }
    cout << "Akun tidak ditemukan" << endl << endl;
}

void registrasi() {
    string username{}, PIN{}, NIK{}, noRekening{};
    double SaldoAwal{};

    cout << "===================" << endl;
    cout << "  MENU REGISTRASI" << endl;
    cout << "===================" << endl;

    // username valid?
    while (true) {
        cout << "Masukkan Nama: ";
        cin >> username;

        bool usernamedahada = false;
        for (int i = 0; i < TABLESIZE; i++) {
            Node* travel = hashTable[i];
            while (travel != nullptr) {
                if (username == travel->username) {
                    usernamedahada = true;
                    break;
                }
                travel = travel->next;
            }
            if (usernamedahada) break;
        }

        if (usernamedahada) {
            cout << "Username sudah terdaftar" << endl;
        } else {
            break; // keluar dari loop username
        }
    }

    // pin valid?
    while (true) {
        cout << "Masukkan Pin (6 digit): ";
        cin >> PIN;
        if (PIN.length() == 6 && all_of(PIN.begin(), PIN.end(), ::isdigit)) {
            break;
        } else {
            cout << "PIN harus 6 digit angka" << endl;
        }
    }

    // nik valid?
    while (true) {
        cout << "Masukkan NIK: ";
        cin >> NIK;

        bool nikdahada = false;
        for (int i = 0; i < TABLESIZE; i++) {
            Node* travel = hashTable[i];
            while (travel != nullptr) {
                if (NIK == travel->NIK) {
                    nikdahada = true;
                    break;
                }
                travel = travel->next;
            }
            if (nikdahada) break;
        }

        if (nikdahada) {
            cout << "NIK sudah terdaftar, silahkan ganti NIK lain" << endl;
        } else {
            break;
        }
    }

    // norek valid?
    while (true) {
        cout << "Masukkan No Rekening: ";
        cin >> noRekening;

        bool norekdahada = false;
        for (int i = 0; i < TABLESIZE; i++) {
            Node* travel = hashTable[i];
            while (travel != nullptr) {
                if (noRekening == travel->noRekening) {
                    norekdahada = true;
                    break;
                }
                travel = travel->next;
            }
            if (norekdahada) break;
        }

        if (norekdahada) {
            cout << "No Rekening sudah terdaftar, silahkan ganti No Rekening lain" << endl;
        } else {
            break;
        }
    }

    // saldo valid?
    cout << "Masukkan Saldo: ";
    while (!(cin >> SaldoAwal) || SaldoAwal < 0) {
        cout << "Input tidak valid, silahkan masukkan angka >= 0: ";
        cin.clear();
    }

    // semua aman? oke masukin
    insertHash(username, PIN, NIK, noRekening, SaldoAwal);
    cout << "Registrasi berhasil" << endl;
    cout << "Silakan login untuk melanjutkan" << endl << endl;
}


int main(){
    // variabel
    char pilihan;
    bool exit = false;

    insertHash("admin", "234567", "1234567890123456", "0000000000", 1000000);
    insertHash("nasabah", "123456", "222222", "222222222", 500000);

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
        cout << "Friendly reminder to delete unnecessary comments before presentation! - Rizki" << endl; 
        cout << "============" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Print Hash Table" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan: "; cin >> pilihan;
        switch(pilihan){
        case '0':
            cout << "Terima kasih telah menggunakan program ini!" << endl;
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