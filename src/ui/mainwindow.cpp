#include "mainwindow.h"
#include "../core/typingtest.h"
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , typingTest(nullptr)
    , statsManager(nullptr)
    , lessonManager(nullptr)
    , soundManager(nullptr)
    , themeManager(nullptr)
    , currentUser("Guest")
{
    setupUI();
    
    // Initialize managers
    statsManager = new StatisticsManager(this);
    if (!statsManager->initializeDatabase()) {
        qDebug() << "Failed to initialize database";
    }
    
    lessonManager = new LessonManager(this);
    soundManager = new SoundManager(this);
    themeManager = new ThemeManager(this);
    typingTest = new TypingTest(this);
    
    connect(typingTest, &TypingTest::statsUpdated, this, &MainWindow::updateStats);
    connect(inputField, &QLineEdit::textChanged, typingTest, &TypingTest::onTextChanged);
    connect(inputField, &QLineEdit::textChanged, this, &MainWindow::updateTextDisplay);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startTest);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetTest);
    connect(difficultyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onDifficultyChanged);
    connect(durationCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onDurationChanged);
    connect(modeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onModeChanged);
    connect(lessonTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onLessonTypeChanged);
    connect(lessonLevelCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onLessonLevelChanged);
    connect(soundEnabledCheckBox, &QCheckBox::toggled, this, &MainWindow::onSoundToggled);
    connect(keystrokeSoundCheckBox, &QCheckBox::toggled, this, &MainWindow::onKeystrokeSoundToggled);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);
    connect(themeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onThemeChanged);
    connect(fontFamilyCombo, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, &MainWindow::onFontFamilyChanged);
    connect(fontSizeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFontSizeChanged);
    connect(highContrastCheckBox, &QCheckBox::toggled, this, &MainWindow::onHighContrastToggled);
    connect(largeTextCheckBox, &QCheckBox::toggled, this, &MainWindow::onLargeTextToggled);
    connect(themeManager, &ThemeManager::themeChanged, this, &MainWindow::applyCurrentTheme);
    connect(themeManager, &ThemeManager::fontChanged, this, &MainWindow::applyCurrentTheme);
    connect(userCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onUserChanged);
    connect(statsButton, &QPushButton::clicked, this, &MainWindow::showUserStats);
    
    // Initialize user list
    QStringList users = statsManager->getAllUsers();
    if (!users.contains("Guest")) {
        statsManager->createUser("Guest");
        users.prepend("Guest");
    }
    
    userCombo->clear();
    userCombo->addItems(users);
    userCombo->setCurrentText("Guest");
    
    // Initialize theme controls with current settings
    themeCombo->setCurrentIndex(static_cast<int>(themeManager->getCurrentTheme()));
    fontFamilyCombo->setCurrentText(themeManager->getFontFamily());
    
    // Find the matching font size index
    int currentSize = themeManager->getFontSize();
    for (int i = 0; i < fontSizeCombo->count(); ++i) {
        if (fontSizeCombo->itemData(i).toInt() == currentSize) {
            fontSizeCombo->setCurrentIndex(i);
            break;
        }
    }
    
    highContrastCheckBox->setChecked(themeManager->isHighContrastMode());
    largeTextCheckBox->setChecked(themeManager->isLargeTextMode());
    
    // Apply the initial theme
    applyCurrentTheme();
    
    setWindowTitle("Typing Speed Test");
    resize(800, 600);
    
    // Center the window
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    
    // Title
    titleLabel = new QLabel("Typing Speed Test", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    // Sample text display
    sampleTextLabel = new QLabel(this);
    sampleTextLabel->setWordWrap(true);
    sampleTextLabel->setAlignment(Qt::AlignLeft);
    sampleTextLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: 15px; border-radius: 5px; }");
    QFont textFont = sampleTextLabel->font();
    textFont.setPointSize(14);
    sampleTextLabel->setFont(textFont);
    sampleTextLabel->setMinimumHeight(120);
    mainLayout->addWidget(sampleTextLabel);
    
    // Input field
    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Click 'Start Test' and begin typing here...");
    inputField->setEnabled(false);
    QFont inputFont = inputField->font();
    inputFont.setPointSize(14);
    inputField->setFont(inputFont);
    inputField->setMinimumHeight(40);
    mainLayout->addWidget(inputField);
    
    // Progress bar
    progressBar = new QProgressBar(this);
    progressBar->setVisible(false);
    mainLayout->addWidget(progressBar);
    
    // User layout
    userLayout = new QHBoxLayout();
    userLayout->setSpacing(15);
    
    userLabel = new QLabel("User:", this);
    userCombo = new QComboBox(this);
    userCombo->setEditable(true);
    userCombo->setMinimumWidth(150);
    
    statsButton = new QPushButton("View Stats", this);
    
    userLayout->addWidget(userLabel);
    userLayout->addWidget(userCombo);
    userLayout->addWidget(statsButton);
    userLayout->addStretch();
    
    mainLayout->addLayout(userLayout);
    
    // Settings layout
    settingsLayout = new QHBoxLayout();
    settingsLayout->setSpacing(15);
    
    difficultyLabel = new QLabel("Difficulty:", this);
    difficultyCombo = new QComboBox(this);
    difficultyCombo->addItem("Easy");
    difficultyCombo->addItem("Medium");
    difficultyCombo->addItem("Hard");
    difficultyCombo->setCurrentIndex(1); // Default to Medium
    
    durationLabel = new QLabel("Duration:", this);
    durationCombo = new QComboBox(this);
    durationCombo->addItem("15 seconds", 15);
    durationCombo->addItem("30 seconds", 30);
    durationCombo->addItem("60 seconds", 60);
    durationCombo->addItem("120 seconds", 120);
    durationCombo->setCurrentIndex(2); // Default to 60 seconds
    
    modeLabel = new QLabel("Mode:", this);
    modeCombo = new QComboBox(this);
    modeCombo->addItem("Standard Test", static_cast<int>(TypingTest::STANDARD_TEST));
    modeCombo->addItem("Lesson Mode", static_cast<int>(TypingTest::LESSON_MODE));
    
    settingsLayout->addWidget(modeLabel);
    settingsLayout->addWidget(modeCombo);
    settingsLayout->addWidget(difficultyLabel);
    settingsLayout->addWidget(difficultyCombo);
    settingsLayout->addWidget(durationLabel);
    settingsLayout->addWidget(durationCombo);
    settingsLayout->addStretch();
    
    mainLayout->addLayout(settingsLayout);
    
    // Lesson-specific layout (initially hidden)
    QHBoxLayout *lessonLayout = new QHBoxLayout();
    lessonLayout->setSpacing(15);
    
    lessonTypeLabel = new QLabel("Lesson:", this);
    lessonTypeCombo = new QComboBox(this);
    lessonTypeCombo->addItem("Home Row Keys", static_cast<int>(LessonManager::HOME_ROW));
    lessonTypeCombo->addItem("Top Row Keys", static_cast<int>(LessonManager::TOP_ROW));
    lessonTypeCombo->addItem("Bottom Row Keys", static_cast<int>(LessonManager::BOTTOM_ROW));
    lessonTypeCombo->addItem("Numbers", static_cast<int>(LessonManager::NUMBERS));
    lessonTypeCombo->addItem("Punctuation", static_cast<int>(LessonManager::PUNCTUATION));
    lessonTypeCombo->addItem("Common Words", static_cast<int>(LessonManager::COMMON_WORDS));
    lessonTypeCombo->addItem("Letter Pairs", static_cast<int>(LessonManager::BIGRAMS));
    lessonTypeCombo->addItem("Programming", static_cast<int>(LessonManager::PROGRAMMING));
    
    lessonLevelLabel = new QLabel("Level:", this);
    lessonLevelCombo = new QComboBox(this);
    lessonLevelCombo->addItem("1 - Beginner", 1);
    lessonLevelCombo->addItem("2 - Basic", 2);
    lessonLevelCombo->addItem("3 - Intermediate", 3);
    lessonLevelCombo->addItem("4 - Advanced", 4);
    lessonLevelCombo->addItem("5 - Expert", 5);
    
    lessonLayout->addWidget(lessonTypeLabel);
    lessonLayout->addWidget(lessonTypeCombo);
    lessonLayout->addWidget(lessonLevelLabel);
    lessonLayout->addWidget(lessonLevelCombo);
    lessonLayout->addStretch();
    
    // Initially hide lesson controls
    lessonTypeLabel->setVisible(false);
    lessonTypeCombo->setVisible(false);
    lessonLevelLabel->setVisible(false);
    lessonLevelCombo->setVisible(false);
    
    mainLayout->addLayout(lessonLayout);
    
    // Audio controls layout
    QHBoxLayout *audioLayout = new QHBoxLayout();
    audioLayout->setSpacing(15);
    
    soundEnabledCheckBox = new QCheckBox("Sound Effects", this);
    soundEnabledCheckBox->setChecked(true);
    
    keystrokeSoundCheckBox = new QCheckBox("Keystroke Sounds", this);
    keystrokeSoundCheckBox->setChecked(false);
    
    volumeLabel = new QLabel("Volume:", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setMaximumWidth(100);
    
    audioLayout->addWidget(soundEnabledCheckBox);
    audioLayout->addWidget(keystrokeSoundCheckBox);
    audioLayout->addWidget(volumeLabel);
    audioLayout->addWidget(volumeSlider);
    audioLayout->addStretch();
    
    mainLayout->addLayout(audioLayout);
    
    // Theme controls layout
    QHBoxLayout *themeLayout = new QHBoxLayout();
    themeLayout->setSpacing(15);
    
    themeLabel = new QLabel("Theme:", this);
    themeCombo = new QComboBox(this);
    themeCombo->addItem("Light", static_cast<int>(ThemeManager::LIGHT_THEME));
    themeCombo->addItem("Dark", static_cast<int>(ThemeManager::DARK_THEME));
    themeCombo->addItem("High Contrast", static_cast<int>(ThemeManager::HIGH_CONTRAST_THEME));
    
    fontFamilyLabel = new QLabel("Font:", this);
    fontFamilyCombo = new QComboBox(this);
    fontFamilyCombo->addItems({"Arial", "Helvetica", "Times", "Courier", "Verdana", "Georgia"});
    fontFamilyCombo->setCurrentText("Arial");
    
    fontSizeLabel = new QLabel("Size:", this);
    fontSizeCombo = new QComboBox(this);
    fontSizeCombo->addItem("Small", static_cast<int>(ThemeManager::SMALL_FONT));
    fontSizeCombo->addItem("Medium", static_cast<int>(ThemeManager::MEDIUM_FONT));
    fontSizeCombo->addItem("Large", static_cast<int>(ThemeManager::LARGE_FONT));
    fontSizeCombo->addItem("Extra Large", static_cast<int>(ThemeManager::EXTRA_LARGE_FONT));
    fontSizeCombo->addItem("Huge", static_cast<int>(ThemeManager::HUGE_FONT));
    fontSizeCombo->setCurrentIndex(1); // Medium
    
    themeLayout->addWidget(themeLabel);
    themeLayout->addWidget(themeCombo);
    themeLayout->addWidget(fontFamilyLabel);
    themeLayout->addWidget(fontFamilyCombo);
    themeLayout->addWidget(fontSizeLabel);
    themeLayout->addWidget(fontSizeCombo);
    themeLayout->addStretch();
    
    mainLayout->addLayout(themeLayout);
    
    // Accessibility controls layout
    QHBoxLayout *accessibilityLayout = new QHBoxLayout();
    accessibilityLayout->setSpacing(15);
    
    highContrastCheckBox = new QCheckBox("High Contrast", this);
    largeTextCheckBox = new QCheckBox("Large Text", this);
    
    accessibilityLayout->addWidget(highContrastCheckBox);
    accessibilityLayout->addWidget(largeTextCheckBox);
    accessibilityLayout->addStretch();
    
    mainLayout->addLayout(accessibilityLayout);
    
    // Stats layout
    statsLayout = new QHBoxLayout();
    statsLayout->setSpacing(30);
    
    wpmLabel = new QLabel("WPM: 0", this);
    accuracyLabel = new QLabel("Accuracy: 100%", this);
    timeLabel = new QLabel("Time: 0s", this);
    
    QFont statsFont;
    statsFont.setPointSize(12);
    statsFont.setBold(true);
    wpmLabel->setFont(statsFont);
    accuracyLabel->setFont(statsFont);
    timeLabel->setFont(statsFont);
    
    statsLayout->addWidget(wpmLabel);
    statsLayout->addWidget(accuracyLabel);
    statsLayout->addWidget(timeLabel);
    statsLayout->addStretch();
    
    mainLayout->addLayout(statsLayout);
    
    // Button layout
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);
    
    startButton = new QPushButton("Start Test", this);
    resetButton = new QPushButton("Reset", this);
    
    startButton->setMinimumHeight(40);
    resetButton->setMinimumHeight(40);
    
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}

void MainWindow::startTest()
{
    inputField->setEnabled(true);
    inputField->clear();
    inputField->setFocus();
    startButton->setEnabled(false);
    progressBar->setVisible(true);
    
    // Play start sound
    if (soundManager) {
        soundManager->playSound(SoundManager::TEST_START);
    }
    
    typingTest->startTest();
    updateTextDisplay();
}

void MainWindow::resetTest()
{
    inputField->clear();
    inputField->setEnabled(false);
    startButton->setEnabled(true);
    progressBar->setVisible(false);
    
    wpmLabel->setText("WPM: 0");
    accuracyLabel->setText("Accuracy: 100%");
    timeLabel->setText("Time: 0s");
    
    typingTest->resetTest();
    
    // Show appropriate message based on mode
    if (typingTest->getTestMode() == TypingTest::LESSON_MODE) {
        QString lessonTitle = lessonManager->getLessonTitle(static_cast<LessonManager::LessonType>(lessonTypeCombo->currentData().toInt()));
        QString lessonDesc = lessonManager->getLessonDescription(static_cast<LessonManager::LessonType>(lessonTypeCombo->currentData().toInt()));
        int level = lessonLevelCombo->currentData().toInt();
        
        sampleTextLabel->setText(QString("Ready for %1 (Level %2)\n%3\nClick 'Start Test' to begin...")
                               .arg(lessonTitle).arg(level).arg(lessonDesc));
    } else {
        // Standard test mode
        QString difficultyText;
        switch (typingTest->getDifficulty()) {
            case TypingTest::EASY:
                difficultyText = "Easy";
                break;
            case TypingTest::MEDIUM:
                difficultyText = "Medium";
                break;
            case TypingTest::HARD:
                difficultyText = "Hard";
                break;
        }
        
        int duration = typingTest->getTestDuration();
        sampleTextLabel->setText(QString("Click 'Start Test' to begin %1 difficulty test (%2 seconds)...")
                               .arg(difficultyText).arg(duration));
    }
}

void MainWindow::updateStats()
{
    wpmLabel->setText(QString("WPM: %1").arg(typingTest->getWPM()));
    accuracyLabel->setText(QString("Accuracy: %1%").arg(typingTest->getAccuracy(), 0, 'f', 1));
    timeLabel->setText(QString("Time: %1s").arg(typingTest->getElapsedTime()));
    
    progressBar->setValue(typingTest->getProgress());
    
    if (typingTest->isTestComplete()) {
        inputField->setEnabled(false);
        startButton->setEnabled(true);
        progressBar->setVisible(false);
        
        // Save test result to database
        TestResult result;
        result.username = currentUser;
        result.difficulty = static_cast<int>(typingTest->getDifficulty());
        result.wpm = typingTest->getWPM();
        result.accuracy = typingTest->getAccuracy();
        result.timeSpent = typingTest->getElapsedTime();
        result.correctCharacters = typingTest->getCorrectCharacters();
        result.totalCharacters = typingTest->getTotalCharacters();
        
        if (statsManager->saveTestResult(result)) {
            qDebug() << "Test result saved successfully";
        } else {
            qDebug() << "Failed to save test result";
        }
        
        // Play completion sound
        if (soundManager) {
            if (typingTest->getAccuracy() >= 95.0) {
                soundManager->playSound(SoundManager::ACHIEVEMENT); // High accuracy achievement
            } else {
                soundManager->playSound(SoundManager::TEST_COMPLETE);
            }
        }
        
        QString resultText = QString("Test Complete!\nFinal WPM: %1\nAccuracy: %2%\nTime: %3s")
                           .arg(typingTest->getWPM())
                           .arg(typingTest->getAccuracy(), 0, 'f', 1)
                           .arg(typingTest->getElapsedTime());
        
        sampleTextLabel->setText(resultText);
    }
}

void MainWindow::updateTextDisplay()
{
    if (!typingTest) return;
    
    QString sampleText = typingTest->getSampleText();
    QString inputText = inputField->text();
    
    if (sampleText.isEmpty() || !inputField->isEnabled()) {
        return;
    }
    
    // Check if we just typed a character and play sound feedback
    static int lastInputLength = 0;
    if (inputText.length() > lastInputLength && inputText.length() <= sampleText.length()) {
        int lastCharIndex = inputText.length() - 1;
        if (lastCharIndex >= 0 && soundManager) {
            QChar inputChar = inputText[lastCharIndex];
            QChar sampleChar = sampleText[lastCharIndex];
            bool isCorrect = (inputChar == sampleChar);
            soundManager->playKeystrokeSound(isCorrect);
        }
    }
    lastInputLength = inputText.length();
    
    QString htmlText = "<span style='font-family: monospace; font-size: 14px;'>";
    
    for (int i = 0; i < sampleText.length(); ++i) {
        QChar sampleChar = sampleText[i];
        
        if (i < inputText.length()) {
            QChar inputChar = inputText[i];
            if (inputChar == sampleChar) {
                QString bgColor = themeManager ? themeManager->getCorrectTextColor().name() : "#90EE90";
                QString textColor = themeManager ? themeManager->getCurrentColors().foreground.name() : "#000000";
                htmlText += QString("<span style='background-color: %1; color: %2;'>%3</span>")
                           .arg(bgColor).arg(textColor).arg(sampleChar.unicode() == ' ' ? "&nbsp;" : QString(sampleChar));
            } else {
                QString bgColor = themeManager ? themeManager->getIncorrectTextColor().name() : "#FFB6C1";
                QString textColor = themeManager ? themeManager->getCurrentColors().foreground.name() : "#8B0000";
                htmlText += QString("<span style='background-color: %1; color: %2;'>%3</span>")
                           .arg(bgColor).arg(textColor).arg(sampleChar.unicode() == ' ' ? "&nbsp;" : QString(sampleChar));
            }
        } else if (i == inputText.length()) {
            QString bgColor = themeManager ? themeManager->getCurrentTextColor().name() : "#87CEEB";
            QString textColor = themeManager ? themeManager->getCurrentColors().foreground.name() : "#000000";
            htmlText += QString("<span style='background-color: %1; color: %2;'>%3</span>")
                       .arg(bgColor).arg(textColor).arg(sampleChar.unicode() == ' ' ? "&nbsp;" : QString(sampleChar));
        } else {
            QString textColor = themeManager ? themeManager->getRemainingTextColor().name() : "#696969";
            htmlText += QString("<span style='color: %1;'>%2</span>")
                       .arg(textColor).arg(sampleChar.unicode() == ' ' ? "&nbsp;" : QString(sampleChar));
        }
    }
    
    htmlText += "</span>";
    sampleTextLabel->setText(htmlText);
}

void MainWindow::onDifficultyChanged(int index)
{
    if (!typingTest) return;
    
    TypingTest::DifficultyLevel difficulty = static_cast<TypingTest::DifficultyLevel>(index);
    typingTest->setDifficulty(difficulty);
    
    // Update the display if not currently testing
    if (!inputField->isEnabled()) {
        updateTextDisplay();
    }
}

void MainWindow::onDurationChanged(int index)
{
    if (!typingTest) return;
    
    int duration = durationCombo->currentData().toInt();
    typingTest->setTestDuration(duration);
}

void MainWindow::onModeChanged(int index)
{
    if (!typingTest) return;
    
    TypingTest::TestMode mode = static_cast<TypingTest::TestMode>(modeCombo->currentData().toInt());
    typingTest->setTestMode(mode);
    
    // Show/hide lesson controls based on mode
    bool showLessonControls = (mode == TypingTest::LESSON_MODE);
    lessonTypeLabel->setVisible(showLessonControls);
    lessonTypeCombo->setVisible(showLessonControls);
    lessonLevelLabel->setVisible(showLessonControls);
    lessonLevelCombo->setVisible(showLessonControls);
    
    // Hide difficulty controls in lesson mode (lessons have their own progression)
    difficultyLabel->setVisible(!showLessonControls);
    difficultyCombo->setVisible(!showLessonControls);
    
    // Update display
    if (!inputField->isEnabled()) {
        updateTextDisplay();
    }
}

void MainWindow::onLessonTypeChanged(int index)
{
    if (!typingTest) return;
    
    LessonManager::LessonType type = static_cast<LessonManager::LessonType>(lessonTypeCombo->currentData().toInt());
    typingTest->setLessonType(type);
    
    // Update display if not currently testing
    if (!inputField->isEnabled()) {
        updateTextDisplay();
    }
}

void MainWindow::onLessonLevelChanged(int index)
{
    if (!typingTest) return;
    
    int level = lessonLevelCombo->currentData().toInt();
    typingTest->setLessonLevel(level);
    
    // Update display if not currently testing
    if (!inputField->isEnabled()) {
        updateTextDisplay();
    }
}

void MainWindow::onSoundToggled(bool enabled)
{
    if (soundManager) {
        soundManager->setEnabled(enabled);
        
        // Disable keystroke sounds if general sounds are disabled
        if (!enabled) {
            keystrokeSoundCheckBox->setChecked(false);
            soundManager->setKeystrokeSoundsEnabled(false);
        }
        
        // Enable/disable volume controls
        volumeLabel->setEnabled(enabled);
        volumeSlider->setEnabled(enabled);
        keystrokeSoundCheckBox->setEnabled(enabled);
    }
}

void MainWindow::onKeystrokeSoundToggled(bool enabled)
{
    if (soundManager) {
        soundManager->setKeystrokeSoundsEnabled(enabled);
    }
}

void MainWindow::onVolumeChanged(int value)
{
    if (soundManager) {
        qreal volume = value / 100.0; // Convert 0-100 to 0.0-1.0
        soundManager->setVolume(volume);
    }
}

void MainWindow::onThemeChanged(int index)
{
    if (!themeManager) return;
    
    ThemeManager::ThemeType theme = static_cast<ThemeManager::ThemeType>(themeCombo->currentData().toInt());
    themeManager->applyTheme(theme);
}

void MainWindow::onFontFamilyChanged(const QString &family)
{
    if (!themeManager) return;
    
    themeManager->setFontFamily(family);
}

void MainWindow::onFontSizeChanged(int index)
{
    if (!themeManager) return;
    
    ThemeManager::FontSize size = static_cast<ThemeManager::FontSize>(fontSizeCombo->currentData().toInt());
    themeManager->setFontSize(size);
}

void MainWindow::onHighContrastToggled(bool enabled)
{
    if (!themeManager) return;
    
    themeManager->setHighContrastMode(enabled);
}

void MainWindow::onLargeTextToggled(bool enabled)
{
    if (!themeManager) return;
    
    themeManager->setLargeTextMode(enabled);
}

void MainWindow::applyCurrentTheme()
{
    if (!themeManager) return;
    
    // Apply theme to main window
    themeManager->applyToWidget(this);
    
    // Update the color-coded text display with new theme colors
    updateTextDisplay();
}

void MainWindow::onUserChanged(int index)
{
    QString newUser = userCombo->currentText().trimmed();
    if (newUser.isEmpty()) {
        newUser = "Guest";
    }
    
    if (newUser != currentUser) {
        currentUser = newUser;
        
        // Create user if doesn't exist
        if (!statsManager->userExists(currentUser)) {
            statsManager->createUser(currentUser);
            
            // Update combo box list
            QStringList users = statsManager->getAllUsers();
            userCombo->blockSignals(true);
            userCombo->clear();
            userCombo->addItems(users);
            userCombo->setCurrentText(currentUser);
            userCombo->blockSignals(false);
        }
    }
}

void MainWindow::showUserStats()
{
    if (!statsManager || currentUser.isEmpty()) return;
    
    UserStats stats = statsManager->getUserStats(currentUser);
    QList<TestResult> personalBests = statsManager->getPersonalBests(currentUser);
    
    QString statsText = QString(
        "=== %1's Statistics ===\n\n"
        "Total Tests: %2\n"
        "Average WPM: %3\n"
        "Best WPM: %4\n"
        "Average Accuracy: %5%\n"
        "Best Accuracy: %6%\n"
        "Total Time: %7 minutes\n\n"
        "Personal Bests:\n"
    ).arg(currentUser)
     .arg(stats.totalTests)
     .arg(stats.averageWpm, 0, 'f', 1)
     .arg(stats.bestWpm, 0, 'f', 1)
     .arg(stats.averageAccuracy, 0, 'f', 1)
     .arg(stats.bestAccuracy, 0, 'f', 1)
     .arg(stats.totalTimeSpent / 60);
    
    QStringList difficultyNames = {"Easy", "Medium", "Hard"};
    for (const TestResult &result : personalBests) {
        statsText += QString("- %1: %2 WPM (%3% accuracy)\n")
                    .arg(difficultyNames[result.difficulty])
                    .arg(result.wpm, 0, 'f', 1)
                    .arg(result.accuracy, 0, 'f', 1);
    }
    
    // Create a simple message box to show stats
    QMessageBox msgBox;
    msgBox.setWindowTitle("User Statistics");
    msgBox.setText(statsText);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
}