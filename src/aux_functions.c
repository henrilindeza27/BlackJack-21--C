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

void ft_load_bar(size_t size) 
{
    printf("Loading: [");
	 
    for (size_t i = 0; i < size; i++) 
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
    ft_load_bar(20);
    ft_wait_enter();
    system("clear");
}


int ft_player_menu(void)
{
    int option;

    printf("╔════════════════════════════╗\n");
    printf("║   [1] Carregar player      ║\n");
    printf("║   [2] Criar player         ║\n");
    printf("║   [3] Iniciar como guest   ║\n");
    printf("║   [4] Sair                 ║\n");
    printf("╚════════════════════════════╝\n");
    printf("→ ");
    while (scanf("%d", &option) <= 0 || (option < 1 || option > 4))
    {
        printf("Opção inválida insira novamente\n");
        printf("→ ");
        ft_clean_input();
    }
    
    return option;
}

int ft_is_empty_nickname(char *nickname)
{
    while (*nickname)
    {
        if (!isspace((unsigned char)*nickname))
            return 0;
        nickname++;
    }
    return 1;
}

double ft_check_bet(int result, double bet)
{
    if(result == 1)
        return (bet);
    else if(result == 2)
        return(bet * 2);
    else if(result == -1)
        return (bet * -1);
    else if(result == -2)
        return(bet * -2);
    else if(result == 3)
       return(bet * 1.5);
    return 0;
}

int ft_double_length(double num) 
{
    int length = 0;

    if (num < 0) 
    {
        length++;
        num = fabs(num);
    }

    int int_part = (int)num;
    if (int_part == 0) 
        length++; 
    else 
    {
        while (int_part > 0) 
        {
            int_part /= 10;
            length++;
        }
    }

    // Contar o ponto decimal e os dígitos da parte fracionária
    double fractional_part = num - (int)num;
    if (fractional_part > 0) 
    {
        length++; // Contar o ponto decimal

        int fractional_digits = 0;

        while (fractional_part > 0 && fractional_digits < 16) 
        {
            fractional_part *= 10;
            int digit = (int)fractional_part;
            fractional_part -= digit;

            fractional_digits++;

            // Se a parte fracionária for suficientemente pequena, termine
            if (fabs(fractional_part) < 1e-10) 
                break;
        }

        length += fractional_digits;
    }

    return length;
}

void ft_spaces(int spaces)
{
	while (spaces)
	{
		printf(" ");
		spaces--;
	}
}
int ft_size_t_length(size_t num) 
{
    int length = 0;

    if (num == 0) 
        return 1; 

    while (num > 0) 
    {
        num /= 10; 
        length++;
    }

    return length;
}

int ft_main_menu(PLAYER player, int is_guest)
{
    int spaces = 42 - (4 + strlen(player.nickname));
    int option;
    int flag = 2;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║ 👤 %s", player.nickname);
    ft_spaces(spaces);
    printf("║\n");
    spaces = 42 - (6 + ft_double_length(player.balance));
    printf("║ 💰 %.2f €", player.balance);
    ft_spaces(spaces);
    printf("║\n");
    printf("╠══════════════════════════════════════════╣\n");
    printf("║ [1] - Jogar                              ║\n");
    if(!is_guest)
    {    
        printf("║ [2] - Ver estatistica                    ║\n");
        flag = 3;
    }
    printf("║ [%d] - Sair                               ║\n", flag);
    printf("╚══════════════════════════════════════════╝\n");
    printf("-> ");
    while (scanf("%d", &option) <= 0 || (option < 1 || option > flag))
    {
        system("clear");
        printf("[ Opção inválida inválida ]\n");
        printf("-> ");
        ft_clean_input();
    }
    return option;

}

void ft_show_stats(PLAYER player)
{
    int spaces = 42 - (4 + strlen(player.nickname));
    system("clear");
    printf("╔══════════════════════════════════════════╗\n");
    printf("║ 👤 %s", player.nickname);
    ft_spaces(spaces);
    printf("║\n");
    printf("╠══════════════════════════════════════════╣\n");
    printf("║                                          ║\n");
    printf("║ Total de jogos: %zu", player.total_games);
    spaces = 42 - (17 + ft_size_t_length(player.total_games));
    ft_spaces(spaces);
    printf("║\n");
    printf("║ Total de vitórias: %zu", player.total_wins);
    spaces = 42 - (20 + ft_size_t_length(player.total_wins));
    ft_spaces(spaces);
    printf("║\n");
    printf("║ Total de derrotas: %zu", player.total_loses);
    spaces = 42 - (20 + ft_size_t_length(player.total_loses));
    ft_spaces(spaces);
    printf("║\n");
    printf("║ Total de empates: %zu", player.total_draw);
    spaces = 42 - (19 + ft_size_t_length(player.total_draw));
    ft_spaces(spaces);
    printf("║\n");
    printf("║                                          ║\n");
    printf("║ Maior vitória: %.2f", player.max_win);
    spaces = 42 - (19 + ft_double_length(player.max_win));
    ft_spaces(spaces);
    printf("║\n");
    printf("║ Maior derrota: %.2f", player.max_lose);
    spaces = 42 - (19 + ft_double_length(player.max_lose));
    ft_spaces(spaces);
    printf("║\n");
    printf("╚══════════════════════════════════════════╝\n");






}