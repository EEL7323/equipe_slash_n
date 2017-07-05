#ifndef AVLBINARYTREE_H
#define AVLBINARYTREE_H

#include "AlunoNode.h"

class ABB{
    private:
        AlunoNode* raiz ;
        void auxApagaABB (AlunoNode*);
        void auxImprimir(AlunoNode* nodo);
        AlunoNode* auxInserirNodo(AlunoNode* node, int matricula, int credito);
        AlunoNode* auxFindNodo(AlunoNode* node, int matricula);
        AlunoNode* rightRotate(AlunoNode* node);
        AlunoNode* leftRotate(AlunoNode* node);
        int getBalance(AlunoNode* node);
        int max(AlunoNode* node);
        int getHeight(AlunoNode* node);

    public:
        ABB ();
        ~ABB ();
        void apagaABB ();
        void inserirNodo (int matricula, int credito);
        AlunoNode* findNodo(int matricula);
        bool estaVazia ();
        void imprimirABB ();
};

#endif // AVLBINARYTREE_H
