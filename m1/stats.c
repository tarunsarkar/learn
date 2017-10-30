/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file stats.c
 * @brief This file contains processing and printing of statistics of an unsigned
 * char array list.
 *
 * <Add Extended Description Here>
 *
 * @author Tarun Kumar Sarkar
 * @date 21-Oct-2017
 *
 */



#include <stdio.h>
#include <string.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)

void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  /* Other Variable Declarations Go Here */
  /* Statistics and Printing Functions Go Here */
  print_array(test, SIZE);
  sort_array(test, SIZE);
  print_statistics(test, SIZE);
}

/* Add other Implementation File Code Here */

void print_array(unsigned char array[], int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    printf("Index %d, Value %d\n", i, array[i]);
  }
}

void sort_array(unsigned char array[], int len) {
//  unsigned char newarray[SIZE];
//  strcpy(newarray, array);
  quicksort(array, 0, len -1);
}

void quicksort(unsigned char array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quicksort(array, low, pi-1);
    quicksort(array, pi+1, high);
  }
}

int partition(unsigned char array[], int low, int high) {
  unsigned char pivot = array[high];
  int i = low - 1;
  int j = low;
  for (j=low; j<high; j++) {
    if (array[j] < pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  i++;
  swap(&array[i],&array[high]);
  return i;

}

void swap(unsigned char *var1, unsigned char *var2) {
  unsigned char temp = *var1;
  *var1 = *var2;
  *var2 = temp;
}

float find_median(unsigned char array[], int len) {
  float median = 0.0;
  if (0 == len % 2) {
    median = (array[len / 2 + 1] + array[len / 2]) / 2.0;
  }
  else {
    median = array[len / 2];
  }
  return median;
}

float find_mean(unsigned char array[], int len) {
  float total = 0.0;
  int i = 0;
  for (i = 0; i< len; i++) {
    total = total + array[i];
  }
  return total / len;
}

unsigned char find_maximum(unsigned char array[], int len) {
  unsigned char max = array[0];
  int i = 0;
  for (i = 0; i< len; i++) {
    if (max < array[i]) {
      max = array[i];
    }
  }
  return max;
}

unsigned char find_minimum(unsigned char array[], int len) {
  unsigned char min = array[0];
  int i = 0;
  for (i = 0; i< len; i++) {
    if (min > array[i]) {
      min = array[i];
    }
  }
  return min;
}

void print_statistics(unsigned char array[], int len) {
  float min = find_minimum(array, len);
  printf("Min %f\n", min);
  float max = find_maximum(array, len);
  printf("Max %f\n", max);
  float mean = find_mean(array, len);
  printf("Mean %f\n", mean);
  float median = find_median(array, len);
  printf("Median %f\n", median);
}
