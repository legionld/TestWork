#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void	err_out(int e)
{
	if (e == 0)
		printf("Error #%d! Don't have memmory\n", e);
	if (e == 1)
		printf("Error #%d! Usage n_1 with one parametr as name file\n", e);
	if (e == 2)
		printf("Error #%d! Don't open file\n", e);
	exit(0);
}

double	get_sq(double x0, double y0, double x1, double y1, double x2, double y2)
{
	double ab;
	double bc;
	double ca;
	double p;
	double s;

	ab = sqrt(fabs(y0 - y1) * fabs(y0 - y1) + fabs(x0 - x1) * fabs(x0 - x1));
	bc = sqrt(fabs(y1 - y2) * fabs(y1 - y2) + fabs(x1 - x2) * fabs(x1 - x2));
	ca = sqrt(fabs(y2 - y0) * fabs(y2 - y0) + fabs(x2 - x0) * fabs(x2 - x0));
	p = (ab + bc + ca) / 2;
	return (sqrtf(p * (p - ab) * (p - bc) * (p - ca)));
}

double   get_sq_base(int *arrX, int *arrY)
{
	double	sq;

	sq = 0;
	sq += get_sq((double)(arrX[0]), (double)(arrY[0]), (double)(arrX[1]), (double)(arrY[1]), (double)(arrX[2]), (double)(arrY[2]));
	sq += get_sq((double)(arrX[0]), (double)(arrY[0]), (double)(arrX[2]), (double)(arrY[2]), (double)(arrX[3]), (double)(arrY[3]));
	return (sq);
}

int		get_info(double sq_base, int *arrX, int *arrY, int x, int y)
{
	double 	s1;
	double	tmp;
	int		i;

	s1 = 0;
	i = -1;
	while (++i < 3)
	{
		if ((x == arrX[i] && y == arrY[i]) || (x == arrX[i + 1] && y == arrY[i + 1]))
			return (3);
		if ((tmp = get_sq((double)(arrX[i]), (double)(arrY[i]), (double)(arrX[i + 1]), (double)(arrY[i + 1]), (double)x, (double)y)) == 0)
			return (0);
		s1 += tmp;
	}
	if (s1 > sq_base)
		return (1);
	return (2);
}
 
int main(int argc, char **argv)
{
	FILE* in;
 
	int arrX[4];
	int arrY[4];
	int x;
	int y;
	int i;
	double   sq_base;

	if (argc != 2)
		err_out(2);
	if ((in = fopen(argv[1], "r")) == NULL)
		err_out(2);
	fscanf(in, "<%d> <%d>\n<%d> <%d>\n<%d> <%d>\n<%d> <%d>\n",
			&arrX[0], &arrY[0], &arrX[1], &arrY[1], &arrX[2], &arrY[2], &arrX[3], &arrY[3]);
	fclose(in);
	scanf("%d %d", &x, &y);
	sq_base = get_sq_base(arrX, arrY);
	i = get_info(sq_base, arrX, arrY, x, y);
	if (i == 0)
		printf("точка лежит на сторонах четырехугольника\n");
	if (i == 1)
		printf("точка снаружи четырехугольника\n");
	if (i == 2)
		printf("точка внутри четырехугольника\n");
	if (i == 3)
		printf("точка - вершина четырехугольника\n");
	exit(0);
}