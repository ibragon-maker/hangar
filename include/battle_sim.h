#ifndef HANGAR_BATTLE_SIM_H
#define HANGAR_BATTLE_SIM_H

#include <string>

#include "mech.h"

/// The outcome of one duel. Provided for you; do not modify this week.
struct DuelResult {
    bool player_won;
    int rounds;
    std::string opponent_name;
    std::string summary;  ///< One line, no newline. Example: "Rust Bucket (hp 120 -> 34) beat Gizmo in 7 rounds"
};

/// Builds a mech with a random name and random stats.
Mech make_random_mech();

/// Fights player vs. challenger until one is destroyed.
/// NOTE: this changes the player's hp. The damage stays on the mech.
DuelResult simulate_duel(Mech& player, Mech& challenger);

/// Current local time as "YYYY-MM-DD HH:MM:SS".
std::string timestamp();

#endif
