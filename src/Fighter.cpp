#include "Fighter.h"
#include "Job.h"
#include <string>
#include <fstream>

 
std::string name = "";

double ratioCon = 2;
double ratioStr = 1.5;

int hpMax;             //max health points
int hp;                //current hp

int spd;

int str;               //strength
int con;               //constitution
int agi;               //agility
int intl;              //intelligence
int luk;               //faith
int fai;               //luck

int xp;
int lv;

bool playerCharacter;



Fighter::Fighter() {   
    name = "Default Fighter";

    spd = 5;

    str = 10;
    con = 10;
    agi = 10;
    intl = 10;
    luk = 10;
    fai = 10;

    hpMax = (ratioCon * con) + (ratioStr * str);
    hp = hpMax;

    xp = 0;
    lv = 0;

    playerCharacter = false;
}

Fighter::Fighter(std::string fighterName, int strength, int constitution, int agility, int intelligence, int luck, int faith, bool playercharacter){
    
    name = fighterName;

    spd = 5;

    str = strength;
    con = constitution;
    agi = agility;
    intl = intelligence;
    luk = luck;
    fai = faith;

    hpMax = (ratioCon * con) + (ratioStr * str);
    hp = hpMax;

    playerCharacter = playercharacter;
}

void Fighter::applyDamage(int damage){
    hp -= damage;
}

void Fighter::gainXp(int ammount){
    xp += ammount;
    if(xp < 99) { this->levelUp(); };
}

void Fighter::levelUp(){
    str += 1;
    con += 1;
    agi += 1;
    intl += 1;
    luk += 1;
    fai += 1;
    xp -= 100;
    lv += 1;
}

int Fighter::getHp(){
    return hp;
}
int Fighter::getHpMax(){
    return hpMax;
}

int Fighter::getStr(){
    return str;
}

int Fighter::getCon(){
    return con;
}

int Fighter::getAgi(){
    return agi;
}

int Fighter::getIntl(){
    return intl;
}

int Fighter::getLuk(){
    return luk;
}

int Fighter::getFai(){
    return fai;
}

int Fighter::getSpd(){
    return spd;
}

//remove
void Fighter::setStr(int newStr){
    int oldHpMax = hpMax;
    hpMax = (ratioCon * con) + (ratioStr * str);
    hp = hp + (hpMax - oldHpMax);
}

void Fighter::saveFighter(std::string fileName){
    std::ofstream outputFile;
    outputFile.open(fileName + ".dat");
    outputFile << this->toSerial();
    outputFile.close();
}

std::string Fighter::toSerial(){
    std::string strOut;
    
    strOut = strOut + name + ",";   

    strOut = strOut + std::to_string(str) + ",";
    strOut = strOut + std::to_string(con) + ",";
    strOut = strOut + std::to_string(agi) + ",";
    strOut = strOut + std::to_string(intl) + ",";
    strOut = strOut + std::to_string(luk) + ",";
    strOut = strOut + std::to_string(fai) + ";";

    return strOut;
}



std::string Fighter::toString(){
    std::string strOut = "";

    strOut = strOut + name + "\n";

    strOut = strOut + "HP: " + std::to_string(hp) + "/";
    strOut = strOut + std::to_string(hpMax) + "\n";
    

    strOut = strOut + "Str: " + std::to_string(str) + "\n";
    strOut = strOut + "Con: " + std::to_string(con) + "\n";
    strOut = strOut + "Agi: " + std::to_string(agi) + "\n";
    strOut = strOut + "Int: " + std::to_string(intl) + "\n";
    strOut = strOut + "Luk: " + std::to_string(luk) + "\n";
    strOut = strOut + "Fai: " + std::to_string(fai) + "\n";

    return strOut;
}

// double randomVal() {
//     srand(time(NULL));
    
//     double val = (rand() % 100) / 100;
//     return val;
// }