/*
 * Gateway.h
 *
 *  Created on: Jan 20, 2020
 *      Author: ltzd
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_

#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/ServerApplication.h"
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::ServerApplication;

class Gateway: public ServerApplication
{
public:
	Gateway();
	virtual ~Gateway();
	void initialize(Application& self);
	void uninitialize();
	void defineOptions(OptionSet& options);
	void handleOption(const std::string& name, const std::string& value);
	int main(const std::vector<std::string>& args);
};


#endif /* GATEWAY_H_ */
