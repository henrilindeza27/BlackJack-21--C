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

    printf("+----------------------------+\n");
    printf("|   [1] Carregar player      |\n");
    printf("|   [2] Criar player         |\n");
    printf("|   [3] Iniciar como guest   |\n");
    printf("|   [4] Sair                 |\n");
    printf("+----------------------------+\n");
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

double ft_check_bet(int result, double bet, int split_flag, int double_flag)
{
    if(result == 0)
        return(bet * split_flag * double_flag);
    else if(result == 1)
    {    
        if(split_flag == 2)
            return((bet * 2) + bet);
        return (bet * 2);
    }
    else if(result == 2)
        return((bet * 2) * 2);
    else if(result == -1)
        return (0);
    else if(result == -2)
        return(0);
    else if(result == 3)
       return((bet * 1.5) + bet);
    else if(result == -3)
        return(bet * -0.5);
    
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

    long long int int_part = (long long int)num;
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

    length += 3;
    

    return length;
}

void ft_print_char(int size, char ch)
{
	while (size)
	{
		printf("%c", ch);
		size--;
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

    printf("+------------------------------------------+\n");
    printf("| 👤 %s", player.nickname);
    ft_print_char(spaces, ' ');
    printf("|\n");
    spaces = 42 - (6 + ft_double_length(player.balance));
    printf("| 💰 %.2f €", player.balance);
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("+------------------------------------------+\n");
    printf("| [1] - Jogar                              |\n");
    if(!is_guest)
    {    
        printf("| [2] - Ver estatistica                    |\n");
        flag = 3;
    }
    if(player.balance < 1)
    {
        printf("| [%d] - Adicionar 250 ao saldo             |\n", flag);
        if(!is_guest)
            flag = 4;
        else
            flag = 3;
        
    }
    printf("| [%d] - Sair                               |\n", flag);
    printf("+------------------------------------------+\n");
    printf("-> ");
    while (scanf("%d", &option) <= 0 || (option < 1 || option > flag))
    {
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
    printf("+------------------------------------------+\n");
    printf("| 👤 %s", player.nickname);
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("|------------------------------------------|\n");
    printf("|                                          |\n");
    printf("| Total de jogos: %zu", player.total_games);
    spaces = 42 - (17 + ft_size_t_length(player.total_games));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("| Total de vitórias: %zu", player.total_wins);
    spaces = 42 - (20 + ft_size_t_length(player.total_wins));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("| Total de derrotas: %zu", player.total_bets);
    spaces = 42 - (20 + ft_size_t_length(player.total_bets));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("| Total de empates: %zu", player.total_draw);
    spaces = 42 - (19 + ft_size_t_length(player.total_draw));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("|                                          |\n");
    printf("| Maior vitória: %.2f", player.max_win);
    spaces = 42 - (16 + ft_double_length(player.max_win));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("| Maior derrota: %.2f", player.max_lose);
    spaces = 42 - (16 + ft_double_length(player.max_lose));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("|                                          |\n");
    printf("| Total ganho: %.2f", player.total_win);
    spaces = 42 - (14 + ft_double_length(player.total_win));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("| Total apostado: %.2f", player.total_bet);
    spaces = 42 - (17 + ft_double_length(player.total_bet));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("| Profit: %.2f", player.total_win - player.total_bet);
    spaces = 42 - (9 + ft_double_length(player.total_win - player.total_bet));
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("+------------------------------------------+\n");

}

void ft_add_balance(PLAYER *player)
{
    player->balance += 250;
}

int ft_ask_to_continue(void)
{
    int option;

    printf("Quer continuar ?\n");
    printf("[1]- Sim  [2]- Não\n");
    printf("→ ");
    while (scanf("%d", &option) <= 0 || (option < 1 || option > 2))
    {
        printf("[ Opção inválida inválida ]\n");
        printf("-> ");
        ft_clean_input();
    }
    return option;
}

int ft_check_bj_player(HandNode *player_hand, HandNode *dealer_hand)
{
    if(ft_calculate_hand_points(player_hand, 0 , 0) == 21 && ft_calculate_hand_points(dealer_hand, 0 , 0) != 21)
        return 1;
    else if(ft_calculate_hand_points(player_hand, 0 , 0) == 21 && ft_calculate_hand_points(dealer_hand, 0 , 0) == 21 && dealer_hand->hand[0][0] == '1')
        return 1;
    return 0;
}

int ft_check_split(HandNode *player_hand)
{
    if(ft_card_value(player_hand->hand[0]) == ft_card_value(player_hand->hand[1]))
        return 1;
    return 0;
}

int ft_check_result(HandNode *player_hand, HandNode *dealer_hand, int flag)
{
    int total_hand = ft_total_hands(player_hand);
    int retrn = 0;
    while (total_hand-- && player_hand != NULL)
    {
        int player_points = ft_calculate_hand_points(player_hand, 0 , 0);
        int dealer_points = ft_calculate_hand_points(dealer_hand, 1, 0);
       
        if(player_points > 21 || player_points < dealer_points)
        {
            if(!total_hand)
            {
                ft_clean_input();
                ft_wait_enter();
            }
            retrn -= 1 * flag;
        }
        else if(player_points > dealer_points)
        {   
            if(!total_hand)
            {
                ft_clean_input();
                ft_wait_enter();
            }
            
            retrn += 1 * flag;
        }
        else
        {   
            if(!total_hand)
            {
                ft_clean_input();
                ft_wait_enter();
            }
            retrn += 0;
        }
        player_hand = player_hand->next;
    }
    return retrn;
}

void ft_in_game_hud(PLAYER player,double *total_bet , double *side_bets, double *side_wins, double bet, int double_flag, double first_play)
{
    static int flag_to_enter_one_time = 0;
    if(!first_play)
    {
        for(int i = 0; i < 4; i++)
            *total_bet += side_bets[i];
        *total_bet += bet;
        flag_to_enter_one_time = 0;
    }
    else if(double_flag == 2 && !flag_to_enter_one_time)
    {    
        *total_bet += bet;
        flag_to_enter_one_time++;
    }
    int size_line = ft_double_length(player.balance) + ft_double_length(*total_bet) + 37;
    int tmp = size_line;
    printf("+");
    ft_print_char(size_line, '-');
    printf("+\n");
    printf("| 💰 Saldo: %.2f € | 🪙 Total Apostado: %.2f€ ", player.balance, *total_bet); 
    printf("|\n");
    printf("+");
    ft_print_char(size_line, '-');
    printf("+\n");
    printf("| [HOT 3]: %.2f    [PERFECT PAIR]: %.2f", side_wins[0], side_wins[1]);
    tmp -= ft_double_length(side_wins[0]) + ft_double_length(side_wins[1]) + 30;
    ft_print_char(tmp, ' ');
    printf("|\n");
    printf("| [21 + 3]: %.2f   [BUST IT]: %.2f", side_wins[2], side_wins[3]);
    tmp = size_line;
    tmp -= ft_double_length(side_wins[2]) + ft_double_length(side_wins[3]) + 25;
    ft_print_char(tmp, ' ');
    printf("|\n");
    printf("+");
    ft_print_char(size_line, '-');
    printf("+\n\n");
}
