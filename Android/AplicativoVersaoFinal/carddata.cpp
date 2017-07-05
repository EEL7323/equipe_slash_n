#include "carddata.h"

CardData::CardData()
{
    cardNumber[0] = ' ';
}

void CardData::setCardNumber(const char *cardReceive)
{
    strcpy(cardNumber, cardReceive);

/*    for(int i = 0; i < 16; i++){
        cardNumber[i] = *aux;
        aux++;
    }
*/}

void CardData::setMonthDeadline(short aux)
{
    monthDeadline = aux;
}

void CardData::setSafeCard(short aux)
{
    safeCard = aux;
}

void CardData::setYearDeadline(short aux)
{
    yearDeadline = aux;
}

short int CardData::getMonthDeadline(){
    return monthDeadline;
}

short int CardData::getYearDeadline()
{
    return yearDeadline;
}

short int CardData::getSafeCard()
{
    return safeCard;
}

char* CardData::getCardNumber()
{
    return cardNumber;
}
