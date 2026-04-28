#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0;
int out = 0;

sem_t empty;   // 빈 슬롯 개수
sem_t full;    // 채워진 슬롯 개수
pthread_mutex_t lock;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {

        sem_wait(&empty);              // (1)
        pthread_mutex_lock(&lock);     // (2)

        buffer[in] = i;                // (3)
        in = (in + 1) % SIZE;          // (4)

        printf("Produced %d\n", i);    // (5)

        pthread_mutex_unlock(&lock);   // (6)
        sem_post(&full);               // (7)
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {

        sem_wait(&full);               // (8)
        pthread_mutex_lock(&lock);     // (9)

        int val = buffer[out];         // (10)
        out = (out + 1) % SIZE;        // (11)

        printf("Consumed %d\n", val);  // (12)

        pthread_mutex_unlock(&lock);   // (13)
        sem_post(&empty);              // (14)
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, SIZE);  // (15)
    sem_init(&full, 0, 0);      // (16)
    pthread_mutex_init(&lock, NULL); // (17)

    pthread_create(&p, NULL, producer, NULL); // (18)
    pthread_create(&c, NULL, consumer, NULL); // (19)

    pthread_join(p, NULL); // (20)
    pthread_join(c, NULL); // (21)

    return 0;
}