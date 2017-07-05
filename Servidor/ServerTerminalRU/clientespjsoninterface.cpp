#include "clientespjsoninterface.h"
#include <QTextStream>

//void ClientEspJsonInterface::JsonRecAluno(QJsonArray *JsonArray, QJsonObject JsonRequest)
//{
//    AlunoServer aluno_int;
//    int howmuch;
//    QJsonObject jsonObj;

//    howmuch = JsonRequest.value("HowMuch").toInt();
//    if (howmuch == 1)
//    {
//        jsonObj = JsonArray->first().toObject();
//        JsonArray->pop_front();

//        aluno.setNome(jsonObj.value("Nome").toString());
//        aluno.setMatricula(jsonObj.value("Matricula").toInt());
//        aluno.setcreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));
//        aluno.setcreditsCard(float(jsonObj.value("creditsCard").toDouble()));
//        aluno.setSenha(jsonObj.value("senhaApp").toString());

//        flag_last_change = "aluno";
//    } else
//    {
//        if (!alunos.empty())
//            alunos.clear();

//        for (int i = 0; i < howmuch; i++)
//        {
//            jsonObj = JsonArray->first().toObject();
//            JsonArray->pop_front();

//            aluno_int.setNome(jsonObj.value("Nome").toString());
//            aluno_int.setMatricula(jsonObj.value("Matricula").toInt());
//            aluno_int.setcreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));
//            aluno_int.setcreditsCard(float(jsonObj.value("creditsCard").toDouble()));

//            alunos.insert(i, aluno_int);
//        }

//        flag_last_change = "lista";
//    }

//}

//void ClientEspJsonInterface::JsonFeedbackHandler(QJsonObject JsonFb)
//{
//    if (JsonFb.value("Acknowledge").toString() == "noError")
//    {
//        flag_last_change = QString("%1:Ok").arg(JsonFb.value("youTry").toString());
//    } else
//    {
//        flag_last_change = QString("%1:Error").arg(JsonFb.value("youTry").toString());
//    }
//    ErrorText = JsonFb.value("ErrorText").toString();
//}

ClientEspJsonInterface::ClientJsonInterface()
{
}

QString ClientEspJsonInterface::JsonReceiver(QByteArray data)
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


    return jsonObj.value("IWant").toString();

//    if (receive == "updateAll")
//    {
//        this->JsonRecAluno(&jsonArray, jsonObj);
//    } else if (receive == "Feedback")
//    {
//        this->JsonFeedbackHandler(jsonObj);
//    }
//    else
//    {
//        out << "Erro na leitura do cabecalho do JSON" << endl;
//    }


}

//AlunoServer ClientEspJsonInterface::getAluno()
//{
//    return aluno;
//}

//QList<AlunoServer> ClientEspJsonInterface::getAlunos()
//{
//    return alunos;
//}

//QString ClientEspJsonInterface::getFlag()
//{
//    return flag_last_change;
//}

//QString ClientEspJsonInterface::getErrorText()
//{
//    return ErrorText;
//}
