#include "LUTapply.h"
#include "CubeLUT.h"
#include <opencv2/opencv.hpp>

void applyLUT(Img* image, float opacity, std::string path, GPUcontroller* GPU)
{
	CubeLUT lut;
	enum { OK = 0, ErrorOpenInFile = 100, ErrorOpenOutFile };

	ifstream infile(path);
	if (!infile.good())
	{
		cout << "Could not open input file " << path << endl;
	}
	int ret = lut.LoadCubeFile(infile);
	infile.close();

	// lut -> actual LUT

	cv::Mat_<cv::Vec3b> img = *(image->getImg());
	for (auto& pixel : img) {
		int b = pixel[0];
		int g = pixel[1];
		int r = pixel[2];

		// indeksy: 0-32
		// barwy: 0-255
		// barwy w LUT: 0-1
		// index = channel/255*32
		// barwa - interpolacja
		// jezeli nie ma dokladnie indeksu odpowiadajacego barwie, to musi byc interpolacja

		int R1 = ceil(r / 255.0f * (float)(lut.LUT3D.size() - 1));
		int R0 = floor(r / 255.0f * (float)(lut.LUT3D.size() - 1));
		int G1 = ceil(g / 255.0f * (float)(lut.LUT3D.size() - 1));
		int G0 = floor(g / 255.0f * (float)(lut.LUT3D.size() - 1));
		int B1 = ceil(b / 255.0f * (float)(lut.LUT3D.size() - 1));
		int B0 = floor(b / 255.0f * (float)(lut.LUT3D.size() - 1));
		float r_o = r * (lut.LUT3D.size() - 1) / 255.0f;
		float g_o = g * (lut.LUT3D.size() - 1) / 255.0f;
		float b_o = b * (lut.LUT3D.size() - 1) / 255.0f;

		float delta_r = (r_o - R0) / (float)(R1 - R0);
		float delta_g = (g_o - G0) / (float)(G1 - G0);
		float delta_b = (b_o - B0) / (float)(B1 - B0);

		auto mul = [](const vector<float>& vec, float val) {vector<float> newVec(3, 0.0f);  for (int i{ 0 }; i < 3; ++i) newVec[i] = vec[i] * val; return newVec; };
		auto sum = [](const vector<float>& a, const vector<float>& b) {vector<float> newVec(3, 0.0f); for (int i{ 0 }; i < 3; ++i) newVec[i] = a[i] + b[i]; return newVec; };
		vector<float> vr_gz_bz = sum(mul(lut.LUT3D[R0][G0][B0], 1 - delta_r), mul(lut.LUT3D[R0][G0][B0], delta_r));
		vector<float> vr_gz_bo = sum(mul(lut.LUT3D[R0][G0][B1], 1 - delta_r), mul(lut.LUT3D[R0][G0][B1], delta_r));
		vector<float> vr_go_bz = sum(mul(lut.LUT3D[R0][G1][B0], 1 - delta_r), mul(lut.LUT3D[R0][G1][B0], delta_r));
		vector<float> vr_go_bo = sum(mul(lut.LUT3D[R0][G1][B1], 1 - delta_r), mul(lut.LUT3D[R0][G1][B1], delta_r));

		vector<float> vrg_b0 = sum(mul(vr_gz_bz, 1 - delta_g), mul(vr_go_bz, delta_g));
		vector<float> vrg_b1 = sum(mul(vr_gz_bo, 1 - delta_g), mul(vr_go_bo, delta_g));

		vector<float> vrgb = sum(mul(vrg_b0, 1 - delta_b), mul(vrg_b1, delta_b));

		pixel[0] = round(vrgb[2] * 255); //b
		pixel[1] = round(vrgb[1] * 255); //g
		pixel[2] = round(vrgb[0] * 255); //r
	}
}