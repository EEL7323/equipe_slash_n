#include "alunoapp.h"

AlunoApp::AlunoApp()
{
    Senha = "";
}

void AlunoApp::setSenha(QString senhaAux)
{
    Senha = senhaAux;
}

QString AlunoApp::getSenha()
{
    return Senha;
}
