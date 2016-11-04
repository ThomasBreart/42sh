/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 10:44:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/04 15:27:22 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

/*
**	builtin_read.c
*/
int    builtin_read(char **argv, t_save_fd *save);
int		 read_usage(void);
int     parse_flag(char **args, int *flag);

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

/*
**	builtin_setenv.c
*/
int		builtin_setenv(char **argv, char ***env);

/*
**	builtin_unsetenv.c
*/
int		builtin_unsetenv(char **argv, char ***env);

#endif
