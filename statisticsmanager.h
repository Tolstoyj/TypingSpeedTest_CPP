#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

struct TestResult {
    int id;
    QString username;
    QDateTime timestamp;
    int difficulty; // 0=Easy, 1=Medium, 2=Hard
    double wpm;
    double accuracy;
    int timeSpent;
    int correctCharacters;
    int totalCharacters;
    
    TestResult() : id(-1), difficulty(1), wpm(0.0), accuracy(0.0), 
                   timeSpent(0), correctCharacters(0), totalCharacters(0) {}
};

struct UserStats {
    QString username;
    int totalTests;
    double averageWpm;
    double bestWpm;
    double averageAccuracy;
    double bestAccuracy;
    int totalTimeSpent;
    QDateTime lastTestDate;
    
    UserStats() : totalTests(0), averageWpm(0.0), bestWpm(0.0), 
                  averageAccuracy(0.0), bestAccuracy(0.0), totalTimeSpent(0) {}
};

class StatisticsManager : public QObject
{
    Q_OBJECT

public:
    explicit StatisticsManager(QObject *parent = nullptr);
    ~StatisticsManager();
    
    bool initializeDatabase();
    
    // User management
    bool createUser(const QString &username);
    QStringList getAllUsers();
    bool userExists(const QString &username);
    
    // Test result management
    bool saveTestResult(const TestResult &result);
    QList<TestResult> getTestHistory(const QString &username, int limit = 50);
    QList<TestResult> getTestHistoryByDifficulty(const QString &username, int difficulty, int limit = 50);
    
    // Statistics
    UserStats getUserStats(const QString &username);
    QList<TestResult> getPersonalBests(const QString &username);
    QList<TestResult> getRecentTests(const QString &username, int days = 7);
    
    // Database maintenance
    bool clearUserData(const QString &username);
    bool clearAllData();

private:
    QSqlDatabase database;
    QString databasePath;
    
    bool createTables();
    QString getDatabasePath();
};

#endif // STATISTICSMANAGER_H