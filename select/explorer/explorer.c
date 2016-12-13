/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explorer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:00:08 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:00:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void		explorer_signal(int signum)
{
	(void)signum;
}

char		**init_env(char **env)
{
	int		index;
	char	**copy;

	index = 0;
	while (env[index])
		index++;
	copy = (char**)malloc(sizeof(char*) * (index + 1));
	index = 0;
	while (env[index])
	{
		copy[index] = ft_strdup(env[index]);
		index++;
	}
	copy[index] = NULL;
	return (copy);
}

void		no_name(int fd, t_args *arg, t_term *t, t_file *f)
{
	if (arg->new_page != arg->page)
	{
		arg->new_page = arg->page;
		write(fd, "\033c", 2);
		write(fd, "\033[s", 3);
		parcours(fd, &t->ws, arg, f);
	}
	write(fd, "\033[u", 3);
	print_at(fd, arg->y + 1);
}

void		start(t_term *t)
{
	tcgetattr(0, &t->term_back);
	tcgetattr(0, &t->term);
	set_rawmode(&t->term);
	tputs(tgetstr("cl", NULL), 1, term_putchar);
	tputs(tgetstr("ti", NULL), 1, term_putchar);
	tputs(tgetstr("vi", NULL), 1, term_putchar);
	tcsetattr(0, 0, &t->term);
}

int			start_explorer(t_term *t, char **args)
{
	t_args	tmp;

	(void)args;
	signal(SIGWINCH, &explorer_signal);
	ioctl(get_fd(), TIOCGWINSZ, &t->ws);
	getcwd(t->dirpath, sizeof(char) * 1024);
	tmp.path = args[2] ? args[2] : t->dirpath;
	tmp.mask = LIST | MTIME | COLOR | ALL;
	tmp.path = t->dirpath;
	tmp.colormap = NULL;
	tmp.typemap = NULL;
	tmp.ret = 0;
	start(t);
	if (!tmp.colormap)
		found_clicolor(&tmp, t->env);
	if (tmp.mask & COLOR)
		tmp.typemap = init_typemap(t->env);
	ls(t, &tmp);
	tputs(tgetstr("te", NULL), 1, term_putchar);
	tputs(tgetstr("ve", NULL), 1, term_putchar);
	tcsetattr(0, 0, &t->term_back);
	return (0);
}
