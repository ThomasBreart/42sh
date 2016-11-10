#include "ft_21sh.h"

int			go_oldpwd(char ***env)
{
	char	*var;

	var = ft_getenv("OLDPWD", *env);
	if (!var)
	{
		ft_putendl_fd("OLDPWD not set", STDERR_FILENO);
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
	ft_putendl(ft_strchr(*ft_getenvadress("PWD", *env), '=') + 1);
	ft_strdel(&var);
	return (1);
}
