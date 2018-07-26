#ifndef ACCEPTERREFUSERCOURSDIALOG_H
#define ACCEPTERREFUSERCOURSDIALOG_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Accepterrefusercoursdialog;
}
class Accepterrefusercoursdialog:public QDialog
{
    Q_OBJECT

public:
    explicit Accepterrefusercoursdialog(QWidget *parent=0);
    ~Accepterrefusercoursdialog();
private slots:
    void on_accepter_clicked();
    void on_refuser_clicked();

private:
    Ui::Accepterrefusercoursdialog *ui;

};

#endif // ACCEPTERREFUSERCOURSDIALOG_H
