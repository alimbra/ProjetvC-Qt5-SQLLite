#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}
using namespace std;

/*!
 * @brief La MainWindow herite de QMainWindow
 * qui va nous permettre d implementer les fonctions lie a l interface
 * principale
 * @see QDialog
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * @brief le constructeur explicit MainWindow
     * @param parent QWidget
     *
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /*!
     * @brief modifie la visibilites des composants de l interface
     * selon le profil de l utilisateur
     *
     */
    void estConnecte();
private slots:
    /*!
     * @brief afficher le formulaire de connexion
     * en appuyant sur le bouton se connecter de l ui
     */
    void on_b_seconnecter_clicked();

    /*!
     * @brief afficher le formulaire d ajout d un utilisateur
     * en appuyant sur le bouton ajouter utilisateur de l ui
     */
    void on_b_ajouterutilisateur_clicked();

    /*!
     * @brief afficher la liste des utilisateurs dans un tableau
     * en appuyant sur le bouton b_utilisateurs de l ui
     */
    void on_b_utilisateurs_clicked();
    /*!
     * @brief afficher le formulaire d ajout d un cours
     * en appuyant sur le bouton proposer cours de l ui
     */
    void on_b_proposercours_clicked();

    /*!
     * @brief afficher la liste des cours proposes dans un tableau
     * en appuyant sur le bouton b_coursproposes de l ui
     */
    void on_b_coursproposes_clicked();

    /*!
     * @brief vider le tableau de l ui
     *
     */
    void viderTable();

    /*!
     * @brief rajouter le head dans le tableau de l ui
     * qui correspond a celui des utilisateurs
     */
    void setTvForUtilisateur();

    /*!
     * @brief rajouter le head dans le tableau de l ui
     * qui correspond a celui des  cours
     */
    void setTvForCours();
    /*!
     * @brief setter: met a jour  le pseudo de l utilisateur connecte
     *@param pseudo pseudo de l utilisateur connecte
     */
    void setPseudo(QString pseudo);

    /*!
     * @brief en appuyant sur le tableau on peut effectuer
     * plusieurs operations ( accepter/refuser un propos de cours)
     * (modifier supprimer un utilisateur)
     * selon le contenu du tableau
     *@param row ligne du tableau
     * @param column colonne du tableau
     */
    void on_tableWidget_cellDoubleClicked(int row, int column);

    /*!
     * @brief afficher la liste des cours valide dans un tableau
     * en appuyant sur le bouton enseignantcoursvalides de l ui
     */
    void on_enseignantcoursvalides_clicked();

    /*!
     * @brief afficher la liste des cours proposes de l enseignant dans un tableau
     * en appuyant sur le bouton mescoursproposes de l ui
     */
    void on_mescoursproposes_clicked();

    /*!
     * @brief afficher la liste des cours valide dans un tableau
     * en appuyant sur le bouton enseignantcoursvalides de l ui
     */
    QString getTypeUtilisateur();

    /*!
     * setter
     * @brief met ajour le statut de l´utilisiteur
     * @param typeUtilisateur de type QString
     */
    void setTypeUtilisateur(QString typeUtilisateur);

    /*!
     * @brief quitter l application en appuyant sur le bouton
     *  quitter de l application
     *
     */
    void on_quitter_clicked();

    /*!
     * @brief se deconnecter l application en appuyant sur le bouton
     * se deconnecter de l application
     *
     */
    void on_sedeconnecter_clicked();

private:
    Ui::MainWindow *ui;
    QString pseudo;
    QString typeUtilisateur;
};

#endif // MAINWINDOW_H
