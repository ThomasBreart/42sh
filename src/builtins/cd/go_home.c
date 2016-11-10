#include "ft_21sh.h"

int			go_home(char ***env)
{
	char	*var;

	var = ft_getenv("HOME", *env);
	if (!var)
	{
		ft_putendl_fd("cd: No home directory.", STDERR_FILENO);
		return (-1);
	}
	if (0 != chdir(var))
	{
		print_error_cd(var);
		ft_strdel(&var);
		return (-1);
	}
	update_oldpwd(env);
	update_pwd(env);
	ft_strdel(&var);
	return (1);
}