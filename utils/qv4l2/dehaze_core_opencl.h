#ifndef DEHAZE_CORE_H
#define DEHAZE_CORE_H

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

static char kernel_file[20] = "kernel.cl";

typedef cl_platform_id		Platform;
typedef cl_device_id		Device;
typedef cl_command_queue	CommandQueue;
typedef cl_program			Program;
typedef cl_kernel			Kernel;
typedef cl_mem				Mem;

typedef struct _Context
{
	cl_context	context;
	Platform	platform;
	Device		device;
}Context;


//#define TRUE	1
//#define FALSE	0
#define CheckErr(err, str) (_checkErr((err), (str), __FILE__, __LINE__))
void	_checkErr(cl_int err, const char *str, const char *file, const unsigned long line);

typedef enum _DEVICE_TYPE
{
	CPU = CL_DEVICE_TYPE_CPU,
	GPU = CL_DEVICE_TYPE_GPU,
	ALL = CL_DEVICE_TYPE_ALL,
}DEVICE_TYPE;
void CL_CALLBACK contextCallback(const char *errinfo, const void *private_info, size_t cb, void *user_data);

Context CreateContext(DEVICE_TYPE device_type);

CommandQueue CreateCommandQueue(Context context);
Program CreateProgram(const char *file, Context *context);

cl_int CreateKernel(Kernel *kernel, Program *program, const char *kernel_name);
cl_int CreateKernelInProgram(Program *program, Kernel **kernels);

cl_int ExecuteKernel(CommandQueue *commandqueue, Kernel *kernel, size_t *global_work_size, size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);

void CleanUp(Context context, CommandQueue commandqueue, Program program, 	Kernel kernel);

void printMat(char *imgname, Mat m);
void printMatInfo(Mat *m);
Mat read_image(char *imagename);

double getAve(unsigned char *M, int height, int width);
int MaxMatrix(unsigned char *src, int height, int width);
double GetA(unsigned char *M_max, unsigned char *M_ave, int height, int width);

#endif
