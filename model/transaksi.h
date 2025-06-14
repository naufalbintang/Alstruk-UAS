#include <vector>
#include <chrono>

class Transaksi{
public:
    struct DataTransaksi {
        int jumlahNominal;
        bool diterima;
        std::string numRekening;
        std::chrono::year_month_day tanggal;
        DataTransaksi(int jumlahNominal, bool diterima, std::string numRekening, std::chrono::year_month_day tanggal);
    };
    struct BlokTransaksi {
        std::vector<DataTransaksi> transaksiTransaksi;
        std::chrono::year_month_day tanggalPertama;
        std::chrono::year_month_day tanggalTerakhir;
        bool isFull;
        static const int DATA_MAX = 50;
        BlokTransaksi();
    };
    struct Node {
        BlokTransaksi blok;
        Node *setelah;
        Node *sebelum;
    };
    int totalBlok;
    Node *kepala;
    Node *ekor;
    Transaksi();
    ~Transaksi();
    void lihatTransaksi();
    void tambahTransaksi();
    void tambahBlok();
    void cariTransaksi();
};
