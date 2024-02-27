/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:51:37 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/27 14:44:11 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	cd MUST be called with the full line received from readline(),
	otherwise it (probably) won't work.
	This should update the env PWD var (using ft_pwd()).
	
	IMPORTANT: env variables should also work, e.g. cd $HOME
*/
int	ft_cd(char *s, t_env_list *envp)
{
	char 	**tokens;
	char	*homepath;

	tokens = NULL;
	if (ft_strchr(s, ' ') != NULL)
		tokens = ft_split(s, ' ');
	/*cd with no parameters changes to home directory*/
	if ((tokens != NULL && tokens[1] == NULL) || tokens == NULL)
	{
		homepath = ft_strjoin("/home/", getenv("USER"));
		chdir(homepath);
		free(homepath);
		free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
		ft_pwd(&envp, false);
		return (0);
	}
	else if (tokens != NULL)
	{
		chdir(tokens[1]);
		ft_pwd(&envp, false);
	}
	free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
	return (0);
}

/*Also changes the env PWD variable to reflect any changes.*/
void	ft_pwd(t_env_list **envp, bool print)
{
	char		*cwd;
	char		*new_pwd_env;
	t_env_list *temp;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (print == true)
	{
		printf("%s\n", cwd);
	}
	new_pwd_env = ft_strjoin("PWD=", cwd);
	temp = *envp;
	while (ft_strncmp((*envp)->original_envp, "PWD", 3) != 0)
		*envp = (*envp)->next;
	if (*envp != NULL)
	{
		//free((*envp)->original_envp);
		(*envp)->original_envp = new_pwd_env;
	}
	if (cwd != NULL)
		free(cwd);
	*envp = temp;
}

/*Displays a list of the environment variables for the
	current terminal session.*/
void	ft_env(char **args, t_all *all, t_pars **pars)
{
	t_env_list *temp;

	if (args[1]) // if there is an argument to env
	{
		ft_putendl_fd("env builtin does not take any argument\n", 2);
		lstfirst(*pars)->last_exit_status = 127; // error code if env fails
		return ;
	} 
	temp = all->env_lst;

	while (all->env_lst != NULL)
	{
		printf("%s\n", all->env_lst->original_envp);
		// ft_putstr_fd(all->env_lst->original_envp, fd);
		// ft_putchar_fd('\n', fd);
		all->env_lst = all->env_lst->next;
	}
	all->env_lst = temp;
	// return (0);
}

/*Remember to also free all!!!*/
// void	ft_exit(char **name_option, t_all *all, t_pars **pars)
// {
// 	t_pars *first_node;
// 	bool error;

// 	first_node = lstfirst(*pars);

// 	if (!name_option[1])
// 		error = false;
// 	else
// 		error = true;
// 	printf("exit\n");
// 	if (error)
// 		printf("exit : %s : unknown argument\n", name_option[1]);
// 	free_all(&all); // free all node + s_env nodes
// 	free_full_t_pars(&first_node);
	
// 	exit(-1);
// }

void	ft_exit(char **name_option, t_all *all, t_pars **pars)
{
	t_pars *first_node;
	
	first_node = lstfirst(*pars);
	// char				**s;
	int					i;

	// s = ft_split(readline_return, ' ');
	i = 0;
	while (name_option[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit\nexit: too many arguments", 2);
		return ;
	}
	free_all(&all); // free all node + s_env nodes
	free_full_t_pars(&first_node);
	ft_putendl_fd("exit", 2);
	if (name_option[1] && ft_are_nums(name_option[1]) == false)
		printf("exit: %s: numeric argument required\n", name_option[1]);
	// free_split(s);
	exit(EXIT_SUCCESS);
}

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	t_all		all;
// 	t_pars		pars;

// 	copy_env_into_list(&all.env_lst, envp);
// 	all.last_exit_status = EMPTY_EXIT_LIST;
// 	all.readline_line = NULL;
// 	while (1)
// 	{
// 		signals(&all);
// 		all.readline_line = readline("minishell$ ");
// 		if (all.readline_line == NULL)	//checks for ctrl+d
// 		{
// 			printf("exit\r");
// 			free_s_env(&all.env_lst);
// 			if (all.readline_line != NULL)
// 				free(all.readline_line);
// 			return (exit(0), 1);
// 		}
// 		// if (ft_strchr(all.readline_line, '|'))
// 		// 	pipes(ft_split(all.readline_line, '|'), envp);
// 		if (ft_strncmp(all.readline_line, "echo", 4) == 0)
// 			ft_echo(all.readline_line, &all, &pars, 1);	//replace 1 with fd
// 		else if (ft_strncmp(all.readline_line, "cd", 2) == 0)
// 			ft_cd(all.readline_line, all.env_lst);
// 		else if (ft_strncmp(all.readline_line, "pwd", 3) == 0)
// 			ft_pwd(all.env_lst, 1, true);	//replace 1 with fd
// 		else if (ft_strncmp(all.readline_line, "env", 3) == 0)
// 			ft_env(&all, 1);
// 		else if (ft_strncmp(all.readline_line, "export", 6) == 0)
// 			ft_export(&all.env_lst, all.readline_line);
// 		else if (ft_strncmp(all.readline_line, "unset", 5) == 0)
// 			ft_unset(&all.env_lst, all.readline_line);
// 		else if (ft_strncmp(all.readline_line, "exit", 4) == 0)
// 			ft_exit(&all, all.readline_line, 1);
// 		add_history(all.readline_line);
// 		free(all.readline_line);
// 	}
// 	free_s_env(&all.env_lst);
// 	free(all.readline_line);
// 	return 0;
// }
