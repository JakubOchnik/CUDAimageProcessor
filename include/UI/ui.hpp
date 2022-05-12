#pragma once

#include <Events/EventHistory.hpp>
#include <Events/History.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <tuple>

namespace ui
{
void clearScreen();
std::tuple<int, int>
customScale(cv::Mat& inputImage, Img& dstImg, unsigned int scale);
std::tuple<int, int, float> autoScale(cv::Mat&					  inputImage,
									  Img&						  dstImg,
									  const std::tuple<int, int>& origSize,
									  const std::tuple<int, int>& screenSize);
void						editHistoryScreen(const History& history);
void						showPreview(Img& dstImg, unsigned int scale = 0);
void						helpScreen();
void draw(const Img& dstImg, const EventHistory& events, bool loaded);
void setWindowName(const std::string& newName);
void printString(const std::string& output);
}; // namespace ui
