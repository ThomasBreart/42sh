/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 17:04:29 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/26 17:58:10 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include "get_next_line.h"
# include "../libft/libft.h"

# define GREEN   		"\x1b[32m"
# define CYAN    		"\x1b[36m"
# define RED				"\x1b[31m"
# define RESET   		"\x1b[0m"
# define KU					4283163
# define KD					4348699
# define KR					4414235
# define KL					4479771
# define ESP				32
# define DEL 				127
# define TILDE			126
# define RET				10
# define HOME				4741915
# define END				4610843
# define CTRL_D			4
# define CTRL_U			21
# define CTRL_P			16
# define CTRL_R			18
# define CTRL_L			12
# define CTRL_T			20
# define U_CUT			117
# define MAX_SIZE		1
# define QUOTES			'\''
# define D_QUOTES		'"'
# define B_QUOTES		'`'
# define PARENTHESES	'('
# define C_PARENTHESES	')'
# define ACCOLADES 		'{'
# define C_ACCOLADES 	'}'
# define CROCHETS 		'['
# define C_CROCHETS 	']'
# define SYNTAX_ERROR 	7

# define ALT_LEFT		1146821403
# define ALT_RIGHT	1130044187
# define ALT_UP			1096489755
# define ALT_DOWN		1113266971
# define TERM_ENV		"xterm-256color"
# define LEFT				"le"
# define RIGHT			"nd"
# define DOWN				"do"
# define UP					"up"
# define DEFAULT		"me"
# define REVERSE		"mr"
# define BEGIN			"cr"
# define DOWN_MAJ		"DO"
# define CLEAR 			"cd"
# define CLEAR_TERM "cl"

pid_t										g_father;

typedef struct								s_norme
{
	int										current;
	int										previous;
	char									*old;
	char									*pwd;
	char									*str;
	char									**copy;
	int										i;
}											t_norme;

typedef struct								s_tty
{
	struct termios							term;
	struct termios							backup;
}											t_tty;

typedef struct								s_ctrl_c
{
	int										bol;
	int										main_loop;
}											t_ctrl_c;

typedef struct								s_env
{
	char									**environ;
}											t_env;

typedef struct								s_it
{
	int										i;
	int										len;
	int										saved_i;
	int										first;
	int										buffer;
	int										offset;
	char									*tmp_line;
	char									*line;
	char									*tmp_buffer;
	int										r_video;
	int										ws_col;
	int										nb_current_line;
	int										eof;
}											t_it;

typedef struct								s_hist
{
	char									*cmd;
	struct s_hist							*prev;
	struct s_hist							*next;
}											t_history;

typedef struct								s_hash_tree
{
	int										indice;
	struct s_list							*node;
	struct s_hash_tree						*left;
	struct s_hash_tree						*right;
	struct s_hash_tree						*equal;
}											t_hash_tree;

/*
**	errors
*/
void										command_not_find(char *arg);
void										permission_denied(char *str,
											char *path);
void										setenv_error(int boolean);
void										unsetenv_error(void);
void										not_access(void);
void										tcgetattr_error(void);
void										tcsetattr_error(void);
void										terminal_not_find(void);
void										cant_move_home(void);
void										no_such_file(char *path);

/*
**	builtins
*/
t_list										*check_bultins_command(
											t_list *pipelines, t_env *env);
int											ft_setenv(char **av, t_env *env);
void										ft_unsetenv(char **av, t_env *env);
void										ft_cd(char **av, t_env *env);
int											ft_env(char **av, char ***environ,
											int ok);
int											env_bad_arg(char *av);
void										env_parse(char **av, char **env);
char										**env_parsing(char ***av);
char										**copy_environ(char **environ);
char										**void_env(void);
void										ft_exit(char **av, t_env *env);
void										ft_echo(char **av, char **environ);

/*
**	free
*/
void										free_double_array(char **arr);
void										free_elements(char *one,
											char *two, char *three,
											char *four);
void										free_struct(t_norme *s);

/*
**	parse arguments
*/
void										check_tilde_and_dollar(
											char **environ, char **av);
void										check_tilde_and_dollar__str(
											char **environ, char **av,
											int i, int duote);
void										replace_tilde(char **origin,
											int *index, char **environ);
void										replace_dollar(char **av,
											int *i, char **environ);
char										*get_token(char *s);

/*
**	parse environ
*/
void										remove_env(char **av, int indice);
int											return_env_indice(char **environ,
											char *env);
char										*return_env(char **environ,
											char *env);
void										move_old_and_pwd(t_env *env,
											char *old, char *pwd);
void										print_env(char **environ);
void										loop_remove_env(char **av,
											t_env *env);
void										replace_item_environ(char **environ,
											char *env, char *av);
void										append_item_environ(t_env *env,
											char *environ, char *av);
int											return_env_size(char **environ);
void										replace_char(t_it *it, char cmd[2]);
int											check_env(char **environ);
char										*append_path(char *environ,
											char *av);

/*
**	init terminal
*/
int											init_terminal_data(t_tty *tty);
t_tty										*ft_stock_term(t_tty *tty);
void										suspend_terminal(void);
void										resumed_terminal(void);
void										reset_term(void);

/*
**	parser
*/
int											check_line(char *line, t_env *env,
											int boolean);
char										**append_set_path(char *cmd);
void										parse_line(t_it *it);
void										edit_line(t_it *it);
int											return_offset(void);

/*
**	quotes gestion
*/
int											check_line_quotes(char *s,
											char **back);
int											quote_not_close(char *begin,
											char *end, char **back);
void										convert_it_line(t_it *it,
											t_list *args, char **back);
int											is_a_newline_quotes(t_it *it,
											char *end, t_list **args);
char										browse_skip_quote(char **s,
											char tmp);
void										free_list_and_struct(t_it *it,
											t_list *args);
void										stop_quotes(t_it *it, t_ctrl_c *c,
											char **back, t_list *args);

/*
**	cursor_moves
*/
void										move_left(t_it *it);
void										move_right(t_it *it);
void										del_char(t_it *it);
void										move_begin(t_it *it);
void										move_end(t_it *it);
void										move_one_word_left(t_it *it);
void										move_one_word_right(t_it *it);
t_it										*init_it_struct(int tmp);
void										del_char_buffer(t_it *it,
											int current);
void										del_current(t_it *it);
void										multi_line_text(t_it *it);
void										move_up_and_down(t_it *it);
void										move_n_char(t_it *it, int direction,
											int n);
void										check_move_first_elem(t_it *it);
void										cursor_on_last_pos(t_it *it,
											int line);
void										move_one_word_left_1(t_it *it,
											int i);
void										move_one_word_left_2(t_it *it,
											int i);

/*
**	copy paste
*/
void										ft_cut_select(t_it *it);
void										cut_line(t_it *it);
void										copy_tmpline(t_it *it);
void										paste_line(t_it *it);
void										put_reverse(t_it *it);

/*
**	History
*/
t_history									*ft_stock_history(t_history
											*history);
void										print_history(t_it *it);
t_history									*create_elem(t_history *history,
											char *line);
t_history									*go_to_end(t_history
											*history);
t_history									*up_history(t_history
											*list, t_it *it);
t_history									*down_history(t_history *list,
											t_it *it);

/*
**	Utilities
*/
int											my_putchar(int c);
int											print_prompt(void);
void										check_shlvl(t_env *env);
void										check_only_space(t_it *it);
t_it										*ft_stock_it(t_it *it);
t_ctrl_c									*ft_stock_ctrl_c(t_ctrl_c *ctrl_c);
void										go_to_bottom(t_it *it);
int											ft_abs(int i);
void										path_manager(t_env *env);

/*
**	Hachage
*/
void										parse_path_directories(t_env *env);
void										insert_node(t_hash_tree **tree,
											t_list *lst);
char										*search_node(t_hash_tree *tree,
											int indice);
int											ft_hash(char *name);
t_hash_tree									*ft_stock_tree(t_hash_tree *tree);
char										*hash_cmd(char *cmd);
void										reset_tree(t_hash_tree **tree);
void										file_counter(char *path);
void										update_hash(t_env *env);

/*
**	Signals
*/
void										rec_size(t_it *it);
void										check_signal(void);

#endif
