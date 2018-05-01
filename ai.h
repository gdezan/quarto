#ifndef ai_H_
#define ai_H_

int aiPlayFirst();      // função principal para jogar o jogo contra a IA (IA joga primeiro)
int aiPlaySecond();     // função principal para jogar o jogo contra a IA (jogador joga primeiro)
int aiChooseNumber();   // retorna um número para o jogador posicionar
int aiPlace(int ans);   // retorna a posição da peça escolhida pelo jogador

#endif