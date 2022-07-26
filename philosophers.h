/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:06:02 by matef             #+#    #+#             */
/*   Updated: 2022/07/26 20:53:16 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct tab
{
	int				staus;
	int				nbr_philo;
	pthread_mutex_t	print;
	pthread_mutex_t	*mtx;
	unsigned long	in_start_time;
	int				numofarg;
}	t_tab;

typedef struct philo
{
	int				id;
	int				eat;
	int				die;
	int				if_die;
	int				sleep;
	int				think;
	int				must_eat;
	int				is_die;
	unsigned long	start_time;
	unsigned long	last_meal;
	t_tab			*tab;
}	t_philo;

int				init_func(pthread_t	**ids, t_tab *tab, t_philo **philo, int n);
void			philo_print(char *str, long time, int id, t_philo *philos);
void			free_parm(t_philo *philo, pthread_mutex_t *mtx, pthread_t *ids);
void			init_philo(char **av, t_philo	*philo, int philo_nbr, int ac);
int				real_time(t_philo *philo, unsigned long time);
long long		apah(long long pers, long long past);
int				parcing(char **av, int ac);
int				has_char(char *str);
void			ft_uslep(int time);
int				ft_atoi(char *str);
unsigned long	in_time(void);

#endif
