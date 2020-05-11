#include "MessageGetter.h"
#include "MessagesQueue.h"
#include "nlohmann/json.hpp"

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/NetException.h"

using json = nlohmann::json;

void MessageGetter::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    const auto& user = request.get("user");

    auto& queue = singleton<MessagesQueue>();

    if (queue.hasNext(user)) {
        auto res = queue.getNext(user);
        std::ostream& ostr = response.send();
        ostr << json{{"id", res.id()}, {"dest", res.dest()}, {"message", res.message()}};
        return;
    }
    throw Poco::NotFoundException("New messages not found");
}

