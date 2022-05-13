#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Img
{
	std::string	 path;
	unsigned int resolutionH;
	unsigned int resolutionW;
	int			 colorChannels;
	cv::Mat		 image;
	bool		 initiated;

public:
	Img();
	Img(cv::Mat img, std::string path);
	// = operator returns a deep copy of the Img class
	Img& operator=(const Img& other);

	std::string	   getPath() const;
	unsigned int   getResolutionH() const;
	unsigned int   getResolutionW() const;
	unsigned int   getChannelNum() const;
	const cv::Mat& getImg() const;
	bool		   getStatus() const;

	void setPath(const std::string& newPath);
	void setResolutionH(int newResH);
	void setResolutionW(int newResW);
	void setChannelNum(int newBitDepth);
	void setImg(cv::Mat& newMat);

	void updateAll(const std::string& newPath, cv::Mat& newMat);
	void updateAll(cv::Mat& newMat);
	void refreshDims();
};
