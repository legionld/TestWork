#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct	s_pas
{
	int		in;
	int		out;
}				t_pas;

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

void	insert_in_lst(t_list **lst, t_pas *pas)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *lst;
	while (ptr->next)
	{
		if (pas->in < ((t_pas*)ptr->content)->in)
		{
			tmp = ptr;
			ptr = ft_lstnew(pas, sizeof(t_pas));
			ptr->next = tmp;
		}
		ptr = ptr->next;
	}
	ptr->next = ft_lstnew(pas, sizeof(t_pas));
}

t_list	*get_pas(char *file)
{
	t_pas	*pas;
	t_list	*lst = NULL;
	char	*line;
	char	**tmp;
	char	**time;
	int		fd;

	if (!(pas = (t_pas*)malloc(sizeof(t_pas))))
			err_out(0);
	if ((fd = open(file, O_RDONLY)) == -1)
		err_out(2);
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strsplit(line, ' ');
		time = ft_strsplit(tmp[0], ':');
		pas->in = ft_atoi(time[0]) * 60 + ft_atoi(time[1]);
		free(time[0]);
		free(time[1]);
		time = ft_strsplit(tmp[1], ':');
		pas->out = ft_atoi(time[0]) * 60 + ft_atoi(time[1]);
		free(time[0]);
		free(time[1]);
		free(line);
		if (lst == NULL)
			lst = ft_lstnew((void*)pas, sizeof(t_pas));
		else
			insert_in_lst(&lst, pas);
	}
	return (lst);
}

t_list	*sot_for_out(t_list *in)
{
	t_list	*out;
	t_list	*tmp;
	t_list	*ptr;
	int		f;

	out = ft_lstnew(in->content, in->content_size);
	ptr = out;
	f = 0;
	while (in->next)
	{
		out = ptr;
		in = in->next;
		while (out->next && ((t_pas*)in->content)->out > ((t_pas*)out->next->content)->out)
		{
			out = out->next;
			f = 1;
		}
		if (f == 1 && out->next)
		{
			tmp = out->next;
			out->next = ft_lstnew(in->content, in->content_size);
			out->next->next = tmp;
		}
		else if (f == 1)
			out->next = ft_lstnew(in->content, in->content_size);
		else if (((t_pas*)in->content)->out < ((t_pas*)out->content)->out)
		{
			tmp = ft_lstnew(in->content, in->content_size);
			tmp->next = out;
			ptr = tmp;
		}
		else
			out->next = ft_lstnew(in->content, in->content_size);
		f = 0;
	}
	return (ptr);
}

void	del_list(void *data, size_t size)
{
	free(data);
}

void	print_data(t_list *lst_max)
{
	while (lst_max)
	{
		printf("in %d:%0.2d	out %d:%0.2d\n", ((t_pas*)lst_max->content)->in / 60,
				((t_pas*)lst_max->content)->in % 60, ((t_pas*)lst_max->content)->out / 60,
				((t_pas*)lst_max->content)->out % 60);
		lst_max = lst_max->next;
	}
}

t_list	*search(t_list *lst_in, t_list *lst_out)
{
	t_list	*lst_max;
	t_list	*tmp;
	t_pas	max;
	int		count;
	int		max_p;
	int		f;

	count = 0;
	max_p = 0;
	max.in = 0;
	max.out = 0;
	f = 0;
	while (lst_in)
	{
		if (((t_pas*)lst_in->content)->in < ((t_pas*)lst_out->content)->out)
		{
			++count;
			if (count > max_p)
			{
				max_p = count;
				max.in = ((t_pas*)lst_in->content)->in;
				max.out = 0;
				f = 1;
				if (lst_max == NULL)
					lst_max = ft_lstnew(&max, sizeof(t_pas));
				else
				{
					ft_lstdel(&lst_max, del_list);
					lst_max = ft_lstnew(&max, sizeof(t_pas));
				}
				
			}
			else if (count == max_p)
			{
				max_p = count;
				max.in = ((t_pas*)lst_in->content)->in;
				max.out = 0;
				f = 1;
				tmp = ft_lstnew(&max, sizeof(t_pas));
				ft_lstadd(&lst_max, tmp);
			}
			lst_in = lst_in->next;
		}
		else
		{
			--count;
			if (f == 1)
			{
				tmp = lst_max;
				while (lst_max)
				{
					if (((t_pas*)lst_max->content)->out == 0)
						((t_pas*)lst_max->content)->out = ((t_pas*)lst_out->content)->out;
					lst_max = lst_max->next;
				}
				lst_max = tmp;
				f = 0;
			}
			lst_out = lst_out->next;
		}
	}
	if (f == 1)
		((t_pas*)lst_max->content)->out = ((t_pas*)lst_out->content)->out;
	return (lst_max);
}

int		main(int argc, char **argv)
{
	t_list	*lst_in;
	t_list	*lst_out;
	t_list	*lst_max;
	int		count;
	int		max_p;

	if (argc != 2)
		err_out(1);
	lst_in = get_pas(argv[1]);
	lst_out = sot_for_out(lst_in);
	lst_max = search(lst_in, lst_out);
	print_data(lst_max);
	return (0);
}
