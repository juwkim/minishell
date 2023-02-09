/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:02:01 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 13:10:31 by juwkim           ###   ########.fr       */
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

t_env	g_env;

static void	process(const char *input);

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
	printf("exit\n");
	env_destroy();
	clear_history();
	return (EXIT_SUCCESS);
}

static void	process(const char *input)
{
	t_list	tokens;
	t_list	commands;

	if (tokenize(&tokens, input) == false)
		return ;
	if (lexical_analyze(&tokens) == false)
		return ;
	if (parse(&commands, &tokens) == false)
		return ;
	print_tokens(&tokens);
	list_destroy(&tokens, free);
	print_commands(&commands);
	if (make_commands_tree(&commands) == false)
		return ;
	execute(&commands, false);
	list_destroy(&commands, destroy_command);
}
