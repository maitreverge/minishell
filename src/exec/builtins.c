/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:51:37 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/26 13:06:17 by flverge          ###   ########.fr       */
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
int	ft_env(t_all *all)//, int fd
{
	t_env_list *temp;

	temp = all->env_lst;
	// if (fd < 0)
	// {
	// 	free_s_env(&all->env_lst);
	// 	perror("ft_env: fd < 0");
	// 	return (exit(EXIT_FAILURE), 1);
	// }
	while (all->env_lst != NULL)
	{
		printf("%s\n", all->env_lst->original_envp);
		// ft_putstr_fd(all->env_lst->original_envp, fd);
		// ft_putchar_fd('\n', fd);
		all->env_lst = all->env_lst->next;
	}
	all->env_lst = temp;
	return (0);
}

/*Remember to also free all!!!*/
int	ft_exit(t_pars *pars, t_all *all, char *readline_return)//, int fd
{
	t_pars *first_node;
	
	first_node = lstfirst(pars);
	char				**s;
	int					i;

	s = ft_split(readline_return, ' ');
	i = 0;
	while (s[i])
		i++;
	if (i > 2)
	{
		printf("exit: too many arguments\n");
		// ft_putstr_fd("exit: too many arguments\n", fd);
		return (0);
	}
	free_all(&all); // free all node + s_env nodes
	free_full_t_pars(&first_node);
	free_split(s);
	exit(-1);
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
