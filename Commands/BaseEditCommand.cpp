#include "BaseEditCommand.hpp"

void BaseEditCommand::execute(const std::vector<std::string>& args, MainHandler& master)
{
	throw Event::notImplemented;
}
