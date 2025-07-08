/**
 * Typing Speed Test - Theme Manager Header
 * 
 * Manages application themes, colors, fonts, and visual customization.
 * 
 * @author Tolstoy Justin
 * @license MIT License
 */

#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QFont>
#include <QColor>
#include <QSettings>
#include <QMap>
#include <QString>

class ThemeManager : public QObject
{
    Q_OBJECT

public:
    enum ThemeType {
        LIGHT_THEME,
        DARK_THEME,
        HIGH_CONTRAST_THEME,
        CUSTOM_THEME
    };

    enum FontSize {
        SMALL_FONT = 10,
        MEDIUM_FONT = 12,
        LARGE_FONT = 14,
        EXTRA_LARGE_FONT = 16,
        HUGE_FONT = 18
    };

    struct ThemeColors {
        QColor background;
        QColor foreground;
        QColor primaryAccent;
        QColor secondaryAccent;
        QColor correctText;
        QColor incorrectText;
        QColor currentText;
        QColor remainingText;
        QColor buttonBackground;
        QColor buttonText;
        QColor inputBackground;
        QColor inputText;
        QColor border;
        QColor success;
        QColor warning;
        QColor error;
    };

    explicit ThemeManager(QObject *parent = nullptr);
    ~ThemeManager();

    // Theme management
    void applyTheme(ThemeType theme);
    void setCustomTheme(const ThemeColors &colors);
    ThemeType getCurrentTheme() const;
    ThemeColors getCurrentColors() const;
    
    // Font management
    void setFontFamily(const QString &family);
    void setFontSize(FontSize size);
    void setFontSize(int size);
    QString getFontFamily() const;
    int getFontSize() const;
    QFont getUIFont() const;
    QFont getTextFont() const;
    
    // Accessibility
    void setHighContrastMode(bool enabled);
    bool isHighContrastMode() const;
    void setLargeTextMode(bool enabled);
    bool isLargeTextMode() const;
    
    // Persistence
    void saveSettings();
    void loadSettings();
    
    // Utility methods
    QString generateStyleSheet() const;
    void applyToWidget(QWidget *widget);
    QColor getCorrectTextColor() const;
    QColor getIncorrectTextColor() const;
    QColor getCurrentTextColor() const;
    QColor getRemainingTextColor() const;

signals:
    void themeChanged();
    void fontChanged();

private:
    void initializeThemes();
    void setupLightTheme();
    void setupDarkTheme();
    void setupHighContrastTheme();
    QString generateButtonStyleSheet() const;
    QString generateInputStyleSheet() const;
    QString generateLabelStyleSheet() const;
    QString generateProgressBarStyleSheet() const;
    QString generateComboBoxStyleSheet() const;
    QString generateCheckBoxStyleSheet() const;
    QString generateSliderStyleSheet() const;
    
    ThemeType currentTheme;
    ThemeColors currentColors;
    QString fontFamily;
    int fontSize;
    bool highContrastMode;
    bool largeTextMode;
    
    QMap<ThemeType, ThemeColors> predefinedThemes;
    QSettings *settings;
};

#endif // THEMEMANAGER_H