#include "../inc/bj.h"


int main()
{
    int N = 1;  

    ft_initial_banner();
    char ***decks = ft_creat_full_deck(N);
    
    ft_play(decks, N);
    ft_free_deck(decks, N);

    return 0;
}