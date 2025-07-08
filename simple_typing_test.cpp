#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>

class SimpleTypingTest {
private:
    std::vector<std::string> sampleTexts = {
        "The quick brown fox jumps over the lazy dog.",
        "A journey of a thousand miles begins with a single step.",
        "To be or not to be, that is the question.",
        "All that glitters is not gold.",
        "The early bird catches the worm.",
        "Actions speak louder than words.",
        "Better late than never.",
        "Don't count your chickens before they hatch.",
        "Every cloud has a silver lining.",
        "Fortune favors the bold."
    };
    
    std::string currentText;
    std::chrono::steady_clock::time_point startTime;
    
public:
    void startTest() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, sampleTexts.size() - 1);
        
        currentText = sampleTexts[dis(gen)];
        
        std::cout << "\n=== TYPING SPEED TEST ===\n";
        std::cout << "Type the following text as quickly and accurately as possible:\n\n";
        std::cout << "\"" << currentText << "\"\n\n";
        std::cout << "Press Enter to start, then type the text: ";
        
        std::string dummy;
        std::getline(std::cin, dummy);
        
        startTime = std::chrono::steady_clock::now();
        
        std::string userInput;
        std::cout << "START: ";
        std::getline(std::cin, userInput);
        
        auto endTime = std::chrono::steady_clock::now();
        
        calculateResults(userInput, startTime, endTime);
    }
    
private:
    void calculateResults(const std::string& userInput, 
                         std::chrono::steady_clock::time_point start,
                         std::chrono::steady_clock::time_point end) {
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        double timeInMinutes = duration.count() / 60000.0;
        
        int correctChars = 0;
        int totalChars = std::min(userInput.length(), currentText.length());
        
        for (int i = 0; i < totalChars; ++i) {
            if (userInput[i] == currentText[i]) {
                correctChars++;
            }
        }
        
        double accuracy = totalChars > 0 ? (double)correctChars / totalChars * 100.0 : 0.0;
        double wpm = timeInMinutes > 0 ? (correctChars / 5.0) / timeInMinutes : 0.0;
        
        std::cout << "\n=== RESULTS ===\n";
        std::cout << "Time taken: " << std::fixed << std::setprecision(2) 
                  << duration.count() / 1000.0 << " seconds\n";
        std::cout << "Accuracy: " << std::fixed << std::setprecision(1) 
                  << accuracy << "%\n";
        std::cout << "Words per minute (WPM): " << std::fixed << std::setprecision(1) 
                  << wpm << "\n";
        std::cout << "Characters typed: " << userInput.length() << "\n";
        std::cout << "Correct characters: " << correctChars << "\n";
        
        if (accuracy < 80) {
            std::cout << "Try to focus on accuracy!\n";
        } else if (wpm > 40) {
            std::cout << "Great typing speed!\n";
        } else {
            std::cout << "Good job! Keep practicing to improve your speed.\n";
        }
    }
};

int main() {
    SimpleTypingTest test;
    char choice;
    
    do {
        test.startTest();
        
        std::cout << "\nWould you like to try again? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer
        
    } while (choice == 'y' || choice == 'Y');
    
    std::cout << "Thanks for using the typing test!\n";
    return 0;
}