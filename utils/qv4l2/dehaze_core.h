#ifndef DEHAZE_CORE_H
#define DEHAZE_CORE_H

const int r = 31;
const double eps = 1.8;

void printMat(char *imgname, Mat m); 
void printMatInfo(Mat *m);
Mat read_image(char *imagename);
int getM(Mat &M, Mat &M_max, const Mat &src, double &m_av);
int getAveM(Mat &M_ave, Mat &M, int r);
int getL(Mat &L, Mat &M, Mat &M_ave, double eps, double m_av);
int MaxMatrix(Mat &src);
double GetA(Mat &M_max, Mat &M_ave);
int dehaze(unsigned char *dst, const Mat &src, Mat &L, double A);

#endif
