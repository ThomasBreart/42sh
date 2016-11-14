#include <ft_glob.h>

char					**glob__create_tab(t_list *results)
{
	t_list	*tmp;
	char	**ret;
	int		len;

	len = ft_lstcpt(results);
	tmp = results;
	ret = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	len = 0;
	while (results)
	{
		tmp = results->next;
//		printf("<res>%s\n", (char*)results->content);
		ret[len] = results->content;
		free(results);
		len++;
		results = tmp;
	}
	ret[len] = NULL;
	return (ret);
}


int						ft_glob2(char *pattern, t_globinfo gi, t_list **res)
{
	t_list		*ps;
	t_list		*next;
	int			p;

	p = 0;
	ps = ft_lstnew(pattern, ft_strlen(pattern) + 2);
	if (glob_brace(ps) == -1)
		p = -1;
	while (ps)
	{
		next = ps->next;
		if (!p && !ft_strchr(ps->content, '{'))
			glob__open_directory(gi, ps->content, res);
		free(ps->content);
		free(ps);
		ps = next;
	}
	if (p != -1)
		p = ft_lstcpt(*res);
//	printf("<ret>%d\n", p);
	return (p);
}

int						ft_glob(const char *pattern, t_glob *gl)
{
//	printf("%s\n", pattern);
	t_globinfo	g;

	g.local = NULL;
	g.path = NULL;
	g.name = NULL;
	g.flags = gl->flags;
	return (ft_glob2((char*)pattern, g, &gl->results));
}

static int				need_globbing(char *arg)
{
	int		quote;

	quote = 0;
	while (*arg)
	{
		if (*arg == '*' || *arg == '{' || *arg == '[' || *arg == '\\' || *arg == '?')
			return (1);
		else if (*arg == '\'' || *arg == '"')
		{
			quote = *arg;
			arg++;
			while (*arg != quote)
				arg++;
		}
		arg++;
	}
	return (0);
}

void					do_globbing(char ***elem)
{
	char	**argv;
	int		index;
	t_glob	g;
	int		n;

	index = 0;
	g.flags = builtin_glob(NULL);
	g.results = NULL;
	argv = *elem;
	while (argv[index])
	{
		n = need_globbing(argv[index]);
		if (!n || ft_glob(argv[index], &g) < 1)
			ft_lstadd_end(&g.results, ft_lstnew(argv[index], ft_strlen(argv[index]) + 1));
		free(argv[index]);
		index++;
	}
	free(*elem);
	*elem = glob__create_tab(g.results);
}
