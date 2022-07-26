/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:05:44 by matef             #+#    #+#             */
/*   Updated: 2022/07/26 18:49:07 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_thread(void *vars)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)vars;
	id = philo->id;
	pthread_mutex_lock(&philo->tab->mtx[id]);
	philo_print("has taken a fork", in_time(), id, philo);
	pthread_mutex_lock(&philo->tab->mtx[(id + 1) % (philo->tab->nbr_philo)]);
	philo_print("has taken a fork", in_time(), id, philo);
	philo_print("is eating", in_time(), id, philo);
	ft_uslep(philo->eat);
	philo->start_time = in_time();
	pthread_mutex_unlock(&philo->tab->mtx[id]);
	pthread_mutex_unlock(&philo->tab->mtx[(id + 1) % (philo->tab->nbr_philo)]);
	philo_print("is sleeping", in_time(), id, philo);
	ft_uslep(philo->sleep);
	philo_print("is thinking", in_time(), id, philo);
}

void	*philosopher(void *var)
{
	int			i;
	t_philo		*philos;

	philos = (t_philo *)var;
	i = 0;
	if (philos->tab->numofarg == 5)
	{
		while (1)
			ft_thread(philos);
	}
	else
	{
		while (i < philos->must_eat)
		{
			ft_thread(philos);
			i++;
		}
		if (i == philos->must_eat)
			philos->tab->staus = 1;
	}
	return (0);
}

void	checker(t_philo *philo, int philo_nbr)
{
	int	i;

	i = 0;
	while (i < philo_nbr)
	{
		if (in_time() - philo[i].start_time
			> philo[i].die)
		{
			pthread_mutex_lock(&philo->tab->print);
			if (philo[i].tab->staus == 0)
				printf("[%ld]     philo %d  died\n", in_time() - philo->tab->in_start_time , philo->id);
			break ;
		}
		i++;
		if (i == philo_nbr)
			i = 0;
	}
}

void start_thread(t_philo *philo, pthread_t *ids, t_tab tab, int philo_nbr)
{
	int i;

	tab.in_start_time = in_time();
	i = 0;
	while (i < philo_nbr)
	{
		philo[i].tab = &tab;
		philo[i].start_time = in_time();
		pthread_create(&ids[i], NULL, philosopher, &philo[i]);
		usleep(500);
		i++;
	}
}

int	main(int ac, char **av)
{
	int			i;
	int			philo_nbr;
	pthread_t	*ids;
	t_philo		*philo;
	t_tab		tab;

	if (ac != 5 && ac != 6)
		return (0);
	if (!parcing(av, ac))
		return (0);
	tab.numofarg = ac;
	philo_nbr = ft_atoi(av[1]);
	i = 0;
	if (!init_func(&ids, &tab, &philo, philo_nbr))
		return (0);
	init_philo(av, philo, philo_nbr, ac);
	start_thread(philo, ids, tab, philo_nbr);
	checker(philo, philo_nbr);
	free_parm(philo, tab.mtx, ids);
	return (0);
}
