#include "Battlefield.h"
#include "Fighter.h"
#include <string>
#include <iostream>
#include <fstream>

//upgrade to vectors?
//array of posible locations for fighters
    int mapX;          //size x, default 10
    int mapY;          //size y, default 10 
    const int defaultXY = 10;
    Fighter* **fighterMap; //2d array to Fighter Pointers

//terrain enum
    enum Terrain {ground, sand, water, mountain, sky};

    Terrain ** terrainMap;  //2d array of terrains
    


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

            //heinously ugly code pls help --make into own function?
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

    Battlefield::Terrain Battlefield::terrainAt(int x, int y){
        return terrainMap[x][y];
    }

    Fighter* Battlefield::fighterAt(int x, int y){
        return fighterMap[x][y];
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