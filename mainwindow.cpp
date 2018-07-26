#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connexiondialog.h"
#include "ajouterutilisateurdialog.h"
#include "utilisateur.h"
#include "systeme.h"
#include "QString"
#include "operationcoursdialog.h"
#include "proposercoursdialog.h"
#include "modifierutilisateurdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->b_ajouterutilisateur->setVisible(false);
    ui->b_coursproposes->setVisible(false);
    ui->b_utilisateurs->setVisible(false);
    ui->tableWidget->setVisible(false);
    ui->mescoursproposes->setVisible(false);
    ui->enseignantcoursvalides->setVisible(false);
    ui->b_proposercours->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_b_seconnecter_clicked(){
    Connexiondialog *cd = new Connexiondialog(this);
    cd->exec();
    if(cd->getStatut()=="Enseignant"){
        ui->b_seconnecter->setVisible(false);
        ui->b_proposercours->setVisible(true);
        ui->enseignantcoursvalides->setVisible(true);
        ui->mescoursproposes->setVisible(true);
        ui->tableWidget->setVisible(true);

        this->setPseudo(cd->getPseudo());
        this->setTypeUtilisateur("Enseignant");

        ui->type->setText("Enseignant");
        ui->pseudo->setText(cd->getPseudo());
       //qCritical() <<this->pseudo;
    }
    if(cd->getStatut()=="Administrateur"){
        ui->b_seconnecter->setVisible(false);
        ui->b_ajouterutilisateur->setVisible(true);
        ui->b_coursproposes->setVisible(true);
        ui->b_utilisateurs->setVisible(true);
        ui->tableWidget->setVisible(true);

        this->setPseudo(cd->getPseudo());
        this->setTypeUtilisateur("Administrateur");
        ui->type->setText("Administrateur");
        ui->pseudo->setText(cd->getPseudo());
       //qCritical() <<this->pseudo;
    }
}
void MainWindow::on_b_ajouterutilisateur_clicked(){
    Ajouterutilisateurdialog *aj=new Ajouterutilisateurdialog(this);
    aj->exec();
}

void MainWindow::setTvForUtilisateur(){
    this->viderTable();
    ui->tableWidget->setColumnCount(8);

    ui->tableWidget->setHorizontalHeaderLabels(QString("pseudo;nom;prenom;statut;"
                                                       "adresse;email;"
                                                       "telephone;motdepasse").split(";"));
}
void MainWindow::viderTable(){
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
}

void MainWindow::on_b_utilisateurs_clicked(){
    Systeme* s = new Systeme();

    QVector<Utilisateur> utilisateurs;
    ui->labelDescours->setText("liste des enseignants/administrateurs");
    utilisateurs = s->afficherlesutilisateurs();
    /*remplire thead */
    this->viderTable();
    this->setTvForUtilisateur();
    for(int i = 0; i < utilisateurs.size(); i++){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem* item_id = new QTableWidgetItem(utilisateurs[i].getUsername());
        item_id->setFlags(item_id->flags() ^ Qt::ItemIsSelectable);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(utilisateurs[i].getUsername()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(utilisateurs[i].getNom()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(utilisateurs[i].getPrenom()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(utilisateurs[i].getStatut()));

        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(utilisateurs[i].getAdresse()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(utilisateurs[i].getEmail()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(utilisateurs[i].getTelephone()));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(utilisateurs[i].getMotDepasse()));

    }
    int columnSize = ui->tableWidget->width() / ui->tableWidget->columnCount();
    for(int i = 0; i < ui->tableWidget->columnCount(); i++){
        ui->tableWidget->horizontalHeader()->resizeSection(i, columnSize);
    }

}
void MainWindow::on_b_proposercours_clicked(){
    Proposercoursdialog *p=new Proposercoursdialog(this,this->pseudo);
    p->exec();
    on_mescoursproposes_clicked();
    QApplication::processEvents();
}

void MainWindow::estConnecte(){
    ui->b_ajouterutilisateur->setVisible(true);
    ui->b_coursproposes->setVisible(true);
    ui->b_utilisateurs->setVisible(true);
    ui->tableWidget->setVisible(true);
    ui->b_seconnecter->setVisible(false);
}
void MainWindow::setPseudo(QString pseudo){
    this->pseudo=pseudo;
}
QString MainWindow::getTypeUtilisateur(){
    return typeUtilisateur;
}

void MainWindow::setTvForCours(){
    this->viderTable();
    ui->tableWidget->setColumnCount(8);

    ui->tableWidget->setHorizontalHeaderLabels(
        QString("titre;date Debut;date Fin ;date debut Inscription ;"
                "date fin Inscription ;commentaire;nbMaxEtudiant;pseudoEnseignant").split(";"));

}

void MainWindow::setTypeUtilisateur(QString typeUtilisateur){
    this->typeUtilisateur=typeUtilisateur;
}

void MainWindow::on_b_coursproposes_clicked(){
    Systeme* s = new Systeme();
    QVector<Cours> cours;
    ui->labelDescours->setText("Les cours proposés par les enseignants");
    cours = s->afficherlescoursproposes();
    /*remplire thead */
    this->viderTable();
    this->setTvForCours();
    for(int i = 0; i < cours.size(); i++){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem* item_id = new QTableWidgetItem(cours[i].getTitre());
        item_id->setFlags(item_id->flags() ^ Qt::ItemIsEditable);
        item_id->setFlags(item_id->flags() ^ Qt::ItemIsSelectable);
        ui->tableWidget->setItem(i, 0,item_id);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(cours[i].getDateDebut().toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(cours[i].getDatefin().toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(cours[i].getDateDebutInscription().toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(cours[i].getDatefinInscription().toString()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(cours[i].getCommentaire()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(cours[i].getnbmaxEtudiant())));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(cours[i].getPseudo()));
    }

    int columnSize = ui->tableWidget->width() / ui->tableWidget->columnCount();
    for(int i = 0; i < ui->tableWidget->columnCount(); i++){
        ui->tableWidget->horizontalHeader()->resizeSection(i, columnSize);
    }
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row,int column){
    //Systeme* s = new Systeme();
    if(ui->tableWidget->horizontalHeaderItem(0)->text()=="titre" &&
     this->getTypeUtilisateur()=="Administrateur"){
        //qDebug()<<ui->tableWidget->item(row,column)->text();
        Operationcoursdialog *op=new Operationcoursdialog(this);
        QString titre=ui->tableWidget->item(row,0)->text();
        QDate datedebut=QDate::fromString(ui->tableWidget->item(row,1)->text());
        QDate datefin=QDate::fromString(ui->tableWidget->item(row,2)->text());
        QDate datedebutinscription=QDate::fromString(ui->tableWidget->item(row,3)->text());
        QDate datefininscription=QDate::fromString(ui->tableWidget->item(row,4)->text());
        QString commentaire=ui->tableWidget->item(row,5)->text();
        QString nbMaxEtudiant=ui->tableWidget->item(row,6)->text();
        QString pseudoEnseignant=ui->tableWidget->item(row,7)->text();

        op->setFormulaireModification(titre,datedebut,datefin,
                                      datedebutinscription,datefininscription,
                                      nbMaxEtudiant,pseudoEnseignant,commentaire);
        op->exec();
        on_b_coursproposes_clicked();
        QApplication::processEvents();
    }
    else if(ui->tableWidget->horizontalHeaderItem(0)->text()=="pseudo" &&
        this->getTypeUtilisateur()=="Administrateur"){
        Modifierutilisateur *mu=new Modifierutilisateur(this);
        QString pseudo=ui->tableWidget->item(row,0)->text();
        QString nom=ui->tableWidget->item(row,1)->text();
        QString prenom=ui->tableWidget->item(row,2)->text();
        QString statut=ui->tableWidget->item(row,3)->text();
        QString adresse=ui->tableWidget->item(row,4)->text();
        QString email=ui->tableWidget->item(row,5)->text();
        QString telephone=ui->tableWidget->item(row,6)->text();
        QString motdepasse=ui->tableWidget->item(row,7)->text();

        mu->modifierformulaire( pseudo, nom,
            prenom, statut,  adresse, email,telephone,motdepasse);
        mu->exec();
        on_b_utilisateurs_clicked();
        QApplication::processEvents();
    }

}
void MainWindow::on_enseignantcoursvalides_clicked(){
    Systeme* s = new Systeme();
    QVector<Cours> cours;

    cours = s->afficherlescoursvalidesCoteEnseignant(pseudo);
    /*remplire thead */
    this->viderTable();
    this->setTvForCours();
    for(int i = 0; i < cours.size(); i++){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem* item_id = new QTableWidgetItem(cours[i].getTitre());
        item_id->setFlags(item_id->flags() ^ Qt::ItemIsEditable);
        item_id->setFlags(item_id->flags() ^ Qt::ItemIsSelectable);
        ui->tableWidget->setItem(i, 0,item_id);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(cours[i].getDateDebut().toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(cours[i].getDatefin().toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(cours[i].getDateDebutInscription().toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(cours[i].getDatefinInscription().toString()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(cours[i].getCommentaire()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(cours[i].getnbmaxEtudiant())));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(cours[i].getPseudo()));
    }

    int columnSize = ui->tableWidget->width() / ui->tableWidget->columnCount();
    for(int i = 0; i < ui->tableWidget->columnCount(); i++){
        ui->tableWidget->horizontalHeader()->resizeSection(i, columnSize);
    }
    ui->labelDescours->setText("Mes cours validés");

}
void MainWindow::on_mescoursproposes_clicked(){
    Systeme* s = new Systeme();

    QVector<Cours> cours;

    cours = s->afficherMescoursproposes(this->pseudo);
    /*remplire thead */
    this->viderTable();
    this->setTvForCours();
    for(int i = 0; i < cours.size(); i++){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem* item_id = new QTableWidgetItem(cours[i].getTitre());
        item_id->setFlags(item_id->flags() ^ Qt::ItemIsEditable);
        item_id->setFlags(item_id->flags() ^ Qt::ItemIsSelectable);
        ui->tableWidget->setItem(i, 0,item_id);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(cours[i].getDateDebut().toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(cours[i].getDatefin().toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(cours[i].getDateDebutInscription().toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(cours[i].getDatefinInscription().toString()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(cours[i].getCommentaire()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(cours[i].getnbmaxEtudiant())));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(cours[i].getPseudo()));
    }

    int columnSize = ui->tableWidget->width() / ui->tableWidget->columnCount();
    for(int i = 0; i < ui->tableWidget->columnCount(); i++){
        ui->tableWidget->horizontalHeader()->resizeSection(i, columnSize);
    }
    ui->labelDescours->setText("Mes cours proposés");
}

void MainWindow::on_quitter_clicked(){
    this->close();
}
void MainWindow::on_sedeconnecter_clicked(){
    ui->b_ajouterutilisateur->setVisible(false);
    ui->b_coursproposes->setVisible(false);
    ui->b_utilisateurs->setVisible(false);
    ui->tableWidget->setVisible(false);
    ui->mescoursproposes->setVisible(false);
    ui->enseignantcoursvalides->setVisible(false);
    ui->b_proposercours->setVisible(false);
    ui->b_seconnecter->setVisible(false);
    ui->b_seconnecter->setVisible(true);
    ui->type->setText("");
    ui->pseudo->setText("");
    ui->labelDescours->setText("");

    this->setPseudo("");
    this->setTypeUtilisateur("");
    this->viderTable();

}
