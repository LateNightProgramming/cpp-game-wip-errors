#include <iostream>
#include <list>
#include <string>
#include <math.h>

namespace settings {
    bool tutorials = true;
    int difficulty = 2;
    bool clean = false;
}

namespace player {
    float health[2] = {0,0};
    int damage;
    std::string name;
    char playerClass;
    int intelligence;
    namespace defense {
        int maxDefense = 5;
        int tempMaxDefense = maxDefense;
        int currentDefense = 0;
    }
    namespace XP {
        int xp = 0;
        int level = 1;
        int levelUp = 50;
    }
}

class enemy {
    public:
        enemy(float givenHealth, float givenDamage, std::string givenName) {
            float health[2] = {givenHealth,givenHealth};
            float damage = givenDamage;
            std::string name = givenName;
        }
};

const std::string possibleNames[4] = {"skeleton","dr phil", "ghost", "sea monster"};

auto randomAccess(auto item, int element) {
    for (int i = 0; i < element; i++) {
        item.pop_front();
    }
    return item.front();
}

namespace battleFuncs {
    auto removeAll(auto item) {
        for (int i = 0; i < item.size(); i++) {
            item.pop_front();
        }
        return item;
    }
    auto isDead(auto item, int element) {
        auto deletedItems = battleFuncs::removeAll(item);
        for (int i = 0; i < element-1; i++) {
            deletedItems.push_back(item.front());
            item.pop_front();
        }
        item.pop_front();
        for (int i = 0; i < deletedItems.size(); i++) {
            item.push_front(deletedItems.back());
            deletedItems.pop_back();
        }
        return item;
    }
}

std::string sanitize(std::string item) {
    if (settings::clean) {

    } 
    return item;
}

std::list <enemy> setup(int enemyCount,std::list <enemy> enemies) {
        for (int i = 0; i < enemyCount; i++) {
            enemies.push_back(enemy(45, 7.5, possibleNames[floor(rand() % 3)]));
        }
        return enemies;
}

bool battle(bool defending, std::list <enemy> enemies) {
    std::string inp;
    if (defending) {
        defending = false;
        player::defense::currentDefense = 0;
    }
    for (int i = 0; i < enemies.size(); i++) {
        std::cout << "\nmonster " << i+1 << " health = " << randomAccess(enemies, i).health[0] << " / " << randomAccess(enemies, i).health[1];
    }
    std::cout << "\nyour health = " << player::health[0] << " / " << player::health[1];
    while (inp != "attack" && inp != "defend" && inp != "do nothing") {
        std::cout << "\ndo you wish to attack, defend or do nothing? ";
        std::cin >> inp;
        if (inp == "attack") {
            int selection;
            while (true) {
                std::cout  << "\nwhich enemy do you wish to attack? (please use the number of the enemy)";
                try {
                    std::cin >> selection;
                    if (selection > enemies.size()) {
                        throw 0;
                    } else {
                        break;
                    }
                } catch (...) {
                    std::cout << "\n";
                }
            }
        } else if (inp == "defend") {
            player::defense::currentDefense = player::defense::tempMaxDefense;
            defending = true;
        } else if (inp == "do nothing") {
            std::cout << "\nyou did nothing... why?";
        } else {
            std::cout << "\ninvalid response";
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (floor(rand() % 1) == 0) {
            player::health -= randomAccess(enemies,i).damage;
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (randomAccess(enemies,i).health[0] <= 0) {
            enemies = battleFuncs::isDead(enemies,i);
        }
    }
    if (enemies.size() == 0) {
        return true;
    } else if (player::health[0] <= 0.0) {
        return false;
    }
}

bool genericBattle(int enemyCount) {
    std::list <enemy> enemies = {};
    bool defending = false;
    enemies = setup(enemyCount,enemies);
    return battle(defending, enemies);
}

void classSetup(float health, int damage, char playerClass, int intelligence) {
    player::health[0] = player::health[1] = health;
    player::damage = damage;
    player::playerClass = playerClass;
    player::intelligence = intelligence;                  
}

void intro() {
    std::cout << "\nyou wake up in a dark room, you dont remember who you are.\nenter your name: ";
    std::cin >> player::name;
    {
        int inp;
        do {
            std::cout << "\nplease select a class [1] warrior, [2] archer, [3] wizard, [4] jimmy kimmel: ";
            try {
                std::cin >> inp;
            } catch (...) {
                inp = 999;
            }
            srand(time(0));
            switch (inp) {
                case 1:
                    classSetup(100.0, floor(20 + (rand() % 5)), "w", 10);
                    break;
                case 2:
                    classSetup(50.0, 25 + floor((rand() % 5)), "a", 15);
                    break;
                case 3:
                    classSetup(75.0, 15 + floor((rand() % 5)), "q", 25);
                    break;
                case 4:
                    classSetup(1.0, 1, "j", 1);
                    break;
                default:
                    std::cout << "\ninvalid response";
            }
        }
        while (inp > 4 || inp < 1);
    }
    std::cout << "\nyou look around the room, theres nothing but a door and a bed";
    {
        bool hasLook = false;
        std::string inp;
        while (true) {
            std::cout << "\ndo you wish to look [bed] under the bed or [door] open the door? ";
            std::cin >> inp;
            if (inp == "bed") {
                if (hasLook) {
                    std::cout << "\nyou found nothing";
                } else {
                    std::cout << "\nyou found nothing, but you feel a forboding presence somewhere";
                    hasLook = true;
                }
            } else if (inp == "door") {
                if (hasLook) {
                    std::cout << "\nthe door wont open.\nsuddenly you here a a loud, evil noise from behind you; you look behind you and see a large monster!";
                    if (genericBattle(1)) {
                        std::cout << "\nyou slayed the monster!";
                        break;
                    } else {
                        death();
                    }
                } else {
                    std::cout << "\nthe door wont open";
                }
            } else {
                std::cout << "\ninvalid response";
            }
        }
    }
    std::cout << "\nyou noticed the mosnter busted a whole in the wall, you walk outside to the clean air outside\nthis is the end of the demo lmao";
}

int main() {
    std::cout << "welcome!";
    int inp;
    do {
        std::cout << "\ndo you wish to [1] start, [2] quit or [3] change settings? ";
        try {
            std::cin >> inp;
        } catch (...) {
            inp = 5;
        }
        switch (inp) {
            case 1:
                std::cout << "\nstarting...";
                intro();
                return 0;
                break;
            case 2:
                std::cout << "\nquitting...";
                return 0;
                break;
            case 3:
                std::string inp_2;
                while (true) {
                    std::cout << "\ndo you wish to turn tutorials on or off? ";
                    std::cin >> inp_2;
                    if (inp_2 == "off") {
                        std::cout << "\ntutorials off";
                        settings::tutorials = false;
                        break;
                    } else if (inp_2 == "on") {
                        std::cout << "\ntutorials on";
                        settings::tutorials = true;
                        break;
                    } else {
                        std::cout << "\ninvalid response";
                    }
                }
                break;
            default:
                std::cout << "\ninvalid response";
        }
    } 
    while (inp > 4 || inp < 0);
}
