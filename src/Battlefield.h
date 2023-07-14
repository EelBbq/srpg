#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <string>
#include <vector>
#include "Fighter.h"


class Battlefield{
    private:
    Fighter* ** fighterMap;     //2d array of fighter pointers
    //Terrain ** terrainMap;      //2d array of terrain
    int mapX;
    int mapY;
    int numFighters;
    bool legalCoord(int x, int y);

    bool isUnblocked(int x, int y);
    int terrainDifficulty(int x, int y);

    enum direction {UP, RIGHT, DOWN, LEFT};
    bool hasDirection(int x, int y, direction dir);
        bool hasUp(int x, int y);
        bool hasRight(int x, int y);
        bool hasDown(int x, int y);
        bool hasLeft(int x, int y);

    struct DkjsXYNode{
        int x, y;   //absolute position xy
        int dist;   //shortest manhattan distance
        
        std::string toString(){
            return "X: " + std::to_string(x) + " Y: " + std::to_string(y)/* + " Path Length: " + std::to_string(dist)*/;
        };
    };

    //void Battlefield::djkExamineNode(int x, int y, int range, std::vector<Battlefield::DkjsXYNode>* knownCoords, std::vector<Battlefield::DkjsXYNode>* legalCoords);
    std::vector<DkjsXYNode> djkRange(int x0, int y0, int range);
    DkjsXYNode* findDkjsXYNode(std::vector<Battlefield::DkjsXYNode> xyNodeVect, int x, int y);
    bool hasDkjsXYNode(std::vector<Battlefield::DkjsXYNode> xyNodeVect, int x, int y);
    


    public:
    enum Terrain {ground, sand, water, mountain, sky};

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

    int getX();
    int getY();
    std::string toString();
    //void deleteBattlefield();
};


#endif