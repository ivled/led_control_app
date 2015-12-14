#ifndef SIMULATION_H
#define SIMULATION_H

// random generation

void InitializeSimulation();

float Random();

void RandomDelay(float maxSeconds);

// simulation constants

struct SimulationConfig
{
    // error probabilities

    static const float cInitializeErrorProbability;
    static const float cDeinitializeErrorProbability;

    static const float cSetLedStateErrorProbability;
    static const float cGetLedStateErrorProbability;

    static const float cSetLedColorErrorProbability;
    static const float cGetLedColorErrorProbability;

    static const float cSetLedRateErrorProbability;
    static const float cGetLedRateErrorProbability;

    // hardware operation delays

    static const float cInitializeDelay;
    static const float cDeinitializeDelay;

    static const float cSetLedStateDelay;
    static const float cGetLedStateDelay;

    static const float cSetLedColorDelay;
    static const float cGetLedColorDelay;

    static const float cSetLedRateDelay;
    static const float cGetLedRateDelay;
};

#endif
