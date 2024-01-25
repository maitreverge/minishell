/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/25 15:26:51 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return value is allocated with malloc and MUST be freed after use.*/
char	*compare_env_var_with_envp(char *str, char **envp)
{
	int		i;
	char	*s;
	char	**env_split;
	char	*res;

	i = 0;
	s = ft_strtrim(str, "$");
	while (envp[i])
	{
		if (strncmp(s, envp[i], ft_strlen(s)) == 0)
		{
			env_split = ft_split(envp[i], '=');
			res = ft_strdup(env_split[1]);
			free_tokens(env_split);
			free(s);
			return (res);
		}
		i++;
	}
	free(s);
	return (NULL);
}

/*Checks if the given string 's' is an environment variable*/
int	check_if_env_var(char *s, char **envp)
{
	char	*free_v;

	if (ft_strchr(s, '$') != NULL)
	{
		if (s[0] != '$')
			return (0);
		else
		{
			free_v = compare_env_var_with_envp(s, envp);
			if (free_v != NULL)
			{
				free(free_v);
				return (1);
			}
			else
			{
				free(free_v);
				return (2);
			}
		}
	}
	return (0);
}

/*Make sure to pass the ENTIRE line (got by readline()),
	otherwise the function might not work properly.*/
/*TODO:
	echo $$ prints shell's PID
	echo $? prints exit status of last command
*/
void	ft_echo(char *s, char **envp)
{
	char	**tokens;
	char 	*trimmed;
	char	*result;
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
			if (check_if_env_var(trimmed, envp) == 1)
			{
				result = compare_env_var_with_envp(trimmed, envp);
				printf("%s ", result);
				free(trimmed);
				free(result);
				continue ;
			}
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
			if (check_if_env_var(trimmed, envp) == 1)
			{
				result = compare_env_var_with_envp(trimmed, envp);
				printf("%s ", result);
				free(trimmed);
				free(result);
				continue ;
			}
			printf("%s ", trimmed);
			free(trimmed);
		}
		printf("\n");
	}
	free_tokens(tokens);
}
