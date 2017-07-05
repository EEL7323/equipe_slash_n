// C program to insert a node in AVL tree
#include "ABB.h"
#include "AlunoNode.h"
#include <iostream>
using namespace std;



/* Drier program to test above function*/
int main()
{



    ABB* arvore = new ABB();
    arvore->inserirNodo(10,50);
    arvore->inserirNodo(5,49);
    arvore->inserirNodo(4,34);
    arvore->inserirNodo(3,345);
    arvore->inserirNodo(2,345);
    arvore->inserirNodo(1,345);
    arvore->inserirNodo(100,345);
    arvore->imprimirABB();
    AlunoNode* ptr;
    ptr = arvore->findNodo(4);
    ptr->setCredito(12345);
    cout<< "Credito 5: " << arvore->findNodo(5)->getCredito() << endl;
    cout<< "Credito 4: " << ptr->getCredito() << endl;
    return 0;
}
