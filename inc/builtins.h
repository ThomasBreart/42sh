/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 10:44:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/04 22:51:25 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

/*
**	builtin_history.c
*/
int		builtin_history(char **argv);
void	print_history(int n);
int		numeric_argument_error(char *argv);
int		ft_isnumber(int c);
int		history_usage();
int		out_of_range(char *argv);
int		flag_d(char *args, t_flags *flags);
void	flag_s(char *str);
void	flag_p(char **ar);
void	flag_c(void);
void	flag_r_or_n(t_flags *flags);
void	flag_a_or_w(t_flags *flags);
int		put_flag_d(t_flags *flags, char **args);
int		check_history_flags(char *args, t_flags flags, char **ar);
int		check_numeric_arg(char *argv);
int		del_indice_history(t_flags flags);
char	*get_argument(char *argv, int end);
int		ft_lst_size(t_list *history);
int		get_value(char *cpy, int index);
void	check_what_element_to_delete(t_historic
		*termcaps, t_list *cpy);
int		get_len_of_int(int nb);
int		append_flag(char **args, t_flags *flags);
char	*reverse_split(char **argv, int i);
char	*get_tokenn(char *argv);

/*
**	builtin_echo.c
*/
int		builtin_echo(char **argv);

/*
**	builtin_read.c
*/
int		builtin_read(char **argv, t_save_fd *save, char ***env);
int		parse_flag(char **args, int *flag);
char	*return_one_line(int flag);
void	make_copies(char *argv, char ***env, int flag);

/*
**	builtin_cd.c
*/
int		builtin_cd(char **argv, char ***env);
int		go_home(char ***env, int flag);
int		go_oldpwd(char ***env, int flag);
int		ft_chdir(char *target, char ***env, int flag);
int		print_error_cd(char *str);
char	*get_symbolink_path(char ***env, char *path);
int		check_arg(char *target);
int		cd_parse_flag(char **args, int *flag);
int		cd_usage(char *args);
void	update_pwd_and_oldpwd(char ***env, char *pwd);
void  update_pwd(char ***env);
void  update_oldpwd(char ***env);

/*
**	builtin_env.c
*/
int		builtin_env(char **argv, char **env);

/*
**	builtin_env_exec_bin.c
*/
int		env_exec_bin(char **argv, char **cpenv, char **env);

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
int		builtin_setenv(char **argv, char ***env, int forced);

/*
**	builtin_unsetenv.c
*/
int		builtin_unsetenv(char **argv, char ***env);

/*
**	builtin_explorer
*/
int		builtin_explorer(t_historic *t, char ***env);
int		builtin_glob(char **argv);

#endif
