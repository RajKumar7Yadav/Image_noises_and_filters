// https://homepages.inf.ed.ac.uk/rbf/HIPR2/median.htm#:~:text=The%20median%20is%20calculated%20by,with%20the%20middle%20pixel%20value.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace cv;
using namespace std;

vector<int> arr;

Mat RGB2Gray(Mat input)
{
	Mat gray(input.rows, input.cols, CV_8UC1);
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			Vec3b pixel = input.at<Vec3b>(i, j);
			gray.at<uchar>(i, j) = (pixel[0] + pixel[1] + pixel[2])/3;
		}
	}
	return gray;
}

Mat mean_blur(Mat gray)
{
	Mat mblur_img(gray.rows, gray.cols, CV_8UC1);
	//Mat mblur_img = gray.clone();
	for (int i = 1; i < gray.rows-1; i++)
	{
		for (int j = 1; j < gray.cols-1; j++)
		{
			mblur_img.at<uchar>(i, j) = (gray.at<uchar>(i - 1, j - 1) + gray.at<uchar>(i - 1, j) + gray.at<uchar>(i - 1, j + 1)
				+ gray.at<uchar>(i, j - 1) + gray.at<uchar>(i, j) + gray.at<uchar>(i, j + 1)
				+ gray.at<uchar>(i + 1, j - 1) + gray.at<uchar>(i + 1, j) + gray.at<uchar>(i + 1, j + 1))/9;
		}
	}
	return mblur_img;
}

Mat gaussian_blur(Mat gray)
{
	Mat gblur_img(gray.rows, gray.cols, CV_8UC1);
	//Mat mblur_img = gray.clone();
	for (int i = 1; i < gray.rows - 1; i++)
	{
		for (int j = 1; j < gray.cols - 1; j++)
		{
			gblur_img.at<uchar>(i, j) = (gray.at<uchar>(i - 1, j - 1) + 2*gray.at<uchar>(i - 1, j) + 1*gray.at<uchar>(i - 1, j + 1)
				+ 2*gray.at<uchar>(i, j - 1) + 4*gray.at<uchar>(i, j) + 2*gray.at<uchar>(i, j + 1)
				+ 1*gray.at<uchar>(i + 1, j - 1) + 2*gray.at<uchar>(i + 1, j) + 1*gray.at<uchar>(i + 1, j + 1)) / 16;
		}
	}
	return gblur_img;
}

int Sort(vector<int> a, int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])
				min = j;
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
	if (n % 2 == 0)
		return ((a[n / 2] + a[n / 2 - 1]) / 2);
	if (n % 2 != 0)
		return(a[(n - 1) / 2]);
}

Mat median_filter(Mat gray)
{
	Mat median_img(gray.rows, gray.cols, CV_8UC1);
	//Mat mblur_img = gray.clone();
	for (int i = 1; i < gray.rows - 1; i++)
	{
		for (int j = 1; j < gray.cols - 1; j++)
		{
			arr = { gray.at<uchar>(i - 1, j - 1),gray.at<uchar>(i - 1, j),gray.at<uchar>(i - 1, j + 1),
				gray.at<uchar>(i, j - 1),gray.at<uchar>(i, j),gray.at<uchar>(i, j + 1),
				gray.at<uchar>(i + 1, j - 1),gray.at<uchar>(i + 1, j),gray.at<uchar>(i + 1, j + 1) };
			int size = sizeof(arr) / sizeof(arr[0]);
			median_img.at<uchar>(i,j)=Sort(arr, size);
		}
	}
	return median_img;
}

int main()
{
	Mat input_img = imread("salt_n_pepper.jpg");
	Mat gray_img = RGB2Gray(input_img);
	imshow("gray_image", gray_img);
	Mat mblur_img=mean_blur(gray_img);
	imshow("mblur_img", mblur_img);
	Mat gblur_img = gaussian_blur(gray_img);
	imshow("gblur_img", gblur_img);
	Mat median_img = median_filter(gray_img);
	imshow("median_img", median_img);
	waitKey(0);
}