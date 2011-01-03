//
// ApacheRequestHandlerFactory.h
//
// $Id: //poco/1.4/ApacheConnector/include/ApacheRequestHandlerFactory.h#1 $
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef ApacheConnector_ApacheRequestHandlerFactory_INCLUDED
#define ApacheConnector_ApacheRequestHandlerFactory_INCLUDED


#include "ApacheServerRequest.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/ClassLoader.h"
#include "Poco/Mutex.h"
#include <map>


class ApacheRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	ApacheRequestHandlerFactory();
		/// Constructs the ApacheRequestHandlerFactory

	~ApacheRequestHandlerFactory();
		/// Destructor of the ApacheRequestHandlerFactory

	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
		/// Creates a new request handler for the given HTTP request.

	bool mustHandle(const std::string& uri);
		/// Returns 1 if the given uri must be handled by the
		/// poco_mapper module, 0 otherwise.

	void handleURIs(const std::string& uris);
		/// Parses the given string for dllName, factoryName and the URIs to handle
		/// by the request-handler

	void addRequestHandlerFactory(const std::string& dllPath, const std::string& factoryName, const std::string& uri);
		/// Adds the request handler from the given dll with the given name and
		/// registers that handler with the given uri

private:
	typedef std::map<std::string, Poco::Net::HTTPRequestHandlerFactory*> RequestHandlerFactories;
	
	RequestHandlerFactories _requestHandlers;
	Poco::ClassLoader<Poco::Net::HTTPRequestHandlerFactory> _loader;
	Poco::FastMutex _mutex;
};


#endif // ApacheConnector_ApacheRequestHandlerFactory_INCLUDED
