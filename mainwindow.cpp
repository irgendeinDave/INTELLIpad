#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QtPrintSupport/QtPrintSupport>
#include <QKeyEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setWindowTitle("Welcome to INTELLIpad!");
    ui->actionActivate_Autocoplete->setShortcut(Qt::Key_AltGr);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showAppOutput(QString message, MainWindow::appOutputMessageType type)
{
    ui->AppOutput->setText(message);
    if (type == Info)
    ui->AppOutput->setStyleSheet("background : green");
    else if (type == Warning)
    ui->AppOutput->setStyleSheet("background : orange");
    else if (type == Error)
        ui->AppOutput->setStyleSheet("background : red");
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Save as");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Could not open file: " + file.errorString());
        return;
    }
    else
    {
        //open file and set window title
        QTextStream in(&file);
        QString fileText = in.readAll();
        ui->textEdit->setText(fileText);
        currentFile = filename;
        MainWindow::setWindowTitle(filename);
        file.close();
    }
}

//save
void MainWindow::on_actionSave_triggered()
{
    //open target file
    QString filename;
    if (currentFile == "")
    {
        filename = QFileDialog::getSaveFileName(nullptr, "Save", "Select file!");
    }
    else
    {
        filename = currentFile;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save into file: ", file.errorString());
        return;
    }
    //save
    QTextStream save(&file);
    QString textToSave = ui->textEdit->toPlainText();
    save << textToSave;

}

//save as
void MainWindow::on_actionSave_As_triggered()
{
    //open target file
    QString filename = QFileDialog::getSaveFileName(nullptr, "Save", "Select file");
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save into file: ", file.errorString());
        return;
    }
    //save
    QTextStream save(&file);
    QString textToSave = ui->textEdit->toPlainText();
    save << textToSave;
}

//save and quit
void MainWindow::on_actionSave_and_Quit_2_triggered()
{
    //open target file
    QString filename;
    if (currentFile == "")
    {
        filename = QFileDialog::getSaveFileName(nullptr, "Save", "Select file!");
    }
    else
    {
        filename = currentFile;
    }


    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save into file: ", file.errorString());
    }
    //save
    QTextStream save(&file);
    QString textToSave = ui->textEdit->toPlainText();
    save << textToSave;

    close();
}

//print to pdf
void MainWindow::on_actionPrint_to_PDF_triggered()
{
    ui->textEdit->setStyleSheet("color : Black;");

    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    printer.setOutputFormat(QPrinter::PdfFormat);
    if (dialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Warning!", "Printing rejected!");
    }
    else
    {
        ui->textEdit->print(&printer);
    }
    ui->textEdit->setStyleSheet("color : White;");

}

void MainWindow::on_actionNew_triggered()
{
    currentFile = "";
    ui->textEdit->setText("");
    MainWindow::setWindowTitle("INTELLIpad");
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

//editing
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//Autocomplete
void MainWindow::on_textEdit_textChanged()
{

    QFile wordlist(":/dicEnglish/usa2.txt");

    //access wordlist
    QString text = ui->textEdit->toPlainText();
    QStringList seperated = text.split(" ");
    wordlist.open(QIODevice::ReadOnly);
    if (wordlist.isOpen())
    {
        //get last word
        QString last = seperated.takeLast();

        //get matching words in dictionary
        QTextStream read(&wordlist);
        QString matching[4];
        unsigned int used = 0;

        ui->listWidget->clear();
        while (!read.atEnd())
        {          
            QString line = read.readLine();
            if (last != "")
            {
                while(!read.atEnd())
                {

                    line = read.readLine();
                    QString inputLineStart;
                    inputLineStart = line.mid(0, last.length());
                    if(inputLineStart.compare(last, Qt::CaseInsensitive) == 0)
                    {
                        ui->listWidget->addItem(line);
                        used++;
                    }
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Error!", "Dictionary not open!");
    }


    //set word and letter count
    unsigned int wordcount = seperated.length();
    ui->WordCount->setText("Words: " + QString::number(wordcount));
    unsigned int charactercount = ui->textEdit->toPlainText().length();
    ui->LetterCount->setText("Characters: " + QString::number(charactercount));

    //mark first autocomplete option
    ui->listWidget->setCurrentRow(0);
}

//apply autocomplete into text

unsigned int selectedLine = 0;
void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    qInfo() << selectedLine;
    addSelectedItem();
}
void MainWindow::on_actionSelect_Element_triggered()
{
    addSelectedItem();
}

//switching selected elements
void MainWindow::on_actionLower_Element_triggered()
{
    selectedLine++;
    ui->listWidget->setCurrentRow(selectedLine);

}
void MainWindow::on_actionUpper_Element_triggered()
{
    selectedLine--;
    ui->listWidget->setCurrentRow(selectedLine);

}

void MainWindow::addSelectedItem()
{
    QString text = ui->textEdit->toPlainText();

    //get last word
    QStringList sep = text.split(" ");
    QString last = sep.takeLast();

    //whole text without last word
    QString untouchedText;
    untouchedText = text.mid(0, text.length() - last.length());

    //append selected text to the old, untouched text
    QString newText;
    //get old text into one QString
    for (int i = 0; i < sep.length(); i++)
    {
        newText += sep.at(i) + " ";
    }
    newText += ui->listWidget->currentItem()->text();
    //overwrite the text
    ui->textEdit->setText("");
    ui->textEdit->append(newText);


}

void MainWindow::on_actionAdd_all_to_Dictionary_triggered()
{
    showAppOutput("Coming soon!", Info);
}
