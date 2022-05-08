#include <iostream>
#include <semaphore>
#include <random>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in, out = 0;

sem_t full, empty;
pthread_mutex_t mutex;

void* produce(void* arg)
{
  while (1)
  {
    sleep(1);
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    int item = rand() % 100;
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    std::cout << "Produced " << item << std::endl;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }
}

void* consume(void* arg)
{
  while (1)
  {
    sleep(2);
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    std::cout << "Consumed " << item << std::endl;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
}

int main()
{
  pthread_t producer, consumer;

  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);

  pthread_mutex_init(&mutex, nullptr);
  pthread_create(&producer, nullptr, produce, nullptr);
  pthread_create(&consumer, nullptr, consume, nullptr);
  pthread_exit(nullptr);
}
