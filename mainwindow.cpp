#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"connection.h"
#include<QMessageBox>
#include<QDebug>
#include"QDate"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->login->show();
    ui->choix->hide();
    ui->employes->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
    /***************************CONNEXION BDD**************************/
    Connection c;
    if (c.createconnect())
    {

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("connection failed.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    /***************************CONROLE DE SAISIE**************************/
    //EMPLOYES
    QRegularExpression rx("^[A-Za-z]+$");

    QValidator *validator1 = new QRegularExpressionValidator(rx, this);
    ui->nom->setValidator(validator1);
    ui->prenom->setValidator(validator1);
    ui->nom_2->setValidator(validator1);
    ui->prenom_2->setValidator(validator1);

    QRegularExpression rx2("^[0-9]+$");
    QValidator *validator2 = new QRegularExpressionValidator(rx2, this);
    ui->salaire->setValidator(validator2);
    ui->salaire_2->setValidator(validator2);
    //FORMATEUR
    ui->nomForm->setValidator(validator1);
    ui->nomForm_2->setValidator(validator1);
    ui->PrenomForm->setValidator(validator1);
    ui->PrenomForm_2->setValidator(validator1);
    ui->SalairForm->setValidator(validator2);
    ui->SalairForm_2->setValidator(validator2);
    /***************************AFFICHAGE**************************/
    //EMPLOYES
    employes = new QSqlQueryModel();
    ui->tableView->setModel(employes);
    e.afficher(employes);
    e.trie(employes , "id");
    //FORMATEUR
    formateur = new QSqlQueryModel();
    ui->tableView_2->setModel(formateur);

    etat_mdp = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete employes ;
}

//EMPLOYES
void MainWindow::on_connecter_clicked()
{
    int id = ui->id_login->text().toInt();
    QString mdp = ui->mdp_login->text() ;
    if(e.login(id , mdp) == true)
    {
        ui->login->hide();
        ui->choix->show();
        ui->employes->hide();
        ui->ajouteremploye->hide();
        ui->modifieremploye->hide();
        ui->supprimer->hide();
        ui->groupBox->hide();
        ui->statEmpl->hide();
        ui->AjouterFormateur->hide();
        ui->ModfierForm->hide();
        ui->SupprimerForm->hide();
        ui->formateurs->hide();
        ui->statform_2->hide();
        ui->groupBox_3->hide();
        qDebug () << "id"<<e.id;
        f.afficher(formateur , e);
        f.trie(formateur , "id");

    }
}
void MainWindow::on_employes_choix_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->show();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->show();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->employes->hide();
    ui->statEmpl->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_addemployee_clicked()
{
    Employees e ;
    e.id = ui->identifiant->text();
    e.nom = ui->nom->text();
    e.prenom = ui->prenom->text();
    e.mdp = ui->motdepasse->text();
    e.salaire = ui->salaire->text().toInt();
    e.ROLE = ui->comboBox->currentText();
    if(e.id == "" || e.nom == "" || e.prenom == "" || e.mdp == "" || e.ROLE == "" )
    {
        QMessageBox::critical(nullptr, QObject::tr("AJOUT FAILED"),
                                    QObject::tr("Veuiller Remplir tous les champs.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if(e.existe())
    {
        QMessageBox::critical(nullptr, QObject::tr("AJOUT FAILED"),
                                    QObject::tr("Employes existe deja!!.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        if(!e.ajout())
        {
            QMessageBox::critical(nullptr, QObject::tr("AJOUT FAILED"),
                                        QObject::tr("PROBLEME.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            e.afficher(employes);
            ui->login->hide();
            ui->choix->hide();
            ui->ajouteremploye->hide();
            ui->modifieremploye->hide();
            ui->supprimer->hide();
            ui->groupBox->hide();
            ui->statEmpl->hide();
            ui->employes->show();
            ui->AjouterFormateur->hide();
            ui->ModfierForm->hide();
            ui->SupprimerForm->hide();
            ui->formateurs->hide();
            ui->statform_2->hide();
    ui->groupBox_3->hide();
        }
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    empl.id = employes->index(index.row() , 0).data().toString();
    empl.mdp = employes->index(index.row() , 6).data().toString();
    empl.nom = employes->index(index.row() , 1).data().toString();
    empl.prenom = employes->index(index.row() , 2).data().toString();
    empl.ROLE = employes->index(index.row() , 4).data().toString();
    empl.mail = employes->index(index.row() , 3).data().toString();
    empl.salaire = employes->index(index.row() , 5).data().toInt();
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->statEmpl->hide();
    ui->groupBox->show();
    ui->employes->show();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_supprimer_2_clicked()
{
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->show();
    ui->groupBox->hide();
    ui->employes->hide();
    ui->statEmpl->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_no_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->show();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_yes_clicked()
{
    if(empl.supprimer())
    {
        e.afficher(employes);
        ui->login->hide();
        ui->choix->hide();
        ui->ajouteremploye->hide();
        ui->modifieremploye->hide();
        ui->supprimer->hide();
        ui->groupBox->hide();
        ui->statEmpl->hide();
        ui->employes->show();
        ui->AjouterFormateur->hide();
        ui->ModfierForm->hide();
        ui->SupprimerForm->hide();
        ui->formateurs->hide();
        ui->statform_2->hide();
    ui->groupBox_3->hide();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("SUPPRETION FAILED"),
                                    QObject::tr("PROBLEME.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_2_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->show();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->employes->hide();
    ui->statEmpl->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
    ui->nom_2->setText(empl.nom);
    ui->prenom_2->setText(empl.prenom);
    ui->salaire_2->setText(QString :: number( empl.salaire));
    ui->role2->setCurrentText(empl.ROLE);
    ui->identifiant_2->setText(empl.id);
    ui->motdepasse_2->setText(empl.mdp);


}

void MainWindow::on_modifier_clicked()
{
    empl.nom = ui->nom_2->text();
    empl.prenom = ui->prenom_2->text();
    empl.mdp = ui->motdepasse_2->text();
    empl.salaire = ui->salaire_2->text().toInt();
    empl.ROLE = ui->role2->currentText();
    if( empl.nom == "" || empl.prenom == "" || empl.mdp == "" || empl.ROLE == "" )
    {
        QMessageBox::critical(nullptr, QObject::tr("MODIFIER FAILED"),
                                    QObject::tr("Veiller Remplir tous les champs.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if(!empl.modifier())
    {
        QMessageBox::critical(nullptr, QObject::tr("MODIFIER FAILED"),
                                    QObject::tr("PROBLEME.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        e.afficher(employes);
        ui->login->hide();
        ui->choix->hide();
        ui->ajouteremploye->hide();
        ui->modifieremploye->hide();
        ui->supprimer->hide();
        ui->groupBox->hide();
        ui->statEmpl->hide();
        ui->employes->show();
        ui->AjouterFormateur->hide();
        ui->ModfierForm->hide();
        ui->SupprimerForm->hide();
        ui->formateurs->hide();
        ui->statform_2->hide();
    ui->groupBox_3->hide();
    }
}

void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    e.recherche(employes , ui->critere->currentText() , arg1);
}

void MainWindow::on_annuler_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->show();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();

}

void MainWindow::on_annuler_2_clicked()
{
    ui->login->hide();
    ui->choix->show();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->employes->hide();
    ui->statEmpl->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_annuler_3_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->show();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}
void MainWindow::on_critere_currentTextChanged(const QString &arg1)
{
    e.trie(employes , arg1);
}

void MainWindow::on_statistique_empl_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->show();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
    QList<QWidget*> childWidgets = ui->label_8->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();
        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->label_8->clear();
        ui->label_8->hide();

    float s0, s1, s2;
    s0 = e.countType("admin");
    s1 = e.countType("RH");
    s2 = e.countType("agent");
    qDebug () << s0 ;
    float stat = s0 + s1 + s2  ;
    float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
    float y = (stat != 0) ? (s1 * 100) / stat : 0.0;
    float z = (stat != 0) ? (s2 * 100) / stat : 0.0;

    QString ch1 = QString("admin %1%").arg(x);
    QString ch2 = QString("RH %1%").arg(y);
    QString ch3 = QString("agent %1%").arg(z);

    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);



    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor(Qt::white));
    slice->setBrush(QColor(189, 76, 224, 1));
    QPieSlice *slice1= series->append(ch2,y);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor(Qt::white));
    slice1->setBrush(QColor(84, 16, 149, 1));
    QPieSlice *slice2= series->append(ch3,z);
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
        slice2->setBrush(QColor(Qt::green));


        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        QBrush backgroundBrush(QColor(187,93,87,0));
        chart->setBackgroundBrush(backgroundBrush);
        QChartView *chartview=new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setFixedSize(ui->label_8->size());
        chartview->setParent(ui->label_8);
        ui->label_8->setStyleSheet("background:transparent; color:white; ");
        ui->label_8->show();
}

void MainWindow::on_pdf_empl_clicked()
{
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());

        if (model) {
            QString content;
            QString logoPath = "C:\\Users\\Lenovo\\Desktop\\qt\\projet2";
            int logoWidth = 100;
            int logoHeight = 100;

            // Insérer le logo avec styles CSS pour la taille et la position
            content += "<div style=\"position:absolute; top:0; left:0;\">"; // Position en haut à gauche
            content += "<img src=\"" + QUrl::toPercentEncoding(logoPath) + "\" width=\"" + QString::number(logoWidth) + "\" height=\"" + QString::number(logoHeight) + "\">";
            content += "</div><br><br>";

            // Titre du document
            content += "<h1>Liste des Employes</h1>";

            // Début du tableau avec styles CSS
            content += "<style>"
                       "table { border-collapse: collapse; width: 100%; }"
                       "th, td { border: 1px solid black; padding: 8px; text-align: center; }"
                       "th { background-color: lightgray; }" // Couleur de fond pour les en-têtes de colonne
                       "</style>";
            content += "<table>";

            // Ajouter les en-têtes de colonne
            content += "<tr>";
            for (int col = 0; col < model->columnCount(); ++col) {
                content += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
            }
            content += "</tr>";

            // Ajouter les données du tableau
            for (int row = 0; row < model->rowCount(); ++row) {
                content += "<tr>";
                for (int col = 0; col < model->columnCount(); ++col) {
                    content += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
                }
                content += "</tr>";
            }

            // Fin du tableau
            content += "</table>";

            // Créer un objet QTextDocument et définir son contenu en utilisant le code HTML
            QTextDocument document;
            document.setHtml(content);

            // Créer un dialogue pour sélectionner l'emplacement de sauvegarde du PDF
            QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "employes", "Fichiers PDF (*.pdf)");

            if (!fileName.isEmpty())
            {
                // Créer un objet QPrinter pour générer le PDF
                QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(fileName);

                // Imprimer le document sur le PDF
                document.print(&printer);

                // Afficher un message à l'utilisateur pour confirmer l'exportation réussie
                QMessageBox::information(this, "Export PDF", "Le PDF a été créé avec succès.");
            }
        }
}

void MainWindow::on_formateurs_choix_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->show();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_ajouterformateur_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->show();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_retour_clicked()
{
    ui->login->hide();
    ui->choix->show();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}


void MainWindow::on_statform_clicked()
{

    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->show();
    ui->groupBox_3->hide();

    QList<QWidget*> childWidgets = ui->label_11->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();
        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->label_11->clear();
        ui->label_11->hide();

    float s0, s1, s2;
    s0 = f.countType("Marketing");
    s1 = f.countType("Soft skills");
    s2 = f.countType("Informatique");
    qDebug () << s0 ;
    float stat = s0 + s1 + s2  ;
    float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
    float y = (stat != 0) ? (s1 * 100) / stat : 0.0;
    float z = (stat != 0) ? (s2 * 100) / stat : 0.0;

    QString ch1 = QString("MARKETING %1%").arg(x);
    QString ch2 = QString("SOFT SKILLS %1%").arg(y);
    QString ch3 = QString("INFORMATIQUE %1%").arg(z);

    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);



    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor(Qt::white));
    slice->setBrush(QColor(189, 76, 224, 1));
    QPieSlice *slice1= series->append(ch2,y);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor(Qt::white));
    slice1->setBrush(QColor(84, 16, 149, 1));
    QPieSlice *slice2= series->append(ch3,z);
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
        slice2->setBrush(QColor(Qt::green));


        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        QBrush backgroundBrush(QColor(187,93,87,0));
        chart->setBackgroundBrush(backgroundBrush);
        QChartView *chartview=new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setFixedSize(ui->label_11->size());
        chartview->setParent(ui->label_11);
        ui->label_11->setStyleSheet("background:transparent; color:white; ");
        ui->label_11->show();
}

void MainWindow::on_annuler_5_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->show();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_annuler_4_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->show();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_retour_2_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->show();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();

}

void MainWindow::on_retour_3_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->show();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}
//FORMATEUR

void MainWindow::on_ajouterform_clicked()
{
    f.id = ui->idForm->text();
    f.nom = ui->nomForm->text();
    f.prenom = ui->PrenomForm->text();
    f.mail = ui->MailForm->text();
    f.domaine = ui->Domaine->currentText();
    f.salaire = ui->SalairForm->text().toInt();
    f.DATEDEBUT = ui->dateEdit->text();
    f.id_empl = e.id;
    if( f.id == "" || f.nom  == "" || f.prenom == "" || f.mail == ""|| f.domaine == "DOMAINE" || ui->SalairForm->text() == ""  )
    {
        QMessageBox::critical(nullptr, QObject::tr("MODIFIER FAILED"),
                                    QObject::tr("Veiller Remplir tous les champs.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if(f.existe())
    {
        QMessageBox::critical(nullptr, QObject::tr("AJOUT FAILED"),
                                    QObject::tr("Employes existe deja!!.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        if(!f.ajout())
        {
            QMessageBox::critical(nullptr, QObject::tr("AJOUT FAILED"),
                                        QObject::tr("PROBLEME.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            f.afficher(formateur , e);
            ui->login->hide();
            ui->choix->hide();
            ui->ajouteremploye->hide();
            ui->modifieremploye->hide();
            ui->supprimer->hide();
            ui->groupBox->hide();
            ui->statEmpl->hide();
            ui->employes->hide();
            ui->AjouterFormateur->hide();
            ui->ModfierForm->hide();
            ui->SupprimerForm->hide();
            ui->formateurs->show();
            ui->statform_2->hide();
            ui->groupBox_3->hide();
        }
    }





}

void MainWindow::on_pushButton_3_clicked()
{
    f.nom = ui->nomForm_2->text();
    f.prenom = ui->PrenomForm_2->text();
    f.mail = ui->MailForm_2->text();
    f.domaine = ui->Domaine_2->currentText();
    f.salaire = ui->SalairForm_2->text().toInt();
    f.DATEDEBUT = ui->dateEdit_2->text();
    f.id_empl = e.id;
    if(f.nom  == "" || f.prenom == "" || f.mail == ""|| f.domaine == "DOMAINE" || ui->SalairForm_2->text() == ""  )
    {
        QMessageBox::critical(nullptr, QObject::tr("MODIFIER FAILED"),
                                    QObject::tr("Veiller Remplir tous les champs.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if (!f.modifier())
    {
        QMessageBox::critical(nullptr, QObject::tr("MODIFICATION FAILED"),
                                    QObject::tr("PROBLEME.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        f.afficher(formateur , e);
        ui->login->hide();
        ui->choix->hide();
        ui->ajouteremploye->hide();
        ui->modifieremploye->hide();
        ui->supprimer->hide();
        ui->groupBox->hide();
        ui->statEmpl->hide();
        ui->employes->hide();
        ui->AjouterFormateur->hide();
        ui->ModfierForm->hide();
        ui->SupprimerForm->hide();
        ui->formateurs->show();
        ui->statform_2->hide();
        ui->groupBox_3->hide();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->show();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    f.id = formateur->index(index.row() , 0).data().toString();
    f.DATEDEBUT = formateur->index(index.row() , 6).data().toString();
    f.nom = formateur->index(index.row() , 1).data().toString();
    f.prenom = formateur->index(index.row() , 2).data().toString();
    f.domaine = formateur->index(index.row() , 4).data().toString();
    f.mail = formateur->index(index.row() , 3).data().toString();
    f.salaire = formateur->index(index.row() , 5).data().toInt();
    f.id_empl = formateur->index(index.row() , 7).data().toInt();
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->show();
    ui->statform_2->hide();
    ui->groupBox_3->show();
}

void MainWindow::on_modfier_clicked()
{
    ui->idForm_2->setText(f.id);
    ui->MailForm_2->setText(f.mail);
    ui->nomForm_2->setText(f.nom);
    ui->PrenomForm_2->setText(f.prenom);
    ui->SalairForm_2->setText(QString :: number(f.salaire));
    ui->Domaine_2->setCurrentText(f.domaine);
    ui->dateEdit_2->setDate(QDate::fromString(f.DATEDEBUT, "yyyy-MM-dd"));
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->show();
    ui->SupprimerForm->hide();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_supprimer_3_clicked()
{
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->show();
    ui->formateurs->hide();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_pushButton_clicked()
{
    if(!f.supprimer())
    {
        QMessageBox::critical(nullptr, QObject::tr("suppression FAILED"),
                                    QObject::tr("PROBLEME.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    f.afficher(formateur , e);
    ui->login->hide();
    ui->choix->hide();
    ui->ajouteremploye->hide();
    ui->modifieremploye->hide();
    ui->supprimer->hide();
    ui->groupBox->hide();
    ui->statEmpl->hide();
    ui->employes->hide();
    ui->AjouterFormateur->hide();
    ui->ModfierForm->hide();
    ui->SupprimerForm->hide();
    ui->formateurs->show();
    ui->statform_2->hide();
    ui->groupBox_3->hide();
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    f.trie(formateur , arg1);
}

void MainWindow::on_recherche_2_textChanged(const QString &arg1)
{
    f.recherche(formateur , ui->comboBox_2->currentText() , arg1);
}

void MainWindow::on_esportationpdf_clicked()
{
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_2->model());

        if (model) {
            QString content;
            QString logoPath = "C:\\Users\\Lenovo\\Desktop\\qt\\projet2";
            int logoWidth = 100;
            int logoHeight = 100;

            // Insérer le logo avec styles CSS pour la taille et la position
            content += "<div style=\"position:absolute; top:0; left:0;\">"; // Position en haut à gauche
            content += "<img src=\"" + QUrl::toPercentEncoding(logoPath) + "\" width=\"" + QString::number(logoWidth) + "\" height=\"" + QString::number(logoHeight) + "\">";
            content += "</div><br><br>";

            // Titre du document
            content += "<h1>Liste des Formateur</h1>";

            // Début du tableau avec styles CSS
            content += "<style>"
                       "table { border-collapse: collapse; width: 100%; }"
                       "th, td { border: 1px solid black; padding: 8px; text-align: center; }"
                       "th { background-color: lightgray; }" // Couleur de fond pour les en-têtes de colonne
                       "</style>";
            content += "<table>";

            // Ajouter les en-têtes de colonne
            content += "<tr>";
            for (int col = 0; col < model->columnCount(); ++col) {
                content += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
            }
            content += "</tr>";

            // Ajouter les données du tableau
            for (int row = 0; row < model->rowCount(); ++row) {
                content += "<tr>";
                for (int col = 0; col < model->columnCount(); ++col) {
                    content += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
                }
                content += "</tr>";
            }

            // Fin du tableau
            content += "</table>";

            // Créer un objet QTextDocument et définir son contenu en utilisant le code HTML
            QTextDocument document;
            document.setHtml(content);

            // Créer un dialogue pour sélectionner l'emplacement de sauvegarde du PDF
            QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "formateur", "Fichiers PDF (*.pdf)");

            if (!fileName.isEmpty())
            {
                // Créer un objet QPrinter pour générer le PDF
                QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(fileName);

                // Imprimer le document sur le PDF
                document.print(&printer);

                // Afficher un message à l'utilisateur pour confirmer l'exportation réussie
                QMessageBox::information(this, "Export PDF", "Le PDF a été créé avec succès.");
            }
        }
}

void MainWindow::on_pushButton_6_clicked()
{
    if(etat_mdp == 0)
    {
        etat_mdp = 1;
        ui->mdp_login->setEchoMode(QLineEdit::Password);
        //ui->pushButton_6->setIcon(":/new/prefix1/image/passwo.png");
    }
    else
    {
        etat_mdp = 0;
        ui->mdp_login->setEchoMode(QLineEdit::Normal);
        ui->pushButton_6->setStyleSheet("background-image: url(:/new/prefix1/image/passwo.png);");
    }
}
