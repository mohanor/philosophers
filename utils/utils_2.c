/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:19:06 by matef             #+#    #+#             */
/*   Updated: 2022/07/26 18:49:16 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	real_time(t_philo *philo, unsigned long time)
{
	return ((int)(time - philo->start_time) % 100);
}

unsigned long	in_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	philo_print(char *str, long time, int id, t_philo *philos)
{
	pthread_mutex_lock(&philos->tab->print);
	printf("[%ld]	philo %d  %s\n", time - philos->tab->in_start_time, id, str);
	pthread_mutex_unlock(&philos->tab->print);
	return ;
}

void init_philo(char **av, t_philo	*philo, int philo_nbr, int ac)
{
	int i;

	i = 0;
	while (i < philo_nbr)
	{
		philo[i].id = i;
		philo[i].die = ft_atoi(av[2]);
		philo[i].eat = ft_atoi(av[3]);
		philo[i].sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo[i].must_eat = ft_atoi(av[5]);
		i++;
	}
}

int	init_func(pthread_t	**ids, t_tab *tab, t_philo **philo, int philo_nbr)
{
	int	i;

	*ids = (pthread_t *)malloc(sizeof(pthread_t) * philo_nbr);
	if (!ids)
		return (0);
	tab->mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_nbr);
	if (!tab->mtx)
		return (0);
	i = 0;
	while (i < philo_nbr)
	{
		if (pthread_mutex_init(&tab->mtx[i], NULL) != 0)
			return (0);
		i++;
	}
	*philo = (t_philo *)malloc(sizeof(t_philo) * philo_nbr);
	if (!philo)
		return (0);
	i = 0;
	tab->nbr_philo = philo_nbr;
	tab->staus = 1;
	if (pthread_mutex_init(&tab->print, NULL) != 0)
		return (0);
	return (1);
}
