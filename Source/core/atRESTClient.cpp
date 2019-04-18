#pragma hdrstop
#include "atRESTClient.h"
#include "atRESTRequest.h"
//#include <IdHTTP.hpp>
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------

namespace at
{
using namespace std;
using namespace dsl;


//RESTClient::RESTClient(shared_ptr<Idhttp::TIdHTTP> client, const string& host)
//:
//mHTTPClient(client)
//{
//    if(!mHTTPClient)
//    {
//		mHTTPClient = shared_ptr<Idhttp::TIdHTTP>(new Idhttp::TIdHTTP());
//    }
}

RESTClient::~RESTClient()
{}

string RESTClient::getBaseURL()
{
    if(mServiceParameters)
	{
        return mServiceParameters->getBaseURL();
    }
    return "";
}

int RESTClient::executeRequest(RESTRequest& request, string& response)
{
    //Synchronous
    unique_ptr<TStringStream> zstrings (new TStringStream);
    string req;
    try
    {
        Log(lDebug) << "Request: " << request.getRequestURL();
        switch(request.getMethod())
        {
            case rmPost:
            break;

            case rmDelete:
                mHTTPClient->Delete(request.getRequestURL().c_str(), zstrings.get());
            break;

            case rmGet:
                req = (request.getRequestURL());
                mHTTPClient->Get(req.c_str(), zstrings.get());
            break;

            default:
            break;
        }

        response = stdstr(zstrings->DataString);
        return mHTTPClient->ResponseCode;
    }
    catch (const EIdHTTPProtocolException& e)
    {
        // an HTTP error occured, do something...
        // details about the HTTP error are in the exception object
        Log(lError) << "Bad stuff..";
        return -1;
    }
    catch (const EIdSocketError& e)
    {
        // an HTTP error occured, do something...
        // details about the HTTP error are in the exception object
        Log(lError) << "Bad stuff..";
        return -1;
    }

    catch (const EIdException& e)
    {
        // a non-HTTP Indy error occured, do something else...
        Log(lError) << "Bad stuff..";
        return -1;
    }
    catch (const Exception& e)
    {
        // some other error occured, do something else...
        return -1;
    }
    catch(...)
    {
        Log(lError) << "Something else..";
    }

    return -1;
}


}
