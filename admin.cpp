#include "admin.h"
#include "ui_admin.h"
#include <QWidget>

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this->parent(), Database::database());

    myDelegate = new Delegate(this);

    QRegularExpression expression("[a-zA-Z ]+");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(expression,this);

    ui->admin_newSouvName->setValidator(validator);

    // set window title
    this->setWindowTitle("NFL Tour Administration");

    // set window icon
    this->setWindowIcon(QIcon("Pics/NFLicon.png"));

    ui->admin_searchBar->setStyleSheet("border-radius: 8px;background: lightgray;");

    //hide the table
    ui->admin_tableview->hide();

    //hide commit button
    ui->admin_commitChanges->hide();

    //hide search
    ui->admin_labelSearch->hide();
    ui->admin_searchBar->hide();

    //hide souvenir delete button
    ui->admin_deleteSouvenir->hide();

    //hide souvenir add button
    ui->admin_addSouvenir->hide();

    //hide add souvenir frame
    ui->admin_addSouvFrame->hide();
}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_back_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void admin::on_admin_showNFLSouvenirs_clicked()
{
    currentTable = "NFLSouvenirs";

    ui->admin_addSouvFrame->hide();

    //Show Table elements
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();
    ui->admin_labelSearch->show();
    ui->admin_searchBar->show();
    ui->admin_deleteSouvenir->show();
    ui->admin_addSouvenir->show();

    model->clear();
    model->setTable("NFLSouvenirs");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void admin::on_admin_showNFLInfo_clicked()
{
    currentTable = "NFLInformation";

    ui->admin_deleteSouvenir->hide();
    ui->admin_addSouvenir->hide();
    ui->admin_addSouvFrame->hide();

    //Show Table elements
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();
    ui->admin_labelSearch->show();
    ui->admin_searchBar->show();

    model->clear();
    model->setTable("NFLInformation");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();


    const QModelIndex index = model->index(0, 0);
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void admin::on_admin_showNFLDistances_clicked()
{
    currentTable = "NFLDistances";

    ui->admin_deleteSouvenir->hide();
    ui->admin_addSouvenir->hide();
    ui->admin_addSouvFrame->hide();

    //Show Table elements
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();
    ui->admin_labelSearch->show();
    ui->admin_searchBar->show();

    model->clear();
    model->setTable("NFLDistances");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void admin::on_admin_commitChanges_clicked()
{
    QString tmpStyleSheet = this->styleSheet(); //copy style sheet of admin window
    QMessageBox updateMsg;

    //Customize the QMessageBox
    updateMsg.setText("Are you sure you want to commit changes to the database?");
    updateMsg.setInformativeText("All changes are final.");
    updateMsg.setWindowTitle("Commit Changes");
    updateMsg.setIcon(QMessageBox::Question);
    updateMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    updateMsg.button(QMessageBox::Yes)->setStyleSheet("width: 50px; background: rgba(150,163,220,0.8);");
    updateMsg.button(QMessageBox::No)->setStyleSheet("width: 50px; background: darkgray;");
    updateMsg.setStyleSheet(tmpStyleSheet);

    int decision = updateMsg.exec();

    if(decision == QMessageBox::Yes)
    {
        model->submitAll(); //onManualSubmit edit strategy (Updates the database with changes)
        qDebug() <<"Changes made to the database.";
    }
    else
    {
        qDebug() << "No changes made to the database.";
    }
}

void admin::on_admin_searchBar_textEdited(const QString &arg1)
{
    if(currentTable == "NFLInformation")
    {
        //Filter all columns in NFLInformation table
        model->setFilter("LOWER(TeamName) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(StadiumName) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(SeatingCapacity) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Location) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Conference) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(SurfaceType) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(StadiumRoofType) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(StarPlayer) LIKE '%"+arg1.toLower()+"%'");
    }
    else if(currentTable == "NFLDistances")
    {
        //Filter all columns in NFLDistances table
        model->setFilter("LOWER(Beginning) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Ending) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Distance) LIKE '%"+arg1.toLower()+"%'");
    }
    else //if(currentTable == "NFLSouvenirs")
    {
        //Filter all columns in NFLSouvenirs table
        model->setFilter("LOWER(Stadium) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Name) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Price) LIKE '%"+arg1.toLower()+"%'");
    }
}


void admin::on_admin_tableview_clicked(const QModelIndex &index)
{
    souvSelectionRow = index.row();
}

void admin::on_admin_deleteSouvenir_clicked()
{
    QString tmpStyleSheet = this->styleSheet(); //copy style sheet of admin window
    QMessageBox updateMsg;

    //Customize the QMessageBox
    updateMsg.setText("Are you sure you want to delete the currently selected souvenir?");
    updateMsg.setInformativeText("Clicking 'Yes' will mark the selected souvenir for deletion. A souvenir pending removal is indicated by a '!' on the leftmost side of the row. Use the 'Commit Change(s)' button finalize a deletion");
    updateMsg.setWindowTitle("Confirm Deletion");
    updateMsg.setIcon(QMessageBox::Question);
    updateMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    updateMsg.button(QMessageBox::Yes)->setStyleSheet("width: 50px; background: rgba(150,163,220,0.8);");
    updateMsg.button(QMessageBox::No)->setStyleSheet("width: 50px; background: darkgray;");
    updateMsg.setStyleSheet(tmpStyleSheet);

    int decision = updateMsg.exec();

    if(decision == QMessageBox::Yes)
    {
        model->removeRow(souvSelectionRow);
        qDebug() <<"Souvenir deleted.";
    }
    else
    {
        qDebug() << "Souvenir not deleted.";
    }
}

void admin::on_admin_addSouvenir_clicked()
{
    //show add souvenir frame
    ui->admin_addSouvFrame->show();
}

void admin::on_admin_newSouvName_textEdited(const QString &arg1)
{
    newSouvName = arg1;
}

void admin::on_admin_addSouvenirFinal_clicked()
{
    QString stadium = ui->admin_addSouvCombo->currentText();
    QString newSouvPrice = "$"+QString::number(ui->admin_newSouvPrice->value());

    QSqlQuery *query = new QSqlQuery(Database::database());
    query->prepare("INSERT INTO NFLSouvenirs (Stadium,Name,Price) VALUES (:stadium, :name, :price)");
    query->bindValue(":stadium", stadium);
    query->bindValue(":name", newSouvName);
    query->bindValue(":price", newSouvPrice);

    if(query->exec())
    {
        QString tmpStyleSheet = this->styleSheet(); //copy style sheet of admin window
        QMessageBox souvAdded;

        //Customize the QMessageBox
        souvAdded.setText("Souvenir has been successfully added to the database.");
        souvAdded.setInformativeText("Click Ok to close this window");
        souvAdded.setWindowTitle("Add Souvenir Status");
        souvAdded.setIcon(QMessageBox::Information);
        souvAdded.setStandardButtons(QMessageBox::Ok);
        souvAdded.button(QMessageBox::Ok)->setStyleSheet("width: 50px; background: darkgray;");
        souvAdded.setStyleSheet(tmpStyleSheet);

        souvAdded.exec();
    }
    else
    {
        QString tmpStyleSheet = this->styleSheet(); //copy style sheet of admin window
        QMessageBox souvNotAdded;

        //Customize the QMessageBox
        souvNotAdded.setText("Souvenir has NOT been successfully added to the database.");
        souvNotAdded.setInformativeText("Click Ok to close this window");
        souvNotAdded.setWindowTitle("Add Souvenir Status");
        souvNotAdded.setIcon(QMessageBox::Information);
        souvNotAdded.setStandardButtons(QMessageBox::Ok);
        souvNotAdded.button(QMessageBox::Ok)->setStyleSheet("width: 50px; background: darkgray;");
        souvNotAdded.setStyleSheet(tmpStyleSheet);

        souvNotAdded.exec();
    }

    ui->admin_addSouvCombo->setCurrentIndex(0);
    ui->admin_newSouvName->clear();
    ui->admin_newSouvPrice->clear();
    ui->admin_addSouvFrame->hide();

    model->setSort(0,Qt::AscendingOrder);
    model->select();
}
