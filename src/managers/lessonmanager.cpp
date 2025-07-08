#include "lessonmanager.h"

LessonManager::LessonManager(QObject *parent)
    : QObject(parent)
{
    // Initialize character sets
    homeRowChars = "asdfghjkl;";
    topRowChars = "qwertyuiop";
    bottomRowChars = "zxcvbnm,./";
    numberChars = "1234567890";
    punctuationChars = ".,;:!?'\"";
    programmingChars = "(){}[]<>=+-*/\\|&%$#@";
    
    initializeLessons();
}

void LessonManager::initializeLessons()
{
    // Common words for practice
    commonWords << "the" << "and" << "for" << "are" << "but" << "not" << "you" << "all"
               << "can" << "had" << "her" << "was" << "one" << "our" << "out" << "day"
               << "get" << "has" << "him" << "his" << "how" << "man" << "new" << "now"
               << "old" << "see" << "two" << "way" << "who" << "boy" << "did" << "its"
               << "let" << "put" << "say" << "she" << "too" << "use" << "what" << "when"
               << "where" << "which" << "with" << "have" << "this" << "will" << "your"
               << "from" << "they" << "know" << "want" << "been" << "good" << "much"
               << "some" << "time" << "very" << "when" << "come" << "here" << "just"
               << "like" << "long" << "make" << "many" << "over" << "such" << "take"
               << "than" << "them" << "well" << "were";
    
    // Common bigrams (two-letter combinations)
    commonBigrams << "th" << "he" << "in" << "er" << "an" << "re" << "ed" << "nd"
                 << "on" << "en" << "at" << "ou" << "it" << "is" << "or" << "ti"
                 << "hi" << "st" << "ar" << "ne" << "ng" << "al" << "se" << "to"
                 << "as" << "de" << "rt" << "ve" << "te" << "es" << "le" << "nt";
    
    // Common trigrams (three-letter combinations)
    commonTrigrams << "the" << "and" << "ing" << "her" << "hat" << "his" << "tha"
                  << "ere" << "for" << "ent" << "ion" << "ter" << "was" << "you"
                  << "ith" << "ver" << "all" << "wit" << "thi" << "tio" << "end";
    
    // Set up lesson titles
    lessonTitles[HOME_ROW] = "Home Row Keys";
    lessonTitles[TOP_ROW] = "Top Row Keys";
    lessonTitles[BOTTOM_ROW] = "Bottom Row Keys";
    lessonTitles[NUMBERS] = "Number Practice";
    lessonTitles[PUNCTUATION] = "Punctuation Practice";
    lessonTitles[COMMON_WORDS] = "Common Words";
    lessonTitles[FINGER_SPECIFIC] = "Finger-Specific Training";
    lessonTitles[BIGRAMS] = "Letter Pairs (Bigrams)";
    lessonTitles[TRIGRAMS] = "Letter Combinations (Trigrams)";
    lessonTitles[PROGRAMMING] = "Programming Characters";
    
    // Set up lesson descriptions
    lessonDescriptions[HOME_ROW] = "Practice the foundation keys: a s d f g h j k l ;";
    lessonDescriptions[TOP_ROW] = "Master the top row: q w e r t y u i o p";
    lessonDescriptions[BOTTOM_ROW] = "Learn the bottom row: z x c v b n m , . /";
    lessonDescriptions[NUMBERS] = "Number typing practice: 1 2 3 4 5 6 7 8 9 0";
    lessonDescriptions[PUNCTUATION] = "Common punctuation marks and symbols";
    lessonDescriptions[COMMON_WORDS] = "Most frequently used English words";
    lessonDescriptions[FINGER_SPECIFIC] = "Targeted exercises for each finger";
    lessonDescriptions[BIGRAMS] = "Common two-letter combinations";
    lessonDescriptions[TRIGRAMS] = "Common three-letter patterns";
    lessonDescriptions[PROGRAMMING] = "Special characters used in programming";
    
    // Initialize lesson content
    lessonContent[HOME_ROW] << "asdf" << "jkl;" << "fjfj" << "dkdk" << "slsl" << "a;a;"
                           << "asdf jkl;" << "fjdk slgh" << "asdfjkl;" << "glad" << "hall"
                           << "fall" << "ask" << "flask" << "glass" << "fast" << "last";
    
    lessonContent[TOP_ROW] << "qwer" << "tyui" << "op" << "quip" << "tire" << "wire"
                          << "quit" << "were" << "power" << "tower" << "quote" << "write"
                          << "quite" << "poetry" << "typewriter" << "query" << "worry";
    
    lessonContent[BOTTOM_ROW] << "zxcv" << "bnm" << ",./" << "zoom" << "next" << "come"
                             << "move" << "bronze" << "complex" << "maximum" << "examine"
                             << "example" << "mixture" << "boxing" << "frozen" << "dozen";
    
    lessonContent[NUMBERS] << "123" << "456" << "789" << "0" << "12345" << "67890"
                          << "1234567890" << "123 456 789" << "1 2 3 4 5" << "6 7 8 9 0";
    
    lessonContent[PUNCTUATION] << ".,;" << ":!?" << "'\"" << "Hello, world!" << "Yes; no."
                              << "What? Why!" << "I said, \"Hello.\"" << "Can't you see?"
                              << "It's great!" << "Time: 3:30" << "Cost: $10.50";
    
    lessonContent[PROGRAMMING] << "()" << "{}" << "[]" << "<>" << "=+" << "-*" << "/\\"
                              << "|&" << "%$" << "#@" << "if (x == y)" << "array[i]"
                              << "function() {}" << "x += y;" << "return true;"
                              << "#include <stdio.h>" << "var x = 10;" << "print(\"hello\");";
}

QString LessonManager::getLessonText(LessonType type, int length)
{
    if (!lessonContent.contains(type)) {
        return "Lesson type not found.";
    }
    
    QStringList content = lessonContent[type];
    return formatLesson(content, length);
}

QString LessonManager::getLessonTitle(LessonType type)
{
    return lessonTitles.value(type, "Unknown Lesson");
}

QString LessonManager::getLessonDescription(LessonType type)
{
    return lessonDescriptions.value(type, "No description available.");
}

QList<LessonManager::LessonType> LessonManager::getAllLessonTypes()
{
    return {HOME_ROW, TOP_ROW, BOTTOM_ROW, NUMBERS, PUNCTUATION, 
            COMMON_WORDS, FINGER_SPECIFIC, BIGRAMS, TRIGRAMS, PROGRAMMING};
}

QString LessonManager::getProgressiveLesson(LessonType type, int level)
{
    // Progressive difficulty: start simple, add complexity
    int baseLength = 20 + (level - 1) * 10; // 20, 30, 40, 50, 60 characters
    
    switch (type) {
        case HOME_ROW:
            switch (level) {
                case 1: return generateCharacterDrill("asdf", baseLength);
                case 2: return generateCharacterDrill("asdfgh", baseLength);
                case 3: return generateCharacterDrill("asdfghjk", baseLength);
                case 4: return generateCharacterDrill("asdfghjkl", baseLength);
                case 5: return generateCharacterDrill(homeRowChars, baseLength);
            }
            break;
        case TOP_ROW:
            switch (level) {
                case 1: return generateCharacterDrill("qwer", baseLength);
                case 2: return generateCharacterDrill("qwerty", baseLength);
                case 3: return generateCharacterDrill("qwertyui", baseLength);
                case 4: return generateCharacterDrill("qwertyuio", baseLength);
                case 5: return generateCharacterDrill(topRowChars, baseLength);
            }
            break;
        case BOTTOM_ROW:
            switch (level) {
                case 1: return generateCharacterDrill("zxcv", baseLength);
                case 2: return generateCharacterDrill("zxcvbn", baseLength);
                case 3: return generateCharacterDrill("zxcvbnm", baseLength);
                case 4: return generateCharacterDrill("zxcvbnm,", baseLength);
                case 5: return generateCharacterDrill(bottomRowChars, baseLength);
            }
            break;
        case COMMON_WORDS:
            return generateWordDrill(commonWords.mid(0, level * 10), baseLength / 4);
        case BIGRAMS:
            return generateBigramDrill(commonBigrams.mid(0, level * 5), baseLength);
        default:
            return getLessonText(type, baseLength);
    }
    
    return getLessonText(type, baseLength);
}

QString LessonManager::generateCharacterDrill(const QString &characters, int length)
{
    return generateRandomString(characters, length);
}

QString LessonManager::generateWordDrill(const QStringList &words, int count)
{
    QStringList result;
    for (int i = 0; i < count; ++i) {
        int index = QRandomGenerator::global()->bounded(words.size());
        result << words[index];
    }
    return result.join(" ");
}

QString LessonManager::generateBigramDrill(const QStringList &bigrams, int length)
{
    QString result;
    while (result.length() < length) {
        int index = QRandomGenerator::global()->bounded(bigrams.size());
        result += bigrams[index] + " ";
    }
    return result.trimmed();
}

QString LessonManager::generateRandomString(const QString &chars, int length)
{
    QString result;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        result += chars[index];
        
        // Add spaces occasionally for readability
        if (i > 0 && i % 4 == 0 && i < length - 1) {
            result += " ";
        }
    }
    return result;
}

QString LessonManager::formatLesson(const QStringList &elements, int totalLength)
{
    QString result;
    int currentLength = 0;
    
    while (currentLength < totalLength && !elements.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(elements.size());
        QString element = elements[index];
        
        if (currentLength + element.length() + 1 <= totalLength) {
            if (!result.isEmpty()) {
                result += " ";
                currentLength++;
            }
            result += element;
            currentLength += element.length();
        } else {
            break;
        }
    }
    
    return result;
}