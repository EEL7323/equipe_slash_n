#include <iostream>
#include "ABB.h"

using namespace std;


ABB::ABB(){
    raiz = 0; //Ptr raiz aponta pro nodo inicial
}

ABB::~ABB(){
    delete raiz;
}




AlunoNode* ABB::auxInserirNodo(AlunoNode* node, int matricula, int credito){

    if(matricula < node->ID){
        if(node->esquerda == 0){
            AlunoNode* ptr = new AlunoNode(matricula,credito);
            node->esquerda = ptr;
        }
        else{
            node->esquerda = auxInserirNodo(node->esquerda, matricula, credito);

        }
    }
    else if (matricula > node->ID){
        if(node->direita == 0){
            AlunoNode* ptr = new AlunoNode(matricula,credito);
            node->direita = ptr;
        }
        else{
            node->direita = auxInserirNodo(node->direita, matricula, credito);
        }
    }
    else // Equal matriculas are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */

    node->height = 1 + max(node);

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && matricula < (node->esquerda)->ID)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && matricula > (node->direita)->ID)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && matricula > (node->esquerda)->ID)
    {
        node->esquerda = leftRotate(node->esquerda);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && matricula < (node->direita)->ID)
    {
        node->direita = rightRotate(node->direita);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

void ABB::inserirNodo (int matricula, int credito){
    AlunoNode* ptr = raiz;
    if(ptr ==0){
        AlunoNode* nodoRaiz = new AlunoNode(matricula,credito);
        raiz = nodoRaiz;
    }
    else{
        raiz = auxInserirNodo(raiz,matricula, credito);
    }
    cout << "Inserido node:" << matricula << endl;



}

AlunoNode* ABB::auxFindNodo(AlunoNode* node, int matricula){
    if(matricula==node->ID){
        return node;
    }
    else if(matricula>node->ID){
        if(node->direita == 0){
            return 0;
        }
        else{
            return auxFindNodo(node->direita,matricula);
        }
    }
    else{
        if(node->esquerda == 0){
            return 0;
        }
        else{
            return auxFindNodo(node->esquerda,matricula);
        }
    }

}

AlunoNode* ABB::findNodo(int matricula){
    if(raiz==0){
        return 0;
    }
    else{
       return auxFindNodo(raiz,matricula);
    }

}




void ABB::auxImprimir(AlunoNode* nodo){
        cout << nodo->ID << endl ;
        if(nodo->direita != 0){
            auxImprimir(nodo->direita);
        }
        if(nodo->esquerda != 0){
            auxImprimir(nodo->esquerda);
        }
}


void ABB::imprimirABB(){
    if(raiz != 0){
        auxImprimir(raiz);
    }
    else{
        cout << "Arvore Vazia" << endl;
    }
}








AlunoNode* ABB::rightRotate(AlunoNode* y)
{
    AlunoNode *x = y->esquerda;
    AlunoNode *T2 = x->direita;

    // Perform rotation
    x->direita = y;
    y->esquerda = T2;

    // Update heights
    y->height = max(y)+1;
    x->height = max(x)+1;

    // Return new root
    return x;
}


AlunoNode* ABB::leftRotate(AlunoNode *x)
{
    AlunoNode *y = x->direita;
    AlunoNode *T2 = y->esquerda;

    // Perform rotation
    y->esquerda = x;
    x->direita = T2;

    // Update heights
    x->height = max(x)+1;
    y->height = max(y)+1;

    // Return new root
    return y;
}

int ABB::getBalance(AlunoNode *N)
{
    if (N == 0)
        return 0;
    return (getHeight(N->esquerda) - getHeight(N->direita));
}


int ABB::getHeight(AlunoNode *node){
    if(node == 0){
        return 0;
    }
    else{
        return node->height;
    }
}


int ABB::max(AlunoNode* node)
{
    int a,b,max;
    a = node->direita ==0 ? 0 : getHeight(node->direita);
    b = node->esquerda == 0? 0: getHeight(node->esquerda);
    max = a>b? a:b;
    return max;
}
