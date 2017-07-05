#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include "entryNode.cpp"

class entryList{
    private:
        entryNode* root;
    public:
        int size;
        entryList();
        void getHead(int &matr, int &creditType);
        void addEntry(int matr, int creditT);

};

#endif // ENTRYLIST_H
