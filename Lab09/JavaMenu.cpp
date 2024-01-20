#include "JavaMenu.h"
#include <iostream>
#include <omp.h>

JNIEXPORT jdouble JNICALL Java_JavaMenu_calculateSTDDev(JNIEnv* env, jobject caller, jintArray arr)
{
    // variables from java and for calculation
    int numN = env->GetArrayLength(arr);
    jint* numbers = (env)->GetIntArrayElements(arr, NULL);
    float sum = 0;
    double mean;
    
    // loop to calculate the mean
    int numProcs = 1;
# pragma omp parallel
        numProcs = omp_get_num_procs();
        //omp_set_num_threads(numProcs / 2);


#pragma omp parallel for reduction(+: sum)
        for (int index = 0; index < numN; index++)
        {
            sum += numbers[index];
        }

        //omp_set_num_threads(1);
#pragma omp barrier
        mean = sum / numN;
    // release array return mean
    env->ReleaseIntArrayElements(arr, numbers, 0);
    return mean;
}

JNIEXPORT jdouble JNICALL Java_JavaMenu_calculateMean(JNIEnv* env, jobject caller, jintArray arr)
{
    // variables from java and for calculation
    int numN = env->GetArrayLength(arr);
    jint* numbers = (env)->GetIntArrayElements(arr, NULL);
    float sum = 0;
    double mean;
    double stanDev = 0;


    // loop to calculate the mean
    int numProcs = 1;
# pragma omp parallel
    numProcs = omp_get_num_procs();
  //  omp_set_num_threads(numProcs/2);

    // loop to calculate the mean
#pragma omp parallel for reduction(+: sum)
    //omp_set_num_threads(1);
    for (int index = 0; index < numN; index++)
    {
        sum += numbers[index];
    }
#pragma omp barrier
    mean = sum / numN;

#pragma omp parallel for reduction(+: stanDev)
    // loop to calculate the sandard deviation
    for (int index = 0; index < numN; index++)
    {
        stanDev += pow((numbers[index] - mean), 2);
    }
#pragma omp barrier
    stanDev = sqrt(stanDev / numN);

    // release array return standard deviation
    env->ReleaseIntArrayElements(arr, numbers, 0);
    return stanDev;
}