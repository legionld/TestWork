#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct	s_data
{
	int		percentile;
	int		median;
	float	avarange;
	int		max;
	int		min;
}				t_data;

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

int		get_max(int	*nums, int len)
{
	int	i;
	int	max;

	i = 0;
	max = nums[i];
	while (++i < len)
		if (nums[i] > max)
			max = nums[i];
	return (max);
}

int		get_min(int	*nums, int len)
{
	int	i;
	int	min;

	i = 0;
	min = nums[i];
	while (++i < len)
		if (nums[i] < min)
			min = nums[i];
	return (min);
}

float	get_avarange(int *nums, int len)
{
	int	i;
	int	sum;

	i = -1;
	sum = 0;
	while(++i < len)
		sum += nums[i];
	return (sum / len);
}

int		get_median(int *nums, int len, int con)
{
	int		left[len];
	int		right[len];
	int		l_len;
	int		r_len;
	int		pivot;
	int		i;

	if (len == 1 || len == 2)
		return (nums[0]);
	i = -1;
	l_len = 0;
	r_len = 0;
	pivot = nums[len / 2];
	while (++i < len)
	{
		if (nums[i] <= pivot)
		{
			left[l_len] = nums[i];
			++l_len;
		}
		else
		{
			right[r_len] = nums[i];
			++r_len;
		}
	}
	if (con - l_len > l_len)
		return (get_median(right, r_len, con));
	return (get_median(left, l_len, con));
}

int		get_percentile(int *nums, int len)
{
	int pr;
	int	l_p;
	int	r_p;
	int	p;
	int	i;

	if (len <= 2)
		return (nums[0]);
	pr = (float)get_max(nums, len) / 100 * 90;
	l_p = nums[0];
	p = nums[1];
	r_p = nums[2];
	i = 0;
	while (++i < len)
	{
		if (nums[i] < pr && nums[i] > l_p)
			l_p = nums[i];
		else if (nums[i] > pr && nums[i] < r_p)
			r_p = nums[i];
		else if (nums[i] != pr && nums[i] > l_p && nums[i] < r_p)
			p = nums[i];
		else if (nums[i] == pr)
			return (nums[i]);
	}
	return (p);
}

void	set_data(t_data *data, int *nums, int len)
{
	data->max = get_max(nums, len);
	data->min = get_min(nums, len);
	data->avarange = get_avarange(nums, len);
	data->median = get_median(nums, len, len);
	data->percentile = get_percentile(nums, len);
}

int		set_nums(char *file, int **nums)
{
	int fd;
	int	i;
	int len;
	char *line;
	char *str;
	char *tmp;
	char **str_nums;

	if ((fd = open(file, O_RDONLY)) == -1)
		err_out(2);
	len = 0;
	str = ft_strdup("");
	while (get_next_line(fd, &line) > 0)
	{
		tmp = str;
		str = ft_strjoin(str, line);
		free(tmp);
		free(line);
	}
	str_nums = ft_strsplit(str, ' ');
	free(str);
	i = 0;
	while (str_nums[i])
		++i;	
	if (!(*nums = (int *)malloc(sizeof(int) * i)))
		err_out(0);
	i = -1;
	while (str_nums[++i])
	{
		(*nums)[len] = ft_atoi(str_nums[i]);
		++len;
		free(str_nums[i]);
	}
	free(str_nums);
	close(fd);
	return (len);
}

void	out_data(t_data *data)
{
	printf("90 percentile <%d>\n", data->percentile);
	printf("median <%d>\n", data->median);
	printf("average <%f>\n", data->avarange);
	printf("max <%d>\n", data->max);
	printf("min <%d>\n", data->min);
}

int		main(int argc, char **argv)
{
	int		*nums;
	int		len;
	t_data	*data;

	if (argc != 2)
		err_out(1);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		err_out(0);
	len = set_nums(argv[1], &nums);
	set_data(data, nums, len);
	out_data(data);
	free(nums);
	free(data);
	exit(0);
}