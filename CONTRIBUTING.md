# Contributing to Typing Speed Test

First off, thank you for considering contributing to the Typing Speed Test project! 🎉

## Code of Conduct

This project is open to everyone. Please be respectful and constructive in all interactions.

## How to Contribute

### Reporting Bugs

Before creating bug reports, please check if the issue already exists. When you create a bug report, please include as many details as possible:

- **Use a clear and descriptive title**
- **Describe the exact steps to reproduce the problem**
- **Provide specific examples** to demonstrate the steps
- **Describe the behavior you observed and what behavior you expected**
- **Include screenshots** if possible
- **Specify your operating system and Qt version**

### Suggesting Enhancements

Enhancement suggestions are welcome! Please provide:

- **A clear and descriptive title**
- **A detailed description of the suggested enhancement**
- **Examples of how the enhancement would be used**
- **Mockups or sketches** if applicable

### Development Process

1. **Fork** the repository
2. **Create a feature branch** from `main`:
   ```bash
   git checkout -b feature/amazing-feature
   ```
3. **Make your changes** following the coding standards
4. **Test your changes** thoroughly
5. **Commit your changes** with descriptive messages:
   ```bash
   git commit -m "Add amazing feature that does X"
   ```
6. **Push to your fork**:
   ```bash
   git push origin feature/amazing-feature
   ```
7. **Create a Pull Request**

### Coding Standards

#### C++ Guidelines
- Use **C++17** features when appropriate
- Follow **RAII principles**
- Use **smart pointers** instead of raw pointers when possible
- Prefer **const correctness**
- Use **meaningful variable and function names**

#### Qt Guidelines
- Use **Qt's signal/slot mechanism** for communication
- Follow **Qt's memory management** patterns (parent-child ownership)
- Use **Qt's container classes** when appropriate
- Follow **Qt's coding conventions**

#### Code Style
- **Indentation**: 4 spaces (no tabs)
- **Line length**: 120 characters maximum
- **Braces**: Opening brace on same line
- **Naming conventions**:
  - Classes: `PascalCase`
  - Functions: `camelCase`
  - Variables: `camelCase`
  - Constants: `UPPER_SNAKE_CASE`

Example:
```cpp
class ExampleClass : public QObject
{
    Q_OBJECT

public:
    explicit ExampleClass(QObject *parent = nullptr);
    void doSomething();

private slots:
    void onButtonClicked();

private:
    void helperFunction();
    
    QString memberVariable;
    static const int MAX_VALUE = 100;
};
```

### Testing

- **Manual Testing**: Test your changes across different scenarios
- **Performance Testing**: Ensure changes don't negatively impact performance
- **Cross-Platform**: Consider compatibility with different operating systems

### Documentation

- **Code Comments**: Add comments for complex logic
- **API Documentation**: Document public interfaces
- **README Updates**: Update README.md if you add new features
- **Commit Messages**: Write clear, descriptive commit messages

### Areas for Contribution

#### High Priority
- **Bug fixes** and stability improvements
- **Performance optimizations**
- **Cross-platform compatibility** fixes
- **Accessibility improvements**

#### Medium Priority
- **New lesson types** and exercises
- **Theme system** implementation
- **Advanced statistics** features
- **UI/UX improvements**

#### Low Priority
- **Additional sound effects**
- **Keyboard layout support**
- **Multiplayer functionality**
- **Mobile app version**

### Pull Request Guidelines

#### Before Submitting
- Ensure your code compiles without warnings
- Test on multiple platforms if possible
- Update documentation as needed
- Follow the established code style

#### Pull Request Description
Please include:
- **Summary** of changes made
- **Motivation** for the changes
- **Testing** performed
- **Screenshots** for UI changes
- **Breaking changes** if any

#### Example PR Template
```markdown
## Summary
Brief description of what this PR does.

## Changes Made
- Feature A added
- Bug B fixed
- Performance improvement C

## Testing
- Tested on macOS 12.0 with Qt 5.15
- Verified all existing tests pass
- Added new test cases for feature A

## Screenshots
[Include screenshots for UI changes]

## Breaking Changes
None / List any breaking changes
```

### Getting Help

If you need help with:
- **Setting up the development environment**
- **Understanding the codebase**
- **Implementing a feature**

Feel free to:
- **Create an issue** with your question
- **Start a discussion** on GitHub
- **Check existing issues** for similar questions

## Recognition

Contributors will be acknowledged in:
- **README.md** acknowledgments section
- **Release notes** for significant contributions
- **GitHub contributors** page

## License

By contributing to this project, you agree that your contributions will be licensed under the MIT License.

---

Thank you for contributing to making typing practice better for everyone! 🚀