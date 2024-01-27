/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:35 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/27 04:26:38 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lft/libft.h" // libft george
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# define S_QUOTE '\'' // backslack for making it a char
# define D_QUOTE '\"'
# define PIPE '|'
# define RED_IN '<'
# define RED_IN_DEL "<<"
# define RED_OUT '>'
# define RED_OUT_APP ">>"
# define DOLL_ENV '$'

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * .h Florian


// ! Master Struct for parsing
typedef	struct	s_pars
{
	
	struct s_pars *prev;
	struct s_pars *next;
}	t_pars;

// ! Parsing Substructures








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * .h George


typedef struct s_exit_status_list
{
	int							status;
	struct s_exit_status_list	*next;
}	t_exit_status_list;

/*Builtins*/
void	free_tokens(char **t);
int		ft_echo(char *s, char **envp, int fd);
int		ft_cd(char *path);
int		ft_pwd(void);

#endif
