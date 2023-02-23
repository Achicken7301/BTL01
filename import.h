#ifndef __IMPORT_H__
#define __IMPORT_H__

#include "knight.h"

void extract_line(string line, int *array_address[],int array_length);
void import(string file_path, int *knight_address[], int *event[]);
int countFreq(string array_string, string array_char);
void relocate(int* arr[],int arr_keep);
int* get_pos(string file_array_string);


#endif // IMPORT_H