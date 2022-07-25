#include "philosophers.h"

typedef struct tab
{
    int staus;
    int nbr_philo;
    pthread_mutex_t print;
    pthread_mutex_t *mtx;
    unsigned long in_start_time;
    int numofarg;
} t_tab;

typedef struct philo
{
    int id;
    int eat;
    int die;
    int if_die;
    int sleep;
    int think;
    int must_eat;
    int is_die;
    unsigned long start_time;
    
    unsigned long last_meal;

    
    t_tab *tab;

} t_philo;

unsigned long in_time()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}


int real_time(t_philo *philo, unsigned long time)
{
    return ((int)(time - philo->start_time) % 100);
}
void	philo_print(char *str, long time, int id, t_philo *philos)
{
	pthread_mutex_lock(&philos->tab->print);
	printf("[%ld]       philo %d  %s\n", time - philos->tab->in_start_time, id, str);
	pthread_mutex_unlock(&philos->tab->print);
	return ;
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
void ft_thread(void *vars)
{
    t_philo *philo;
    int id;

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

void checker(t_philo *philo, int philo_nbr)
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
                printf("[%ld]     philo %d  died\n", in_time() -  philo->tab->in_start_time , philo->id);
            break;
			
		}
		i++;
		if (i == philo_nbr)
			i = 0;
	}
}

void    free_parm(t_philo *philo, pthread_mutex_t *mtx, pthread_t *ids)
{
    free(philo);
    free(mtx);
    free(ids);
}

int main(int ac, char **av)
{
    int i;
    pthread_t   *ids;
    
    int philo_nbr;
    t_philo *philo;
    t_tab tab;


    tab.numofarg = ac;
    philo_nbr = ft_atoi(av[1]);
    i = 0;
    ids = (pthread_t *)malloc(sizeof(pthread_t) * philo_nbr);
    if (!ids)
        return 0;

    tab.mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_nbr);
    if (!tab.mtx)
        return 0;
    
    i = 0;
    while (i < philo_nbr)
    {
        if (pthread_mutex_init(&tab.mtx[i], NULL) != 0)
            return (1);
        i++;
    }

    philo = (t_philo *)malloc(sizeof(t_philo) * philo_nbr);
    if (!philo)
        return 0;
    
    i = 0;

    tab.nbr_philo = philo_nbr;
    tab.staus = 1;
    if (pthread_mutex_init(&tab.print, NULL) != 0)
            return (1);

    while (i < philo_nbr)
    {
        
        philo[i].id = i;
        philo[i].die = ft_atoi(av[2]);
        philo[i].eat = ft_atoi(av[3]);
        philo[i].sleep = ft_atoi(av[4]);
        philo[i].must_eat = ft_atoi(av[5]);

        
        i++;
    }
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

    checker(philo, philo_nbr);
    free_parm(philo, tab.mtx, ids);
   
    return 0;
}


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

