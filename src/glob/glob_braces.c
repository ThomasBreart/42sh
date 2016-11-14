#include "ft_glob.h"

static char		*get_begin(char *pattern)
{
	int			i;
	char		*begin;

	i = 0;
	while (*(pattern + i) != '{' && *(pattern + i))
		i++;
	begin = ft_strnew(i + 2);
	ft_strncpy(begin, pattern, i);
	return (begin);
}

static void		replace_begin(char *begin, t_list *tmp)
{
	char	*tmp2;

	while (tmp)
	{
		tmp2 = tmp->content;
		tmp->content = ft_strjoin(begin, tmp2);
		free(tmp2);
		tmp = tmp->next;
	}
}

int				glob_brace(t_list *first)
{
	char		*begin;
	char		*tmp2;
	int			n;
	t_list		*tmp;

	while (first)
	{
		n = 0;
		tmp2 = first->content;
		begin = get_begin(tmp2);
		while (*tmp2 && *tmp2 != '{')
			tmp2++;
		tmp = NULL;
		if (*tmp2 == '{' &&
			(n = get_patterns(&tmp, tmp2 + 1)) > 0)
		{
			ft_lstadd_end(&first, tmp);
			replace_begin(begin, tmp);
		}
		first = first->next;
		free(begin);
		if (n == -1)
			return (-1);
	}
	return (0);
}
