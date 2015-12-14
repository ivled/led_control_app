// request handler interface
#ifndef IREQUEST_HANDLER_H
#define IREQUEST_HANDLER_H

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;

class IRequestHandler
{
public:
    IRequestHandler() { };
    virtual ~IRequestHandler() { };
    //
    virtual void ProcessRequest(const vector<string>& request, string& response) = 0;
};

typedef std::shared_ptr<IRequestHandler> SP_RequestHandler;

#endif
