#include "ajouterutilisateurdialog.h"
#include "systeme.h"
#include "ui_ajouterutilisateurdialog.h"
#include "QRegularExpression"
#include "QErrorMessage"
#include "mainwindow.h"

Ajouterutilisateurdialog::Ajouterutilisateurdialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::ui_ajouterutilisateurdialog)
{
    ui->setupUi(this);
}
Ajouterutilisateurdialog::~Ajouterutilisateurdialog(){
    delete ui;
}
void Ajouterutilisateurdialog::on_b_valider_accepted(){
    QString nom=this->ui->nom->text();
    QString prenom=this->ui->prenom->text();
    QString pseudo=this->ui->pseudo->text();
    QString adresse=this->ui->adresse->text();
    QString email=this->ui->email->text();
    QString telephone=this->ui->telephone->text();
    QString statut=this->ui->statut->currentText();
    QString motdepasse=this->ui->motdepasse->text();
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
    else if(s->verifier(pseudo))
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
        s->ajouterutilisateur( pseudo,  nom, prenom, statut,
                               adresse, email, telephone,motdepasse);
        this->close();
        msg->showMessage("utilisateur insere");
    }
}

