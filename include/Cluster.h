#ifndef CLUSTER_H
#define CLUSTER_H

#include "Environment.h"
#include "Species.h"
#include <string>

class Cluster : public Environment, protected Bacterium
{

protected:
    vector<Bacterium> alive = {};
    vector<Bacterium> dead = {};

    unsigned long int totalBacteria = 0;
    unsigned long int totalAliveBacteria = 0;
    unsigned long int totalDeadBacteria = 0;
    
    std::pair<bool, unsigned long int> isPresent( Bacterium );
    
    void add( Bacterium* );
    void omit( Bacterium* );

    void step();


public:

    Cluster(int numBacteria = 100, int randomiseType = 1, 
            double EnergyLevel = 300.0f);

    void updateTemporalResolution(double tempRes);

    void run(std::string filename);
    void run(std::string filename, double time);  

};


#endif
