#include "BaseGenericCmd.hpp"

void BaseGenericCmd::execute(MainHandler& master, const std::string& args)
{
	throw Event::notImplemented;
}
