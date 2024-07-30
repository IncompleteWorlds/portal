#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "data_handler.h"
#include "root_handler.h"

void
handleRequest(Poco::Net::HTTPServerRequest& request,
              Poco::Net::HTTPServerResponse& response)
{
  if (!request.hasCredentials()) {
    response.requireAuthentication("My Realm");
    response.setContentLength(0);
    response.send();
    return;
  } else {
    Poco::Net::HTTPBasicCredentials cred(request);

    const std::string& user = cred.getUsername();
    const std::string& pwd = cred.getPassword();

    // [...]
  }
}

class MyRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
  MyRequestHandlerFactory() {}

  Poco::Net::HTTPRequestHandler* createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
  {
    if (request.getURI() == "/")
      return new RootHandler();
    else
      return new DataHandler();
  }
};

int
main(int argc, char* argv[])
{
  Poco::UInt16 port = 9999;

  HTTPServerParams* pParams = new HTTPServerParams();
  pParams->setMaxQueued(100);
  pParams->setMaxThreads(16);

  ServerSocket svs(port); // set-up a server socket

  HTTPServer srv(new MyRequestHandlerFactory(), svs, pParams);

  // start the HTTPServer
  srv.start();

  waitForTerminationRequest();

  // Stop the HTTPServer
  srv.stop();
}
