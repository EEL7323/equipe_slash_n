#ifndef AVLBINARYTREE_H
#define AVLBINARYTREE_H

#include "AlunoNode.cpp"

class ABB{
    private:
        AlunoNode* raiz ;
        void auxApagaABB (AlunoNode*);
        void auxImprimir(AlunoNode* nodo);
        AlunoNode* auxInserirNodo(AlunoNode* node, int matricula, float creditoC, float creditoM);
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
        void inserirNodo (int matricula, float creditoC, float creditoM);
        AlunoNode* findNodo(int matricula);
        bool estaVazia ();
        void imprimirABB ();
};

#endif // AVLBINARYTREE_H
