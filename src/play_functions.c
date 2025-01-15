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

int ft_ask_play(int flag, int can_split, int hand)
{
    int option;

    if(hand == 1)
        puts("[Hand 1]");
    else if(hand == 2)
        puts("[Hand 2]");
    if(flag && can_split)
        printf("1- Hit | 2- Double | 3- Split | 4- Stop \n");
    else if(flag && !can_split)
        printf("1- Hit | 2- Double | 3- Stop \n");
    else
        printf("1- Hit | 2- Stop \n");
    while(scanf("%d", &option) <= 0 || (option < 1 || option > 2 + (can_split + flag)))
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

int ft_player_play(char ***deck, HandNode **player_hand, HandNode *dealer_hand ,int *cards_played, int number_decks, PLAYER *player, double bet, int *flag, double *side_bets, double *side_wins, double *total_bet)
{
    int option;
    char *dhand = dealer_hand->hand[1];
    int flag_show = 0;
    int first_play = 1;
    int can_split = ft_check_split(*player_hand);
    *flag = 1;
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
                player->total_bet += (bet / 2);  
            }
            if(ft_calculate_hand_points(dealer_hand, 0 , 0) == 21)
            {  
                
                ft_print_played_cards(0, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
                return 0;
            }
            else
            {
                ft_print_played_cards(1, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
                printf("[ O dealer não tem blackjack ]\n");
            }
            
        }
        else
        {
            system("clear");
            if(ft_calculate_hand_points(dealer_hand, 0 , 0) == 21)
            {  
                
                ft_print_played_cards(0, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
                return 0;
            }
            else
            {
                ft_print_played_cards(1, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
                printf("[ O dealer não tem blackjack ]\n");
            }
        }
    }
    else if(dhand[0] == 'K' || dhand[0] == 'J' || dhand[0] == 'Q' || dhand[0] == '1')
    {
        if(ft_calculate_hand_points(dealer_hand, 0 , 0) == 21)
        {
            if(ft_calculate_hand_points(*player_hand, 0 , 0) != 21)
            {
                system("clear");
                ft_print_played_cards(0, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
                return 1;
            }
            return 0;
        }
        else
        {
            system("clear");
            ft_print_played_cards(1, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
            printf("[ O dealer não tem blackjack ]\n");
        }
        
    }
    
    do
    {
        option = ft_ask_play(first_play, can_split, 0);
        if(option == 1)
        {    
            first_play = 0;
            can_split = 0;
            system("clear");
            ft_player_single_play(deck, *player_hand, cards_played, number_decks);
            ft_print_played_cards(1, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
            if(ft_calculate_hand_points(*player_hand, 0 , 0) > 21)
                return 1;
                
        }
        else if(option == 2 && first_play)
        {
            system("clear");
            if(player->balance >= bet)
            {
                *flag = 2;
                player->balance -= bet;
                ft_player_single_play(deck, *player_hand, cards_played, number_decks);
                ft_print_played_cards(1, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
                if(ft_calculate_hand_points(*player_hand, 0 , 0) > 21)
                    return 1;
                break;
            }
            ft_print_played_cards(1, *player_hand,  dealer_hand, *player, side_bets, side_wins, bet, *flag, total_bet);
        }
        else if(option == 3 && player->balance >= bet  && can_split)
        {
            first_play = 0;
            can_split = 0;
            player->balance -= bet;
            if(ft_split(deck, player_hand, dealer_hand, cards_played, number_decks, *player, side_bets, side_wins, bet, total_bet) == 2)
                return 1;
            break;
        }
    } while(option != 2 + (first_play + can_split));
    return 0;
}

int ft_dealer_play(char ***deck, HandNode *dealer_hand, HandNode *player_hand, int *cards_played, int number_decks, PLAYER player, double *side_bets, double *side_wins, double bet, int double_flag, double *total_bet)
{
    usleep(50000);
    system("clear"); 
    
    ft_print_played_cards(0, player_hand, dealer_hand, player, side_bets, side_wins, bet, double_flag, total_bet);

    while (ft_calculate_hand_points(dealer_hand, 1, 0) < 17)
    {
        usleep(700000); 
        system("clear");
        ft_dealer_single_play(deck, dealer_hand, cards_played, number_decks);
        ft_print_played_cards(0, player_hand, dealer_hand, player, side_bets, side_wins, bet, double_flag, total_bet);

        if (ft_calculate_hand_points(dealer_hand, 1, 0) > 21)
            return 1; 
    }
    return 0; 
}



int ft_main_play(char ***deck, int *cards_played, int number_decks, PLAYER *player, double bet, int *split_flag, int *double_flag, double *side_bets, double **side_bet_win, double *total_bet)
{
    HandNode *player_hand = ft_create_hand_node(NULL, 0);
    HandNode *dealer_hand = ft_create_hand_node(NULL, 0);

    int option;
    int dealer_bj = 0;
    int flag = 0;
    *total_bet = 0;

    ft_shuffle_deck(deck, number_decks);

    ft_initial_play(deck, cards_played, number_decks, player_hand, dealer_hand);

    if(ft_check_exist_side_bets(side_bets))
        *side_bet_win = ft_check_side_bets_win(side_bets, player, player_hand, dealer_hand);
    else
        *side_bet_win = (double *)calloc(4, sizeof(double));

    
    ft_print_played_cards(1, player_hand, dealer_hand, *player, side_bets, *side_bet_win, bet, *double_flag, total_bet);
    

    if(ft_check_bj_player(player_hand, dealer_hand))
        flag = 3;
    if(flag != 3)
    {    
        if(ft_player_play(deck, &player_hand, dealer_hand, cards_played, number_decks, player, bet, double_flag, side_bets, *side_bet_win, total_bet))
            flag = -1 * (*double_flag);
    }   
           
    if(ft_total_hands(player_hand) == 2)
        *split_flag = 2;
    if(ft_dealer_play(deck, dealer_hand, player_hand, cards_played, number_decks, *player, side_bets, *side_bet_win, bet, *double_flag, total_bet))
    {   
        (*side_bet_win)[3] = ft_check_bust_win(side_bets[3], dealer_hand) + side_bets[3];
        system("clear");
        ft_print_played_cards(0, player_hand, dealer_hand, *player, side_bets, *side_bet_win, bet, *double_flag, total_bet);
        if(flag != -1 * (*double_flag) && flag != 3)
            flag = 1 * (*double_flag) * (*split_flag);
    }
    if(flag != -1 * (*double_flag) && flag != 3 && flag != 1 * (*double_flag) * (*split_flag))
    {    
        int res = ft_check_result(player_hand,dealer_hand, *double_flag);
        ft_free_hand(player_hand);
        ft_free_hand(dealer_hand);
        return(res);
    }

    ft_clean_input();
    ft_wait_enter();
    ft_free_hand(player_hand);
    ft_free_hand(dealer_hand);

    return flag;
}


double ft_make_bet(PLAYER *player)
{
    double tmp;
    int spaces = 34 - (6 + ft_double_length(player->balance));
    printf("+----------------------------------+\n");
    printf("|        APOSTA PRINCIPAL          |\n");
    printf("+----------------------------------+\n");
    printf("| Digite 0 para sair               |\n");
    printf("| 💰 %.2f €", player->balance);
    ft_print_char(spaces, ' ');
    printf("|\n");
    printf("+----------------------------------+\n");
    printf(" ⛃ Bet: ");
    while (scanf("%lf", &tmp) <= 0 || (tmp != 0 && (tmp < 0.2 || tmp > player->balance)))
    {
        printf("[ Valor de aposta inválido ]\n");
        printf(" ⛃ Bet: ");
        ft_clean_input();
    }
    system("clear");
    player->balance -= tmp;
    return tmp;
}

void ft_update_balance(PLAYER *player, int result, double bet, int split_flag, int double_flag, double *side_win, double *total_win)
{
    double amount_to_change = ft_check_bet(result, bet, split_flag, double_flag);
    for(int i = 0; i < 4; i++)
        amount_to_change += side_win[i];
    
    if(amount_to_change > 0)
    {    
        int size = 19 + ft_double_length(amount_to_change);
        printf("+");
        ft_print_char(size, '-');
        printf("+\n");
        printf("|");
        ft_print_char(size, ' ');
        printf("|\n");
        printf("| Total de Ganhos: %.2f", amount_to_change);
        printf(" |\n");
        printf("|");
        ft_print_char(size, ' ');
        printf("|\n");
        printf("+");
        ft_print_char(size, '-');
        printf("+\n");
        ft_wait_enter();
    }
    *total_win = amount_to_change;
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
    int double_flag = 1;
    double total_win;
    double total_bet = 0;
    

    if(jogador.balance == 0)
            exit_flag = 4;
        else
            exit_flag = 3;
    while ((option != exit_flag && !is_guest) || (option != exit_flag - 1 && is_guest))
    {
        system("clear");
        int split_flag = 1;
        if (option == 1)
        {
            aposta = ft_make_bet(&jogador);
            
            if (!aposta)
                option = ft_main_menu(jogador, is_guest);
            else
            {
                double *side_bets = ft_make_side_bet(&jogador);
                double *side_wins = NULL;
                int result = ft_main_play(deck, &cards_played, number_decks, &jogador, aposta, &split_flag, &double_flag, side_bets, &side_wins, &total_bet);

                ft_update_balance(&jogador,result, aposta, split_flag, double_flag, side_wins, &total_win);
                ft_update_stats(&jogador, total_win, total_bet, result);
                free(side_bets);
                free(side_wins);
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
    ft_clear_player(&jogador);
    
}