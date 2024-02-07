/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:51:37 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/07 13:23:20 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(char **t)
{
	int	i;

	i = 0;
	if (t == NULL)
		return ;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

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
		free_tokens(tokens);
		ft_pwd(envp, 1, false);
		return (0);
	}
	else if (tokens != NULL)
	{
		chdir(tokens[1]);
		ft_pwd(envp, 1, false);
	}
	free_tokens(tokens);
	return (0);
}

/*Also changes the env PWD variable to reflect any changes.*/
int	ft_pwd(t_env_list *envp, int fd, bool print)
{
	char		*cwd;
	char		*new_pwd_env;
	t_env_list *temp;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (fd < 0)
		return (free_list(envp), exit(EXIT_FAILURE), 1);
	if (print == true)
	{
		ft_putstr_fd(cwd, fd);
		ft_putchar_fd('\n', fd);	
	}
	new_pwd_env = ft_strjoin("PWD=", cwd);
	temp = envp;
	while (ft_strncmp(envp->env_line, "PWD", 3) != 0)
		envp = envp->next;
	if (envp != NULL)
	{
		free(envp->env_line);
		envp->env_line = new_pwd_env;
	}
	if (cwd != NULL)
		free(cwd);
	envp = temp;
	return (0);
}

/*Displays a list of the environment variables for the
	current terminal session.*/
int	ft_env(t_all *all, int fd)
{
	t_env_list *temp;

	temp = all->env_lst;
	if (fd < 0)
	{
		free_list(all->env_lst);
		perror("ft_env: fd < 0");
		return (exit(EXIT_FAILURE), 1);
	}
	while (all->env_lst != NULL)
	{
		ft_putstr_fd(all->env_lst->env_line, fd);
		ft_putchar_fd('\n', fd);
		all->env_lst = all->env_lst->next;
	}
	all->env_lst = temp;
	return (0);
}

int	ft_exit(t_all *all, char *readline_return, int fd)
{
	char				**s;
	int					i;

	s = ft_split(readline_return, ' ');
	i = 0;
	while (s[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", fd);
		return (0);
	}
	if (readline_return != NULL)
		free(readline_return);
	free_list((all)->env_lst);
	exit((all)->last_exit_status);
}
//a
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_all		all;

	all.env_lst = copy_env_into_list(envp);
	all.last_exit_status = EMPTY_EXIT_LIST;
	all.readline_line = NULL;
	while (1)
	{
		signals(&all);
		all.readline_line = readline("minishell$ ");
		if (all.readline_line == NULL)	//checks for ctrl+d
		{
			printf("exit\r");
			free_list(all.env_lst);
			if (all.readline_line != NULL)
				free(all.readline_line);
			return (exit(0), 1);
		}
		if (ft_strchr(all.readline_line, '|'))
			pipes(ft_split(all.readline_line, '|'), envp);
		if (ft_strncmp(all.readline_line, "echo", 4) == 0)
			ft_echo(all.readline_line, &all, 1);	//replace 1 with fd
		else if (ft_strncmp(all.readline_line, "cd", 2) == 0)
			ft_cd(all.readline_line, all.env_lst);
		else if (ft_strncmp(all.readline_line, "pwd", 3) == 0)
			ft_pwd(all.env_lst, 1, true);	//replace 1 with fd
		else if (ft_strncmp(all.readline_line, "env", 3) == 0)
			ft_env(&all, 1);
		else if (ft_strncmp(all.readline_line, "export", 6) == 0)
			ft_export(&all.env_lst, all.readline_line);
		else if (ft_strncmp(all.readline_line, "unset", 5) == 0)
			ft_unset(&all.env_lst, all.readline_line);
		else if (ft_strncmp(all.readline_line, "exit", 4) == 0)
			ft_exit(&all, all.readline_line, 1);
		add_history(all.readline_line);
		free(all.readline_line);
	}
	free_list(all.env_lst);
	free(all.readline_line);
	return 0;
}
