#include <ft_glob.h>
#include <glob.h>

int		process__glob_sys(char *s2)
{
	glob_t	g;
	int		i;

	i = 0;
	glob(s2, 0, 0, &g);
	#ifdef DEBUG
	char	**r;
	if ((r = g.gl_pathv))
	while (r[i])
	{
		printf("%d, %s\n", i, r[i]);
		i++;
	}
	#endif
	i = g.gl_pathc;
	globfree(&g);
	return (i);
}

int		process__glob_ft(char *s1)
{
	char	*s;
	t_list	*lst;

	lst = NULL;
	s = ft_strdup("\0");
	int r = ft_glob(&s, s1, GLOB_CASE_SENSITIVE, &lst);
	#ifdef DEBUG
	printf("FIN:%s\n", s);
	#endif
	return (r);
}

int		process(char *s1)
{
	int	ret_sys;
	int	ret_ft;

	ret_ft = process__glob_ft(s1);
	#ifdef DEBUG
		printf("ft: %d", ret_ft);
	#endif

	ret_sys = process__glob_sys(s1);
	#ifdef DEBUG
		printf("|sys: %d\n", ret_sys);
	#endif

	return (ret_ft == ret_sys);
}

int		main(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc == 2)
	{
		ret = process(argv[1]);
		#ifdef DEBUG
			printf("<%s> %d\n", argv[1], ret);
		#endif
	}
	else
		printf("Bad args\n");
	return (ret);
}