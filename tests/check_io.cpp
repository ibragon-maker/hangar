// Self-check for roster_io. Run from anywhere:  ./build/check_io
// This does not replace testing the real program; it only checks the basics.

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "mech.h"
#include "roster_io.h"

#ifndef HANGAR_DATA_DIR
#define HANGAR_DATA_DIR "data"
#endif

namespace {

int checks_run = 0;
int checks_passed = 0;

void check(bool condition, const std::string& label) {
    ++checks_run;
    if (condition) {
        ++checks_passed;
        std::cout << "  PASS  " << label << '\n';
    } else {
        std::cout << "  FAIL  " << label << '\n';
    }
}

std::vector<std::string> read_lines(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    return lines;
}

void write_text(const std::string& path, const std::string& text) {
    std::ofstream out(path);
    out << text;
}

}  // namespace

int main() {
    const std::string data_dir = HANGAR_DATA_DIR;
    const std::string temp_path = data_dir + "/_check_tmp.txt";
    std::remove(temp_path.c_str());

    std::cout << "Checkpoint 1: save_roster\n";
    std::vector<Mech> roster = {Mech("Old Faithful", 120, 30, 10), Mech("Gizmo", 80, 45, 5)};
    bool saved = save_roster(roster, temp_path);
    check(saved, "save_roster returns true for a writable path");
    std::vector<std::string> lines = read_lines(temp_path);
    check(lines.size() == 2, "file has one line per mech");
    check(lines.size() == 2 && lines[0] == "Old Faithful,120,30,10", "line 1 matches the format exactly");
    check(lines.size() == 2 && lines[1] == "Gizmo,80,45,5", "line 2 matches the format exactly");
    check(!save_roster(roster, data_dir + "/no_such_folder/roster.csv"),
          "save_roster returns false when the file cannot be opened");

    std::cout << "Checkpoint 2: load_roster (valid data)\n";
    std::vector<Mech> loaded;
    int skipped = -1;
    bool ok = load_roster(temp_path, loaded, skipped);
    check(ok, "load_roster returns true for an existing file");
    check(loaded.size() == 2, "loads 2 mechs");
    check(skipped == 0, "reports 0 skipped lines");
    check(loaded.size() == 2 && loaded[0].name() == "Old Faithful" && loaded[0].hp() == 120 &&
              loaded[0].attack() == 30 && loaded[0].armor() == 10,
          "first mech round-trips exactly (name with a space, all stats)");
    check(loaded.size() == 2 && loaded[1].name() == "Gizmo" && loaded[1].hp() == 80,
          "second mech round-trips exactly");

    std::cout << "Checkpoint 3: failure handling\n";
    std::vector<Mech> untouched = {Mech("Keeper", 50, 10, 1)};
    int skipped_missing = -1;
    bool missing_ok = load_roster(data_dir + "/does_not_exist.csv", untouched, skipped_missing);
    check(!missing_ok, "missing file returns false");
    check(untouched.size() == 1 && untouched[0].name() == "Keeper",
          "missing file leaves the roster unchanged");

    std::vector<Mech> from_corrupt;
    int corrupt_skipped = -1;
    bool corrupt_ok = load_roster(data_dir + "/corrupt_roster.csv", from_corrupt, corrupt_skipped);
    check(corrupt_ok, "corrupt file still returns true (file opened)");
    check(from_corrupt.size() == 2, "loads exactly the 2 valid mechs");
    check(corrupt_skipped == 5, "reports exactly 5 skipped lines");
    check(from_corrupt.size() == 2 && from_corrupt[0].name() == "Aegis" &&
              from_corrupt[1].name() == "Viper",
          "the valid mechs are Aegis and Viper");

    write_text(temp_path, "Ember,100abc,30,10\nSpark,50,10,5\n");
    std::vector<Mech> from_garbage;
    int garbage_skipped = -1;
    load_roster(temp_path, from_garbage, garbage_skipped);
    check(from_garbage.size() == 1 && garbage_skipped == 1,
          "a number with trailing letters (100abc) is rejected");

    std::cout << "Checkpoint 4: append_line\n";
    std::remove(temp_path.c_str());
    bool first = append_line(temp_path, "first entry");
    bool second = append_line(temp_path, "second entry");
    check(first && second, "append_line returns true");
    std::vector<std::string> log_lines = read_lines(temp_path);
    check(log_lines.size() == 2, "two appends produce two lines (nothing overwritten)");
    check(log_lines.size() == 2 && log_lines[0] == "first entry" && log_lines[1] == "second entry",
          "lines are complete and in order");

    std::remove(temp_path.c_str());
    std::cout << "\n" << checks_passed << " of " << checks_run << " checks passed.\n";
    return checks_passed == checks_run ? 0 : 1;
}
