#include <ft_glob.h>

int		builtin_glob(char **argv)
{
	static int	flag = 0;

	if (!argv)
		return (flag);
	while (*argv)
	{
		if (**argv == '-')
		{
			(*argv)++;
			while (**argv)
			{
				if (**argv == 'c')
					flag |= GLOB_CASE;
				else if (**argv == 'h')
					flag |= GLOB_HIDE;
				else if (**argv == 'r')
					flag = 0;
				else
					return (0);
				(*argv)++;
			}
		}
		argv++;
	}
	return (flag);
}
