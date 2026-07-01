#!/usr/bin/env python3
"""
generate_docs.py

Regenerates CHANGELOG.md and CONTRIBUTORS.md from the current repository's
git history. Designed to be run in CI (see .github/workflows/update-docs.yml)
on every push to main, but works fine run locally too.

Usage:
    python3 scripts/generate_docs.py
"""

import subprocess
import re
from collections import defaultdict, OrderedDict
from datetime import datetime

REPO_URL = "https://github.com/992501030482-glitch/QuizGame"


def run(cmd):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True, check=True).stdout


def get_commits():
    """Return list of commit dicts in reverse-chronological order."""
    fmt = "%H%x01%an%x01%ae%x01%ad%x01%s%x01%P"
    raw = run(f'git log --all --date=format:"%Y-%m-%d %H:%M:%S %z" --pretty=format:"{fmt}"')
    commits = []
    for line in raw.strip().split("\n"):
        if not line:
            continue
        h, author, email, date, subject, parents = line.split("\x01")
        commits.append({
            "hash": h,
            "author": author,
            "email": email,
            "date": date,
            "subject": subject,
            "is_merge": len(parents.split()) > 1,
        })
    return commits


def dedupe_identity(email):
    """Merge known duplicate git identities that share the same email."""
    return email.strip().lstrip('"\u201d').strip()


def generate_contributors(commits):
    stats = defaultdict(lambda: {"commits": 0, "name": "", "modules": set()})

    for c in commits:
        if c["is_merge"]:
            continue
        key = dedupe_identity(c["email"])
        stats[key]["commits"] += 1
        # keep the most "human" looking name (prefer names with a space)
        if " " in c["author"] and " " not in stats[key]["name"]:
            stats[key]["name"] = c["author"]
        elif not stats[key]["name"]:
            stats[key]["name"] = c["author"]

    ranked = sorted(stats.items(), key=lambda kv: kv[1]["commits"], reverse=True)

    lines = []
    lines.append("# Contributors\n")
    lines.append(
        "This file is auto-generated from the repository's git history. "
        "Do not edit manually — update `scripts/generate_docs.py` instead.\n"
    )
    lines.append(f"_Last generated: {datetime.utcnow().strftime('%Y-%m-%d %H:%M UTC')}_\n")
    lines.append("## Core Team\n")
    lines.append("| Name | Email | Commits |")
    lines.append("|---|---|---|")
    for email, data in ranked:
        lines.append(f"| {data['name']} | {email} | {data['commits']} |")

    total_commits = sum(d["commits"] for _, d in ranked)
    lines.append("")
    lines.append(f"**Total tracked commits:** {total_commits}")
    lines.append(f"**Total contributors:** {len(ranked)}")
    lines.append("")

    return "\n".join(lines)


def generate_changelog(commits):
    non_merge = [c for c in commits if not c["is_merge"]]
    merges = [c for c in commits if c["is_merge"]]

    by_date = OrderedDict()
    for c in non_merge:
        day = c["date"].split(" ")[0]
        by_date.setdefault(day, {"added": [], "merged": []})
        by_date[day]["added"].append(c)

    for c in merges:
        day = c["date"].split(" ")[0]
        by_date.setdefault(day, {"added": [], "merged": []})
        by_date[day]["merged"].append(c)

    ordered_days = sorted(by_date.keys(), reverse=True)

    lines = []
    lines.append("# Changelog\n")
    lines.append(
        "This file is auto-generated from the repository's git history on "
        "every push to `main`. Do not edit manually.\n"
    )
    lines.append(
        "Format loosely follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/). "
        "Entries are grouped by date until the project adopts semantic version tags.\n"
    )

    for day in ordered_days:
        lines.append(f"## {day}\n")
        entry = by_date[day]
        if entry["added"]:
            lines.append("### Changes")
            for c in entry["added"]:
                short = c["hash"][:7]
                subject = re.sub(r"\s+", " ", c["subject"]).strip()
                lines.append(f"- {subject} ({short} — {c['author']})")
            lines.append("")
        if entry["merged"]:
            lines.append("### Merged")
            for c in entry["merged"]:
                subject = re.sub(r"\s+", " ", c["subject"]).strip()
                lines.append(f"- {subject}")
            lines.append("")

    return "\n".join(lines)


def main():
    commits = get_commits()

    with open("CHANGELOG.md", "w") as f:
        f.write(generate_changelog(commits))

    with open("CONTRIBUTORS.md", "w") as f:
        f.write(generate_contributors(commits))

    print(f"Regenerated CHANGELOG.md and CONTRIBUTORS.md from {len(commits)} commits.")


if __name__ == "__main__":
    main()