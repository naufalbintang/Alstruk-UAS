#include <iostream>
#include <string>
#include <iomanip> // Biar saldoawal ga 1+e06 di output kalau 1 juta. - Rizki
#include <algorithm> // Karena pin gw malas buat ubah dari string ke int, jadi gw tanya AI dan bisa pake algortihm all_off bakal masalah gasi? - Rizki
using namespace std;

// hash function
struct Node{
    // Ganti password ke pin, added nik - Rizki
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
    bool status;
    TreeNode* left;
    TreeNode* right;
};


TreeNode* bikinNode(string nik, string norek, double saldo, bool status = true) {
    TreeNode* nodeBaru = new TreeNode;
    nodeBaru->NIK = nik;
    nodeBaru->noRekening = norek;
    nodeBaru->SaldoAwal = saldo;
    nodeBaru->status = status;
    nodeBaru->left = nullptr;
    nodeBaru->right = nullptr;
    return nodeBaru;
}


// Hmm, OH ini buat ukuran hash table-nya ya? - Rizki
const int TABLESIZE = 10;
Node* hashTable[TABLESIZE] = {};
TreeNode* root = nullptr;

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

TreeNode* insertTree(string nik, string norek, double saldo, bool status = true) {
    TreeNode* baru = bikinNode(nik, norek, saldo, status);

    if (root == nullptr) {
        root = baru;
        return root;
    }

    TreeNode* travelTree = root;
    TreeNode* parent = nullptr;

    while (travelTree != nullptr) {
        parent = travelTree;
        if (nik < travelTree->NIK) {
            travelTree = travelTree->left;
        } else if (nik > travelTree->NIK) {
            travelTree = travelTree->right;
        } else {
            cout << "NIK sudah ada. Data tidak disisipkan.\n";
            return root;
        }
    }

    if (nik < parent->NIK) {
        parent->left = baru;
    } else {
        parent->right = baru;
    }

    return root;
}

void inorderTree(TreeNode* root) {
    if (root != nullptr) {
        inorderTree(root->left);
        cout << "  NIK         : " << root->NIK << endl;
        cout << "  Rekening    : " << root->noRekening << endl;
        cout << "  Saldo Awal  : Rp " << fixed << setprecision(2) << root->SaldoAwal << endl;
        cout << "  Status      : " << (root->status ? "AKTIF" : "BLOKIR") << endl;
        cout << "-----------------------------" << endl;
        inorderTree(root->right);
    }
}

// NGEMERGE DISPLAY OUTPUT HASHTABLE DAN TREE

// Cari Node di hashtable berdasarkan NIK

Node* cariNIKHashTable(string nik) {
    for (int i = 0; i < TABLESIZE; i++) {
        Node* travel = hashTable[i];
        while (travel != nullptr) {
            if (travel -> NIK == nik && travel -> username != "admin") {
                return travel;
            }
            travel = travel->next;
        }
    }
    return nullptr;
}

void MergeDataStructure(TreeNode* root) {
    if (root != nullptr) {
        MergeDataStructure(root->left);
        if (root->NIK != "111111") { // skip admin
            Node* user = cariNIKHashTable(root->NIK); // Akses dari hashtable
            if (user != nullptr && user->username != "admin") {
                cout << "Username    : " << user->username << endl;
                cout << "PIN         : " << string(user->PIN.length(), '*') << endl;
            } else {
                cout << "[WARNING] Data pengguna dengan NIK " << root->NIK << " tidak ditemukan di Hash Table.\n";
            }

            cout << "NIK         : " << root->NIK << endl;
            cout << "No Rekening : " << root->noRekening << endl;
            cout << "Saldo Awal  : " << fixed << setprecision(2) << root->SaldoAwal << endl;
            cout << "Status      : " << (root->status ? "AKTIF" : "BLOKIR") << endl;
            cout << "-------------------" << endl;
        }

        MergeDataStructure(root->right);
    }
}

void DisplayAllNasabah() {
    cout << endl;
    cout << "===================" << endl;
    cout << "  DATA NASABAH" << endl;
    cout << "===================" << endl;
    MergeDataStructure(root);
    cout << endl;
}

// Cari NIK di Tree buat fitur di Admin
void cariNIKTree(string nik) {
    if (nik == "111111") {
        cout << "Data dengan NIK " << nik << " tidak ditemukan.\n";
        return;
    }
    if (root == nullptr) {
        cout << "Tree kosong.\n";
        return;
    }
    TreeNode* travelTree = root; // GUNAKAN POINTER LOKAL
    while (travelTree != nullptr) {
        if (nik < travelTree->NIK) {
            travelTree = travelTree->left;
        } else if (nik > travelTree->NIK) {
            travelTree = travelTree->right;
        } else {
            Node* user = cariNIKHashTable(travelTree->NIK);
            if (user != nullptr) {
                cout << "\n=== Data Ditemukan ===\n";
                cout << "Username       : " << user->username << endl;
                cout << "PIN            : " << string(user->PIN.length(), '*') << endl;
                cout << "NIK            : " << travelTree->NIK << endl;
                cout << "Nomor Rekening : " << travelTree->noRekening << endl;
                cout << fixed << setprecision(2);
                cout << "Saldo          : Rp " << travelTree->SaldoAwal << endl;
                cout << "Status         : " << (travelTree->status ? "AKTIF" : "BLOKIR") << endl;
                cout << "========================\n\n";
            } else {
                cout << "Data dengan NIK " << nik << " tidak ditemukan.\n";
            }
            return;
        }
    }
    cout << "Data dengan NIK " << nik << " tidak ditemukan.\n\n";
}


void printHashAndTree(TreeNode* root) {
    cout << endl;

    cout << "\n======= HASH TABLE =======\n";
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
    
    cout << "\n======= BINARY SEARCH TREE (Data Rekening) =======\n";
    if (root == nullptr) {
        cout << "Pohon kosong.\n";
    } else {
        inorderTree(root);
        cout << endl;
    }
}

void ubahStatusNasabah() {
    if (root == nullptr) {
        cout << "Pohon kosong. Tidak ada nasabah yang dapat diubah statusnya.\n";
        return;
    }

    string nik;
    char pilihan;

    cout << "=== Ubah Status Nasabah ===\n";
    cout << "1. Blokir Nasabah\n";
    cout << "2. Buka Blokir Nasabah\n";
    cout << "0. kembali ke menu admin\n";
    cout << "Pilihan: "; 
    cin >> pilihan;
    if (pilihan == '0') return;
    if (pilihan != '1' && pilihan != '2') {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    cout << "Masukkan NIK Nasabah: ";
    cin >> nik;

    bool statusBaru;

    if (nik == "111111") {
        cout << "Tidak dapat mengubah status admin.\n";
        return;
    }

    if (pilihan == '1') statusBaru = false;
    else if (pilihan == '2') statusBaru = true;
    else {
        cout << "pilihan tidak valid.\n";
        return;
    }

    TreeNode* travelTree = root;
    while (travelTree != nullptr) {
        if (nik < travelTree->NIK) {
            travelTree = travelTree->left;
        } else if (nik > travelTree->NIK) {
            travelTree = travelTree->right; 
        } else {
            travelTree->status = statusBaru;
            cout << "Status nasabah dengan NIK " << nik << " telah diubah menjadi "
                 << (statusBaru ? "AKTIF" : "BLOKIR") << ".\n";
            return;
        }
    }
    cout << "NIK tidak ditemukan.\n";
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
        cout << "2. Ubah Status Nasabah\n";
        cout << "3. Cari Nasabah (Implementasi Tree)\n";
        cout << "4. Log out\n";
        cout << "Masukkan pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case '1':
                DisplayAllNasabah();
                break;
            case '2':
                ubahStatusNasabah();
                break;
            case '3':
                cout << "Masukkan NIK yang ingin dicari: ";
                cin >> nik;
                cariNIKTree(nik);
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
            TreeNode* travelTree = root;
            while (travelTree != nullptr) {
            if (travel->NIK == travelTree->NIK) break;
            if (travel->NIK < travelTree->NIK) travelTree = travelTree->left;
            else travelTree = travelTree->right;
    }

            if (travelTree == nullptr) {
                cout << "Akun tidak ditemukan" << endl << endl;
                return;
            }

            if (!travelTree->status) {
                cout << "Akun dengan NIK " << travelTree->NIK << " sedang diblokir. Silahkan hubungi Admin." << endl;
                return;
            }

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
    cout << "Username atau Pin salah" << endl << endl;
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
        TreeNode* cek = root;
        while (cek != nullptr) {
            if (noRekening == cek->noRekening) {
                norekdahada = true;
                break;
            } 
            if (noRekening < cek->noRekening) {
                cek = cek->left;
            } else {
                cek = cek->right;
            }
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
    insertHash(username, PIN, NIK);
    root = insertTree(NIK, noRekening, SaldoAwal);
    cout << "Registrasi berhasil" << endl;
    cout << "Silakan login untuk melanjutkan" << endl << endl;
}


int main(){
    // variabel
    char pilihan;
    bool exit = false;

    // Hardcoded data (REMINDER: DATA NIK DI HASHTABLE DAN TREE HARUS SAMA  - Rizki)
    // Username, PIN, NIK (HASHTABLE)
    insertHash("admin", "234567", "111111");
    insertHash("adelio", "123456", "222222");
    insertHash("boy", "098765", "333333");
    insertHash("rizki", "112233", "444444");
    insertHash("naufal", "445566", "555555");

    // NIK, No Rekening, Saldo Awal (TREE) 
    insertTree("111111", "1234567890", 1000000.00, true); // Admin
    insertTree("222222", "0987654321", 500000.00, true); // adelio
    insertTree("333333", "1122334455", 750000.00, true); // boy
    insertTree("444444", "5566778899", 300000.00, true); // rizki
    insertTree("555555", "6677889900", 200000.00, true); // naufal

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
        cout << "3. Print Data HashTable and Tree" << endl;
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
            printHashAndTree(root);
            break;
        default:
            cout << "Input tidak valid" << endl;
            break;
        }
    }
}