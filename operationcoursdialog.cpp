#include "operationcoursdialog.h"
#include "ui_operationcoursdialog.h"
#include "systeme.h"
#include "QErrorMessage"

Operationcoursdialog::Operationcoursdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Operationcoursdialog)
{
    ui->setupUi(this);
    ui->pseudoenseignant->setReadOnly(true);
}


Operationcoursdialog::~Operationcoursdialog()
{
    delete ui;
}

void Operationcoursdialog::setFormulaireModification(
        QString titre,QDate datedebut,
        QDate datefin,QDate datedebutInscription,
        QDate datefinInscription,QString nbMaxEtudiant,
        QString pseudo,QString commentaire
        ){
    ui->titre->setText(titre);
    ui->datedebut->setDate(datedebut);
    ui->datefin->setDate(datefin);
    ui->datedebutinscription->setDate(datedebutInscription);
    ui->datefininscription->setDate(datefinInscription);
    ui->nbmaxetudiant->setText(nbMaxEtudiant);
    ui->commentaire->setText(commentaire);
    ui->pseudoenseignant->setText(pseudo);
}
void Operationcoursdialog::on_accepter_clicked(){
    QString titre=this->ui->titre->text();
    QDate datedebut=this->ui->datedebut->date();
    QDate datefin=this->ui->datefin->date();
    QDate datedebutInscription=this->ui->datedebutinscription->date();
    QDate datefinInscription=this->ui->datefininscription->date();
    QString commentaire=this->ui->commentaire->toPlainText();
    QString nbmax=this->ui->nbmaxetudiant->text();
    QString pseudo=this->ui->pseudoenseignant->text();
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
        s->accepter_proposition(titre, datedebut, datefin,
                          datedebutInscription, datefinInscription,
                          nbmax.toInt(),commentaire,
                          pseudo);

        msg->showMessage("cours accepte");
        this->close();
    }
}

void Operationcoursdialog::on_refuser_clicked(){
    Systeme *s = new Systeme();
    QString titre=this->ui->titre->text();
    QErrorMessage *msg=new QErrorMessage();
    s->refuser_proposition(titre);

    msg->showMessage("cours supprime");
    this->close();
}
void Operationcoursdialog::on_annuler_clicked(){
    this->close();
}
