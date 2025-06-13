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
    Node* next;

    Node(string usn, string pin, string nik){
        username = usn;
        PIN = pin;
        NIK = nik;
        next = nullptr;
    }
};

// Implementasi TREE YAY ANJ-
struct TreeNode {
    string NIK;
    string noRekening;
    double SaldoAwal;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* bikinNode(string nik, string norek, double saldo) {
    TreeNode* nodeBaru = new TreeNode;
    nodeBaru->NIK = nik;
    nodeBaru->noRekening = norek;
    nodeBaru->SaldoAwal = saldo;
    nodeBaru->left = nullptr;
    nodeBaru->right = nullptr;
    return nodeBaru;
}

TreeNode* insertTree(TreeNode* root, string nik, string norek, double saldo) {
    if (root = nullptr) {
        return bikinNode(nik, norek, saldo);
    }

    if (nik < root->NIK)
        root->left = insertTree(root->left, nik, norek, saldo);
    else if (nik > root->NIK)
        root->right = insertTree(root->right, nik, norek, saldo);
    else
        cout << "NIK " << nik << " sudah ada, data tidak disisipkan ulang.\n";

    return root;
}

TreeNode* CariNIK(TreeNode* root, string nik) {
    if (root == nullptr || root->NIK == nik) {
        return root; // ketemu nik / pohon kosong
    }

    if (nik < root->NIK) 
        return CariNIK(root->left, nik); // cari di subtree kiri
    else 
        return CariNIK(root->right, nik); // cari di subtree kanan
} 

void inorder(TreeNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "NIK: " << root->NIK
             << ", No Rekening: " << root->noRekening
             << ", Saldo Awal: " << root->SaldoAwal << endl;
        inorder(root->right);
    }
}


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

void insertHash(string username, string pin, string nik){

    int index = hashFunction(username);
    Node* newNode = new Node(username, pin, nik);

    // Insert node ke hash table bukan? - Rizki
    if(hashTable[index] == nullptr){
        hashTable[index] = newNode;
    }else{
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
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
             << travel->NIK << ", "; 
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
                cout << "Fitur pencarian nasabah belum tersedia\n";
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

    //ab

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

    // semua aman? oke masukin
    insertHash(username, PIN, NIK);
    cout << "Registrasi berhasil" << endl;
    cout << "Silakan login untuk melanjutkan" << endl << endl;
}


int main(){
    // variabel
    char pilihan;
    bool exit = false;

    // Hardcoded data
    // Username, PIN, NIK, No Rekening, saldo awal
    insertHash("admin", "234567", "111111");
    insertHash("nasabah", "123456", "222222");

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