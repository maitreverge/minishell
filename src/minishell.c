/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:40 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/02 10:14:02 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	If pid == 0, we free the pars structure.
*/
void	exec_builtin(t_pars *pars, t_all *all, int pid)
{
	if (!ft_strcmp(pars->cmd->name_options_args[0], "echo"))
		ft_echo(pars->cmd->name_options_args, pars);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "cd"))
		ft_cd(&pars, &all->env_lst);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "pwd"))
		ft_pwd(pars->cmd->name_options_args, &pars);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "env"))
		ft_env(pars->cmd->name_options_args, all, &pars);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "export"))
		ft_export(&all->env_lst, pars->cmd->name_options_args, all, &pars);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "unset"))
		ft_unset(&all->env_lst, pars->cmd->name_options_args, &pars);
	else if (!ft_strcmp(pars->cmd->name_options_args[0], "exit"))
		ft_exit(pars->cmd->name_options_args, all, &pars);
	if (pid == 0)
	{
		free_t_pars(&pars);
		free_all(&all);
	}
	return ;
}

int	g_pid;

static void	asdf(int sig)
{
	(void)sig;
	kill(g_pid, SIGINT);
}

int	exec_external_func(t_pars *lst, t_all *all)
{
	pid_t	ch_pid;
	t_pars	*frst;

	frst = lstfirst(lst);
	ch_pid = fork();
	if (ch_pid > 0)
	{
		g_pid = ch_pid;
		signal(SIGINT, &asdf);
	}
	if (ch_pid == 0)
	{
		if (!lst->cmd->command_path)
			return (printf("Command not found\n"),
				lstfirst(lst)->last_exit_status = 127, exit(127), 1);
		else if (execve(lst->cmd->command_path, lst->cmd->name_options_args,
				all->copy_envp) < 0)
			return (perror("execve"), exit(EXIT_FAILURE), 1);
	}
	else if (ch_pid < 0)
		return (perror("fork"), lstfirst(lst)->last_exit_status = errno, 1);
	wait(&frst->last_exit_status);
	frst->last_exit_status = WEXITSTATUS(frst->last_exit_status);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_all		*all;
	t_utils		*utils;
	t_pars		*pars;
	int			k;

	(void)ac;
	(void)av;
	main_init(&all, &pars, &utils, envp);
	while (1)
	{
		signals(pars);
		reset_t_pars(&pars);
		refresh_envp(&all);
		all->readline_line = readline("minishell$ ");
		check_ctrl_d(all, pars);
		turbo_parser(all->readline_line, &pars, &all->env_lst, &utils);
		if (!pars->masterkill)
			masterkill_false(pars, all, &k);
		if (pars && pars->next)
			add_history(all->readline_line);
		free(all->readline_line);
		free_t_pars(&pars);
	}
}
