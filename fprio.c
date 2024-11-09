// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria ()
{
  struct fprio_t *f;

  f = malloc(sizeof(struct fprio_t));
  if (!f)
   return NULL;

  f->prim = NULL;
  f->num = 0;
  return f;
}


// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f)
{
  struct fpnodo_t *aux1;
  struct fpnodo_t *aux2;
  
  if (!f)
    return NULL;

  if (f->prim)
  { 
    aux1 = f->prim;
    aux2 = aux1;
    while (aux2 != NULL)
    {
      aux2 = aux1->prox;
      free(aux1);
      aux1 = NULL;
    }
  }
  free (f);
  f = NULL;
  return f;
}


// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
  struct fpnodo_t *paiTemp;
  struct fpnodo_t *temp;
  struct fpnodo_t *novo_nodo; 
  
  novo_nodo = malloc(sizeof(struct fpnodo_t));
  
  if (!novo_nodo || !f || !item)
    return -1;
  //verifica se ja tem o item
  temp = f->prim;
  while (temp) 
  {
    if (temp->item == item)
      return -1;
    temp = temp->prox;
  }
    
  // Inicializa o novo nodo
  novo_nodo->item = item;
  novo_nodo->tipo = tipo;
  novo_nodo->prio = prio;
  novo_nodo->prox = NULL;
    
  // Caso a fila esteja vazia, o novo nodo é o primeiro
  if (!f->prim) 
    f->prim = novo_nodo;
  else 
  {
    paiTemp = NULL;
    temp = f->prim;
    while (temp && (temp->prio <= prio)) 
    {
      paiTemp = temp;
      temp = temp->prox;
    }
    if (!paiTemp) 
    {
      // Inserção no início da fila
      novo_nodo->prox = f->prim;
      f->prim = novo_nodo;
    } 
    else 
    {
      // Inserção após paiTemp
      paiTemp->prox = novo_nodo;
      novo_nodo->prox = temp;
    }
  }
  f->num++;
  return f->num;
}


// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
  struct fpnodo_t *temp;
  void *enditem;
  
  if (!f || !f->prim) 
    return NULL;

  *tipo = f->prim->tipo;
  *prio = f->prim->prio;
  enditem = f->prim->item;
  temp= f->prim;
  f->prim = f->prim->prox;
  free(temp);
  f->num--;
  return enditem;
}


// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f)
{
  if (!f)
    return -1;
  return f->num;
}


// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f)
{
  struct fpnodo_t *aux;
  aux = f->prim;
  while (aux)
  {
      printf ("(%d %d)", aux->tipo, aux->prio);
      aux = aux->prox; 
  }
}
