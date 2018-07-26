#ifndef COURS_H
#define COURS_H

#include <QString>
#include <QDate>
#include <QVector>
#include <utilisateur.h>

class Cours{

public:
    Cours();
    Cours(QString titre,
          QDate datedebut,QDate datefin,
          QDate datedebutInscription,QDate datefinInscription,
          int nbmaxEtudiant,QString commentaire,
          bool valide,QString pseudo);
    QString getTitre();
    QDate getDateDebut();
    QDate getDatefin();
    QDate getDateDebutInscription();
    QDate getDatefinInscription();
    QString getPseudo();
    int getnbmaxEtudiant();
    QString getCommentaire();
    bool getValide();
    void setValide(bool valide);
    void setTitre(QString titre);
    void setPseudo(QString pseudo);

    QVector<Utilisateur> getListeprincipale();
    QVector<Utilisateur> getListeAttente();
private:
  QString titre;
  QDate datedebut;
  QDate datefin;
  QDate datedebutInscription;
  QDate datefinInscription;
  int nbmaxEtudiant;
  QString commentaire;
  bool valide;
  QString pseudo;

  QVector<Utilisateur> listeprincipale;
  QVector<Utilisateur> listeAttente;
};

#endif // COURS_H
