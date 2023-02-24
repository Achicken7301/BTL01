#include "import.h"

// Get postition for each line from file, each element is one line
int *get_pos(string file_array_string)
{
    // 3 is the number of line in file
    string line;
    ifstream myfile(file_array_string);
    int *pos_line = new int(3);
    int i = 0;
    if (myfile.is_open())
    {
        int pos = myfile.tellg();
        while (getline(myfile, line))
        {
            pos_line[i] = pos;
            i++;
            pos = myfile.tellg();
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
    return pos_line;
}
// Import load file and read data from each line as string type
void import(string file_array_string, int *knight_address[], int *event[])
{
    string line;
    ifstream myfile(file_array_string);
    int *pos_line = get_pos(file_array_string);
    if (myfile.is_open())
    {
        int pos = myfile.tellg();
        while (getline(myfile, line))
        {
            if (pos == pos_line[0])
            {
                extract_line(line, knight_address, 5);
            }
            if (pos == pos_line[1])
            {
                int num_of_event = countFreq(line, " ") + 1;
                extract_line(line, event, num_of_event);
                // relocate(event,num_of_event);
            }
            pos = myfile.tellg(); // end pos in a line
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}
// From each line convert to int and save into the address of variable
void extract_line(string line, int *array_address[], int array_length)
{
    int length = line.length();
    int i = 0;
    // Generate variable tmp to store substring fron line string
    int line_blank;
    string line_num;

    // 5 is element value of kngiht's propertise
    while (i < array_length)
    {
        int line_blank = line.find(" ");
        string line_num;
        line_num = line.substr(0, line_blank);
        *array_address[i] = stoi(line_num);
        i++;
        line = line.substr(line_blank + 1, length - line_blank);
    }
}
// Caculate the num of element from file (just in event)
int countFreq(string array_string, string array_char)
{
    int length = array_string.length();
    string tmp = array_string;
    int res = 0;
    int found = array_string.find(array_char);
    for (int i = 0; i <= length; i++)
    {
        if (found != -1)
        {
            res++;
            tmp = tmp.substr(found + 1, array_string.length() - (found + 1));
            found = tmp.find(array_char);
        }
        else
        {
            break;
        }
    }
    return res;
}
// Resize the array length (but not work)
void relocate(int *arr[], int arr_keep)
{
    // Delete last specific number of array
    int *newArr = new int(arr_keep);
    for (int i = 0; i < arr_keep; i++)
    {
        newArr[i] = *arr[i];
    }
    delete arr;
    arr = &newArr;
}
