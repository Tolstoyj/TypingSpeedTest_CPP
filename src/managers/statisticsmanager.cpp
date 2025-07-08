#include "statisticsmanager.h"

StatisticsManager::StatisticsManager(QObject *parent)
    : QObject(parent)
{
    databasePath = getDatabasePath();
}

StatisticsManager::~StatisticsManager()
{
    if (database.isOpen()) {
        database.close();
    }
}

QString StatisticsManager::getDatabasePath()
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath(dataPath);
    }
    return dir.filePath("typing_stats.db");
}

bool StatisticsManager::initializeDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databasePath);
    
    if (!database.open()) {
        qDebug() << "Error opening database:" << database.lastError().text();
        return false;
    }
    
    return createTables();
}

bool StatisticsManager::createTables()
{
    QSqlQuery query(database);
    
    // Create users table
    QString createUsersTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            created_date DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createUsersTable)) {
        qDebug() << "Error creating users table:" << query.lastError().text();
        return false;
    }
    
    // Create test_results table
    QString createResultsTable = R"(
        CREATE TABLE IF NOT EXISTS test_results (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
            difficulty INTEGER NOT NULL,
            wpm REAL NOT NULL,
            accuracy REAL NOT NULL,
            time_spent INTEGER NOT NULL,
            correct_characters INTEGER NOT NULL,
            total_characters INTEGER NOT NULL,
            FOREIGN KEY (username) REFERENCES users(username)
        )
    )";
    
    if (!query.exec(createResultsTable)) {
        qDebug() << "Error creating test_results table:" << query.lastError().text();
        return false;
    }
    
    // Create indexes for better performance
    query.exec("CREATE INDEX IF NOT EXISTS idx_username ON test_results(username)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_timestamp ON test_results(timestamp)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_difficulty ON test_results(difficulty)");
    
    return true;
}

bool StatisticsManager::createUser(const QString &username)
{
    if (username.isEmpty() || userExists(username)) {
        return false;
    }
    
    QSqlQuery query(database);
    query.prepare("INSERT INTO users (username) VALUES (?)");
    query.addBindValue(username);
    
    if (!query.exec()) {
        qDebug() << "Error creating user:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QStringList StatisticsManager::getAllUsers()
{
    QStringList users;
    QSqlQuery query(database);
    
    if (query.exec("SELECT username FROM users ORDER BY username")) {
        while (query.next()) {
            users << query.value(0).toString();
        }
    }
    
    return users;
}

bool StatisticsManager::userExists(const QString &username)
{
    QSqlQuery query(database);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    return false;
}

bool StatisticsManager::saveTestResult(const TestResult &result)
{
    if (result.username.isEmpty()) {
        return false;
    }
    
    // Ensure user exists
    if (!userExists(result.username)) {
        createUser(result.username);
    }
    
    QSqlQuery query(database);
    query.prepare(R"(
        INSERT INTO test_results 
        (username, difficulty, wpm, accuracy, time_spent, correct_characters, total_characters)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    )");
    
    query.addBindValue(result.username);
    query.addBindValue(result.difficulty);
    query.addBindValue(result.wpm);
    query.addBindValue(result.accuracy);
    query.addBindValue(result.timeSpent);
    query.addBindValue(result.correctCharacters);
    query.addBindValue(result.totalCharacters);
    
    if (!query.exec()) {
        qDebug() << "Error saving test result:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<TestResult> StatisticsManager::getTestHistory(const QString &username, int limit)
{
    QList<TestResult> results;
    QSqlQuery query(database);
    
    query.prepare(R"(
        SELECT id, username, timestamp, difficulty, wpm, accuracy, 
               time_spent, correct_characters, total_characters
        FROM test_results 
        WHERE username = ? 
        ORDER BY timestamp DESC 
        LIMIT ?
    )");
    
    query.addBindValue(username);
    query.addBindValue(limit);
    
    if (query.exec()) {
        while (query.next()) {
            TestResult result;
            result.id = query.value(0).toInt();
            result.username = query.value(1).toString();
            result.timestamp = query.value(2).toDateTime();
            result.difficulty = query.value(3).toInt();
            result.wpm = query.value(4).toDouble();
            result.accuracy = query.value(5).toDouble();
            result.timeSpent = query.value(6).toInt();
            result.correctCharacters = query.value(7).toInt();
            result.totalCharacters = query.value(8).toInt();
            
            results << result;
        }
    }
    
    return results;
}

QList<TestResult> StatisticsManager::getTestHistoryByDifficulty(const QString &username, int difficulty, int limit)
{
    QList<TestResult> results;
    QSqlQuery query(database);
    
    query.prepare(R"(
        SELECT id, username, timestamp, difficulty, wpm, accuracy, 
               time_spent, correct_characters, total_characters
        FROM test_results 
        WHERE username = ? AND difficulty = ?
        ORDER BY timestamp DESC 
        LIMIT ?
    )");
    
    query.addBindValue(username);
    query.addBindValue(difficulty);
    query.addBindValue(limit);
    
    if (query.exec()) {
        while (query.next()) {
            TestResult result;
            result.id = query.value(0).toInt();
            result.username = query.value(1).toString();
            result.timestamp = query.value(2).toDateTime();
            result.difficulty = query.value(3).toInt();
            result.wpm = query.value(4).toDouble();
            result.accuracy = query.value(5).toDouble();
            result.timeSpent = query.value(6).toInt();
            result.correctCharacters = query.value(7).toInt();
            result.totalCharacters = query.value(8).toInt();
            
            results << result;
        }
    }
    
    return results;
}

UserStats StatisticsManager::getUserStats(const QString &username)
{
    UserStats stats;
    stats.username = username;
    
    QSqlQuery query(database);
    query.prepare(R"(
        SELECT 
            COUNT(*) as total_tests,
            AVG(wpm) as avg_wpm,
            MAX(wpm) as best_wpm,
            AVG(accuracy) as avg_accuracy,
            MAX(accuracy) as best_accuracy,
            SUM(time_spent) as total_time,
            MAX(timestamp) as last_test
        FROM test_results 
        WHERE username = ?
    )");
    
    query.addBindValue(username);
    
    if (query.exec() && query.next()) {
        stats.totalTests = query.value(0).toInt();
        stats.averageWpm = query.value(1).toDouble();
        stats.bestWpm = query.value(2).toDouble();
        stats.averageAccuracy = query.value(3).toDouble();
        stats.bestAccuracy = query.value(4).toDouble();
        stats.totalTimeSpent = query.value(5).toInt();
        stats.lastTestDate = query.value(6).toDateTime();
    }
    
    return stats;
}

QList<TestResult> StatisticsManager::getPersonalBests(const QString &username)
{
    QList<TestResult> results;
    QSqlQuery query(database);
    
    // Get best WPM for each difficulty
    query.prepare(R"(
        SELECT id, username, timestamp, difficulty, wpm, accuracy, 
               time_spent, correct_characters, total_characters
        FROM test_results r1
        WHERE username = ? AND wpm = (
            SELECT MAX(wpm) 
            FROM test_results r2 
            WHERE r2.username = r1.username AND r2.difficulty = r1.difficulty
        )
        GROUP BY difficulty
        ORDER BY difficulty
    )");
    
    query.addBindValue(username);
    
    if (query.exec()) {
        while (query.next()) {
            TestResult result;
            result.id = query.value(0).toInt();
            result.username = query.value(1).toString();
            result.timestamp = query.value(2).toDateTime();
            result.difficulty = query.value(3).toInt();
            result.wpm = query.value(4).toDouble();
            result.accuracy = query.value(5).toDouble();
            result.timeSpent = query.value(6).toInt();
            result.correctCharacters = query.value(7).toInt();
            result.totalCharacters = query.value(8).toInt();
            
            results << result;
        }
    }
    
    return results;
}

QList<TestResult> StatisticsManager::getRecentTests(const QString &username, int days)
{
    QList<TestResult> results;
    QSqlQuery query(database);
    
    query.prepare(R"(
        SELECT id, username, timestamp, difficulty, wpm, accuracy, 
               time_spent, correct_characters, total_characters
        FROM test_results 
        WHERE username = ? AND timestamp >= datetime('now', '-' || ? || ' days')
        ORDER BY timestamp DESC
    )");
    
    query.addBindValue(username);
    query.addBindValue(days);
    
    if (query.exec()) {
        while (query.next()) {
            TestResult result;
            result.id = query.value(0).toInt();
            result.username = query.value(1).toString();
            result.timestamp = query.value(2).toDateTime();
            result.difficulty = query.value(3).toInt();
            result.wpm = query.value(4).toDouble();
            result.accuracy = query.value(5).toDouble();
            result.timeSpent = query.value(6).toInt();
            result.correctCharacters = query.value(7).toInt();
            result.totalCharacters = query.value(8).toInt();
            
            results << result;
        }
    }
    
    return results;
}

bool StatisticsManager::clearUserData(const QString &username)
{
    QSqlQuery query(database);
    
    // Delete test results
    query.prepare("DELETE FROM test_results WHERE username = ?");
    query.addBindValue(username);
    
    if (!query.exec()) {
        qDebug() << "Error clearing test results:" << query.lastError().text();
        return false;
    }
    
    // Delete user
    query.prepare("DELETE FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (!query.exec()) {
        qDebug() << "Error deleting user:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool StatisticsManager::clearAllData()
{
    QSqlQuery query(database);
    
    if (!query.exec("DELETE FROM test_results")) {
        qDebug() << "Error clearing test results:" << query.lastError().text();
        return false;
    }
    
    if (!query.exec("DELETE FROM users")) {
        qDebug() << "Error clearing users:" << query.lastError().text();
        return false;
    }
    
    return true;
}