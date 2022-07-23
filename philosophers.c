#include "philosophers.h"

void   check()
{
    printf("good\n");
} 

void *ft_thread(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->ifo->mutex[philo->id]);
        // printf()
        pthread_mutex_lock(&philo->ifo->mutex[philo->id+1]);
        printf("eat %d\n", philo->id);
        sleep(1);
        pthread_mutex_unlock(&philo->ifo->mutex[philo->id]);
        pthread_mutex_unlock(&philo->ifo->mutex[philo->id+1]);
        sleep(1);
    }

    return NULL;
}

int main(int ac, char **av)
{
    pthread_t   *ids;
    t_info      *t_nbr;
    t_philo     *philo;
    int i;

    t_nbr = (t_info *)malloc(sizeof(t_nbr));
    if (!t_nbr)
        return 0;
    t_nbr->nbr_philo = ft_atoi(av[1]);

    philo = (t_philo *)malloc(sizeof(t_philo) * t_nbr->nbr_philo);
    if (!philo)
        return 0;

    ids = (pthread_t *)malloc(sizeof(pthread_t) * t_nbr->nbr_philo);
    if (!ids)
        return 0;

    i = 0;
    while (i < t_nbr->nbr_philo)
    {
        philo[i].id = i;
        philo[i].ifo = t_nbr;
        i++;
    }

    t_nbr->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * t_nbr->nbr_philo);
    if (!t_nbr->mutex)
        return 0;

    i = 0;
    while (i < t_nbr->nbr_philo)
    {
        if (pthread_mutex_init(&t_nbr->mutex[i], NULL) != 0)
            return (1);
        i++;
    }

    i = 0;
    while (i < t_nbr->nbr_philo)
    {
        pthread_create(&ids[i], NULL, ft_thread, &philo[i]);
        i++;
        
        usleep(500);
    }

    // printf("good\n");
    while (1);


    // pthread_mutex_init(t_mutex->mutex, NULL);  
    //ids = (pthread_t *)malloc(sizeof(pthread_t) * t_nbr->nbr_philo);
    //if (!ids)
    //    return 0;

    // pthread_mutex_destroy(t_mutex->mutex);
    // ft_putnbr(t_mutex->nbr);
    return (0);
}
