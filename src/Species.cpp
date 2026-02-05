#include <cmath>
#include <stdexcept>
#include <iostream> 
#include "Species.h"
#include "Random.h"

using namespace std;

double Bacterium::temporalResolution = 1.0f;
RandomGenerator ranGen;



void Bacterium::setID(unsigned long int id)
{
    if ( bacteriaID != 0 ) throw runtime_error("Cannot modify value - Bacteria already registered");
    if ( id == 0 ) throw invalid_argument("Cannot set bacteriaID to 0");
    bacteriaID = id;
}

unsigned long int Bacterium::getID() { return bacteriaID; }

void Bacterium::updateTemporalResolution(double resolution) {
    if (resolution <= 0) throw invalid_argument("Temporal resolution must be a positive value.");
    temporalResolution = resolution;
}

double Bacterium::getTemporalResolution() { return temporalResolution; }


double Bacterium::getAcetateNearby(Environment* env) const
{
    double totalAcetate = 0.0f;
    const vector<int> size = env->getSize();
    
    for (int x = max(0, position[0] - (int)proximity);
         x <= min(size[0] - 1, position[0] + (int)proximity); ++x)
      for (int y = max(0, position[1] - (int)proximity);
           y <= min(size[1] - 1, position[1] + (int)proximity); ++y)
        for (int z = max(0, position[2] - (int)proximity);
             z <= min(size[2] - 1, position[2] + (int)proximity); ++z)
        {
            double distance = sqrt(pow(x - position[0], 2) + 
                                   pow(y - position[1], 2) + 
                                   pow(z - position[2], 2));
            if (distance <= proximity)
                totalAcetate += env->getAcetateLevel({x, y, z});
        }
    return totalAcetate;
}


Bacterium::Bacterium(){
    energy = 0.0f;
    alive = 0;
}

Bacterium::Bacterium( const vector<int> pos, double const energy_lvl){
    alive = 1;
    position = pos;
    energy = ranGen.Double(energy_lvl);
}

bool Bacterium::operator==(const Bacterium& other) const{
    return bacteriaID == other.bacteriaID;
}



void Bacterium::reproduce( Environment* surroundings , Bacterium& offspring)
{
    if (energy > reproductionEnergy)
    {
        offspring = Bacterium( position, energy / 2 );
        energy /= 2;
    }
    else
        offspring = Bacterium(); 
}

void Bacterium::eat(Environment* surroundings) {
    double totalConsumed = 0.0;

    double centerRate = rateOfConsumption * 0.5;
    totalConsumed += surroundings->consumeNutrient(position, centerRate);

    double neighborRate = (rateOfConsumption * 0.5) / 6.0;
    int dx[] = {1, -1, 0, 0, 0, 0};
    int dy[] = {0, 0, 1, -1, 0, 0};
    int dz[] = {0, 0, 0, 0, 1, -1};

    for (int i = 0; i < 6; i++) {
        vector<int> neighborPos = {
            position[0] + dx[i], 
            position[1] + dy[i], 
            position[2] + dz[i]
        };
        totalConsumed += surroundings->consumeNutrient(neighborPos, neighborRate);
    }
    energy += totalConsumed * energyPerNutrient;
}

void Bacterium::move(Environment* surroundings)
{
    const int range = (int)movementSpeed; 
    int dx = ranGen.Int(-range, range);
    int dy = ranGen.Int(-range, range);
    int dz = ranGen.Int(-range, range);

    vector<double> force = surroundings->getExternalForce();
    vector<int> s = surroundings->getSize();
    int x = position[0];
    int y = position[1];
    int z = position[2];

    auto getNut = [&](int px, int py, int pz) {
        if(px<0 || py<0 || pz<0 || px>=s[0] || py>=s[1] || pz>=s[2]) return 0.0;
        return surroundings->getNutrientLevel({px, py, pz});
    };
    auto getAce = [&](int px, int py, int pz) {
        if(px<0 || py<0 || pz<0 || px>=s[0] || py>=s[1] || pz>=s[2]) return 0.0;
        return surroundings->getAcetateLevel({px, py, pz});
    };

    double trueGradNutX = getNut(x+1, y, z) - getNut(x-1, y, z);
    double trueGradNutY = getNut(x, y+1, z) - getNut(x, y-1, z);
    double trueGradNutZ = getNut(x, y, z+1) - getNut(x, y, z-1);

    double gradAceX = getAce(x+1, y, z) - getAce(x-1, y, z);
    double gradAceY = getAce(x, y+1, z) - getAce(x, y-1, z);
    double gradAceZ = getAce(x, y, z+1) - getAce(x, y, z-1);

    double noiseLevel = 25.0; 

    double perceivedGradX = trueGradNutX + ranGen.Double(-noiseLevel, noiseLevel);
    double perceivedGradY = trueGradNutY + ranGen.Double(-noiseLevel, noiseLevel);
    double perceivedGradZ = trueGradNutZ + ranGen.Double(-noiseLevel, noiseLevel);

    double sensitivityNut = 5.0; 
    double sensitivityAce = 0.5; 

    force[0] += (perceivedGradX * sensitivityNut) - (gradAceX * sensitivityAce);
    force[1] += (perceivedGradY * sensitivityNut) - (gradAceY * sensitivityAce);
    force[2] += (perceivedGradZ * sensitivityNut) - (gradAceZ * sensitivityAce);

    if (force[0] != 0.0 && ranGen.Double(0, 1) < abs(force[0])) dx += (force[0] > 0) ? 1 : -1;
    if (force[1] != 0.0 && ranGen.Double(0, 1) < abs(force[1])) dy += (force[1] > 0) ? 1 : -1;
    if (force[2] != 0.0 && ranGen.Double(0, 1) < abs(force[2])) dz += (force[2] > 0) ? 1 : -1;

    position[0] += dx;
    position[1] += dy;
    position[2] += dz;

    const int max_x = s[0] - 1; 
    const int max_y = s[1] - 1;
    const int max_z = s[2] - 1;

    if (position[0] < 0) position[0] = -position[0];
    else if (position[0] > max_x) position[0] = max_x - (position[0] - max_x);

    if (position[1] < 0) position[1] = -position[1];
    else if (position[1] > max_y) position[1] = max_y - (position[1] - max_y);

    if (position[2] < 0) position[2] = -position[2];
    else if (position[2] > max_z) position[2] = max_z - (position[2] - max_z);
}

void Bacterium::die(){ alive = 0; }
void Bacterium::adapt( Environment* surroundings ){}
double Bacterium::getEnergy(){ return energy; }
bool Bacterium::isAlive() const { return alive; }

bool Bacterium::canLive(Environment* surroundings) const {
    if (energy <= minEnergy) return 0;
    if (getAcetateNearby(surroundings) > acidicLimit) return 0;
    return 1;
}

void Bacterium::live(Environment* surroundings, Bacterium& offspring) {
    move(surroundings);
    eat(surroundings);
    adapt(surroundings);
    reproduce(surroundings, offspring);
    
    energy -= livingEnergy;
    surroundings->updateCO2(livingEnergy * CO2PerEnergy);
    surroundings->updateAcetate(position, 1); 

    if (!canLive(surroundings)) {
        die();
    }
}