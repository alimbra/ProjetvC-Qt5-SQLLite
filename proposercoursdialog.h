#ifndef PROPOSERCOURSDIALOG_H
#define PROPOSERCOURSDIALOG_H

#include <QDialog>
#include <QString>

using namespace std;

namespace Ui {
    class Proposercoursdialog;
}

class Proposercoursdialog:public QDialog
{
    Q_OBJECT
public:
    explicit Proposercoursdialog(QWidget *parent=0);
    Proposercoursdialog(QWidget *parent,QString pseudo);
    ~Proposercoursdialog();
private slots:
    void on_valider_accepted();
private:
    Ui::Proposercoursdialog *ui;
    QString pseudo;
};

#endif // PROPOSERCOURSDIALOG_H
