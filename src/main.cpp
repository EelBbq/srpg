// //vulkan setup
// #include <vulkan/vulkan.h>

// #define GLFW_INCLUDE_VULKAN
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>

// #include <array>
// #include <stdexcept>
// #include <algorithm>
// #include <vector>
// #include <cstring>
// #include <cstdlib>
// #include <cstdint>
// #include <limits>
// #include <optional>
// #include <set>
//#include <iostream>

// //pipeline
// #include <fstream>

//game
#include <iostream>
#include "Fighter.h"
#include "Battlefield.h"

#include <stdio.h> //Null
#include <stdlib.h> //srand, rand
#include <time.h>   //time



double randomVal() {
    srand(time(NULL));
    
    double val = (rand() % 100) / 100;
    return val;
}

int battle(Fighter* fighter1, Fighter* fighter2) {
    int damage;
    int atk;            //offensive strength f1
    int def;            //defensive strength f2
    double critVal1;    //offensive crit value f1
    double critVal2;    //defensive crit value f2
    int critMod = 3;    //the damage multiplier in the case of critical hits
    double critThresh = randomVal();    //the randomly rolled threshhold that crit % has to beat in order to crit
    bool crit;          //whether the attack crits or not

    //derrives atk and defense from fighter stats
    atk = (fighter1->getStr()) +  (fighter1->getAgi());
    atk = atk * .75;
    def = (fighter2->getCon());
    
    //is crit?
    critVal1 = (fighter1->getAgi()) + (fighter1->getLuk()); 
    critVal2 = 0.75 * ((fighter2->getAgi()) + ((fighter2->getLuk()) + (fighter2->getFai())));
    crit = critThresh < (critVal1 - critVal2);

    damage = atk - def;

    if(crit){
        damage = critMod * damage;
        std::cout << "critical hit!";
    }
    if(damage < 0){
        damage = 0;
    }
        
    fighter2->applyDamage(damage);
    
    return damage;
}




int main() {

    // HelloTriangleApplication app;

    // try {
    //     app.run();
    // } catch (const std::exception& e) {
    //     std::cerr << e.what() << std::endl;
    //     return EXIT_FAILURE;
    // }

    //fighter 1 and 2
    // Fighter* f1;
    // Fighter* f2;
    // Fighter* f3;

    // f1 = new Fighter();
    // f2 = new Fighter();
    // f3 = new Fighter("Amogus Test", 18, 14, 12, 11, 11, 11, false);

    // std::cout << f3->toString();


    Battlefield* battleMap = new Battlefield();
    battleMap->testDikjstras();
    // battleMap->addFighter(1, 1, f3);
    // battleMap->addFighter(1, 3, f2);
    // battleMap->saveBattlefield("test");
    // Battlefield* battleMap2 = new Battlefield("test");
    // std::cout << battleMap2->toString();
    
    // Battlefield* battleMap2 = new Battlefield(10, 10);
    
    // std::cout << battleMap->toString();
    // std::cout << "\n";
    // std::cout << battleMap2->toString();





    // std::cout << "fighter 1 hp: " << f1->getHp() << "\n";
    // std::cout << "fighter 2 hp: " << f2->getHp() << "\n";

    // int turn = 1;
    // while(f1->getHp()>0 && f2->getHp()>0){
    //     std::cout << "turn: " << turn << "\n";

    //     std::cout << "fighter 1 dealt: ";
    //     std::cout << battle(f1, f2);
    //     std::cout << " damage to fighter 2, leaving it with ";
    //     std::cout << f2->getHp();
    //     std::cout << " HP.\n";
        
    //     std::cout << "fighter 2 dealt: ";
    //     std::cout << battle(f2, f1); 
    //     std::cout <<" damage to fighter 1, leaving it with ";
    //     std::cout << f1->getHp();
    //     std::cout << " HP.\n\n";

    //     turn++;
    // }

    // if(f1->getHp() <= 0){
    //     std::cout << "Fighter 1 has been defeated";
    // }
    // else{
    //     std::cout << "Fighter 2 has been defeated";
    // }
    //return EXIT_SUCCESS;
    return 0;
}



//warwock would be a funny name