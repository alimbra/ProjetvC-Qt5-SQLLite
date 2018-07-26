#include "connexiondialog.h"
#include "ui_connexiondialog.h"
#include "systeme.h"
#include "QErrorMessage"

Connexiondialog::Connexiondialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexiondialog)
{
    ui->setupUi(this);
}

Connexiondialog::~Connexiondialog()
{
    delete ui;
}
void Connexiondialog::on_b_connecter_accepted(){
    Systeme *s=new Systeme();
    QString pseudo=ui->pseudo->text();
    QString motdepasse=ui->motdepasse->text();
    QErrorMessage* msg = new QErrorMessage();

    if(pseudo.isEmpty()){
        msg->showMessage("Vous devez renseigner le pseudo");
    }
    else if(motdepasse.isEmpty()){
        msg->showMessage("Vous devez renseigner votre mot de passe");
    }
    else if(!s->verifier(pseudo,motdepasse)){
        msg->showMessage("vous n existez pas");
    }
    else{
        this->close();
        this->setStatut(s->getTypeUtilisateur());
        this->setPseudo(s->getPseudo());
        msg->showMessage("vous etes connectes ");

    }
    this->close();
}
QString Connexiondialog::getStatut(){
    return this->statut;
}
QString Connexiondialog::getPseudo(){
    return this->pseudo;
}

void Connexiondialog::setStatut(QString statut){
    this->statut=statut;
}
void Connexiondialog::setPseudo(QString pseudo){
    this->pseudo=pseudo;
}

void Connexiondialog::on_b_connecter_rejected(){
    this->close();
}
