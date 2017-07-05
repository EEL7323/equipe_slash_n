#include "entryList.h"


entryList::entryList(){
    root = 0;
    size = 0;
}


void entryList::getHead(int &matr, int &creditType){
    int retVal = -1;
    int credType = 0;
    if(root != 0){
        retVal = root->matricula;
        credType = root->creditType;
        entryNode* ptr = root;
        root = root->getNext();
        delete ptr;
    }
    size -= 1;
    matr = retVal;
    creditType = credType;
}

void entryList::addEntry(int matr, int creditT){
    entryNode* ptr = new entryNode(matr, creditT);
    ptr->setNext(root);
    root = ptr;
    size += 1;
}
