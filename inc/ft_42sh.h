/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 22:31:35 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/06 15:46:58 by jmaccion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include "../libft/includes/libft.h"
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
# include "builtins.h"
# include "termcaps.h"
# include "redirs.h"

/*
**	check_word_and_subsh.c
*/
int					check_word_and_subsh(t_list *first);

/*
**	get_set_save_fd.c
*/
t_save_fd			*get_set_save_fd(t_save_fd *save);

/*
**	exec_backquotes.c
*/
int					exec_backquotes(char **str);

/*
**	remove_onelvl_escape_backslash.c
*/
void				remove_onelvl_escape_backslash(char **str);

/*
**	extract_subcmd.c
*/
int					extract_subcmd(char **str, int start_analysis,
					int *start_subcmd, char **sub_cmd);

/*
**	extract_event.c
*/
int					extract_event(char **str, int start_analysis,
					int *start_subcmd, char **sub_cmd);

/*
**	exec_subshell.c
*/
int					exec_subshell(t_list *elem, t_save_fd *save);
int					exec_cmd_subsh(t_list *first, char ***env, t_save_fd *save);

/*
**	update_elem.c
*/
void				update_elem(t_list *elem, int change_argv);

/*
**	remove_quoting_chars.c
*/
void				remove_quoting_chars(t_list *elem);

/*
**	realloc_tab.c
*/
char				**realloc_tab(char **oldtab, int *maxlen,
					const char *filename);

/*
**	find_full_cmd.c
*/
char				*find_full_cmd(char *s, t_historic *termcaps);

/*
**	cmd_is_open.c
*/
int					cmd_is_open(char *str, int *end_backslash);

/*
**	check_event_designators.c
*/
int					check_event_designators(char **entryr);

/*
**	add_str_in_str.c
*/
char				*add_str_in_str(char *dest, char *src, int position);

/*
**	goto_next_funcs.c
*/
char				*goto_next_quote(char *str);
char				*goto_next_backquote(char *str);
char				*goto_next_parenthesis(char *str);
char				*goto_next_word(char *str, char c);

/*
**	goto_next_char.c
*/
char				*goto_next_char(char *str, char c);

/*
**	goto_close_quote.c
*/
int					goto_close_bracket(const char *str);

/*
**	handler_sigwinch.c
*/
void				handler_sigwinch(int numsig);

/*
**	handler_sigint.c
*/
void				handler_sigint(int numsig);

/*
**	handler_sigcont.c
*/
void				handler_sigcont(int numsig);

/*
**	handler_sigtstp.c
*/
void				handler_sigtstp(int numsig);

/*
**	check_backquotes.c
*/
void				check_backquotes(t_list **first);

/*
**	clean.c
*/
void				free_tree(t_list *root);

/*
**	cmd_analysis.c
*/
t_list				*cmd_analysis(char **entry);

/*
**	cmd_simple.c
*/
int					exec_simple(t_list *elem, char ***env, t_save_fd *save);
int					cmd_simple_prog(t_list *elem, char **env, t_save_fd *save);
void				stock_ret_val_in_env(int ret, char ***env);

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
void				del_tlist(t_list *elem);

int					del_elem_list(t_list *first);
/*
**	errors.c
*/
void				errors(int a);
int					error_name(char *fullpath, char *content);
int					internal_error(char *s, char *error, int dead);
int					error_fd_aggr(int fd_aggr);

/*
**	error_event_not_found.c
*/
int					error_event_not_found(char *str, int error);

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
int					event_string_substitution(char *sub_cmd, char **new_str,
														int *is_substitution);

/*
**	exec_cmd.c
*/
int					exec_cmd(t_list *first, char ***env);
int					exec_token(t_list *elem, char ***env, t_save_fd *save);

/*
**	exec_cmd_tools.c
*/
int					check_return_redirs(t_vars_redirs *vars, char ***env);
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
char				**recover_historic_file(t_historic *termcaps, int limit);
void				create_historic_list(t_historic *termcaps, char **taab);
void				set_path_historic_file(t_historic *termcaps, char **env);

/*
**	cmd_simple_builtin.c
*/
int					is_a_builtin(char *s);
int					cmd_simple_builtin(t_list *elem, char ***env,
															t_save_fd *save);

/*
**	main.c
*/
void				free_memory(char **entry, t_historic *termcaps,
													t_list **root, int prompt);

/*
**	manage_historic.c
*/
void				add_historic(t_historic *termcaps, char **entry,
					int check_max, int new);
void				save_historic_file(t_historic *termcaps, int flag_a);

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
void				show_elem(t_list *elem);

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

/*
**	glob/glob.c
*/
void				do_globbing(char ***elem);

/*
**	add_hash.c
*/
int					add_bin_to_hashtable(char *bin, char *fullpath_bin);

/*
**	find_shell_lvl.c
*/
char				*find_shlvl(char **taab);

/*
**	hash.c
*/
char				*check_hashtable(char *bin, char **env);
int					hash_content(char *str);

/*
**	meta_check_shellvar.c
*/
void				check_shell_variable(char **entry, char *tmp, char **env);

/*
**	meta_check_tild.c
*/
void				check_tild(char **entry);

/*
**	metacharacters.c
*/
int					convert_metacharacters(t_list *elem, char **env);
void				edit_line_meta(char **entry, char *value, int pos_key,\
int len_key);

#endif
