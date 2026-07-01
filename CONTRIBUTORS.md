# Contributors

This project follows an open-source collaborative development model. The
table below lists all contributors to **OpenQuiz (QuizGame)**, derived
directly from the repository's commit history, along with their primary
areas of responsibility.

> Note: Two contributors committed under two different local Git identities
> that resolve to the same email address. These have been merged into a
> single entry below for accuracy (Aditya Kumar Singh /
> `992501030482-glitch`, and Satyam Shekhar / `992501030278-afk`).

## Core Team

| Name | GitHub Identity | Commits | Role | Primary Responsibilities |
|---|---|---|---|---|
| Aditya Kumar Singh | `992501030482-glitch` | 16 | Project Lead / Repository Maintainer | Repository creation, `LICENSE`, MySQL connection layer bootstrap, pull request review & merging (PRs #1, #2, #3, #6, #7, #8, #9, #13), Windows-edition build path, indentation/formatting fixes |
| DIPESHCHOUDHARY-CODES (Dipesh Choudhary) | `DIPESHCHOUDHARY-CODES` | 7 | Core Gameplay Developer | `Player` class design, `addPlayers()` implementation, code consolidation into main project structure, duplicate-code cleanup, README poster integration |
| Maharshi Paul | — | 6 | Database & Documentation Lead | `Database`/`QuizGame` class with MySQL schema setup (`setupDatabase()`), `TimedQuiz` class with `startQuiz()`, `CONTRIBUTING.md` authorship, README updates |
| Satyam Shekhar | `992501030278-afk` | 5 | Backend Developer | Leaderboard functionality, `main()` entry-point logic updates, README content contributions |
| Disha | — | 3 | Feature Developer | `Question` function (question presentation/handling), `About` function, leaderboard function implementation |
| Ananya | `ananya2501020074` | 3 | Cross-Platform / Windows Support | Windows-specific `main` build updates, additional MySQL database setup and configuration |

## Contribution Summary

| Contributor | Commits | Modules Owned | Notes |
|---|---|---|---|
| Aditya Kumar Singh | 16 | Repository infrastructure, `LICENSE`, Windows build, merge management | Authored/merged 8 of 8 tracked pull requests |
| Dipesh Choudhary | 7 | `Player` class, player registration logic | Active on `DIPESH_work` branch |
| Maharshi Paul | 6 | Database layer, `TimedQuiz` class, `CONTRIBUTING.md` | Active on `maharshicodes`, `maharshi_main` branches |
| Satyam Shekhar | 5 | Leaderboard logic, `main()` control flow | Active on `satyam`, `satyam-WinQuiz` branches |
| Disha | 3 | Question handling, About screen, leaderboard | Contributed via `leader` branch |
| Ananya | 3 | Windows build compatibility, DB setup | Active on `ananya-branch`, `ananya-winquiz`, `windows` branches |

**Total tracked commits:** 40
**Total merged pull requests:** 8 (#1, #2, #3, #6, #7, #8, #9, #13)
**Total contributors:** 6

## How to Become a Contributor

We welcome contributions from the community. Please review
[CONTRIBUTING.md](./CONTRIBUTING.md) for guidelines on branching conventions,
commit message standards, and the pull request review process before
submitting changes.

## Acknowledgements

Thanks to all contributors above for their work across the database layer,
core gameplay logic, cross-platform build support, and documentation that
make up OpenQuiz.