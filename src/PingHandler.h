#pragma once

#include <Poco/Net/HTTPRequestHandler.h>

#include <atomic>

class PingHandler : public Poco::Net::HTTPRequestHandler {

public:
    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;
};


