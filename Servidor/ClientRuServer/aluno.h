#ifndef ALUNO_H
#define ALUNO_H

#include <QCoreApplication>

class Aluno
{
    QString Nome;
    ulong Matricula;
    float creditsMobile, creditsCard;

public:
    Aluno();

    QString getNome();
    ulong   getMatricula();
    float   getcreditsMobile();
    float   getcreditsCard();

    void    setMatricula(ulong   matricula);
    void    setNome(QString nome);
    void    setcreditsMobile(float credito);
    void    setcreditsCard(float credito);

};

#endif // ALUNO_H
