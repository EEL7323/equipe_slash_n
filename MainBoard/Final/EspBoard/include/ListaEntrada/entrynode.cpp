#include "entryNode.h"

entryNode::entryNode(int matr, int creditT)
{
    matricula = matr;
    creditType = creditT; // 0 -> cartao , 1 -> mobile
    nextNode = 0;

}


entryNode* entryNode::getNext(){
    return nextNode;
}

void entryNode::setNext(entryNode *next){
    nextNode = next;
}


