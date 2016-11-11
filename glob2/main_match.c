#include <ft_glob.h>

int		main(int argc, char **argv)
{
	int		ret;
	t_glob	g;

	ret = 0;
	if (argc == 3)
	{
		ret = glob__match(&g, argv[1], argv[2], NULL);
		#ifdef DEBUG
			printf("<%s, %s> %d\n", argv[1], argv[2], ret);
		#endif
	}
	else
		printf("Bad args\n");
	return (ret);
}
