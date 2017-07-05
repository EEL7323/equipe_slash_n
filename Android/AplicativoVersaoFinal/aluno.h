#ifndef ALUNO_H
#define ALUNO_H

#include <QCoreApplication>

class Aluno
{
protected:
    QString Nome;
    ulong Matricula;
    float creditsMobile, creditsCard;

public:
    Aluno();

    QString getNome();
    ulong   getMatricula();
    float   getCreditsMobile();
    float   getCreditsCard();

    void    setMatricula(ulong   matricula);
    void    setNome(QString nome);
    void    setCreditsMobile(float credito);
    void    setCreditsCard(float credito);

};

#endif // ALUNO_H
