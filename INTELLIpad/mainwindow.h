#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_and_Quit_2_triggered();

    void on_actionPrint_to_PDF_triggered();

    void on_actionNew_triggered();

    void on_actionQuit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_textEdit_textChanged();    

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    void keyPressEvent(QKeyEvent* event);
};
#endif // MAINWINDOW_H