#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <sstream>
#include <algorithm>

// Menggunakan namespace std agar tidak perlu menulis std:: berulang kali
using namespace std;

// Forward declarations untuk class yang saling bergantung
class Hash;
class BinaryTreeNasabah;

// =================================================================
// == BAGIAN 1: DEFINISI MODEL (Struktur Data Dasar)
// =================================================================

// Model untuk merepresentasikan akun pengguna untuk otentikasi
struct Akun {
    string username;
    string pin;
    string nik;
    string IdNasabah; // Kunci penghubung ke data Nasabah

    // Konstruktor default
    Akun() = default;

    // Konstruktor dengan parameter
    Akun(string username, string pin, string nik, string IdNasabah)
        : username(username), pin(pin), nik(nik), IdNasabah(IdNasabah) {}
};

// Model untuk merepresentasikan data nasabah yang lebih detail
struct Nasabah {
    string IdNasabah;
    string nik;
    double saldo;
    string NoRekening;
    bool aktif;

    // Konstruktor default
    Nasabah() = default;

    // Konstruktor dengan parameter
    Nasabah(string IdNasabah, string nik, double saldo, string NoRekening, bool aktif = true)
        : IdNasabah(IdNasabah), nik(nik), saldo(saldo), NoRekening(NoRekening), aktif(aktif) {}
};


// =================================================================
// == BAGIAN 2: FUNGSI UTILITAS (Fungsi Bantuan)
// =================================================================

// Penghitung global untuk memastikan ID Nasabah unik
int globalNasabahCounter = 1;

/**
 * @brief Menghasilkan ID Nasabah yang unik dan berurutan.
 * Format: "NSB" diikuti 3 digit angka (e.g., "NSB001").
 * @return string ID Nasabah baru.
 */
string generateIdNasabah() {
    stringstream ss;
    ss << "NSB" << setw(3) << setfill('0') << globalNasabahCounter++;
    return ss.str();
}

/**
 * @brief Menghasilkan Nomor Rekening 8 digit secara acak.
 * @return string Nomor Rekening baru.
 */
string generateNoRekening() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10000000, 99999999);
    return to_string(dis(gen));
}


// =================================================================
// == BAGIAN 3: STRUKTUR DATA (Hash Table & Binary Tree)
// =================================================================

// --- IMPLEMENTASI HASH TABLE ---
class Hash {
private:
    // Node untuk linked list (mengatasi kolisi)
    struct Node {
        string username{};
        string pin{};
        string nik{};
        string IdNasabah{};
        Node* next{};

        Node(string username, string pin, string nik, string IdNasabah) {
            this->username = username;
            this->nik = nik;
            this->pin = pin;
            this->IdNasabah = IdNasabah;
        }
    };
    
    // Ukuran tabel hash, diset ke 10 untuk contoh ini
    static const int TABLE_SIZE = 10;
    Node* hashTable[TABLE_SIZE]{};

    /**
     * @brief Fungsi hash sederhana, menjumlahkan nilai ASCII dari username.
     * @param username Username yang akan di-hash.
     * @return int Indeks dalam hash table.
     */
    int hashFunction(string username) {
        int usernameASCII{};
        for (char c : username) {
            usernameASCII += c;
        }
        return usernameASCII % TABLE_SIZE;
    }

public:
    // Destruktor untuk membersihkan memori yang dialokasikan
    ~Hash() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* entry = hashTable[i];
            while (entry != nullptr) {
                Node* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }

    /**
     * @brief Menyisipkan data ke dalam hash table.
     */
    void insertHash(string username, string pin, string nik, string IdNasabah) {
        int hashCode = hashFunction(username);
        Node* newNode = new Node(username, pin, nik, IdNasabah);
        
        if (hashTable[hashCode] == nullptr) {
            hashTable[hashCode] = newNode;
        } else {
            Node* travel = hashTable[hashCode];
            while (travel->next != nullptr) {
                travel = travel->next;
            }
            travel->next = newNode;
        }
    }

    /**
     * @brief Helper untuk menyisipkan objek Akun.
     */
    void insertAkun(const Akun& akun) {
        insertHash(akun.username, akun.pin, akun.nik, akun.IdNasabah);
    }

    /**
     * @brief Mencari node berdasarkan username dan pin untuk login.
     * @return true jika ditemukan, false jika tidak.
     */
    bool isNodeFound(const string& username, const string& pin) {
        int hashCode = hashFunction(username);
        Node* travel = hashTable[hashCode];
        while (travel != nullptr) {
            if (username == travel->username && pin == travel->pin) {
                return true;
            }
            travel = travel->next;
        }
        return false;
    }

    /**
     * @brief Memeriksa apakah username sudah ada.
     */
    bool isUsernameExist(const string& username) {
        int hashCode = hashFunction(username);
        Node* travel = hashTable[hashCode];
        while (travel != nullptr) {
            if (username == travel->username) {
                return true;
            }
            travel = travel->next;
        }
        return false;
    }

    /**
     * @brief Memvalidasi format PIN (harus 6 digit angka).
     */
    bool isValidPin(const string& pin) {
        return pin.length() == 6 && all_of(pin.begin(), pin.end(), ::isdigit);
    }

    /**
     * @brief Memeriksa apakah NIK sudah ada di seluruh tabel.
     */
    bool isNIKExist(const string& nik) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* travel = hashTable[i];
            while (travel != nullptr) {
                if (travel->nik == nik) {
                    return true;
                }
                travel = travel->next;
            }
        }
        return false;
    }

    /**
     * @brief Mencetak seluruh isi hash table untuk debugging.
     */
    void printHashTable() {
        cout << "\n--- Isi Hash Table ---" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* travel = hashTable[i];
            cout << "Index " << i << ": ";
            while (travel != nullptr) {
                cout << "{U: " << travel->username << ", P: " << travel->pin << "} -> ";
                travel = travel->next;
            }
            cout << "nullptr" << endl;
        }
        cout << "----------------------" << endl;
    }
};

// --- IMPLEMENTASI BINARY SEARCH TREE ---
class BinaryTreeNasabah {
private:
    struct TreeNode {
        Nasabah data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const Nasabah& data)
            : data(data), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    /**
     * @brief Fungsi rekursif untuk menyisipkan node baru.
     */
    TreeNode* insert(TreeNode* node, const Nasabah& nasabah) {
        if (node == nullptr) return new TreeNode(nasabah);

        if (nasabah.IdNasabah < node->data.IdNasabah)
            node->left = insert(node->left, nasabah);
        else if (nasabah.IdNasabah > node->data.IdNasabah)
            node->right = insert(node->right, nasabah);
        
        return node;
    }

    /**
     * @brief Fungsi rekursif untuk menampilkan data (In-Order Traversal).
     */
    void InOrderTraversal(TreeNode* node) {
        if (node == nullptr) return;

        InOrderTraversal(node->left);
        cout << "\n> ID Nasabah  : " << node->data.IdNasabah
             << "\n  NIK         : " << node->data.nik
             << "\n  Saldo       : " << fixed << setprecision(2) << node->data.saldo
             << "\n  No Rekening : " << node->data.NoRekening
             << "\n  Status      : " << (node->data.aktif ? "Aktif" : "Diblokir") << endl;
        InOrderTraversal(node->right);
    }

    /**
     * @brief Fungsi rekursif untuk menghapus semua node (membersihkan memori).
     */
    void destroy(TreeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTreeNasabah() : root(nullptr) {}

    ~BinaryTreeNasabah() {
        destroy(root);
    }

    void insertTree(const Nasabah& data) {
        root = insert(root, data);
    }

    void DisplayInOrderAllNasabah() {
        cout << "\n--- Data Nasabah (Binary Tree) ---" << endl;
        if(root == nullptr){
            cout << "   (Tidak ada data nasabah)" << endl;
        } else {
            InOrderTraversal(root);
        }
        cout << "----------------------------------" << endl;
    }
};


// =================================================================
// == BAGIAN 4: VIEW (Tampilan Antarmuka Pengguna)
// =================================================================

class MainView {
public:
    /**
     * @brief Menampilkan menu utama aplikasi.
     */
    static void tampilkanMenuUtama() {
        cout << "\n===== E-BANKING KELOMPOK 5 =====" << endl;
        cout << "1. Registrasi Nasabah Baru" << endl;
        cout << "2. Login Nasabah" << endl;
        cout << "3. (Debug) Tampilkan Semua Data" << endl;
        cout << "0. Keluar" << endl;
        cout << "================================" << endl;
        cout << "Masukkan pilihan Anda: ";
    }

    /**
     * @brief Menampilkan pesan jika input tidak valid.
     */
    static void tampilkanPesanTidakValid() {
        cout << "\n[!] Pilihan tidak valid. Silakan coba lagi." << endl;
    }

    /**
     * @brief Membersihkan layar konsol.
     */
    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
};


// =================================================================
// == BAGIAN 5: DATA DUMMY (Untuk Pengujian)
// =================================================================

/**
 * @brief Mengisi hash table dan tree dengan data contoh.
 * @param hash Referensi ke objek Hash.
 * @param tree Referensi ke objek BinaryTreeNasabah.
 */
void loadDummyData(Hash& hash, BinaryTreeNasabah& tree) {
    // Dummy 1
    string id1 = generateIdNasabah();
    string rek1 = generateNoRekening();
    hash.insertAkun(Akun("admin", "123123", "1111111111", id1));
    tree.insertTree(Nasabah(id1, "1111111111", 500000.0, rek1));

    // Dummy 2
    string id2 = generateIdNasabah();
    string rek2 = generateNoRekening();
    hash.insertAkun(Akun("adelio", "123456", "2222222222", id2));
    tree.insertTree(Nasabah(id2, "2222222222", 2500000.0, rek2));

    cout << "[OK] Data dummy berhasil dimuat." << endl;
}


// =================================================================
// == BAGIAN 6: CONTROLLER (Logika Aplikasi)
// =================================================================

// --- CONTROLLER UNTUK LOGIN ---
class LoginController {
private:
    Hash* hashTable;

public:
    LoginController(Hash* hashTable) : hashTable(hashTable) {}

    bool loginUser() {
        string username, pin;

        cout << "\n--- LOGIN NASABAH ---" << endl;
        cout << "Masukkan username : ";
        cin >> username;
        cout << "Masukkan PIN      : ";
        cin >> pin;

        if (hashTable->isNodeFound(username, pin)) {
            cout << "\n[OK] Login berhasil! Selamat datang, " << username << "!" << endl;
            // Di sini bisa ditambahkan logika untuk masuk ke menu nasabah
            return true;
        } else {
            cout << "\n[!] Login gagal! Username atau PIN salah." << endl;
            return false;
        }
    }
};

// --- CONTROLLER UNTUK REGISTRASI ---
class RegisterController {
private:
    Hash* hashTable;
    BinaryTreeNasabah* treeNasabah;

public:
    RegisterController(Hash* hashTable, BinaryTreeNasabah* treeNasabah)
        : hashTable(hashTable), treeNasabah(treeNasabah) {}

    void RegisterUser() {
        string username, pin, nik, norekening;
        double saldo;

        cout << "\n--- REGISTRASI NASABAH ---" << endl;

        // Validasi Username
        while (true) {
            cout << "Masukkan username baru: ";
            cin >> username;
            if (hashTable->isUsernameExist(username)) {
                cout << "[!] Username '" << username << "' sudah terdaftar, coba lagi.\n";
            } else break;
        }

        // Validasi PIN
        while (true) {
            cout << "Masukkan PIN (6 digit angka): ";
            cin >> pin;
            if (!hashTable->isValidPin(pin)) {
                cout << "[!] PIN harus terdiri dari 6 digit angka.\n";
            } else break;
        }

        // Validasi NIK
        while (true) {
            cout << "Masukkan NIK: ";
            cin >> nik;
            if (hashTable->isNIKExist(nik)) {
                cout << "[!] NIK ini sudah terdaftar, coba lagi.\n";
            } else break;
        }

        // Input Saldo Awal
        cout << "Masukkan saldo awal: ";
        cin >> saldo;

        // Generate otomatis ID dan No Rekening
        string idNasabah = generateIdNasabah();
        norekening = generateNoRekening();

        // Buat objek dan masukkan ke struktur data
        hashTable->insertAkun(Akun(username, pin, nik, idNasabah));
        treeNasabah->insertTree(Nasabah(idNasabah, nik, saldo, norekening, true));

        // Konfirmasi
        cout << "\n[OK] Registrasi berhasil!" << endl;
        cout << "   ID Nasabah Anda  : " << idNasabah << endl;
        cout << "   No Rekening Anda : " << norekening << endl;
    }
};

// --- CONTROLLER UTAMA (Orkestrator Aplikasi) ---
class MainController {
private:
    Hash hashTable;
    BinaryTreeNasabah tree;
    RegisterController regController;
    LoginController loginController;
    bool exitApp = false;

public:
    MainController()
        : regController(&hashTable, &tree),
          loginController(&hashTable) {}

    void run() {
        char pilihan;
        MainView::clearScreen();
        cout << "Memuat aplikasi e-banking..." << endl;
        loadDummyData(hashTable, tree);

        while (!exitApp) {
            MainView::tampilkanMenuUtama();
            cin >> pilihan;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer

            switch (pilihan) {
                case '1':
                    regController.RegisterUser();
                    break;
                case '2':
                    loginController.loginUser();
                    break;
                case '3':
                    hashTable.printHashTable();
                    tree.DisplayInOrderAllNasabah();
                    break;
                case '0':
                    exitApp = true;
                    cout << "\nTerima kasih telah menggunakan aplikasi kami. Sampai jumpa!" << endl;
                    break;
                default:
                    MainView::tampilkanPesanTidakValid();
            }
        }
    }
};


// =================================================================
// == BAGIAN 7: FUNGSI MAIN (Titik Masuk Program)
// =================================================================

int main() {
    // Membuat objek MainController yang akan menjalankan seluruh aplikasi
    MainController app;
    
    // Memulai aplikasi
    app.run();
    
    return 0; // Mengindikasikan program berakhir dengan sukses
}
