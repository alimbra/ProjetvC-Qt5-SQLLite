#ifndef OPERATIONCOURSDIALOG_H
#define OPERATIONCOURSDIALOG_H

#include <QDialog>

namespace Ui {
    class Operationcoursdialog;
}
using namespace std;

class Operationcoursdialog:public QDialog
{
    Q_OBJECT
public:
    explicit Operationcoursdialog(QWidget *parent);
    ~Operationcoursdialog();
    void setFormulaireModification(
            QString titre,QDate datedebut,
            QDate datefin,QDate datedebutInscription,
            QDate datefinInscription,QString nbMaxEtudiant,
            QString pseudo,QString commentaire
            );
private slots:
    void on_accepter_clicked();
    void on_refuser_clicked();
    void on_annuler_clicked();

private:
    Ui::Operationcoursdialog *ui;


};
#endif // OPERATIONCOURSDIALOG_H
