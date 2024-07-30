/**
 * (c) Incomplete Worlds July 2024
 * Alberto Fernandez
 *
 * Your own Portal to your Internet
 */

#include <iostream>
#include <string>

using namespace std;

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;
using namespace std::string_literals;

const string DEFAULT_CONFIG_PATH = "./conf/Portal.properties";

class HelloRequestHandler : public HTTPRequestHandler
{
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Application &app = Application::instance();

        app.logger().information("Request from %s"s, request.clientAddress().toString());

        response.setChunkedTransferEncoding(true);
        response.setContentType("text/html"s);

        response.send()
            << "<html>"
            << "<head><title>Hello</title></head>"
            << "<body><h1>Hello from the POCO Web Server</h1></body>"
            << "</html>";
    }
};

class HelloRequestHandlerFactory : public HTTPRequestHandlerFactory
{
    /// The method should inspect the given HTTPServerRequest object (e.g., method
    /// and URI) and create an appropriate HTTPRequestHandler object to handle the
    /// request.

    HTTPRequestHandler *createRequestHandler(const HTTPServerRequest &)
    {
        return new HelloRequestHandler;
    }
};

class WebServerApp : public ServerApplication
{
    void initialize(Application &self)
    {
        loadConfiguration(DEFAULT_CONFIG_PATH);

        ServerApplication::initialize(self);

        // Add a File Logger
        string log_filename = config().getString("log_path", "./log").append("/portal.log");

        FormattingChannel *pFCFile = new FormattingChannel(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
        pFCFile->setChannel(new FileChannel(log_filename));
        pFCFile->open();

        Logger &fileLogger = Logger::create("FileLogger", pFCFile, Message::PRIO_INFORMATION);

        // Example
        // Logger::get("ConsoleLogger").error("Another error message");
        this->setLogger(fileLogger);
    }

    int main(const vector<string> &)
    {
        // Default port
        UInt16 port = config().getUInt16("port"s, 8080);

        HTTPServer srv(new HelloRequestHandlerFactory, port);

        srv.start();

        logger().information("HTTP Server started on port %hu."s, port);

        waitForTerminationRequest();

        logger().information("Stopping HTTP Server..."s);

        srv.stop();

        return Application::EXIT_OK;
    }
};

POCO_SERVER_MAIN(WebServerApp)