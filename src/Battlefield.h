#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <string>
#include "Fighter.h"

class Battlefield{
    private:
    Fighter* ** fighterMap;     //2d array of fighter pointers
    enum Terrain {ground, sand, water, mountain, sky};
    Terrain ** terrainMap;      //2d array of terrain
    int mapX;
    int mapY;
    int numFighters;
    

    public:
    Battlefield();
    Battlefield(int x, int y);
    Battlefield(std::string fileName);

    void saveBattlefield(std::string fileName);

    Terrain terrainAt(int x, int y);
    Fighter* fighterAt(int x, int y);

    int addFighter(int x, int y, Fighter* newFighter);
    int moveFighter(int x0, int y0, int x1, int y1);
    
    std::string toString();
    //void deleteBattlefield();
};


#endif