#include "../inc/bj.h"


void	ft_clean_input(void)
{
	while (getchar() != '\n')
		;
}

void ft_wait_enter(void) 
{
    char av[5] = {};
    int enter = 0;
    
    do {
        printf("\nPressione a tecla ENTER para avançar");
        fgets(av, sizeof(av), stdin);
        
        if (strchr(av, '\n') != NULL) 
		{
            if (strcmp(av, "\n") == 0) 
			{
                enter = 1; 
                system("clear");
            } 
        } 
		else 
            while (getchar() != '\n');
        
    } while (enter == 0);
}