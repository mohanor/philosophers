#include "philosophers.h"

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
    pthread_mutex_t *mtx;
} t_philo;

void    print(char *str)
{
    printf("%s\n", str);
}

void *ft_thread(void *vars)
{
    t_philo *philo;
    int id;

    philo = (t_philo *)vars;
    id = philo->id;
    while (philo->eat--)
    {
        if (!philo->must_eat)
            return (0);
        pthread_mutex_lock(&philo->mtx[id]);
        printf("%d      has taken a fork\n", id);
        pthread_mutex_lock(&philo->mtx[(id + 1) % 6]);
        printf("%d      has taken a fork\n", id);
        printf("%d      is eating\n", id);
        sleep(philo->eat);
        philo->if_die -= philo->eat;
        if (philo->if_die <= 0)
            return (0);
        pthread_mutex_unlock(&philo->mtx[id]);
        pthread_mutex_unlock(&philo->mtx[(id + 1) % 6 ]);
        printf("%d      sleeping\n", id);
        sleep(philo->sleep);
        philo->if_die = philo->die;
        philo->must_eat--;
        printf("%d      thinking\n", id);
    }
    
    printf("%d ok\n", philo->id);
    return 0;
}

void checker_1(t_philo *philo, int philo_nbr)
{
    int i;
    int counter;

    counter = 0;
    while (1)
    {
        usleep(300);
        i = 0;
        while (i < philo_nbr)
        {
            if (!philo[i].must_eat)
                counter++;
            i++;
        }

        if (counter == philo_nbr)
        {
            printf("all philo ate");
            exit(0);
        }
        i = 0;
        while (i < philo_nbr)
        {
            if (philo[i].is_die)
            {
                printf("philo die");
                exit (0);
            }
            i++;
        }
    }
}

void checker_2(t_philo *philo)
{
    printf("checker 2");
    while(1);
}

int main(int ac, char **av)
{
    int i;
    pthread_t   *ids;
    pthread_mutex_t *mtx;
    int philo_nbr;
    t_philo *philo;

    philo_nbr = ft_atoi(av[1]);



    i = 0;
    ids = (pthread_t *)malloc(sizeof(pthread_t) * philo_nbr);
    if (!ids)
        return 0;

    mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_nbr);
    if (!mtx)
        return 0;
    
    i = 0;
    while (i < philo_nbr)
    {
        if (pthread_mutex_init(&mtx[i], NULL) != 0)
            return (1);
        i++;
    }

    philo = (t_philo *)malloc(sizeof(t_philo) * philo_nbr);
    if (!philo)
        return 0;
    
    i = 0;
    while (i < philo_nbr)
    {
        philo[i].mtx = mtx;
        philo[i].id = i + 1;
        philo[i].die = ft_atoi(av[2]);
        philo[i].if_die = ft_atoi(av[2]);
        philo[i].eat = ft_atoi(av[3]);
        philo[i].sleep = ft_atoi(av[4]);
        philo[i].must_eat = ft_atoi(av[5]);
        philo[i].is_die = 0;
        i++;
    }

    i = 0;
    while (i < philo_nbr)
    {
        pthread_create(&ids[0], NULL, ft_thread, &philo[i]);
        usleep(500);
        i++;
    }


    // if phile is die
    // if all philo ate

    if (ac == 6)
        checker_1(philo, philo_nbr);
    else
        checker_2(philo);
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

