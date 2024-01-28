/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:35 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/28 16:13:29 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
//# include <stropts.h>
# include <termios.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include "env_linked_list.h"

typedef struct s_exit_status_list
{
	int							status;
	struct s_exit_status_list	*next;
}	t_exit_status_list;

void		free_list(t_env_list *lst);
t_env_list	*copy_env_into_list(char **envp);

/*Builtins*/
void	free_tokens(char **t);
int		ft_echo(char *s, char **envp, int fd);
int		ft_cd(char *path, t_env_list *envp);
int		ft_pwd(t_env_list *envp, int fd, bool print);


#endif
