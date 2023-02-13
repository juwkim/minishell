/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:02:01 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 17:08:24 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../readline/history.h"
#include "../../../readline/readline.h"

#include "global.h"
#include "linked_list.h"
#include "tokenizer/tokenizer.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "expander/expander.h"
#include "executor/executor.h"
#include "utils/print.h"
#include "utils/exit_status.h"
#include "utils/environment.h"
#include "utils/signal_handler.h"

t_env	g_env;

static int	process(const char *input);

int	main(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	if (env_init() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	input = readline(PROMPT);
	while (input != NULL)
	{
		if (input[0] != '\0')
		{
			add_history(input);
			exit_status_set(process(input));
		}
		free(input);
		input = readline(PROMPT);
	}
	printf("exit\n");
	env_destroy();
	clear_history();
	exit(exit_status_get());
}

static int	process(const char *input)
{
	t_list	tokens;
	t_list	commands;
	int		exit_status;

	if (tokenize(&tokens, input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lexical_analyze(&tokens) == EXIT_FAILURE)
		return (EXIT_SYNTAX_ERROR);
	if (parse(&commands, &tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// print_tokens(&tokens);
	list_destroy(&tokens, free);
	// print_commands(&commands);
	if (make_commands_tree(&commands) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exit_status = execute(&commands, false);
	list_destroy(&commands, destroy_command);
	return (exit_status);
}
