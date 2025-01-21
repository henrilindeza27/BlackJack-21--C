# Jogo de Blackjack

Bem-vindo ao meu jogo de Blackjack! Este projeto foi desenvolvido em C e permite que jogues Blackjack contra um dealer, com várias funcionalidades interessantes, como apostas laterais e gestão de jogadores.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

- **inc/**: Contém os ficheiros de cabeçalho.
- **src/**: Contém os ficheiros de código fonte.
- **users/**: Contém os dados dos jogadores.
- **Makefile**: Script para compilar o projeto.

## Como Compilar e Executar

Para compilar o jogo, abre o terminal e navega até ao diretório do projeto. Em seguida, executa o comando:
```sh
make exec
```
ou então:
```sh
make
```
```sh
./blackjack
```
## Funcionalidades do Jogo

- **Gestão de Jogadores**: Podes criar, carregar e guardar jogadores.
- **Apostas Laterais**: O jogo suporta várias apostas laterais, como HOT 3, PERFECT PAIR, 21 + 3 e BUST IT.
- **Estatísticas do Jogador**: O jogo exibe estatísticas detalhadas do jogador, como total de jogos, vitórias, apostas e ganhos.
- **Interface de Jogo**: Uma interface de texto simples e intuitiva para jogar Blackjack contra o dealer.

## Como Jogar

1. **Menu Principal**: Ao iniciar o jogo, verás o menu principal onde podes escolher entre criar um novo jogador, carregar um jogador existente ou jogar como convidado.
2. **Fazer Apostas**: Após escolheres ou criares um jogador, podes fazer as tuas apostas.
3. **Jogar**: Joga as tuas cartas contra o dealer, tentando chegar o mais próximo possível de 21 pontos sem ultrapassar.
4. **Apostas Laterais**: Além da aposta principal, podes fazer apostas laterais para aumentar as tuas chances de ganhar.
5. **Estatísticas**: No final de cada jogo, podes ver as tuas estatísticas e decidir se queres continuar a jogar ou sair.


## OFF TOPIC
-**Lista de afazeres**
- [x] Funcionalidade do split 
- [x] Interface melhor
- [x] Carregar user através de um ficheiro
- [x] Guardar status do user no ficheiro
- [x] Menu
- [x] Mostrar status
- [x] Adiconar saldo caso chegue ao 0
- [x] Fazer seguro se o dealer tiver um Às e verificar bj
- [x] Se o dealer tiver um 10 verificar se tem bj
- [x] Side bets
- [x] Resolver o erro de atualizar o saldo no split
- [x] Dar fix aos status
- [x] Dar fix a leaks
- [x] Colocar limite minimo de bet (0.2)
- [x] Quando for a carregar user mostrar lista de useres existentes
- [x] Adicionar no menu principal uma opção para sair da conta
- [ ] Adicionar opção de eliminar conta
