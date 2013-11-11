#include <stdio.h>
#include <pthread.h>


int* arr;
int size;

typedef struct task* task_thread;

struct task
{
	int first;
	int last;
};

void* sort_bubble(void* arg) {
	task_thread t = (task_thread)arg;
	int first = t->first;
	int last = t->first;
//	printf("%d %d\n", first, last);

    int tmp, i, j;
 
    for(i = first; i < last - 1; ++i) // i - номер прохода
    {            
        for(j = first; j < last - 1; ++j) // внутренний цикл прохода
        {     
            if (arr[j + 1] < arr[j]) 
            {
                tmp = arr[j + 1]; 
                arr[j + 1] = arr[j]; 
                arr[j] = tmp;
            }
        }
    }
}

void start_sort() {
	int midle = size / 2;
	pthread_t thr1, thr2;
	task_thread t1 = malloc(sizeof(struct task));
	task_thread t2 = malloc(sizeof(struct task));
	printf("Middle = %d\n", midle);
	t1->first = 0;
	t1->last = midle;
	t2->first = midle;
	t2->last = size;
	int i = pthread_create(&thr1, NULL, &sort_bubble, (void*)t1);
	i = pthread_create(&thr2, NULL, &sort_bubble, (void*)t2);
	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	free(t1);
	free(t2);
}

 void merge(int *dest, int second) {
 	int c1 = 0, c2 = second;
 	for (int i = 0; i < size; i++) {
 		if (c1 <= second && c2 <= size) {
 			dest[i] = arr[c1] > arr[c2] ? arr[c2++] : arr[c1++];
 		}
 		if (c1 > second && c2 < size) {
 			dest[i] = arr[c2++];
 		}
 		if (c1 < second && c2 > size) {
 			dest[i] = arr[c1++];
 		}
 	}
 }


int main(){
        printf("Enter size:");   
	scanf("%d", &size);
	printf("Size = %d\n", size);
        printf("Enter the array:\n");   
      	arr=malloc(sizeof(int) * size);// захватить память под массив
	for (int i=0; i<size; i++){
		scanf("%d", arr + i);
	}
	printf("%s\n");

	start_sort();
	int *final = malloc(sizeof(int) * size);
	merge(final, size / 2);


	for (int i=0; i<size; i++){
		printf("%d ", *(arr + i));
	}
	printf("\n");	
	for (int i=0; i<size; i++){
		printf("%d ", *(final + i));
	}
	printf("\n");
	free(arr);
	free(final);
	return 0;

}


