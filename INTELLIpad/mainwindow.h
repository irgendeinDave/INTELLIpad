#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

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

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_actionLower_Element_triggered();

    void on_actionUpper_Element_triggered();

    void addSelectedItemToText();

    void on_actionSelect_Element_triggered();

    void on_actionAdd_all_to_Dictionary_triggered();

    void on_actionBold_triggered();

    void on_actionItalics_triggered();

    void on_actionUnderlined_triggered();

    void on_actionSelect_Dictionary_triggered();

private:

    Ui::MainWindow *ui;
    QString currentFile = "";
};
#endif // MAINWINDOW_H
