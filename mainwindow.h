/**
 * Typing Speed Test - Main Window Header
 * 
 * Main application window handling UI components and user interactions.
 * 
 * @author Tolstoy Justin
 * @license MIT License
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
#include <QTime>
#include <QFont>
#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QMessageBox>
#include <QCheckBox>
#include <QSlider>
#include "statisticsmanager.h"
#include "lessonmanager.h"
#include "soundmanager.h"

class TypingTest;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startTest();
    void resetTest();
    void updateStats();
    void updateTextDisplay();
    void onDifficultyChanged(int index);
    void onUserChanged(int index);
    void onDurationChanged(int index);
    void onModeChanged(int index);
    void onLessonTypeChanged(int index);
    void onLessonLevelChanged(int index);
    void onSoundToggled(bool enabled);
    void onKeystrokeSoundToggled(bool enabled);
    void onVolumeChanged(int value);
    void showUserStats();

private:
    void setupUI();
    void resizeEvent(QResizeEvent *event) override;
    
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *statsLayout;
    QHBoxLayout *settingsLayout;
    QHBoxLayout *userLayout;
    
    QLabel *titleLabel;
    QLabel *sampleTextLabel;
    QLineEdit *inputField;
    QPushButton *startButton;
    QPushButton *resetButton;
    QComboBox *difficultyCombo;
    QLabel *difficultyLabel;
    QComboBox *durationCombo;
    QLabel *durationLabel;
    QComboBox *modeCombo;
    QLabel *modeLabel;
    QComboBox *lessonTypeCombo;
    QLabel *lessonTypeLabel;
    QComboBox *lessonLevelCombo;
    QLabel *lessonLevelLabel;
    
    QCheckBox *soundEnabledCheckBox;
    QCheckBox *keystrokeSoundCheckBox;
    QSlider *volumeSlider;
    QLabel *volumeLabel;
    
    QComboBox *userCombo;
    QLabel *userLabel;
    QPushButton *statsButton;
    
    QLabel *wpmLabel;
    QLabel *accuracyLabel;
    QLabel *timeLabel;
    QProgressBar *progressBar;
    
    TypingTest *typingTest;
    StatisticsManager *statsManager;
    LessonManager *lessonManager;
    SoundManager *soundManager;
    QString currentUser;
};

#endif // MAINWINDOW_H