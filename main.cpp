    #include "HashGraph.cpp"
    #include "Node.cpp"
    using namespace std;
    void NomeFile(string&);
    void displayMenu();
    void varIns(int&);

    int main() {
        auto i=0,j=0,s=0;
        int c=0;
        int scelta=0;
        auto x=new Node<int>(i);
        auto y=new Node<int>(j);
        cout<<"Quale traccia vuoi eseguire 1 o 2 ?"<<endl;
        cin>>scelta;
        string file;
        NomeFile(file);
        HashGraph<int> a(file);
            if(scelta==1) {
                while (true) {
                    displayMenu();
                    cout << "Enter your choice :" << endl;
                    cin >> c;
                    switch (c) {
                        case 1:
                            varIns(i);
                            varIns(j);
                            x->setKey(i);
                            y->setKey(j);
                            a.addEdge(x, y);
                            break;
                        case 2:
                            varIns(i);
                            varIns(j);
                            x->setKey(i);
                            y->setKey(j);
                            if (!a.findEdge(x, y))
                                continue;
                            break;
                        case 3:
                            varIns(i);
                            varIns(j);
                            x->setKey(i);
                            y->setKey(j);
                            a.removeEdge(x, y);
                            break;
                        case 4:
                            varIns(s);
                            x->setKey(s);
                            a.itDFS(x);
                            break;
                        case 5:
                            a.DFS();
                            break;
                        case 6:
                            a.printAdjList();
                            break;
                        case 7:
                            exit(1);
                        default:
                            cout << "enter correct option " << endl;
                    }
                }
            }else if(scelta==2) {
                //a.printAdjList();
                a.solve();
            }else{
                cout<<"inserisci opzione corretta"<<endl;
                exit(1);
            }
    }
    void varIns(int& x){
        cout<<"Inserisci il valore del Nodo"<<endl;
        cin>>x;
    }
    void NomeFile(string &fileName){
        cout<<"*** Posizionare il file nello stesso percorso del progetto ***"<<endl;
        cout<<"inserire il nome del file.txt"<<endl;
        cin>>fileName;
    }
    void displayMenu(){
        cout<<"===================================================== "<<endl;
        cout<<"     MENU    "<<endl;
        cout<<"===================================================== "<<endl;
        cout<<" 1.Add Edge(i,j) "<<endl;
        cout<<" 2.Find Edge(i,j) "<<endl;
        cout<<" 3.Delete Edge(i,j) "<<endl;
        cout<<" 4.Iterative DFS(s) "<<endl;
        cout<<" 5.Recursive DFS()"<<endl;
        cout<<" 6.Print Graph in Table with AdjList "<<endl;
        cout<<" 7.Exit  "<<endl;
    }