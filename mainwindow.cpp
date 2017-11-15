#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Tour");

    // remove ugly ass toolbar
    this->removeToolBar(this->ui->mainToolBar);

    // Team Info table setup
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->table->setColumnCount(8);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Stadium Name" << "Seating Capacity" << "Location"
                         << "Conference" << "Surface Type" << "Roof Type" << "Start Player";

    ui->table->setHorizontalHeaderLabels(teamInfoTableHeaders);

    ui->comboBox_nflType->addItem("All NFL Teams");
    ui->comboBox_nflType->addItem("AFC");
    ui->comboBox_nflType->addItem("NFC");

    ui->comboBox_nflType->hide();
    ui->lineEdit_searchNflTeams->hide();

    // hide table
    ui->table->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayTable(QSqlQuery query) {

    // loop through every record in the query
    while(query.next()) {
        QTableWidgetItem *teamName = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *stadiumName = new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *seatingCap = new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *location = new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *conference = new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *surfaceType = new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *roofType = new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *starPlayer = new QTableWidgetItem(query.value(7).toString());

        // center items
        teamName->setTextAlignment(Qt::AlignCenter);
        stadiumName->setTextAlignment(Qt::AlignCenter);
        seatingCap->setTextAlignment(Qt::AlignCenter);
        location->setTextAlignment(Qt::AlignCenter);
        conference->setTextAlignment(Qt::AlignCenter);
        surfaceType ->setTextAlignment(Qt::AlignCenter);
        roofType->setTextAlignment(Qt::AlignCenter);
        starPlayer ->setTextAlignment(Qt::AlignCenter);

        // insert new row
        ui->table->insertRow(ui->table->rowCount());

        // insert items
        ui->table->setItem(ui->table->rowCount() - 1, 0, teamName);
        ui->table->setItem(ui->table->rowCount() - 1, 1, stadiumName);
        ui->table->setItem(ui->table->rowCount() - 1, 2, seatingCap);
        ui->table->setItem(ui->table->rowCount() - 1, 3, location);
        ui->table->setItem(ui->table->rowCount() - 1, 4, conference);
        ui->table->setItem(ui->table->rowCount() - 1, 5, surfaceType);
        ui->table->setItem(ui->table->rowCount() - 1, 6, roofType);
        ui->table->setItem(ui->table->rowCount() - 1, 7, starPlayer);
    }
}

void MainWindow::on_lineEdit_searchNflTeams_textEdited(const QString &arg1)
{
    QSqlQuery query = Database::getInstance()->getSearchTeam(arg1);
    ui->table->setRowCount(0);
    displayTable(query);
}

void MainWindow::on_comboBox_nflType_currentIndexChanged(int index)
{
    // clear rows
    ui->table->setRowCount(0);
    QSqlQuery query = Database::getInstance()->getTeamTypes(index);
    displayTable(query);
}

void MainWindow::on_teamInformation_pushButton_clicked()
{
    ui->comboBox_nflType->show();
    ui->lineEdit_searchNflTeams->show();
    ui->table->show();
}

void MainWindow::on_pushButton_admin_clicked()
{   
    AdminLogin *adminLoginPage = new AdminLogin();
    adminLoginPage->show();
    this->close();
}
