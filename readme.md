# nanogit

A minimal, git-compatible version control system written from scratch in C++20.

The goal of this project is to understand git from the inside out by reimplementing the parts that matter: the content-addressable object store, the staging index, refs, and a working subset of porcelain commands. Where possible, nanogit is **byte-compatible with real git** — repositories produced by nanogit can be read by `git`, and vice versa.

> ⚠️ Work in progress. This is a learning project, not a production tool.

## Status

| Feature | Status |
|---|---|
| `init` — create a repository | ✅ done |
| `hash-object` — hash and store a file as a blob | 🚧 in progress |
| `cat-file` — read an object by hash | ⏳ planned |
| `add` — stage a file | ⏳ planned |
| `write-tree` — snapshot the index as a tree | ⏳ planned |
| `commit` — create a commit object | ⏳ planned |
| `log` — walk commits backwards from HEAD | ⏳ planned |
| `status` — compare working dir, index, HEAD | ⏳ planned |
| `diff` — show changes | ⏳ planned |
| `checkout` — restore working dir from a commit | ⏳ planned |
| `branch` — create/list branches | ⏳ planned |
| Fast-forward `merge` | ⏳ planned |

## Why

Git is one of the most-used tools in software, but most engineers (myself included, before this project) treat it as a black box. The internals — how a commit is actually stored, why two identical files share storage, what HEAD really means — are hidden behind the porcelain commands.

This project is an attempt to demystify that. The implementation aims to be small enough to understand in one sitting (target: ~2000 lines) but real enough to be useful: you can `init`, commit, branch, and check out history with it. And the object format is compatible with real git, which means at any point you can run `git status` against a nanogit repo to verify correctness.

## Building

Requires a Linux environment (tested on Ubuntu 22.04 / WSL2) with:

- C++20 compiler (g++ 11+ or clang++ 14+)
- CMake 3.16+
- zlib (`zlib1g-dev`)
- OpenSSL (`libssl-dev`)

```bash
sudo apt install build-essential cmake zlib1g-dev libssl-dev
git clone https://github.com/<your-username>/nanogit.git
cd nanogit
cmake -B build
cmake --build build -j
```

The binary lands at `build/nanogit`.

## Usage

```bash
# Initialize a new repository in the current directory
nanogit init

# Initialize in a specific path
nanogit init my-project
```

More commands coming as the project progresses.

## Git compatibility

A core design goal is to match git's on-disk format byte-for-byte. This enables a powerful sanity check: at any point, you can rename `.nanogit/` to `.git/` and run real `git` commands against the repository.

```bash
mkdir test && cd test
nanogit init
mv .nanogit .git
git status
# On branch main
# No commits yet
# nothing to commit (create/copy files and use "git add" to track)
```

Real git reads nanogit's repository structure. As more commands are implemented, more of git will work against a nanogit repo (and vice versa).

## Architecture

```
src/
├── main.cpp              # CLI entry point and subcommand dispatch
├── repository.{h,cpp}    # repository-level operations (init, path resolution)
├── commands/             # one file per subcommand
│   └── init.{h,cpp}
└── (more to come: object.*, sha1.*, index.*, refs.*)
```

Design principles:

- **One module, one responsibility.** The CLI layer doesn't know about file formats; the object module doesn't know about subcommands.
- **No dynamic memory tricks.** Use the standard library; let RAII and `std::filesystem` do the work.
- **Errors are exit codes, not exceptions.** This is a CLI tool, not a library — error handling is `return 1; std::cerr << ...`.
- **Match git's bytes where it costs nothing.** It costs almost nothing and unlocks free correctness testing.

## Roadmap notes

Out of scope (deliberately, to keep the project achievable):

- Bare repositories
- The packfile format (objects are stored loose only)
- The binary index format — using a simple text format instead
- 3-way merge — only fast-forward merge is planned
- Remote operations (`fetch`, `push`, `clone`)
- Hooks, templates, attributes, gitignore parsing
- Submodules

These are mentioned because *what a project doesn't do* is part of its design.

## References

- Mary Rose Cook, ["Git from the inside out"](https://maryrosecook.com/blog/post/git-from-the-inside-out)
- James Coglan, *Building Git*
- The Pro Git book, [chapter 10 ("Git Internals")](https://git-scm.com/book/en/v2/Git-Internals-Plumbing-and-Porcelain)
- The git source itself: [github.com/git/git](https://github.com/git/git)

## License

MIT
