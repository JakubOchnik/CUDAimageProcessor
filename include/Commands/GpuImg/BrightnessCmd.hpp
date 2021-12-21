#pragma once
#include <Commands/BaseEditCmd.hpp>

#include <Commands/GpuImg/Kernels/BrightnessKernel.cuh>

class BrightnessCmd : public BaseEditCmd
{
    using BaseEditCmd::BaseEditCmd;
public:
    static inline const std::string displayName = "brightnessCommand";
	static inline const std::string shortName = "brightness";

	void execute(const std::vector<std::string>& args) override;
	void action(const int shift);

	std::string getShortName() override;
	std::string getDisplayName() override;
};