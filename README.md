Orbit is a programming language that provides shell-style utilities — not a modern interactive shell. It’s designed for writing programs that use shell-like commands as composable, typed primitives (with an emphasis on .pipe() and exec(...).arg(...)). Orbit combines an object-oriented syntax, file operations (fs module), Git/http utilities, and an LLVM JIT backend for performance. Note: Orbit does not aim to be POSIX-compatible.

Badges ![License](./LICENSE) ![Contributions Welcome](https://img.shields.io/badge/contributions-welcome-green.svg)

Table of Contents

Features
Quick Start
Installation
Usage
Configuration
Development
Contributing
License
Features

Programming-language-first design with shell utilities (not an interactive shell).
Composable command pipelines via .pipe().
Clear command API: exec(Array[String]).arg(Array[String]).
File-system utilities via fs module.
Git and network utilities via the got / git modules.
LLVM JIT for execution speed.
Designed for embedding in programs and scripts.
Quick Start

Fork the repo and clone: git clone https://github.com/The-Coding-Decoders/Orbit.git cd Orbit

Install dependencies (development): python -m pip install -e .

Or, to install from PyPI (replace with the actual package name if published): python -m pip install orbit

Run the REPL or main entry (example — replace with actual entrypoint if different): python -m orbit

Run tests: python -m pip install -r requirements-dev.txt pytest

Installation

Local development: python -m pip install -e .

From PyPI (replace package name if different): python -m pip install orbit

Docker example: docker build -t orbit . docker run -it --rm orbit

Usage Orbit exposes a composable exec API and a .pipe() method to build pipelines programmatically. The canonical API shape is exec(Array[String]).arg(Array[String]) and pipeline chaining with .pipe().

Examples:

Simple command with arguments from orbit import exec proc = exec(["git"]).arg(["status", "--porcelain"]) result = proc.run() print(result.stdout)

Pipeline: cat file.txt | grep 'TODO' | wc -l from orbit import exec pipeline = exec(["cat"]).arg(["file.txt"])
.pipe(exec(["grep"]).arg(["TODO"]))
.pipe(exec(["wc"]).arg(["-l"])) result = pipeline.run() print(result.stdout)

Using fs utilities (read a file) from orbit import fs content = fs.read("notes.txt") print(content)

Notes

This is a programming environment: use Orbit’s API to construct, inspect, and run pipelines from code. It is not intended as a drop-in replacement for interactive shells like bash/zsh with their POSIX features.
Commands and arguments are passed as arrays of strings for clarity and safety: exec(["cmd", "subcmd"]).arg(["--flag", "value"]).
Development

Install dev requirements: python -m pip install -r requirements-dev.txt

Run linters and type checks:

example; adjust to the project's tools
ruff check . mypy .

Run tests: pytest

Contributing We ❤️ contributions — see CONTRIBUTING.md for guidelines.

License This project is licensed under the Apache License 2.0 — see the LICENSE file for details.

Maintainers

The-Coding-Decoders (https://github.com/The-Coding-Decoders
