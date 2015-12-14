#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "color.h"
#include <string>

using std::string;

// API for LED control
// note: all functions are blocking
class LedController
{
    bool          m_initialized;

    // LED state variables
    unsigned char m_on;
    EColor        m_color;
    unsigned int  m_rate;

public:
    LedController();
    ~LedController();

    // initialize/deinitialize hardware for working with LED
    // note: set initial parameters after hardware starting
    bool Initialize(bool on, EColor color, unsigned char rate, string& errorDescription);
    bool Deinitialize(string& errorDescription);

    bool SetLedState(bool on, string& errorDescription);
    bool GetLedState(bool& on, string& errorDescription) const;

    bool SetLedColor(EColor color, string& errorDescription);
    bool GetLedColor(EColor& color, string& errorDescription) const;

    bool SetLedRate(unsigned int rate, string& errorDescription);
    bool GetLedRate(unsigned int& rate, string& errorDescription) const;
};

#endif
