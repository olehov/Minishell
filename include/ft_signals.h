/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:10:08 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:45:14 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNALS_H
# define FT_SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_received_signal;

void	set_heredoc_signals(void);
void	set_signals(void);

void	signal_handler(int signo);
void	heredoc_signal_handler(int signo);

#endif