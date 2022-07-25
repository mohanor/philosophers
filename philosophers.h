#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct info
{ 
    pthread_mutex_t  *mutex;
    int nbr_philo;
} t_info;
/*
typedef struct philo {
    int id;
    t_info  *ifo;
} t_philo;
*/
void	ft_putstr(char *s);
void	ft_putnbr(int n);
int     ft_atoi(char *str);

#endif
