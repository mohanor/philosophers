/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:14:39 by matef             #+#    #+#             */
/*   Updated: 2022/07/26 13:14:40 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		i = -1;
		str++;
	}	
	while (*str && (*str >= '0' && *str <= '9'))
	{
		j = (j * 10) + (*str - 48);
		str++;
	}
	return (i * j);
}
