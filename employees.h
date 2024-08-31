#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#include"connection.h"
#include<QString>
class Employees
{
public:
    QString id;
    QString nom;
    QString prenom;
    QString mail;
    QString ROLE ;
    QString mdp ;
    int salaire;

public:
    Employees();

    void afficher(QSqlQueryModel *model);
    bool ajout();
    bool login(int id , QString mdp);
    bool existe();
    bool supprimer();
    bool modifier();
    void recherche(QSqlQueryModel *model , QString critere , QString ch);
    void trie (QSqlQueryModel *model , QString critere);
    int countType (QString ch);
};

#endif // EMPLOYEES_H
