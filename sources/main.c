/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:02:01 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/06 08:57:21 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../readline/history.h"
#include "../../../readline/readline.h"

#include "global.h"
#include "environment/environment.h"
#include "signal_handler/signal_handler.h"
#include "tokenizer/tokenizer.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "expander/expander.h"
#include "executor/executor.h"

t_hash_table	g_env;

static void	process(char *input);

int	main(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	if (env_init() == false)
		return (EXIT_FAILURE);
	input = readline(PROMPT);
	while (input != NULL)
	{
		if (input[0] != '\0')
		{
			add_history(input);
			process(input);
		}
		free(input);
		input = readline(PROMPT);
	}
	printf("\nexit\n");
	env_destroy();
	clear_history();
	return (EXIT_SUCCESS);
}

static void	process(char *input)
{
	t_deque			tokens;
	t_deque			commands;
	t_commands_tree	*commands_tree;

	if (tokenize(&tokens, input) == false)
		return ;
	if (lexical_analyze(&tokens) == false)
		return ;
	print_tokens(&tokens);
	if (parse(&commands, &tokens) == false)
		return ;
	destroy_tokens(&tokens);
	print_commands(&commands);
	print_commands_structure(&commands);
	commands_tree = make_commands_tree(&commands_tree, &commands);
	if (commands_tree == NULL)
		print_error(NULL, NULL, strerror(ENOMEM));
	// else
	// 	execute(&commands, commands.head, commands.tail, false);
	destroy_commands(&commands);
	destroy_commands_tree(commands_tree);
}
