// ImageMachinator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void cutROI(string imPathRoot, string imFileName, vector<Point> points);

int main()
{
	vector<Point> points;
	/*points.push_back(Point(56, 40));
	points.push_back(Point(524, 363));
	points.push_back(Point(89, 369));
	points.push_back(Point(479, 156));*/
	points.push_back(Point(40, 100));
	points.push_back(Point(200, 5));
	points.push_back(Point(311, 62));
	points.push_back(Point(465, 80));
	points.push_back(Point(536, 44));
	points.push_back(Point(636, 86));
	points.push_back(Point(491, 359));
	points.push_back(Point(236, 394));
	cutROI("D:\\Documents\\Pictures", "Koala.jpg", points);

    return 0;
}

void cutROI(string imPathRoot, string imFileName, vector<Point> points)
{
	string imPath = imPathRoot + "\\" + imFileName;
	int psize = points.size();
	Mat im = imread(imPath, CV_LOAD_IMAGE_COLOR);	//CV_LOAD_IMAGE_COLOR, CV_LOAD_IMAGE_GRAYSCALE
	bool imok = im.data != NULL;

	if (psize <= 8 && imok) {
		namedWindow("ImageDisplay", 1);

		for (auto it = points.begin(); it != points.end(); ++it) {
			int index = distance(points.begin(), it);
			Point p0, p1;
			if (index == 0) {
				p0 = points[psize - 1];
				p1 = points[0];
			}
			else {
				p0 = points[index - 1];
				p1 = points[index];
			}
			line(im, p0, p1, Scalar(0, 0, 0));
		}

		Mat mask = Mat::zeros(im.rows, im.cols, CV_8UC1);
		vector<vector<Point>> pts{ points };
		fillPoly(mask, pts, Scalar(255, 255, 255));

		Mat ROI;
		im.copyTo(ROI, mask);

		//imshow("ImageDisplay", ROI);
		//waitKey(0);

		string outImPath = imPathRoot + "\\out.jpg";
		try
		{
			imwrite(outImPath, ROI);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what();
		}
	}
	else {
		cout << "Init failed!" << endl;
	}
}