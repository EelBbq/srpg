#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <string>
#include <vector>
#include "Fighter.h"


class Battlefield{
    private:
    Fighter* ** fighterMap;     //2d array of fighter pointers
    enum Terrain {ground, sand, water, mountain, sky};
    Terrain ** terrainMap;      //2d array of terrain
    int mapX;
    int mapY;
    int numFighters;
    bool legalCoord(int x, int y);

    struct DkjsXYNode{
        int x, y;   //absolute position xy
        int dist;   //shortest manhattan distance
        
        std::string toString(){
            return "X: " + std::to_string(x) + " Y: " + std::to_string(y) + " Path Length: " + std::to_string(dist);
        };
    };

    std::vector<DkjsXYNode> djkRange(int x0, int y0, int range);
    DkjsXYNode* findDkjsXYNode(std::vector<Battlefield::DkjsXYNode> xyNodeVect, int x, int y);
    bool hasDkjsXYNode(std::vector<Battlefield::DkjsXYNode> xyNodeVect, int x, int y);
    


    public:
    Battlefield();
    Battlefield(int x, int y);
    Battlefield(std::string fileName);

    void saveBattlefield(std::string fileName);

    Terrain terrainAt(int x, int y);
    Fighter* fighterAt(int x, int y);

    int addFighter(int x, int y, Fighter* newFighter);
    int moveFighter(int x0, int y0, int x1, int y1);
    
    bool isLegalMove(int x0, int y0, int x1, int y1);
    
    void testDikjstras();

    std::string toString();
    //void deleteBattlefield();
};


#endif