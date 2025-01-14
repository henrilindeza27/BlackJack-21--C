#include "../inc/bj.h"

char *ft_save_nickname(void)
{
    char *nickname = NULL;      
    size_t size = 0;           
    size_t len;              

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

int ft_check_nickname(char *nickname)
{
    FILE *file_players = fopen(file_name, "r");
    if(!file_name)
    {
        printf("Erro a abrir o ficheiro\n");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    int position = -1;
    while (getline(&line, &len, file_players) != -1) 
    {
        ++position;
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ";");
        if(token && !strcmp(token, nickname))
        {    
            free(line);
            fclose(file_players);
            return position;
        }
    }
    free(line);
    fclose(file_players);
    return -1;
}

PLAYER ft_create_player(int is_guest)
{
    PLAYER player;
    int flag = 0;
    char *nickname;

    while(!flag && !is_guest)
    {
        printf("Insira o nickname → ");
        nickname = ft_save_nickname();
        if(ft_check_nickname(nickname) != -1)
            printf("O nickname inserido já existe, insira outro\n");
        else if(!strcmp(nickname, " ") || !strcmp(nickname, "\n") || !strcmp(nickname, "\0"))  
            printf("O nickname não pode estar vazio, insira outro\n");
        else
            flag++;
    }

    if(!is_guest)
    {    
        player.nickname = strdup(nickname);
        free(nickname);
    }
    else
        player.nickname = strdup("Guest");

    player.balance = 1000;
    player.max_lose = 0;
    player.max_win = 0;
    player.total_games = 0;
    player.total_wins = 0;
    player.total_loses = 0;
    player.total_draw = 0;
    player.total_win = 0;
    player.total_lose = 0;

    
    return player;
}

int ft_save_player(PLAYER *player)
{
    FILE *file = fopen(file_name, "r+"); // Abrir em modo de leitura e escrita
    if (!file)
    {
        perror("Erro ao abrir o arquivo para salvar jogador");
        return 0;
    }

    int pos = ft_check_nickname(player->nickname);
    if (pos == -1)
    {
        // Jogador não encontrado, adicionar ao final do arquivo
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s;%.2f;%zu;%zu;%zu;%zu;%.2f;%.2f;%.2f;%.2f\n",
                player->nickname,
                player->balance,
                player->total_games,
                player->total_wins,
                player->total_loses,
                player->total_draw,
                player->max_win,
                player->max_lose,
                player->total_win,
                player->total_lose);
        fclose(file);
    }
    else
    {
        // Jogador encontrado, atualizar dados
        FILE *temp_file = fopen("temp_file.txt", "w");
        if (!temp_file)
        {
            printf("Erro ao criar o ficheiro temporário\n");
            fclose(file);
            return 0;
        }

        char *line = NULL;
        size_t len = 0;
        int current_pos = 0;
        rewind(file);

        while (getline(&line, &len, file) != -1)
        {
            if (current_pos == pos)
            {
                fprintf(temp_file, "%s;%.2f;%zu;%zu;%zu;%zu;%.2f;%.2f;%.2f;%.2f\n",
                    player->nickname,
                    player->balance,
                    player->total_games,
                    player->total_wins,
                    player->total_loses,
                    player->total_draw,
                    player->max_win,
                    player->max_lose,
                    player->total_win,
                    player->total_lose);
            }
            else
                fprintf(temp_file, "%s", line);
            current_pos++;
        }

        free(line);
        fclose(file);
        fclose(temp_file);

        // Substituir o arquivo original pelo temporário
        remove(file_name);
        rename("temp_file.txt", file_name);
    }

    return 1; // Sucesso
}

int ft_load_player(char *nickname, PLAYER *player)
{
    FILE *file_players = fopen(file_name, "r");
    if(!file_name)
    {
        printf("Erro a abrir o ficheiro\n");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file_players) != -1) 
    {
        line[strcspn(line, "\n")] = '\0';

        char *fields[10];
        int field_count = 0;

        char *token = strtok(line, ";");
        while (token && field_count < 10)
        {
            fields[field_count++] = token;
            token = strtok(NULL, ";");
        }

        // Verifica se o nickname corresponde
        if (field_count == 10 && !strcmp(fields[0], nickname))
        {
            player->nickname = strdup(fields[0]); 
            player->balance = atof(fields[1]);
            player->total_games = strtoul(fields[2], NULL, 10);
            player->total_wins = strtoul(fields[3], NULL, 10);
            player->total_loses = strtoul(fields[4], NULL, 10);
            player->total_draw = strtoul(fields[5], NULL, 10);
            player->max_win = atof(fields[6]);
            player->max_lose = atof(fields[7]);
            player->total_win = atof(fields[8]);
            player->total_lose = atof(fields[9]);
            free(line); 
            fclose(file_players);
            return 1; 
        }
    }

    free(line); 
    fclose(file_players);
    printf("Jogador '%s' não encontrado.\n", nickname);
    return 0;
}

int ft_player_menu_logic(PLAYER *player)
{
    int option = ft_player_menu();

    while(option != 4)
    {
        
        if(option == 1)
        {
            if(ft_ask_to_continue() == 2)   
            {   
                system("clear");
                option = ft_player_menu(); 
                continue;
            }
            char user[100];
            ft_clean_input();

            printf("Insira o nickname do player que quer carregar\n");
            printf("→ ");
            fgets(user, sizeof(user), stdin);
            user[strcspn(user, "\n")] = '\0'; 
            
            while(!ft_load_player(user, player))
            {
                printf("→ ");
                scanf("%99s", user);
                ft_clean_input();
            }
            ft_load_bar(10);
            ft_wait_enter();
            break;
        }
        else if(option == 2)
        {
            if(ft_ask_to_continue() == 2)
            {   
                system("clear");
                option = ft_player_menu(); 
                continue;
            }
            ft_clean_input();
            *player = ft_create_player(0);

            ft_save_player(player);
            
            ft_load_bar(10);
        
            ft_wait_enter();
            break;
        }
        else if(option == 3)
        {
            if(ft_ask_to_continue() == 2)
            {   
                system("clear");
                option = ft_player_menu(); 
                continue;
            }
            *player = ft_create_player(1);
            ft_load_bar(10);
            ft_clean_input();
            ft_wait_enter();
            break;
        }
    }
    
    return option;

}


void ft_update_stats(PLAYER *player, int result, double bet, int split_flag, int double_flag)
{
    double amount = 0;
    if(result >= 0)
        amount = ft_check_bet(result, bet, split_flag, double_flag);
    else
        amount += (result * bet);

    player->total_games++;
    if(!amount)
        player->total_draw++;
    else if(amount > 0)
    {
        player->total_wins++;
        player->total_win += amount - bet;
        if(amount > player->max_win)
            player->max_win = amount;
    }
    else
    {
        player->total_loses++;
        player->total_lose += amount;
        if(amount < player->max_lose)
            player->max_lose = amount;
    }
}