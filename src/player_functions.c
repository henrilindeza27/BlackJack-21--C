#include "../inc/bj.h"

char *ft_save_nickname(void)
{
    char *nickname = NULL;      
    size_t size = 0;           
    size_t len;              

    printf("Digite o nickname: ");
    len = getline(&nickname, &size, stdin);

    if (len == -1)
    {
        fprintf(stderr, "Erro ao ler o nickname.\n");
        exit(EXIT_FAILURE);
    }

    if (len > 0 && nickname[len - 1] == '\n')
        nickname[len - 1] = '\0';

    return nickname;
}

PLAYER ft_create_player()
{
    PLAYER player;

    player.nickname = ft_save_nickname();

    player.balance = 1000;

    return player;
}

int ft_show_status(PLAYER player)
{
    system("clear");
    int option;
    printf(" 👤 %s\n", player.nickname);
    printf(" 💰 %.2f €\n", player.balance);
    printf(" [1] - JOGAR  [2] - SAIR\n");

    while (scanf("%d", &option) <= 0 || (option < 1 || option > 2))
    {
        system("clear");
        printf("[ Opção inválida inválida ]\n");
        printf(" 👤 %s\n", player.nickname);
        printf(" 💰 %.2f €\n", player.balance);
        printf(" [1] - JOGAR  [2] - SAIR\n");
        ft_clean_input();
    }


    return option;
}