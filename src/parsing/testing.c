#include "../../minishell.h"

t_env_list	*env_lstnew(char *s_key, char *s_value, char *envp)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->key = s_key;
	new_node->value = s_value;
	new_node->original_envp = envp;
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
	// new->prev = tail;
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
			// current->original_envp = envp[i];
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