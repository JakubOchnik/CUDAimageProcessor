#pragma once
#include <exception>
#include <iostream>

namespace event
{
namespace error
{
struct IOopenFail : std::runtime_error
{
	IOopenFail() : std::runtime_error("Failed to open file."){};
};
struct IOsaveFail : std::runtime_error
{
	IOsaveFail() : std::runtime_error("Failed to save file."){};
};
struct CommandFail : std::runtime_error
{
	CommandFail() : std::runtime_error("Failed to execute the command."){};
};
struct IncorrectCommand : std::runtime_error
{
	IncorrectCommand() : std::runtime_error("Incorrect command."){};
};
struct ActionFail : std::runtime_error
{
	ActionFail() : std::runtime_error("Failed to perform the action."){};
};
struct ParamFail : std::runtime_error
{
	ParamFail() : std::runtime_error("Incorrect command parameters."){};
};
struct NotLoadedFail : std::runtime_error
{
	NotLoadedFail() : std::runtime_error("Image has not been loaded yet."){};
};
struct UndoFail : std::runtime_error
{
	UndoFail() : std::runtime_error("The history is empty."){};
};
struct RedoFail : std::runtime_error
{
	RedoFail() : std::runtime_error("There are no newer history entries."){};
};
struct GpuMallocFail : std::runtime_error
{
	GpuMallocFail() : std::runtime_error("Insufficient GPU memory."){};
};
struct MemoryFail : std::runtime_error
{
	MemoryFail() : std::runtime_error("Insufficient memory."){};
};
struct NotImplementedFail : std::runtime_error
{
	NotImplementedFail() : std::runtime_error("Function is not implemented."){};
};
} // namespace error
} // namespace event