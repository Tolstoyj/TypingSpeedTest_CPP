#include "typingtest.h"
#include <QDebug>

TypingTest::TypingTest(QObject *parent)
    : QObject(parent)
    , timer(new QTimer(this))
    , correctCharacters(0)
    , totalCharacters(0)
    , wordsTyped(0)
    , testActive(false)
    , testComplete(false)
    , currentWPM(0.0)
    , currentAccuracy(100.0)
    , currentTime(0)
    , currentDifficulty(MEDIUM)
    , testDuration(60)
    , currentTestMode(STANDARD_TEST)
    , currentLessonType(LessonManager::HOME_ROW)
    , currentLessonLevel(1)
    , lessonManager(new LessonManager(this))
{
    connect(timer, &QTimer::timeout, this, &TypingTest::updateTimer);
    timer->setInterval(100); // Update every 100ms for smooth display
    
    initializeDifficultyTexts();
    generateSampleText();
}

void TypingTest::startTest()
{
    resetTest();
    testActive = true;
    testComplete = false;
    elapsedTimer.start();
    timer->start();
    
    emit statsUpdated();
}

void TypingTest::resetTest()
{
    timer->stop();
    testActive = false;
    testComplete = false;
    
    correctCharacters = 0;
    totalCharacters = 0;
    wordsTyped = 0;
    currentWPM = 0.0;
    currentAccuracy = 100.0;
    currentTime = 0;
    
    currentInput.clear();
    generateSampleText();
    
    emit statsUpdated();
}

QString TypingTest::getSampleText() const
{
    return sampleText;
}

void TypingTest::generateSampleText()
{
    sampleText.clear();
    
    if (currentTestMode == LESSON_MODE) {
        // Generate lesson-specific text
        sampleText = lessonManager->getProgressiveLesson(currentLessonType, currentLessonLevel);
        
        // Ensure minimum length for lessons
        if (sampleText.length() < 50) {
            sampleText = lessonManager->getLessonText(currentLessonType, 100);
        }
    } else {
        // Standard test mode - generate about 200-300 characters of text
        while (sampleText.length() < 200) {
            if (!sampleText.isEmpty()) {
                sampleText += " ";
            }
            sampleText += getRandomSentence();
        }
        
        // Trim to a reasonable length
        if (sampleText.length() > 250) {
            int lastSpace = sampleText.lastIndexOf(' ', 250);
            if (lastSpace > 0) {
                sampleText = sampleText.left(lastSpace);
            }
        }
    }
}

QString TypingTest::getRandomSentence()
{
    QStringList* currentSentences = &mediumSentences;
    
    switch (currentDifficulty) {
        case EASY:
            currentSentences = &easySentences;
            break;
        case MEDIUM:
            currentSentences = &mediumSentences;
            break;
        case HARD:
            currentSentences = &hardSentences;
            break;
    }
    
    int index = QRandomGenerator::global()->bounded(currentSentences->size());
    return (*currentSentences)[index];
}

void TypingTest::initializeDifficultyTexts()
{
    // Easy level: Simple, common words and short sentences
    easySentences << "The cat sat on the mat."
                 << "I like to eat pizza."
                 << "The sun is bright today."
                 << "Dogs are good pets."
                 << "She went to the store."
                 << "We play games at home."
                 << "The book is on the table."
                 << "He likes to read books."
                 << "The car is red and fast."
                 << "They live in a big house."
                 << "Water is good for you."
                 << "The bird can fly high."
                 << "I want to go home now."
                 << "The tree has green leaves."
                 << "She has a nice smile.";
    
    // Medium level: Current difficulty level
    mediumSentences << "The quick brown fox jumps over the lazy dog."
                   << "A journey of a thousand miles begins with a single step."
                   << "To be or not to be, that is the question."
                   << "All that glitters is not gold."
                   << "The early bird catches the worm."
                   << "Actions speak louder than words."
                   << "Better late than never."
                   << "Don't count your chickens before they hatch."
                   << "Every cloud has a silver lining."
                   << "Fortune favors the bold."
                   << "Good things come to those who wait."
                   << "Haste makes waste."
                   << "If at first you don't succeed, try, try again."
                   << "Knowledge is power."
                   << "Laughter is the best medicine."
                   << "Make hay while the sun shines."
                   << "No pain, no gain."
                   << "Opportunity knocks but once."
                   << "Practice makes perfect."
                   << "Rome wasn't built in a day.";
    
    // Hard level: Complex vocabulary, technical terms, and programming concepts
    hardSentences << "The implementation of polymorphism requires understanding inheritance hierarchies."
                 << "Asynchronous programming paradigms utilize event-driven architectures effectively."
                 << "Quantum entanglement demonstrates non-local correlations between particles."
                 << "The algorithm's time complexity exhibits exponential growth characteristics."
                 << "Microservices architecture facilitates scalable distributed system design."
                 << "Cryptographic hash functions ensure data integrity and authenticity."
                 << "Machine learning algorithms optimize parameters through gradient descent."
                 << "Blockchain technology implements decentralized consensus mechanisms."
                 << "Neuroplasticity enables synaptic reorganization throughout human development."
                 << "Bioinformatics algorithms analyze genomic sequences for pattern recognition."
                 << "Electromagnetic radiation propagates through vacuum at light speed."
                 << "Thermodynamic equilibrium requires energy conservation across system boundaries."
                 << "Pharmaceutical compounds undergo rigorous clinical trial protocols."
                 << "Semiconductor fabrication utilizes photolithography for circuit patterning."
                 << "Epidemiological studies investigate disease transmission patterns statistically.";
}

void TypingTest::setDifficulty(DifficultyLevel level)
{
    currentDifficulty = level;
    generateSampleText();
}

TypingTest::DifficultyLevel TypingTest::getDifficulty() const
{
    return currentDifficulty;
}

void TypingTest::onTextChanged(const QString &text)
{
    if (!testActive || testComplete) {
        return;
    }
    
    currentInput = text;
    calculateStats();
    
    // Check if test is complete
    if (currentInput.length() >= sampleText.length()) {
        testComplete = true;
        testActive = false;
        timer->stop();
    }
    
    emit statsUpdated();
}

void TypingTest::calculateStats()
{
    totalCharacters = currentInput.length();
    correctCharacters = 0;
    
    // Calculate correct characters
    for (int i = 0; i < totalCharacters && i < sampleText.length(); ++i) {
        if (currentInput[i] == sampleText[i]) {
            correctCharacters++;
        }
    }
    
    // Calculate accuracy
    if (totalCharacters > 0) {
        currentAccuracy = (double)correctCharacters / totalCharacters * 100.0;
    } else {
        currentAccuracy = 100.0;
    }
    
    // Calculate WPM
    double timeInMinutes = elapsedTimer.elapsed() / 60000.0; // Convert to minutes
    if (timeInMinutes > 0) {
        // Standard WPM calculation: (characters typed / 5) / time in minutes
        currentWPM = (correctCharacters / WORDS_PER_MINUTE_DIVISOR) / timeInMinutes;
    } else {
        currentWPM = 0.0;
    }
    
    // Ensure WPM is not negative
    if (currentWPM < 0) {
        currentWPM = 0.0;
    }
}

void TypingTest::updateTimer()
{
    if (!testActive) {
        return;
    }
    
    currentTime = elapsedTimer.elapsed() / 1000; // Convert to seconds
    
    // Check if test duration exceeded
    if (currentTime >= testDuration) {
        testComplete = true;
        testActive = false;
        timer->stop();
    }
    
    calculateStats();
    emit statsUpdated();
}

double TypingTest::getWPM() const
{
    return currentWPM;
}

double TypingTest::getAccuracy() const
{
    return currentAccuracy;
}

int TypingTest::getElapsedTime() const
{
    return currentTime;
}

int TypingTest::getProgress() const
{
    if (sampleText.isEmpty()) {
        return 0;
    }
    
    int progress = (currentInput.length() * 100) / sampleText.length();
    return qMin(progress, 100);
}

bool TypingTest::isTestComplete() const
{
    return testComplete;
}

int TypingTest::getCorrectCharacters() const
{
    return correctCharacters;
}

int TypingTest::getTotalCharacters() const
{
    return totalCharacters;
}

void TypingTest::setTestDuration(int seconds)
{
    testDuration = seconds;
}

int TypingTest::getTestDuration() const
{
    return testDuration;
}

void TypingTest::setTestMode(TestMode mode)
{
    currentTestMode = mode;
    generateSampleText();
}

TypingTest::TestMode TypingTest::getTestMode() const
{
    return currentTestMode;
}

void TypingTest::setLessonType(LessonManager::LessonType type)
{
    currentLessonType = type;
    if (currentTestMode == LESSON_MODE) {
        generateSampleText();
    }
}

void TypingTest::setLessonLevel(int level)
{
    currentLessonLevel = qBound(1, level, 5); // Limit to 1-5
    if (currentTestMode == LESSON_MODE) {
        generateSampleText();
    }
}