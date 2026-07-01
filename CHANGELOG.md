# Changelog

All notable changes to **OpenQuiz** (QuizGame) are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).
This project has not yet cut a formal semantic-versioned release, so entries
are grouped by development date and pull request rather than version number.
Once the project reaches a stable v1.0.0, this file will switch to
[Semantic Versioning](https://semver.org/).

---

## [Unreleased]

### Added
- Windows-specific build path with dedicated `main.c` entry point and headers (PR-pending, `windows` / `WinQuiz` branches).
- `CONTRIBUTING.md` outlining the contribution workflow for the project (PR #13).

---

## 2026-06-30

### Merged
- **PR #13** — `maharshi_main` → `main`: introduced `CONTRIBUTING.md` (169 lines) documenting the contribution process.

---

## 2026-06-29

### Added
- Leaderboard functionality extended in the Windows build (`main.c`).
- Indentation and formatting corrections applied across the Windows codebase.

### Changed
- `CONTRIBUTING.md` added as a new project document.

---

## 2026-06-27 – 2026-06-28

### Added
- `About` function added to the CLI quiz flow.
- `Question` function implemented for question presentation/handling.
- Windows build (`main.c`) updated with additional `main` logic and headers.
- Leaderboard functionality added to the Windows branch (`satyam-WinQuiz`).

---

## 2026-06-26

### Added
- Initial Windows-version scaffolding: required headers and function stubs for a Windows-compatible build.

### Merged
- **PR #9** — `satyam` → `main`: updates to `int main()` entry logic.
- **PR #8** — `leader` → `main`: leaderboard function added.
- **PR #7** — `maharshicodes` → `main`: `TimedQuiz` class introduced with `startQuiz()` functionality.

### Removed
- Duplicate/legacy `main.cpp` content removed from the Windows edition (225 lines removed) to eliminate divergence between platform builds.

### Changed
- `README.md` restructured and updated to meet documentation requirements.

---

## 2026-06-25

### Added
- `Player` class introduced, encapsulating player identity and score data.
- `addPlayers()` function implemented to register multiple players at quiz start.
- Project poster image (`assets/readme-poster.png`) added and linked in `README.md`.
- Additional MySQL database setup (schema/connection groundwork extended).

### Changed
- Updated code relocated/consolidated into the main `QuizGame` project structure.
- `README.md` updated with project overview content.

### Removed
- Duplicate code removed from the core game logic file.

### Merged
- **PR #6** — `test-Atlas` → `main`: repository cleanup, verified build with no compile errors.
- **PR #3** — `DIPESH_work` → `main`: player class and README poster integration.
- **PR #1** — `satyam` → `main`: `README.md` update.
- **PR #2** — `ananya-branch` → `main`: additional database setup.

---

## 2026-06-24

### Added
- `QuizGame` class introduced (extends `Database`), including:
  - `setupDatabase()` — creates the `quiz` database and `score` table (`id`, `name`, `score`, `time`).
  - `addPlayers(int n)` — inserts player names into the `score` table via parameterized query construction.

### Changed
- Iterative revisions to `main.cpp` while stabilizing the initial database-integration logic (added, then reverted, then re-added in refined form).

---

## 2026-06-23

### Added
- **Project initialized** — first commit establishing `README.md`.
- MIT `LICENSE` added.
- Initial MySQL connectivity layer: `Database` class with `connect()`, `getConn()`, and RAII-style constructor/destructor managing the `MYSQL*` connection handle.

---

## Notes on Repository Activity

- **Branches used during development:** `main`, `windows`, `WinQuiz`, `winquiz`, `satyam-WinQuiz`, `maharshicodes`, `maharshi_main`, `DIPESH_work`, `ananya-winquiz`, `ananya-branch`, `leader`, `satyam`, `test-Atlas`.
- **Pull requests merged to `main`:** #1, #2, #3, #6, #7, #8, #9, #13.
- Development has occurred primarily through short-lived feature branches merged via pull request, consistent with the project's open-source collaborative workflow.

[Unreleased]: https://github.com/992501030482-glitch/QuizGame/compare/main...HEAD
