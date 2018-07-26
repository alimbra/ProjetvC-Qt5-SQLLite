#ifndef SYSTEME_H
#define SYSTEME_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QDebug>
#include <QDate>
#include <QDir>
#include <QString>

#include <iostream>
#include <string>
#include <sstream>

#include "utilisateur.h"
#include "cours.h"


#define DB_NAME "ApplicationcoursDB"
using namespace std;

/*!
 * @brief La classe Systeme est la classe
 * qui permet d'intéragir avec les données enregistrées dans la base de données.
 */
class Systeme
{
private:
    string db_path;
    QString typeUtilisateur;
    QString pseudo;

public:
    /*!
     * @brief Le constructeur de Systeme créé le dossier où sera stocké la base de données.
     * on cree aussi les tables necessaires a l iteration 1
     */
    Systeme();

    /*!
     * @brief Insère un utilisateur dans la base de données
     * @param pseudo de l utilisateur
     * @param nom de l utilisateur
     * @param adresse de l utilisateur
     * @param statut de l utilisateur
     * @param telephone de l utilisateur
     * @param email de l utilisateur
     * @param motdepasse de l utilisateur
     * @see Utilisateur
     */
    void ajouterutilisateur(QString username, QString nom,
                            QString prenom,QString statut,
                            QString adresse,QString email,
                            QString telephone,QString motdepasse);

    /*!
     * @brief modifier un utilisateur dans la base de données
     * @param pseudo de l utilisateur
     * @param nom de l utilisateur
     * @param adresse de l utilisateur
     * @param statut de l utilisateur
     * @param telephone de l utilisateur
     * @param email de l utilisateur
     * @param motdepasse de l utilisateur
     * @see Utilisateur
     */
    void modifierutilisateur(QString pseudoancien,QString username, QString nom,
                            QString prenom,QString statut,
                            QString adresse,QString email,
                            QString telephone,QString motdepasse);

    /*!
     * @brief supprime un utilisateur dans la base de données
     * @param pseudo de l utilisateur
     * @see Utilisateur
     */
    void supprimerutilisateur(QString pseudoancien);


    /*!
     * @brief etablit la connexion et recupere la base de donnees
     *
     *
     */
    QSqlDatabase openDatabase();
    /*!
     * @brief recupere tous les utilisateurs de la base de donnee
     * et le rajoute dans la liste des utilisateurs
     *
     *
     */
    QVector<Utilisateur> afficherlesutilisateurs();

    /*!
     * @brief recupere tous les cours proposes de la base de donnee
     * (qui ne sont pas encore valides)
     * et le rajoute dans la liste des cours
     * @return la liste des cours
     */
    QVector<Cours> afficherlescoursproposes();
    /*!
     * @brief supprime un cours de la base de donnees
     * @param nom du cours en QString
     */
    void supprimerCours(QString nomcours);
    /*!
     * @brief rajouter un cours dans la base de donnees
     * @param nomcours nom du cours en QString
     * @param datedebut date debut du cours en QDate
     * @param datefin en QDate
     * @param datedebutinscription en  QDate
     * @param datefininscription en QDate
     * @param nbMaxEtudiant en int
     * @param commentaire en QString
     * @param pseudoEnseignant en QString
     * @param valide en bool
     */
    void proposercours(QString nomcours,QDate datedebut,QDate datefin,
                QDate datedebutinscription,QDate datefininscription,
                int nbMaxEtudiant,QString commentaire,
                QString pseudoEnseignant,bool valide);

    /*!
     * @brief verifie si l enseignant existe dans la base de donnee
     * @param usermame pseudo de l utilisateur en QString
     * @return bool
     */
    bool verifier(QString username);

    /*!
     * @brief verifie si l enseignant existe dans la base de donnee
     * @param usermame pseudo de l utilisateur en QString
     * @param motdepasse mot de passe de l utilisateur en QString
     * @return bool
     */
    bool verifier(QString username,QString motdepasse);

    /*!
     *
     * @brief getter: retourn le type de l utilisateur connecte(Enseignant, Etudiant, Administrateur)
     * @return un QString
     */
    QString getTypeUtilisateur();

    /*!
     * @brief setter: met a jour  le type de l utilisateur connecte
     * (Enseignant, Etudiant, Administrateur)
     *@param typeUtilisateur type de l utilisateur
     */
    void setTypeUtilisateur(QString typeUtilisateur);
    /*!
     * @brief setter: met a jour  le pseudo de l utilisateur connecte
     * (Enseignant, Etudiant, Administrateur)
     *
     */
    void setPseudo(QString pseudo);

    /*!
     * @brief getter: retourn le pseudo l utilisateur connecte(Enseignant, Etudiant, Administrateur)
     * @return un QString
     */
    QString getPseudo();
    /*!
     * @brief modifie un cours dans la base de donnees en validant le cours
     * @param nomcours nom du cours en QString
     * @param datedebut date debut du cours en QDate
     * @param datefin en QDate
     * @param datedebutinscription en  QDate
     * @param datefininscription en QDate
     * @param nbMaxEtudiant en int
     * @param commentaire en QString
     * @param pseudoEnseignant en QString
     * @see Cours
     */
    void accepter_proposition(QString nomcours,
                              QDate datedebut,QDate datefin,
                              QDate datedebutinscription,QDate datefininscription,
                              int nbMaxEtudiant,QString commentaire,
                              QString pseudoEnseignant);
    /*!
     * @brief supprimer un cours dans la base de donnees
     * @param titre nom du cours en QString

     */
    void refuser_proposition(QString titre);

    /*!
     * @brief afficher lescours valides depuis la base de donnees
     * ou l etudiant n a pas encore fait d inscription
     * @param pseudo de l etudiant
     * @return liste des Cours
     * @attention a modifier la requete apres pour rajouter la liste d attente
     */
    QVector<Cours> afficherlescoursvalidesCoteEtudiant(QString pseudo);

    /*!
     * @brief afficher lescours valides
     * par l administrateur depuis la base de donnees
     * @param pseudo de l enseignant
     * @return liste des Cours
     *
     */
    QVector<Cours> afficherlescoursvalidesCoteEnseignant(QString pseudo);

    /*!
     * @brief afficher lescours proposes
     * par l enseignant depuis la base de donnees
     * @param pseudo de l enseignant
     * @return liste des Cours
     *
     */

    QVector<Cours> afficherMescoursproposes(QString pseudo);

};

#endif // SYSTEME_H
