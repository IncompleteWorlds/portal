
# Portal
Your Own Portal to Internet

Select, arrange and visualize the information that matters to you
on your own way

Created on July 25th 2024 by Alberto Fernandez, (c) Incomplete Worlds

## Compile

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Run

```sh
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/alberto/Documents/poco-install/lib
$ ./Portal
```
Replace `poco-install/lib` by the folder where all Poco libs are installed

## Notes

*Response*

set content type of the answer
`response.setContentType("text/html");`

either set the length of the content or use chunked transfer encoding

```cpp
response.setContentLength(1024);
response.setChunkedTransferEncoding(true);

response.setStatus[AndReason](HTTPResponse::HTTP_OK); // default
response.setStatus[AndReason](HTTPResponse::HTTP_UNAUTHORIZED)
```

after response is fully configured, send the header
`std::ostream& out = response.send()`


`response.setContentType("text/html");`

either set the length of the content or use chunked transfer encoding
```
response.setContentLength(1024);
response.setChunkedTransferEncoding(true);
```


helper class to handle HTML form data
```cpp
Poco::Net::HTMLForm form(request);
form[“entry1”] == “somedata”;
```

to handle file uploads (POST with attachments) you must combine it with a Poco::Net::PartHandler
```cpp
MyPartHandler myHandler;
Poco::Net::HTMLForm form(request, request.stream(), myHandler);

#include “Poco/Net/PartHandler.h”
#include “Poco/Net/MessageHeader.h”
class MyPartHandler: public Poco::Net::PartHandler
{
public:
    void handlePart(const Poco::Net::MessageHeader& header,
                    std::istream& stream)
    {
        _disp = header["Content-Disposition"];
        _type = header["Content-Type"];
        // read from stream and do something with it
    }

    private:
        std::string _disp;
        std::string _type;
};
```


Poco::Net::HTTPClientSession
> allows you set GET/POST
> authentication information


```cpp
using namespace Poco::Net;

HTTPClientSession s("www.somehost.com");
//s.setProxy("localhost", srv.port());

HTTPRequest request(HTTPRequest::HTTP_GET, "/large");
HTMLForm form;

form.add(“entry1”, “value1”);
form.prepareSubmit(request);

s.sendRequest(request);

HTTPResponse response;

std::istream& rs = s.receiveResponse(response);

StreamCopier::copyStream(rs, std::cout);
```