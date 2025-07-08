#ifndef LESSONMANAGER_H
#define LESSONMANAGER_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include <QRandomGenerator>

class LessonManager : public QObject
{
    Q_OBJECT

public:
    enum LessonType {
        HOME_ROW,           // asdf jkl;
        TOP_ROW,            // qwerty uiop
        BOTTOM_ROW,         // zxcv bnm
        NUMBERS,            // 1234567890
        PUNCTUATION,        // .,;'[]
        COMMON_WORDS,       // the, and, for, etc.
        FINGER_SPECIFIC,    // exercises for specific fingers
        BIGRAMS,            // common letter pairs (th, er, in)
        TRIGRAMS,           // common 3-letter combinations (the, and, ing)
        PROGRAMMING         // programming-specific characters
    };

    explicit LessonManager(QObject *parent = nullptr);
    
    // Lesson management
    QString getLessonText(LessonType type, int length = 50);
    QString getLessonTitle(LessonType type);
    QString getLessonDescription(LessonType type);
    QList<LessonType> getAllLessonTypes();
    
    // Progressive difficulty
    QString getProgressiveLesson(LessonType type, int level); // level 1-5
    
    // Custom exercises
    QString generateCharacterDrill(const QString &characters, int length = 30);
    QString generateWordDrill(const QStringList &words, int count = 10);
    QString generateBigramDrill(const QStringList &bigrams, int length = 40);

private:
    void initializeLessons();
    QString generateRandomString(const QString &chars, int length);
    QString formatLesson(const QStringList &elements, int totalLength);
    
    QMap<LessonType, QStringList> lessonContent;
    QMap<LessonType, QString> lessonTitles;
    QMap<LessonType, QString> lessonDescriptions;
    
    // Character sets for different rows
    QString homeRowChars;
    QString topRowChars;
    QString bottomRowChars;
    QString numberChars;
    QString punctuationChars;
    QString programmingChars;
    
    // Common patterns
    QStringList commonWords;
    QStringList commonBigrams;
    QStringList commonTrigrams;
};

#endif // LESSONMANAGER_H