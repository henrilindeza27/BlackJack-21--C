#include "../inc/bj.h"
char ft_get_naipe(char *card)
{
    return card[strlen(card) - 1];
}

int ft_check_red_or_black(char *player_card)
{
    char naipe = ft_get_naipe(player_card);
    if(naipe == 'c' || naipe == 'o')
        return 1;
    return 0;
}

int ft_check_two_naipes_color(char *card1, char *card2)
{
    if(ft_check_red_or_black(card1) && ft_check_red_or_black(card2))
        return 1;
    else if(!ft_check_red_or_black(card1) && !ft_check_red_or_black(card2))
        return 1;
    return 0;
}

int ft_check_same_naipe(char **player_hand, char *dealer_card)
{
    if((ft_get_naipe(player_hand[0]) == ft_get_naipe(player_hand[1])) && (ft_get_naipe(player_hand[0]) == ft_get_naipe(dealer_card)))
        return 1;
    return 0;
}

int ft_check_same_value(char **player_hand, char *dealer_card)
{
    if(ft_card_value(player_hand[0]) == ft_card_value(player_hand[1]) && ft_card_value(player_hand[0]) == ft_card_value(dealer_card))
        return 1;
    return 0;
}

int ft_check_sequence(char **player_hand, char *dealer_card)
{
    int flag_d = 0;
    int flag_p1 = 0;
    int flag_p2 = 0;

    if(dealer_card[0] == 'K')
        flag_d = 3;
    else if(dealer_card[0] == 'J')
        flag_d = 2;
    else if(dealer_card[0] == 'Q')
        flag_d = 1;
    else if(dealer_card[0] == 'A')
        flag_d = -10;
    if(player_hand[0][0] == 'K')
        flag_p1 = 3;
    else if(player_hand[0][0] == 'J')
        flag_p1 = 2;
    else if(player_hand[0][0] == 'Q')
        flag_p1 = 1;
    else if(player_hand[0][0] == 'A')
        flag_p1 = -10;
    if(player_hand[1][0] == 'K')
        flag_p2 = 3;
    else if(player_hand[1][0] == 'J')
        flag_p2 = 2;
    else if(player_hand[1][0] == 'Q')
        flag_p2 = 1;
    else if(player_hand[1][0] == 'A')
        flag_p2 = -10;

    int values[3] = {ft_card_value(dealer_card)+flag_d, ft_card_value(player_hand[0])+flag_p1, ft_card_value(player_hand[1])+flag_p2};

    for (int i = 0; i < 2; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (values[i] > values[j])
            {
                int temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }

    return (values[1] == values[0] + 1 && values[2] == values[1] + 1);
}

int ft_hot_3(HandNode *player_hand, HandNode *dealer_hand)
{
    int tree_cards_value = ft_calculate_hand_points(player_hand,0,0) + ft_card_value(dealer_hand->hand[1]);

    if(tree_cards_value == 19)
        return 1;
    else if(tree_cards_value == 20)
        return 2;
    else if(tree_cards_value == 21)
    {
        if(!ft_check_same_naipe(player_hand->hand, dealer_hand->hand[1]))
            return 3;
        else
            return 4;
    }
    else if(ft_card_value(dealer_hand->hand[1]) == 7 && ft_card_value(player_hand->hand[1]) == 7 && ft_card_value(player_hand->hand[0]) == 7)
        return 5;
    return 0;
}

int ft_pair(char **player_hand)
{
    if(!strcmp(player_hand[0], player_hand[1]))
        return 1;
    else if(!strncmp(player_hand[0], player_hand[1], 1) &&  ft_check_two_naipes_color(player_hand[0], player_hand[1]))
        return 2;
    else if(!strncmp(player_hand[0], player_hand[1], 1) &&  !ft_check_two_naipes_color(player_hand[0], player_hand[1]))
        return 3;
    return 0;
}


int ft_21_plus_3(char **player_hand, char *dealer_card)
{
    if(ft_check_same_value(player_hand,dealer_card) && ft_check_same_naipe(player_hand,dealer_card))
        return 1;
    else if(ft_check_sequence(player_hand, dealer_card) && ft_check_same_naipe(player_hand,dealer_card))
        return 2;
    else if(ft_check_same_value(player_hand,dealer_card) && !ft_check_same_naipe(player_hand,dealer_card))
        return 3;
    else if(ft_check_sequence(player_hand, dealer_card) && !ft_check_same_naipe(player_hand,dealer_card))
        return 4;
    else if(ft_check_same_naipe(player_hand, dealer_card))
        return 5;
    return 0;
    
}

int ft_bust_it(HandNode *dealer_hand)
{
    if(ft_calculate_hand_points(dealer_hand, 1, 0) <= 21)
        return 0;
    
    int hand_size = dealer_hand->size_hand;

    if(hand_size == 3)
        return 1;
    else if(hand_size == 4)
        return 2;
    else if(hand_size == 5)
        return 3;
    else if(hand_size == 6)
        return 4;
    else if(hand_size == 7)
        return 5;
    else if(hand_size >= 8)
        return 6;
}


double *ft_make_side_bet(PLAYER *player)
{
    double tmp;
    double *bets = (double *)malloc(4 * sizeof(double));
    
    
    for(int i = 0; i < 4; i++)
    {
        int spaces = 34 - (6 + ft_double_length(player->balance));
        system("clear");
        printf("+----------------------------------+\n");
        printf("|             SIDE BETS            |\n");
        printf("+----------------------------------+\n");
        printf("| Digite 0 para sair               |\n");
        printf("| 💰 %.2f €", player->balance);
        ft_print_char(spaces, ' ');
        printf("|\n");
        printf("+----------------------------------+\n");
        if(i == 0)
            printf(" ⛃ [HOT 3]: ");
        else if(i == 1)
            printf(" ⛃ [PERFECT PAIR]: ");
        else if(i == 2)
            printf(" ⛃ [21 + 3]: ");
        else if(i == 3)
            printf(" ⛃ [BUST IT]: ");
        while (scanf("%lf", &tmp) <= 0 || tmp < 0 || tmp > player->balance)
        {
            printf("[ Valor de aposta inválido ]\n");
            if(i == 0)
            printf(" ⛃ [HOT 3]: ");
            else if(i == 1)
                printf(" ⛃ [PERFECT PAIR]: ");
            else if(i == 2)
                printf(" ⛃ [21 + 3]: ");
            else if(i == 3)
                printf(" ⛃ [BUST IT]: ");
            ft_clean_input();
        }
        bets[i] = tmp;
        player->balance -= tmp;
        
    }

    return bets;
}

double ft_check_hot3_win(double bet, HandNode *player, HandNode *dealer)
{
    int result = ft_hot_3(player, dealer);
    if(result == 1)
        return (bet * 2);
    else if(result == 2)
        return (bet * 3);
    else if(result == 3)
        return (bet * 5);
    else if(result == 4)
        return (bet * 21);
    else if(result == 5)
        return (bet * 101);
    return 0;
}

double ft_check_ppair_win(double bet, char **player_hand)
{
    int result = ft_pair(player_hand);
    if(result == 1)
        return (bet * 26);
    else if(result == 2)
        return (bet * 13);
    else if(result == 3)
        return (bet * 7);
    return 0;
}

double ft_check_21_plus3_win(double bet, char **player_hand, char *dealer_card)
{
    int result = ft_21_plus_3(player_hand, dealer_card);
    if(result == 1)
        return (bet * 101);
    else if(result == 2)
        return (bet * 41);
    else if(result == 3)
        return (bet * 31);
    else if(result == 4)
        return (bet * 11);
    else if(result == 5)
        return (bet * 6);
    return 0;
}

double ft_check_bust_win(double bet, HandNode *dealer)
{
    int result = ft_bust_it(dealer);
    if(result == 1)
        return (bet * 2);
    else if(result == 2)
        return (bet * 3);
    else if(result == 3)
        return (bet * 10);
    else if(result == 4)
        return (bet * 51);
    else if(result == 5)
        return (bet * 101);
    else if(result == 6)
        return (bet * 251);
    return 0;
}

double *ft_check_side_bets_win(double *bets, PLAYER *player, HandNode *player_hand, HandNode *dealer_hand)
{
    double *side_wins = (double *)malloc(4 * sizeof(double));
    if(!side_wins)
        return 0;
    
    if(bets[0] != 0)
        side_wins[0] = ft_check_hot3_win(bets[0], player_hand, dealer_hand);
    if(bets[1] != 0)
        side_wins[1] = ft_check_ppair_win(bets[1], player_hand->hand);
    if(bets[2] != 0)
        side_wins[2] = ft_check_21_plus3_win(bets[2], player_hand->hand, dealer_hand->hand[1]);
        
    side_wins[3] = 0;

    
    return side_wins;
}

int ft_check_exist_side_bets(double *sidebets)
{
    int flag = 0;
    for(int i = 0; i < 4; i++)
    {   
        if(sidebets[i] > 0)
            flag = 1;
    } 
    return flag;
    
}