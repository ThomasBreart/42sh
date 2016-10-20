/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 22:31:35 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/20 17:39:29 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "../lib/libft/includes/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <pwd.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <fcntl.h>

#include <stdio.h>


# define SUBCMD_BACKQUOTE	1
# define SUBCMD_DOLLAR		2

# define ERR_ARGV		0
# define ERR_SETTERM	1

/*
**	WORD = [a-zA-Z-_1-9...\]+
**	OPE_AND = &&
**	OPE_OR = ||
**	OPE_PIPE = |
**	PTH_BEG = (
**	PTH_END = )
*/

# define LEX_WORD 1
# define LEX_AND 2
# define LEX_OR 3
# define LEX_PIPE 4
# define LEX_L_R 5
# define LEX_LL_R 6
# define LEX_R_R 7
# define LEX_RR_R 8
# define LEX_COMA 9
# define LEX_SPACES 10
# define LEX_SUBSH 11

# define E_NOT_FOUND 10
# define E_NO_PREVSUB 11

# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "bonus.h"
# include "builtins.h"
# include "termcaps.h"
# include "redirs.h"

char	*goto_next_char(char *str, char c);
char		*add_str_in_str(char *dest, char *src, int position);
int		check_event_designators(char **entryr);
int		cmd_is_open(char *str);
int		open_chars_error(t_historic *tcaps, char error);
char	*find_full_cmd(char *s, t_historic *termcaps);
char	*goto_next_quote(char *str);
char	*goto_next_backquote(char *str);
char	*goto_next_parenthesis(char *str);
char	*goto_next_word(char *str, char c);
char	**realloc_tab(char **oldtab, int *maxlen, const char *filename);
void	remove_quoting_chars(t_list *elem);
void	update_elem(t_list *elem, int change_argv);
int		exec_subshell(t_list *elem);

/*
**	check_backquotes.c
*/
void	check_backquotes(t_list **first);

/*
**	clean.c
*/
void				free_tree(t_list *root);

/*
**	cmd_analysis.c
*/
t_list				*cmd_analysis(/*t_list **root, */char **entry);

/*
**	cmd_simple.c
*/
int					exec_simple(t_list *elem, char ***env, t_save_fd *save);
int					cmd_simple_prog(t_list *elem, char **env, t_save_fd *save);

/*
**	create_env.c
*/
char				**create_env(char **environ);

/*
**	del_elem_list.c
*/
int					del_elem_list(t_list *first);

/*
**	del_tlist.c
*/
void	del_tlist(t_list *elem);

int					del_elem_list(t_list *first);
/*
**	errors.c
*/
void				errors(int a);
int					error_name(char *fullpath, char *content);
int					internal_error(char *s, char *error, int dead);
int					error_fd_aggr(int fd_aggr);

/*
**	event_negatif_number.c
*/
int					is_event_negatif_number(char *str);
int					event_negatif_number(char *sub_cmd, char **new_str);

/*
**	event_positif_number.c
*/
int					is_event_positif_number(char *str);
int					event_positif_number(char *sub_cmd, char **new_str);

/*
**	event_previous_command.c
*/
int					is_event_previous_command(char *str);
int					event_previous_command(char **new_str);

/*
**	event_sharp.c
*/
int					is_event_sharp(char *str);
int					event_sharp(char *sub_cmd, char *entry, int start_subcmd,
																char **new_str);

/*
**	event_string.c
*/
int					event_string(char *sub_cmd, char **new_str);

/*
**	event_string_anywhere.c
*/
int					is_event_string_anywhere(char *str);
int					event_string_anywhere(char *sub_cmd, char **new_str);

/*
**	event_string_substitution.c
*/
int					is_event_string_substitution(char *str);
int					event_string_substitution(char *sub_cmd, char **new_str);

/*
**	exec_cmd.c
*/
int					exec_cmd(t_list *first, char ***env);

/*
**	exec_cmd_tools.c
*/
int					check_return_redirs(t_vars_redirs *vars);
void				redirs_init(t_vars_redirs *vars, t_list *elem,
																t_list **prog);
int					save_fd(t_save_fd *save);
int					close_fd(t_save_fd *save);
int					restore_fd(t_save_fd *save);

/*
**	fake_argv.c
*/
char				**fake_argv(char *s, char *s2);

/*
**	find_fullpath_bin.c
*/
char				*create_filename(char *cmd, char *filename);
char				*check_cmd_exist(char *cmd, char **tab_path);
char				**check_dir_path(char **env);
char				*create_fullpath(char *s, char **env);
void				find_fullpath_bin(t_list *elem, char **env);

/*
**	ft_atoi_fd.c
*/
int					ft_atoi_fd(const char *s);

/*
**	ft_lst_add_end.c
*/
void				ft_lst_add_end(t_list *previous, t_list *neew);

/*
**	ft_strncmp_complete.c
*/
int					ft_strncmp_complete(char *s1, char *s2, size_t n);

/*
**	init.c
*/
void				init(t_historic **termcaps, char ***env, char **entry);

/*
**	init2.c
*/
void				init_proc(void);
void				init_var_aggrfd(t_historic *termcaps);

/*
**	init_historic.c
*/
char				**recover_historic_file(t_historic *termcaps);
void				create_historic_list(t_historic *termcaps, char **taab);
void				set_path_historic_file(t_historic *termcaps, char **env);

/*
**	is_a_builtin.c
*/
int					is_a_builtin(char *s);

/*
**	main.c
*/
void				free_memory(char **entry, t_historic *termcaps,
													t_list **root, int prompt);

/*
**	manage_historic.c
*/
void				add_historic(t_historic *termcaps, char **entry,
																int check_max);
void				save_historic_file(t_historic *termcaps);

/*
**	proc_management.c
*/
void				save_pid(pid_t pid);
void				kill_process_still_in_progress(void);

/*
**	s_lstnew.c
*/
t_list				*s_lstnew(char const *content, const char *filename);

/*
**	set_termios.c
*/
int					set_termios(struct termios *term, t_save_fd *save);

/*
**	show_elem.c
*/
void	show_elem(t_list *elem);

/*
**	signals.c
*/
void				resize_win(int numsig);
void				signals_management(void);
int					sig_child_func(int status);
void				signals_reset(void);

/*
**	singletons.c
*/
t_historic			*get_termcaps(void);
char				***get_env(void);
t_proc				*get_proc(void);

/*
**	tools.c
*/
int					len_before_thischar(char *s, char c);
int					there_are_no_equal(char *s);
int					len_at_thischar(char *s, char c);
int					len_after_thischar(char *s, char c);

/*
**	tools2.c
*/
char				*ft_getenvfull(char *name, char **env, int dup);
char				*ft_getenv(char *name, char **env);
char				**ft_getenvadress(char *name, char **env);
int					is_just_spaces(char *cmd);

/*
**	debugg
*/
void				show_binary_tree(t_list *root);
void				show_binary_tree_lr(t_list *root);

#endif
