//
// Created by Mimmo on 29/10/2022.
//

#ifndef PROGETTOASD_HASHGRAPH_H
#define PROGETTOASD_HASHGRAPH_H
#include "Node.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>

template<typename T>
class HashGraph {
public:
    explicit HashGraph(const string& fileName);
    void addEdge(Node<T>*,Node<T>*);
    void printAdjList();
    bool findEdge(Node<T>*,Node<T>*);
    void removeEdge(Node<T>*,Node<T>*);
    void itDFS(Node<T>*);
    void DFS();
    void DFSUtil(Node<T>*,vector<bool>&);
    void solve();//Metodo per risolvere il quesito della seconda traccia
private:
    void readFromFile();
    void nodeToAdd(Node<T>*);
    int HashKey(Node<T>*);
    bool ifNodeEx(T);
    int hash1(int);
    int hash2(int);
    int getPrime(int);
    bool isPrime(int) const;
    int getPrime();/* Function to get prime number less than table size for myhash2 function */
    void setTableSize(int);
    vector<Node<T>*> parent;//mi serve per la seconda traccia
    vector<Node<T>*> table;
    int tableSize;
    string fileName;
};

#endif //PROGETTOASD_HASHGRAPH_H
