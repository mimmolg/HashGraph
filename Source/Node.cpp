//
// Created by Mimmo on 29/10/2022.
//

#include "Node.h"


template<typename T>
Node<T>::Node(T key){
    this->key=key;
    this->stato=false;
}

template<typename T>
T Node<T>::getKey(){return key;}

template<typename T>
vector<Node<T>*> Node<T>::getEdges(){return edges;}

template<typename T>
void Node<T>::addEdge(Node<T>* x){
    for(auto e : edges){
        if(e->getKey() == x->getKey()){
            cout<<"The edge already exists"<<endl;
            return;
        }
    }
    edges.push_back(x);
}

template<typename T>
Node<T>::~Node()
{
    //dtor
}
template<typename T>
bool Node<T>::checkEdge(Node<T> *x) {
    for(auto e:edges) {
        if (e->getKey() == x->getKey()) {
            cout << "Esiste un arco tra i due nodi" << endl;
            return true;
        }
    }
    cout<<"non esiste un arco tra i due nodi"<<endl;
    return false;
}

template<typename T>
void Node<T>::setKey(T key) {
    this->key=key;
}

template<typename T>
void Node<T>::addEdgeS(Node<T> *x) {
    edges.push_back(x);
}








