#include "import.h"

// Get postition for each line from file, each element is one line
int *get_pos(string file_array_string)
{
    // 3 is the number of line in file
    string line;
    ifstream myfile(file_array_string);
    int *pos_line = new (nothrow) int;
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
// Import load file and read line from each line as string type
void import(string file_array_string, int *knight_address[], int *event[], string *packet_address[])
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
                extract_line_num(line, knight_address, 5, " ");
            }
            if (pos == pos_line[1])
            {
                int num_of_event = countFreq(line, " ") + 1;
                extract_line_num(line, event, num_of_event, " ");
                // relocate(event,num_of_event);
            }
            if (pos == pos_line[2])
            {
                extract_line_string(line, packet_address, 3, ",");
            }
            pos = myfile.tellg(); // end pos in a line
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}
// From each line convert to int and save into the address of variable
void extract_line_num(string line, int *array_address[], int array_length, string delimeter)
{
    int length = line.length();
    int i = 0;
    // Generate variable tmp to store substring fron line string
    int line_blank;
    string line_num;

    // 5 is element value of kngiht's propertise
    while (i < array_length)
    {
        int line_blank = line.find(delimeter);
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
void extract_line_string(string line, string *array_address[], int array_length, string delimeter)
{
    int length = line.length();
    int i = 0;
    // Generate variable tmp to store substring fron line string
    int line_blank;
    string line_num;

    // 5 is element value of kngiht's propertise
    while (i < array_length)
    {
        int line_blank = line.find(delimeter);
        string line_num;
        line_num = line.substr(0, line_blank);
        *array_address[i] = line_num;
        i++;
        line = line.substr(line_blank + 1, length - line_blank);
    }
}
int *get_item(string file_packet, int event)
{
    // HP increase,Remedy,Maidenkiss,Phoenix down
    int *item = new int[4];
    *item = 0;
    *(item + 1) = 0;
    *(item + 2) = 0;
    *(item + 3) = 0;
    int *pos_line = get_pos(file_packet);
    string line;
    ifstream myfile(file_packet);
    int row_item;
    int num_merlin;
    if (myfile.is_open())
    {
        int pos = myfile.tellg();
        while (getline(myfile, line))
        {
            switch (event)
            {
            case MUSH_GHOST:

                break;
            case ASCLEPIUS:
            if (pos>pos_line[1])
            {
                if (countFreq(line, "16")>=1)
                {
                    *(item + 1) += countFreq(line, "16");
                }
                if (countFreq(line, "17")>=1)
                {
                    *(item + 2) += countFreq(line, "17");
                }
                if (countFreq(line, "18")>=1)
                {
                    *(item + 3) += countFreq(line, "18");
                }
            }
                break;
            case MERLIN:
                for (int i = 0; i < line.length(); i++)
                {
                    line[i] = tolower(line[i]);
                }
                num_merlin = countFreq(line, "m") + countFreq(line, "e") + countFreq(line, "r") + countFreq(line, "l") + countFreq(line, "i") + countFreq(line, "n");
                // num_merlin=6 that mean in string have full character of merlin
                if (num_merlin >= 6)
                {
                    *item += 2;
                    if (countFreq(line, "merlin") == 1 || countFreq(line, "Merlin") == 1)
                    {
                        *item += 1;
                    }
                }
                break;
            default:
                break;
            }
            pos = myfile.tellg();
        }

        myfile.close();
    }
    else
        cout << "Unable to open file";
    return item;
}
