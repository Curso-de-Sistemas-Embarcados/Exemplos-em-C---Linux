#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg);

int main(){
  int res;
  pthread_t a_thread;
  void *thread_result;

  res = pthread_create(&a_thread, NULL, thread_function, NULL);
  if (res != 0){
    perror("Não foi possível criar a thread!");
    exit(EXIT_FAILURE);
  }

  sleep(15);

  printf("Cancelando a thread ... \n");

  res = pthread_cancel(a_thread);
  if (res != 0){
    perror("Não foi possível cancelar a thread!");
    exit(EXIT_FAILURE);
  }

  printf("Esperando o fim da execução da thread ... \n");

  res = pthread_join(a_thread,&thread_result);

  if (res != 0){
    perror("Não foi possível juntar as threads!");
    exit(EXIT_FAILURE);
  } 

  exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){

  int i, res;

  res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  if (res != 0){
    perror("Falha na pthread_setcancelstate");
    exit(EXIT_FAILURE);
  }

  res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
  if (res != 0){
    perror("Falha na pthread_setcanceltype");
    exit(EXIT_FAILURE);
  }

  printf("Função thread executando. \n");

  for (i = 0; i < 10; i++){
    printf("Thread em execução (%d) ... \n", i);
    sleep(1); 
  }
  
  pthread_exit(0);
}