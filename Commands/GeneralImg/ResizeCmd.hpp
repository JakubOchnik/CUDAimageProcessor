#pragma once
#include "../BaseEditCmd.hpp"
class ResizeCmd : public BaseEditCmd
{
	using BaseEditCmd::BaseEditCmd;
public:
	static inline const std::string displayName = "resizeCommand";
	static inline const std::string shortName = "resize";

	void execute(const std::vector<std::string>& args) override;
	void resizeAction(cv::Rect& area);

	std::string getShortName() override;
	std::string getDisplayName() override;
};