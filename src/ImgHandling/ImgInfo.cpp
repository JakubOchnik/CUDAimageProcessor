#include <ImgHandling/ImgInfo.hpp>
#include <opencv2/opencv.hpp>
#include <string>

Img::Img(cv::Mat img, std::string path) : image(img)
{
	this->path	  = path;
	resolutionH	  = img.size().height;
	resolutionW	  = img.size().width;
	colorChannels = img.channels();
	initiated	  = true;
}

Img::Img()
	: resolutionH(0)
	, resolutionW(0)
	, colorChannels(0)
	, image(cv::Mat())
	, initiated(false)
{
}

Img& Img::operator=(const Img& other)
{
	this->colorChannels = other.colorChannels;
	this->initiated		= other.initiated;
	this->resolutionH	= other.resolutionH;
	this->resolutionW	= other.resolutionW;
	this->path			= other.path;
	this->image			= other.image.clone();
	return *this;
}

std::string Img::getPath() const
{
	return path;
}

unsigned int Img::getResolutionH() const
{
	return resolutionH;
}

unsigned int Img::getResolutionW() const
{
	return resolutionW;
}

unsigned int Img::getChannelNum() const
{
	return colorChannels;
}

const cv::Mat& Img::getImg() const
{
	// image.data can be modified, as it
	// becomes char* const (data can be modified,
	// but the address can't)
	return image;
}

void Img::setPath(const std::string& newPath)
{
	path = newPath;
}

void Img::setResolutionH(int newResH)
{
	resolutionH = newResH;
}

void Img::setResolutionW(int newResW)
{
	resolutionW = newResW;
}

void Img::setChannelNum(int newBitDepth)
{
	colorChannels = newBitDepth;
}

void Img::setImg(cv::Mat& newMat)
{
	// This function is probably invoked by a command. After leaving it,
	// the original scope of newMat will be gone.
	// ...dangling reference?
	// Apparently not, as cv::Mat uses reference counting.
	// Technically you don't even have to pass it by reference!
	// There's some crazy magic happening there.
	image = newMat;
}

void Img::updateAll(const std::string& newPath, cv::Mat& newMat)
{
	setPath(newPath);
	setImg(newMat);
	setResolutionW(newMat.size().width);
	setResolutionH(newMat.size().height);
	setChannelNum(newMat.depth());
	initiated = true;
}

void Img::updateAll(cv::Mat& newMat)
{
	setImg(newMat);
	setResolutionW(newMat.size().width);
	setResolutionH(newMat.size().height);
	setChannelNum(newMat.channels());
	initiated = true;
}

bool Img::getStatus() const
{
	return initiated;
}
