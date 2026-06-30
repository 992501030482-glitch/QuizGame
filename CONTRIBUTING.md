# Contributing to OpenQuiz 🎯

Thank you for your interest in contributing to **OpenQuiz** — an open-source multiplayer quiz application built with C++ and MySQL! Whether you're fixing a bug, adding a feature, or improving documentation, all contributions are welcome.

---

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Branch Structure](#branch-structure)
- [How to Contribute](#how-to-contribute)
- [Coding Standards](#coding-standards)
- [Commit Message Guidelines](#commit-message-guidelines)
- [Pull Request Process](#pull-request-process)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Features](#suggesting-features)

---

## Code of Conduct

By participating in this project, you agree to be respectful and constructive. Harassment, discrimination, or disruptive behavior of any kind will not be tolerated.

---

## Getting Started

### Prerequisites

Make sure you have the following installed:

- G++ compiler (GCC 9+ recommended)
- MySQL Server and MySQL C API Connector
- Git
- A code editor (VS Code recommended)

### Fork & Clone

```bash
# Fork the repo on GitHub, then clone your fork
git clone https://github.com/YOUR-USERNAME/QuizGame.git
cd QuizGame
```

### Build

```bash
g++ main.cpp -o OpenQuiz
```

### Run

```bash
./OpenQuiz
```

---

## Branch Structure

| Branch           | Purpose                          |
|------------------|----------------------------------|
| `main`           | Stable release branch            |
| `windows-support`| Windows-specific development     |
| `linux-support`  | Linux-specific development       |

> **Never commit directly to `main`.** All changes must go through a Pull Request.

---

## How to Contribute

1. **Fork** the repository and create your feature branch from the appropriate base branch:

```bash
# For a new feature
git checkout -b feature/your-feature-name

# For a bug fix
git checkout -b fix/short-description

# For Windows-specific work
git checkout -b windows-support/your-change
```

2. **Make your changes** following the coding standards below.

3. **Test your changes** — ensure the quiz runs correctly, player scores are stored properly, and the leaderboard displays as expected.

4. **Commit** with a clear message (see guidelines below).

5. **Push** to your fork and open a Pull Request.

---

## Coding Standards

This project follows standard C++ conventions:

- Use **C++17** or later features where appropriate.
- Follow **Object-Oriented Programming (OOP)** principles — keep classes focused and methods small.
- Use **descriptive variable and function names** (`playerScore` not `ps`).
- Add **comments** for non-obvious logic, especially around MySQL queries and leaderboard calculations.
- Keep database queries in separate functions; avoid embedding raw SQL inline in game logic.
- Ensure code compiles **without warnings** on both Windows and Linux.

**Formatting:**
- 4-space indentation (no tabs)
- Opening braces on the same line as the statement
- One blank line between function definitions

---

## Commit Message Guidelines

Use clear, imperative commit messages:

```
feat: add ASCII animation for second-place winner
fix: correct score not saving when player exits early
docs: update setup instructions for Windows
refactor: extract leaderboard logic into separate class
```

Prefix types: `feat`, `fix`, `docs`, `refactor`, `test`, `chore`

---

## Pull Request Process

1. Ensure your branch is up to date with the target branch before opening a PR.
2. Fill in the PR description explaining **what** you changed and **why**.
3. Link any related Issues (e.g., `Closes #12`).
4. Make sure your code builds and runs without errors on your platform.
5. Request a review from the maintainer (`@992501030482-glitch`).
6. Address any review comments and push updates to the same branch.

PRs will be merged once approved by the maintainer.

---

## Reporting Bugs

If you find a bug, please [open an Issue](https://github.com/992501030482-glitch/QuizGame/issues) with:

- A clear, descriptive title
- Steps to reproduce the bug
- Expected vs actual behavior
- Your OS and compiler version (e.g., Windows 11, GCC 12.3)
- Any relevant error output or screenshots

---

## Suggesting Features

Have an idea? [Open an Issue](https://github.com/992501030482-glitch/QuizGame/issues) with the label `enhancement` and describe:

- The feature you'd like
- Why it would be useful for OpenQuiz
- Any implementation ideas you have in mind

---

## Questions?

Feel free to open an Issue with the `question` label if you're stuck or need clarification. We're happy to help!

Happy coding! 🎮