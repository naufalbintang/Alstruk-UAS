#include "../model/transaksi.hpp"
#include "../main.cpp"
#include <chrono>
#include <cstdlib>
#include <vector>

Transaksi::Transaksi() {
    kepala = nullptr;
    ekor = nullptr;
}

void Transaksi::tambahBlok() {
    Node *nodeBaru = (Node *) malloc(sizeof(Node));
    nodeBaru->blok = BlokTransaksi();
    nodeBaru->setelah = kepala;
    nodeBaru->sebelum = nullptr;
    if (kepala != nullptr) {
        kepala->sebelum = nodeBaru;
    }
    if (ekor == nullptr) {
        ekor = nodeBaru;
    }
    kepala = nodeBaru;
}

Transaksi::DataTransaksi::DataTransaksi(int jumlahNominal, bool diterima, std::string numRekening, std::chrono::year_month_day tanggal) {
    this->jumlahNominal = jumlahNominal;
    this->diterima = diterima;
    this->numRekening = numRekening;
    this->tanggal = tanggal;
}

void Transaksi::tambahTransaksi() {
    int nominal;
    
    //literally basic how to add
    DataTransaksi data(nominal, false, "121", {chrono::year{2020}, chrono::month{02}, chrono::day{01}});
    std::vector<DataTransaksi> blok = kepala->blok.transaksiTransaksi;
    blok.insert(blok.begin(), data);
}
