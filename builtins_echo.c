/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/28 16:23:24 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_exit_status(t_exit_status_list *lst)
{
	//return (ft_lstlast(lst));
	(void)lst;//test
	return (0);//test
}

/*
	Determines which environment variable the given string/key corresponds to,
	and returns its value.

	Return value is allocated with malloc and MUST be freed after use.
*/
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
			// !
		// else if (s[0] == '$' && s[1] == '$')
		// 	return (1);
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

/*
	Make sure to pass the ENTIRE line (got by readline()),
	otherwise the function might not work properly.
*/
/*	TODO:
		-echo $? prints exit status of last command
*/
int	ft_echo(char *s, char **envp, int fd)
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
		//printf("\n");
		ft_putstr_fd("\n", fd);
		free_tokens(tokens);
		return (0);
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
				// printf("%s ", result);
				ft_putstr_fd(result, fd);
				if (i != last)
					ft_putchar_fd(' ', fd);
				free(trimmed);
				free(result);
				continue ;
			}
			else if (trimmed[0] == '$' && trimmed[1] == '?')
			{
				free(trimmed);
				//trimmed = get_last_exit_status(s_exit_status_list);
				trimmed[0] = '0';///test
				trimmed[1] = '\0';///test
			}
			else if (check_if_env_var(trimmed, envp) == 2)
				continue ;
			if (i == last - 1)
				ft_putstr_fd(trimmed, fd);
				//printf("%s", trimmed);
			else
			{
				// printf("%s ", trimmed);
				ft_putstr_fd(trimmed, fd);
				ft_putchar_fd(' ', fd);
			}
			free(trimmed);
		}
		free_tokens(tokens);
		return (0);
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
				// printf("%s ", result);
				ft_putstr_fd(result, fd);
				ft_putchar_fd(' ', fd);
				free(trimmed);
				free(result);
				continue ;
			}
			else if (trimmed[0] == '$' && trimmed[1] == '?')
			{
				//trimmed = get_last_exit_status(s_exit_status_list);
				trimmed[0] = '0';///test
				trimmed[1] = '\0';///test
			}
			/*Has a $ sign, but isn't in the list of env vars.*/
			else if (check_if_env_var(trimmed, envp) == 2)
				continue ;
			//printf("%s ", trimmed);
			char *temp;
			temp = ft_strtrim(trimmed, "\'");
			ft_putstr_fd(temp, fd);
			free(temp);
			ft_putchar_fd(' ', fd);
			free(trimmed);
		}
		printf("\n");
	}
	free_tokens(tokens);
	return (0);
}
