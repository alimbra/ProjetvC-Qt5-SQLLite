#include "modifierutilisateurdialog.h"
#include "ui_modifierutilisateurdialog.h"
#include "QErrorMessage"
#include "QRegularExpression"
#include "systeme.h"
Modifierutilisateur::Modifierutilisateur(QWidget *parent):
    QDialog(parent),ui(new Ui::Modifierutilisateurdialog){
    ui->setupUi(this);
}

void Modifierutilisateur::modifierformulaire(QString pseudo,QString nom,
QString prenom,QString statut, QString adresse,
QString email,QString telephone,QString motdepasse){
    this->ui->nom->setText(nom);
    this->ui->ancienpseudo->setText(pseudo);
    this->ui->ancienpseudo->setVisible(false);

    this->ui->prenom->setText(prenom);
    this->ui->pseudomod->setText(pseudo);
    this->ui->adresse->setText(adresse);
    this->ui->email->setText(email);
    this->ui->telephone->setText(telephone);
    this->ui->statut->setCurrentText(statut);
    this->ui->motdepasse->setText(motdepasse);

}

void Modifierutilisateur::on_modifier_clicked(){
    QString nom=this->ui->nom->text();
    QString prenom=this->ui->prenom->text();
    QString pseudo=this->ui->pseudomod->text();
    QString adresse=this->ui->adresse->text();
    QString email=this->ui->email->text();
    QString telephone=this->ui->telephone->text();
    QString statut=this->ui->statut->currentText();
    QString motdepasse=this->ui->motdepasse->text();
    QString ancienpseudo=this->ui->ancienpseudo->text();
    Systeme *s = new Systeme();

    QErrorMessage* msg = new QErrorMessage();
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*"
                             "[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)"
                             "*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    QRegularExpression regTel("^[0-9]{10}$");
    if(email.isEmpty() || !regex.match(email).hasMatch())
    {
        msg->showMessage("Vous devez renseigner l email de l´utilisateur correctement.");
    }
    else if(pseudo.isEmpty() ){
        msg->showMessage("Vous devez renseigner le pseudo de l´utilisateur");
    }
    else if(s->verifier(pseudo) && pseudo!=ancienpseudo)
    {
        msg->showMessage(" pseudo existant de l´utilisateur ! ");
    }
    else if(prenom.isEmpty()){
        msg->showMessage("Vous devez renseigner le prénom de l´utilisateur");
    }
    else if(nom.isEmpty()){
        msg->showMessage("Vous devez renseigner le nom de l´utilisateur.");
    }
    else if(adresse.isEmpty()){
        msg->showMessage("Vous devez renseigner l'adresse de l´utilisateur.");
    }
    else if(telephone.isEmpty() || !regTel.match(telephone).hasMatch()){
        msg->showMessage("Vous devez renseigner le telephone de l´utilisateur Correctement.");
    }
    else if(motdepasse.isEmpty()){
        msg->showMessage("Vous devez renseigner le mot de passe de l´utilisateur.");
    }
    else{
        s->modifierutilisateur( ancienpseudo,pseudo,  nom, prenom, statut,
                               adresse, email, telephone,motdepasse);
        this->close();
        msg->showMessage("utilisateur modifie");
    }
}

void Modifierutilisateur::on_supprimer_clicked(){
    Systeme *s=new Systeme();
    QErrorMessage *msg=new QErrorMessage();
    s->supprimerutilisateur(ui->ancienpseudo->text());
    msg->showMessage("utilisateur supprime");
    this->close();
}

void Modifierutilisateur::on_annuler_clicked(){
    this->close();
}
