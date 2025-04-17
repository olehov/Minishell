/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:47:37 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/17 21:44:13 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_parser.h"

int	handle_single_redirect(char *input,
	t_token *tokens, t_tokenizer_ctx *ctx)
{
	t_tokenizer_ctx	tmp;

	if (ctx->accum)
	{
		set_token(&tokens[ctx->j++], ctx);
		reset_quote_state(ctx);
	}
	tmp.accum = ft_substr(input, ctx->i, 1);
	tmp.in_quotes = 0;
	tmp.quote_char = 0;
	set_token(&tokens[ctx->j++], &tmp);
	if (tmp.accum != NULL)
		free(tmp.accum);
	ctx->i++;
	ctx->skip_next_token_quote_handling = 1;
	return (1);
}
