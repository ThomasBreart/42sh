/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 10:44:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/19 16:48:48 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

/*
**	builtin_history.c
*/

int			                builtin_history(char **argv);
char                    *reverse_split(char **argv);
int                     history_usage();
int                     numeric_argument_error(char *argv);
int                     check_errors(char *argv, int index);
int                     check_numeric_arg(char *argv);
void                    print_historyy(int n);
int                     out_of_range(char *argv);
int                     get_value(char *cpy, int index);
int                     flag_d(char *args, t_flags *flags);
int                     put_flag_d(t_flags *flags);
char                    *get_argument(char *argv, int end);
int                     check_history_flags(char *args, t_flags flags, char **ar);
void                    flag_p(char **ar);
void                    flag_c(void);
int                     del_indice_history(t_flags flags);
int                     ft_lst_size(t_list *history);
void                    flag_w(t_flags *flags);
void                    check_what_element_to_delete(t_historic
                        *termcaps, t_list *cpy);
void                     flag_r(t_flags *flags);
void                     flag_s(char *str);
int		                   del_element_list(t_list *first);
int                      ft_isnumber(int c);
int	                     get_len_of_int(int nb);
void	                   flag_n(t_flags *flags);
void	                   flag_a(t_flags *flags);


/*
**	builtin_cd.c
*/
int		builtin_cd(char **argv, char ***env);

/*
**	builtin_env.c
*/
int		builtin_env(char **argv, char **env);

/*
**	builtin_env_options.c
*/
char	**shift_options(char ***argv);
int		env_check_option_i(char **argv);
char	**env_exec_option_u(char ***cpenv, char **argv);
int		builtin_env_options(char **argv);

/*
**	builtin_exit.c
*/
int		builtin_exit(t_list *elem, char **env, t_save_fd *save);
int		clean_exit(char **env, t_save_fd *save);
void	free_historic(t_historic *termcaps);

/*
**	builtin_setenv.c
*/
int		builtin_setenv(char **argv, char ***env);

/*
**	builtin_unsetenv.c
*/
int		builtin_unsetenv(char **argv, char ***env);

#endif
