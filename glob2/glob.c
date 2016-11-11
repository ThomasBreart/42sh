#include <ft_glob.h>

char					*glob__create_string(t_list *results)
{
	t_list	*tmp;
	int		len;
	char	*ret;

	ret = NULL;
	len = 0;
	tmp = results;
	while (tmp)
	{
		len += tmp->content_size;
		tmp = tmp->next;
	}
	if (len)
		ret = ft_strnew(len);
	len = 0;
	while (results)
	{
		tmp = results->next;
		ft_strcpy(ret + len, (char*)results->content);
		len += results->content_size;
		if (tmp)
			*(ret + len - 1) = ' ';
		free(results->content);
		free(results);
		results = tmp;
	}
	return (ret);
}


int						ft_glob2(char *pattern, t_globinfo gi, t_list **res)
{
	t_list		*ps = ft_lstnew(pattern, ft_strlen(pattern) + 2);
	t_list		*next;
	int			p = 0;

	if (glob_brace(ps) == -1)
	{
		p = -1;
		write(2, "Bad pattern\n", 12);
	}
	while (ps)
	{
		next = ps->next;
		if (!p && !ft_strchr(ps->content, '{'))
		{
			printf("= %s =\n", (char*)ps->content);
			glob__open_directory(gi, ps->content, res);
		}
		free(ps->content);
		free(ps);
		ps = next;
	}
	return !p;
}

int						ft_glob(const char *pattern, t_glob *gl)
{
	t_globinfo			g;

	g.local = NULL;
	g.path = NULL;
	g.name = NULL;
	gl->results = NULL;
	g.flags = gl->flags;
	return (ft_glob2((char*)pattern, g, &gl->results));
}