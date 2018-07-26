#include "systeme.h"
#include "QDebug"
#include "QtSql"
#include "QString"
#include "QDate"



using namespace std;
Systeme::Systeme(){
    QDir path_to_db = QDir::homePath() + QString::fromStdString("/Documents/bddplateforme");

    if(!path_to_db.exists()){
        qDebug() << "Création du dossier.";
        path_to_db.mkpath(".");
    }

    this->db_path = path_to_db.path().toStdString() + "/plateforme.db";

    QSqlDatabase db = this->openDatabase();
    /*
    //supprimer une table cours
    QSqlQuery drop_table(db);
    drop_table.prepare("drop table Cours;");
    if(!drop_table.exec()){
        qCritical() << "Impossible de supprimer cours";
        qCritical() << drop_table.lastError().text();
    }*/
    QSqlQuery create_table(db);
    create_table.prepare("create table if not exists Utilisateur("
                         "pseudo varchar(40) primary key,"
                         "nom varchar(40),"
                         "prenom varchar(40),"
                         "statut varchar(40),"
                         "adresse varchar(100),"
                         "telephone varchar(100),"
                         "email varchar(100),"
                         "motdepasse varchar(100),"
                         "CONSTRAINT CHK_Statut CHECK (statut='Enseignant' "
                         "OR statut='Etudiant' OR statut='Administrateur' )"
                         ");");

    if(!create_table.exec()){
        qCritical() << "Impossible de créer la table Utilisateur";
        qCritical() << create_table.lastError().text();
    }
    QSqlQuery creer_table1(db);
    creer_table1.prepare("create table if not exists Cours("
                         "titre varchar(40) primary key,"
                         "datedebut Date,"
                         "datefin Date,"
                         "datedebutInscription Date,"
                         "datefinInscription Date,"
                         "nbMaxEtudiant integer,"
                         "commentaire varchar(100),"
                         "pseudoEnseignantcreateur varchar(40),"
                         "valide bool,"
                         "foreign key (pseudoEnseignantcreateur)"
                         "references Utilisateur(pseudo));");
    if(!creer_table1.exec()){
        qCritical() << "Impossible de créer la table Cours";
        qCritical() << creer_table1.lastError().text();
    }
    /*creer une nvlle table cours_etudiant Liste principale */
    QSqlQuery creer_table2(db);
    creer_table2.prepare("create table if not exists Liste_principale("
                         "titrecours varchar(40),"
                         "pseudoetudiant varchar(40),"
                         "dateInscription Date,"
                         "primary key(titrecours,pseudoetudiant),"
                         "foreign key(titrecours) references Cours(titre),"
                         "foreign key(pseudoetudiant) references Utilisateur(titre)"
                         ");");

    if(!creer_table2.exec()){
        qCritical() << "Impossible de créer la table Liste Principale";
        qCritical() << creer_table2.lastError().text();
    }

    /*creer une nvlle table cours_etudiant Liste Attente */
    QSqlQuery creer_table3(db);
    creer_table3.prepare("create table if not exists Liste_attente("
                         "titrecours varchar(40),"
                         "pseudoetudiant varchar(40),"
                         "dateInscription Date,"
                         "primary key(titrecours,pseudoetudiant),"
                         "foreign key(titrecours) references Cours(titre),"
                         "foreign key(pseudoetudiant) references Utilisateur(titre)"
                         ");");

    if(!creer_table3.exec()){
        qCritical() << "Impossible de créer la table Liste attente";
        qCritical() << creer_table3.lastError().text();
    }

    db.close();
}
QSqlDatabase Systeme::openDatabase(){
    QSqlDatabase db;

    if(!QSqlDatabase::contains(DB_NAME)){
        db = QSqlDatabase::addDatabase("QSQLITE", DB_NAME);
    }
    else{
        db = QSqlDatabase::database(DB_NAME);
    }

    db.setDatabaseName(QString::fromStdString(this->db_path));

    if(!db.open()){
        qCritical() << "Impossible d'ouvrir la base de données.";
    }
    else{
        return db;
    }
}

void Systeme::ajouterutilisateur(QString pseudo, QString nom,
                            QString prenom,QString statut,
                            QString adresse,QString email,
                            QString telephone,QString motdepasse){
    QSqlDatabase db=this->openDatabase();
    QSqlQuery inserer_user(db);
    inserer_user.prepare("insert into Utilisateur values(:pseudo, :nom, :prenom,"
                            " :statut, :adresse, :telephone,:email,:motdepasse);");
    inserer_user.bindValue(":pseudo", pseudo);
    inserer_user.bindValue(":nom", nom);
    inserer_user.bindValue(":prenom", prenom);
    inserer_user.bindValue(":statut", statut);
    inserer_user.bindValue(":adresse", adresse);
    inserer_user.bindValue(":telephone", telephone);
    inserer_user.bindValue(":email", email);
    inserer_user.bindValue(":motdepasse", motdepasse);

    if(!inserer_user.exec()){
        qCritical() << "Impossible d'insérer l utilisateur";
        qCritical() << inserer_user.lastError().text();
    }

    db.close();
}

void Systeme::modifierutilisateur(QString ancienpseudo,QString pseudo, QString nom,
                            QString prenom,QString statut,
                            QString adresse,QString email,
                            QString telephone,QString motdepasse){
    QSqlDatabase db=this->openDatabase();
    QSqlQuery inserer_user(db);
    inserer_user.prepare("update Utilisateur set "
                         "pseudo=:pseudo,"
                         " nom=:nom,"
                         " prenom=:prenom,"
                         " statut=:statut, "
                         " adresse=:adresse, "
                         " telephone=:telephone,"
                         " email=:email,"
                         " motdepasse=:motdepasse "
                 "where pseudo=:ancienpseudo;");

    inserer_user.bindValue(":pseudo", pseudo);
    inserer_user.bindValue(":nom", nom);
    inserer_user.bindValue(":prenom", prenom);
    inserer_user.bindValue(":statut", statut);
    inserer_user.bindValue(":adresse", adresse);
    inserer_user.bindValue(":telephone", telephone);
    inserer_user.bindValue(":email", email);
    inserer_user.bindValue(":motdepasse", motdepasse);
    inserer_user.bindValue(":ancienpseudo", ancienpseudo);


    if(!inserer_user.exec()){
        qCritical() << "Impossible de modifier l utilisateur";
        qCritical() << inserer_user.lastError().text();
    }

    db.close();
}
void Systeme::supprimerutilisateur(QString pseudoancien){
    QSqlDatabase db=this->openDatabase();
    QSqlQuery inserer_user(db);
    inserer_user.prepare("delete from Utilisateur  "
                 "where pseudo=:ancienpseudo;");

  inserer_user.bindValue(":ancienpseudo", pseudoancien);


    if(!inserer_user.exec()){
        qCritical() << "Impossible de supprimer l utilisateur";
        qCritical() << inserer_user.lastError().text();
    }

}

QVector<Utilisateur> Systeme::afficherlesutilisateurs(){
        QVector<Utilisateur> result;
        QSqlDatabase db = this->openDatabase();

        QSqlQuery fetch_utilisateurs("select *"
                                  "from Utilisateur;", db);


        while(fetch_utilisateurs.next()){

            QString pseudo= fetch_utilisateurs.value("pseudo").toString();
            QString nom = fetch_utilisateurs.value("nom").toString();
            QString prenom = fetch_utilisateurs.value("prenom").toString();
            QString statut = fetch_utilisateurs.value("statut").toString();
            QString motdepasse = fetch_utilisateurs.value("motdepasse").toString();
            QString adresse = fetch_utilisateurs.value("adresse").toString();
            QString telephone = fetch_utilisateurs.value("telephone").toString();
            QString email = fetch_utilisateurs.value("email").toString();
            Utilisateur *u = new Utilisateur( pseudo,  nom,
                                              prenom, statut,
                                              adresse, email,
                                              telephone,motdepasse);
            result.push_back(*u);
        }

        db.close();
        return result;
    }

bool Systeme::verifier(QString username){
    QVector<Utilisateur> result;
    QSqlDatabase db = this->openDatabase();

    QSqlQuery fetch_utilisateur("select *"
                              "from Utilisateur where  "
                               "pseudo=?;", db);

    fetch_utilisateur.bindValue(0, username);
    if(!fetch_utilisateur.exec()){
        qCritical()<<fetch_utilisateur.lastError();
        return false;
    }
    if(!fetch_utilisateur.next()){
        qCritical()<<fetch_utilisateur.lastError();
        return false;
    }

    return true;
}
    bool Systeme::verifier(QString username,QString motdepasse){
        QVector<Utilisateur> result;
        QSqlDatabase db = this->openDatabase();

        QSqlQuery fetch_utilisateur("select *"
                                  "from Utilisateur where  "
                                   "pseudo=? and "
                                     "motdepasse=?;", db);

        fetch_utilisateur.bindValue(0, username);
        fetch_utilisateur.bindValue(1, motdepasse);
        if(!fetch_utilisateur.exec()){
            qCritical()<<fetch_utilisateur.lastError();
            return false;
        }
        if(!fetch_utilisateur.next()){
            qCritical()<<fetch_utilisateur.lastError();
            return false;
        }
        this->setTypeUtilisateur(fetch_utilisateur.value("statut").toString());
        this->setPseudo(fetch_utilisateur.value("pseudo").toString());
        return true;
    }

    QString Systeme::getTypeUtilisateur(){
        return this->typeUtilisateur;
    }
    void Systeme::setTypeUtilisateur(QString typeUtilisateur){
        this->typeUtilisateur=typeUtilisateur;
    }
    void Systeme::proposercours(QString nomcours,
                                QDate datedebut,QDate datefin,
                                QDate datedebutinscription,QDate datefininscription,
                                int nbMaxEtudiant,QString commentaire,
                                QString pseudoEnseignant,bool valide){
        QSqlDatabase db=this->openDatabase();
        QSqlQuery inserer_cours(db);
        inserer_cours.prepare("insert into Cours values(:titre, "
                                " :datedebut, :datefin,"
                                " :datedebutinscription, :datefininscription,"
                                " :nbMaxEtudiant,:commentaire,"
                                " :pseudoEnseignantcreateur,:valide);");
        inserer_cours.bindValue(":titre", nomcours);
        inserer_cours.bindValue(":datedebut", datedebut);
        inserer_cours.bindValue(":datefin", datefin);
        inserer_cours.bindValue(":datedebutinscription", datedebutinscription);
        inserer_cours.bindValue(":datefininscription", datefininscription);
        inserer_cours.bindValue(":nbMaxEtudiant", nbMaxEtudiant);
        inserer_cours.bindValue(":commentaire", commentaire);
        inserer_cours.bindValue(":pseudoEnseignantcreateur", pseudoEnseignant);
        inserer_cours.bindValue(":valide", valide);

        if(!inserer_cours.exec()){
            qCritical() << "Impossible d'insérer le cours";
            qCritical() << inserer_cours.lastError().text();
        }

        db.close();
    }
    void Systeme::setPseudo(QString pseudo){
        this->pseudo=pseudo;
    }

    QString Systeme::getPseudo(){
        return this->pseudo;
    }
    QVector<Cours> Systeme::afficherlescoursproposes(){
        QVector<Cours> result;
        QSqlDatabase db = this->openDatabase();

        QSqlQuery fetch_cours("select *"
                                  "from Cours where valide=0 ;", db);

        while(fetch_cours.next()){

            QString titre= fetch_cours.value("titre").toString();
            QDate datedebut = fetch_cours.value("datedebut").toDate();
            QDate datefin = fetch_cours.value("datefin").toDate();
            QDate datedebutIncsription = fetch_cours.value("datedebutInscription").toDate();
            QDate datefinIncsription = fetch_cours.value("datefinInscription").toDate();
            int nbMax = fetch_cours.value("nbMaxEtudiant").toInt();

            //qCritical() << fetch_cours.value("pseudoEnseignantcreateur").toString();
            QString commentaire = fetch_cours.value("commentaire").toString();
            QString pseudo = fetch_cours.value("pseudoEnseignantcreateur").toString();
            bool valide = fetch_cours.value("valide").toBool();

            Cours *c = new Cours( titre,
                                  datedebut, datefin,
                                  datedebutIncsription, datefinIncsription,
                                  nbMax, commentaire,
                                  valide,pseudo);
            result.push_back(*c);
        }

        db.close();
        return result;
    }

    void Systeme::accepter_proposition(QString nomcours,
                                       QDate datedebut,QDate datefin,
                                       QDate datedebutinscription,QDate datefininscription,
                                       int nbMaxEtudiant,QString commentaire,
                                       QString pseudoEnseignant){

        QSqlDatabase db = this->openDatabase();

        QSqlQuery acceptercours(db);
        acceptercours.prepare("update Cours set "
        " datedebut=:datedebut,"
        " datefin=:datefin, "
        " datedebutinscription=:datedebutinscription,"
        " datefininscription=:datefininscription,"
        " nbMaxEtudiant=:nbMaxEtudiant,"
        " commentaire=:commentaire,"
        " pseudoEnseignantcreateur=:pseudoEnseignantcreateur,"
        " valide=1"
        " where titre=:titre");

        acceptercours.bindValue(":titre",nomcours);
        acceptercours.bindValue(":datedebut", datedebut);
        acceptercours.bindValue(":datefin", datefin);
        acceptercours.bindValue(":datedebutinscription", datedebutinscription);
        acceptercours.bindValue(":datefininscription", datefininscription);
        acceptercours.bindValue(":nbMaxEtudiant", nbMaxEtudiant);
        acceptercours.bindValue(":commentaire", commentaire);
        acceptercours.bindValue(":pseudoEnseignantcreateur", pseudoEnseignant);

        if(!acceptercours.exec()){
            qCritical() << "Impossible de modifier ce cours";
            qCritical() << acceptercours.lastError().text();
        }
    }
    void Systeme::refuser_proposition(QString titre){
        QSqlDatabase db = this->openDatabase();

        QSqlQuery refusercours(db);
        refusercours.prepare("delete from Cours where titre=:titre;");
        refusercours.bindValue(":titre",titre);

        if(!refusercours.exec()){
            qCritical() << "Impossible de supprimer ce cours";
            qCritical() << refusercours.lastError().text();
        }
    }
    /*
    a modifier apres pour rajouter la liste en attente
    */
    QVector<Cours> Systeme::afficherlescoursvalidesCoteEtudiant(QString pseudo){
        QVector<Cours> result;
        QSqlDatabase db = this->openDatabase();

        QSqlQuery fetch_cours("select *"
                              "from Cours where valide=1 "
                              "and titre not in  "
                              "(select titrecours from Liste_principale "
                              "where pseudoetudiant=?);", db);
        fetch_cours.addBindValue(pseudo);
        if(!fetch_cours.exec()){
            qDebug()<<fetch_cours.lastError();
        }

        while(fetch_cours.next()){

            QString titre= fetch_cours.value("titre").toString();
            QDate datedebut = fetch_cours.value("datedebut").toDate();
            QDate datefin = fetch_cours.value("datefin").toDate();
            QDate datedebutIncsription = fetch_cours.value("datedebutInscription").toDate();
            QDate datefinIncsription = fetch_cours.value("datefinInscription").toDate();
            int nbMax = fetch_cours.value("nbMaxEtudiant").toInt();

            //qCritical() << fetch_cours.value("pseudoEnseignantcreateur").toString();
            QString commentaire = fetch_cours.value("commentaire").toString();
            QString pseudo = fetch_cours.value("pseudoEnseignantcreateur").toString();
            bool valide = fetch_cours.value("valide").toBool();

            Cours *c = new Cours( titre,
                                  datedebut, datefin,
                                  datedebutIncsription, datefinIncsription,
                                  nbMax, commentaire,
                                  valide,pseudo);
            result.push_back(*c);
        }

        db.close();
        return result;
    }

    QVector<Cours> Systeme::afficherMescoursproposes(QString pseudo){
        QVector<Cours> result;
        QSqlDatabase db = this->openDatabase();

        QSqlQuery fetch_cours("select *"
                              "from Cours where valide=0 "
                              "and pseudoEnseignantcreateur=:pseudo;", db);
        fetch_cours.addBindValue(pseudo);
        if(!fetch_cours.exec()){
            qDebug()<<fetch_cours.lastError();
        }

        while(fetch_cours.next()){

            QString titre= fetch_cours.value("titre").toString();
            QDate datedebut = fetch_cours.value("datedebut").toDate();
            QDate datefin = fetch_cours.value("datefin").toDate();
            QDate datedebutIncsription = fetch_cours.value("datedebutInscription").toDate();
            QDate datefinIncsription = fetch_cours.value("datefinInscription").toDate();
            int nbMax = fetch_cours.value("nbMaxEtudiant").toInt();

            qCritical() << fetch_cours.value("pseudoEnseignantcreateur").toString();
            QString commentaire = fetch_cours.value("commentaire").toString();
            QString pseudo = fetch_cours.value("pseudoEnseignantcreateur").toString();
            bool valide = fetch_cours.value("valide").toBool();

            Cours *c = new Cours( titre,
                                  datedebut, datefin,
                                  datedebutIncsription, datefinIncsription,
                                  nbMax, commentaire,
                                  valide,pseudo);
            result.push_back(*c);
        }

        db.close();
        return result;
    }

    QVector<Cours> Systeme::afficherlescoursvalidesCoteEnseignant(QString pseudo){
        QVector<Cours> result;
        QSqlDatabase db = this->openDatabase();

        QSqlQuery fetch_cours("select *"
                              "from Cours where valide=1 "
                              "and pseudoEnseignantcreateur=?;", db);
        fetch_cours.bindValue(0,pseudo);
        if(!fetch_cours.exec()){
            qDebug()<<fetch_cours.lastError();
        }

        while(fetch_cours.next()){

            QString titre= fetch_cours.value("titre").toString();
            QDate datedebut = fetch_cours.value("datedebut").toDate();
            QDate datefin = fetch_cours.value("datefin").toDate();
            QDate datedebutIncsription = fetch_cours.value("datedebutInscription").toDate();
            QDate datefinIncsription = fetch_cours.value("datefinInscription").toDate();
            int nbMax = fetch_cours.value("nbMaxEtudiant").toInt();

            //qCritical() << fetch_cours.value("pseudoEnseignantcreateur").toString();
            QString commentaire = fetch_cours.value("commentaire").toString();
            QString pseudo = fetch_cours.value("pseudoEnseignantcreateur").toString();
            bool valide = fetch_cours.value("valide").toBool();

            Cours *c = new Cours( titre,
                                  datedebut, datefin,
                                  datedebutIncsription, datefinIncsription,
                                  nbMax, commentaire,
                                  valide,pseudo);
            result.push_back(*c);
        }

        db.close();
        return result;
    }

