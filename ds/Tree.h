#pragma once

#include "../model/Nasabah.h"
#include <iostream>
#include <iomanip>

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

        TreeNode* insert(TreeNode* node, const Nasabah& nasabah) {
        if (node == nullptr) return new TreeNode(nasabah);

        if (nasabah.IdNasabah < node->data.IdNasabah)
            node->left = insert(node->left, nasabah);
        else if (nasabah.IdNasabah > node->data.IdNasabah)
            node->right = insert(node->right, nasabah);
        // jika sama, tidak disisipkan (ID unik)
        return node;
        }

        Nasabah* searchTree(TreeNode* node, const string& IdNasabah) {
            if (node == nullptr) return nullptr;

            if (IdNasabah == node->data.IdNasabah)
                return &node->data;
            else if (IdNasabah < node->data.IdNasabah)
                return searchTree(node->left, IdNasabah);
            else
                return searchTree(node->right, IdNasabah);
        }

        void InOrderTraversal(TreeNode* node) {
            if (node == nullptr) return;

            InOrderTraversal(node->left);
            cout << "\nID Nasabah: " << node->data.IdNasabah 
                 << "\nNIK: " << node->data.nik 
                 << "\nSaldo: " << fixed << setprecision(2) << node->data.saldo 
                 << "\nNo Rekening: " << node->data.NoRekening 
                 << "\nAktif: " << (node->data.aktif ? "Aktif" : "Blokir") << endl;
            InOrderTraversal(node->right);
        }

        void destroy(TreeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    Nasabah* cariByRekeningHelper(TreeNode* node, string norekening) {
    if (!node) return nullptr;
    if (node->data.NoRekening == norekening) return &node->data;

    Nasabah* left = cariByRekeningHelper(node->left, norekening);
    if (left) return left;

    return cariByRekeningHelper(node->right, norekening);
    }

    public:
        BinaryTreeNasabah() {
            root = nullptr;
        }

        void insertTree(const Nasabah& data) {
            root = insert(root, data);
        }

        Nasabah* searchNasabah(const string& IdNasabah) {
            return searchTree(root, IdNasabah);
        }

        void DisplayInOrderAllNasabah() {
            InOrderTraversal(root); 
        }

        ~BinaryTreeNasabah() {
            destroy(root);
        }

        Nasabah* findByRekening(string norekening) {
        return cariByRekeningHelper(root, norekening);
        }

        bool deposit(string norekening, double jumlah) {
        Nasabah* nasabah = findByRekening(norekening);
        if (!nasabah) return false;
        nasabah->saldo += jumlah;
        return true;
        }

        bool withdraw(string norekening, double jumlah) {
        Nasabah* nasabah = findByRekening(norekening);
        if (!nasabah || nasabah->saldo < jumlah) return false;
        nasabah->saldo -= jumlah;
        return true;
        }

        bool transfer(string fromRekening, string toRekening, double jumlah) {
        Nasabah* from = findByRekening(fromRekening);
        Nasabah* to = findByRekening(toRekening);
        if (!from || !to || from->saldo < jumlah) return false;
        from->saldo -= jumlah;
        to->saldo += jumlah;
        return true;
        }
};