//
// Created by Mimmo on 29/10/2022.
//
#include "HashGraph.h"
#include <cmath>
#include <iterator>

    template<typename T>
    HashGraph<T>::HashGraph(const string& fileName){
        tableSize=0;
        this->fileName=fileName;
        readFromFile();
        parent.resize(tableSize);
    }

    template<typename T>
    void HashGraph<T>::readFromFile(){
        ifstream fs;
        string delim=" ";
        string tmp;
        int pos=0;
        int s;
        int d;
        fs.open(this->fileName);
        if(fs.is_open()){
            getline(fs,tmp);
            pos=tmp.find(delim);
            int nodes= stoi(tmp.substr(0,pos));
           if(nodes<=0 || nodes>1000){
                cout<<"Inserire nel file un numero corretto di nodi";
                exit(EXIT_FAILURE);
            }
            if(!isPrime(nodes)){
                nodes=getPrime(nodes);
            }
            table.resize(nodes+1);
            setTableSize(nodes+1);
            int edges= stoi(tmp.substr(pos+1,tmp.length()));
            if(edges<=0 || edges>1000){
                cout<<"Inserire nel file un numero corretto di archi";
                exit(EXIT_FAILURE);
            }
            for(int i=0; i<edges;i++){
                fs>>s;
                fs>>d;
                auto source=new Node<int>(s);
                auto dest=new Node<int>(d);
                if(!ifNodeEx(s)){//se il nodo non esiste lo aggiungo
                    nodeToAdd(source);
                }
                if(!ifNodeEx(d)){//se il nodo non esiste lo aggiungo
                    nodeToAdd(dest);
                }
                auto y=HashKey(source);
                table[y]->addEdge(dest);
            }
        }else {
            cout<<"impossibile aprire il file specificato"<< endl;
            exit(-1);
        }
    }

    template<typename T>
    void HashGraph<T>::setTableSize(int sz){
        this->tableSize=sz;
    }

    template<typename T>
    bool HashGraph<T>::isPrime(int n) const {/*O(sqrt(n))*/
        if(n<2)return false;
        if(n==2)return true;
        if(n%2==0)return false;
        for(int i=3;(i*i)<=n;i++){
            if(n%i==0)return false;
        }
        return true;
    }

    template<typename T>
    int HashGraph<T>::getPrime(int n) {
        int i=n+1;/*parto dal numero successivo dato che se entro allora il size non è primo*/
        while(!isPrime(i)) {
            i+=1;
        }
        return i;
    }

    template<typename T>
    int HashGraph<T>::hash1(int key) {
        return key%tableSize;
    }

    template<typename T>
    int HashGraph<T>::hash2(int key) {
        int coPrime = getPrime();
        return (coPrime-(key%coPrime));
    }

    template<typename T>
    void HashGraph<T>::nodeToAdd(Node<T>* node) {
        int hash_1= hash1(node->getKey());
        if(table[hash_1]!= nullptr && node->getKey()!=table[hash_1]->getKey()){ //in caso di collisione
            int hash_2= hash2(node->getKey());
            int i=1;
            while (true){
                int newIndex=(hash_1+i*hash_2)%tableSize;
                if(table[newIndex]==nullptr){//no collisioni
                    table[newIndex]=node;
                    break;
                }
                i++;
            }
        }else {
            table[hash_1] = node;
        }
    }

    template<typename T>
    int HashGraph<T>::HashKey(Node<T> *x) {
    int hash_1= hash1(x->getKey());
    int hash_2= hash2(x->getKey());
    int i=1;
    while(table[hash_1] != nullptr && table[hash_1]->getKey()!=x->getKey()){
        hash_1=(hash_1+i*hash_2)%tableSize;
        i++;
    }
    //cout<<"nodo con chiave : "<<k->getKey()<<" trovato in posizione :"<<hash_1<<endl;
    return hash_1;
}

    template<typename T>
    void HashGraph<T>::addEdge(Node<T>* i,Node<T>* j) {
            auto x=HashKey(i);
            if(table[x]!=nullptr)
            table[x]->addEdge(j);
    }

    template<typename T>
    void HashGraph<T>::printAdjList() {
        for (int i = 0; i < tableSize; i++)
        {
            if (table[i]!= nullptr) {
                cout<<i <<":"<< table[i]->getKey();
                for(auto c:table[i]->getEdges())
                    cout<<"-->"<<c->getKey();
                cout<<endl;
            }else{
                cout<<i<<":"<<endl;
            }
        }


    }

    template<typename T>
    bool HashGraph<T>::findEdge(Node<T>* i, Node<T>* j) {
        auto x= HashKey(i);
        if(table[x]!=nullptr){
            return table[x]->checkEdge(j);
        }else{
            cout<<"Non esiste un arco tra i due nodi"<<endl;
            return false;
        }
    }

    template<typename T>
    void HashGraph<T>::removeEdge(Node<T>* i,Node<T>* j) {
       auto x= HashKey(i);
       auto t = new Node<T>(0);
       if(table[x] != nullptr && findEdge(i,j)){
           auto tmp=table[x]->getEdges();
           for(auto it:tmp){
               if(it->getKey()==j->getKey()){
                   t=it;
                   break;
               }
           }
           tmp.erase(remove(tmp.begin(), tmp.end(), t),tmp.end());
           table[x]->getEdgesPointer()->swap(tmp);
       }else{
           cout<<"impossibile effettuare la cancellazione"<<endl;
           return;
       }
    }

    template<typename T>
    void HashGraph<T>::itDFS(Node<T>* x) {
        stack<Node<T> *> stackDFS;
        vector<bool> visited(tableSize, false);
        auto v = HashKey(x);
        if(table[v]==nullptr){
            cout<<"il nodo inserito non esiste "<<endl;
            return;
        }
        stackDFS.push(x);
        while (!stackDFS.empty()) {
            auto vertex = stackDFS.top();
            stackDFS.pop();
            if (!visited[HashKey(vertex)]) {
                cout << vertex->getKey() << " ";
                visited[HashKey(vertex)] = true;
            }
            for (auto neighbor: table[HashKey(vertex)]->getEdges()) {
                if (neighbor!=nullptr && !visited[HashKey(neighbor)]){
                        stackDFS.push(neighbor);
                    }
                }
            }
            cout << endl;
        }

    template<typename T>
    bool HashGraph<T>::ifNodeEx(T key) {
    for(auto x:table){
        if(x!= nullptr && x->getKey()==key){
            return true;
        }
    }
    return false;
}

    template<typename T>
    int HashGraph<T>::getPrime() {
    for(int i=tableSize-1;i>=1;i--){
        int fact=0;
        for(int j=2;j<=(int)sqrt(i);j++)
            if(i%j==0)
                fact++;
        if(fact==0)
            return i;
    }
    /*return a prime number*/
    return 3;
}

    template<typename T>
    void HashGraph<T>::DFS() {
        vector<bool> vis(tableSize);
        for(auto it:table){
            if(it!= nullptr && !vis[HashKey(it)]){
                DFSUtil(it,vis);
                parent[HashKey(it)]=it;
            }
        }
    }

    template<typename T>
    void HashGraph<T>::DFSUtil(Node<T> *x, vector<bool> &vis) {
        vis[HashKey(x)] = true;
        cout<< x->getKey()<<" ";
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != nullptr) {
                for (auto c: table[i]->getEdges()) {
                    if (!vis[HashKey(c)]) {
                        DFSUtil(c, vis);
                    }
                }
            }
        }
}

    template<typename T>
    void HashGraph<T>::solve() {
        DFS();
    /*dopo la dfs scorro le liste di adiacenza di tutti i vertici e per i nodi che sono raggiungibili imposto lo stato a true
    * i nodi che non sono raggiungibili avranno stato a false*/
    for(auto x:parent){
        if(x!= nullptr) {
            for (auto i: x->getEdges()) {
                i->setStato(true);
            }
        }
    }
    auto x=new Node<int>(0);
    if(parent[HashKey(x)]==nullptr){
        /*controllo il nodo zero che è il bacino se esiste se non esite lo devo creare di default avrà già stato a false*/
        parent[HashKey(x)]=x;
    }
    /*aggiungo gli archi tra i nodi*/
    int min=-1;
    for(int i=0;i<parent.size();i++){
        if(parent[i]!= nullptr) {
            if (!(parent[i]->getStato())) {
                cout << parent[i]->getKey() << " ";
                parent[i]->addEdgeS(x);
                min++;
            }
        }
    }
    cout<<endl;
    cout<<"il minimo numero di collegamenti e' :"<<min<<endl;
    for (int i = 1; i < tableSize; i++) {
        if (parent[i] != nullptr && !parent[i]->getStato()) {
            cout<< parent[i]->getKey();
            for (auto c: parent[i]->getEdges())
                if (!c->getStato()) {
                    cout<< "-->" << c->getKey()<<" ";
                }
        }
    }
}

