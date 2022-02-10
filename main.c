/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_all(t_tlist **tokens)
{
//	printf("check\n");
	if (tokens)
		tlist_clear(tokens);
//	if (ast)
//		clear_ast(ast);
//	ast = NULL;
}

void	print_tokens(t_tlist *tokens)
{
	t_tlist	*current_node;
	int		i;
	int		j;

	i = 0;
	current_node = tokens;
	while (current_node != NULL)
	{
		printf("[");
		j = -1;
		while (current_node->cmd[++j])
			printf("%s ", current_node->cmd[j]);
		printf("]->");
		current_node = current_node->next;
		i++;
	}
	printf("\nnum of nodes = %d\n", i);
}

int	main(void)
{
	char	*prompt;
	t_tlist	*tokens;
	t_btree	*ast;
	int		*fd;
	t_list **var_list;
	extern char **environ;

	tokens = NULL;
	ast = NULL;
	fd = NULL;
	while (*environ != NULL)
	{
		ft_save_var(&var_list, *environ, 1);
		environ++;
	}
	while (1)
	{
		prompt = readline("minishell > ");
		printf("prompt: |%s|\n", prompt);
		if (prompt)
			add_history(prompt);
		if (!(prompt = preparse(prompt)))
			printf("Error in preparse\n");
		printf("preparse: |%s|\n", prompt);
		lexer(prompt, &tokens);
		printf("tokens :");
//		printf("check\n");
		print_tokens(tokens);
//		if (!(ast = parse_line(tokens)))
//			printf("problem with AST");
//		printf("check1\n");
//		if (!(start(ast)))
//			printf("problem with executor");      //EXECUTION
//		printf("main check \n");
		clear_all(&tokens);
	}
	exit(EXIT_SUCCESS);
}
