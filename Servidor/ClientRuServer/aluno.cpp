#include "aluno.h"

Aluno::Aluno()
{
   Nome = "Empty";
   Matricula = 0;
   creditsCard = 0;
   creditsMobile = 0;
}

QString Aluno::getNome() {
    return Nome;
}

ulong   Aluno::getMatricula() {
    return Matricula;
}

float   Aluno::getcreditsMobile() {
    return creditsMobile;
}

float   Aluno::getcreditsCard() {
    return creditsCard;
}

void    Aluno::setMatricula(ulong matricula) {
    if (matricula != 0)
        Matricula = matricula;
}

void    Aluno::setNome(QString nome) {
    if (nome != "")
        Nome = nome;
}

void    Aluno::setcreditsMobile(float credito) {
    creditsMobile = credito;
}

void    Aluno::setcreditsCard(float credito) {
    creditsCard = credito;
}
