#ifndef LED_CONTROL_HANDLERS_H
#define LED_CONTROL_HANDLERS_H

#include "irequest_handler.h"
#include "led_controller.h"

// set-led-state on, off OK, FAILED - turn on/run off LED
class LedHandler_SetLedState : public IRequestHandler
{
    LedController& m_ledController;
public:
    LedHandler_SetLedState(LedController& ledController);
    virtual ~LedHandler_SetLedState() { };
    //
    virtual void ProcessRequest(const vector<string>& request, string& response);
};

// get-led-state OK on|off, FAILED - get LED state
class LedHandler_GetLedState : public IRequestHandler
{
    LedController& m_ledController;
public:
    LedHandler_GetLedState(LedController& ledController);
    virtual ~LedHandler_GetLedState() { };
    //
    virtual void ProcessRequest(const vector<string>& request, string& response);
};

// set-led-color red, green, blue OK, FAILED - set LED color
class LedHandler_SetLedColor : public IRequestHandler
{
    LedController& m_ledController;
public:
    LedHandler_SetLedColor(LedController& ledController);
    virtual ~LedHandler_SetLedColor() { };
    //
    virtual void ProcessRequest(const vector<string>& request, string& response);
};

// get-led-color OK red|green|blue, FAILED - get LED color
class LedHandler_GetLedColor : public IRequestHandler
{
    LedController& m_ledController;
public:
    LedHandler_GetLedColor(LedController& ledController);
    virtual ~LedHandler_GetLedColor() { };
    //
    virtual void ProcessRequest(const vector<string>& request, string& response);
};

// set-led-rate 0..5 OK, FAILED - change LED rate
class LedHandler_SetLedRate : public IRequestHandler
{
    LedController& m_ledController;
public:
    LedHandler_SetLedRate(LedController& ledController);
    virtual ~LedHandler_SetLedRate() { };
    //
    virtual void ProcessRequest(const vector<string>& request, string& response);
};

// get-led-rate OK 0..5, FAILED - get LED rate
class LedHandler_GetLedRate : public IRequestHandler
{
    LedController& m_ledController;
public:
    LedHandler_GetLedRate(LedController& ledController);
    virtual ~LedHandler_GetLedRate() { };
    //
    virtual void ProcessRequest(const vector<string>& request, string& response);
};

#endif
