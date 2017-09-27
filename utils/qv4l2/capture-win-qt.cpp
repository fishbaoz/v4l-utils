/* qv4l2: a control panel controlling v4l2 devices.
 *
 * Copyright (C) 2006 Hans Verkuil <hverkuil@xs4all.nl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "capture-win-qt.h"
#include "laplacian.h"

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

/* also need to change the Makefile.am */
#define _USE_OPENCL_ 0
#if !_USE_OPENCL_
#include "dehaze_core.h"
Mat M;
Mat M_max;
Mat M_ave;
Mat L;
Mat dst;
double m_av, A;
#else
#include "dehaze_core_opencl.h"
float g_fps = 0;
clock_t g_time = 0;
clock_t g_lastTime = 0;
Context context;
CommandQueue commandqueue;
Program program;

Kernel getM_kernel = NULL;
Kernel box_filter_horizontal_kernel = NULL;
Kernel box_filter_vertical_kernel = NULL;
Kernel getL_kernel = NULL;
Kernel getTable_kernel = NULL;
Kernel dehaze_kernel = NULL;
unsigned char *gpu_image = NULL;
cl_mem M, M_max, M_temp, M_ave, L, dst;

#define GROUPSIZE 256
#define R 31

#endif

void init_cl();
void create_buffer(int size);
void init_buffer(int height, int width);

CaptureWinQt::CaptureWinQt(ApplicationWindow *aw) :
	CaptureWin(aw),
	m_image(new QImage(0, 0, QImage::Format_Invalid)),
	m_data(NULL),
	m_supportedFormat(false),
	m_filled(false),
	m_cropBytes(0),
	m_cropOffset(0)
{
	m_videoSurface = new QLabel(this);
	#if _USE_OPENCL_
	init_cl();
	//create_buffer(1280*720);
	//create_buffer(1280*1920);
	create_buffer(900*1600);
	#else
	//init_buffer(720, 1280);
	init_buffer(768, 1024);
	#endif
	CaptureWin::buildWindow(m_videoSurface);
}

CaptureWinQt::~CaptureWinQt()
{
	delete m_image;
}

void CaptureWinQt::resizeEvent(QResizeEvent *event)
{
	// Get size of frame viewport.
	QSize margins = getMargins();
	m_windowSize = size() - margins;
	// Re-calculate sizes
	m_frame.updated = true;
	CaptureWin::updateSize();
	// Draw
	paintFrame();
	event->accept();
}

void CaptureWinQt::setRenderFrame()
{
	// Get/copy (TODO: use direct?)
	m_data = m_frame.planeData[0];

	QImage::Format dstFmt;
	m_supportedFormat = findNativeFormat(m_frame.format, dstFmt);
	if (!m_supportedFormat)
		dstFmt = QImage::Format_RGB888;

	if (m_frame.updated || m_image->format() != dstFmt ||
	    m_image->width() != m_frame.size.width() ||
	    m_image->height() != m_frame.size.height()) {
		delete m_image;
		m_image = new QImage(m_frame.size.width(),
				     m_frame.size.height(),
				     dstFmt);
	}

	m_frame.updated = false;

	paintFrame();
}
#if !_USE_OPENCL_
void init_buffer(int height, int width)
{
	Mat TM(height, width, CV_8UC1, Scalar::all(0));
	Mat TM_max(height, width, CV_8UC1, Scalar::all(0));
	Mat TM_ave(height, width, CV_8UC1, Scalar::all(0));
	Mat TL(height, width, CV_8UC1, Scalar::all(0));
	Mat Tdst(height, width, CV_8UC3, Scalar::all(0));

	TM.copyTo(M);
	TM_max.copyTo(M_max);
	TM_ave.copyTo(M_ave);
	TL.copyTo(L);
	Tdst.copyTo(dst);
}
int dehaze_core(Mat &src, unsigned char *data)
{
	#if !_USE_OPENCL_
	getM(M, M_max, src, m_av);
	getAveM(M_ave, M, r);
	getL(L, M, M_ave, eps, m_av);
	A = GetA(M_max, M_ave);
	dehaze(data, src, L, A);
	#endif
	return 0;
}
#endif

#if _USE_OPENCL_
void init_cl()
{
	context = CreateContext(GPU);
	CheckErr((context).context != NULL,"Create context failed");
	commandqueue = CreateCommandQueue(context);
	CheckErr(commandqueue != NULL, "Create command queue failed");
	program = CreateProgram(kernel_file, &context);
	CheckErr(program != NULL, "CreateProgram");
	CreateKernel(&getM_kernel, &program, "getM");
	CreateKernel(&box_filter_horizontal_kernel, &program, "box_filter_horizontal");
	CreateKernel(&box_filter_vertical_kernel, &program, "box_filter_vertical");
	CreateKernel(&getL_kernel, &program, "getL");
	CreateKernel(&dehaze_kernel, &program, "dehaze");
	return ;
}

void create_buffer(int size)

{
	cl_int errNum;
	gpu_image = (unsigned char *)malloc(size* 3 * sizeof(unsigned char));
	assert(gpu_image);
	M = clCreateBuffer(context.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, (size)*sizeof(unsigned char), NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS,"clCreateBuffer for M");
	M_max = clCreateBuffer(context.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, (size)*sizeof(unsigned char), NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS,"clCreateBuffer for M_max");
	M_temp = clCreateBuffer(context.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, (size) * sizeof(unsigned char), NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clCreateBuffer for M_temp");
	M_ave = clCreateBuffer(context.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, (size) * sizeof(unsigned char), NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clCreateBuffer for M_ave");
	L = clCreateBuffer(context.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, (size)*sizeof(unsigned char), NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clCreateBuffer for L");
	dst = clCreateBuffer(context.context, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, (size*3)*sizeof(unsigned char), NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clCreateBuffer for dst");

	return ;
}

unsigned char *dehaze_core(unsigned char *data, int height, int width)
{

	int size = height * width;
	cl_mem src;
	cl_int errNum;
	src = clCreateBuffer(context.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, size * 3 * sizeof(unsigned char), data, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clCreateBuffer for src");
	errNum  = clSetKernelArg(getM_kernel, 0, sizeof(cl_mem), &M);
	errNum |= clSetKernelArg(getM_kernel, 1, sizeof(cl_mem), &M_max);
	errNum |= clSetKernelArg(getM_kernel, 2, sizeof(cl_mem), &src);
	CheckErr(errNum == CL_SUCCESS, "clSetKernelArg for getM_kernel");
	size_t globalWorkSize[2] = {(size_t)width, (size_t)height};
	size_t localWorkSize[2] = {256, 1};
	errNum = clEnqueueNDRangeKernel(commandqueue, getM_kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueNDRange for getM_kernel");
	clFinish(commandqueue);


	errNum = clSetKernelArg(box_filter_horizontal_kernel, 0, sizeof(cl_mem), &M);
	errNum |= clSetKernelArg(box_filter_horizontal_kernel, 1, sizeof(cl_mem), &M_temp);
	errNum |= clSetKernelArg(box_filter_horizontal_kernel, 2, sizeof(unsigned char)*(GROUPSIZE+R-1), 0);
	CheckErr(errNum == CL_SUCCESS, "clSetKenrelArg for box_filter_horizontal_kernel");
	errNum = clEnqueueNDRangeKernel(commandqueue, box_filter_horizontal_kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueNDRange for box_filter_horizontal_kernel");
	clFinish(commandqueue);

	errNum = clSetKernelArg(box_filter_vertical_kernel, 0, sizeof(cl_mem), &M_temp);
	errNum |= clSetKernelArg(box_filter_vertical_kernel, 1, sizeof(cl_mem), &M_ave);
	CheckErr(errNum == CL_SUCCESS, "clSetKenrelArg for box_filter_vertical_kernel");
	errNum = clEnqueueNDRangeKernel(commandqueue, box_filter_vertical_kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueNDRange for box_filter_vertical_kernel");
	clFlush(commandqueue);

	unsigned char*M_gpu;
	double M_av = 0;
	M_gpu = (unsigned char*)clEnqueueMapBuffer(commandqueue, M, CL_TRUE, CL_MAP_READ | CL_MAP_WRITE, 0, size*sizeof(unsigned char), 0, NULL, NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueMapBuffer for M_gpu");
	M_av = getAve(M_gpu, height, width);
	errNum = clEnqueueUnmapMemObject(commandqueue, M, M_gpu, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueUnmapMemObject for M");
	clFinish(commandqueue);

	errNum = clSetKernelArg(getL_kernel, 0, sizeof(cl_mem), &L);
	errNum |= clSetKernelArg(getL_kernel, 1, sizeof(cl_mem), &M);
	errNum |= clSetKernelArg(getL_kernel, 2, sizeof(cl_mem), &M_ave);
	errNum |= clSetKernelArg(getL_kernel, 3, sizeof(double), &M_av);
	CheckErr(errNum == CL_SUCCESS, "clSetKenrelArg for getL_kernel");
	errNum = clEnqueueNDRangeKernel(commandqueue, getL_kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueNDRange for getL_kernel");
	clFlush(commandqueue);

	unsigned char*M_max_gpu, *M_ave_gpu;
	M_max_gpu = (unsigned char*)clEnqueueMapBuffer(commandqueue, M_max, CL_TRUE, CL_MAP_READ | CL_MAP_WRITE, 0, size*sizeof(unsigned char), 0, NULL, NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueMapBuffer for M_max_gpu");
	M_ave_gpu = (unsigned char*)clEnqueueMapBuffer(commandqueue, M_ave, CL_TRUE, CL_MAP_READ | CL_MAP_WRITE, 0, size*sizeof(unsigned char), 0, NULL, NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueMapBuffer for M_ave_gpu");
	double A = 0;
	A = GetA(M_max_gpu, M_ave_gpu, height, width);
	errNum = clEnqueueUnmapMemObject(commandqueue, M_ave, M_ave_gpu, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueUnmapMemObject for M_ave");
	errNum = clEnqueueUnmapMemObject(commandqueue, M_max, M_max_gpu, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueUnmapMemObject for M_max");
	clFinish(commandqueue);

	errNum = clSetKernelArg(dehaze_kernel, 0, sizeof(cl_mem), &dst);
	errNum |= clSetKernelArg(dehaze_kernel, 1, sizeof(cl_mem), &src);
	errNum |= clSetKernelArg(dehaze_kernel, 2, sizeof(cl_mem), &L);
	errNum |= clSetKernelArg(dehaze_kernel, 3, sizeof(double), &A);
	CheckErr(errNum == CL_SUCCESS, "clSetKenrelArg for dehaze_kernel");
	errNum = clEnqueueNDRangeKernel(commandqueue, dehaze_kernel, 2, NULL, globalWorkSize,localWorkSize, 0, NULL, NULL);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueNDRange for dehaze_kernel");
	clFinish(commandqueue);

	unsigned char *dst_gpu = NULL;
	dst_gpu = (unsigned char*)clEnqueueMapBuffer(commandqueue, dst, CL_TRUE, CL_MAP_READ | CL_MAP_WRITE, 0, size*3*sizeof(unsigned char), 0, NULL, NULL, &errNum);
	CheckErr(errNum == CL_SUCCESS, "clEnqueueMapBuffer for dst_gpu");

	clReleaseMemObject(src);

	return dst_gpu;
}

void free_cl()
{
	clReleaseContext(context.context);
	clReleaseCommandQueue(commandqueue);
	clReleaseProgram(program);
	clReleaseMemObject(dst);
	clReleaseKernel(dehaze_kernel);
	clReleaseMemObject(L);
	clReleaseKernel(getL_kernel);
	clReleaseMemObject(M_ave);
	clReleaseKernel(box_filter_vertical_kernel);
	clReleaseMemObject(M_temp);
	clReleaseKernel(box_filter_horizontal_kernel);
	clReleaseMemObject(M);
	clReleaseMemObject(M_max);
	clReleaseKernel(getM_kernel);
	free(gpu_image);
	return ;
}
#endif


void CaptureWinQt::paintFrame()
{
	if (m_crop.updated) {
		m_cropOffset = m_crop.delta.height() * (m_image->depth() / 8)
			* m_frame.size.width()
			+ m_crop.delta.width() * (m_image->depth() / 8);

		// Even though the values above can be valid, it might be that
		// there is no data at all. This makes sure that it is.
		m_cropBytes =  m_crop.size.width() * m_crop.size.height()
			* (m_image->depth() / 8);
		m_crop.updated = false;
	}

	if (!m_supportedFormat || !m_cropBytes) {
		if (!m_filled) {
			m_filled = true;
			m_image->fill(0);
			QPixmap img = QPixmap::fromImage(*m_image);
			m_videoSurface->setPixmap(img);
		}
		return;
	}
	m_filled = false;

	unsigned char *data = (m_data == NULL) ? m_image->bits() : m_data;
//	printf("format=%x, h=%d, w=%d, data=%x\n", m_image->format(), m_image->height(), m_image->width(), data);


	if (m_appWin->enhanceVideoFlag) {
		#if _USE_OPENCL_
		data = dehaze_core(data, m_image->height(), m_image->width());
		#else
		Mat src(m_image->height(), m_image->width(), CV_8UC3, data), dst, gray;
	//	init_buffer(m_image->height(), m_image->width());
	//	edgeEnhance(src, dst);
	//	cv::imwrite("capture.jpg", src);
	//	cvtColor(src, gray, CV_BGR2GRAY);
	//	gray.convertTo(gray, CV_8UC3);
	//	cv::imwrite("gray.jpg", gray);
	//	data = gray.data;
	//	dst.convertTo(dst, CV_8UC3);
	//	sharpenImage2(src,dst);
	//	data = dst.data;

		dehaze_core(src, data);
//		data = dst.data;
		#endif
	}
	QImage displayFrame(&data[m_cropOffset],
			    m_crop.size.width(), m_crop.size.height(),
			    m_image->width() * (m_image->depth() / 8),
			    m_image->format());

	QPixmap img = QPixmap::fromImage(displayFrame);

	// No scaling is performed by scaled() if the scaled size is equal to original size
	img = img.scaled(m_scaledSize.width(), m_scaledSize.height(), Qt::IgnoreAspectRatio);

	m_videoSurface->setPixmap(img);
}

void CaptureWinQt::stop()
{
	if (m_data != NULL)
#if QT_VERSION >= 0x050000
		memcpy(m_image->bits(), m_data, m_image->byteCount());
#else
		memcpy(m_image->bits(), m_data, m_image->numBytes());
#endif
	m_data = NULL;
}

bool CaptureWinQt::hasNativeFormat(__u32 format)
{
	QImage::Format fmt;
	return findNativeFormat(format, fmt);
}

bool CaptureWinQt::findNativeFormat(__u32 format, QImage::Format &dstFmt)
{
	static const struct {
		__u32 v4l2_pixfmt;
		QImage::Format qt_pixfmt;
	} supported_fmts[] = {
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
		{ V4L2_PIX_FMT_RGB32, QImage::Format_RGB32 },
		{ V4L2_PIX_FMT_XRGB32, QImage::Format_RGB32 },
		{ V4L2_PIX_FMT_ARGB32, QImage::Format_ARGB32 },
		{ V4L2_PIX_FMT_RGB24, QImage::Format_RGB888 },
		{ V4L2_PIX_FMT_RGB565X, QImage::Format_RGB16 },
		{ V4L2_PIX_FMT_RGB555X, QImage::Format_RGB555 },
#else
		{ V4L2_PIX_FMT_BGR32, QImage::Format_RGB32 },
		{ V4L2_PIX_FMT_XBGR32, QImage::Format_RGB32 },
		{ V4L2_PIX_FMT_ABGR32, QImage::Format_ARGB32 },
		{ V4L2_PIX_FMT_RGB24, QImage::Format_RGB888 },
		{ V4L2_PIX_FMT_RGB565, QImage::Format_RGB16 },
		{ V4L2_PIX_FMT_RGB555, QImage::Format_RGB555 },
		{ V4L2_PIX_FMT_XRGB555, QImage::Format_RGB555 },
		{ V4L2_PIX_FMT_RGB444, QImage::Format_RGB444 },
		{ V4L2_PIX_FMT_XRGB444, QImage::Format_RGB444 },
#endif
		{ 0, QImage::Format_Invalid }
	};

	for (int i = 0; supported_fmts[i].v4l2_pixfmt; i++) {
		if (supported_fmts[i].v4l2_pixfmt == format) {
			dstFmt = supported_fmts[i].qt_pixfmt;
			return true;
		}
	}
	return false;
}
