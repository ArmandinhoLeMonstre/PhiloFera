/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:12:10 by armitite          #+#    #+#             */
/*   Updated: 2024/12/24 17:32:31 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int stock_args(t_data *data, int ac, char **av)
{
    data->p_total= ft_atoi(av[1]);
    data->starving_t = ft_atoi(av[2]);
    data->eating_t = ft_atoi(av[3]);
    data->sleeping_t = ft_atoi(av[4]);
    if (ac == 6)
        data->meals_nbr = ft_atoi(av[5]);
    else
		data->meals_nbr = -1;
	data->death = 0;
	data->meals_eaten = 0;
	data->mutex_print = malloc(sizeof(pthread_mutex_t) * 1);
    // data->mutex_print = malloc(sizeof(pthread_mutex_t) * 1);
	// data->mutex_print = malloc(sizeof(pthread_mutex_t) * 1);
	if (pthread_mutex_init(data->mutex_print, (void *)data) != 0)
        return (2);
    // if (pthread_mutex_init(data->mutex_print, (void *)data) != 0)
	// 	return (free(data->mutex_print), 2);
	// if (pthread_mutex_init(data->mutex_print, (void *)data) != 0)
	// 	return (free(data->mutex_print), 2);
	return (0);
}

int	allocate_forks(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->p_total);
	for (i = 0; i < data->p_total; i++) {
		if (pthread_mutex_init(&data->mutex_forks[i], NULL) != 0) {
			perror("Mutex initialization failed");
			// Cleanup code here...
		}
	}

	return (0);
}

int	init_philo(t_data *data)
{
	int	i;
	t_philo **philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->p_total);
	while (i < data->p_total)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->n = i + 1;
		philo[i]->time = 0;
		philo[i]->data = malloc(sizeof(t_data));
		philo[i]->data = data;
		philo[i]->left_fork = &data->mutex_forks[philo[i]->n - 1];
    	philo[i]->right_fork = &data->mutex_forks[philo[i]->n % data->p_total];
		i++;
	}
	create_philo(philo, data);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
    if (ac != 5 && ac != 6)
        return (printf("Error args\n"), 2);
    stock_args(&data, ac, av);
	allocate_forks(&data);
	init_philo(&data);
	//ft_usleep(data.sleeping_t);
    return (0);
}