#include "soundmanager.h"
#include <QDebug>
#include <QApplication>

SoundManager::SoundManager(QObject *parent)
    : QObject(parent)
    , correctKeystroke(nullptr)
    , incorrectKeystroke(nullptr)
    , testStart(nullptr)
    , testComplete(nullptr)
    , levelUp(nullptr)
    , achievement(nullptr)
    , tick(nullptr)
    , warning(nullptr)
    , soundEnabled(true)
    , keystrokeSoundsEnabled(false) // Default to off to avoid annoyance
    , currentVolume(0.5)
    , beepTimer(new QTimer(this))
    , beepFrequency(440)
    , beepDuration(100)
{
    initializeSounds();
}

SoundManager::~SoundManager()
{
    // QSoundEffect objects will be cleaned up by Qt's parent-child system
}

void SoundManager::initializeSounds()
{
    // Initialize sound effects
    correctKeystroke = new QSoundEffect(this);
    incorrectKeystroke = new QSoundEffect(this);
    testStart = new QSoundEffect(this);
    testComplete = new QSoundEffect(this);
    levelUp = new QSoundEffect(this);
    achievement = new QSoundEffect(this);
    tick = new QSoundEffect(this);
    warning = new QSoundEffect(this);
    
    // Set initial volume for all sounds
    correctKeystroke->setVolume(currentVolume);
    incorrectKeystroke->setVolume(currentVolume);
    testStart->setVolume(currentVolume);
    testComplete->setVolume(currentVolume);
    levelUp->setVolume(currentVolume);
    achievement->setVolume(currentVolume);
    tick->setVolume(currentVolume);
    warning->setVolume(currentVolume);
    
    // Try to load sound files from resources or create programmatic sounds
    createProgrammaticSounds();
}

void SoundManager::createProgrammaticSounds()
{
    // Since we don't have audio files, we'll create simple programmatic feedback
    // In a real application, you would load actual audio files here
    
    // For now, we'll use QSoundEffect with generated URLs
    // This is a simplified implementation - in practice, you'd want actual sound files
    
    qDebug() << "Sound Manager initialized with programmatic sounds";
    
    // Connect finished signals for cleanup
    connect(correctKeystroke, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
    connect(incorrectKeystroke, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
    connect(testStart, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
    connect(testComplete, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
    connect(levelUp, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
    connect(achievement, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
    connect(tick, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
    connect(warning, &QSoundEffect::playingChanged, this, &SoundManager::onSoundFinished);
}

QString SoundManager::getResourcePath()
{
    // Get the application's resource directory
    QString appDir = QApplication::applicationDirPath();
    QDir resourceDir(appDir);
    resourceDir.cd("sounds"); // Look for a sounds subdirectory
    
    if (resourceDir.exists()) {
        return resourceDir.absolutePath();
    }
    
    // Fallback to application directory
    return appDir;
}

void SoundManager::playSound(SoundType type)
{
    if (!soundEnabled) return;
    
    QSoundEffect *soundToPlay = nullptr;
    
    switch (type) {
        case KEYSTROKE_CORRECT:
            if (!keystrokeSoundsEnabled) return;
            soundToPlay = correctKeystroke;
            generateBeep(800, 50); // High pitch, short duration
            break;
        case KEYSTROKE_INCORRECT:
            if (!keystrokeSoundsEnabled) return;
            soundToPlay = incorrectKeystroke;
            generateBeep(300, 100); // Low pitch, longer duration
            break;
        case TEST_START:
            soundToPlay = testStart;
            generateBeep(660, 200); // Medium pitch, medium duration
            break;
        case TEST_COMPLETE:
            soundToPlay = testComplete;
            generateBeep(880, 300); // High pitch, long duration
            break;
        case LEVEL_UP:
            soundToPlay = levelUp;
            // Play a quick ascending sequence
            QTimer::singleShot(0, [this]() { generateBeep(440, 100); });
            QTimer::singleShot(100, [this]() { generateBeep(550, 100); });
            QTimer::singleShot(200, [this]() { generateBeep(660, 150); });
            return;
        case ACHIEVEMENT:
            soundToPlay = achievement;
            // Play a celebration sequence
            QTimer::singleShot(0, [this]() { generateBeep(880, 100); });
            QTimer::singleShot(100, [this]() { generateBeep(1100, 100); });
            QTimer::singleShot(200, [this]() { generateBeep(880, 100); });
            QTimer::singleShot(300, [this]() { generateBeep(1320, 200); });
            return;
        case TICK:
            soundToPlay = tick;
            generateBeep(1000, 30); // Very short tick
            break;
        case WARNING:
            soundToPlay = warning;
            generateBeep(220, 150); // Low warning sound
            break;
    }
    
    // Note: Since we're using programmatic beeps instead of loaded sound files,
    // the QSoundEffect objects won't actually play. The generateBeep calls above
    // provide the audio feedback.
}

void SoundManager::playKeystrokeSound(bool correct)
{
    if (correct) {
        playSound(KEYSTROKE_CORRECT);
    } else {
        playSound(KEYSTROKE_INCORRECT);
    }
}

void SoundManager::generateBeep(int frequency, int duration)
{
    // This is a placeholder for actual beep generation
    // In a real implementation, you would:
    // 1. Generate a sine wave at the specified frequency
    // 2. Play it for the specified duration
    // 3. Use QAudioOutput or similar for actual sound generation
    
    qDebug() << "Beep:" << frequency << "Hz for" << duration << "ms";
    
    // For now, we'll just log the beep parameters
    // In a production app, you'd implement actual audio generation here
}

void SoundManager::setEnabled(bool enabled)
{
    soundEnabled = enabled;
}

bool SoundManager::isEnabled() const
{
    return soundEnabled;
}

void SoundManager::setVolume(qreal volume)
{
    currentVolume = qBound(0.0, volume, 1.0);
    
    // Update volume for all sound effects
    if (correctKeystroke) correctKeystroke->setVolume(currentVolume);
    if (incorrectKeystroke) incorrectKeystroke->setVolume(currentVolume);
    if (testStart) testStart->setVolume(currentVolume);
    if (testComplete) testComplete->setVolume(currentVolume);
    if (levelUp) levelUp->setVolume(currentVolume);
    if (achievement) achievement->setVolume(currentVolume);
    if (tick) tick->setVolume(currentVolume);
    if (warning) warning->setVolume(currentVolume);
}

qreal SoundManager::getVolume() const
{
    return currentVolume;
}

void SoundManager::setKeystrokeSoundsEnabled(bool enabled)
{
    keystrokeSoundsEnabled = enabled;
}

bool SoundManager::areKeystrokeSoundsEnabled() const
{
    return keystrokeSoundsEnabled;
}

void SoundManager::onSoundFinished()
{
    // Handle sound finished events if needed
    // This can be used for cleanup or chaining sounds
}