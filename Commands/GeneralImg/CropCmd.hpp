#pragma once
#include "../BaseEditCmd.hpp"
class CropCmd : public BaseEditCmd
{
	using BaseEditCmd::BaseEditCmd;
public:
	static inline const std::string displayName = "cropCommand";
	static inline const std::string shortName = "crop";

	void execute(const std::vector<std::string>& args) override;
	void cropAction(cv::Rect& area);

	std::string getShortName() override;
	std::string getDisplayName() override;
};