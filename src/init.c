/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 20:00:21 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 02:12:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	set_termcaps(t_historic *termcaps, char **env)
{
	if ((termcaps->name_term = ft_getenv("TERM", env)) == NULL)
		termcaps->name_term = s_strdup("xterm-256color", __FILE__);
	if (tgetent(NULL, termcaps->name_term) <= 0)
		return (-1);
	if (tcgetattr(termcaps->fd_tty, &termcaps->term) == -1)
		return (-1);
	if (tcgetattr(termcaps->fd_tty, &termcaps->save) == -1)
		return (-1);
	termcaps->term.c_lflag &= ~(ICANON);
	termcaps->term.c_lflag &= ~(ECHO);
	termcaps->term.c_cc[VMIN] = 1;
	termcaps->term.c_cc[VTIME] = 0;
	if (tcsetattr(termcaps->fd_tty, TCSADRAIN, &termcaps->term) == -1)
		return (-1);
	tputs(tgoto(tgetstr("sc", NULL), 0, 0), 1, ft_outc);
	tputs(tgoto(tgetstr("rc", NULL), 0, 0), 1, ft_outc);
	return (0);
}

static void	set_vars(t_historic *termcaps)
{
	int		i;

	termcaps->child_end_sig = 0;
	termcaps->stdout_modified = 0;
	termcaps->end_select = -1;
	termcaps->start_select = -1;
	termcaps->select_mode = 0;
	termcaps->cur_x = 0;
	termcaps->in_llr = 0;
	termcaps->llr_eof = 0;
	termcaps->in_child = 0;
	termcaps->in_builtin = 0;
	termcaps->cmd_inprogress = NULL;
	termcaps->buff_paste = NULL;
	termcaps->head = NULL;
	termcaps->cur = NULL;
	termcaps->end = NULL;
	termcaps->entry = NULL;
	i = 0;
	while (i < 100)
	{
		termcaps->hashtable[i] = NULL;
		i++;
	}
}

static void	set_prompt(t_historic *termcaps)
{
	termcaps->prompt = s_strdup("42sh> ", __FILE__);
	termcaps->len_prompt = ft_strlen(termcaps->prompt);
	termcaps->prompt_open = s_strdup("> ", __FILE__);
	termcaps->prompt_in_llr = s_strdup("heredoc> ", __FILE__);
	termcaps->prompt_current = termcaps->prompt;
}

static void	init_historic(t_historic *termcaps, char **my_env)
{
	char	**taab;

	set_path_historic_file(termcaps, my_env);
	if (termcaps->istty == 1)
	{
		if (termcaps->path_historic_file != NULL)
			if ((taab = recover_historic_file(termcaps, -1)) != NULL)
				create_historic_list(termcaps, taab);
		ft_putstr(termcaps->prompt);
	}
}

void		init(t_historic **termcaps, char ***env, char **e)
{
	char	***my_env;

	*termcaps = get_termcaps();
	my_env = get_env();
	(*termcaps)->in_getcmd = 0;
	if (((*termcaps)->fd_tty = open("/dev/tty", O_RDWR)) == -1)
		errors(ERR_SETTERM);
	(*termcaps)->istty = isatty(STDIN_FILENO);
	if ((*termcaps)->istty == 1 && set_termcaps(*termcaps, *env) == -1)
		errors(ERR_SETTERM);
	*my_env = create_env(*env);
	close((*termcaps)->fd_tty);
	(*termcaps)->fd_tty = -1;
	set_vars(*termcaps);
	set_prompt(*termcaps);
	handler_sigwinch(42);
	signals_management();
	*e = NULL;
	init_historic(*termcaps, *my_env);
	init_proc();
	(*termcaps)->index_tab_aggrfd = 0;
}
