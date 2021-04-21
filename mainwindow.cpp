#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    //edit colors
    this->setStyleSheet("background-color : #131212;");
    ui->textEdit->setTextColor(qRgb(255, 255, 255));
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
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
    QString filename = currentFile;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save into file: ", file.errorString());
        return;
    }
    QTextStream save(&file);
    QString textToSave = ui->textEdit->toPlainText();
    save << textToSave;

}

//save as
void MainWindow::on_actionSave_As_triggered()
{
    //open target file
    QString filename = QFileDialog::getSaveFileName(nullptr, "Save", "Enter Filename");
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save into file: ", file.errorString());
        return;
    }
    QTextStream save(&file);
    QString textToSave = ui->textEdit->toPlainText();
    save << textToSave;
}
