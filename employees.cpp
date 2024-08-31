#include "employees.h"
#include<QMessageBox>
#include<QDebug>
Employees::Employees()
{

}
void Employees :: afficher(QSqlQueryModel *model)
{
    model->setQuery("SELECT * FROM EMPLOYE");
}
bool Employees :: login(int id , QString mdp)
{
    QSqlQuery query;
    query.prepare("SELECT * from EMPLOYE where :id=id and :mdp=mdp");
    query.bindValue(":id", id);
    query.bindValue(":mdp", mdp);
    if(query.exec() && query.next())
    {
        this->id =query.value(0).toString();
        nom = query.value(1).toString();
        prenom = query.value(2).toString();
        mail = query.value(3).toString();
        ROLE = query.value(4).toString();
        mdp = query.value(5).toString();
        qDebug() << this->id ;
        return true;
    }
    else
    {
        return  false;
    }
}
bool Employees :: existe()
{
    QSqlQuery query;
    query.prepare("SELECT * from EMPLOYE where :id=id");
    query.bindValue(":id", id);
    if(query.exec() && query.next())
    {
        return true;
    }
    else
    {
        return  false;
    }
}

bool Employees :: ajout()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (ID, NOM, PRENOM, MAIL, ROLE, SALAIRE, MDP) "
                  "VALUES (:ID, :NOM, :PRENOM, :MAIL, :ROLE, :SALAIRE, :MDP)");
    query.bindValue(":ID" , id);
    query.bindValue(":NOM" , nom);
    query.bindValue(":PRENOM" , prenom);
    query.bindValue(":MAIL" , mail);
    query.bindValue(":ROLE" , ROLE);
    query.bindValue(":SALAIRE" , salaire);
    query.bindValue(":MDP" , mdp);
    if(query.exec())
    {
        return true;
    }
    else
    {
        qDebug () << query.lastError() ;
        return false ;
    }
}
bool Employees :: supprimer()
{
    QSqlQuery query;
    query.prepare("Delete from EMPLOYE where :id = id");
    query.bindValue(":id" , id);
    if(query.exec())
    {
        return true;
    }
    else
    {
        qDebug () << query.lastError() ;
        return false ;
    }
}
bool Employees :: modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE set nom = :nom, prenom = :prenom, mail = :mail, role = :role, mdp = :mdp, salaire= :salaire WHERE id = :id");
    query.bindValue(":id" , id);
    query.bindValue(":nom" , nom);
    query.bindValue(":prenom" , prenom);
    query.bindValue(":mail" , mail);
    query.bindValue(":role" , ROLE);
    query.bindValue(":salaire" , salaire);
    query.bindValue(":mdp" , mdp);
    if(query.exec())
    {
        return true;
    }
    else
    {
        qDebug () << query.lastError() ;
        return false ;
    }
}
void Employees :: recherche(QSqlQueryModel *model , QString critere , QString ch)
{
    model->setQuery("SELECT * FROM employe WHERE " + critere + " LIKE '%" + ch + "%'");
}
void Employees :: trie (QSqlQueryModel *model , QString critere)
{
    model->setQuery("SELECT * from employe order by " +  critere +" ASC") ;
}
int Employees :: countType (QString ch)
{
    QSqlQueryModel* searchModel = new QSqlQueryModel();
    searchModel->setQuery("SELECT * FROM EMPLOYE WHERE role LIKE '%" + ch + "%'");
    return searchModel->rowCount() ;
}
