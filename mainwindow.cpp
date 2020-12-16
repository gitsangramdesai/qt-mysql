#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void ShowMsg(QString strMsg)
{
    QMessageBox msgBox;
    msgBox.setText(strMsg);
    msgBox.exec();
}


void MainWindow::on_pbSubmit_clicked()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QMYSQL","MyConnect");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("sangram");
    db.setDatabaseName("sangram");

   QString name = ui->leName->text();
   QString  tel = ui->leTel->text();

    if (db.open()) {
        QMessageBox::information(this,"Connection","Connection Success");
        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare("INSERT INTO MyUser(shortName,tel)values(:shortName,:telephone)");
        query.bindValue(":shortName",name);
        query.bindValue(":telephone",tel);

         if(query.exec())
        {
                QMessageBox::information(this,"Insertion","Insertion Success");
        }else
        {
                QMessageBox::information(this,"Insertion","Insertion failed");
        }


    }else{
        QMessageBox::information(this,"Connection","Connection failed");
    }
}


