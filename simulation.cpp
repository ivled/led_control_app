#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "simulation.h"

void InitializeSimulation()
{
    std::srand(std::time(0)); // use current time as seed for random generator
}

float Random()
{
    return static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) + 1.0);
}

void RandomDelay(float maxSeconds)
{
//    Sleep(static_cast<unsigned int>(SimulationConfig::cInitializeDelay * Random() * 1000.0));
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned int>(SimulationConfig::cInitializeDelay * Random() * 1000.0)));
}

// --- simulation config ---

// error probabilities

const float SimulationConfig::cInitializeErrorProbability = 0.05;
const float SimulationConfig::cDeinitializeErrorProbability = 0.05;

const float SimulationConfig::cSetLedStateErrorProbability = 0.1;
const float SimulationConfig::cGetLedStateErrorProbability = 0.1;

const float SimulationConfig::cSetLedColorErrorProbability = 0.1;
const float SimulationConfig::cGetLedColorErrorProbability = 0.1;

const float SimulationConfig::cSetLedRateErrorProbability = 0.1;
const float SimulationConfig::cGetLedRateErrorProbability = 0.1;

// hardware operation delays (in seconds)

const float SimulationConfig::cInitializeDelay = 3.0;
const float SimulationConfig::cDeinitializeDelay = 1.0;

const float SimulationConfig::cSetLedStateDelay = 1.0;
const float SimulationConfig::cGetLedStateDelay = 1.0;

const float SimulationConfig::cSetLedColorDelay = 1.0;
const float SimulationConfig::cGetLedColorDelay = 1.0;

const float SimulationConfig::cSetLedRateDelay = 1.0;
const float SimulationConfig::cGetLedRateDelay = 1.0;
