#include<iostream>
#include<string>

class GameObject{
protected:
    int id; // Идентификатор объекта
    std::string name; // имя объекта
    int x; // координаты
    int y; 
public:
    GameObject(int id, const std::string& name, int x, int y)
        : id(id), name(name), x(x), y(y) {}

    int getId() const { return id; } //возвращает идентификатор объекта
    std::string getName() const { return name; } // возвращает имя объекта
    int getX() const { return x; } //где находится объект по X координате
    int getY() const { return y; } //где находится объект по Y координате   
};

class Unit: public GameObject{
protected:
    float hp;
    bool alive;
public:
    Unit(int id, const std::string& name, int x, int y, float hp)
        : GameObject(id, name, x, y), hp(hp), alive(true) {}

    bool isAlive() const { return alive; } //возвращает, жив ли юнит
    float getHp() const { return hp; } //возвращает количество здоровья у юнита

    void receiveDamage(float damage) { //метод, который вызывается для получения урона этим юнитом
        hp -= damage;
        if (hp <= 0) {
            alive = false;
        }
    } 
};

class Attacker {
public:
    virtual void attack(Unit& unit) = 0;
};

class Moveable {
public:
    virtual void move(int newX, int newY) = 0;
};

class Archer : public Unit, public Attacker, public Moveable {
public:
    Archer(int id, const std::string& name, int x, int y, float hp)
        : Unit(id, name, x, y, hp) {}

    void attack(Unit& unit) override {
         if (isAlive() && unit.isAlive()) {
            std::cout << getName() << " атакует " << unit.getName() << "!" << std::endl;
        }
    }

    void move(int newX, int newY) override {
        x = newX;
        y = newY;
        std::cout << getName() << " перемещается в точку (" << x << ", " << y << ")." << std::endl;
    }
};

class Building : public GameObject {
protected:
    bool built;

public:
    Building(int id, const std::string& name, int x, int y)
        : GameObject(id, name, x, y), built(false) {}

    bool isBuilt() const { return built; }

    void construct() {
        built = true;
        std::cout << name << " построена!" << std::endl;
    }
};

class Fort : public Building, public Attacker {
public:
    Fort(int id, const std::string& name, int x, int y)
        : Building(id, name, x, y) {}

    void attack(Unit& unit) override {
        if (isBuilt() && unit.isAlive()) {
            std::cout << getName() << " стреляет по " << unit.getName() << "!" << std::endl;
        }
    }
};

class MobileHouse : public Building, public Moveable {
public:
    MobileHouse(int id, const std::string& name, int x, int y)
        : Building(id, name, x, y) {}

    void move(int newX, int newY) override {
        x = newX;
        y = newY;
        std::cout << getName() << " перемещается в точку (" << x << ", " << y << ")." << std::endl;
    }
};