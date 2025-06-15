#pragma once

#include <iostream>
#include "../controller/login_controller.h"
#include "../controller/register_controller.h"
#include "../ds/Hash.h"
#include "../ds/Tree.h"
#include "../ds/datadummy.h"
#include "../view/MainView.h"

using namespace std;

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
          loginController(&hashTable) {
    }

    void run() {
    char pilihan;
    MainView::clearScreen();
    loadDummyData(hashTable, tree);

    while (!exitApp) {
        MainView::tampilkanMenuUtama();
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                regController.RegisterUser();
                break;
            case '2':
                loginController.loginUser();
                break;
            case '3':
                cout << "\n=== HashTable Akun ===" << endl;
                hashTable.printHashTable();

                cout << "\n=== BinaryTree Nasabah ===" << endl;
                tree.DisplayInOrderAllNasabah();
                break;
            case '0':
                exitApp = true;
                break;
            default:
                MainView::tampilkanPesanTidakValid();
        }
    }
}
};