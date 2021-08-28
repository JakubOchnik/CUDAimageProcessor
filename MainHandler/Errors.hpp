#pragma once
#include <iostream>
#include <exception>

namespace Error
{
	struct IOopenFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Failed to open file.";
		}
	};
	struct IOsaveFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Failed to save file.";
		}
	};
	struct CommandFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Failed to execute the command.";
		}
	};
	struct ActionFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Failed to perform the action.";
		}
	};
	struct ParamFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Incorrect command parameters.";
		}
	};
	struct NotLoadedFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Image has not been loaded yet.";
		}
	};
	struct UndoFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "The history is empty.";
		}
	};
	struct RedoFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "There are no newer history entries.";
		}
	};
	struct GpuMallocFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Insufficient GPU memory.";
		}
	};
	struct NotImplementedFail : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "Command is not implemented.";
		}
	};
}
