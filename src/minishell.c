/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:40 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/13 15:51:24 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//george main
// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	t_all		all;
// 	t_pars		pars;

// 	copy_env_into_list(&all.env_lst, envp);
// 	all.last_exit_status = EMPTY_EXIT_LIST;
// 	all.readline_line = NULL;
// 	while (1)
// 	{
// 		signals(&all);
// 		all.readline_line = readline("minishell$ ");
// 		if (all.readline_line == NULL)	//checks for ctrl+d
// 		{
// 			printf("exit\r");
// 			free_s_env(&all.env_lst);
// 			if (all.readline_line != NULL)
// 				free(all.readline_line);
// 			return (exit(0), 1);
// 		}
// 		// if (ft_strchr(all.readline_line, '|'))
// 		// 	pipes(ft_split(all.readline_line, '|'), envp);
// 		if (ft_strncmp(all.readline_line, "echo", 4) == 0)
// 			ft_echo(all.readline_line, &all, &pars, 1);	//replace 1 with fd
// 		else if (ft_strncmp(all.readline_line, "cd", 2) == 0)
// 			ft_cd(all.readline_line, all.env_lst);
// 		else if (ft_strncmp(all.readline_line, "pwd", 3) == 0)
// 			ft_pwd(all.env_lst, 1, true);	//replace 1 with fd
// 		else if (ft_strncmp(all.readline_line, "env", 3) == 0)
// 			ft_env(&all, 1);
// 		else if (ft_strncmp(all.readline_line, "export", 6) == 0)
// 			ft_export(&all.env_lst, all.readline_line);
// 		else if (ft_strncmp(all.readline_line, "unset", 5) == 0)
// 			ft_unset(&all.env_lst, all.readline_line);
// 		else if (ft_strncmp(all.readline_line, "exit", 4) == 0)
// 			ft_exit(&all, all.readline_line, 1);
// 		add_history(all.readline_line);
// 		free(all.readline_line);
// 	}
// 	free_s_env(&all.env_lst);
// 	free(all.readline_line);
// 	return 0;
// }

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
	if (ft_strncmp(pars->cmd->command_name, "echo", 4) == 0)
		ft_echo(all->readline_line, &all, &pars);	//replace 1 with fd
	else if (ft_strncmp(pars->cmd->command_name, "cd", 2) == 0)
		ft_cd(all->readline_line, all->env_lst);
	else if (ft_strncmp(pars->cmd->command_name, "pwd", 3) == 0)
		ft_pwd(all->env_lst, true);	//replace 1 with fd
	else if (ft_strncmp(pars->cmd->command_name, "env", 3) == 0)
		ft_env(&all);
	else if (ft_strncmp(pars->cmd->command_name, "export", 6) == 0)
		ft_export(all->env_lst, all->readline_line);
	else if (ft_strncmp(pars->cmd->command_name, "unset", 5) == 0)
		ft_unset(all->env_lst, all->readline_line);
	else if (ft_strncmp(pars->cmd->command_name, "exit", 4) == 0)
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
			free_t_pars(&lst);
			return ;
		}
	}
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(&lst);
		return ;
	}
	wait(NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_all		all;
	t_utils		*utils;
	t_pars		*pars;

	utils = NULL;
	pars = NULL;

	copy_env_into_list(&all.env_lst, envp);
	all.readline_line = NULL;
	while (1)
	{
		signals(&all);
		if (!pars)
			pars = init_1st_node_pars();
		all.readline_line = readline("minishell$ ");
		if (all.readline_line == NULL)	//checks for ctrl+d
		{
			printf("exit\r");
			free_s_env(&all.env_lst);
			free_firstnode_pars(&pars);
			if (all.readline_line != NULL)
				free(all.readline_line);
			return (exit(0), 1);
		}
		turbo_parser(all.readline_line, &pars, &all.env_lst, &utils);
		if (pars->MasterKill == true)
		{
			//probably free some stuff
			break ;
		}
		if (check_next_operator(pars) == 1)
			pipes(pars, -1);
		else if (check_next_operator(pars) == 2)
			redirect_input(pars);
		else if (check_next_operator(pars) == 3)
			redirect_input_delimitor(pars);
		else if (check_next_operator(pars) == 4)
			redirect_output(pars, &all, -1);
		else //there are no operators
		{
			if (pars->cmd->isBuiltin == true)
				exec_builtin(pars, &all);
			else
				exec_external_func(pars);
		}
		add_history(all.readline_line);
		free(all.readline_line);
		//probably free the list
	}
}
