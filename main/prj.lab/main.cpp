#include "laba2.hpp"
#include <iostream>

int main() {
    Archer archer(1, "Лучник", 0, 0, 100);
    Unit enemy(2, "Враг", 1, 1, 50);
    Fort fort(3, "Крепость", 2, 2);
    MobileHouse mobileHouse(4, "Подвижный дом", 3, 3);

    fort.construct();
    fort.attack(enemy);
    archer.attack(enemy);
    mobileHouse.construct();
    mobileHouse.move(10,10);
    archer.move(1, 2);

    enemy.receiveDamage(20);
    std::cout << enemy.getHp();
    return 0;
}

