#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_STUDENTS 100

#define DEFAULT_M 10
#define DEFAULT_N 3
#define DEFAULT_R1 3
#define DEFAULT_R2 4
#define DEFAULT_R3 5

int M, N, r1, r2, r3;
sem_t sem_auditorium;
pthread_mutex_t mutex_professor;
int students_finished = 0;

void* student_thread(void* param) {
    int student_id = *(int*)param;
    printf("Student %d arrives.\n", student_id);

    sem_wait(&sem_auditorium);
    printf("Student %d enters the auditorium.\n", student_id);

    int prep_time = rand() % 5 + 1;
    sleep(prep_time);

    pthread_mutex_lock(&mutex_professor);
    printf("Student %d starts the exam.\n", student_id);

    int exam_time = rand() % 4;
    if (exam_time == 0) {
        printf("Student %d leaves without answering.\n", student_id);
    } else {
        sleep(exam_time);
        int grade = rand() % 4 + 2;
        printf("Student %d finishes exam. Grade: %d\n", student_id, grade);
    }

    pthread_mutex_unlock(&mutex_professor);
    sem_post(&sem_auditorium);
    students_finished++;
    free(param); 
	return NULL;
}

int main() {
    srand(time(NULL));
	printf("enter M: ");
    scanf("%d", &M); if (M <= 0) M = DEFAULT_M;

    printf("enter N:");
    scanf("%d", &N); if (N <= 0) N = DEFAULT_N;

    printf("enter: r1: ");
    scanf("%d", &r1); if (r1 <= 0) r1 = DEFAULT_R1;

    printf("enter r2: ");
    scanf("%d", &r2); if (r2 <= 0) r2 = DEFAULT_R2;

    printf("enter r3: ");
    scanf("%d", &r3); if (r3 <= 0) r3 = DEFAULT_R3;	
    
	sem_init(&sem_auditorium, 0, N);
    pthread_mutex_init(&mutex_professor, NULL);

    pthread_t students[MAX_STUDENTS];
    for (int i = 0; i < M; i++) {
        int *student_id = (int*)malloc(sizeof(int)); 
        *student_id = i + 1;
        pthread_create(&students[i], NULL, student_thread, student_id);
        sleep(rand() % r1 + 1);
    }

    while (students_finished < M) sleep(1);

    sem_destroy(&sem_auditorium);
    pthread_mutex_destroy(&mutex_professor);
    return 0;
}
