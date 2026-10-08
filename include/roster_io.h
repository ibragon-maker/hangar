#ifndef HANGAR_ROSTER_IO_H
#define HANGAR_ROSTER_IO_H

#include <string>
#include <vector>

#include "mech.h"

/*
 * FILE FORMAT (data/roster.csv)
 * One mech per line:   name,hp,attack,armor
 *   Example:           Old Faithful,120,30,10
 *   - name may contain spaces but never a comma, and cannot be empty
 *   - hp must be at least 1; attack and armor must be 0 or greater
 *   - exactly 4 fields per line, all numbers must be whole numbers
 */

/// Writes every mech in roster to the file at path, one per line, replacing
/// whatever was there before.
/// @return true if the file was opened and written successfully, false otherwise.
bool save_roster(const std::vector<Mech>& roster, const std::string& path);

/// Reads mechs from the file at path.
/// - If the file cannot be opened: return false and leave roster unchanged.
/// - Otherwise: roster is replaced with the valid mechs found, skipped_lines is
///   set to the number of lines that were NOT valid records, and true is returned.
/// A line is invalid if it breaks any rule in the file format above.
bool load_roster(const std::string& path, std::vector<Mech>& roster, int& skipped_lines);

/// Adds text as one new line at the END of the file at path. Existing content
/// must be kept. The file is created if it does not exist.
/// @return true if the line was written, false otherwise.
bool append_line(const std::string& path, const std::string& text);

#endif
