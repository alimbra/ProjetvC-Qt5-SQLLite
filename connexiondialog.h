#ifndef CONNEXIONDIALOG_H
#define CONNEXIONDIALOG_H

#include <QDialog>

namespace Ui {
    class Connexiondialog;
}
using namespace std;
/*!
 * @brief La Ajouterutilisateurdialog herite de QDialog
 * qui va nous permettre d implementer les fonctions lie a l interface
 * de connexion
 * @see QDialog
 *
 */
class Connexiondialog:public QDialog
{
    Q_OBJECT
public:
    /*!
     * @brief le constructeur explicit Ajouterutilisateurdialog
     * @param parent QWidget
     *
     */
    explicit Connexiondialog(QWidget *parent);
    /*!
     * @brief le destructeur Ajouterutilisateurdialog
     *
     */
    ~Connexiondialog();

    /*!
     * @brief setter: met a jour  le type de l utilisateur connecte
     * (Enseignant, Etudiant, Administrateur)
     *@param statut statut de l utilisateur connecte
     */
    void setStatut(QString statut);

    /*!
     *
     * @brief getter: retourn le statut de l utilisateur
     * connecte(Enseignant, Etudiant, Administrateur)
     * @return un QString
     */
    QString getStatut();

    /*!
     * @brief getter: retourn le pseudo l utilisateur
     * connecte
     * @return un QString
     */
    QString getPseudo();

    /*!
     * @brief setter: met a jour  le pseudo de l utilisateur connecte
     * (Enseignant, Etudiant, Administrateur)
     *
     */
    void setPseudo(QString pseudo);

private slots:

    /*!
     * @brief pour valider la connexion
     *
     *
     */
    void on_b_connecter_accepted();

    /*!
     * @brief pour annuler la connexion
     *
     *
     */

    void on_b_connecter_rejected();


private:
    Ui::Connexiondialog *ui;
    QString statut;
    QString pseudo;

};
#endif // CONNEXIONDIALOG_H
