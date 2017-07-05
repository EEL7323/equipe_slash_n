#include "AlunoNode.h"


AlunoNode::AlunoNode (int matricula, int val){
    ID = matricula;
    credito = val;
    height = 1;
    esquerda = 0;
    direita = 0;
}
// retorna o valor armazenado no nodo
int AlunoNode::getCredito (){
    return credito;
}
// altera o valor armazenado no nodo
void AlunoNode::setCredito (int novoCredito){
    credito = novoCredito;
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

