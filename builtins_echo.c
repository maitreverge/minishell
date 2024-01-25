/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/25 14:02:31 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compare_env_var_with_envp(char *s, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(s, envp[i], ft_strlen(envp[i])) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	check_if_env_var(char *s, char **envp)
{
	if (ft_strchr(s, '$') == 0)
	{
		if (s[0] != '$')
			return (0);
		else
		{
			if (compare_env_var_with_envp(s, envp) != NULL)
				return (1);
			else
				return (2);
		}
	}
	return (0);
}

/*Make sure to pass the ENTIRE line (got by readline()),
	otherwise the function might not work properly.*/
/*TODO:
	handle environment variables passed as input, e.g. "echo $USER"
	echo $$ prints shell's PID
	echo $? prints exit status of last command
	echo "hello" "this is a test" "aaa" prints without the quotes
*/
void	ft_echo(char *s, char **envp)
{
	(void)envp;
	char	**tokens;
	char *trimmed;
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
			trimmed = ft_strtrim(tokens[i++], "\"");
			if (i == last - 1)
				printf("%s", trimmed);
			else
				printf("%s ", trimmed);
			free(trimmed);
		}
		free_tokens(tokens);
		return ;
	}
	else
	{
		i = 1;
		while (tokens[i])
		{
			trimmed = ft_strtrim(tokens[i++], "\"");
			printf("%s ", trimmed);
			free(trimmed);
		}
		printf("\n");
	}
	free_tokens(tokens);
}
