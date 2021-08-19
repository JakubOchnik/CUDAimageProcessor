#include "BaseEditCommand.hpp"

void BaseEditCommand::execute(const std::string& args, MainHandler& master)
{
	throw Event::notImplemented;
}
