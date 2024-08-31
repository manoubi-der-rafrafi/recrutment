#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"connection.h"
#include"employees.h"

#include"formateurs.h"
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include <QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connecter_clicked();


    void on_employes_choix_clicked();

    void on_pushButton_4_clicked();

    void on_addemployee_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_supprimer_2_clicked();

    void on_no_clicked();

    void on_yes_clicked();

    void on_modifier_2_clicked();

    void on_modifier_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void on_annuler_clicked();

    void on_annuler_2_clicked();

    void on_annuler_3_clicked();

    void on_critere_currentTextChanged(const QString &arg1);

    void on_statistique_empl_clicked();

    void on_pdf_empl_clicked();

    void on_formateurs_choix_clicked();

    void on_ajouterformateur_clicked();

    void on_retour_clicked();

    void on_statform_clicked();

    void on_annuler_5_clicked();

    void on_annuler_4_clicked();

    void on_retour_2_clicked();

    void on_retour_3_clicked();

    void on_ajouterform_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_modfier_clicked();

    void on_supprimer_3_clicked();

    void on_pushButton_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_recherche_2_textChanged(const QString &arg1);

    void on_esportationpdf_clicked();

    void on_mdp_login_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *employes;
    QSqlQueryModel *formateur;
    Employees e;
    Employees empl;
    Formateurs f;
    int etat_mdp ;
};
#endif // MAINWINDOW_H
