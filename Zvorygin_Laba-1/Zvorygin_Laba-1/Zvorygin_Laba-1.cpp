#include <stdio.h>
#include <time.h>
#include <Windows.h>

const int N = 1000;//значение показывающие кол-во сгенерированных элементов и диапозон чисел
int mas[N];
int mas1[N];

//заполнение массива рандомными значениями
void randomNumb(FILE* f)
{
    for (int i = 0; i < N; ++i)
    {
        fprintf_s(f, "%d ", 0 + rand() % N);
    }
}

//сортировка пузырьком
void bubleSort()
{
    int temp;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N - 1; ++j)
        {
            if (mas[j] > mas[j + 1])
            {
                temp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = temp;
            }
        }
    }
}

//сортировка Шелла
void shellSort()
{
    int tmp,j;
    for (int step = N / 2; step > 0; step /= 2)
        for (int i = step; i < N; i++)
        {
            tmp = mas[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mas[j - step])
                    mas[j] = mas[j - step];
                else
                    break;
            }
            mas[j] = tmp;
        }
}

//сортировка слиянием
void mergeSort(int i, int j, int mas[], int mas1[]) {
    if (j <= i) {
        return;     
    }
    int mid = (i + j) / 2;


    mergeSort(i, mid, mas, mas1);   
    mergeSort(mid + 1, j, mas, mas1);   

    int pointer_left = i;     
    int pointer_right = mid + 1;        
    int k;     

    for (k = i; k <= j; k++) {
        if (pointer_left == mid + 1) {     
            mas1[k] = mas[pointer_right];
            pointer_right++;
        }
        else if (pointer_right == j + 1) {     
            mas1[k] = mas[pointer_left];
            pointer_left++;
        }
        else if (mas[pointer_left] < mas[pointer_right]) {      
            mas1[k] = mas[pointer_left];
            pointer_left++;
        }
        else {       
            mas1[k] = mas[pointer_right];
            pointer_right++;
        }
    }

    for (k = i; k <= j; k++) {
        mas[k] = mas1[k];
    }
}


int main()
{
    FILE* f = fopen("input.txt", "w+");//создаю файл для записи рандомных значений

    if (f == NULL)
    {
        printf_s("Файл не открылся!");
        return 0;
    }

    randomNumb(f);
    fclose(f);

    FILE* f1 = fopen("input.txt", "r");//открываю файл чтобы скопировать значения в массив

    if (f1 == NULL)
    {
        printf_s("Файл не открылся!");
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        fscanf_s(f1, "%d", &mas[i]);
    }


    //каждый блок отвечает за вычисления времени каждой сортировки

    clock_t start1 = clock();
    bubleSort();
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;


    clock_t start2 = clock();
    shellSort();
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

    clock_t start3 = clock();
    mergeSort(0,N-1,mas,mas1);
    clock_t end3 = clock();
    double seconds3 = (double)(end3 - start3) / CLOCKS_PER_SEC;

    fclose(f1);

    FILE* f3 = fopen("out.txt", "w");

    if (f3 == NULL)
    {
        printf("Файл не открылся!");
        return 0;
    }

    for (int i = 0; i < N; ++i)
    {
        fprintf(f3, "%d\n", mas[i]);
    }

    fclose(f3);


    printf("Time sort %d values - %f\n",N, seconds1);
    printf("Time sort %d values - %f\n", N, seconds2);
    printf("Time sort %d values - %f\n", N, seconds3);
}

