#include "knight.h"

string file_mush_ghost;
string file_asclepius_pack;
string file_merlin_pack;
// void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
// {
//     cout << "HP=" << HP
//          << ", level=" << level
//          << ", remedy=" << remedy
//          << ", maidenkiss=" << maidenkiss
//          << ", phoenixdown=" << phoenixdown
//          << ", rescue=" << rescue << endl;
// }

void display(knight *knight)
{
    cout << "HP=" << knight->HP
         << ", level=" << knight->level
         << ", remedy=" << knight->remedy
         << ", maidenkiss=" << knight->maidenkiss
         << ", phoenixdown=" << knight->phoenixdown
         << ", rescue=" << knight->rescue << endl;
}
void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int knight_address[6] = {HP, level, remedy, maidenkiss, phoenixdown, rescue};
    int num_event = MAX;
    int *event = new int[num_event];
    string *packet_address[3] = {&file_mush_ghost, &file_asclepius_pack, &file_merlin_pack};

    // Readfile import Knight's properties, events, bag_items.
    import(file_input, knight_address, event, num_event, packet_address);
    knight knight1;
    // HP,level,remedy,maidenkiss,pheonixdown
    knight1.HP = knight_address[0];
    knight1.level = knight_address[1];
    knight1.remedy = knight_address[2];
    knight1.maidenkiss = knight_address[3];
    knight1.phoenixdown = knight_address[4];

    knight1.rescue = NOT_OVER;
    knight1.MAX_HP = knight1.HP;
    knight1.id = NORMAL;
    knight1.tiny_lasted = 0;

    if (knight1.HP == 999)
    {
        knight1.id = ARTHUR;
    }
    else if (is_prime(knight1.HP))
    {
        knight1.id = LANCELOT;
    }
    // Loop all events and return rescue value.
    for (int i = 1; i <= num_event; i++)
    {
        knightMeetsEvent(&i, event[i - 1], &knight1);

        // TINY CONDITION
        if (knight1.tiny_lasted > 0 && (knight1.id == FROG || knight1.id == TINY))
        {
            knight1.tiny_lasted--;
            // printf("knight1.tiny_lasted: %d\n", knight1.tiny_lasted);
            if (knight1.tiny_lasted == 0)
            {
                // printf("Tiny no longer, turn back to normal health x 5\n");
                knight1.HP *= 5;
            }
        }

        // rescure CONDITION
        if (knight1.rescue == OVER)
        {
            // cout << "WIN GAME\n";
            display(&knight1);
            break;
        }
        else if ((knight1.rescue == CANT_RESCUED))
        {
            // cout << "princess cant be rescued\n";
            display(&knight1);
            break;
        }
        else if ((i < num_event) && (knight1.rescue == NOT_OVER))
        {
            display(&knight1);
        }
        if (i == num_event)
        {
            knight1.rescue = OVER;
            display(&knight1);
            break;
        }

        // std::cout << endl;
    }
    // if (knight1.rescue == OVER)
    //     // cout << "Passed all enemies: winner winner chicken dinner!!\n";
}

/// @brief
/// @param event_id
/// @param knight: knight's infomation
/// @return knight->rescue
void knightMeetsEvent(int *event_index, int event_id, knight *knight)
{
    int *item = new int[4];
    string mush_ghost_arr_id;
    if (std::to_string(event_id).substr(0, 2) == std::to_string(13))
    {
        mush_ghost_arr_id = std::to_string(event_id).substr(2);
        event_id = MUSH_GHOST;
    }

    switch (event_id)
    {
    case BOWSER_SURRENDER:
        // std::cout << "BOWSER_SURRENDER\n";
        // knight->level += 1;
        knight->rescue = OVER;
        break;

    case MADBEAR:
        // std::cout << "MEET MADBEAR\n";
        enemy madbear;
        madbear.baseDamge = 1;
        madbear.id = MONSTER;
        battle(event_index, knight, &madbear);
        break;

    case BANDIT:
        // std::cout << "MEET BANDIT\n";

        enemy bandit;
        bandit.baseDamge = 1.5;
        bandit.id = MONSTER;
        battle(event_index, knight, &bandit);
        break;

    case LORDLUPIN:
        // std::cout << "MEET LORDLUPIN\n";
        enemy LordLupin;
        LordLupin.baseDamge = 4.5;
        LordLupin.id = MONSTER;
        battle(event_index, knight, &LordLupin);
        break;

    case ELF:
        // std::cout << "MEET ELF\n";
        enemy elf;
        elf.baseDamge = 7.5;
        elf.id = MONSTER;
        battle(event_index, knight, &elf);
        break;

    case TROLL:
        // std::cout << "MEET TROLL\n";
        enemy troll;
        troll.baseDamge = 9.5;
        troll.id = MONSTER;
        battle(event_index, knight, &troll);
        break;

    case SHAMAN:
        // std::cout << "MEET SHAMAN\n";
        enemy shaman;
        shaman.id = WITCH;
        shaman.name = SHAMAN;
        battle(event_index, knight, &shaman);
        break;

    case VAJISH:
        // std::cout << "MEET VAJISH\n";
        enemy vajish;
        vajish.id = WITCH;
        vajish.name = VAJISH;
        battle(event_index, knight, &vajish);
        break;

    case MUSH_MARIO:
        // std::cout << "MEET MUSH_MARIO\n";
        int n1, s1;
        n1 = ((knight->level + knight->phoenixdown) % 5 + 1) * 3;
        s1 = sum_largest_odds(n1);
        knight->HP = knight->HP + (s1 % 100);
        if (knight->HP > knight->MAX_HP)
        {
            knight->HP = knight->MAX_HP;
        }

        break;

    case MUSH_FIB:
        // std::cout << "MEET MUSH_FIB\n";
        if (knight->HP > 1)
        {
            // printf("nearest_fibonacci(%d): %d\n", knight->HP, nearest_fibonacci(knight->HP));
            knight->HP = nearest_fibonacci(knight->HP);
        }
        else if (knight->HP == 1)
        {
            knight->HP = 1;
        }

        break;

    case MUSH_GHOST:
        // std::cout << "MEET MUSH_GHOST\n";
        for (size_t i = 0; i < mush_ghost_arr_id.length(); i++)
        {
            int mush_type = mush_ghost_arr_id[i] - '0';
            // cout<<mush_type;
            get_item(item, 4, file_mush_ghost, event_id, mush_type);
            increaseHP(knight, item[0]);
        }

        break;

    case REMEDY:
        // std::cout << "MEET REMEDY\n";
        increaseRemedy(knight, 1);
        if (knight->id == TINY)
        {
            useRemedy(knight);
        }

        break;

    case MAIDEN_KISS:
        // std::cout << "MEET MAIDEN_KISS\n";
        increaseMaidenKiss(knight, 1);
        if (knight->id == FROG)
            useMaidenKiss(knight);

        break;

    case PHOENIX_DOWN:
        // std::cout << "MEET PHOENIX_DOWN\n";
        increasePhoenixDown(knight, 1);
        break;

    case MERLIN:
        // std::cout << "MEET MERLIN\n";
        get_item(item, 4, file_merlin_pack, event_id, 0);
        increaseHP(knight, item[0]);
        break;

    case ASCLEPIUS:
        // std::cout << "MEET ASCLEPIUS\n";
        // 0 beacause do not meet MUSH GHOST
        get_item(item, 4, file_asclepius_pack, event_id, 0);
        // cout<<"Remedy:"<<*(item+1)<<endl;
        // cout<<"MaidenKiss:"<<*(item+2)<<endl;
        // cout<<"PhoenixDown:"<<*(item+3)<<endl;
        increaseRemedy(knight, item[1]);
        increaseMaidenKiss(knight, item[2]);
        increasePhoenixDown(knight, item[3]);
        break;

    case BOWSER:
        // std::cout << "MEET BOWSER\n";
        enemy bowser;
        bowser.name = BOWSER;
        battle(event_index, knight, &bowser);
        break;

    default:
        break;
    }
}

void battle(int *event_index, knight *knight, enemy *enemy)
{
    int b = *event_index % 10;
    enemy->level = *event_index > 6 ? (b > 5 ? b : 5) : b;
    // printf("Enemy LevelO: %d\n", enemy->level);

    switch (compareLevel(knight, enemy))
    {
    case GREATER:
        // LEVEL UP KNIGHT
        if (knight->level < 10)
        {
            if (enemy->id == MONSTER)
            {
                knight->level += 1;
            }
            else if (enemy->id == WITCH)
            {
                knight->level += 2;
            }
        }

        if (knight->level > 10)
            knight->level = 10;

        knight->rescue = NOT_OVER;
        break;

    case LESS:
        // CAL ENEMY HP
        if (enemy->id == MONSTER)
        {
            enemy->realDamge = enemy->baseDamge * enemy->level * 10;
            // std::cout << "knight's health lost: " << enemy->realDamge << endl;
            knight->HP = knight->HP - enemy->realDamge;
            // CAL KNIGHT HP
            if (knight->HP <= 0)
            {
                // printf("knight's HP < 0\n");
                if (knight->phoenixdown > 0)
                {
                    usePhoenixDown(knight);
                    knight->rescue = NOT_OVER;
                    break;
                }
                else
                {
                    knight->rescue = CANT_RESCUED;
                    break;
                }
            }
            knight->rescue = NOT_OVER;
        }
        // MEET Shaman or Vajish
        else if (enemy->id == WITCH)
        {
            if (knight->id == TINY || knight->id == FROG)
            {
                // printf("knight already a frog or being tiny\n");
                break;
            }

            if (enemy->name == SHAMAN)
            {
                // printf("Turn knight to tiny\n");
                knight->id = TINY;
                // 4 = current event + next 3 events
                knight->tiny_lasted = 4;

                // HEX ENEMY
                /*
                if (knight->HP < 5)
                {
                    knight->HP = 1;
                }
                else
                {
                    knight->HP = knight->HP / 5;
                }
                */
                (knight->HP < 5) ? (knight->HP = 1) : (knight->HP = knight->HP / 5);

                // USE Remedy
                if (knight->remedy > 0)
                    useRemedy(knight);

                /*
                Nếu HP của hiệp sĩ giảm xuống bằng hoặc dưới 0 khi hiệp sĩ ở
                trạng thái tí hon và hiệp sĩ có PhoenixDown để sử dụng
                */
                if (knight->HP <= 0 && knight->phoenixdown > 0)
                {
                    usePhoenixDown(knight);
                    knight->id = NORMAL; // normal
                    knight->HP = knight->MAX_HP;
                }
                break;
            }

            if (enemy->name == VAJISH)
            {
                // printf("Turn knight to frog with level 1\n");
                knight->id = FROG;
                knight->before_turn_frog_level = knight->level;
                knight->level = 1;
                // 4 = current event + next 3 events
                knight->tiny_lasted = 4;

                if (knight->maidenkiss > 0)
                    useMaidenKiss(knight);

                break;
            }
        }

        break;

    case EQUAL:
        // printf("FIGHT EVEN\n");
        break;

    default:
        break;
    }
}

void useMaidenKiss(knight *knight)
{
    // printf("knight uses maiden kiss\n");
    knight->maidenkiss--;
    knight->id = NORMAL; // normal
    knight->level = knight->before_turn_frog_level;
    knight->tiny_lasted = 0;
}

void usePhoenixDown(knight *knight)
{
    // printf("knight has Phoenix Down\n");
    knight->phoenixdown--;
    knight->HP = knight->MAX_HP;
    knight->tiny_lasted = 0;
}

void useRemedy(knight *knight)
{
    // printf("knight uses remedy\n");
    knight->remedy--;
    knight->id = NORMAL; // normal condition
    knight->HP *= 5;
    knight->tiny_lasted = 0;
}

int compareLevel(knight *knight, enemy *enemy)
{
    // Meet Bowser
    /*
    (arthur or lancelot with level < 8) vs bowser => lose
    normal knight with level < 10 vs bowser => lose
    */
    if (((knight->id == NORMAL && knight->level < 10) or (knight->level < 8 && (knight->id == ARTHUR || knight->id == LANCELOT))) && enemy->name == BOWSER)
    {
        // printf("Meets bowser and lost\n");
        knight->rescue = CANT_RESCUED;
        return 123;
    }

    // Arthur
    if (knight->id == ARTHUR)
    {
        // printf("Arthur WIN\n");
        return GREATER;
    }

    // Lancelot
    if (knight->id == LANCELOT && (enemy->id == MONSTER or enemy->id == WITCH))
    {
        // printf("Lancelot wins Monster and Witch\n");
        return GREATER;
    }

    // normal knight
    if (knight->level > enemy->level)
    {
        if (enemy->name == BOWSER)
        {
            knight->level = 10;
            // printf("Arthur or lancelot or knight's level 10 wins bowser\n");
            return GREATER;
        }

        // printf("knight level > enemy level\n");
        return GREATER;
    }
    else if (knight->level < enemy->level)
    {
        // printf("knight level < enemy level\n");
        return LESS;
    }

    else if (knight->level == enemy->level)
    {
        // printf("knight level = enemy level\n");
        return EQUAL;
    }
    else
    {
        // printf("WTF IS THIS???\n");
        return -99;
    }
}

int sum_largest_odds(int n1)
{
    int sum = 0;

    for (int i = 99; i > 0; i -= 2)
    {
        if (n1 > 0)
        {
            sum += i;
        }
        else
        {
            break;
        }
        n1--;
    }
    return sum;
}

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n; // base case
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2); // recursive case
    }
}

int nearest_fibonacci(int num)
{
    int i = 0;
    while (true)
    {
        int fib = fibonacci(i);
        if (num - fib <= 0)
        {
            return fibonacci(i - 1); // found nearest Fibonacci number
        }
        i++;
    }
}

void increaseHP(knight *knight, int HP_increase)
{
    knight->HP += HP_increase;
    if (knight->HP > knight->MAX_HP)
    {
        knight->HP = knight->MAX_HP;
    }
    if (knight->HP <= 0)
    {
        if (knight->phoenixdown > 0)
        {
            usePhoenixDown(knight);
            knight->rescue = NOT_OVER;
        }
    }
}

void increaseRemedy(knight *knight, int num_increase)
{
    // printf("knight's remedy %d\n", num_increase);
    knight->remedy += num_increase;
    if (knight->remedy > 99)
    {
        knight->remedy = 99;
    }
}
void increaseMaidenKiss(knight *knight, int num_increase)
{
    // printf("knight's maidenkiss %d\n", num_increase);

    knight->maidenkiss += num_increase;
    if (knight->maidenkiss > 99)
    {
        knight->maidenkiss = 99;
    }
}
void increasePhoenixDown(knight *knight, int num_increase)
{
    // printf("knight's phoenixdown %d\n", num_increase);

    knight->phoenixdown += num_increase;
    if (knight->phoenixdown > 99)
    {
        knight->phoenixdown = 99;
    }
}

int is_prime(int n)

{
    if (n <= 1)
    {
        return 0; // 1 and below are not prime
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0; // n is divisible by i, so it is not prime
        }
    }
    return 1; // n is prime
}

// Get postition for each line from file, each element is one line
int *get_pos(string file_array_string)
{
    // 3 is the number of line in file
    string line;
    ifstream myfile(file_array_string);
    int *pos_line = new int[MAX];
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
        myfile.seekg(0); // set file pointer to the beginning of the file
        myfile.close();
    }
    else
        cout << "Unable to open file";
    return pos_line;
}
// Import load file and read line from each line as string type
void import(string file_array_string, int *knight_address, int *&event, int &num_event, string *packet_address[])
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
                num_event = countFreq(line, " ") + 1;
                extract_line_num(line, event, num_event, " ");
                relocate(event, num_event);
            }
            if (pos == pos_line[2])
            {
                extract_line_string(line, packet_address, 3, ",");
            }
            pos = myfile.tellg(); // end pos in a line
        }
        myfile.seekg(0); // set file pointer to the beginning of the file
        myfile.close();
    }
    else
        cout << "Unable to open file";
}
// From each line convert to int and save into the address of variable
void extract_line_num(string line, int *array_address, int array_length, string delimeter)
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
        array_address[i] = std::stoi(line_num);
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
void get_item(int *&item, int length, string file_packet, int event, int mush_ghosh_type)
{
    for (int i = 0; i < length; i++)
    {
        item[i] = 0;
    }
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
                if (pos == pos_line[1])
                {
                    int length = countFreq(line, ",") + 1;
                    int mush_ghost[length];
                    extract_line_num(line, mush_ghost, length, ",");
                    row_item = countFreq(line, ",") + 1;
                    *item = event_mush_ghost(mush_ghost, row_item, mush_ghosh_type);
                }

                break;
            case ASCLEPIUS:
                if (pos > pos_line[1])
                {
                    int item_count;
                    item_count = 0;
                    int size = countFreq(line, " ") + 1;
                    int arr[size];
                    extract_line_num(line, arr, size, " ");
                        for (int i = 0; i < size; i++)
                            {
                                switch (arr[i])
                                {
                                case 16:
                                    item[1]++;
                                    item_count++;
                                    break;
                                case 17:
                                    item[2]++;
                                    item_count++;
                                    break;
                                case 18:
                                    item[3]++;
                                    item_count++;
                                    break;
                                default:
                                    break;
                                }
                                if (item_count>= 3 )
                                    break;
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
        myfile.seekg(0); // set file pointer to the beginning of the file
        myfile.close();
    }
    else
        cout << "Unable to open file";
}
// Subfunction for MUSH GHOST EVENT

// Function to find the index of
// the peak element in the array
int findMountainArray(int arr[], int length)
{
    int peak;
    if (length < 3)
        peak = -3;
    int i = 0;
    for (i = 1; i < length; i++)
        if (arr[i] <= arr[i - 1])
            break;
    peak = i - 1;
    for (; i < length; i++)
        if (arr[i] >= arr[i - 1])
        {
            peak = -3;
            break;
        }
    return peak;
}
void findMaxMin(int arr[], int length, int &maxIndex, int &minIndex)
{
    int max_min[2];
    int i_max = 0;
    int i_min = 0;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] >= arr[i_max])
            i_max = i;
        if (arr[i] <= arr[i_min])
            i_min = i;
    }
    maxIndex = i_max;
    minIndex = i_min;
}
// Function to find the second maximum value in an array
int findSecondMax(int arr[], int n)
{
    int i_max, i_secondmax;
    findMaxMin(arr, n, i_max, i_secondmax);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != arr[i_max] && arr[i] > arr[i_secondmax])
        {
            i_secondmax = i;
        }
    }
    // If there is no second maximum value, set i_secondmax to -1
    if (i_secondmax == i_max)
    {
        i_secondmax = -7;
    }
    return i_secondmax;
}
// MUSH GHOST EVENT
int event_mush_ghost(int arr[], int length, int type)
{
    int HP_change;
    int max, min;
    int i_second_max = -7;
    int second_max = -5;

    int *tmp;
    switch (type)
    {
    case MUSH_GHOST_1:
        findMaxMin(arr, length, min, max);
        HP_change = -(max + min);
        break;
    case MUSH_GHOST_2:
        int mtx, mti;
        mti = findMountainArray(arr, length);
        if (mti < 0)
            mtx = -2;
        mtx = arr[mti];
        HP_change = -(mtx + mti);
        break;
    case MUSH_GHOST_3:
        for (int i = 0; i < length; i++)
        {
            arr[i] = abs(arr[i]);
            arr[i] = (17 * arr[i] + 9) % 257;
        }
        findMaxMin(arr, length, max, min);
        HP_change = -(max + min);
        break;
    case MUSH_GHOST_4:
        for (int i = 0; i < length; i++)
        {
            arr[i] = abs(arr[i]);
            arr[i] = (17 * arr[i] + 9) % 257;
        }
        int sub_arr[3];
        for (int i = 0; i < 3; i++)
        {
            sub_arr[i] = arr[i];
        }

        i_second_max = findSecondMax(sub_arr, 3);
        if (i_second_max != -7)
            second_max = arr[i_second_max];
        HP_change = -(second_max + i_second_max);
    default:
        break;
    }
    return HP_change;
}
void relocate(int *&arr, int count)
{
    int *new_arr = new int[count];
    for (int i = 0; i < count; i++)
    {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
}