#include "proposercoursdialog.h"
#include "ui_proposercoursdialog.h"
#include "QErrorMessage"
#include "systeme.h"


Proposercoursdialog::Proposercoursdialog(QWidget *parent):
    QDialog(parent),ui(new Ui::Proposercoursdialog)
{
    ui->setupUi(this);
}

Proposercoursdialog::Proposercoursdialog(QWidget *parent,QString pseudo):
    QDialog(parent),ui(new Ui::Proposercoursdialog)
{
    ui->setupUi(this);
    this->pseudo=pseudo;
}


Proposercoursdialog::~Proposercoursdialog()
{
    delete ui;
}

void Proposercoursdialog::on_valider_accepted(){
    QString titre=this->ui->titre->text();
    QDate datedebut=this->ui->datedebut->date();
    QDate datefin=this->ui->datefin->date();
    QDate datedebutInscription=this->ui->datedebutinscription->date();
    QDate datefinInscription=this->ui->datefininscription->date();
    QString commentaire=this->ui->commentaire->toPlainText();
    QString nbmax=this->ui->nbmaxetudiant->text();
    QErrorMessage *msg=new QErrorMessage();
    QDate dateactuelle=QDate::currentDate();
    Systeme *s = new Systeme();
    if(nbmax.isEmpty() or nbmax.toInt()<=0){
        msg->showMessage("inserer le nbMax des etudiants correctement");
    }
    else if(titre.isEmpty()){
        msg->showMessage("inserer le titre du cours ");
    }
    else if(!datedebut.isValid() || (datedebut<=dateactuelle)){
        msg->showMessage("date debut format incorrect ou illogique ");

    }
    else if(!datefin.isValid() || datefin<=dateactuelle){
        msg->showMessage("date fin format incorrect ou illogique ");
    }
    else if(!datedebutInscription.isValid() || datedebutInscription<=dateactuelle){
        msg->showMessage("date debut inscription format incorrect ou illogique ");

    }
    else if(!datefinInscription.isValid() || datefinInscription<=dateactuelle){
        msg->showMessage("date fin inscription format incorrect ou illogique ");
    }
    else if(datefin<=datedebut){
        msg->showMessage("date debut> date fin ");
    }
    else if(datefinInscription<=datedebutInscription){
        msg->showMessage("date debut inscription > date fin inscription ");
    }
    else if(commentaire.isEmpty()){
        msg->showMessage("inserer le commentaire ");
    }
    else{
        s->proposercours(titre, datedebut, datefin,
                          datedebutInscription, datefinInscription,
                          nbmax.toInt(),commentaire,
                          this->pseudo,false);
        msg->showMessage("cours insere");
        this->close();
    }
}


