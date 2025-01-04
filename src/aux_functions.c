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

void ft_load_bar(void) 
{
    printf("Loading: [");
	
    for (int i = 0; i < 20; i++) 
	{
		printf("■");
		fflush(stdout);
        usleep(50000);
    }
    printf(" ] ✔");
    usleep(500000);
}  
void ft_initial_banner(void)
{
    printf("╔═════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                             ║ \n");
    printf("║   ██████  ██       █████   ██████ ██   ██      ██  █████   ██████ ██   ██   ║\n");
    printf("║   ██   ██ ██      ██   ██ ██      ██  ██       ██ ██   ██ ██      ██  ██    ║\n");        
    printf("║   ██████  ██      ███████ ██      █████        ██ ███████ ██      █████     ║\n");
    printf("║   ██   ██ ██      ██   ██ ██      ██  ██  ██   ██ ██   ██ ██      ██  ██    ║\n");
    printf("║   ██████  ███████ ██   ██  ██████ ██   ██  █████  ██   ██  ██████ ██   ██   ║\n");
    printf("║                                                                             ║ \n");
    printf("║                                ██████   ██                                  ║\n");
    printf("║                                     ██ ███                                  ║\n");
    printf("║                                 █████   ██                                  ║\n");
    printf("║                                ██       ██                                  ║\n");
    printf("║                                ███████  ██                                  ║\n");
    printf("║                                                                             ║ \n");
    printf("║   Made by: henrilindeza27                                                   ║ \n");
    printf("╚═════════════════════════════════════════════════════════════════════════════╝\n");
    ft_load_bar();
    ft_wait_enter();
    system("clear");
}