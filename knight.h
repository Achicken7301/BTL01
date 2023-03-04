#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

// SIZE ARRAY
#define MAX 10
// EVENTS
#define BOWSER_SURRENDER 0
#define MADBEAR 1
#define BANDIT 2
#define LORDLUPIN 3
#define ELF 4
#define TROLL 5
#define SHAMAN 6
#define VAJISH 7
#define MUSH_MARIO 11
#define MUSH_FIB 12
#define MUSH_GHOST 13
#define REMEDY 15
#define MAIDEN_KISS 16
#define PHOENIX_DOWN 17
#define MERLIN 18
#define ASCLEPIUS 19
#define BOWSER 99

/// @brief id, level, baseDamge, realDamge
#define MONSTER 51
#define WITCH 52
typedef struct enemy
{
    int id;
    int name;
    int level;
    float baseDamge;
    float realDamge;
} enemy;

#define NORMAL 70
#define TINY 71
#define FROG 72
#define ARTHUR 73
#define LANCELOT 74

#define MUSH_GHOST_1 1
#define MUSH_GHOST_2 2
#define MUSH_GHOST_3 3
#define MUSH_GHOST_4 4

#define NOT_OVER -1
#define OVER 1
#define CANT_RESCUED 0
typedef struct knight
{
    /// @brief 1: normal, 2: tiny, 3: frog, 4: Arthur, 5: Lancelot
    int id;
    int HP;
    int MAX_HP;
    int level;

    /// @brief when frog out of time
    int before_turn_frog_level;
    int remedy;
    int maidenkiss;
    int phoenixdown;

    /// @brief Use for frog and tiny as well
    int tiny_lasted;

    /// @brief -1: not over, 1: over, 0: cant rescued
    int rescue;

    /// @brief Condition when meet Asclepius
    int is_meet_Asclepius;
} knight;

void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void display(knight *knight);
void knightMeetsEvent(int *event_index, int event_id, knight *knight);

#define GREATER 21
#define LESS -21
#define EQUAL 20
int compareLevel(knight *knight, enemy *enemy);

void battle(int *event_index, knight *knight, enemy *enemy);

void usePhoenixDown(knight *knight);
void useRemedy(knight *knight);
void useMaidenKiss(knight *knight);

int sum_largest_odds(int n1);
int nearest_fibonacci(int num);

void increaseHP(knight *knight, int HP_increase);

void increaseRemedy(knight *knight, int num_increase);
void increaseMaidenKiss(knight *knight, int num_increase);
void increasePhoenixDown(knight *knight, int num_increase);

int is_prime(int n);
//Import function
int *get_pos(string file_array_string);
//Import from file to array
void import(string file_array_string, int *knight_address, int *&event,int&num_event ,string *packet_address[]);
void extract_line_num(string line, int *array_address, int array_length, string delimerter);
int countFreq(string array_string, string array_char);
void extract_line_string(string line, string *array_address[], int array_length, string delimeter);
// EVENT interactive with file.
int *get_item(string file_packet, int event, int mush_ghosh_type);
// MUSH GHOST EVENT
int event_mush_ghost(int arr[],int length ,int type);
void findMaxMin(int arr[],int length,int& maxIndex, int& minIndex);
int findSecondMax(int arr[], int length);
int findMountainArray(int arr[], int length);
void relocate(int*&arr,int count);
#endif // __KNIGHT_H__