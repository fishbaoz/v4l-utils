#include "Fast_dehaze_cpu.h"
#include "dehaze_core.h"


void printMat(char *name, Mat m)
{
	cout << name << "\n" << m << endl;
	return ;
}
void printMatInfo(Mat *m)
{
	cout << "\t" << "cols = " << m->cols << endl;
	cout << "\t" << "rows = " << m->rows << endl;
	cout << "\t" << "channels = " << m->channels() << endl;
	return ;
}

Mat read_image(char *imgname)
{
	Mat img = imread(imgname, CV_LOAD_IMAGE_COLOR);
	Mat outimg(img.rows,img.cols,CV_8UC3);
	img.convertTo(outimg, CV_8UC3);
	return outimg;
}

int getM(Mat &M, Mat &M_max, const Mat &src, double &m_av)
{
	double sum = 0;
	for (int i = 0; i < src.rows; i++) 
	{
		for (int j = 0; j < src.cols; j++) 
		{
			uchar r, g, b;
			uchar temp1, temp2;
			r = src.at<Vec3b>(i,j)[0];
			g = src.at<Vec3b>(i,j)[1];
			b = src.at<Vec3b>(i,j)[2];
			temp1 = my_min(my_min(r, g), b);
			temp2 = my_max(my_max(r, g), b);
//			printf("temp1=%x, temp2=%x\n", temp1, temp2);
			M.at<uchar>(i, j) = temp1;
//			printf("temp1=%x, temp2=%x\n", temp1, temp2);
			M_max.at<uchar>(i, j) = temp2;
			sum += temp1;
//			printf("sum=%x\n", sum);
		}
	}
	m_av = sum / (src.rows * src.cols * 255);
	return 0;
}

int getAveM(Mat &M_ave, Mat &M, int r)
{
	boxFilter(M, M_ave, CV_8UC1, Size(r, r));

	return 0;
}
int getL(Mat &L, Mat &M, Mat &M_ave, double eps, double m_av)
{
	double delta = my_min(0.9, eps*m_av);
	for (int i = 0; i < M.rows; i++) 
	{
		for (int j = 0; j < M.cols; j++) 
		{
			L.at<uchar>(i, j) = (int)my_min(delta * M_ave.at<uchar>(i, j), M.at<uchar>(i, j));
		}
	}
	return 0;
}

int MaxMatrix(Mat &src)
{
	int temp = 0;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			temp = my_max(src.at<uchar>(i, j), temp);
		}
		if (temp == 255)
			return temp;
	}
	return temp;
}

double GetA(Mat &M_max, Mat &M_ave)
{
	return (MaxMatrix(M_max) + MaxMatrix(M_ave)) * 0.5;
}

int dehaze(unsigned char *dst, const Mat &src, Mat &L, double A)
{
	int temp, value;

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			temp = L.at<uchar>(i, j);
			for (int k = 0; k < 3; k++)
			{
				value = A*(src.at<Vec3b>(i,j)[k] - temp)/ (A-temp);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
//				printf("index=%d, %x\n", (i*src.cols+j)*3+k);
				dst[(i*src.cols+j)*3+k] = value;
			}
		}
	}
	return 0;
}

