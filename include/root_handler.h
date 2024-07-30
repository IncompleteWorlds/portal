#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

class RootHandler : public Poco::Net::HTTPRequestHandler
{
public:
  void handleRequest(Poco::Net::HTTPServerRequest& request,
                     Poco::Net::HTTPServerResponse& response)
  {
    Application& app = Application::instance();

    app.logger().information("Request from " +
                             request.clientAddress().toString());

    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream& ostr = response.send();

    ostr << "<html><head><title>HTTP Server powered by POCO C++ Libraries</ "
            "title> </head>";
    ostr << "<body>";
    // [...]
    ostr << "</body></html>";
  }
};