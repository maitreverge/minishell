#include "../../minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:21:44 by flverge           #+#    #+#             */
/*   Updated: 2023/10/06 16:10:26 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sub_check(char const *s, char c, size_t *i, size_t *start)
{
	while (s[*i] == c)
		(*i)++;
	if (s[*i] != c && s[*i])
	{
		*start = *i;
		while (s[*i] != c && s[*i])
			(*i)++;
	}
}

static void	allocation(char **buffer, char const *s, char c, size_t len_s)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	if (!s)
		return ;
	while (s[i])
	{
		sub_check(s, c, &i, &start);
		if (j < len_s)
		{
			buffer[j] = ft_calloc(sizeof(char), (i - start + 1));
			if (!buffer[j])
				return ;
			ft_strncpy(buffer[j], &s[start], i - start);
			j++;
		}
		while (s[i] == c && s[i])
			i++;
	}
}

static size_t	ft_countwords(char const *str, char c)
{
	size_t	result;
	int		i;

	result = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			result++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**buffer;
	size_t	len_s;

	len_s = ft_countwords(s, c);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	allocation(buffer, s, c, len_s);
	return (buffer);
}

t_env_list	*env_lstnew(char *s_key, char *s_value, char *envp)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->original_envp = envp;
	new_node->key = s_key;
	new_node->value = s_value;
	new_node->next = NULL; // add 
	return (new_node);
}

t_env_list	*env_lstlast(t_env_list *lst)
{
	t_env_list	*current;

	current = lst;
	if (!current)
		return (0);
	if (!current->next)
		return (current);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

void	env_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*tail;

	tail = env_lstlast(*lst);
	tail->next = new;
}

void	my_copy_env_into_list(t_env_list **env, char **envp)
{
	t_env_list	*current;
	char		*s_key;
	char		*s_value;
	char		**splitted_value;
	int			i;

	current = *env;
	i = 0;
	while (envp[i])
	{
		splitted_value = ft_split(envp[i], '=');
		s_key = splitted_value[0];
		s_value = splitted_value[1];
		if (!current)
		{
			current = env_lstnew(s_key, s_value, envp[i]);
			*env = current;
		}
		else
		{
			env_lstadd_back(&current, env_lstnew(s_key, s_value, envp[i]));
			// current->next->original_envp = envp[i];
		}
		i++;
	}
	// free(splitted_value);
}

int main(int ac, char **av, char **envp)
{
	t_env_list *env;
	// t_env_list *current;

	env = NULL;
	my_copy_env_into_list(&env, envp);
	// current = env;

	do
	{
		printf("Current node Original Key = %s\n", env->original_envp);
		printf("Current node key = %s\n", env->key);
		printf("Current node value = %s\n", env->value);
		env = env->next;

	} while (env);

}