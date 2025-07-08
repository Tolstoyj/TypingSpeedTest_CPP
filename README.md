# Typing Speed Test - C++ Qt Application

A comprehensive typing speed test and training application built with C++ and Qt, featuring multiple difficulty levels, structured lessons, user profiles, and audio feedback.

![Typing Speed Test - Main Interface](Screenshots/Screenshot%202025-07-08%20at%2013.48.09.png)

## 🚀 Features

### Core Functionality
- **Real-time WPM (Words Per Minute) calculation**
- **Accuracy tracking with percentage display**
- **Color-coded visual feedback**: Green (correct), Red (incorrect), Blue (current position), Gray (remaining)
- **Progress bar and timer**
- **Customizable test durations**: 15s, 30s, 60s, 120s

### Difficulty Levels
- **Easy**: Simple words and short sentences for beginners
- **Medium**: Standard complexity phrases for intermediate users
- **Hard**: Technical terms and complex vocabulary for advanced users

### Typing Lessons & Practice Modes
- **8 Different Lesson Types**:
  - Home Row Keys (asdf jkl;)
  - Top Row Keys (qwerty uiop)
  - Bottom Row Keys (zxcv bnm)
  - Numbers (1234567890)
  - Punctuation (.,;:!?)
  - Common Words (most frequently used English words)
  - Letter Pairs/Bigrams (th, er, in, etc.)
  - Programming Characters ((){}[]<>=+-*/\\)

- **5 Progressive Difficulty Levels** for each lesson type
- **Structured Learning Path** from basic finger positioning to advanced patterns

### User Profiles & Statistics
- **SQLite Database Integration** for persistent data storage
- **User Creation and Management**
- **Comprehensive Test History** with detailed metrics
- **Personal Statistics Dashboard** showing:
  - Total tests completed
  - Average and best WPM
  - Average and best accuracy
  - Total practice time
  - Personal best records for each difficulty level

### Audio Feedback System
- **Keystroke Sound Effects** for correct/incorrect typing
- **Test Start/Complete Audio Cues**
- **Achievement Sounds** for high accuracy (95%+)
- **Customizable Volume Control**
- **Toggle switches** for sound effects and keystroke sounds

![Typing Speed Test - Lesson Mode](Screenshots/Screenshot%202025-07-08%20at%2013.48.28.png)

## 🛠️ Technical Details

### Built With
- **C++17** - Core programming language
- **Qt5/Qt6** - Cross-platform GUI framework
- **SQLite** - Lightweight database for statistics
- **CMake** - Build system

### Architecture
- **Object-Oriented Design** with separate classes for different responsibilities:
  - `TypingTest` - Core test logic and timing
  - `LessonManager` - Lesson content and progression
  - `StatisticsManager` - Database operations and user statistics
  - `SoundManager` - Audio feedback system
  - `MainWindow` - User interface and event handling

## 📋 Requirements

### System Requirements
- **Operating System**: macOS, Linux, or Windows
- **Qt5 or Qt6** with the following modules:
  - Core
  - Widgets
  - Sql
  - Multimedia
- **CMake 3.16** or higher
- **C++17 compatible compiler**

### Dependencies

#### macOS (with Homebrew)
```bash
brew install qt@5 cmake
# or
brew install qt@6 cmake
```

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install qt5-default qt5-multimedia-dev cmake build-essential
# or for Qt6
sudo apt install qt6-base-dev qt6-multimedia-dev cmake build-essential
```

#### Windows
- Install Qt6 from the official Qt installer
- Install CMake
- Use Visual Studio or MinGW compiler

## 🚀 Installation & Building

### Clone the Repository
```bash
git clone https://github.com/Tolstoyj/TypingSpeedTest_CPP.git
cd TypingSpeedTest_CPP
```

### Build Instructions

#### macOS/Linux
```bash
mkdir build
cd build
cmake ..
make -j4
```

#### Windows (Visual Studio)
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Run the Application
```bash
./TypingSpeedTest
```

## 🎯 Usage

### Getting Started
1. **Select a User**: Choose an existing user or create a new profile
2. **Choose Mode**: 
   - **Standard Test**: Traditional typing speed test
   - **Lesson Mode**: Structured learning exercises
3. **Configure Settings**:
   - Select difficulty level (Easy/Medium/Hard)
   - Set test duration (15s-120s)
   - Choose lesson type and level (in lesson mode)
4. **Audio Settings**: Enable/disable sound effects and adjust volume
5. **Start Typing**: Click "Start Test" and begin typing!

### Lesson Mode
- Start with **Home Row Keys** at **Level 1**
- Progress through levels as you improve
- Each lesson type focuses on specific skills
- Use the progressive difficulty system to build muscle memory

### Tracking Progress
- Click **"View Stats"** to see your performance history
- Track improvement over time
- Set personal goals for WPM and accuracy
- Review test history for different difficulty levels

## 🎨 Customization

### Audio Settings
- **Sound Effects**: Toggle general sound effects on/off
- **Keystroke Sounds**: Enable/disable typing sound feedback
- **Volume Control**: Adjust audio levels from 0-100%

### Test Configuration
- **Duration**: Choose from preset durations or focus on completing text
- **Difficulty**: Select appropriate challenge level
- **Lesson Focus**: Target specific skills with lesson mode

## 📊 Statistics & Analytics

The application tracks comprehensive statistics including:
- **Performance Metrics**: WPM, accuracy, time spent
- **Progress Tracking**: Improvement over time
- **Personal Records**: Best performances for each difficulty
- **Session History**: Detailed logs of all practice sessions

## 🤝 Contributing

Contributions are welcome! Here are some ways you can help:

### Development Areas
- Additional lesson types and exercises
- New themes and visual customizations
- Advanced statistics and analytics
- Multiplayer functionality
- Mobile app version

### How to Contribute
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

**Free to use, modify, and distribute for any purpose, including commercial use.**

## 👨‍💻 Author

**Tolstoy Justin**
- GitHub: [@Tolstoyj](https://github.com/Tolstoyj)

## 🙏 Acknowledgments

- Built with the powerful Qt framework
- SQLite for reliable data storage
- Inspired by the need for comprehensive typing training tools
- Community feedback and suggestions

## 🐛 Bug Reports & Feature Requests

Found a bug or have a feature idea? Please open an issue on GitHub:
[Create an Issue](https://github.com/Tolstoyj/TypingSpeedTest_CPP/issues)

## 📈 Roadmap

### Upcoming Features
- **Themes and Visual Customization**
- **Advanced Statistics Dashboard**
- **Import Custom Text Feature**
- **Typing Heatmap Visualization**
- **Multiple Keyboard Layout Support**
- **Competition and Multiplayer Modes**

---

**Happy Typing! 🎯**

Improve your typing speed and accuracy with structured practice and comprehensive feedback.