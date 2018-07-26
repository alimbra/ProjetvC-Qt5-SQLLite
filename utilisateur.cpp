#include "utilisateur.h"



Utilisateur::Utilisateur(){

}

Utilisateur::Utilisateur(QString username, QString nom,
                         QString prenom,QString statut,
                         QString adresse,QString email,
                         QString telephone,QString motdepasse){
    this->username=username;
    this->nom=nom;
    this->prenom=prenom;
    this->statut=statut;
    this->adresse=adresse;
    this->email=email;
    this->telephone=telephone;
    this->motdepasse=motdepasse;
}

QString Utilisateur::getUsername(){
    return this->username;
}


QString Utilisateur::getNom(){
    return this->nom;
}

QString Utilisateur::getPrenom(){
    return this->prenom;
}

QString Utilisateur::getStatut(){
    return this->statut;
}

QString Utilisateur::getAdresse(){
    return this->adresse;
}

QString Utilisateur::getEmail(){
    return this->email;
}

QString Utilisateur::getTelephone(){
    return this->telephone;
}
QString Utilisateur::getMotDepasse(){
    return this->motdepasse;
}


