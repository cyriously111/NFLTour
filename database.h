#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QSqlField>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <vector>
#include <QString>

/** Database
 * - Singleton
 * - Inherits from QSqlDatabase
 */
class Database: public QSqlDatabase
{
public:
    static Database* getInstance();

    /**
     * @brief getTeamInfo
     * @return query of all items in TeamInfo table
     */
    QSqlQuery getTeamInfo();

private:
    // private constructor
    Database();

    // instance of Database
    // created once on startup
    static Database* instance;
};

#endif // DATABASE_H