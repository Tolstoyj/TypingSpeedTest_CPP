/**
 * Typing Speed Test - Theme Manager Implementation
 * 
 * Manages application themes, colors, fonts, and visual customization.
 * 
 * @author Tolstoy Justin
 * @license MIT License
 */

#include "thememanager.h"
#include <QDebug>

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
    , currentTheme(LIGHT_THEME)
    , fontFamily("Arial")
    , fontSize(MEDIUM_FONT)
    , highContrastMode(false)
    , largeTextMode(false)
    , settings(new QSettings("TypingSpeedTest", "Themes", this))
{
    initializeThemes();
    loadSettings();
}

ThemeManager::~ThemeManager()
{
    saveSettings();
}

void ThemeManager::initializeThemes()
{
    setupLightTheme();
    setupDarkTheme();
    setupHighContrastTheme();
}

void ThemeManager::setupLightTheme()
{
    ThemeColors light;
    light.background = QColor(255, 255, 255);           // White
    light.foreground = QColor(33, 37, 41);              // Dark gray
    light.primaryAccent = QColor(0, 123, 255);          // Blue
    light.secondaryAccent = QColor(108, 117, 125);      // Gray
    light.correctText = QColor(40, 167, 69);            // Green
    light.incorrectText = QColor(220, 53, 69);          // Red
    light.currentText = QColor(23, 162, 184);           // Cyan
    light.remainingText = QColor(108, 117, 125);        // Light gray
    light.buttonBackground = QColor(0, 123, 255);       // Blue
    light.buttonText = QColor(255, 255, 255);           // White
    light.inputBackground = QColor(255, 255, 255);      // White
    light.inputText = QColor(33, 37, 41);               // Dark gray
    light.border = QColor(206, 212, 218);               // Light border
    light.success = QColor(40, 167, 69);                // Green
    light.warning = QColor(255, 193, 7);                // Yellow
    light.error = QColor(220, 53, 69);                  // Red
    
    predefinedThemes[LIGHT_THEME] = light;
}

void ThemeManager::setupDarkTheme()
{
    ThemeColors dark;
    dark.background = QColor(33, 37, 41);               // Dark gray
    dark.foreground = QColor(248, 249, 250);            // Light gray
    dark.primaryAccent = QColor(0, 123, 255);           // Blue
    dark.secondaryAccent = QColor(108, 117, 125);       // Gray
    dark.correctText = QColor(40, 167, 69);             // Green
    dark.incorrectText = QColor(220, 53, 69);           // Red  
    dark.currentText = QColor(23, 162, 184);            // Cyan
    dark.remainingText = QColor(108, 117, 125);         // Gray
    dark.buttonBackground = QColor(0, 123, 255);        // Blue
    dark.buttonText = QColor(255, 255, 255);            // White
    dark.inputBackground = QColor(52, 58, 64);          // Dark gray
    dark.inputText = QColor(248, 249, 250);             // Light gray
    dark.border = QColor(73, 80, 87);                   // Dark border
    dark.success = QColor(40, 167, 69);                 // Green
    dark.warning = QColor(255, 193, 7);                 // Yellow
    dark.error = QColor(220, 53, 69);                   // Red
    
    predefinedThemes[DARK_THEME] = dark;
}

void ThemeManager::setupHighContrastTheme()
{
    ThemeColors highContrast;
    highContrast.background = QColor(0, 0, 0);          // Black
    highContrast.foreground = QColor(255, 255, 255);    // White
    highContrast.primaryAccent = QColor(255, 255, 0);   // Yellow
    highContrast.secondaryAccent = QColor(128, 128, 128); // Gray
    highContrast.correctText = QColor(0, 255, 0);       // Bright green
    highContrast.incorrectText = QColor(255, 0, 0);     // Bright red
    highContrast.currentText = QColor(0, 255, 255);     // Bright cyan
    highContrast.remainingText = QColor(192, 192, 192); // Light gray
    highContrast.buttonBackground = QColor(255, 255, 0); // Yellow
    highContrast.buttonText = QColor(0, 0, 0);          // Black
    highContrast.inputBackground = QColor(255, 255, 255); // White
    highContrast.inputText = QColor(0, 0, 0);           // Black
    highContrast.border = QColor(255, 255, 255);        // White
    highContrast.success = QColor(0, 255, 0);           // Bright green
    highContrast.warning = QColor(255, 255, 0);         // Yellow
    highContrast.error = QColor(255, 0, 0);             // Bright red
    
    predefinedThemes[HIGH_CONTRAST_THEME] = highContrast;
}

void ThemeManager::applyTheme(ThemeType theme)
{
    currentTheme = theme;
    
    if (predefinedThemes.contains(theme)) {
        currentColors = predefinedThemes[theme];
    }
    
    // Apply high contrast adjustments if enabled
    if (highContrastMode && theme != HIGH_CONTRAST_THEME) {
        // Increase contrast for existing themes
        currentColors.correctText = currentColors.correctText.darker(150);
        currentColors.incorrectText = currentColors.incorrectText.lighter(150);
        currentColors.border = currentColors.border.darker(200);
    }
    
    emit themeChanged();
}

void ThemeManager::setCustomTheme(const ThemeColors &colors)
{
    currentTheme = CUSTOM_THEME;
    currentColors = colors;
    predefinedThemes[CUSTOM_THEME] = colors;
    
    emit themeChanged();
}

ThemeManager::ThemeType ThemeManager::getCurrentTheme() const
{
    return currentTheme;
}

ThemeManager::ThemeColors ThemeManager::getCurrentColors() const
{
    return currentColors;
}

void ThemeManager::setFontFamily(const QString &family)
{
    fontFamily = family;
    emit fontChanged();
}

void ThemeManager::setFontSize(FontSize size)
{
    fontSize = static_cast<int>(size);
    
    // Adjust for large text mode
    if (largeTextMode) {
        fontSize += 2;
    }
    
    emit fontChanged();
}

void ThemeManager::setFontSize(int size)
{
    fontSize = qBound(8, size, 24);
    
    if (largeTextMode) {
        fontSize += 2;
    }
    
    emit fontChanged();
}

QString ThemeManager::getFontFamily() const
{
    return fontFamily;
}

int ThemeManager::getFontSize() const
{
    return fontSize;
}

QFont ThemeManager::getUIFont() const
{
    QFont font(fontFamily, fontSize);
    return font;
}

QFont ThemeManager::getTextFont() const
{
    QFont font(fontFamily, fontSize);
    font.setStyleHint(QFont::Monospace);
    return font;
}

void ThemeManager::setHighContrastMode(bool enabled)
{
    highContrastMode = enabled;
    
    if (enabled && currentTheme != HIGH_CONTRAST_THEME) {
        // Apply high contrast modifications to current theme
        applyTheme(currentTheme);
    }
}

bool ThemeManager::isHighContrastMode() const
{
    return highContrastMode;
}

void ThemeManager::setLargeTextMode(bool enabled)
{
    largeTextMode = enabled;
    
    // Recalculate font size
    if (enabled) {
        fontSize += 2;
    } else {
        fontSize = qMax(8, fontSize - 2);
    }
    
    emit fontChanged();
}

bool ThemeManager::isLargeTextMode() const
{
    return largeTextMode;
}

void ThemeManager::saveSettings()
{
    settings->setValue("theme", static_cast<int>(currentTheme));
    settings->setValue("fontFamily", fontFamily);
    settings->setValue("fontSize", fontSize);
    settings->setValue("highContrast", highContrastMode);
    settings->setValue("largeText", largeTextMode);
    
    // Save custom theme colors if current theme is custom
    if (currentTheme == CUSTOM_THEME) {
        settings->beginGroup("CustomTheme");
        settings->setValue("background", currentColors.background);
        settings->setValue("foreground", currentColors.foreground);
        settings->setValue("primaryAccent", currentColors.primaryAccent);
        settings->setValue("secondaryAccent", currentColors.secondaryAccent);
        settings->setValue("correctText", currentColors.correctText);
        settings->setValue("incorrectText", currentColors.incorrectText);
        settings->setValue("currentText", currentColors.currentText);
        settings->setValue("remainingText", currentColors.remainingText);
        settings->setValue("buttonBackground", currentColors.buttonBackground);
        settings->setValue("buttonText", currentColors.buttonText);
        settings->setValue("inputBackground", currentColors.inputBackground);
        settings->setValue("inputText", currentColors.inputText);
        settings->setValue("border", currentColors.border);
        settings->setValue("success", currentColors.success);
        settings->setValue("warning", currentColors.warning);
        settings->setValue("error", currentColors.error);
        settings->endGroup();
    }
}

void ThemeManager::loadSettings()
{
    currentTheme = static_cast<ThemeType>(settings->value("theme", LIGHT_THEME).toInt());
    fontFamily = settings->value("fontFamily", "Arial").toString();
    fontSize = settings->value("fontSize", MEDIUM_FONT).toInt();
    highContrastMode = settings->value("highContrast", false).toBool();
    largeTextMode = settings->value("largeText", false).toBool();
    
    // Load custom theme colors if they exist
    if (currentTheme == CUSTOM_THEME && settings->childGroups().contains("CustomTheme")) {
        settings->beginGroup("CustomTheme");
        ThemeColors custom;
        custom.background = settings->value("background").value<QColor>();
        custom.foreground = settings->value("foreground").value<QColor>();
        custom.primaryAccent = settings->value("primaryAccent").value<QColor>();
        custom.secondaryAccent = settings->value("secondaryAccent").value<QColor>();
        custom.correctText = settings->value("correctText").value<QColor>();
        custom.incorrectText = settings->value("incorrectText").value<QColor>();
        custom.currentText = settings->value("currentText").value<QColor>();
        custom.remainingText = settings->value("remainingText").value<QColor>();
        custom.buttonBackground = settings->value("buttonBackground").value<QColor>();
        custom.buttonText = settings->value("buttonText").value<QColor>();
        custom.inputBackground = settings->value("inputBackground").value<QColor>();
        custom.inputText = settings->value("inputText").value<QColor>();
        custom.border = settings->value("border").value<QColor>();
        custom.success = settings->value("success").value<QColor>();
        custom.warning = settings->value("warning").value<QColor>();
        custom.error = settings->value("error").value<QColor>();
        settings->endGroup();
        
        predefinedThemes[CUSTOM_THEME] = custom;
    }
    
    applyTheme(currentTheme);
}

QString ThemeManager::generateStyleSheet() const
{
    QString styleSheet;
    
    // Main window style
    styleSheet += QString("QMainWindow { background-color: %1; color: %2; }")
                 .arg(currentColors.background.name())
                 .arg(currentColors.foreground.name());
    
    // Add component styles
    styleSheet += generateButtonStyleSheet();
    styleSheet += generateInputStyleSheet();
    styleSheet += generateLabelStyleSheet();
    styleSheet += generateProgressBarStyleSheet();
    styleSheet += generateComboBoxStyleSheet();
    styleSheet += generateCheckBoxStyleSheet();
    styleSheet += generateSliderStyleSheet();
    
    return styleSheet;
}

QString ThemeManager::generateButtonStyleSheet() const
{
    return QString(
        "QPushButton {"
        "    background-color: %1;"
        "    color: %2;"
        "    border: 1px solid %3;"
        "    border-radius: 4px;"
        "    padding: 6px 12px;"
        "    font-family: %4;"
        "    font-size: %5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: %6;"
        "}"
        "QPushButton:pressed {"
        "    background-color: %7;"
        "}"
        "QPushButton:disabled {"
        "    background-color: %8;"
        "    color: %9;"
        "}"
    ).arg(currentColors.buttonBackground.name())
     .arg(currentColors.buttonText.name())
     .arg(currentColors.border.name())
     .arg(fontFamily)
     .arg(fontSize)
     .arg(currentColors.buttonBackground.lighter(110).name())
     .arg(currentColors.buttonBackground.darker(110).name())
     .arg(currentColors.secondaryAccent.name())
     .arg(currentColors.remainingText.name());
}

QString ThemeManager::generateInputStyleSheet() const
{
    return QString(
        "QLineEdit {"
        "    background-color: %1;"
        "    color: %2;"
        "    border: 1px solid %3;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "    font-family: %4;"
        "    font-size: %5px;"
        "}"
        "QLineEdit:focus {"
        "    border: 2px solid %6;"
        "}"
    ).arg(currentColors.inputBackground.name())
     .arg(currentColors.inputText.name())
     .arg(currentColors.border.name())
     .arg(fontFamily)
     .arg(fontSize)
     .arg(currentColors.primaryAccent.name());
}

QString ThemeManager::generateLabelStyleSheet() const
{
    return QString(
        "QLabel {"
        "    color: %1;"
        "    font-family: %2;"
        "    font-size: %3px;"
        "}"
    ).arg(currentColors.foreground.name())
     .arg(fontFamily)
     .arg(fontSize);
}

QString ThemeManager::generateProgressBarStyleSheet() const
{
    return QString(
        "QProgressBar {"
        "    border: 1px solid %1;"
        "    border-radius: 4px;"
        "    background-color: %2;"
        "    text-align: center;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: %3;"
        "    border-radius: 3px;"
        "}"
    ).arg(currentColors.border.name())
     .arg(currentColors.inputBackground.name())
     .arg(currentColors.primaryAccent.name());
}

QString ThemeManager::generateComboBoxStyleSheet() const
{
    return QString(
        "QComboBox {"
        "    background-color: %1;"
        "    color: %2;"
        "    border: 1px solid %3;"
        "    border-radius: 4px;"
        "    padding: 4px;"
        "    font-family: %4;"
        "    font-size: %5px;"
        "}"
        "QComboBox:hover {"
        "    border: 2px solid %6;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "}"
        "QComboBox::down-arrow {"
        "    width: 12px;"
        "    height: 12px;"
        "}"
    ).arg(currentColors.inputBackground.name())
     .arg(currentColors.inputText.name())
     .arg(currentColors.border.name())
     .arg(fontFamily)
     .arg(fontSize)
     .arg(currentColors.primaryAccent.name());
}

QString ThemeManager::generateCheckBoxStyleSheet() const
{
    return QString(
        "QCheckBox {"
        "    color: %1;"
        "    font-family: %2;"
        "    font-size: %3px;"
        "}"
        "QCheckBox::indicator {"
        "    width: 16px;"
        "    height: 16px;"
        "    border: 1px solid %4;"
        "    border-radius: 3px;"
        "    background-color: %5;"
        "}"
        "QCheckBox::indicator:checked {"
        "    background-color: %6;"
        "}"
    ).arg(currentColors.foreground.name())
     .arg(fontFamily)
     .arg(fontSize)
     .arg(currentColors.border.name())
     .arg(currentColors.inputBackground.name())
     .arg(currentColors.primaryAccent.name());
}

QString ThemeManager::generateSliderStyleSheet() const
{
    return QString(
        "QSlider::groove:horizontal {"
        "    border: 1px solid %1;"
        "    height: 6px;"
        "    background: %2;"
        "    border-radius: 3px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: %3;"
        "    border: 1px solid %4;"
        "    width: 16px;"
        "    border-radius: 8px;"
        "    margin-top: -5px;"
        "    margin-bottom: -5px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: %5;"
        "    border-radius: 3px;"
        "}"
    ).arg(currentColors.border.name())
     .arg(currentColors.inputBackground.name())
     .arg(currentColors.primaryAccent.name())
     .arg(currentColors.border.name())
     .arg(currentColors.primaryAccent.name());
}

void ThemeManager::applyToWidget(QWidget *widget)
{
    if (!widget) return;
    
    widget->setStyleSheet(generateStyleSheet());
    widget->setFont(getUIFont());
}

QColor ThemeManager::getCorrectTextColor() const
{
    return currentColors.correctText;
}

QColor ThemeManager::getIncorrectTextColor() const
{
    return currentColors.incorrectText;
}

QColor ThemeManager::getCurrentTextColor() const
{
    return currentColors.currentText;
}

QColor ThemeManager::getRemainingTextColor() const
{
    return currentColors.remainingText;
}