#include <ressource.h>



Ressource::Ressource(){

}


QString Ressource::getNom(){
    return this->nom;
}

QString Ressource::getType(){
    return this->type;
}

Cours Ressource::getCours(){
    return this->cours;
}
