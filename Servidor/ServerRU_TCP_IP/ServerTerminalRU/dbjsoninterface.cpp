#include "dbjsoninterface.h"
#include <QTextStream>


DbJsonInterface::DbJsonInterface()
{

}

QByteArray DbJsonInterface::Handler(QByteArray inputData)
{
    QByteArray JsonOut;

    QTextStream out(stdout);

    QJsonDocument jsonDoc;
    QJsonObject jsonObj;
    QJsonArray jsonArr;

    // generate a doc json
    jsonDoc = QJsonDocument::fromJson(inputData);

    if (!jsonDoc.isArray())
    {
        out << "JSON is not configured as an Array" << endl;

        return JsonOut;
    }

    jsonArr = jsonDoc.array(); // array;

    // extrai o cabeçalho do json -> contem as informações do pedido
    jsonObj = jsonArr.first().toObject();
    jsonArr.pop_front();

    QString request;

    request = jsonObj.value("IWant").toString();

    if (request == "rAluno")
    {
        jsonDoc = requestAluno(jsonObj.value("Matricula").toInt());
        JsonOut = jsonDoc.toJson();
    } else if (request == "addAluno")
    {
        AlunoServer aluno;
        aluno.setMatricula(ulong(jsonObj.value("Matricula").toInt()));
        aluno.setNome(jsonObj.value("Nome").toString());
        aluno.setcreditsCard(float(jsonObj.value("creditsCard").toDouble()));
        aluno.setcreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));

        jsonDoc = addAluno(aluno);
        JsonOut = jsonDoc.toJson();
    } else if (request == "updateAluno")
    {
        AlunoServer aluno;
        aluno.setMatricula(ulong(jsonObj.value("Matricula").toInt()));
        aluno.setNome(jsonObj.value("Nome").toString());
        aluno.setcreditsCard(float(jsonObj.value("creditsCard").toDouble()));
        aluno.setcreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));

        jsonDoc = updateAluno(aluno);
        JsonOut = jsonDoc.toJson();
    } else if (request == "delAluno")
    {
        jsonDoc = delAluno(jsonObj.value("Matricula").toInt());
        JsonOut = jsonDoc.toJson();
    } else
    {
        out << "Erro na leitura do cabecalho do JSON" << endl;
    }

    return JsonOut;
}

QJsonDocument DbJsonInterface::requestAluno(int matricula)
{
    QTextStream out(stdout);

    QJsonDocument jsonDoc;
    QJsonObject jsonHeader;
    QJsonObject jsonAluno;
    QJsonArray jsonAlunos;
    QJsonArray jsonArray;

    if (!dbManager.isConnected())
    {
        if (!dbManager.Connect(Error))
            return jsonDoc;
    }


    if (matricula == 0)
    {
        AlunoServer aluno;
        QList<AlunoServer> alunos;
        int howmuch;
        alunos = dbManager.getAllAlunos(&howmuch);

        jsonHeader = QJsonObject{
                    {"ThereIs", "Aluno"},
                    {"HowMuch", howmuch},
                };

        for (int i = 0; i < howmuch; i++)
        {
            aluno = alunos.first();
            alunos.pop_front();

            jsonAluno = QJsonObject{
                        {"Matricula", int(aluno.getMatricula())},
                        {"Nome", aluno.getNome()},
                        {"creditsCard", aluno.getcreditsCard()},
                        {"creditsMobile", aluno.getcreditsMobile()},
                    };


            jsonAlunos.insert(i, jsonAluno);

        }

        jsonArray = QJsonArray{jsonHeader, jsonAlunos};

    } else
    {
        AlunoServer aluno;

        QString ErrorText;
        bool Error;

        aluno = dbManager.SearchAluno(ulong(matricula), &ErrorText, Error);

        if (Error)
        {

            jsonHeader = QJsonObject{
                        {"ThereIs", "Feedback"},
                        {"youTry", "rAluno"},
                        {"Acknowledge", "Error"},
                        {"ErrorText", ErrorText},
                    };

            jsonArray = QJsonArray{jsonHeader};
        } else
        {
            jsonHeader = QJsonObject{
                        {"ThereIs", "Aluno"},
                        {"HowMuch", 1},
                    };

            jsonAluno = QJsonObject{
                        {"Matricula", int(aluno.getMatricula())},
                        {"Nome", aluno.getNome()},
                        {"creditsCard", aluno.getcreditsCard()},
                        {"creditsMobile", aluno.getcreditsMobile()},
                    };

            jsonArray = QJsonArray{jsonHeader, jsonAluno};
        }

    }

    jsonDoc = QJsonDocument{jsonArray};

    return jsonDoc;
}

QJsonDocument DbJsonInterface::addAluno(AlunoServer aluno)
{
    QTextStream out(stdout);

    QJsonDocument jsonDoc;
    QJsonObject jsonHeader;
    QJsonArray jsonArray;

    if (!dbManager.isConnected())
    {
        if (!dbManager.Connect(Error))
            return jsonDoc;
    }

    QString ErrorText;
    QString Ackowledge;

    if (dbManager.AddAluno(aluno, &ErrorText))
    {
        Ackowledge = "noError";
    } else
    {
        Ackowledge = "Error";
    }

    jsonHeader = QJsonObject{
                {"ThereIs", "Feedback"},
                {"youTry", "addAluno"},
                {"Acknowledge", Ackowledge},
                {"ErrorText", ErrorText},
            };

    jsonArray = QJsonArray{jsonHeader};
    jsonDoc = QJsonDocument{jsonArray};

    return jsonDoc;

}

QJsonDocument DbJsonInterface::updateAluno(AlunoServer aluno)
{
    QTextStream out(stdout);

    QJsonDocument jsonDoc;
    QJsonObject jsonHeader;
    QJsonArray jsonArray;

    if (!dbManager.isConnected())
    {
        if (!dbManager.Connect(Error))
            return jsonDoc;
    }

    QString ErrorText;
    QString Ackowledge;

    if (dbManager.UpdateAluno(aluno, &ErrorText))
    {
        Ackowledge = "noError";
    } else
    {
        Ackowledge = "Error";
    }

    jsonHeader = QJsonObject{
                {"ThereIs", "Feedback"},
                {"youTry", "updateAluno"},
                {"Acknowledge", Ackowledge},
                {"ErrorText", ErrorText},
            };

    jsonArray = QJsonArray{jsonHeader};
    jsonDoc = QJsonDocument{jsonArray};

    return jsonDoc;
}

QJsonDocument DbJsonInterface::delAluno(int matricula)
{
    QTextStream out(stdout);

    QJsonDocument jsonDoc;
    QJsonObject jsonHeader;
    QJsonArray jsonArray;

    if (!dbManager.isConnected())
    {
        if (!dbManager.Connect(Error))
            return jsonDoc;
    }

    QString ErrorText;
    QString Ackowledge;

    if (dbManager.delAluno(matricula, &ErrorText))
    {
        Ackowledge = "noError";
    } else
    {
        Ackowledge = "Error";
    }

    jsonHeader = QJsonObject{
                {"ThereIs", "Feedback"},
                {"youTry", "delAluno"},
                {"Acknowledge", Ackowledge},
                {"ErrorText", ErrorText},
            };

    jsonArray = QJsonArray{jsonHeader};
    jsonDoc = QJsonDocument{jsonArray};

    return jsonDoc;
}

