/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tlist	*tlistnew(char *cmd, int type, char *args)
{
	t_tlist	*tmp;

	if (!(tmp = (t_tlist *)malloc(sizeof(t_tlist))))
			return (NULL);
	tmp->type = type;
//	tmp->token = NULL;
//	tmp->infile = NULL;
//	tmp->outfile = NULL;
//	tmp->envkey = NULL;
	tmp->cmd = ft_strdup(cmd);
	tmp->args = ft_strdup(args);
	tmp->next = NULL;
	return (tmp);
}

void	tlistadd_back(t_tlist **head_token, t_tlist *newtoken)
{
	t_tlist	*final;

	if(!head_token && !newtoken)
		return ;
	if (!(*head_token))
	{
		*head_token = newtoken;
		return ;
	}
	final = *head_token;
	while (final->next != NULL)
		final = final->next;
	final->next = newtoken;
}

void	tlist_del(t_tlist *head)
{
	t_tlist	*tmp;

	tmp = head;
	head = head->next;
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->args)
		free(tmp->args);
	free(tmp);
}

void	tlist_clear(t_tlist **head)
{
	t_tlist	*tmp;
	t_tlist	*nextnode;

	tmp = *head;
	while (tmp != NULL)
	{
		nextnode = tmp->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			free(tmp->args);
		free(tmp);
		tmp = nextnode;
	}
	*head = NULL;
}

void	init_lexer(t_tlist *token)
{
//	token->token = NULL;
	token->type = 0;
//	token->infile = NULL;
//	token->outfile = NULL;
	token->cmd = NULL;
	token->args = NULL;
//	token->envkey = NULL;
	token->next = NULL;
}