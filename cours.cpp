#include<cours.h>

Cours::Cours(){

}

Cours::Cours(QString titre,
      QDate datedebut,QDate datefin,
      QDate datedebutInscription,QDate datefinInscription,
      int nbmaxEtudiant,QString commentaire,
      bool valide,QString pseudo){

    this->titre=titre;
    this->datedebut=datedebut;
    this->datefin=datefin;
    this->datedebutInscription=datedebutInscription;
    this->datefinInscription=datefinInscription;
    this->nbmaxEtudiant=nbmaxEtudiant;
    this->valide=valide;
    this->commentaire=commentaire;
    this->pseudo=pseudo;
}

void Cours::setValide(bool valide){
    this->valide=valide;
}

void Cours::setTitre(QString titre){
    this->titre=titre;
}
QString Cours::getTitre(){
    return this->titre;
}

QDate Cours::getDateDebut(){
    return this->datedebut;
}

QDate Cours::getDatefin(){
    return this->datefin;
}

QDate Cours::getDateDebutInscription(){
    return this->datedebutInscription;
}
QDate Cours::getDatefinInscription(){
    return this->datefinInscription;
}
QVector<Utilisateur> Cours::getListeprincipale(){
    return this->listeprincipale;
}
QVector<Utilisateur> Cours::getListeAttente(){
    return this->listeAttente;
}
int Cours::getnbmaxEtudiant(){
    return this->nbmaxEtudiant;
}

QString Cours::getCommentaire(){
    return this->commentaire;
}

bool Cours::getValide(){
    return this->valide;
}
QString Cours::getPseudo(){
    return this->pseudo;
}
