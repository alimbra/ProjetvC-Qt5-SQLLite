#ifndef AJOUTERUTILISATEURDIALOG_H
#define AJOUTERUTILISATEURDIALOG_H

#include <QWidget>
#include <QDialog>


namespace Ui {
class ui_ajouterutilisateurdialog;
}
/*!
 * @brief La Ajouterutilisateurdialog herite de QDialog
 * qui va nous permettre d implementer les fonctions lie a l interface
 * d´ajout d un utilisateur
 * @see QDialog
 *
 */

class Ajouterutilisateurdialog:public QDialog
{
    Q_OBJECT
public:
    /*!
     * @brief le constructeur explicit Ajouterutilisateurdialog
     * @param parent QWidget
     *
     */
    explicit Ajouterutilisateurdialog(QWidget *parent);
    /*!
     * @brief le destructeur Ajouterutilisateurdialog
     *
     */

    ~Ajouterutilisateurdialog();
private slots:

    /*!
     * @brief pour valider l ajout d un utilisateur
     *
     */

    void on_b_valider_accepted();
private:
    /*!
     * @brief l interface lie a la classe
     */

Ui::ui_ajouterutilisateurdialog *ui;
};

#endif // AJOUTERUTILISATEURDIALOG_H
