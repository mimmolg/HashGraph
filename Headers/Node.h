//
// Created by Mimmo on 29/10/2022.
//
    #ifndef PROGETTOASD_NODE_H
    #define PROGETTOASD_NODE_H
    #include <vector>
    #include <memory>
    #include <iostream>
    using namespace std;
    template <typename T>
    class Node{
    public:
        explicit Node(T key);
        T getKey();
        vector<Node<T>*> getEdges();
        vector<Node<T>*> *getEdgesPointer(){return &edges;}/*Mi serve per quando vado a rimuovere il nodo*/
        void addEdge(Node<T>*);
        void addEdgeS(Node<T>*);
        bool checkEdge(Node<T>*);
        virtual ~Node();
        void setKey(T key);
        void setStato(bool s){this->stato=s;}
        bool getStato(){return this->stato;}
    private:
        bool stato;
        T key;
        vector<Node<T>*> edges;
    };
    #endif //PROGETTOASD_NODE_H
