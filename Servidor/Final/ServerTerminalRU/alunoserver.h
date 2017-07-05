#ifndef ALUNOSERVER_H
#define ALUNOSERVER_H

#include "aluno.h"

class AlunoServer : public Aluno
{
    QString senhaApp;
public:
    AlunoServer();

    void setSenha(QString senha);
    QString getSenha();
};

#endif // ALUNOSERVER_H
