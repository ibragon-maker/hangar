#ifndef HANGAR_MECH_H
#define HANGAR_MECH_H

#include <string>

/// A single combat mech. Provided for you; do not modify this week.
class Mech {
public:
  Mech(std::string name, int hp, int attack, int armor);

  const std::string &name() const;
  int hp() const;
  int attack() const;
  int armor() const;
  bool is_destroyed() const;

  /// Reduces hp by (amount - armor), minimum 1 damage per hit. hp never drops
  /// below 0.
  void take_damage(int amount);

  /// Prints one line: name | HP | ATK | ARM
  void print() const;

private:
  std::string m_name;
  int m_hp;
  int m_attack;
  int m_armor;
};

#endif
