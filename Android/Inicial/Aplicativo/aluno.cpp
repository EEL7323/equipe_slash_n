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

float   Aluno::getCreditsMobile() {
    return creditsMobile;
}

float   Aluno::getCreditsCard() {
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

void    Aluno::setCreditsMobile(float credito) {
    creditsMobile = credito;
}

void    Aluno::setCreditsCard(float credito) {
    creditsCard = credito;
}
