#include "AlunoNode.h"


AlunoNode::AlunoNode (int matricula, float val1, float val2){
    ID = matricula;
    creditoCard = val1;
    creditoMobile = val2;
    height = 1;
    esquerda = 0;
    direita = 0;
}
// retorna o valor armazenado no nodo
float AlunoNode::getCreditoCard (){
    return creditoCard;
}
float AlunoNode::getCreditoMobile (){
    return creditoMobile;
}
// altera o valor armazenado no nodo
void AlunoNode::setCreditoCard (float novoCredito1){
    creditoCard = novoCredito1;
}

void AlunoNode::setCreditoMobile (float novoCredito2){
    creditoMobile = novoCredito2;
}
// retorna ponteiro para o filho esquerdo do nodo atual
AlunoNode* AlunoNode::nodoEsquerda(){
    return esquerda;
}
// retorna ponteiro para o filho direito do nodo atual
AlunoNode* AlunoNode::nodoDireita (){
    return direita;
}
// retorna verdadeiro se o nodo e' uma folha
bool AlunoNode::isLeaf(){
    return (esquerda == 0) && (direita == 0);
}

