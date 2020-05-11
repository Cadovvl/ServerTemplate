#include "MessageAdder.h"
#include "MessagesQueue.h"
#include "nlohmann/json.hpp"

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/StreamCopier.h"

#include <istream>
#include <sstream>

using json = nlohmann::json;

void MessageAdder::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    std::stringstream str;
    Poco::StreamCopier::copyStream(request.stream(), str);
    std::string body(str.str());

    auto b = json::parse(body.begin(), body.end());

    auto& queue = singleton<MessagesQueue>();
    const Message m(b["dest"], b["message"]);
    queue.addMessage(m);

    json resp = {
            {"id", m.id()}
    };

    response.setContentType("application/json");
    std::ostream& ostr = response.send();

    ostr << resp.dump();
}
