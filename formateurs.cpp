#include "formateurs.h"
#include<QMessageBox>
#include<QDebug>


Formateurs::Formateurs()
{

}
void Formateurs:: afficher(QSqlQueryModel *model , Employees e)
{
    if(e.ROLE == "agent")
    {
        model->setQuery("SELECT * FROM FORMATEUR WHERE id_empl = " + e.id);
    }
    else
    {
        model->setQuery("SELECT * FROM FORMATEUR");
    }
}
bool Formateurs :: ajout()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMATEUR (ID, ID_EMPL, PRENOM , NOM, MAIL, DOMAINE , SALAIRE , DATEDEBUT) "
                  "VALUES (:ID, :ID_EMPL, :PRENOM , :NOM, :MAIL, :DOMAINE , :SALAIRE , :DATE_DEBUT)");
    qDebug() << id_empl;
    query.bindValue(":ID" , id);
    query.bindValue(":ID_EMPL" , id_empl);
    query.bindValue(":NOM" , nom);
    query.bindValue(":PRENOM" , prenom);
    query.bindValue(":MAIL" , mail);
    query.bindValue(":DOMAINE" , domaine);
    query.bindValue(":SALAIRE" , salaire);
    query.bindValue(":DATE_DEBUT" , DATEDEBUT);
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
bool Formateurs :: existe()
{
    QSqlQuery query;
    query.prepare("SELECT * from FORMATEUR where :id=id");
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
bool Formateurs :: supprimer()
{
    QSqlQuery query;
    query.prepare("Delete from FORMATEUR where :id = id");
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
bool Formateurs :: modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE FORMATEUR set nom = :nom, prenom = :prenom, mail = :mail, domaine = :domaine, DATEDEBUT = :datedebut, salaire= :salaire WHERE id = :id");
    query.bindValue(":id" , id);
    query.bindValue(":nom" , nom);
    query.bindValue(":prenom" , prenom);
    query.bindValue(":mail" , mail);
    query.bindValue(":domaine" , domaine);
    query.bindValue(":salaire" , salaire);
    query.bindValue(":datedebut" , DATEDEBUT);
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
void Formateurs :: recherche(QSqlQueryModel *model , QString critere , QString ch)
{
    model->setQuery("SELECT * FROM FORMATEUR WHERE " + critere + " LIKE '%" + ch + "%'");
}
void Formateurs :: trie (QSqlQueryModel *model , QString critere)
{
    model->setQuery("SELECT * from FORMATEUR order by " +  critere +" ASC") ;
}
int Formateurs :: countType (QString ch)
{
    QSqlQueryModel* searchModel = new QSqlQueryModel();
    searchModel->setQuery("SELECT * FROM FORMATEUR WHERE domaine LIKE '%" + ch + "%'");
    return searchModel->rowCount() ;
}
