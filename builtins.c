/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:51:37 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/25 15:50:06 by glambrig         ###   ########.fr       */
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

/*cd MUST be called with the full line received from readline(),
	otherwise it won't work.*/
void	ft_cd(char *s)
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
		return ;
	}
	else if (tokens != NULL)
		chdir(tokens[1]);
	free_tokens(tokens);
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

//test main
int main(int ac, char **av, char **envp)//, char **env
{
	(void)ac;
	(void)av;
	char *line;

	int i = 0;
	while (i < 5)
	{
		line = readline("minishell$ ");
		if (ft_strncmp(line, "echo", 4) == 0)
			ft_echo(line, envp);
		else if (ft_strncmp(line, "cd", 2) == 0)
			ft_cd(line);
		else if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(line, "env", 3) == 0)
			ft_env(envp);
		else if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), exit(0), 0);
		free(line);
		i++;
	}
	return 0;
}
