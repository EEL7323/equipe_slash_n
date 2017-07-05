#include "clientjsoninterface.h"
#include <QTextStream>

void ClientJsonInterface::JsonSync(QJsonArray *JsonArray, QJsonObject JsonRequest)
{
	QJsonObject jsonObj;

	aluno.setCreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));
	aluno.setCreditsCard(float(jsonObj.value("creditsCard").toDouble()));
}

void ClientJsonInterface::JsonSaldoCard(QJsonArray *JsonArray, QJsonObject JsonRequest)
{
	QJsonObject jsonObj;

	aluno.setCreditsCard(float(jsonObj.value("creditsCard").toDouble()));
}

void ClientJsonInterface::JsonSaldoMobile(QJsonArray *JsonArray, QJsonObject JsonRequest)
{
	QJsonObject jsonObj;

	aluno.setCreditsCard(float(jsonObj.value("creditsMobile").toDouble()));
}


void ClientJsonInterface::JsonFeedbackHandler(QJsonObject JsonFb)
{
    if (JsonFb.value("Acknowledge").toString() == "noError")
    {
        flag_last_change = QString("%1:Ok").arg(JsonFb.value("youTry").toString());
    } else
    {
        flag_last_change = QString("%1:Error").arg(JsonFb.value("youTry").toString());
    }
    ErrorText = JsonFb.value("ErrorText").toString();
}

ClientJsonInterface::ClientJsonInterface()
{
    flag_last_change = "";
}

void ClientJsonInterface::JsonReceiver(QByteArray data)
{
    QTextStream out(stdout);

    QJsonDocument   jsonDoc;
    QJsonArray      jsonArray;
    QJsonObject     jsonObj;

    jsonDoc = QJsonDocument::fromJson(data);

    if (!jsonDoc.isArray())
    {
        out << "JSON is not configured like Array" << endl;

        return;
    }

    jsonArray = jsonDoc.array(); // array;

    // extrai o cabeçalho do json -> contem as informações do pedido
    jsonObj = jsonArray.first().toObject();
    jsonArray.pop_front();


    QString receive;

    receive = jsonObj.value("ThereIs").toString();

    if (receive == "SaldoMobile")
    {
        this->JsonSaldoMobile(&jsonArray, jsonObj);
    } else if (receive == "SaldoCard")
    {
    	this->JsonSaldoCard(&jsonArray, jsonObj);
    } else if (receive == "Sync")
    {
    	this->JsonSync(&jsonArray, jsonObj);
    } else if (receive == "Feedback")
    {
        this->JsonFeedbackHandler(jsonObj);
    }
    else
    {
        out << "Erro na leitura do cabecalho do JSON" << endl;
    }


}

QString ClientJsonInterface::getFlag()
{
    return flag_last_change;
}

QString ClientJsonInterface::getErrorText()
{
    return ErrorText;
}