/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 16:15:00 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/07 16:50:15 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_size(char **argv)
{
	int		i;
	int		len;

	len = 0;
	i = 1;
	while (argv[i])
	{
		len += ft_strlen(argv[i]);
		i++;
	}
	len += --i;
	return (len);
}

static char	*reverse_split(char **argv, int i)
{
	char	*ret;
	int		len;

	len = get_size(argv);
	ret = (char*)ft_memalloc(sizeof(char) * (len + 1));
	while (argv[i])
	{
		ft_strcat(ret, argv[i]);
		if (argv[i + 1])
			ft_strcat(ret, " ");
		i++;
	}
	return (ret);
}

static void	put_cooked_mode(t_save_fd *save)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	set_termios(&termcaps->term, save);
}

static void	put_raw_mode(t_save_fd *save)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	set_termios(&termcaps->save, save);
}

char		*return_one_line(int flag)
{
	char	*str;

	get_next_line(STDIN_FILENO, &str);
	if (!flag)
		remove_onelvl_escape_backslash(&str);
	return (str);
}

static void	put_on_reply(char ***env, int flag)
{
	char	**ret;
	char	*str;

	str = return_one_line(flag);
	ret = fake_argv("REPLY", str);
	builtin_setenv(ret, env);
	ft_memdel((void**)&str);
	free_double_tab(ret);
}

int			builtin_read(char **ar, t_save_fd *save, char ***env)
{
	char	*begin;
	char	*argv;
	int		flag;
	int		ret;

	ret = 0;
	flag = 0;
	argv = reverse_split(ar, 1);
	begin = argv;
	put_raw_mode(save);
	ret = parse_flag(&argv, &flag);
	if (!ret && *argv == '\0')
		put_on_reply(env, flag);
	else if (!ret)
		make_copies(argv, env, flag);
	put_cooked_mode(save);
	ft_memdel((void**)&begin);
	return (ret);
}
