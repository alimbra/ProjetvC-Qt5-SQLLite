#ifndef UTILISATEUR_H
#define UTILISATEUR_H


#include <QString>

class Utilisateur
{
public:
    Utilisateur();
    Utilisateur(QString username, QString nom,
                QString prenom,QString statut,
                QString adresse,QString email,
                QString telephone,QString motdepasse);

    QString getUsername();
    QString getNom();
    QString getPrenom();
    QString getStatut();
    QString getAdresse();
    QString getEmail();
    QString getTelephone();
    QString getMotDepasse();

private:
    QString username;
    QString nom;
    QString prenom;
    QString statut;
    QString adresse;
    QString email;
    QString telephone;
    QString motdepasse;

};

#endif // UTILISATEUR_H
