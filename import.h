#ifndef __IMPORT_H__
#define __IMPORT_H__

#include "knight.h"
#include "main.h"


//
int* get_pos(string file_array_string);
void import(string file_array_string, int *knight_address[], int *event[],string *packet_address[]);
void extract_line_num(string line, int *array_address[],int array_length,string delimerter);
int countFreq(string array_string, string array_char);
void extract_line_string(string line, string *array_address[], int array_length,string delimeter);
int* get_item(string file_packet,int event);




#endif // IMPORT_H