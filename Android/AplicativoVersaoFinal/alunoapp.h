#ifndef ALUNOAPP_H
#define ALUNOAPP_H

#include "aluno.h"

class AlunoApp : public Aluno
{
    QString Senha;
public:
    AlunoApp();

    void setSenha(QString senhaAux);
    QString getSenha();
};

#endif // ALUNOAPP_H
