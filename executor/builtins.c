/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:16:22 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:16:29 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_list **var_list)
{
	t_list	*tmp_list;
	t_var	*tmp_var;

	(void)args;
	tmp_list = ft_find_var(var_list, "PWD");
	tmp_var = (t_var *)tmp_list->content;
	printf("%s\n", tmp_var->value);
	return (1);
}

int	ft_unset(char **args, t_list **var_list)
{
	t_list	*tmp_list;
	int		index;

	index = 1;
	while (args[index] != NULL)
	{
		tmp_list = ft_find_var(var_list, args[index]);
		if (tmp_list == NULL)
			ft_check_var(args[index], "unset");
		else
			ft_del_elem(tmp_list, var_list, ft_del_var);
		index++;
	}
	return (0);
}

int	ft_env(char **args, t_list **var_list)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_ptr;

	tmp = *var_list;
	(void)args;
	if (!ft_find_var(var_list, "PATH"))
	{
		printf("minishell: env: No such file or directory\n");
		return (1);
	}
	while (tmp)
	{
		next = tmp->next;
		tmp_ptr = (t_var *)tmp->content;
		if (tmp_ptr->is_exported == 1)
		{
			printf("%s=", tmp_ptr->name);
			if (tmp_ptr->value)
				printf("%s", tmp_ptr->value);
			printf("\n");
		}
		tmp = next;
	}
	return (1);
}

int	ft_exit(char **args, t_list **var_list)
{
	int	lvl;

	(void)args;
	printf("exit\n");
	lvl = ft_change_lvl(var_list, 0);
	if (lvl != 2)
		return (1);
	if (lvl == 2)
	{
		ft_clear_vars(var_list); //TODO: здесь очистить все
		exit(EXIT_SUCCESS);
	}
	return (1);
}
