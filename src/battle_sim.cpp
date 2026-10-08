#include "battle_sim.h"

#include <ctime>
#include <random>
#include <vector>

namespace {

int random_int(int low, int high) {
    static std::mt19937 engine{std::random_device{}()};
    std::uniform_int_distribution<int> dist(low, high);
    return dist(engine);
}

}  // namespace

Mech make_random_mech() {
    const std::vector<std::string> names = {
        "Rust Bucket", "Old Faithful", "Iron Widow", "Tin Titan", "Gizmo",
        "Mauler", "Scrapper", "Bolt Cutter", "Night Owl", "Big Gerald",
        "Static", "Hammerhead"};
    const std::string& name = names[random_int(0, static_cast<int>(names.size()) - 1)];
    return Mech(name, random_int(60, 200), random_int(15, 50), random_int(0, 20));
}

DuelResult simulate_duel(Mech& player, Mech& challenger) {
    const int hp_before = player.hp();
    int rounds = 0;

    while (!player.is_destroyed() && !challenger.is_destroyed()) {
        ++rounds;
        challenger.take_damage(player.attack() + random_int(0, 9));
        if (challenger.is_destroyed()) {
            break;
        }
        player.take_damage(challenger.attack() + random_int(0, 9));
    }

    DuelResult result;
    result.player_won = !player.is_destroyed();
    result.rounds = rounds;
    result.opponent_name = challenger.name();
    result.summary = player.name() + " (hp " + std::to_string(hp_before) + " -> " +
                     std::to_string(player.hp()) + ") " +
                     (result.player_won ? "beat " : "lost to ") + challenger.name() +
                     " in " + std::to_string(rounds) + (rounds == 1 ? " round" : " rounds");
    return result;
}

std::string timestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    if (local == nullptr) {
        return "unknown-time";
    }
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    return buffer;
}
