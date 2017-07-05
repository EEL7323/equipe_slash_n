#ifndef ALUNONODE_H
#define ALUNONODE_H




class AlunoNode {
   private:
    int credito;
   public:
    int ID;
    int height;
    AlunoNode *esquerda;
    AlunoNode *direita;

    AlunoNode();
    AlunoNode(int matricula, int val);
    int getCredito();
    void setCredito(int novoCredito);
    AlunoNode* nodoEsquerda();
    AlunoNode* nodoDireita();
    bool isLeaf();
};

#endif // ALUNONODE_H
