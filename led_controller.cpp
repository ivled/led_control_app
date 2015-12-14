#include <iostream>
#include "simulation.h"
#include "led_controller.h"

static const unsigned int cMaxLedRate = 5;

LedController::LedController()
    : m_initialized(false)
    , m_on(false)
    , m_color(EColor::Red)
    , m_rate(0)
{
}

LedController::~LedController()
{
    string errorDescription;
    //
    if (!Deinitialize(errorDescription))
    {
        // note: write error message to log for example
        std::cout << "WARNING: couldn't deinitialize LED controller on exit: " << errorDescription << "\n";
    }
}

bool LedController::Initialize(bool on, EColor color, unsigned char rate, string& errorDescription)
{
    if (m_initialized)
    {
        return true;
    }

    InitializeSimulation();

    // simulate hardware error
    if (Random() < SimulationConfig::cInitializeErrorProbability)
    {
        errorDescription = "ERROR: couldn't initialize LED hardware";
        return false;
    }

    // simulate initialization delay
    RandomDelay(SimulationConfig::cInitializeDelay);

    // do hardware-related operations here
    m_on = on;
    m_color = color;
    m_rate = rate;

    m_initialized = true;

    std::cout << "DEBUG: LED controller successfully initialized\n";

    return true;
}

bool LedController::Deinitialize(string& errorDescription)
{
    if (!m_initialized)
    {
        return true;
    }

    // simulate hardware error
    if (Random() < SimulationConfig::cDeinitializeErrorProbability)
    {
        m_initialized = false; // set state in any case
        errorDescription = "ERROR: couldn't deinitialize LED hardware";
        return false;
    }

    // simulate deinitialization delay
    RandomDelay(SimulationConfig::cDeinitializeDelay);

    // do hardware-related operations here
    m_on = false;
    m_rate = 0;

    m_initialized = false;

    std::cout << "DEBUG: LED controller successfully deinitialized\n";

    return true;
}

bool LedController::SetLedState(bool on, string& errorDescription)
{
    if (!m_initialized)
    {
        errorDescription = "ERROR: couldn't set LED state: hardware not initialized";
        return false;
    }

    // simulate hardware error
    if (Random() < SimulationConfig::cSetLedStateErrorProbability)
    {
        errorDescription = "ERROR: couldn't set LED state: hardware error";
        return false;
    }

    // simulate hardware delay
    RandomDelay(SimulationConfig::cSetLedStateDelay);

    // do hardware-related operations here
    m_on = on;

    std::cout << "DEBUG: LED turned " << (m_on ? "on" : "off") << "\n";

    return true;
}

bool LedController::GetLedState(bool& on, string& errorDescription) const
{
    if (!m_initialized)
    {
        errorDescription = "ERROR: couldn't get LED state: hardware not initialized";
        return false;
    }

    // simulate hardware error
    if (Random() < SimulationConfig::cGetLedStateErrorProbability)
    {
        errorDescription = "ERROR: couldn't get LED state: hardware error";
        return false;
    }

    // simulate hardware delay
    RandomDelay(SimulationConfig::cGetLedStateDelay);

    // do hardware-related operations here
    on = m_on;

    return true;
}

bool LedController::SetLedColor(EColor color, string& errorDescription)
{
    if (!m_initialized)
    {
        errorDescription = "ERROR: couldn't set LED color: hardware not initialized";
        return false;
    }

    // check colors supported by LED
    if ((color != EColor::Red) && (color != EColor::Green) && (color != EColor::Blue))
    {
        errorDescription = "ERROR: specified LED color not supported";
        return false;
    }

    // simulate hardware error
    if (Random() < SimulationConfig::cSetLedColorErrorProbability)
    {
        errorDescription = "ERROR: couldn't set LED color: hardware error";
        return false;
    }

    // simulate hardware delay
    RandomDelay(SimulationConfig::cSetLedColorDelay);

    // do hardware-related operations here
    m_color = color;

    std::cout << "DEBUG: LED color set to '" << ColorToString(color) << "'\n";

    return true;
}

bool LedController::GetLedColor(EColor& color, string& errorDescription) const
{
    if (!m_initialized)
    {
        errorDescription = "ERROR: couldn't set LED state: hardware not initialized";
        return false;
    }

    // simulate hardware error
    if (Random() < SimulationConfig::cGetLedColorErrorProbability)
    {
        errorDescription = "ERROR: couldn't set LED color: hardware error";
        return false;
    }

    // simulate hardware delay
    RandomDelay(SimulationConfig::cGetLedColorDelay);

    // do hardware-related operations here
    color = m_color;

    return true;
}

bool LedController::SetLedRate(unsigned int rate, string& errorDescription)
{
    if (!m_initialized)
    {
        errorDescription = "ERROR: couldn't set LED rate: hardware not initialized";
        return false;
    }

    if (rate > cMaxLedRate)
    {
        errorDescription = "ERROR: couldn't set LED rate: specified rate is greater than max LED rate";
        return false;
    }

    // simulate hardware error
    if (Random() < SimulationConfig::cSetLedRateErrorProbability)
    {
        errorDescription = "ERROR: couldn't set LED rate: hardware error";
        return false;
    }

    // simulate hardware delay
    RandomDelay(SimulationConfig::cSetLedRateDelay);

    // do hardware-related operations here
    m_rate = rate;

    return true;
}

bool LedController::GetLedRate(unsigned int& rate, string& errorDescription) const
{
    if (!m_initialized)
    {
        errorDescription = "ERROR: couldn't get LED rate: hardware not initialized";
        return false;
    }

    // simulate hardware failure
    if (Random() < SimulationConfig::cGetLedRateErrorProbability)
    {
        errorDescription = "ERROR: couldn't get LED rate: hardware error";
        return false;
    }

    // simulate hardware delay
    RandomDelay(SimulationConfig::cGetLedRateDelay);

    // do hardware-related operations here
    rate = m_rate;

    return true;
}
