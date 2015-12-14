#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <iterator>
#include <functional>
#include "error_codes.h"
#include "led_control_server.h"

static const char* cLedControlRequestPipePath = "/tmp/led_control_request";
static const char* cLedControlResponsePipePath = "/tmp/led_control_response";

LedControlServer::LedControlServer()
    : m_isRunning(false)
{
}

LedControlServer::~LedControlServer()
{
    Stop();
}

void LedControlServer::ProcessRequest(const string& request, string& response)
{
    vector<string> requestParts;

    std::cout << "Process request: '" << request << "'\n";

    // split string into parts
    std::istringstream input_stream(request);
    copy(std::istream_iterator<string>(input_stream), std::istream_iterator<string>(), std::back_inserter(requestParts));

    if (requestParts.size() < 1)
    {
        std::cout << "LED control server error: bad request format\n";
        response = cResultString_Failed;
        return;
    }

    // get request handler
    map<string, SP_RequestHandler>::iterator it = m_requestHandlerMap.find(requestParts[0]);
    if (it == m_requestHandlerMap.end())
    {
        std::cout << "LED control server error: unknown request '" << requestParts[0] << "'\n";
        response = cResultString_Failed;
        return;
    }

    // note: message dispatching can be added here for multiple clients support

    // process request with the help of proper request handler
    it->second->ProcessRequest(requestParts, response);
}

void LedControlServer::RequestProcessingThread()
{
    // set running flag
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_isRunning = true;
    }

    // unlink existing pipes before creating new pipes
    unlink(cLedControlRequestPipePath);
    unlink(cLedControlResponsePipePath);

    // create LED control read and write pipes
    mkfifo(cLedControlRequestPipePath, 0600);
    mkfifo(cLedControlResponsePipePath, 0600);

    int ledControlReadPipeDescriptor = open(cLedControlRequestPipePath, O_RDWR | O_NONBLOCK);
    if (ledControlReadPipeDescriptor < 0)
    {
        std::cout << "LED control read pipe open error\n";
        return;
    }

    int ledControlWritePipeDescriptor = open(cLedControlResponsePipePath, O_RDWR | O_NONBLOCK);
    if (ledControlWritePipeDescriptor < 0)
    {
        std::cout << "LED control write pipe open error\n";
        return;
    }

    string request, response;

    while (IsRunning())
    {
        fd_set set;
        //
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        //
        FD_ZERO(&set);                              // clear the set
        FD_SET(ledControlReadPipeDescriptor, &set); // add named pipe descriptor to the set

        // waiting for message
        int rv = select(ledControlReadPipeDescriptor+1, &set, NULL, NULL, &timeout);
        if (rv == -1)
        {
            std::cout << "LED control read pipe error\n";
            continue; // exit?
        }
        else if (rv == 0)
        {
            continue; // timeout
        }

        char buffer[256];

        int receivedBytes = read(ledControlReadPipeDescriptor, buffer, sizeof(buffer));
        if (receivedBytes < 0)
        {
            std::cout << "LED control read pipe buffer reading error\n";
            continue;
        }
        if (receivedBytes == 0)
        {
            continue;
        }

        // analyze received data

        for (size_t i = 0; i < receivedBytes; i++)
        {
            if (buffer[i] == '\n')
            {
                // process request (accumulated data)
                ProcessRequest(request, response);

                // build response buffer
                memcpy(buffer, response.c_str(), response.size());
                buffer[response.size()] = '\n';

                // write response
                // note: including terminating zero
                int r = write(ledControlWritePipeDescriptor, buffer, response.size() + 1);
                if (r < 0)
                {
                    std::cout << "LED control write pipe error\n";
                }

                // clear request string after processing
                request.clear();

                break;
            }
            if (buffer[i] < 32)
            {
                std::cout << "bad data received\n"; // skip this request
                continue;
            }
            request += buffer[i];
        }
    }

    close(ledControlReadPipeDescriptor);
    close(ledControlWritePipeDescriptor);

    unlink(cLedControlRequestPipePath);
    unlink(cLedControlResponsePipePath);
}

bool LedControlServer::RegisterRequestHandler(const string& requestId, SP_RequestHandler requestHandler)
{
    if (m_requestHandlerMap.find(requestId) != m_requestHandlerMap.end())
    {
        return false; // specified handler already registered
    }

    m_requestHandlerMap.insert(std::make_pair(requestId, requestHandler));

    return true;
}

bool LedControlServer::UnregisterRequestHandler(const string& requestId)
{
    if (m_requestHandlerMap.find(requestId) == m_requestHandlerMap.end())
    {
        return false; // specified handler not found
    }

    m_requestHandlerMap.erase(requestId);

    return true;
}

bool LedControlServer::IsRunning()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_isRunning;
}

void LedControlServer::Start()
{
    m_thread = std::thread(&LedControlServer::RequestProcessingThread, this);
    std::cout << "DEBUG: LED control server successfully started\n";
}

void LedControlServer::Stop()
{
    if (!m_isRunning)
    {
        return;
    }

    // reset running flag to stop dispatching loop
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_isRunning = false;
    }

    m_thread.join();

    std::cout << "DEBUG: LED control server successfully stopped\n";
}
