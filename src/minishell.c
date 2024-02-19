/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:40 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/19 13:21:50 by glambrig         ###   ########.fr       */
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
		ft_unset(&all->env_lst, all->readline_line);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "exit"))
		ft_exit(pars, all, all->readline_line);
}

void	exec_external_func(t_pars *lst)
{
	pid_t	ch_pid;

	ch_pid = fork();
	if (ch_pid == 0)
	{
		if (execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL) < 0)
		{
			perror("execve");
			// free_t_pars(&lst);
			return ;
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
	t_env_list	*new_list;

	// allocate two nodes for t_all and t_env_list
	new_all = malloc(sizeof(t_all));
	if (!new_all)
		return (NULL);
	new_list = malloc(sizeof(t_env_list));
	if (!new_list)
		return (NULL);

	// connecting node t_all to sub_node t_env_list
	new_all->env_lst = new_list;
	
	// Init sub_node to null
	new_all->env_lst = NULL;
	
	// init readline buffer to null
	new_all->readline_line = NULL;

	// init env_list nodes from envp
	copy_env_into_list(&new_all->env_lst, envp);
	

	// ! IMPORTANT :
	// both t_all and t_env_list need to be freed when an exit signal occurs

	return (new_all);
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
	signals(pars);
	while (1)
	{
		all->readline_line = readline("minishell$ ");
		if (all->readline_line == NULL)	//checks for ctrl+d
		{
			//there are certainly things here that i forgot to free
			printf("exit\r");
			free_s_env(&all->env_lst);
			free_firstnode_pars(&pars);
			if (all->readline_line != NULL)
				free(all->readline_line);
			return (exit(0), 1);
		}
		turbo_parser(all->readline_line, &pars, &all->env_lst, &utils);
		if (pars->MasterKill == true)
		{
			free_firstnode_pars(&pars);
			break ;
		}
		int	fds;
		fds = -1;
		while (check_next_operator(pars->next) != 0)
		{
			if (check_next_operator(pars->next) == 1)
			{
				fds = pipes(&pars->next, all, fds);
				continue ;
			}
			else if (check_next_operator(pars->next) == 2)
				redirect_input(&pars->next);
			else if (check_next_operator(pars->next) == 3)
				redirect_input_delimitor(&pars->next);
			else if (check_next_operator(pars->next) == 4)
				redirect_output(&pars->next, all, fds);
		}
		if (fds != -1)
			close(fds);
		if (check_next_operator(pars->next) == 0) //there are no operators
		{
			if (pars && pars->next && pars->next->cmd->isBuiltin == true)
				exec_builtin(pars->next, all);
			else if (pars && pars->next)
				exec_external_func(pars->next);
		}
		if (pars && pars->next)
			add_history(all->readline_line);
		free(all->readline_line);
		free_t_pars(&pars);//not sure, but seems right
		// ! need to free cleaned prompt and splitted
	}
}
