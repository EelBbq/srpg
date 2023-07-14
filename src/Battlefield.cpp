#include "Battlefield.h"
#include "Fighter.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdexcept>

//upgrade to vectors?
//array of posible locations for fighters
    int mapX;          //size x, default 10
    int mapY;          //size y, default 10 
    const int MOVEMENTCOEFFICIENT = 5;
    const int defaultXY = 10;
    Fighter* **fighterMap; //2d array to Fighter Pointers

//terrain enum
    // enum Terrain {ground, sand, water, mountain, sky};

    Battlefield::Terrain ** terrainMap;  //2d array of terrains
    


    Battlefield::Battlefield(){
    //todo: write constructor, test battlefield and moving with whatsAt, write an overload version of the function for files

        numFighters = 0;

        mapX = defaultXY;
        mapY = defaultXY;

        //ititialize fighterMap
        fighterMap = new Fighter* *[mapX];  //rows
        for(int i = 0; i < mapX; i++){
            fighterMap[i] = new Fighter* [mapY]; // build Columns
        }

        for(int i = 0; i < mapX; i++){
            for(int j = 0; j < mapY; j++){
                fighterMap[i][j] = nullptr; //initialize fighterMap[i][j] to nullptr
            }
        }

        //ititialize terrainMap
        terrainMap = new Terrain *[mapX];  //rows
        for(int i = 0; i < mapX; i++){
            terrainMap[i] = new Terrain [mapY]; // build Columns
        }

        for(int i = 0; i < mapX; i++){
            for(int j = 0; j < mapY; j++){
                terrainMap[i][j] = ground;  //initialize i,j to ground
            }
        }
    }

    Battlefield::Battlefield(int x, int y){
    //todo: write constructor, test battlefield and moving with whatsAt, write an overload version of the function for files

        numFighters = 0;

        mapX = x;
        mapY = y;

        //ititialize fighterMap
        fighterMap = new Fighter* *[mapX];  //rows
        for(int i = 0; i < mapX; i++){
            fighterMap[i] = new Fighter* [mapY]; // build Columns
        }

        for(int i = 0; i < mapX; i++){
            for(int j = 0; j < mapY; j++){
                fighterMap[i][j] = nullptr; //initialize fighterMap[i][j] to nullptr
            }
        }

        //ititialize terrainMap
        terrainMap = new Terrain *[mapX];  //rows
        for(int i = 0; i < mapX; i++){
            terrainMap[i] = new Terrain [mapY]; // build Columns
        }

        for(int i = 0; i < mapX; i++){
            for(int j = 0; j < mapY; j++){
                terrainMap[i][j] = ground;  //initialize i,j to ground
            }
        }
    }

    Battlefield::Battlefield(std::string fileName){
        std::ifstream mapFile;
        mapFile.open(fileName + ".dat");
        std::string line;
        if (mapFile.is_open()){
            getline(mapFile, line);
            mapX = std::stoi(line);

            getline(mapFile, line);
            mapY = std::stoi(line);

            getline(mapFile, line);
            numFighters = std::stoi(line);

            getline(mapFile, line);
            //ititialize terrainMap
            terrainMap = new Terrain *[mapX];  //rows
            for(int i = 0; i < mapX; i++){
                terrainMap[i] = new Terrain [mapY]; // build Columns
            }

            for(int i = 0; i < mapX; i++){
                for(int j = 0; j < mapY; j++){
                    switch(line[(i*10)+j]){             /*potential person of interest line of code*/
                        case 'G':
                            terrainMap[i][j] = ground;  //initialize i,j to ground
                            break;
                        case 'S':
                            terrainMap[i][j] = sand;  //initialize i,j to ground
                            break;
                        case 'W':
                            terrainMap[i][j] = water;  //initialize i,j to ground
                            break;
                        case 'M':
                            terrainMap[i][j] = mountain;  //initialize i,j to ground
                            break;
                        case 'A':
                            terrainMap[i][j] = sky;  //initialize i,j to ground
                            break;
                        default:
                            terrainMap[i][j] = ground;  //initialize i,j to ground
                        
                        }
                    }
                }

            //ititialize fighterMap
            fighterMap = new Fighter* *[mapX];  //rows
            for(int i = 0; i < mapX; i++){
                fighterMap[i] = new Fighter* [mapY]; // build Columns
            }

            for(int i = 0; i < mapX; i++){
                for(int j = 0; j < mapY; j++){
                    fighterMap[i][j] = nullptr; //initialize fighterMap[i][j] to nullptr
                }
            }

            //heinously ugly code --make into own function?
            while(getline(mapFile, line)){
                const int NUM_ARGS = 9;        //number of arguments of fighter(args) + 2 for x, y
                std::string args[NUM_ARGS];    //stores the arguments of addFighter and Fighter constructor in array
                int argCounter = 0;     //tracks which arg has been added to args[]
                std::string temp = "";  //temp string that stores each argument before its finished being tokenized at , or ; and added to args[]
                for(int i=0; i < line.size(); i++){
                    if(!(line[i] == ',' || line[i] == ';')){    //delimit tokens at ',' and ';'
                        temp += line[i];                        //add each char to temp
                    }
                    else{
                        args[argCounter] = temp;                //add temp to args
                        temp = "";                              //reset temp
                        argCounter++;                           //iterate onto the next arg in args[]
                    }
                }
                
                //add at x, y a new Fighter with arguments from args[]
                addFighter(std::stoi(args[0]), std::stoi(args[1]),
                           new Fighter(args[2], std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), 
                                       std::stoi(args[6]), std::stoi(args[7]), std::stoi(args[8]), false));
            }
            mapFile.close();
        }
    }
        

    void Battlefield::saveBattlefield(std::string fileName){
        std::ofstream outputFile;
        outputFile.open(fileName + ".dat");
        

        outputFile 
        << mapX << "\n"
        << mapY << "\n"
        << numFighters;

        // int fighterCounter = 1; //keeps track of which fighter is where, coordinated at bottom of file
        outputFile << "\n";
        for(int i = 0; i < mapX; i++){
            for(int j = 0; j < mapY; j++){
                //Fighter
                // if((fighterMap[i][j] == nullptr)) {
                //     outputFile << "0";  //no fighter
                // }
                // else{
                //     outputFile << fighterCounter;  //fighter
                //     fighterCounter++;
                // }
                
                //terrain
                switch(terrainMap[i][j]){
                    case ground:
                        outputFile << "G";
                        break;
                    case sand:
                        outputFile << "S";
                        break;
                    case water:
                        outputFile << "W";
                        break;
                    case mountain:
                        outputFile << "M";
                        break;
                    case sky:
                        outputFile << "A";
                        break;
                    default:
                        outputFile << "N";
                }
                // if(j < mapY-1) { outputFile << " "; }
            }
        }

         outputFile << "\n";
        

        for(int i = 0; i < mapX; i++){
            for(int j = 0; j < mapY; j++){
                if(!(fighterMap[i][j] == nullptr)){
                    outputFile << std::to_string(i) << ","  << std::to_string(j) << "," << fighterMap[i][j]->toSerial() << "\n";
                }
            }
        }

        outputFile.close();
    }


    
    int Battlefield::addFighter(int x, int y, Fighter* newFighter){
        int retVal;
        if((0 <= x && x < mapX) && (0 <= y && y < mapY)){
            if(fighterMap[x][y] == nullptr){
                fighterMap[x][y] = newFighter;

                numFighters++;
            }
            else {
                retVal = -2;    //already a fighter at xy error
            }
        }
        else {
            retVal = -1;        //xy out of bounds error
        }

        return retVal;
    }

    int Battlefield::moveFighter(int x0, int y0, int x1, int y1){
        int retVal;
        if((0 <= x0 && x0 < mapX) && (0 <= y0 && y0 < mapY) && (0 <= x1 && x1 < mapX) && (0 <= y1 && y1 < mapY)){   //if 0 == x0, y0, x1, y1 < mapXY
            if(((fighterMap[x0][y0] != nullptr) && (fighterMap[x1][y1] == nullptr))){                                   //if position0 occupied && position1 unoccupied, 
                fighterMap[x1][y1] = fighterMap[x0][y0];                                                                //copy pointer to fighter at position0 to position 1
                fighterMap[x0][y0] = nullptr;                                                                           //null out pointer to fighter at position 0;
                
                retVal = 0;
            }
            else{
                retVal = -2;
            }
        } else {
            retVal = -1;
        }

        return retVal;
    }
    
    

    bool Battlefield::hasDirection(int x, int y, Battlefield::direction dir){
        bool retValue = false;
        switch (dir) {
            case UP:
                retValue = Battlefield::legalCoord(x, y - 1);
                break;
            case RIGHT:
                retValue = Battlefield::legalCoord(x + 1, y);
                break;
            case DOWN:
                retValue = Battlefield::legalCoord(x, y - 1);
                break;
            case LEFT:
                retValue = Battlefield::legalCoord(x - 1, y);
                break;
            default: 
                retValue = false;
        }

        return retValue;
    }

    bool Battlefield::hasUp(int x, int y){
        return Battlefield::hasDirection(x, y, UP);
    }
    
    bool Battlefield::hasRight(int x, int y){
        return Battlefield::hasDirection(x, y, RIGHT);
    }

    bool Battlefield::hasDown(int x, int y){
        return Battlefield::hasDirection(x, y, DOWN);
    }

    bool Battlefield::hasLeft(int x, int y){
        return Battlefield::hasDirection(x, y, LEFT);
    }

    bool Battlefield::isUnblocked(int x, int y){
        bool retBool = false;
        switch (terrainMap[x][y]) {
            case water:
                retBool = false;
                break;
            case sky:
                retBool = false;
                break;
            case mountain:
                retBool = false;
                break;
            case ground:
                retBool = true;
                break;
            case sand:
                retBool = true;
            default:
                retBool = false;
                break;
        }
        return retBool;
    }

    int Battlefield::terrainDifficulty(int x, int y){
        int retValue = 5;
            switch (terrainMap[x][y]) {
                case water:
                    retValue = 8;
                    break;
                case sky:
                    retValue = 5;
                    break;
                case mountain:
                    retValue = 8;
                    break;
                case ground:
                    retValue = 5;
                    break;
                case sand:
                    retValue = 8;
                default:
                    retValue = 5;
                    break;
            }
        return retValue;
    }

//returns true if current position is the specified destination
    bool isDestination(int x, int y, int x1, int y1) {
        bool retBool = false;
        if(x == x1 && y == y1){
            retBool = true;
        }
        return retBool;
    }

    // class Tree {
    //     class treeNode {
    //         int x, y;
    //         treeNode* parent;
    //         std::vector<treeNode*> children;
            
    //         public:
    //         bool hasXY(int targetX, int targetY){
    //             bool retVal = false;
                
    //             //recursive
    //             if(x == targetX && y == targetY){
    //                 retVal = true;
    //             }
    //             else {
    //                 for(int i = 0; i < children.size(); i++) {
    //                     if(children[i]->hasXY(targetX, targetY)) {
    //                         retVal = true;
    //                     }
    //                 }
    //             }

    //             return retVal;
    //         }
    //     };

    //     treeNode* source;
    //     int size = 0;

    //     bool hasXY(int x, int y){
    //         bool retVal = false;
    //         if(size > 0){
    //             retVal = source->hasXY(x, y);
    //         }
    //         return retVal;
    //     }
    // };

//returns true if x and y are within the bounds of the map
    bool Battlefield::legalCoord(int x, int y){
        bool retValue = true;

        if(x < 0 || x >= mapX) {
            retValue = false;
        }
        if(y < 0 || y >= mapY) {
            retValue = false;
        }

        return retValue;
    }

    bool Battlefield::hasDkjsXYNode(std::vector<Battlefield::DkjsXYNode> xyNodeVect, int x, int y){
        bool retbool = false;
        
        for(int i = 0; i < xyNodeVect.size(); i++) {
            if(xyNodeVect[i].x == x && xyNodeVect[i].y == y){
                retbool = true;
            }
        }

        //std::cout << retbool;

        return retbool;
    }

    void debugOut(std::string str, int i){
        std::cout << str;
        std::cout << i;
    }

    Battlefield::DkjsXYNode* Battlefield::findDkjsXYNode(std::vector<Battlefield::DkjsXYNode> xyNodeVect, int x, int y){
        Battlefield::DkjsXYNode* retNode;
        
        for(int i = 0; i < xyNodeVect.size(); i++) {
            if(xyNodeVect[i].x == x && xyNodeVect[i].y == y){
                retNode = &xyNodeVect[i];
                
            }
        }

        return retNode;
    }

    // void Battlefield::djkExamineNode(int x, int y, int range, std::vector<Battlefield::DkjsXYNode>* knownCoords, std::vector<Battlefield::DkjsXYNode>* legalCoords){
    //     if(Battlefield::hasDkjsXYNode(legalCoords, x, y) &&                    //check if there is a node for the xy coordinate above current
    //         (findDkjsXYNode(legalCoords, xi, yi)->dist > disti)) {    //and if there is check if the node above's previous shortest path is longer than the current one
    //         findDkjsXYNode(legalCoords, xi, yi)->dist = disti;      //if it is, replace previous distance for xy with current one
    //     } else {
    //         DkjsXYNode tempUp;                                          //if up not in legalCoords, define a new node for it and add it to tempCoords to be explored next while loop cycle
    //         tempUp.x = xi;       
    //         tempUp.y = yi + 1;
    //         tempUp.dist = disti + 1;
    //         tempCoords.push_back(tempUp);
    //     }
    // }

//returns list of coords that are accessible within a range around
    std::vector<Battlefield::DkjsXYNode> Battlefield::djkRange(int x0, int y0, int range){
        std::vector<DkjsXYNode> legalCoords;    //list of known legal nodes to be returned
        std::vector<DkjsXYNode> knownCoords;    //list of known nodes to be explored
        bool hasCoords = false;                  //sentinel bool for while loop

        DkjsXYNode tempNode;
        if(Battlefield::legalCoord(x0, y0)){
            tempNode.x = x0;                    //create and add initial src node to known coords if legals 
            tempNode.y = y0;
            tempNode.dist = 0;
            knownCoords.push_back(tempNode);    
            hasCoords = true;                   //enable sentinel bool if legal coord
        }
        
        while(hasCoords){
            std::vector<DkjsXYNode> tempCoords;

            for(int i = 0; i < knownCoords.size(); i++) {
                if(knownCoords[i].dist <= range){
                    //store values of current node
                    int xi = knownCoords[i].x;
                    int yi = knownCoords[i].y;
                    int disti = knownCoords[i].dist;

                    bool hasNode = Battlefield::hasDkjsXYNode(legalCoords, xi, yi);
                    if(!hasNode || (hasNode && (findDkjsXYNode(legalCoords, xi, yi)->dist > disti))){
                        legalCoords.push_back(knownCoords[i]);
                    }

                    //add neighbors to known coords

//tons of redundancy, would be a good candidate to refactor
                    if(hasUp(xi, yi) && isUnblocked(xi, yi + 1)){                                                  //if up is a valid xy coordiant
                        if(hasDkjsXYNode(legalCoords, xi, yi + 1) &&                    //check if there is already a legalCoords node for the xy coordinate above current
                          (findDkjsXYNode(legalCoords, xi, yi + 1)->dist < disti)) {    //and if there is check if the node above's previous shortest path is longer than the current one
                            findDkjsXYNode(legalCoords, xi, yi + 1)->dist = disti;      //if it is, replace previous distance for xy with current one
                        } else {
                            DkjsXYNode tempUp;                                          //if up not in legalCoords, define a new node for it and add it to tempCoords to be explored next while loop cycle
                            tempUp.x = xi;       
                            tempUp.y = yi + 1;
                            tempUp.dist = disti + terrainDifficulty(xi, yi);
                            tempCoords.push_back(tempUp);
                        }
                    }
                    if(hasDown(xi, yi) && isUnblocked(xi, yi - 1)){                       //down
                        if(hasDkjsXYNode(legalCoords, xi, yi - 1) &&
                          (findDkjsXYNode(legalCoords, xi, yi - 1)->dist < disti)) {
                            findDkjsXYNode(legalCoords, xi, yi - 1)->dist = disti;
                        } else {
                            DkjsXYNode tempDown;
                            tempDown.x = xi;       
                            tempDown.y = yi - 1;
                            tempDown.dist = disti + terrainDifficulty(xi, yi);
                            tempCoords.push_back(tempDown);
                        }
                    }
                    if(hasLeft(xi, yi) && isUnblocked(xi - 1, yi)){                                                //left
                        if(hasDkjsXYNode(legalCoords, xi - 1, yi) &&
                          (findDkjsXYNode(legalCoords, xi - 1, yi)->dist < disti)) {
                            findDkjsXYNode(legalCoords, xi - 1, yi)->dist = disti;
                        } else {
                            DkjsXYNode tempLeft;
                            tempLeft.x = xi - 1;       
                            tempLeft.y = yi;
                            tempLeft.dist = disti + terrainDifficulty(xi, yi);
                            tempCoords.push_back(tempLeft);
                        }
                    }
                    if(hasRight(xi, yi) && isUnblocked(xi + 1, yi)){                                                //right
                        if(hasDkjsXYNode(legalCoords, xi + 1, yi) &&
                          (findDkjsXYNode(legalCoords, xi + 1, yi)->dist < disti)) {
                            findDkjsXYNode(legalCoords, xi + 1, yi)->dist = disti;
                        } else {
                            DkjsXYNode tempRight;
                            tempRight.x = xi + 1;       
                            tempRight.y = yi;
                            tempRight.dist = disti + terrainDifficulty(xi, yi);
                            tempCoords.push_back(tempRight);
                        }
                    }
                }
            }//end for loop

            //after iterating-through/exploring all of knownCoords and filling out tempCoords, update knownCoords to tempCoords for next iteration
            knownCoords = tempCoords;

            //if known coords runs out of nodes to explore, update sentinel bool hasCoords to quit out of while loop
            if(knownCoords.size() == 0){
                hasCoords = false;
            }
        }

        return legalCoords;
    }

    

    void Battlefield::testDikjstras(){
        // std::cout << "isLegal(1, 4): ";
        // std::cout << legalCoord(1, 4);
        // std::cout << "\nisLegal(-1, 4): ";
        // std::cout << legalCoord(-1, 4);
        // std::cout << "\nisLegal(4, -1): ";
        // std::cout << legalCoord(4, -1);

        // std::cout << "hasup(0, 0) ";
        // std::cout << Battlefield::hasUp(0, 0);
        // std::cout << "\nhasup(0, 11) ";
        // std::cout << Battlefield::hasUp(0, 11);
        // std::cout << "\nhasLeft(0, 0) ";
        // std::cout << Battlefield::hasLeft(0, 0);
        // std::cout << "\nhasLeft(9, 0) ";
        // std::cout << Battlefield::hasLeft(9, 0);
        // std::cout << "\nhasDown(0, 0) ";
        // std::cout << Battlefield::hasDown(0, 0);
        // std::cout << "\nhasDown(0, 0) ";
        // std::cout << Battlefield::hasDown(0, 9);
        // std::cout << "\nhasRight(9, 0) ";
        // std::cout << Battlefield::hasRight(9, 0);
        // std::cout << "\nhasRight(0, 0) ";
        // std::cout << Battlefield::hasRight(0, 0);

        int x0 = 5;
        int y0 = 5;
        int range = 3;
        std::vector<DkjsXYNode> testList = djkRange(x0, y0, range);

        // std::cout << "Coords within 3 range of 5, 5:\n";
        // for(int i = 0; i < testList.size(); i++){
        //     std::cout << testList[i].toString() + "\n";
        // }
        // std::cout << "\n";

        x0 = 1;
        y0 = 3;
        range = 5 * MOVEMENTCOEFFICIENT;
        testList = djkRange(x0, y0, range);

        std::cout << "Coords within 5 range of 1, 3:\n";
        for(int i = 0; i < testList.size(); i++){
            std::cout << "Iteration ";
            std::cout << i;
            std::cout << ": ";
            std::cout << testList[i].toString() + "\n";
        }
        std::cout << "\n";
    }

    Battlefield::Terrain Battlefield::terrainAt(int x, int y){
        return terrainMap[x][y];
    }

    Fighter* Battlefield::fighterAt(int x, int y){
        return fighterMap[x][y];
    }

    int Battlefield::getX(){
        return mapX;
    }

    int Battlefield::getY(){
        return mapY;
    }

    std::string Battlefield::toString(){

        std::string strOut = "";
        
        for(int i = 0; i < mapX; i++){
            
            for(int j = 0; j < mapY; j++){
                
                //print fighter symbol
                if((fighterMap[i][j] == nullptr)) {
                    strOut = strOut + "0";  //no fighter
                }
                else{
                    strOut = strOut + "F";  //fighter
                }

                switch(terrainMap[i][j]){
                    case ground:
                        strOut = strOut + "G";
                        break;
                    case sand:
                        strOut = strOut + "S";
                        break;
                    case water:
                        strOut = strOut + "W";
                        break;
                    case mountain:
                        strOut = strOut + "M";
                        break;
                    case sky:
                        strOut = strOut + "S";
                        break;
                    default:
                        strOut = strOut + "N";
                }

                strOut = strOut + " ";  //space between the grids
            }
            
            strOut = strOut + "\n";     //newlines
        }

        return strOut;
    }
    
    
//void deleteBattlefield();