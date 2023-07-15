//sfml
#include <SFML/Graphics.hpp>

//game
#include <iostream>
#include "Fighter.h"
#include "Battlefield.h"

#include <stdio.h> //Null
#include <stdlib.h> //srand, rand
#include <time.h>   //time

#include <optional>

const int SPRITE_RESOLUTION = 64;

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

void spriteTerrain(Battlefield* bf, sf::Sprite* **terrainSpriteArr, int* xOut, int* yOut) {
    int y = bf->getY();
    int x = bf->getX();

    

    terrainSpriteArr = new sf::Sprite* *[x];
    for(int i = 0; i < x; i++) {
        terrainSpriteArr[i] = new sf::Sprite* [y]; // build Columns
    }

    //load textures
    sf::Texture grass;
    if (!grass.loadFromFile("textures/grass.png"))
    {
        return;
    }
    sf::Texture sand;
    if (!sand.loadFromFile("textures/sand.png"))
    {
        return;
    }
    sf::Texture missingTexture;
    if (!missingTexture.loadFromFile("textures/missingTexture.png"))
    {
        return;
    }
    
    //assign textures to sprites
    for(int i = 0; i < y; i++) {
        
        for(int j = 0; j < x; j++){                
            sf::Sprite tempSprite;

            switch (bf->terrainAt(i, j)){
                case Battlefield::Terrain::ground:
                    tempSprite.setTexture(grass);
                    break;
                case Battlefield::Terrain::sand:
                    tempSprite.setTexture(sand);
                    break;
                case Battlefield::Terrain::water:
                case Battlefield::Terrain::mountain:
                case Battlefield::Terrain::sky:
                default:
                    tempSprite.setTexture(missingTexture);
                    break;
            }

            terrainSpriteArr[i][j] = &tempSprite;
        }
    }
}

void drawTerrain(sf::RenderWindow* window, sf::Sprite ***terrainSpriteArr, int sizeX, int sizeY){
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            std::cout << "sizeX: " << sizeX << "\n";
            std::cout << "sizeY: " << sizeY << "\n";
            std::cout << "i: " << i << "\n";
            std::cout << "j: " << j << "\n";
            sf::Sprite* tempSprite;
            terrainSpriteArr[i][j];
            //sf::Sprite* tempSprite = terrainSpriteArr[i][j];
            std::cout << "sizeX: " << sizeX << "\n";
            std::cout << "sizeY: " << sizeY << "\n";
            tempSprite->setPosition(i * SPRITE_RESOLUTION, j * SPRITE_RESOLUTION);
            window->draw(tempSprite[0]);
        }
    }
}


int main() {

    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

    sf::Texture texture;
    if (!texture.loadFromFile("textures/grass.png"))
    {
        return 0;
    }
    texture.setRepeated(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Texture fighterTexture;
    if (!fighterTexture.loadFromFile("textures/fighter.png"))
    {
        return 0;
    }
    sf::Sprite fighterSprite;
    fighterSprite.setTexture(fighterTexture);

    Battlefield* battleMap2 = new Battlefield(10, 10);
    sf::Sprite*** terrainSprites;
    int terrainX = battleMap2->getX();
    int terrainY = battleMap2->getY();
    spriteTerrain(battleMap2, terrainSprites, nullptr, nullptr);
    
    
    
    // std::cout << battleMap->toString();
    // std::cout << "\n";
    // std::cout << battleMap2->toString();


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        fighterSprite.setPosition(0.0f, 64.0f);

        // clear the window with black color
        window.clear(sf::Color::Black);


        // draw everything here...
        // window.draw(...);
        drawTerrain(&window, terrainSprites, terrainX, terrainY);
        window.draw(fighterSprite);


        // end the current frame
        window.display();
    }

    //fighter 1 and 2
    // Fighter* f1;
    // Fighter* f2;
    // Fighter* f3;

    // f1 = new Fighter();
    // f2 = new Fighter();
    // f3 = new Fighter("Amogus Test", 18, 14, 12, 11, 11, 11, false);

    // std::cout << f3->toString();


    // Battlefield* battleMap = new Battlefield();
    // battleMap->testDikjstras();
    // battleMap->addFighter(1, 1, f3);
    // battleMap->addFighter(1, 3, f2);
    // battleMap->saveBattlefield("test");
    // Battlefield* battleMap2 = new Battlefield("test");
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