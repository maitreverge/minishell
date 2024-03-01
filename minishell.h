/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:04:35 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/01 18:09:54 by flverge          ###   ########.fr       */
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
# include <errno.h>
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


typedef	struct	s_pars
{
	// only the first node
	bool MasterKill;
	bool isRedirIn; // does the whole input contains at least one redir_in > OR >>
	int	error_message;
	int		last_exit_status; // variable of $?

	// Node Command
	bool	isCommand;
	struct s_command	*cmd;
	
	// Node File
	bool isFile;
	struct s_file *fl;
	
	// Node Operator
	bool isOperator;
	struct s_operator *operator;

	// Node here_doc
	bool isHereDoc;
	char *here_doc;
	
	// adresses
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
	// char	*to_allocate; // ! useful ??
	int		i;
	int		j;
	int		k;
	char	starting_quote;
	char	end_quote;
	int		real_len;
	bool	expansion;
	
}	t_utils;

typedef struct s_env_list
{
	char *original_envp; // ! add original value
	char *key;
	char *value;
	struct s_env_list *next;
}	t_env_list;

typedef struct s_alloc
{
	char **splitted_prompt;
	char **cleaned_prompt;
	char **paths;
}	t_alloc;

// struct for norming parsing
typedef struct s_split_utils
{
	int start_quote;
	int end_quote;
	int i;
	size_t j; // allocation
	int start; // allocation
	size_t result; // countwords
}	t_split_utils;


// ! Functions prototypes

// new_nodes
void	new_node_command(t_pars **pars, t_alloc **utils, int *i);
void	new_node_file(t_pars **pars, char *cleaned);
void	new_node_operator(t_pars **pars, char *cleaned);
void	new_node_here_doc(t_pars **pars, char *cleaned);

//split_parser
char	**parsing_split(char *s);
size_t	parsing_countwords(char *str);
void	allocation(char **buffer, char *str, size_t len_s);




// turbo_parser
void	turbo_parser(char *p, t_pars **pars, t_env_list **env, t_utils **s_u);


// turbo_parser_2
void	pars_alloc(t_pars **pars, t_alloc **u_alloc);
void	search_redir_in(t_pars **pars, char **splited, char **cleaned);
bool	testing_builtin(char *cleaned);
char	*join_path_cmd(char *cleaned, char **paths);


//extract_paths
char **extract_paths(t_env_list **s_env);

// path_splitting
char	**path_split(char const *s, char c);


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
t_pars	*lstfirst(t_pars *lst);



// bools_parsing

bool	is_token_opr(char *splited, char *cleaned);
bool is_token_redir_delim(char *cleaned);
bool is_last_node_operator(t_pars **pars);
bool is_last_node_pipe(t_pars **pars);
bool is_last_node_redir(t_pars **pars);

bool is_last_node_r_in_delim(t_pars **pars);
bool is_last_node_here_doc(t_pars **pars);

bool is_last_node_cmd(t_pars **pars);
bool is_last_node_file(t_pars **pars);
bool is_token_pipe(char *splited, char *cleaned);

bool is_token_redir_out(char *splited, char *cleaned);






// print_final_struct
void	print_final_struct(t_pars **pars);

bool	is_operator_char(char c);

void	free_t_alloc(t_alloc *alloc);

t_env_list	*env_lstnew(char *s_key, char *s_value, char *envp);
t_env_list	*env_lstlast(t_env_list *lst);
void	env_lstadd_back(t_env_list **lst, t_env_list *new);

void	free_full_t_pars(t_pars **pars);

void	print_env(t_env_list **envp, char *target, char *message);

void	alloc_pars(char *str, t_split_utils *u);
void	loop_sub_quote(char *str, t_split_utils *u);

char	**clean_prompt(char **b, t_utils **ut, t_env_list **env, t_pars **p);


bool	is_buff_valid_doll(char *str);
void	parsing_doll_var(t_utils **utils, char *buff, t_env_list **s_env, t_pars **pars);

void	calculate_len_doll(char *buff, t_utils **u, t_env_list **s_env, t_pars **pars);

void	copying_doll(char *buff, t_utils **utils, t_env_list **s_env, t_pars **pars);

bool	unclosed_quotes(char *str);


bool alloc_part_1(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc);
bool alloc_part_2(t_alloc *cur, int *i, t_pars **pars);
bool alloc_part_3(t_alloc *cur, int *i, t_pars **pars);
bool alloc_part_4(t_alloc *cur, int *i, t_pars **pars);
bool alloc_part_5(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc);





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * .h George

typedef struct s_all
{
	char	**copy_envp;
	t_env_list	*env_lst;
	char		*readline_line;
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
int		ft_echo(char **args, t_pars *pars);//char *s, t_all *all, 
void	ft_cd(t_pars **pars, t_env_list **envp);
void	ft_pwd(char **name_args, t_pars **pars);
void	ft_export(t_env_list **envp, char **args, t_all *all, t_pars **pars);
void	ft_unset(t_env_list **envp, char **name_args, t_pars **parsing);
void	ft_env(char **args, t_all *all, t_pars **pars);
void	ft_exit(char **name_option, t_all *all, t_pars **pars);



/*Signal handler*/
int		signals(t_pars *all);

/*Pipes, redirections*/

int		check_next_operator(t_pars *lst);
void	exec_builtin(t_pars *pars, t_all *all);
int		pipes(t_pars **lst, t_all *all, int fd_stdin);
int		redirect_input_delimitor(t_pars **lst, t_all *all);
int		redirect_input(t_pars **lst, t_all *all);
int		redirect_output(t_pars **lst, t_all *all, int input_fd);

/*Utils*/
size_t	size_of_ptr_ptr(void **arr);
void	free_arr(void **array, int size);
void	free_t_pars(t_pars **lst);
size_t	lstlen(t_pars *lst);
void	fork_error(int **fds, pid_t **ch_pid);
size_t	num_of_pipes(t_pars *lst);

/*Flo, but i don't want to touch his part of this .h*/
t_pars	*init_1st_node_pars(void);
void	free_firstnode_pars(t_pars **pars);

void	free_all(t_all **all);

#endif
