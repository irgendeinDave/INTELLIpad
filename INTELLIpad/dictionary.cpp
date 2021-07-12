#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardPaths>
#include <QMessageBox>

#include "dictionary.h"

void selectActiveDic(QWidget* parent)
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString newDicPath = QFileDialog::getSaveFileName(parent, "Select Diectionary", "Select File!");
    qInfo() << "filename specified: " + newDicPath;

    //set storing file
    QFile storingFile(home + "/.INTELLIpad/activeDic");
    storingFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if (storingFile.isOpen())
    {
        QTextStream save(&storingFile);
        save << newDicPath;
    }
    else qInfo() << "not open!";

}

QString readActiveDic()
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QFile dicNameStoringFile(home + "/.INTELLIpad/activeDic");
    if(!dicNameStoringFile.open(QIODevice::ReadOnly))
    {
        qInfo() << "Error: " << dicNameStoringFile.errorString();
        return home + "/.INTELLIpad/usa2.txt";
    }
    else
    {
        QTextStream read(&dicNameStoringFile);
        QString fileContent = read.readLine(0);
        return fileContent;
    }

}

bool WordInDic(QString wordToCheck, QString dic)
{
    QFile activeDicFile(dic);
    if(activeDicFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&activeDicFile);
        while(!in.atEnd())
        {
            if(in.readLine() == wordToCheck) return false;
        }
        return true;
    }
}

void addAllToDic(QString text)
{
    qInfo() << "Adding to dictionary";
    QStringList split = text.split(' ');

    QFile dictionary(readActiveDic());

    if (dictionary.open(QIODevice::ReadOnly | QIODevice::Append))
    {
        QTextStream out(&dictionary);
        for (int i = 0; i < split.length(); i++)
        {
            if (WordInDic(split.at(i), readActiveDic()))
            {
                out << split.at(i) << "\n";
            }
        }
    }
    else QMessageBox::critical(nullptr, "Dictionary not open!", "Dictionary could not be opened: ", dictionary.errorString());
}

