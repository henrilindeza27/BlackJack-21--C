#include "../inc/bj.h"


void ft_player_single_play(char ***deck, HandNode *player_hand, int *cards_played, int number_decks)
{
    ft_save_card_played(player_hand, deck[0][0]);
    ft_play_card(deck, number_decks, cards_played);
}

void ft_dealer_single_play(char ***deck, HandNode *dealer_hand, int *cards_played, int number_decks)
{
    ft_save_card_played(dealer_hand, deck[0][0]);
    ft_play_card(deck, number_decks, cards_played);
}

void ft_initial_play(char ***deck, int *cards_played, int number_decks, HandNode *player_hand, HandNode *dealer_hand)
{
    
    ft_player_single_play(deck, player_hand, cards_played, number_decks);
    ft_dealer_single_play(deck, dealer_hand, cards_played, number_decks);
    ft_player_single_play(deck, player_hand, cards_played, number_decks);
    ft_dealer_single_play(deck, dealer_hand, cards_played, number_decks);
}

int ft_ask_play()
{
    int option;

    printf("1- Hit | 2- Double | 3 - Stop \n");
    while(scanf("%d", &option) <= 0 || (option < 1 || option > 3))
        ft_clean_input();

    return option;
}

int ft_ask_insurance()
{
    int option;

    printf("Quer fazer seguro? (Metade do valor apostado)\n");
    printf("1- Sim | 2- Não \n");
    while(scanf("%d", &option) <= 0 || (option < 1 || option > 2))
        ft_clean_input();

    return option;
}

int ft_player_play(char ***deck, HandNode *player_hand, HandNode *dealer_hand ,int *cards_played, int number_decks, PLAYER *player, double bet, int *flag)
{
    int option;
    char *dhand = dealer_hand->hand[1];
    int flag_show = 0;
    int first_play = 1;

    if(dhand[0] == 'A')
    {
        flag_show = 1;
        if(player->balance >= bet * 1.5)
        {
            int op = ft_ask_insurance();
            system("clear");
            if(op == 1)
            {    
                player->balance -= (bet / 2);
                player->total_lose -= (bet / 2);  
            }
            if(ft_calculate_hand_points(dealer_hand, 0 , 0) == 21)
            {  
                
                ft_print_played_cards(0, player_hand, dealer_hand, player->nickname);
                return 0;
            }
            else
            {
                ft_print_played_cards(1, player_hand, dealer_hand, player->nickname);
                printf("[ O dealer não tem blackjack ]\n");
            }
            
        }
        else
        {
            system("clear");
            if(ft_calculate_hand_points(dealer_hand, 0 , 0) == 21)
            {  
                
                ft_print_played_cards(0, player_hand, dealer_hand, player->nickname);
                return 0;
            }
            else
            {
                ft_print_played_cards(1, player_hand, dealer_hand, player->nickname);
                printf("[ O dealer não tem blackjack ]\n");
            }
        }
    }
    else if(dhand[0] == 'K' || dhand[0] == 'J' || dhand[0] == 'Q' || dhand[0] == '1')
    {
        if(ft_calculate_hand_points(dealer_hand, 0 , 0) == 21)
        {
            if(ft_calculate_hand_points(player_hand, 0 , 0) != 21)
            {
                system("clear");
                ft_print_played_cards(0, player_hand, dealer_hand, player->nickname);
                return 1;
            }
            return 0;
        }
        else
        {
            system("clear");
            ft_print_played_cards(1, player_hand, dealer_hand, player->nickname);
            printf("[ O dealer não tem blackjack ]\n");
        }
        
    }
    
    do
    {
        option = ft_ask_play();
        if(option == 1)
        {    
            first_play = 0;
            system("clear");
            ft_player_single_play(deck, player_hand, cards_played, number_decks);
            ft_print_played_cards(1, player_hand, dealer_hand, player->nickname);
            if(ft_calculate_hand_points(player_hand, 0 , 0) > 21)
                return 1;
                
        }
        else if(option == 2 && first_play)
        {
            system("clear");
            if(player->balance >= bet * 2)
            {
                *flag = 2;
                ft_player_single_play(deck, player_hand, cards_played, number_decks);
                ft_print_played_cards(1, player_hand, dealer_hand,player->nickname);
                if(ft_calculate_hand_points(player_hand, 0 , 0) > 21)
                    return 1;
                break;
            }
            ft_print_played_cards(1, player_hand, dealer_hand, player->nickname);
        }
    } while(option != 3);
    return 0;
}

int ft_dealer_play(char ***deck, HandNode *dealer_hand, HandNode *player_hand, int *cards_played, int number_decks, char *nickname)
{
    usleep(50000);
    system("clear"); 
    ft_print_played_cards(0, player_hand, dealer_hand, nickname);

    while (ft_calculate_hand_points(dealer_hand, 1, 0) < 17)
    {
        usleep(700000); 
        system("clear");
        ft_dealer_single_play(deck, dealer_hand, cards_played, number_decks);
        ft_print_played_cards(0, player_hand, dealer_hand, nickname);

        if (ft_calculate_hand_points(dealer_hand, 1, 0) > 21)
            return 1; 
    }
    return 0; 
}



int ft_main_play(char ***deck, int *cards_played, int number_decks, PLAYER *player, double bet)
{
    HandNode *player_hand = ft_create_hand_node(NULL, 0);
    HandNode *dealer_hand = ft_create_hand_node(NULL, 0);

    int option;
    int flag = 1;
    int dealer_bj = 0;

    ft_shuffle_deck(deck, number_decks);

    ft_initial_play(deck, cards_played, number_decks, player_hand, dealer_hand);
    ft_print_played_cards(1, player_hand, dealer_hand, player->nickname);

    if(ft_check_bj_player(player_hand, dealer_hand))
    {
        system("clear");
        ft_print_played_cards(0, player_hand, dealer_hand, player->nickname);
        printf("\n[ BLACKJACK ]");
        ft_clean_input();
        ft_wait_enter(); 
        return 1 * 3;
    }

    if(ft_player_play(deck, player_hand, dealer_hand, cards_played, number_decks, player, bet, &flag))
    {    
        printf("\n[ PERDEU ]");
        ft_clean_input();
        ft_wait_enter();
        return -1 * flag;
    }
    else
    {        
        if(ft_dealer_play(deck, dealer_hand, player_hand, cards_played, number_decks, player->nickname))
        {   
            printf("\n[ GANHOU ]");
            ft_clean_input();
            ft_wait_enter(); 
            return 1 * flag;
        }
        else
        {
            int player_points = ft_calculate_hand_points(player_hand, 0 , 0);
            int dealer_points = ft_calculate_hand_points(dealer_hand, 1, 0);
            if(player_points > dealer_points)
            {   
                printf("\n[ GANHOU ]");
                ft_clean_input();
                ft_wait_enter();
                return 1 * flag;
            }
            else if(player_points < dealer_points)
            {
                printf("\n[ PERDEU ]");
                ft_clean_input();
                ft_wait_enter();
                return -1 * flag;
            }
            else
            {   
                printf("\n[ EMPATE ]");
                ft_clean_input();
                ft_wait_enter();
                return 0;
            }
        }
    }
    ft_free_hand(player_hand);
    ft_free_hand(dealer_hand);
}


double ft_make_bet(PLAYER player)
{
    double tmp;
    int spaces = 34 - (9 + ft_double_length(player.balance));
    printf("╔══════════════════════════════════╗\n");
    printf("║ Digite 0 para sair               ║\n");
    printf("║ 💰 %.2f €", player.balance);
    ft_spaces(spaces);
    printf("║\n");
    printf("╚══════════════════════════════════╝\n");
    printf(" ⛃ Bet: ");
    while (scanf("%lf", &tmp) <= 0 || tmp < 0 || tmp > player.balance)
    {
        printf("[ Valor de aposta inválido ]\n");
        printf(" ⛃ Bet: ");
        ft_clean_input();
    }
    system("clear");
    return tmp;
}

void ft_update_balance(int result, PLAYER *player, double bet)
{
    double amount_to_change = ft_check_bet(result, bet);
    player->balance += amount_to_change;
}

void ft_play(char ***deck, int number_decks)
{
    
    PLAYER jogador;
    int op = ft_player_menu_logic(&jogador);
    int is_guest = 0;

    if(op == 4)
        return;
    else if(op == 3)
        is_guest = 1;


    double aposta;
    int cards_played = 0;
    int exit_flag = 3;
    int option = ft_main_menu(jogador, is_guest);
    if(jogador.balance == 0)
            exit_flag = 4;
        else
            exit_flag = 3;
    while ((option != exit_flag && !is_guest) || (option != exit_flag - 1 && is_guest))
    {
        system("clear");
        
        if (option == 1)
        {
            aposta = ft_make_bet(jogador);
            if (!aposta)
                option = ft_main_menu(jogador, is_guest);
            else
            {
                int result = ft_main_play(deck, &cards_played, number_decks, &jogador, aposta);

                ft_update_balance(result, &jogador, aposta);
                ft_update_stats(&jogador, result, aposta);
                if(!is_guest)
                    ft_save_player(&jogador);
                    
                option = ft_main_menu(jogador, is_guest);
            }
        }
        else if (option == 2)
        {
            if(!is_guest)
            {
                ft_show_stats(jogador);
                ft_clean_input();
                ft_wait_enter();
            }
            else
                ft_add_balance(&jogador);
            option = ft_main_menu(jogador, is_guest);
            
        }
        else if(option == 3)
        {
            ft_add_balance(&jogador);
            option = ft_main_menu(jogador, is_guest);
        } 
        if(jogador.balance == 0)
            exit_flag = 4;
        else
            exit_flag = 3;

        
    }
    
}