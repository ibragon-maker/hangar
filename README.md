# Mech Hangar

A command-line garage for your combat mechs. 

## Persistent Roster

Your job this week is to make the roster survive a restart by writing the file-handling
code in `src/roster_io.cpp`. Everything else is provided.

### Build and run

```
cmake -S . -B build
cmake --build build
./build/hangar
```

### Self-check

```
./build/check_io
```

Each line is PASS or FAIL. Passing everything is strong evidence your functions work,
but the rubric on Canvas also grades code quality and your commits.

### Files you edit

| File | What to do |
|---|---|
| `src/roster_io.cpp` | Implement `save_roster`, `load_roster`, `append_line` |
| `app/main.cpp` | Fill in the `TODO` blocks (menu options 3, 4, and 5) |

### Files you do not edit

`src/mech.cpp`, `include/mech.h`, `src/battle_sim.cpp`, `include/battle_sim.h`, `include/roster_io.h`, `tests/`, `CMakeLists.txt`

### Data files

| File | Purpose |
|---|---|
| `data/roster.csv` | Your saved roster. Reset it with `git checkout -- data/roster.csv` |
| `data/corrupt_roster.csv` | Test file full of bad lines. Do not edit |
| `data/battle_log.txt` | Created by your program (Checkpoint 4) |
| `data/graveyard.txt` | Created by your program (Checkpoint 4) |

### Commits

Conventional Commits, composed in your editor. At least one commit per checkpoint,
for example `feat(roster): save roster to file`.
