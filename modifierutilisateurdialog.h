#ifndef MODIFIERUTILISATEURDIALOG_H
#define MODIFIERUTILISATEURDIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class Modifierutilisateurdialog;
}
class Modifierutilisateur:public QDialog{
Q_OBJECT
public:
    explicit Modifierutilisateur(QWidget *parent=0);
    void modifierformulaire(QString pseudo,QString nom,
    QString prenom,QString statut, QString adresse,
    QString email,QString telephone,QString motdepasse);

private slots:
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_annuler_clicked();
private:
    Ui::Modifierutilisateurdialog *ui;
};

#endif // MODIFIERUTILISATEURDIALOG_H
