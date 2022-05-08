#pragma once
#include <Commands/BaseEditCmd.hpp>
#include <Commands/GpuImg/Kernels/ContrastKernel.cuh>

class ContrastCmd : public BaseEditCmd
{
	using BaseEditCmd::BaseEditCmd;

public:
	static inline const std::string displayName = "contrastCommand";
	static inline const std::string shortName	= "contrast";

	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};
