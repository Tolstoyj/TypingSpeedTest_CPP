#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QUrl>
#include <QDir>
#include <QStandardPaths>
#include <QTimer>
#include <QRandomGenerator>

class SoundManager : public QObject
{
    Q_OBJECT

public:
    enum SoundType {
        KEYSTROKE_CORRECT,
        KEYSTROKE_INCORRECT,
        TEST_START,
        TEST_COMPLETE,
        LEVEL_UP,
        ACHIEVEMENT,
        TICK,
        WARNING
    };

    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager();
    
    // Sound control
    void playSound(SoundType type);
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setVolume(qreal volume); // 0.0 to 1.0
    qreal getVolume() const;
    
    // Keyboard sound simulation
    void setKeystrokeSoundsEnabled(bool enabled);
    bool areKeystrokeSoundsEnabled() const;
    void playKeystrokeSound(bool correct = true);
    
    // Generate sounds programmatically (if audio files not available)
    void generateBeep(int frequency, int duration);

private slots:
    void onSoundFinished();

private:
    void initializeSounds();
    void createProgrammaticSounds();
    QString getResourcePath();
    
    QSoundEffect *correctKeystroke;
    QSoundEffect *incorrectKeystroke;
    QSoundEffect *testStart;
    QSoundEffect *testComplete;
    QSoundEffect *levelUp;
    QSoundEffect *achievement;
    QSoundEffect *tick;
    QSoundEffect *warning;
    
    bool soundEnabled;
    bool keystrokeSoundsEnabled;
    qreal currentVolume;
    
    // For programmatic sound generation
    QTimer *beepTimer;
    int beepFrequency;
    int beepDuration;
};

#endif // SOUNDMANAGER_H