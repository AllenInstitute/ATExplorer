#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace Poco::Net;
using namespace Poco;
using namespace std;

bool doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request,
              Poco::Net::HTTPResponse& response);
main()
{
    URI uri("http://localhost/render-ws/v1/likelyUniqueId");
    string path(uri.getPathAndQuery());
    if (path.empty()) path = "/";
    HTTPClientSession session(uri.getHost(), uri.getPort());
    HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    HTTPResponse response;

    if (!doRequest(session, request, response))
    {
        cerr << "Invalid username or password" << endl;
        return 1;
    }
}

bool doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response)
{
    session.sendRequest(request);
    istream& rs = session.receiveResponse(response);

   	StreamCopier::copyStream(rs, cout);
//    Poco::JSON::Parser parser;
//    Poco::JSON::Object::Ptr ret = parser.parse(s).extract<Poco::JSON::Object::Ptr>();
//
//    // (*ret) will contain all the members in a json structure returned
//    if ((*ret).get("success") != true) {
//        std::cout << "Failed to upload: " << (*ret).get("message").toString();
//        return;
//    }



    cout << response.getStatus() << " " << response.getReason() << endl;
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
    {
        ofstream ofs("Poco_banner.jpg", fstream::binary);
        StreamCopier::copyStream(rs, ofs);
        return true;
    }
    else
    {
        //it went wrong ?
        return false;
    }
}

#pragma comment(lib, "poco_foundation")
#pragma comment(lib, "poco_net")
