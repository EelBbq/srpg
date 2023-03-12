#ifndef FIGHTER_H
#define FIGHTER_H
#include <string>

    class Fighter {
        private:
            std::string name;
            int hpMax;             //max health points
            int hp;                //current hp

            int str;               //strength
            int con;               //constitution
            int agi;               //agility
            int intl;              //intelligence
            int luk;               //luck
            int fai;               //faith

            int xp;                //experience points
            int lv;                //level
            void levelUp();

            bool playerCharacter;

        public:
            Fighter();
            Fighter(std::string fighterName, int strength, int constitution, int agility, int intelligence, int luck, int faith, bool playercharacter);
            Fighter(std::string fileName);

            void applyDamage(int damage);   //apply damage
            void gainXp(int ammount);
            
            int getHp();
            int getHpMax();
            int getStr();
            int getCon();
            int getAgi();
            int getIntl();
            int getLuk();
            int getFai();
            int getXp();
            int getLv();
            void setStr(int newStr);
            void saveFighter(std::string fileName);
            std::string toSerial();
            std::string toString();

//make private            

    };
#endif