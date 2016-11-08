/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 22:24:18 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/07 16:23:36 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

typedef struct		s_list
{
	char			*content;
	char			*fullcontent;
	char			**argv;
	int				type;
	int				aggr_fd;
	struct s_list	*parent;
	struct s_list	*prev;
	struct s_list	*next;
	struct s_list	*left;
	struct s_list	*right;
}					t_list;

typedef struct		s_save_fd
{
	int				save_stdin;
	int				save_stdout;
	int				save_stderr;
	int				fd_parent;
	int				fd_parent_sub;
	int				fd_file[100];
	int				index_file;
}					t_save_fd;

typedef struct		s_hash
{
	char			*name_bin;
	char			*fullpath_bin;
	struct s_hash	*next;
}					t_hash;

typedef struct		s_historic
{
	t_list			*head;
	t_list			*cur;
	t_list			*end;
	int				hist;
	char			**entry;
	int				in_getcmd;
	struct winsize	ws;
	char			*name_term;
	struct termios	term;
	struct termios	save;
	int				cur_x;
	long int		buff;
	char			*cmd_inprogress;
	char			*buff_paste;
	char			*bslash_split;
	size_t			len_prompt;
	char			*prompt;
	char			*prompt_open;
	int				in_llr;
	int				llr_eof;
	char			*prompt_in_llr;
	int				in_child;
	int				fd_tty;
	int				istty;
	char			**env;
	char			*prompt_current;
	t_hash			*hashtable[100];
	char			*path_historic_file;
	int				tab_aggrfd[100];
	int				index_tab_aggrfd;
	int				start_select;
	int				select_mode;
	int				end_select;
	int				stdout_modified;
}					t_historic;

typedef struct		s_vars_redirs
{
	int				ret;
	int				fd_file;
	t_list			*current;
}					t_vars_redirs;

typedef struct		s_proc
{
	int				tab_pid[100];
	int				index;
}					t_proc;

#endif
