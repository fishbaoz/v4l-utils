#include "Fast_dehaze_cpu.h"
#include "dehaze_core_opencl.h"

void  _checkErr(int err, const char *str, const char *file, const unsigned long line)
{
	if (!err) {
		fprintf(stderr, "%s error [file:%s line:%lu]", str, file,line);
		exit(-1);
	}
	else
		return ;
}
static void GetPlatform(Platform *platforms)
{
	cl_int errcode;
	cl_uint numPlatforms = 0;

	errcode = clGetPlatformIDs(1, platforms, &numPlatforms);
	CheckErr(errcode == CL_SUCCESS && numPlatforms > 0, "Ecl_GetPlatform");
	return ;
}

static void GetDevice(Platform *platform, DEVICE_TYPE device_type, Device *device)
{
	cl_int errcode;
	cl_uint numDevices = 0;

	errcode = clGetDeviceIDs(*platform, device_type, 1, device, &numDevices);
	CheckErr(errcode==CL_SUCCESS && numDevices > 0, "Ecl_GetDevice");

	return ;
}
void CL_CALLBACK contextCallback(const char *errinfo, const void *private_info, size_t cb, void *user_data)
{
	printf("Error occured during context use: %s\n", errinfo);
	exit(EXIT_FAILURE);
}
Context CreateContext(DEVICE_TYPE device_type)
{
	cl_int errcode;
	Platform platform = NULL;
	Device device = NULL;
	cl_context context = NULL;
	Context return_con;
	return_con.context = NULL; /* ?????????????? */

	GetPlatform(&platform);
	GetDevice(&platform, device_type, &device);

	cl_context_properties contextProperties[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0};
	context = clCreateContext(contextProperties, 1 , &device, NULL,	NULL, &errcode);
	CheckErr(errcode==CL_SUCCESS, "Ecl_CreateContext");

	return_con.context = context;
	return_con.platform = platform;
	return_con.device = device;
	return return_con;
}

CommandQueue CreateCommandQueue(Context context)
{
	cl_int errcode;
	CommandQueue commandqueue = NULL;

	commandqueue = clCreateCommandQueueWithProperties(context.context, context.device, 0, &errcode);
	CheckErr((errcode == CL_SUCCESS && (commandqueue != NULL)), "Ecl_CreatCommandQueue");

	return commandqueue;
}

size_t LoadFile(const char *file, char **program_buffer)
{
	FILE *program_handle = NULL;
	size_t program_size;
	program_handle = fopen(file, "rb");
	CheckErr(program_handle != NULL, "Couldn't open file");

	fseek(program_handle, 0, SEEK_END);
	program_size = ftell(program_handle);
	rewind(program_handle);
	*program_buffer = (char *)malloc(program_size + 1);
	CheckErr(program_buffer != NULL, "malloc memory failed");

	(*program_buffer)[program_size] = '\0';
	if (fread(*program_buffer, sizeof(char), program_size, program_handle) != program_size)
	{
		perror("fread error: ");
		return 0;
	}
	fclose(program_handle);
	return program_size;
}

cl_int BuildProgram(Program *program, Device *device)
{
	cl_int errcode;
	size_t log_size = 0;
	errcode = clBuildProgram(*program, 0, NULL, NULL, NULL, NULL);
	if (errcode != CL_SUCCESS)
	{
		char *buildLog;

		clGetProgramBuildInfo(*program, *device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		if (log_size <= 0)
		{
			printf("log_size invalid\n");
			exit(EXIT_FAILURE);
		}
		buildLog = (char *)malloc(log_size+1);
		assert(buildLog);
		buildLog[log_size] = '\0';

		clGetProgramBuildInfo(*program, *device, CL_PROGRAM_BUILD_LOG, log_size+1, buildLog, NULL);
		printf("Error in kernel: %s\n", buildLog);
		free(buildLog);
		return FALSE;
	}
	return TRUE;
}


Program CreateProgram(const char *file, Context *context)
{
	cl_int errcode;
	cl_program program = NULL;
	size_t program_size;
	char *kernel_buffer;
	//cout << "kernel file " << file << endl;
	if ((program_size = LoadFile(file, &kernel_buffer)) <= 0)
	{
		free(kernel_buffer);
		return NULL;
	}
	program = clCreateProgramWithSource(context->context, 1, (const char **)&kernel_buffer, &program_size, &errcode);
	CheckErr(errcode == CL_SUCCESS, "Ecl_CreateProgram");
	free(kernel_buffer);
	if (BuildProgram(&program, &(context->device)))
		return program;
	else
		return NULL;
}

cl_int CreateKernel(Kernel *kernel, Program *program, const char *kernel_name)
{
	*kernel = clCreateKernel(*program, kernel_name, NULL);
	CheckErr(*kernel != NULL, "Ecl_CreateKernel");

	return TRUE;
}
Mat read_image(char *imgname)
{
	Mat img = imread(imgname, CV_LOAD_IMAGE_COLOR);
	Mat outimg(img.rows,img.cols,CV_8UC3);
	img.convertTo(outimg, CV_8UC3);
	return outimg;
}

double getAve(unsigned char *M, int height, int width)
{
	double sum = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += M[i*width + j];
		}
	}
	return sum/(height*width*255);
}
int MaxMatrix(unsigned char *src, int height, int width)
{
	int temp = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			temp = my_max(src[i*width + j], temp);

		}
		if (temp == 255)
			return temp;
	}
	return temp;
}

double GetA(unsigned char *M_max, unsigned char *M_ave, int height, int width)
{
	return (MaxMatrix(M_max, height, width) + MaxMatrix(M_ave, height, width)) * 0.5;
}
