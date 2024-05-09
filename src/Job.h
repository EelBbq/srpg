#ifndef JOB_H
#define JOB_H
#include "Spell.h"
#include <vector>

struct Stats{
            double strengthBase;
            double constitutionBase;
            double agilityBase;
            double intelligenceBase;
            double luckBase;
            double faithBase;
            double strengthRate;
            double constitutionRate;
            double agilityRate;
            double intelligenceRate;
            double luckRate;
            double faithRate;
            int    moveSpeed;
};

struct Spellbook_Duple {
    int level;
    SPELL_enum SPELL;
};

struct Job{
    std::vector<Spellbook_Duple> spellbook;
    Stats stats;
};

Job warrior;
//warrior


//  class Job {
//     protected:
//         //enum stats {strength, constitution, agility, intelligence, luck, faith};
//         Stats stats;
//         // const double warrior[6];
//         // const double mage[6];
//         // const double assassin[6];
//         // const double hunter[6];
//     public:
//         double getStrengthBase();
//         double getconstitutionBase();
//         double getagilityBase();
//         double getintelligenceBase();
//         double getluckBase();
//         double getfaithBase();
//         double getstrengthRate();
//         double getconstitutionRate();
//         double getagilityRate();
//         double getintelligenceRate();
//         double getluckRate();
//         double getfaithRate();
//         int    getmoveSpeed();
        
//         int    learnSpell(int level);
// };

//class Warrior : public Job {};
// class Mage : public Job {};
// class Assassin : public Job {};
// class Hunter : public Job {};



#endif