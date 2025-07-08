#ifndef TYPINGTEST_H
#define TYPINGTEST_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QStringList>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include "lessonmanager.h"

class TypingTest : public QObject
{
    Q_OBJECT

public:
    enum DifficultyLevel {
        EASY,
        MEDIUM,
        HARD
    };
    
    enum TestMode {
        STANDARD_TEST,
        LESSON_MODE
    };
    
    explicit TypingTest(QObject *parent = nullptr);
    
    void startTest();
    void resetTest();
    QString getSampleText() const;
    
    void setDifficulty(DifficultyLevel level);
    DifficultyLevel getDifficulty() const;
    void setTestDuration(int seconds);
    int getTestDuration() const;
    void setTestMode(TestMode mode);
    TestMode getTestMode() const;
    void setLessonType(LessonManager::LessonType type);
    void setLessonLevel(int level);
    
    double getWPM() const;
    double getAccuracy() const;
    int getElapsedTime() const;
    int getProgress() const;
    bool isTestComplete() const;
    int getCorrectCharacters() const;
    int getTotalCharacters() const;

public slots:
    void onTextChanged(const QString &text);

signals:
    void statsUpdated();
    void testCompleted();

private slots:
    void updateTimer();

private:
    void generateSampleText();
    void calculateStats();
    QString getRandomSentence();
    void initializeDifficultyTexts();
    
    QTimer *timer;
    QElapsedTimer elapsedTimer;
    
    QString sampleText;
    QString currentInput;
    
    int correctCharacters;
    int totalCharacters;
    int wordsTyped;
    bool testActive;
    bool testComplete;
    
    double currentWPM;
    double currentAccuracy;
    int currentTime;
    
    DifficultyLevel currentDifficulty;
    QStringList easySentences;
    QStringList mediumSentences;
    QStringList hardSentences;
    
    int testDuration; // Test duration in seconds
    TestMode currentTestMode;
    LessonManager::LessonType currentLessonType;
    int currentLessonLevel;
    LessonManager *lessonManager;
    
    static const int WORDS_PER_MINUTE_DIVISOR = 5; // Average word length
};

#endif // TYPINGTEST_H