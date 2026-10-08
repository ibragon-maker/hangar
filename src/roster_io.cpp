#include "roster_io.h"

#include <fstream>
#include <sstream>

bool save_roster(const std::vector<Mech>& roster, const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    for (size_t i = 0; i < roster.size(); i++) {
        file << roster[i].name() << ","
             << roster[i].hp() << ","
             << roster[i].attack() << ","
             << roster[i].armor() << "\n";
    }

    return file.good();
}

bool load_roster(const std::string& path, std::vector<Mech>& roster, int& skipped_lines) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::vector<Mech> loaded_mechs;
    skipped_lines = 0;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            skipped_lines++;
            continue;
        }

        std::stringstream ss(line);
        std::string name_str, hp_str, attack_str, armor_str, extra;

        if (!std::getline(ss, name_str, ',') ||
            !std::getline(ss, hp_str, ',') ||
            !std::getline(ss, attack_str, ',') ||
            !std::getline(ss, armor_str, ',') ||
            std::getline(ss, extra, ',')) {
            skipped_lines++;
            continue;
        }

        if (name_str.empty() || hp_str.empty() || attack_str.empty() || armor_str.empty()) {
            skipped_lines++;
            continue;
        }

        std::stringstream hp_ss(hp_str);
        int hp = 0;
        hp_ss >> hp;
        if (hp_ss.fail() || !hp_ss.eof()) {
            skipped_lines++;
            continue;
        }

        std::stringstream attack_ss(attack_str);
        int attack = 0;
        attack_ss >> attack;
        if (attack_ss.fail() || !attack_ss.eof()) {
            skipped_lines++;
            continue;
        }

        std::stringstream armor_ss(armor_str);
        int armor = 0;
        armor_ss >> armor;
        if (armor_ss.fail() || !armor_ss.eof()) {
            skipped_lines++;
            continue;
        }

        if (hp < 1 || attack < 0 || armor < 0) {
            skipped_lines++;
            continue;
        }

        loaded_mechs.push_back(Mech(name_str, hp, attack, armor));
    }

    roster = loaded_mechs;
    return true;
}

bool append_line(const std::string& path, const std::string& text) {
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) {
        return false;
    }

    file << text << "\n";
    return file.good();
}
