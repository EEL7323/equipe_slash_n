#ifndef ALUNONODE_H
#define ALUNONODE_H


class AlunoNode {
  private:
    float creditoCard, creditoMobile;
  public:
    int ID;
    int height;
    AlunoNode *esquerda;
    AlunoNode *direita;

    AlunoNode();
    AlunoNode(int matricula, float val1, float val2);
    float getCreditoCard();
    float getCreditoMobile();
    void setCreditoCard(float novoCredito1);
    void setCreditoMobile(float novoCredito2);
    AlunoNode* nodoEsquerda();
    AlunoNode* nodoDireita();
    bool isLeaf();
};

#endif // ALUNONODE_H
