#include "dbjsoninterface.h"
#include <QTextStream>


DbJsonInterface::DbJsonInterface()
{

}

QByteArray DbJsonInterface::Handler(QByteArray inputData, bool &flag, int index, int size)
{
    QByteArray JsonOut;

    QTextStream out(stdout);

    QJsonDocument jsonDoc;
    QJsonObject jsonObj;
    QJsonArray jsonArr;

    flag = false;
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
        jsonDoc = requestAluno(jsonObj.value("Matricula").toInt(), flag, index, size);
        JsonOut = jsonDoc.toJson();
    } else if (request == "addAluno")
    {
        AlunoServer aluno;
        aluno.setMatricula(ulong(jsonObj.value("Matricula").toInt()));
        aluno.setNome(jsonObj.value("Nome").toString());
        aluno.setcreditsCard(float(jsonObj.value("creditsCard").toDouble()));
        aluno.setcreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));
        aluno.setSenha(jsonObj.value("senhaApp").toString());

        jsonDoc = addAluno(aluno);
        JsonOut = jsonDoc.toJson();
    } else if (request == "updateAluno")
    {
        AlunoServer aluno;
        aluno.setMatricula(ulong(jsonObj.value("Matricula").toInt()));
        aluno.setNome(jsonObj.value("Nome").toString());
        aluno.setcreditsCard(float(jsonObj.value("creditsCard").toDouble()));
        aluno.setcreditsMobile(float(jsonObj.value("creditsMobile").toDouble()));
        aluno.setSenha(jsonObj.value("senhaApp").toString());

        jsonDoc = updateAluno(aluno);
        JsonOut = jsonDoc.toJson();
    } else if (request == "updateAlunos")
    {
        QString ErrorText;
        AlunoServer aluno;
        bool error;

        int howmuch = jsonObj.value("HowMuch").toInt();
        jsonArr = jsonArr.first().toArray();

        for (int i = 0; i < howmuch; i++)
        {
            jsonObj = jsonArr.first().toObject();
            jsonArr.pop_front();

            aluno = dbManager.SearchAluno(ulong(jsonObj.value("Matricula").toInt()), &ErrorText, error);

            if (jsonObj.value("credit").toString() == "Mobile")
            {
                aluno.setcreditsMobile(aluno.getcreditsMobile() - RUprice);
            } else if (jsonObj.value("credit").toString() == "Card")
            {
                aluno.setcreditsCard(aluno.getcreditsCard() - RUprice);
            } else
            {
                out << "Erro ao debitar credito de " << aluno.getNome() << ".\n\n";
            }

            dbManager.UpdateAluno(aluno, &ErrorText);
        }

        request = "Good";
        JsonOut = request.toLocal8Bit();
    }
    else if (request == "delAluno")
    {
        jsonDoc = delAluno(jsonObj.value("Matricula").toInt());
        JsonOut = jsonDoc.toJson();
    }
    else if (request == "changeCard")
    {
        jsonDoc = addCreditCard(jsonObj.value("Matricula").toInt(), float(jsonObj.value("Amount").toDouble()));
        JsonOut = jsonDoc.toJson();
    }
    else if (request == "changeMobile")
    {
        jsonDoc = addCreditMobile(jsonObj.value("Matricula").toInt(), float(jsonObj.value("Amount").toDouble()));
        JsonOut = jsonDoc.toJson();
    }
    else if (request == "nothing")
        JsonOut = request.toLocal8Bit();
    else
    {
        jsonDoc = DontUnderstand(jsonObj);
        JsonOut = jsonDoc.toJson();
        out << "Erro na leitura do cabecalho do JSON" << endl;
    }

    return JsonOut;
}

QJsonDocument DbJsonInterface::addCreditCard(int matricula, float amount)
{
    QJsonDocument jsonDoc;
    QJsonObject jsonHeader;
    QJsonArray jsonArray;

    AlunoServer aluno;
    QString ErrorText;
    bool Error;

    aluno = dbManager.SearchAluno(ulong(matricula), &ErrorText, Error);

    if (Error)
    {
        jsonHeader = QJsonObject{
                    {"ThereIs", "Feedback"},
                    {"youTry", "changeCard"},
                    {"Acknowledge", "Error"},
                    {"ErrorText", ErrorText},
                };

    } else
    {
        aluno.setcreditsCard(aluno.getcreditsCard()+amount);
        Error = dbManager.UpdateAluno(aluno, &ErrorText);
        if (Error)
        {
            jsonHeader = QJsonObject{
                         {"ThereIs", "Feedback"},
                         {"youTry", "changeCard"},
                         {"Acknowledge", "Error"},
                         {"ErrorText", ErrorText},
                     };

        } else
        {
            jsonHeader = QJsonObject{
                        {"ThereIs", "Feedback"},
                        {"youTry", "changeCard"},
                        {"Acknowledge", "noError"},
                    };
        }
    }

    jsonArray = QJsonArray{jsonHeader};
    jsonDoc = QJsonDocument{jsonArray};
    return jsonDoc;
}


QJsonDocument DbJsonInterface::addCreditMobile(int matricula, float amount)
{
    AlunoServer aluno;
    QString ErrorText;
    bool Error;

    QJsonDocument jsonDoc;
    QJsonObject jsonHeader;
    QJsonArray jsonArray;

    aluno = dbManager.SearchAluno(ulong(matricula), &ErrorText, Error);

    if (Error)
    {
       jsonHeader = QJsonObject{
                    {"ThereIs", "Feedback"},
                    {"youTry", "changeMobile"},
                    {"Acknowledge", "Error"},
                    {"ErrorText", ErrorText},
                };

    } else
    {
        aluno.setcreditsMobile(aluno.getcreditsMobile()+amount);
        Error = dbManager.UpdateAluno(aluno, &ErrorText);
        if (Error)
        {
            jsonHeader = QJsonObject{
                         {"ThereIs", "Feedback"},
                         {"youTry", "changeMobile"},
                         {"Acknowledge", "Error"},
                         {"ErrorText", ErrorText},
                     };

        } else
        {
            jsonHeader = QJsonObject{
                        {"ThereIs", "Feedback"},
                        {"youTry", "changeMobile"},
                        {"Acknowledge", "noError"},
                    };
        }
    }
    jsonArray = QJsonArray{jsonHeader};
    jsonDoc = QJsonDocument{jsonArray};

    return jsonDoc;
}

QJsonDocument DbJsonInterface::requestAluno(int matricula, bool &has_aluno, int index, int size)
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
        has_aluno = true;
        if (size != 0)
        {
            for (int i = 0; i < index; i++)
                if (!alunos.empty())
                    alunos.pop_front();

            has_aluno = !alunos.empty();

            if (howmuch > size + index)
                howmuch = size;
            else
                howmuch = howmuch - index;
        }
        if (howmuch <= 0)
            return jsonDoc;

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
                        {"senhaApp", aluno.getSenha()},
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
                        {"senhaApp", aluno.getSenha()},
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

QJsonDocument DbJsonInterface::DontUnderstand(QJsonObject header)
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

    QString ErrorText = "Nao sei o que voce quis dizer..";
    QString Ackowledge;

    Ackowledge = "Error";

    jsonHeader = QJsonObject{
                {"ThereIs", "Feedback"},
                {"youTry", header.value("IWant").toString()},
                {"Acknowledge", Ackowledge},
                {"ErrorText", ErrorText},
            };

    jsonArray = QJsonArray{jsonHeader};
    jsonDoc = QJsonDocument{jsonArray};

    return jsonDoc;
}
