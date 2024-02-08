/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:35 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/08 15:34:31 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE //NO idea why this needs to be here or wtf it does, but sigaction doesn't work otherwise

# include "lft/libft.h" // libft george
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <stdbool.h> // library for handling bool
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
# define PIPE "|"
# define RED_IN "<"
# define RED_IN_DELIM "<<"
# define RED_OUT ">"
# define RED_OUT_APP ">>"
# define DOLL_ENV '$'
# define EMPTY_EXIT_LIST -999	//Glambrig

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * .h Florian


// ! Master Struct for parsing
typedef	struct	s_pars
{
	// only the first node
	bool MasterKill;
	bool isRedirIn;
	int		last_exit_status; // variable of $?

	// real parsing	
	bool	isCommand;
	struct s_command	*cmd;
	
	bool isFile;
	struct s_file *fl;
	
	bool isOperator;
	struct s_operator *operator;
	// bool isPipe;
	// bool isRedir;
	// int	which_redir; // let's say something like 1 for >, 2 for <, 3 for >>, 4 for <<
	
	struct s_pars *prev;
	struct s_pars *next;
}	t_pars;

// ! Parsing Substructures

typedef	struct	s_command
{
	bool isBuiltin;
	char *command_name;
	char *command_path; // full valid path
	char **name_options_args; //Split ' '
}	t_command;

typedef	struct	s_file
{
	char *file_name;
	bool file_exist;
	bool auth_r;
	bool auth_w;
	bool auth_x;
}	t_file;

typedef	struct	s_operator
{
	bool pipe;
	
	bool redir_in;
	bool redir_in_delim;
	
	bool redir_out;
	bool redir_out_app;
} 	t_operator;

// ! Utils structures

typedef	struct	s_utils
{
	char	**result; // final parsing
	char	*to_allocate; // ! useful ??
	int		i;
	int		j;
	int		k;
	char	starting_quote;
	char	end_quote;
	int		real_len;
	
}	t_utils;

typedef struct s_env_list
{
	char *original_envp; // ! add original value
	char *key;
	char *value;
	struct s_env_list *next;
}	t_env_list;

// ! Functions prototypes

// turbo_parser
void	turbo_parser(char *prompt, t_pars **pars, t_env_list **s_env, t_utils **s_utils);

// turbo_parser_2
void	pars_alloc(t_pars **pars, char **splited, char **cleaned);


// utils_parsing
bool	is_whitespace(char c);
bool	is_any_quote(char c);
void	free_split(char **to_free);
char	*ft_strncpy(char *dest, char const *src, size_t n);
void	free_s_env(t_env_list **env);
void	free_s_utils(t_utils **utils);
int		int_len(int n);
int		ft_strcmp(char *s1, char *s2);




// split_parser
char	**parsing_split(char *s);
size_t	parsing_countwords(char *str);

//pars_struct_fts
void	init_pars_struct(t_pars **pars);
t_utils *utils_init_struct(int len);

// split_2
char	**ft_2_split(char const *s, char c);

// linked_list_functions
t_pars	*lstnew(int number);
t_pars	*lstlast(t_pars *lst);
void	lstadd_back(t_pars **lst, t_pars *new);
void	lstadd_front(t_pars **lst, t_pars *new);
int		lstsize(t_pars *lst);






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * .h George

typedef struct s_all
{
	t_env_list	*env_lst;
	char		*readline_line;
	int			last_exit_status;
}	t_all;


typedef struct s_exit_status_list
{
	int							status;
	struct s_exit_status_list	*next;
}	t_exit_status_list;

/*Env*/
void	copy_env_into_list(t_env_list **env, char **envp);

/*Builtins*/
void	free_tokens(char **t);
int		ft_echo(char *s, t_all *all, int fd);
int		ft_cd(char *path, t_env_list *envp);
int		ft_pwd(t_env_list *envp, int fd, bool print);
void	ft_export(t_env_list **envp, char *line);
void	ft_unset(t_env_list **envp, char *line);
int		ft_exit(t_all *all, char *readline_return, int fd);

/*Signal handler*/
int		signals(t_all *all);

/*Pipes, redirections*/
void	pipes(t_pars *lst, int fd_stdin);

/*Utils.c*/
void	free_arr(void **array, int size);

#endif
