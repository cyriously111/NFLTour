#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <locale>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Tour");

    // remove ugly ass toolbar
    this->removeToolBar(this->ui->mainToolBar);

    // table setup
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->table_souvenirs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_souvenirs->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // hide team info stuff
    ui->comboBox_nflType->hide();
    ui->lineEdit_searchNflTeams->hide();

    // hide stadium stuff
    ui->openStadiums_pushButton->hide();
    ui->SeatingCapacity_pushButton->hide();
    ui->allStadiums_pushButton->hide();

    // hide table
    ui->table->hide();

    ui->comboBox_nflType->addItem("All NFL Teams");
    ui->comboBox_nflType->addItem("AFC");
    ui->comboBox_nflType->addItem("NFC");

    ui->comboBox_sort->addItem("");
    ui->comboBox_sort->addItem("Team Name");
    ui->comboBox_sort->addItem("Stadium Name");
    ui->comboBox_sort->addItem("Seating Capacity");
    ui->comboBox_sort->addItem("Location");
    ui->comboBox_sort->addItem("Conference");
    ui->comboBox_sort->addItem("Surface Type");
    ui->comboBox_sort->addItem("Roof Type");
    ui->comboBox_sort->addItem("Star Player");

    // hide the sorting stuff
    ui->comboBox_sort->hide();
    ui->label->hide();

    // hide players pictures
    ui->label_3->hide();

    //hide the souvenirs table
    ui->table_souvenirs->hide();
    ui->pushButton_souvenirs->hide();

    //hide tour Button
    ui->pushButton_tour->hide();

    ui->table_souvenirs->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayTeamInfo(QSqlQuery query) {
    ui->table->setRowCount(0);

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
    displayTeamInfo(query);
}

void MainWindow::on_comboBox_nflType_currentIndexChanged(int index)
{
    // clear rows
    ui->table->setRowCount(0);
    QSqlQuery query = Database::getInstance()->getTeamTypes(index);
    displayTeamInfo(query);
}

void MainWindow::on_teamInformation_pushButton_clicked()
{
    // hide the sorting stuff
    ui->comboBox_sort->show();
    ui->label->show();

    //show the souvenirs push button
    ui->pushButton_souvenirs->show();

    //hide tour Button
    ui->pushButton_tour->hide();

    // hide players pictures
    ui->label_3->hide();

    // hide stadium stuff
    ui->openStadiums_pushButton->hide();
    ui->SeatingCapacity_pushButton->hide();
    ui->allStadiums_pushButton->hide();

    // table headers
    ui->table->setColumnCount(8);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Stadium Name" << "Seating Capacity" << "Location"
                         << "Conference" << "Surface Type" << "Roof Type" << "Star Player";

    ui->table->setHorizontalHeaderLabels(teamInfoTableHeaders);

    ui->comboBox_nflType->show();
    ui->lineEdit_searchNflTeams->show();

    QSqlQuery query = Database::getInstance()->getTeamInfo();
    displayTeamInfo(query);
    ui->table->show();
}

void MainWindow::on_pushButton_admin_clicked()
{   
    AdminLogin *adminLoginPage = new AdminLogin();
    adminLoginPage->show();
    this->close();
}

void MainWindow::on_starPlayers_pushButton_clicked()
{
    //hide the souvenirs table
    ui->table_souvenirs->hide();
    ui->pushButton_souvenirs->hide();

    //hide tour Button
    ui->pushButton_tour->hide();

    // show the players picture
    ui->label_3->show();
    ui->label_3->setStyleSheet("border-image:url('Pics/MWBadass.jpg') 0 0 0 0 stretch stretch; "
                               "background-position: center; background-repeat: no-repeat;");

    // hide the sorting stuff
    ui->comboBox_sort->hide();
    ui->label->hide();

    // hide team info stuff
    ui->comboBox_nflType->hide();
    ui->lineEdit_searchNflTeams->hide();

    // hide stadium stuff
    ui->openStadiums_pushButton->hide();
    ui->SeatingCapacity_pushButton->hide();
    ui->allStadiums_pushButton->hide();

    // clear rows
    ui->table->setRowCount(0);
    QSqlQuery query = Database::getInstance()->getTeamInfo();

    // Team Info table setup
    ui->table->setColumnCount(2);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Star Player";
    ui->table->setHorizontalHeaderLabels(teamInfoTableHeaders);

    // loop through every record in the query
    while(query.next()) {
        QTableWidgetItem *teamName = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *starPlayer = new QTableWidgetItem(query.value(7).toString());

        // center items
        teamName->setTextAlignment(Qt::AlignCenter);
        starPlayer ->setTextAlignment(Qt::AlignCenter);

        // insert new row
        ui->table->insertRow(ui->table->rowCount());

        // insert items
        ui->table->setItem(ui->table->rowCount() - 1, 0, teamName);
        ui->table->setItem(ui->table->rowCount() - 1, 1, starPlayer);
    }

    ui->table->show();
}

void MainWindow::on_stadiums_pushButton_clicked()
{
    //hide the souvenirs table
    ui->table_souvenirs->hide();
    ui->pushButton_souvenirs->hide();

    //hide tour Button
    ui->pushButton_tour->hide();

    // hide the sorting stuff
    ui->comboBox_sort->hide();
    ui->label->hide();

    // show the stadium picture
    ui->label_3->show();
    ui->label_3->setStyleSheet("border-image:url('Pics/stadiums.jpg') 0 0 0 0 stretch stretch; "
                               "background-position: center; background-repeat: no-repeat;");

    // hide team info stuff
    ui->comboBox_nflType->hide();
    ui->lineEdit_searchNflTeams->hide();

    // show stadium stuff
    ui->openStadiums_pushButton->show();
    ui->SeatingCapacity_pushButton->show();
    ui->allStadiums_pushButton->show();

    // clear rows
    ui->table->setRowCount(0);
    QSqlQuery query = Database::getInstance()->getAllStadiums();

    // Team Info table setup
    ui->table->setColumnCount(2);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Stadium Name";
    ui->table->setHorizontalHeaderLabels(teamInfoTableHeaders);

    // loop through every record in the query
    while(query.next()) {
        QTableWidgetItem *teamName = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *stadiumName = new QTableWidgetItem(query.value(1).toString());

        // center items
        teamName->setTextAlignment(Qt::AlignCenter);
        stadiumName->setTextAlignment(Qt::AlignCenter);

        // insert new row
        ui->table->insertRow(ui->table->rowCount());

        // insert items
        ui->table->setItem(ui->table->rowCount() - 1, 0, teamName);
        ui->table->setItem(ui->table->rowCount() - 1, 1, stadiumName);
    }

    ui->table->show();
}

void MainWindow::displayOpenStadiums() {
    // hide team info stuff
    ui->comboBox_nflType->hide();
    ui->lineEdit_searchNflTeams->hide();

    // show stadium stuff
    ui->openStadiums_pushButton->show();
    ui->SeatingCapacity_pushButton->show();
    ui->allStadiums_pushButton->show();

    // clear rows
    ui->table->setRowCount(0);
    QSqlQuery query = Database::getInstance()->getOpenStadiums();

    // Team Info table setup
    ui->table->setColumnCount(2);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Stadium Name";
    ui->table->setHorizontalHeaderLabels(teamInfoTableHeaders);

    int counter = 0;

    // loop through every record in the query
    while(query.next()) {
        counter++;
        QTableWidgetItem *teamName = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *stadiumName = new QTableWidgetItem(query.value(1).toString());

        // center items
        teamName->setTextAlignment(Qt::AlignCenter);
        stadiumName->setTextAlignment(Qt::AlignCenter);

        // insert new row
        ui->table->insertRow(ui->table->rowCount());

        // insert items
        ui->table->setItem(ui->table->rowCount() - 1, 0, teamName);
        ui->table->setItem(ui->table->rowCount() - 1, 1, stadiumName);
    }

    // display open roof count
    ui->table->insertRow(ui->table->rowCount());
    ui->table->insertRow(ui->table->rowCount());

    QTableWidgetItem *countStr = new QTableWidgetItem("Count");
    QTableWidgetItem *countInt = new QTableWidgetItem(QString::number(counter));

    countStr->setTextAlignment(Qt::AlignRight);
    countInt->setTextAlignment(Qt::AlignLeft);

    QFont font;
    font.setBold(true);
    countStr->setFont(font);
    countInt->setFont(font);

    ui->table->setItem(ui->table->rowCount()-1, 0, countStr);
    ui->table->setItem(ui->table->rowCount()-1, 1, countInt);

    ui->table->show();
}

void MainWindow::displayStadiumSeatingCapacities() {
    // hide team info stuff
    ui->comboBox_nflType->hide();
    ui->lineEdit_searchNflTeams->hide();

    // show stadium stuff
    ui->openStadiums_pushButton->show();
    ui->SeatingCapacity_pushButton->show();
    ui->allStadiums_pushButton->show();

    // clear rows
    ui->table->setRowCount(0);
    QSqlQuery query = Database::getInstance()->getStadiumsBySeatingCapacity();

    // Team Info table setup
    ui->table->setColumnCount(3);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Stadium Name" << "Seating Capacity";
    ui->table->setHorizontalHeaderLabels(teamInfoTableHeaders);

    int totalCapacity = 0;
    QLocale english(QLocale::English);
    // loop through every record in the query
    while(query.next()) {

        totalCapacity += english.toDouble(query.value(2).toString());

        QTableWidgetItem *teamName = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *stadiumName = new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *seatingCap = new QTableWidgetItem(query.value(2).toString());

        // center items
        teamName->setTextAlignment(Qt::AlignCenter);
        stadiumName->setTextAlignment(Qt::AlignCenter);
        seatingCap->setTextAlignment(Qt::AlignCenter);

        // insert new row
        ui->table->insertRow(ui->table->rowCount());

        // insert items
        ui->table->setItem(ui->table->rowCount() - 1, 0, teamName);
        ui->table->setItem(ui->table->rowCount() - 1, 1, stadiumName);
        ui->table->setItem(ui->table->rowCount() - 1, 2, seatingCap);
    }

    // display open roof count
    ui->table->insertRow(ui->table->rowCount());
    ui->table->insertRow(ui->table->rowCount());

    QTableWidgetItem *countStr = new QTableWidgetItem("Total Seating Capacity");
    QTableWidgetItem *countInt = new QTableWidgetItem(english.toString(totalCapacity));

    countStr->setTextAlignment(Qt::AlignRight);
    countInt->setTextAlignment(Qt::AlignCenter);

    QFont font;
    font.setBold(true);
    countStr->setFont(font);
    countInt->setFont(font);

    ui->table->setItem(ui->table->rowCount()-1, 1, countStr);
    ui->table->setItem(ui->table->rowCount()-1, 2, countInt);

    ui->table->show();
}

void MainWindow::on_openStadiums_pushButton_clicked()
{
    displayOpenStadiums();
}

void MainWindow::on_allStadiums_pushButton_clicked()
{
    on_stadiums_pushButton_clicked();
}

void MainWindow::on_SeatingCapacity_pushButton_clicked()
{
    displayStadiumSeatingCapacities();
}

void MainWindow::on_comboBox_sort_currentIndexChanged(int index)
{
    QSqlQuery query = Database::getInstance()->sortTable(index);
    displayTeamInfo(query);
    ui->table->show();
}


void MainWindow::on_pushButton_souvenirs_clicked()
{
    QModelIndex current = ui->table->currentIndex();

    if(!current.isValid()) {
        QMessageBox::warning(this, "Error", "Select A College from the table!");
    } else {

        //show the souvenirs table
        ui->table_souvenirs->show();

        QSqlQuery query = Database::getInstance()->getSouvenirs(ui->table->item(current.row(),1)->text());

        // clear rows
        ui->table_souvenirs->setRowCount(0);

        // Team Info table setup
        ui->table_souvenirs->setColumnCount(3);
        QStringList teamInfoTableHeaders;
        teamInfoTableHeaders << "Stadium Name" << "Souvenir Name" << "Price";
        ui->table_souvenirs->setHorizontalHeaderLabels(teamInfoTableHeaders);

        // loop through every record in the query
        while(query.next()) {

            QTableWidgetItem *stadiumName = new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *souvnirName = new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *souvenirPrice = new QTableWidgetItem(QString::number(query.value(2).toDouble(),'f',2));

            // center items
            stadiumName->setTextAlignment(Qt::AlignCenter);
            souvnirName->setTextAlignment(Qt::AlignCenter);
            souvenirPrice->setTextAlignment(Qt::AlignCenter);

            // insert new row
            ui->table_souvenirs->insertRow(ui->table_souvenirs->rowCount());

            // insert items
            ui->table_souvenirs->setItem(ui->table_souvenirs->rowCount() - 1, 0, stadiumName);
            ui->table_souvenirs->setItem(ui->table_souvenirs->rowCount() - 1, 1, souvnirName);
            ui->table_souvenirs->setItem(ui->table_souvenirs->rowCount() - 1, 2, souvenirPrice);
        }

        //show tour Button
        ui->pushButton_tour->show();
    }
}
