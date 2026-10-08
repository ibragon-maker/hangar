#include "mech.h"

#include <algorithm>
#include <iostream>
#include <utility>

Mech::Mech(std::string name, int hp, int attack, int armor)
    : m_name(std::move(name)), m_hp(hp), m_attack(attack), m_armor(armor) {}

const std::string &Mech::name() const { return m_name; }
int Mech::hp() const { return m_hp; }
int Mech::attack() const { return m_attack; }
int Mech::armor() const { return m_armor; }
bool Mech::is_destroyed() const { return m_hp <= 0; }

void Mech::take_damage(int amount) {
  int damage = std::max(1, amount - m_armor);
  m_hp = std::max(0, m_hp - damage);
}

void Mech::print() const {
  std::cout << m_name << " | HP " << m_hp << " | ATK " << m_attack << " | ARM "
            << m_armor << '\n';
}
