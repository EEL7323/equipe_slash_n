#ifndef CARDDATA_H
#define CARDDATA_H

#include <string.h>

class CardData
{
    short int monthDeadline;
    short int yearDeadline;
    short int safeCard;
    char cardNumber[16];

public:
    CardData();
    void setMonthDeadline(short int aux);
    void setYearDeadline(short int aux);
    void setSafeCard(short int aux);
    void setCardNumber(const char* cardReceive);
    short int getMonthDeadline();
    short int getYearDeadline();
    short int getSafeCard();
    char* getCardNumber();
};

#endif // CARDDATA_H
