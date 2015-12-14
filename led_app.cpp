// LED control application
// Author: I.G.
#include <iostream>
#include <exception>
#include "color.h"
#include "irequest_handler.h"
#include "led_controller.h"
#include "led_control_server.h"
#include "led_control_handlers.h"

static const bool cDefaultLedState = false;         // LED is off by default
static const EColor cDefaultLedColor = EColor::Red; // red color by default
static const bool cDefaultLedRate = 0;              // blinking is disabled by default

int main()
{
    LedController ledController;

    LedControlServer ledControlServer;
    // register request handlers
    ledControlServer.RegisterRequestHandler("set-led-state", SP_RequestHandler(new LedHandler_SetLedState(ledController)));
    ledControlServer.RegisterRequestHandler("get-led-state", SP_RequestHandler(new LedHandler_GetLedState(ledController)));
    ledControlServer.RegisterRequestHandler("set-led-color", SP_RequestHandler(new LedHandler_SetLedColor(ledController)));
    ledControlServer.RegisterRequestHandler("get-led-color", SP_RequestHandler(new LedHandler_GetLedColor(ledController)));
    ledControlServer.RegisterRequestHandler("set-led-rate", SP_RequestHandler(new LedHandler_SetLedRate(ledController)));
    ledControlServer.RegisterRequestHandler("get-led-rate", SP_RequestHandler(new LedHandler_GetLedRate(ledController)));
  
    string errorDescription;

    try
    {
        // set default LED parameters
        if (!ledController.Initialize(cDefaultLedState, cDefaultLedColor, cDefaultLedRate, errorDescription))
        {
            std::cout << "ERROR: couldn't initialize LED controller: " << errorDescription << "\n";
            return 1; // LED controller initialize error
        }

        ledControlServer.Start();

        std::cout << "Press ENTER to exit...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ledControlServer.Stop();

        if (!ledController.Deinitialize(errorDescription))
        {
            std::cout << "ERROR: couldn't deinitialize LED controller: " << errorDescription << "\n";
            return 2; // LED controller deinitialize error
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "FATAL ERROR: " << e.what() << "\n";
    }

    return 0;
}
