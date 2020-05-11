#include "EntityRequestHandlerFactory.h"
#include "PingHandler.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Logger.h>

#include <regex>

namespace {
    std::regex pingRegex("/ping\?.*");
}

Poco::Net::HTTPRequestHandler *EntityRequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
  
    Poco::Logger& logger = Poco::Logger::get("RequestFactory");
    logger.debug("Got message from URI " + request.getURI());

    // How to read request body
    /*

    std::stringstream str;
    Poco::StreamCopier::copyStream(request.stream(), str);
    std::string body(str.str());

    logger.debug("Got add message request with body " + body);

    auto b = json::parse(body.begin(), body.end());

     */
  
    std::smatch sm;
    if (std::regex_match(request.getURI(), sm, pingRegex)) { 
      logger.debug("Match ping request ");     
      return new PingHandler();
    }
    
    return nullptr;
}
