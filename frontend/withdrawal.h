#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QDialog>

namespace Ui {
class withdrawal;
}

class withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit withdrawal(QWidget *parent = nullptr);
    ~withdrawal();

private:
    Ui::withdrawal *ui;
};

#endif // WITHDRAWAL_H
