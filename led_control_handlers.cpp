#include <sstream>
#include <iostream>
#include "error_codes.h"
#include "led_control_handlers.h"

// set-led-state on, off OK, FAILED - turn on/run off LED

LedHandler_SetLedState::LedHandler_SetLedState(LedController& ledController)
    : m_ledController(ledController)
{
}

void LedHandler_SetLedState::ProcessRequest(const vector<string>& request, string& response)
{
    response = cResultString_Failed;

    if (request.size() != 2)
    {
        std::cout << "DEBUG: one argument expected in request\n";
        return; 
    }

    bool on = false;

    if (request[1] == "on")
    {
        on = true;
    }
    else if (request[1] == "off")
    {
        on = false;
    }
    else // error
    {
        std::cout << "DEBUG: bad request argument\n";
        return; 
    }

    string errorDescription;

    if (m_ledController.SetLedState(on, errorDescription))
    {
        response = cResultString_Ok;
    }
    else // error
    {
        std::cout << "DEBUG: LED error: " << errorDescription << "\n";
    }
}

// get-led-state OK on|off, FAILED - get LED state

LedHandler_GetLedState::LedHandler_GetLedState(LedController& ledController)
    : m_ledController(ledController)
{
}

void LedHandler_GetLedState::ProcessRequest(const vector<string>& request, string& response)
{
    response = cResultString_Failed;

    if (request.size() != 1)
    {
        std::cout << "DEBUG: no arguments expected in request\n";
        return; 
    }

    bool on;
    string errorDescription;

    if (m_ledController.GetLedState(on, errorDescription))
    {
        response = cResultString_Ok + (on ? " on" : " off");
    }
    else // error
    {
        std::cout << "DEBUG: LED error: " << errorDescription << "\n";
    }
}

// set-led-color red, green, blue OK, FAILED - set LED color

LedHandler_SetLedColor::LedHandler_SetLedColor(LedController& ledController)
    : m_ledController(ledController)
{
}

void LedHandler_SetLedColor::ProcessRequest(const vector<string>& request, string& response)
{
    response = cResultString_Failed;

    if (request.size() != 2)
    {
        std::cout << "DEBUG: one argument expected in request\n";
        return; 
    }

    EColor ledColor = EColor::Red;

    if (!ParseColor(request[1], ledColor))
    {
        std::cout << "DEBUG: bad request argument\n";
        return; 
    }

    string errorDescription;

    if (m_ledController.SetLedColor(ledColor, errorDescription))
    {
        response = cResultString_Ok;
    }
    else // error
    {
        std::cout << "DEBUG: LED error: " << errorDescription << "\n";
    }
}

// get-led-color OK red|green|blue, FAILED - get LED color

LedHandler_GetLedColor::LedHandler_GetLedColor(LedController& ledController)
    : m_ledController(ledController)
{
}

void LedHandler_GetLedColor::ProcessRequest(const vector<string>& request, string& response)
{
    response = cResultString_Failed;

    if (request.size() != 1)
    {
        std::cout << "bad request: no arguments expected\n";
        return; 
    }

    EColor ledColor;

    string errorDescription;

    if (m_ledController.GetLedColor(ledColor, errorDescription))
    {
        response = cResultString_Ok + " " + ColorToString(ledColor);
    }
    else // error
    {
        std::cout << "LED error: " << errorDescription << "\n";
    }
}

// set-led-rate 0..5 OK, FAILED - change LED rate

LedHandler_SetLedRate::LedHandler_SetLedRate(LedController& ledController)
    : m_ledController(ledController)
{
}

void LedHandler_SetLedRate::ProcessRequest(const vector<string>& request, string& response)
{
    response = cResultString_Failed;

    if (request.size() != 2)
    {
        std::cout << "DEBUG: one argument expected in request\n";
        return; 
    }

    if (request[1].empty())
    {
        std::cout << "DEBUG: bad request argument\n";
        return; 
    }

    unsigned int ledRate;

    std::stringstream ss;
    ss << std::dec << request[1];
    ss >> ledRate;

    if (ss.fail() || !ss.eof())
    {
        std::cout << "DEBUG: bad request argument\n";
        return; 
    }

    string errorDescription;

    if (m_ledController.SetLedRate(ledRate, errorDescription))
    {
        response = cResultString_Ok;
    }
    else // error
    {
        std::cout << "DEBUG: LED error: " << errorDescription << "\n";
    }
}

// get-led-rate OK 0..5, FAILED - get LED rate

LedHandler_GetLedRate::LedHandler_GetLedRate(LedController& ledController)
    : m_ledController(ledController)
{
}

void LedHandler_GetLedRate::ProcessRequest(const vector<string>& request, string& response)
{
    response = cResultString_Failed;

    if (request.size() != 1)
    {
        std::cout << "bad request: no arguments expected\n";
        return; 
    }

    unsigned int ledRate;
    string errorDescription;

    if (m_ledController.GetLedRate(ledRate, errorDescription))
    {
        std::ostringstream os;
        os << static_cast<unsigned short>(ledRate);
        response = cResultString_Ok + " " + os.str();
    }
    else // error
    {
        std::cout << "LED error: " << errorDescription << "\n";
    }
}
