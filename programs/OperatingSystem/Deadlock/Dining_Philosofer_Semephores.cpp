#include <pthread.h> 
#include <semaphore.h> 
#include <iostream>
#include <cstdio.h> 
  
#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phnum + 4) % N 
#define RIGHT (phnum + 1) % N 
using namespace std;
  
int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex; 
sem_t S[N]; 
  
void test(int phnum) { 
  if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) { 
    
    state[phnum] = EATING; 
    sleep(2); 
  
    cout <<"Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1<<endl;
    cout <<"Philosopher %d is Eating\n", phnum + 1<<endl;
    
    sem_post(&S[phnum]); 
  } 
} 
  
// take up chopsticks 
void take_fork(int phnum) { 
  
  sem_wait(&mutex); 
  state[phnum] = HUNGRY; 
  cout<< "Philosopher %d is Hungry\n", phnum + 1<<endl; 
  
  test(phnum); 
  sem_post(&mutex); 
  
  sem_wait(&S[phnum]); 
  sleep(1); 
} 
  
// put down chopsticks 
void put_fork(int phnum){
  
  sem_wait(&mutex); 
  state[phnum] = THINKING;   

  cout << "Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1<<endl;
  cout<<"Philosopher %d is thinking\n", phnum + 1<<endl;
  
  test(LEFT); 
  test(RIGHT); 
  
  sem_post(&mutex); 
} 

void* philospher(void* num) { 
  
  while (1) { 
    int* i = num; 
    sleep(1); 
    take_fork(*i); 
    sleep(0); 
    put_fork(*i); 
  } 
} 
  
int main() { 
  
  int i; 
  pthread_t thread_id[N]; 
  
  sem_init(&mutex, 0, 1); 
  
  for (i = 0; i < N; i++) {sem_init(&S[i], 0, 0);}
  
  for (i = 0; i < N; i++) { 
    
    pthread_create(&thread_id[i], NULL,philospher, &phil[i]); 
    cout << "Philosopher %d is thinking\n"<<endl; 
  } 
  
  for (i = 0; i < N; i++){
    pthread_join(thread_id[i], NULL); 
  }
  
} 
