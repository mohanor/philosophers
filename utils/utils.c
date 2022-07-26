/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:15:16 by matef             #+#    #+#             */
/*   Updated: 2022/07/26 13:18:15 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	has_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	parcing(char **av, int ac)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (has_char(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_parm(t_philo *philo, pthread_mutex_t *mtx, pthread_t *ids)
{
	free(philo);
	free(mtx);
	free(ids);
}

long	long	apah(long long pers, long long past)
{
	return (pers - past);
}

void	ft_uslep(int time)
{
	long long	start_resting;

	start_resting = in_time();
	while (1)
	{
		if (apah(in_time(), start_resting) >= time)
			break ;
		usleep(500);
	}
}
