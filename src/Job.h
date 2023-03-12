#ifndef JOB_H
#define JOB_H

class Job {
    private:
        
    public:   
        Job();
        enum stats {strength, constitution, agility, intelligence, luck, faith};
        const double warrior[6];
        const double mage[6];
        const double assassin[6];
};

#endif