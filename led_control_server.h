#ifndef LED_CONTROL_SERVER_H
#define LED_CONTROL_SERVER_H

#include <vector>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include "irequest_handler.h"

using std::vector;
using std::string;
using std::map;

class LedControlServer
{
    map<string, SP_RequestHandler> m_requestHandlerMap;
    std::thread                    m_thread;
    std::mutex                     m_mutex;
    bool                           m_isRunning;

    void ProcessRequest(const string& request, string& response);

    void RequestProcessingThread();

public:
    LedControlServer();
    ~LedControlServer();

    bool RegisterRequestHandler(const string& requestId, SP_RequestHandler requestHandler);
    bool UnregisterRequestHandler(const string& requestId);

    bool IsRunning();

    void Start();
    void Stop();
};

#endif
