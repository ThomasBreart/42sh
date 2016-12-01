/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 09:08:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/24 16:25:09 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char		**shift_options(char ***argv)
{
	char	**cpenv;
	char	**tmp;

	tmp = *argv;
	while (*tmp != NULL && *(tmp)[0] == '-')
	{
		if (ft_strchr(*tmp, 'u') != NULL)
			tmp++;
		tmp++;
	}
	*argv = tmp;
	cpenv = (char**)s_memalloc(sizeof(char*), __FILE__);
	*cpenv = NULL;
	return (cpenv);
}

int			env_check_option_i(char **argv)
{
	int		i;
	int		pass;
	char	*tmp;

	tmp = *argv;
	while (tmp != NULL && tmp[0] == '-')
	{
		if (tmp[1] == '\0')
			return (1);
		pass = 0;
		i = 0;
		while (tmp[i] != '\0')
		{
			if (tmp[i] == 'i')
				return (1);
			if (tmp[i] == 'u')
				pass = 1;
			i++;
		}
		if (pass == 1 && *(argv + 1) != NULL)
			argv++;
		argv++;
		tmp = *argv;
	}
	return (0);
}

static char	check_good_options(char **argv, char *good_opt)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *argv;
	while (tmp != NULL && tmp[0] == '-')
	{
		i = 0;
		while (tmp[++i] != '\0')
		{
			j = -1;
			while (good_opt[++j] != '\0')
				if (good_opt[j] == tmp[i])
					break ;
			if (good_opt[j] == '\0')
				return (tmp[i]);
			if (good_opt[j] == 'u' && *(argv + 1) != NULL)
				argv++;
			else if (good_opt[j] == 'u')
				return ('u');
		}
		argv++;
		tmp = *argv;
	}
	return (1);
}

char		**env_exec_option_u(char ***cpenv, char **argv)
{
	char	**fake_tab;

	while (*argv != NULL && *(argv)[0] == '-')
	{
		if (ft_strchr(*argv, 'u') != NULL)
		{
			argv++;
			fake_tab = fake_argv(*argv, NULL);
			builtin_unsetenv(fake_tab, cpenv);
			free_double_tab(fake_tab);
		}
		argv++;
	}
	return (argv);
}

int			builtin_env_options(char **argv)
{
	char	*good_opt;
	char	err;

	good_opt = s_strnew(2, __FILE__);
	good_opt[0] = 'i';
	good_opt[1] = 'u';
	good_opt[2] = '\0';
	if ((err = check_good_options(argv, good_opt)) != 1)
	{
		free(good_opt);
		if (err == 'u')
		{
			ft_putstr_fd("env: option requires an argument ", STDERR_FILENO);
			ft_putendl_fd("-- u", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("env: illegal option -- ", STDERR_FILENO);
			ft_putchar_fd(err, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		return (-1);
	}
	free(good_opt);
	return (1);
}
