#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

#define R 31
#define EPS 1.8
#define GROUP_SIZE 256

__kernel void getM(__global uchar *M, __global uchar *M_max, __global uchar *src)
{
	int x = (int)get_global_id(0);
	int y = (int)get_global_id(1);
	int width = get_global_size(0);

	int i = y * width + x;
	unsigned char temp1, temp2, r, g, b;
	r = src[3*i];
	g = src[3*i+1];
	b = src[3*i+2];
	temp1 = min(min(r, g), b);
	temp2 = max(max(r, g), b);
	M[i] = temp1;
	M_max[i] = temp2;

	return ;
}
__kernel void box_filter_horizontal(__global uchar* inputImage, __global uchar* outputImage, __local uchar *lds)
{
	int x = get_global_id(0);
    int y = get_global_id(1);

	int width = get_global_size(0);

	int pos = x + y * width;
	int k = (R - 1)/2;

	int lid = get_local_id(0);
	int gidX = get_group_id(0);
	int gidY = get_group_id(1);

	int gSizeX = get_local_size(0);
	int gSizeY = get_local_size(1);

	int firstElement = gSizeX * gidX + width * gidY * gSizeY;
	if(lid < k)
	{
		lds[lid] = inputImage[firstElement - k + lid];
		lds[GROUP_SIZE + k + lid] = inputImage[firstElement + lid + GROUP_SIZE];
	}

	/* Load GROUP_SIZE  values into shared memory */
	lds[lid + k] = inputImage[firstElement + lid];

	barrier(CLK_LOCAL_MEM_FENCE);

	if(x < k || x >= (width - k))
	{
		outputImage[pos] = inputImage[pos];
		return;
	}

	int sum = 0;
	for(int X = -k; X <= k; X++)
	{
		sum += lds[lid+X+k];
	}
	outputImage[pos] = (sum / R);
}


__kernel void box_filter_vertical(__global uchar* inputImage, __global uchar* outputImage)
{
	int x = get_global_id(0);
    int y = get_global_id(1);

	int width = get_global_size(0);
	int height = get_global_size(1);

	int pos = x + y * width;
	int k = (R - 1)/2;

	/* Discard pixels in apron */
	if(y < k || y >= (height - k))
	{
		outputImage[pos] = inputImage[pos];
		return;
	}

	int sum = 0;
	/* Read values from (filterWidth x filterWidth) sized kernel */
	for(int Y = -k; Y < k; Y=Y+2)
	{
		sum += inputImage[pos + Y * width];
		sum += inputImage[pos + (Y + 1) * width];
	}
	sum += inputImage[pos + k * width];
	outputImage[pos] = sum / R;
}

__kernel void getL(__global uchar *L, __global uchar *M, __global uchar *M_ave, double m_av)
{

	int x = get_global_id(0);
    int y = get_global_id(1);

	int width = get_global_size(0);
	int height = get_global_size(1);

	int i = x + y * width;
	double delta = min(0.9, EPS*m_av);
	L[i] = min(delta*M_ave[i], M[i]);

	return ;
}

__kernel void dehaze(__global uchar *dst, __global uchar *src, __global uchar *L, double A)
{
	int x = get_global_id(0);
	int y = get_global_id(1);

	int width = get_global_size(0);
	int height = get_global_size(1);

	int i = x + y * width;
	int temp = L[i];
	int value = 0;
	for (int k = 0; k < 3; k++)
	{
		value = A*(src[3*i+k]-temp)/(A-temp);
		if (value > 255)
			value = 255;
		else if (value < 0)
			value = 0;
		dst[3*i+k] = value;
	}
	return ;
}
