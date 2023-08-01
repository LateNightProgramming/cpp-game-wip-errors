#include <iostream>
#include <list>
#include <string>
#include <math.h>

namespace settings {
    bool tutorials = true;
    int difficulty = 2;
}

namespace player {
    float health[2] = {0,0};
    float damage;
    std::string name;
    char playerClass;
    int intelligence;
    namespace XP {
        int xp = 0;
        int level = 1;
        int levelUp = 50;
    }
}

class enemy {
    public:
        enemy(float health, float damage, std::string name) {
            float health[2] = {health,health};
            float damage = damage;
            std::string name = name;
        }
};

const std::string possibleNames[4] = {"skeleton","dr phil", "ghost", "sea monster"};

auto randomAccess(auto item, int element) {
    for (int i = 0; i < element; i++) {
        item.pop_front();
    }
    return item.front();
}

bool genericBattle(int enemyCount) {
    std::list <enemy> enemies = {};
    void setup(int enemyCount) {
        for (int i = 0; i < enemyCount; i++) {
            enemies.push_back(enemy(45, 7.5, possibleNames[floor(rand() % 3)]));
        }
    }
    bool battle() {
        std::string inp;
        for (int i = 0; i < enemies.size; i++) {
            std::cout << "\nmonster " << i+1 << " health = " << randomAccess(enemies, i).health[0] << " / " << randomAccess(enemies, i).health[1];
        }
        std::cout << "\nyour health = " << player::health[0] << " / " << player::health[1];
        while (inp != "attack" && inp != "defend" && inp != "do nothing") {
            std::cout << "\ndo you wish to attack, defend or do nothing? ";
            std::cin >> inp;
            if (inp == "attack") {
                int selection;
                while (true) {
                    std::cout  << "\n";
                    try {

                    } catch (...) {

                    }
                }
            } else if (inp == "defend") {

            } else if (inp == "do nothing") {
                std::cout << "\nyou did nothing... why?";
            } else {

            }
        }
    }
    setup(enemyCount);
    if (battle()) {
        return true;
    } else {
        return false;
    }
}

void classSetup(float health, float damage, char playerClass, int intelligence) {
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
                    classSetup(100, floor(20 + (rand() % 5)), "w", 10);
                    break;
                case 2:
                    classSetup(50, 25 + floor((rand() % 5)), "a", 15);
                    break;
                case 3:
                    classSetup(75, 15 + floor((rand() % 5)), "q", 25);
                    break;
                case 4:
                    classSetup(1, 1, "j", 1);
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
                if (hasLooked) {
                    std::cout << "\nyou found nothing";
                } else {
                    std::cout << "\nyou found nothing, but you feel a forboding presence somewhere";
                    hasLooked = true;
                }
            } else if (inp == "door") {
                if (hasLooked) {
                    std::cout << "\nthe door wont open.\nsuddenly you here a a loud, evil noise from behind you; you look behind you and see a large monster!";
                    if (genericBattle(1)) {

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
                std::string inp_2
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
                default:
                    std::cout << "\ninvalid response";
        }
    } 
    while (inp > 4 || inp < 0);
}
