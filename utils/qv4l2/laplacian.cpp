//  基于Laplacian算子的图像边缘增强
//  Author： www.icvpr.com
//  Blog： http://blog.csdn.net/icvpr


#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <laplacian.h>
#include <stdio.h>
void edgeEnhance(cv::Mat& srcImg, cv::Mat& dstImg)
{
        if (!dstImg.empty())
        {
		dstImg.release();
        }

        std::vector<cv::Mat> rgb;

        if (srcImg.channels() == 3)        // rgb image
        {
		cv::split(srcImg, rgb);
        }
        else if (srcImg.channels() == 1)   // gray image
        {
		rgb.push_back(srcImg);
        }
//	printf("gaussian1\n");

        // 分别对R、G、B三个通道进行边缘增强
        for (size_t i = 0; i < rgb.size(); i++)
        {
		cv::Mat sharpMat8U;
		cv::Mat sharpMat;
		cv::Mat blurMat;

		// 高斯平滑
		//printf("laplacian\n");
		cv::GaussianBlur(rgb[i], blurMat, cv::Size(3,3), 0, 0);

//		std::cout<<"gaussian" <<std::endl;
		// 计算拉普拉斯
		cv::Laplacian(blurMat, sharpMat, CV_16S);

		// 转换类型
		sharpMat.convertTo(sharpMat8U, CV_8U);
		cv::add(rgb[i], sharpMat8U, rgb[i]);
        }


        cv::merge(rgb, dstImg);
}

/* main */
int laplacian(int argc, char** argv)
{
        cv::Mat image = cv::imread("./lena.jpg");
        if (image.empty())
        {
		std::cout<<"read image failure"<<std::endl;
		return -1;
        }

        // rgb
        cv::Mat resultRgb;
        edgeEnhance(image, resultRgb);
        cv::imwrite("./outRgb.jpg", resultRgb);

        // gray
        cv::Mat gray;
        cv::cvtColor(image, gray, CV_BGR2GRAY);
        cv::imwrite("./gray.jpg", gray);

        cv::Mat resultGray;
        edgeEnhance(gray, resultGray);
        cv::imwrite("./outGray.jpg", resultGray);

        return 0;
}
