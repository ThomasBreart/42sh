/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 10:56:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 15:25:33 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMCAPS_H
# define FT_TERMCAPS_H

/*
**	ctrl H = copier partie de ligne
**	ctrl K = couper partie de ligne
**	ctrl T = copier toute la cmd
**	ctrl P = coller
**	ctrl U = couper toute la cmd
*/

# define KEY_UP 4283163
# define KEY_DOWN 4348699
# define KEY_LEFT 4479771
# define KEY_RIGHT 4414235
# define KEY_BACKSP 2117294875
# define KEY_SHIFT_LEFT 74982532143899
# define KEY_SHIFT_RIGHT 73883020516123
# define KEY_SHIFT_UP 71683997260571
# define KEY_SHIFT_DOWN 72783508888347
# define KEY_HOME 4741915
# define KEY_END 4610843
# define KEY_RET 10
# define KEY_EOF 4
# define KEY_NOPE 0
# define KEY_TAB 9
# define KEY_CTRL_E 5
# define KEY_CTRL_H 8
# define KEY_CTRL_R 18
# define KEY_CTRL_K 11
# define KEY_CTRL_T 20
# define KEY_CTRL_P 16
# define KEY_CTRL_U 21
# define KEY_DEL 127
# define KEY_SUPP 2117294875

typedef struct	s_func_tab
{
	long int	k;
	int			(*f)(t_historic *hist, char **entry);
}				t_func_tab;

int				cmd_is_open_error(char error);

/*
**	calculation_parenthesis.c
*/
int				calculation_parenthesis(t_historic *tcaps, char *s, char open,
																char close);

/*
**	check_backslash.c
*/
int				check_backslash(t_historic *termcaps, char *entry);

/*
**	cmd_still_open.c
*/
int				cmd_still_open(t_historic *termcaps, char **entry);

/*
**	continue_cmd.c
*/
int				check_open_chars(t_historic *termcaps, char *s, char open,
																char close);
int				check_open_quotes(t_historic *termcaps, char *s);

/*
**	get_command.c
*/
int				get_command(t_historic *termcaps, char **entry);

/*
**	get_func_tab.c
*/
t_func_tab		*get_func_tab(void);

/*
**	init_get_cmd.c
*/
void			init_var_cmd(t_historic *termcaps, char **entry);

/*
**	key_copy.c
*/
int				ft_key_copy_part(t_historic *termcaps, char **entry);
int				ft_key_copy_all(t_historic *termcaps, char **entry);

/*
**	key_cut.c
*/
int				ft_key_cut_part(t_historic *termcaps, char **entry);
int				ft_key_cut_all(t_historic *termcaps, char **entry);

/*
**	key_del.c
*/
int				ft_key_del(t_historic *termcaps, char **entry);

/*
**	key_down.c
*/
int				ft_key_down(t_historic *termcaps, char **entry);

/*
**	key_end.c
*/
int				ft_key_end(t_historic *termcaps, char **entry);

/*
**	key_eof.c
*/
int				ft_key_eof(t_historic *termcaps, char **entry);

/*
**	key_home.c
*/
int				ft_key_home(t_historic *termcaps, char **entry);

/*
**	key_left.c
*/
int				ft_key_left(t_historic *termcaps, char **entry);

/*
**	key_paste.c
*/
int				ft_key_paste(t_historic *termcaps, char **entry);

/*
**	key_right.c
*/
int				ft_key_right(t_historic *termcaps, char **entry);

/*
**	key_selection_mode.c
*/
void			set_end_select(t_historic *termcaps);
int				ft_key_selection_mode(t_historic *termcaps, char **entry);

/*
**	key_shifts.c
*/
int				ft_key_shift_left(t_historic *termcaps, char **entry);
int				ft_key_shift_right(t_historic *termcaps, char **entry);
int				ft_key_shift_up(t_historic *termcaps, char **entry);
int				ft_key_shift_down(t_historic *termcaps, char **entry);

/*
**	key_supp.c
*/
int				ft_key_supp(t_historic *termcaps, char **entry);

/*
**	key_tab.c
*/
int				ft_key_tab(t_historic *termcaps, char **entry);

/*
**	key_tab_search.c
*/
void			find_dir_to_open(char **word, char **dir_path, char **word_cut);
int				check_just_one_file_in_dir(DIR *dir, char **part_match);
void			part_match_files(DIR *dir, char *word_cut, char **part_match);

/*
**	key_up.c
*/
int				ft_key_up(t_historic *termcaps, char **entry);

/*
**	keys_cmds_addchar.c
*/
char			*concat_entry(char *buffread, char newchar, int j);
int				cmd_add_char(t_historic *termcaps, char **entry);

/*
**	keys_cmds_ret.c
*/
int				ft_key_ret(t_historic *termcaps, char **entry);

/*
**	key_cmds_ret_llr.c
*/
int				ft_key_ret_llr(t_historic *termcaps, char **entry);

/*
**	key_tools_show.c
*/
void			show_entry(t_historic *termcaps, char *entry);
void			reset_curx(int decal);
void			erase_cmd(int col_sup, t_historic *termcaps);

/*
**	tools_termcaps.c
*/
int				ft_outc(int c);
void			set_cur_end(t_historic *termcaps, char *entry);

#endif
