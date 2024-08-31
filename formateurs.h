#ifndef FORMATEURS_H
#define FORMATEURS_H
#include"connection.h"
#include<QString>
#include"employees.h"
class Formateurs
{
public:
    QString id;
    QString id_empl;
    QString nom;
    QString prenom;
    QString mail;
    QString domaine ;
    QString DATEDEBUT;
    int salaire;
public:
    Formateurs();
    void afficher(QSqlQueryModel *model , Employees e);
    bool ajout();
    bool existe();
    bool supprimer();
    bool modifier();
    void recherche(QSqlQueryModel *model , QString critere , QString ch);
    void trie (QSqlQueryModel *model , QString critere);
    int countType (QString ch);
};

#endif // FORMATEURS_H
