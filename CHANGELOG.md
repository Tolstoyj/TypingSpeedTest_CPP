# Changelog

All notable changes to the Typing Speed Test project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-07-08

### Added
- **Initial Release** - Comprehensive typing speed test application
- **Multiple Difficulty Levels**
  - Easy: Simple words and short sentences
  - Medium: Standard complexity phrases  
  - Hard: Technical terms and complex vocabulary
- **User Profiles & Statistics**
  - SQLite database integration for persistent storage
  - User creation and management system
  - Comprehensive test history tracking
  - Personal statistics dashboard with detailed metrics
- **Customizable Test Durations**
  - 15, 30, 60, and 120-second test options
  - Dynamic UI updates showing selected duration
- **Typing Lessons & Practice Modes**
  - 8 different lesson types (Home row, Top row, Bottom row, Numbers, Punctuation, Common words, Letter pairs, Programming)
  - 5 progressive difficulty levels for each lesson type
  - Structured learning path from basic to advanced
  - Mode selector with dynamic UI controls
- **Audio Feedback System**
  - Keystroke sound effects for correct/incorrect typing
  - Test start/complete audio cues
  - Achievement sounds for high accuracy (95%+)
  - Customizable volume control
  - Toggle switches for sound effects and keystroke sounds
- **Core Functionality**
  - Real-time WPM (Words Per Minute) calculation
  - Accuracy tracking with percentage display
  - Color-coded visual feedback (Green=correct, Red=incorrect, Blue=current, Gray=remaining)
  - Progress bar and timer
  - Cross-platform compatibility (macOS, Linux, Windows)
- **Technical Implementation**
  - C++17 with Qt5/Qt6 framework
  - Object-oriented architecture with separate manager classes
  - CMake build system
  - MIT License for free use and modification

### Technical Details
- **Architecture**: Modular design with separate classes for TypingTest, LessonManager, StatisticsManager, SoundManager, and MainWindow
- **Database**: SQLite integration for user profiles and statistics
- **Audio**: Qt Multimedia for sound effects (programmatic generation ready)
- **UI**: Responsive Qt Widgets with dynamic control visibility
- **Cross-platform**: Compatible with macOS, Linux, and Windows

---

## Future Releases

### [1.1.0] - Planned
- **Themes and Visual Customization**
- **Advanced Statistics Dashboard**
- **Import Custom Text Feature**

### [1.2.0] - Planned
- **Typing Heatmap Visualization**
- **Multiple Keyboard Layout Support**
- **Progress Tracking Graphs**

### [2.0.0] - Future
- **Multiplayer and Competition Modes**
- **Mobile App Version**
- **Cloud Synchronization**

---

**Author**: Tolstoy Justin  
**License**: MIT License  
**Repository**: https://github.com/Tolstoyj/TypingSpeedTest_CPP