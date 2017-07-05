#include "alunoserver.h"

AlunoServer::AlunoServer()
{

}

void AlunoServer::setSenha(QString senha)
{
    senhaApp = senha;
}

QString AlunoServer::getSenha()
{
    return senhaApp;
}

