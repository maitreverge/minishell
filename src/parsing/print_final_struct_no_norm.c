#include "../../minishell.h"

void	print_final_struct(t_pars **pars)
{
	t_pars *cur = *pars;

	printf("\nFIRST NODE OF STRUCT :\n");
	printf((*pars)->MasterKill ? "MASTERKILL SWITCH ON ✅\n" : "MASTERKILL SWITCH OFF ❌\n");

	printf("Last exit status = %i\n", (*pars)->last_exit_status);
	printf("\n------------------------\n");
	// cur = cur->next;
	while (cur)
	{
		if (cur->isCommand)
		{
			printf("CURRENT NODE IS A COMMAND\n\n");

			printf("\033[31m%s\033[0m", cur->cmd->isBuiltin ? "Command is a Builtin\n" : "Command is a regular command\n");
						
			printf("\033[31mCommand Name = %s\n\033[0m", cur->cmd->command_name);			
			printf("\033[31mCommand Path = %s\n\033[0m", cur->cmd->command_path);			
			for (int i = 0; cur->cmd->name_options_args[i]; i++)
				printf("\033[31mCommand name_options_args #%i = %s\n\033[0m", i + 1, cur->cmd->name_options_args[i]);			
		}
		else if (cur->isHereDoc)
		{
			printf("CURRENT NODE IS A DELIM STRING\n\n");
			printf("\033[33mDELIM value = %s\n\033[0m", cur->here_doc);
		}
		else if (cur->isFile)
		{
			printf("CURRENT NODE IS A FILE\n\n");

			printf("\033[34mFile Name = %s\n\033[0m", cur->fl->file_name);
			printf("\033[34m%s\033[0m", cur->fl->file_exist ? "File Does exist\n" : "FILE DOESN'T EXISTS\n");
			printf("\033[34m%s\033[0m", cur->fl->auth_r ? "READ AUTHORISATION ✅\n" : "READ AUTHORISATION ❌\n");
			printf("\033[34m%s\033[0m", cur->fl->auth_w ? "WRITE AUTHORISATION ✅\n" : "WRITE AUTHORISATION ❌\n");
			printf("\033[34m%s\033[0m", cur->fl->auth_x ? "EXECUTION AUTHORISATION ✅\n" : "EXECUTION AUTHORISATION ❌\n");

		}
		else if (cur->isOperator)
		{
			printf("CURRENT NODE IS AN OPERATOR\n\n");
			if (cur->operator->pipe)
				printf("Operator = | \n");
			else if (cur->operator->redir_in)
				printf("Operator = < \n");
			else if (cur->operator->redir_out)
				printf("Operator = > \n");
			else if (cur->operator->redir_out_app)
				printf("Operator = >> \n");
			else if (cur->operator->redir_in_delim)
				printf("Operator = << \n");
		}
		printf("\n------------------------\n");
		cur = cur->next;
	}
}

void	print_env(t_env_list **envp, char *target, char *message)
{
	t_env_list *current;

	current = *envp;

	printf("%s\n", message);
	while (current)
	{
		if (!ft_strcmp(current->key, target))
		{
			printf("Original envp = %s\n", current->original_envp);
			printf("Key = %s\n", current->key);
			printf("Value = %s\n", current->value);
			printf("\n");
		}
		current = current->next;
	}
}
