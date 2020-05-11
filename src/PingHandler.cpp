#include "PingHandler.h"


#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/NetException.h"

#include "Poco/URI.h"

#include "Poco/Logger.h"

#include "nlohmann/json.hpp"

#include <algorithm>



using json = nlohmann::json;

namespace {
  std::atomic<int> requestNum;
}

void PingHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
  
  Poco::Logger& logger = Poco::Logger::get("RequestFactory");
  logger.debug("ping request");
    
  ++requestNum;

  const auto& params = Poco::URI(request.getURI()).getQueryParameters(); // vec<pair<str, str>>

  /*
  logger.debug("Request headers");
  for (const auto& param: request) { // Name-ValueCollection
    logger.debug("Key: " + param.first + "; Value: " + param.second);
  }


  logger.debug("Request params");
  for (const auto& param: params) {
    logger.debug("Key: " + param.first + "; Value: " + param.second);
  }
  */
  

  auto val = find_if(std::begin(params), std::end(params), [](const auto& x) { return x.first == "value"; });
  
  if (val == std::end(params)) {
    // throw Poco::NotFoundException("Ping request should contain value");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND);
    response.send();
    return;
  }
  
  std::ostream& ostr = response.send();
  ostr << json{
    {"from", request.clientAddress().toString() },
    {"method", request.getMethod() },
    {"value", val->second },
    {"requestNumber", (int)requestNum}};

  response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
  
  logger.debug("Success");
}




