/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:51:37 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/24 17:56:27 by glambrig         ###   ########.fr       */
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

/*Make sure to pass the ENTIRE line (got by readline()),
	otherwise the function might not work properly*/
void	ft_echo(char *s)
{
	char	**tokens;
	int		last;
	int		i;

	tokens = NULL;
	if (ft_strchr(s, ' ') != NULL)
		tokens = ft_split(s, ' ');
	/*There are no spaces, or there's only one word*/
	if ((tokens != NULL && tokens[1] == NULL) || tokens == NULL)
	{
		printf("\n");
		free_tokens(tokens);
		return ;
	}
	last = 0;
	while (tokens[last])
		last++;
	if (ft_strncmp(tokens[1], "-n", 3) == 0)
	{
		i = 2;
		while (tokens[i])
		{
			if (i == last - 1)
				printf("%s", tokens[i++]);
			else
				printf("%s ", tokens[i++]);

		}
		free_tokens(tokens);
		return ;
	}
	else
	{
		i = 1;
		while (tokens[i])
			printf("%s ", tokens[i++]);
		printf("\n");
	}
	free_tokens(tokens);
}
/* As an extension to the POSIX.1-2001 standard, glibc's getcwd()
    allocates the buffer dynamically using malloc(3) if buf is NULL.
    In this case, the allocated buffer has the length size unless
  	size is zero, when buf is allocated as big as necessary.
*/
// static short check_rel_or_abs_path(void)//char *path
// {
// 	char	*cwd;

// 	//cwd = ft_calloc(1000, sizeof(char));
// 	cwd = NULL;
// 	cwd = getcwd(cwd, 0);
// 	if (!cwd)
// 	{
// 		free(cwd);
// 		perror("check_rel_or_abs_path: ");
// 		exit(-1);
// 	}
// 	if (cwd[0] == '~' || cwd[0] == '/')
// 	{
// 		free(cwd);
// 		return (1);
// 	}
// 	else
// 	{
// 		free(cwd);
// 		return (2);
// 	}
// }

/*cd MUST be called with the full line received from readline(),
	otherwise it won't work.*/
void	ft_cd(char *s)
{
	char 	**tokens;
	char	*homepath;

	tokens = NULL;
	if (ft_strchr(s, ' ') != NULL)
		tokens = ft_split(s, ' ');
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

void	ft_env(void)
{
	if (getenv("SHELL") != NULL)
		printf("SHELL=%s\n", getenv("SHELL"));
	if (getenv("NAME") != NULL)
		printf("NAME=%s\n", getenv("NAME"));
	if (getenv("PWD") != NULL)
		printf("PWD=%s\n", getenv("PWD"));
	if (getenv("LOGNAME") != NULL)
		printf("LOGNAME=%s\n", getenv("LOGNAME"));
	if (getenv("HOME") != NULL)
		printf("HOME=%s\n", getenv("HOME"));
	if (getenv("LANG") != NULL)
		printf("LANG=%s\n", getenv("LANG"));
	if (getenv("USER") != NULL)
		printf("USER=%s\n", getenv("USER"));
	if (getenv("PATH") != NULL)
		printf("PATH=%s\n", getenv("PATH"));
}

//test main
int main(int ac, char **av)//, char **env
{
	(void)ac;
	(void)av;
	char *line;

	int i = 0;
	while (i < 5)
	{
		line = readline("minishell$ ");
		if (ft_strncmp(line, "echo", 4) == 0)
			ft_echo(line);
		else if (ft_strncmp(line, "cd", 2) == 0)
			ft_cd(line);
		else if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(line, "env", 3) == 0)
			ft_env();
		else if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), exit(0), 0);
		free(line);
		i++;
	}
	return 0;
}
