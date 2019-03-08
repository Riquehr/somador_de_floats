
/* Demonstracao de maquina de estados */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Maquina de estados:
 * Detecta se existe ao menos um numero inteiro na linha inserida */

int eh_digito(char c)
{
  if ((c >= '0') && (c <= '9')) return 1;
  else return 0;
}
int eh_espaco(char c){
  if (c==' ' || c=='\0') return 1;
  else return 0;
}
int eh_ponto(char c){
  if (c=='.') return 1;
  else return 0;
}

typedef struct {
  int estado_atual;
} fsm, *Fsm; /* fsm = finite state machine */
float soma;
int opera_fsm(void *this_fsm, char entrada) {
  Fsm maquina = (Fsm) this_fsm;
  // if(entrada=='\0')printf("Avisa");
  // printf("Entrada: %c\tEstado: %d\n", entrada, maquina->estado_atual);
  switch (maquina->estado_atual) {
    /*Comecou o programa*/
    case 0:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 2;
      }
      if(!eh_digito(entrada)){
        maquina->estado_atual=1;
      }
      break;
    case 1:
      if (eh_espaco(entrada)) {
        maquina->estado_atual = 2;
      }
      break;
    case 2:
      if(!eh_espaco(entrada)){
        maquina->estado_atual = 1;
      }
      if(eh_digito(entrada)){
        maquina->estado_atual = 2;
      }
      if(eh_espaco(entrada)){
        maquina->estado_atual = 4; /*Somar Numero*/
      }
      if(eh_ponto(entrada)){
        maquina->estado_atual = 3;
      }
      if(!eh_digito(entrada) && !eh_ponto(entrada) && !eh_espaco(entrada)){
        // printf("Aqui");
        maquina->estado_atual = 1;
      }
      break;
    case 3:
      if(!eh_espaco(entrada)){
        maquina->estado_atual = 1;
      }
      if(eh_digito(entrada)){
        maquina->estado_atual = 3;
      }
      if(eh_espaco(entrada)){
        // printf("aquiespaco");
        maquina->estado_atual = 4;
      }
      if(!eh_digito(entrada) && !eh_espaco(entrada)){
        maquina->estado_atual = 1;
      }
      break;
    case 4:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 2;
      }
      if(!eh_digito(entrada)){
        maquina->estado_atual=1;
      }
      break;
  }
  return (maquina->estado_atual);
}

int main() {
  char buffer_in[300];
  int pointer;
  soma=0.0;
  int achei_inteiro;
  char c;
  for (int i=0; i<100; i++) buffer_in[i] = '\0';
  char numeroASomar[300];
  pointer = 0;
  do {
    c=getchar();
    buffer_in[pointer++] = c;
  } while (c != '\n');
  int j=0;
  fsm maquina;
  maquina.estado_atual = 0;
  int apontador_digito1=-1;
  int apontador_ultimoDigito=-1;
  pointer = 0;
  int final= 0;
  int numerocorrente=0;


  while (buffer_in[pointer] != '\0') {
    // if(buffer_in[pointer]=='\n')printf("fff");

    if(final==1){
      opera_fsm((void*) (&maquina), ' ');
      // printf("entrou no final");
      pointer++;
    }
      else
        opera_fsm((void*) (&maquina), buffer_in[pointer]);

    if (maquina.estado_atual == 2 && numerocorrente==0){
      apontador_digito1 = pointer;
      numerocorrente=1;
    }

    if(maquina.estado_atual == 4){
      apontador_ultimoDigito = pointer-1;
      // printf("Apontador1 %d Apontador2 %d",apontador_digito1,apontador_ultimoDigito);
      for(int i=apontador_digito1;i<=apontador_ultimoDigito;i++){
        numeroASomar[j] = buffer_in[i];
        j++;
      }
      // printf("\nNumero: %s\n",numeroASomar);
      soma = soma + atof(numeroASomar);
      memset(numeroASomar,0,strlen(numeroASomar));
      apontador_digito1=-1;
      numerocorrente=0;
      j=0;
    }

    // printf("Entrada: %c\tEstado: %d\n", buffer_in[pointer], maquina.estado_atual);
    if(buffer_in[pointer+1] != '\0' && buffer_in[pointer + 1] !='\n' ){
      pointer++;
      if (maquina.estado_atual == 1 )numerocorrente=0;
    }else{
      final=1;
    }
  }




  printf("%g\n",soma);
  return 0;
}
