#ifndef SPECIES_H
#define SPECIES_H

#include <vector>
#include "Environment.h"
using std::vector, std::min, std::max;


class Bacterium
{

private:
    unsigned long int bacteriaID = 0;

protected:

    static double temporalResolution;          
    

    bool alive = 1;
    
    double 
        minEnergy = 0,
        maxEnergy = 500.0f,
        livingEnergy = 1.0f, 
        reproductionEnergy = 300.0f,
    
        acidicLimit = 150.0f,        
        proximity = 3.0f,
        energyPerNutrient = 10.0f,  
        CO2PerEnergy = 10.0f,
        rateOfConsumption = 1.0f,
        movementSpeed = 1.0f;

    vector<int> position = {0,0,0};
    double energy = 0.0f;        
    
    double getAcetateNearby(Environment* surroundings) const;
    

public:
    Bacterium();
    Bacterium(const vector<int> , double const energy_lvl = 300.0f);
    
    void setID(unsigned long int);
    unsigned long int getID();

    
    void move( Environment* );
    void eat( Environment* );
    void reproduce( Environment* , Bacterium& );
    void live( Environment* , Bacterium& );
    void die();
    void adapt( Environment* );
    static void updateTemporalResolution(const double tempresNew);

    double getEnergy();
    bool canLive( Environment* ) const;
    bool isAlive() const;
    static double getTemporalResolution();

    bool operator==(const Bacterium&) const;
    vector<int> getPosition() const { return position; }
};


#endif
