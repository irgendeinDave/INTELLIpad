#ifndef ACINPUT_H
#define ACINPUT_H

#include <QWidget>

class acInput : public QWidget
{
    Q_OBJECT;
public:
    acInput();
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::acInput * ui;
};

#endif // ACINPUT_H
