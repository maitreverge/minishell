#include "../../minishell.h"

t_env_list	*env_lstnew(char *s_key, char *s_value)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->key = s_key;
	new_node->value = s_value;
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
	// new->prev = tail;
}

void	copy_env_into_list(t_env_list **env, char **envp)
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
			current = env_lstnew(s_key, s_value);
		else
			env_lstadd_back(current, env_lstnew(s_key, s_value));
		i++;
	}
	free(splitted_value);
}

int main(char **envp)
{
	t_env_list *env;
	t_env_list *current;

	env = NULL;


	copy_env_into_list(&env, envp);
	current = env;

	for(int i = 0; current; i++)
	{
		printf("Current node key = %s\n", current->key);
		printf("Current node value = %s\n", current->value);
		printf("Current node value = %s\n", current->value);
		current = current->next;

	}



}