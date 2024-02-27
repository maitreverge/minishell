/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:40 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/27 10:37:56 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Returns:
	1 for pipe
	2 for redir in
	3 for heredoc
	4 for redir out or redir out append
	0 for no operators
*/
int	check_next_operator(t_pars *lst)
{
	t_pars	*temp;

	temp = lst;
	while (lst)
	{
		if (lst->isOperator == true)
		{
			if (lst->operator->pipe == true)
				return (1);
			if (lst->operator->redir_in == true)
				return (2);
			if (lst->operator->redir_in_delim == true)
				return (3);
			if (lst->operator->redir_out == true || lst->operator->redir_out_app == true)
				return (4);
		}
		lst = lst->next;
	}
	lst = temp;
	return (0);
}

void	exec_builtin(t_pars *pars, t_all *all)
{
	if (!ft_strcmp(pars->cmd->name_options_args[0], "echo"))
		ft_echo(pars);	//all->readline_line, all, 
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "cd"))
		ft_cd(all->readline_line, all->env_lst);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "pwd"))
		ft_pwd(&all->env_lst, true);	//replace 1 with fd
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "env"))
		ft_env(all);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "export"))
		ft_export(&all->env_lst, all->readline_line);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "unset"))
		ft_unset(&all->env_lst, all->readline_line, &pars);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "exit"))
		ft_exit(pars, all, all->readline_line);
	return ;
}

void	exec_external_func(t_pars *lst, t_all *all)
{
	t_pars *first_node;

	first_node = lstfirst(lst);
	pid_t	ch_pid;

	ch_pid = fork();
	if (ch_pid == 0)
	{
		if (!lst->cmd->command_path)
		{
			printf("Command not found\n");
			first_node->last_exit_status = 127;
			// return ;
			exit (1);
		}
		else if (execve(lst->cmd->command_path, lst->cmd->name_options_args, all->copy_envp) < 0)
		{
			perror("execve");
			// free_t_pars(&lst);
			// return ;
			exit (1);
		}
	}
	else if (ch_pid < 0)
	{
		perror("fork");
		// free_t_pars(&lst);
		return ;
	}
	wait(NULL);
}

t_all	*init_t_all_struct(char **envp)
{
	t_all		*new_all;

	// allocate two nodes for t_all and t_env_list
	new_all = malloc(sizeof(t_all));
	if (!new_all)
		return (NULL);
	
	// Init sub_node to null
	new_all->env_lst = NULL;
	
	// init readline buffer to null
	new_all->readline_line = NULL;

	// init env_list nodes from envp
	copy_env_into_list(&new_all->env_lst, envp);

	new_all->copy_envp = NULL; // ! NEW ALLOCATED STUFF
	
	return (new_all);
}

void	reset_t_pars(t_pars **pars)
{
	(*pars)->MasterKill = false;
	(*pars)->isRedirIn = false; // reseting this one when search_redir_in turn it on
	(*pars)->error_message = 0;	
}

char **convert_env_list_to_array(t_env_list **list)
{
	t_env_list	*current;
	char		**result;
	int			size;
	int			j; // buffer index

	current = *list;
	size = 0;
	j = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	current = *list;
	result = ft_calloc(size + 1, sizeof(char *));
	while (current)
	{
		result[j] = ft_strdup(current->original_envp);
		current = current->next;
		j++;
	}
	return (result);
}

void	refresh_envp(t_all **all)
{
	t_all *current;

	current = *all;
	
	free_split(current->copy_envp);
	current->copy_envp = convert_env_list_to_array(&current->env_lst);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_all		*all;
	t_utils		*utils;
	t_pars		*pars;
	
	utils = NULL;
	pars = NULL;
	
	// Nodes all and node t_env_list are create and init here
	all = init_t_all_struct(envp);
	pars = init_1st_node_pars();
	signals(pars); // calling 
	while (1)
	{
		reset_t_pars(&pars);
		refresh_envp(&all);
		all->readline_line = readline("minishell$ ");
		if (all->readline_line == NULL)	//checks for ctrl+d
		{
			//there are certainly things here that i forgot to free
			printf("exit\r"); // ! is this really usefull, knowing that the program will instantly quit ?
			free_all(&all); // free all node + s_env nodes
			// free_s_env(&all->env_lst);
			// free_t_pars(&pars);
			free_firstnode_pars(&pars);
			// if (all->readline_line != NULL)
			// 	free(all->readline_line);
			return (exit(0), 1);
		}
		turbo_parser(all->readline_line, &pars, &all->env_lst, &utils);
		// ! In this form, masterkill actually exit minishell, instead of giving back the prompt
		// ! I need to skip all the execution part, trow a error message, then stay in the loop
		// if (pars->MasterKill == true)
		// {
		// 	free_firstnode_pars(&pars);
		// 	break ; 
		// }
		if (!pars->MasterKill) // if master_kill if false
		{
			int	fds;
			fds = -1;
			int k = 0;
			if (check_next_operator(pars->next) == 1)
			{
				fds = pipes(&pars->next, all, fds);
				k = 123;
			}
			else if (check_next_operator(pars->next) == 2)
			{
				redirect_input(&pars->next, all);
				k = 123;
			}
			else if (check_next_operator(pars->next) == 3)
			{
				redirect_input_delimitor(&pars->next, all);
				k = 123;
			}
			else if (check_next_operator(pars->next) == 4)
			{
				redirect_output(&pars->next, all, fds);
				k = 123;
			}
			if (fds != -1)
				close(fds);
			if (check_next_operator(pars->next) == 0 && (k != 123)) //there are no operators
			{
				if (pars && pars->next && pars->next->cmd->isBuiltin == true)
					exec_builtin(pars->next, all);
				else if (pars && pars->next)
					exec_external_func(pars->next, all);
			}
		}
		// those next 4 lines will execute regardless if master Kill is on 
		if (pars && pars->next)
			add_history(all->readline_line);
		free(all->readline_line);
		free_t_pars(&pars);//not sure, but seems right
	} 
}
