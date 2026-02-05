#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
using std::vector;

class Environment
{

protected:
    struct patch
    {
        double 
            nutrientLevel = 0,          
            acetateLevel = 0;           

        patch();

    };

    vector<vector<vector<patch>>> locale; 

    vector<vector<vector<patch>>> buffer; 
    vector<int> ranges; 

    double CO2Level = 0.0f;
    long double totalNutrientLevel = 0.0f; 
    long double totalAcetateLevel = 0.0f;
    double temporalResolution = 1.0f;     
    double diffusionConstant = 1.0f;
    vector<double> externalForce = {0.0, 0.0, 0.0};

public:

    Environment( int randomiseType = 0, vector<int> = {50,50,50},
                 double nutrientValue = 1.0f, double acetateValue = 0.0f, 
                 double tempres = 1.0f);


    void updateNutrient(const vector<int>& location, double nutrientChange);

    void updateAcetate(const vector<int>& location, double acetateChange);
    void updateCO2(double CO2Increase);
    void updateTemporalResolution(const double tempresNew);
    void diffuse();

    vector<int> getSize() const;
    double getNutrientLevel(const vector<int>& ) const;
    double getNutrientLevel() const;
    double getAcetateLevel(const vector<int>& ) const;
    double getAcetateLevel() const;
    double getCO2Level();
    double getTemporalResolution();
    double consumeNutrient(const vector<int>& pos, double amount);
    void setExternalForce(vector<double> force);
    vector<double> getExternalForce() const;
};

#endif
