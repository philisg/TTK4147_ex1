#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <x86intrin.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>


void test1(){
    int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);


    for(int i = 0; i < 10*1000*1000; i++){
        unsigned long t1 = __rdtsc();
        unsigned long t2 = __rdtsc();

        int ns = (int)((t2-t1)*1000.0/2659.829);

        if (ns >=0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }
}

void test2(){
    int ns_max = 800;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);

    struct timespec t1;
    struct timespec t2;


    for(int i = 0; i < 10*1000*1000; i++){
        
        clock_gettime(CLOCK_MONOTONIC, &t1);
        sched_yield();
        clock_gettime(CLOCK_MONOTONIC, &t2);


        int ns = (int)(t2.tv_nsec-t1.tv_nsec);

        if (ns >=0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }
}

void test3(){
    int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);

    struct tms cpu_times;
    clock_t t1;
    clock_t t2;

    int one_second = sysconf(_SC_CLK_TCK);


    for(int i = 0; i < 10*1000*1000; i++){
        
        t1 = times(&cpu_times);
        t2 = times(&cpu_times);



        int ns = (int)((double)(t2-t1)* 1e9 / one_second);

        if (ns >=0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }
}

int main(){
    //test1();
    test2();
    //test3();
}