/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 06:20:25 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 08:55:49 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <errno.h>
# include <string.h>
# include "global.h"

# define SHELL_NAME	"minishell"

# define DEF_COLOR	"\033[0;39m"
# define GRAY		"\033[1;90m"
# define RED		"\033[1;91m"
# define GREEN		"\033[1;92m"
# define YELLOW		"\033[1;93m"
# define BLUE		"\033[1;94m"
# define MAGENTA	"\033[1;95m"
# define CYAN		"\033[1;96m"
# define WHITE		"\033[1;97m"

bool	print_error(const char *program_name, const char *file, \
												const char *message);
void	print_tokens(const t_list *tokens);
void	print_commands(const t_list *commands);
void	print_commands_structure(const t_list *commands);

#endif // PRINT_H
