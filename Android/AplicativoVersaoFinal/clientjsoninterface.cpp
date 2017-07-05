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
    } else if (receive == "Aluno")
    {
        this->JsonRecAluno(&jsonArray, jsonObj);
    }
    else if (receive == "ocupacaoRU")
    {
        occupants = jsonObj.value("ocupacao").toInt();
    } else
    {
        out << "Erro na leitura do cabecalho do JSON" << endl;
    }


}

AlunoApp ClientJsonInterface::getAluno()
{
    return aluno;
}

int ClientJsonInterface::getOccupants()
{
    return occupants;
}

void ClientJsonInterface::JsonRecAluno(QJsonArray *JsonArray, QJsonObject JsonRequest)
{
    AlunoApp aluno_int;
    int howmuch;
    QJsonObject jsonObj;

    howmuch = JsonRequest.value("HowMuch").toInt();
    if (howmuch == 1)
    {
        jsonObj = JsonArray->first().toObject();
        JsonArray->pop_front();

        aluno.setNome(jsonObj.value("Nome").toString());
        aluno.setMatricula(jsonObj.value("Matricula").toInt());
        aluno.setCreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));
        aluno.setCreditsCard(float(jsonObj.value("creditsCard").toDouble()));
        aluno.setSenha(jsonObj.value("senhaApp").toString());

        flag_last_change = "aluno";
    } else
    {
        if (!alunos.empty())
            alunos.clear();

        for (int i = 0; i < howmuch; i++)
        {
            jsonObj = JsonArray->first().toObject();
            JsonArray->pop_front();

            aluno_int.setNome(jsonObj.value("Nome").toString());
            aluno_int.setMatricula(jsonObj.value("Matricula").toInt());
            aluno_int.setCreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));
            aluno_int.setCreditsCard(float(jsonObj.value("creditsCard").toDouble()));

            alunos.insert(i, aluno_int);
        }

        flag_last_change = "lista";
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
