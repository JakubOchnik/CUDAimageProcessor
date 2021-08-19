#include "BaseCommand.hpp"

BaseCommand::BaseCommand(MainHandler* handler)
{
	if (handler != nullptr)
	{
		this->initialized = true;
		this->handler = handler;
	}
}

BaseCommand::BaseCommand()
{
	this->initialized = false;
	this->handler = nullptr;
}

std::string BaseCommand::getDisplayName() const
{
	return displayName;
}

