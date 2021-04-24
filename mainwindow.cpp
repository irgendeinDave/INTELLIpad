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
    this->setCentralWidget(ui->textEdit);

    MainWindow::setWindowTitle("INTELLIpad");
}

MainWindow::~MainWindow()
{
    delete ui;
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
