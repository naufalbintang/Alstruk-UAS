#pragma once
#include <iostream>
using namespace std;

class Hash{
    private:
        struct Node{
            string username{};
            string pin{};
            string nik{};
            Node* next{};

            Node(string username, string pin, string nik){
                this->username = username;
                this->nik = nik;
                this->pin = pin;
            }   
        };
        static int const TABLE_SIZE = 10;
        Node* hashTable[TABLE_SIZE]{};
        
    public:
        int hashFunction(string username){
            int usernameASCII{};
            for(int i{}; i < username.length(); i++){
                usernameASCII += username[i];
            }
            return usernameASCII % 10;
        }

        void insertHash(string username, string pin, string nik){
            int hashCode = hashFunction(username);
            Node* newNode = new Node(username, pin, nik);
            Node* travel = hashTable[hashCode];

            if(hashTable[hashCode] == nullptr){
                hashTable[hashCode] = newNode;
            }else{
                travel = hashTable[hashCode];
                while(travel->next != nullptr){
                    travel = travel->next;
                }
                travel->next = newNode;
            }
        }

        bool isUsernameExist(string username){
            int hashCode = hashFunction(username);
            Node* travel = hashTable[hashCode];
            while(travel != nullptr){
                if(username == travel->username){
                    return true;
                }
                travel = travel->next;
            }
            return false;
        }

        bool isNodeFound(string username, string pin){
            int hashCode = hashFunction(username);
            Node* travel = hashTable[hashCode];
            while(travel != nullptr){
                if(username == travel->username && pin == travel->pin){
                    return true;
                }
                travel = travel->next;
            }
            return false;
        }
};