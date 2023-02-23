#include "knight.h"
#include "import.h"
const int MAX=10;

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int *kngiht_address[6] = {&HP, &level, &remedy, &maidenkiss, &phoenixdown, &rescue};
    int* event_address[MAX];  
    // In proccess
    rescue=-1;
  for (int i = 0; i < MAX; i++) {
        event_address[i] = new int(-1);
    } 
    // FIle was import will change value HP,level,remedy,maidenkiss,resuce
    import(file_input, kngiht_address,event_address);
    display(HP,level,phoenixdown,maidenkiss,phoenixdown,rescue);
    // Readfile import Knight's properties, events, bag_items.
    knight knight1;
    // HP,level,remedy,maidenkiss,pheonixdown
    knight1.HP = 172;
    knight1.level = 2;
    knight1.remedy = 0;
    knight1.maidenkiss = 1;
    knight1.phoenixdown = 1;

    knight1.rescue = -1;
    knight1.MAX_HP = knight1.HP;
    knight1.id = 1; // ENUM
    // input events
    // int event[1000] = {0, 1, 2, 3};
    int event[] = {1, 2, 2, 18, 99};

    // Loop all events and return rescue value.
    for (int i = 1; i <= sizeof(event) / sizeof(int); i++)
    {
        knightMeetsEvent(&i, event[i - 1], &knight1);
        // rescure CONDITION
        if (knight1.rescue == 1)
        {
            cout << "WIN GAME\n";
            break;
        }
        else if (knight1.rescue == 0)
        {
            cout << "princess cant be rescued\n";
            break;
        }
        else if (knight1.rescue == -1)
        {
            if (i == sizeof(event) / sizeof(int))
            {
                knight1.rescue = 1;
            }
        }

        // TINY CONDITION
        if (knight1.tiny_lasted > 0)
        {
            knight1.tiny_lasted--;
        }
        else
        {
            printf("Tiny no longer, turn back to normal health*5\n");
            knight1.HP *= 5;
        }

        display(&knight1);
        std::cout << endl;
    }
    display(&knight1);
}

/// @brief
/// @param event_id
/// @param knight: knight's infomation
/// @return knight->rescue
void knightMeetsEvent(int *event_index, int event_id, knight *knight)
{
    // cout << (string)event_id << endl;
    switch (event_id)
    {
    case BOWSER_SURRENDER:
        std::cout << "BOWSER_SURRENDER\n";
        knight->rescue = 1;
        display(knight);
        break;

    case MADBEAR:
        std::cout << "MEET MADBEAR\n";
        enemy madbear;
        madbear.baseDamge = 1;
        madbear.id = 1;
        battle(event_index, knight, &madbear);
        break;

    case BANDIT:
        std::cout << "MEET BANDIT\n";

        enemy bandit;
        bandit.baseDamge = 1;
        bandit.id = 1;
        battle(event_index, knight, &bandit);
        break;

    case LORDLUPIN:
        std::cout << "MEET LORDLUPIN\n";
        enemy LordLupin;
        LordLupin.baseDamge = 4.5;
        LordLupin.id = 1;
        battle(event_index, knight, &LordLupin);
        break;

    case ELF:
        std::cout << "MEET ELF\n";
        enemy elf;
        elf.baseDamge = 7.5;
        elf.id = 1;
        battle(event_index, knight, &elf);

        break;

    case TROLL:
        std::cout << "MEET TROLL\n";
        enemy troll;
        troll.id = 1;
        troll.baseDamge = 9.5;
        battle(event_index, knight, &troll);
        break;

    case SHAMAN:
        std::cout << "MEET SHAMAN\n";
        enemy shaman;
        shaman.id = 2;
        shaman.name = SHAMAN;
        battle(event_index, knight, &shaman);
        break;

    case VAJISH:
        std::cout << "MEET VAJISH\n";
        enemy vajish;
        vajish.id = 2;
        vajish.name = VAJISH;
        battle(event_index, knight, &vajish);

        break;

    case MUSH_MARIO:
        std::cout << "MEET MUSH_MARIO\n";
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
        std::cout << "MEET MUSH_FIB\n";
        if (knight->HP > 1)
        {
            knight->HP = nearest_fibonacci(knight->HP);
        }
        else if (knight->HP == 1)
        {
            knight->HP = 1;
        }

        break;

    case MUSH_GHOST:
        std::cout << "MEET MUSH_GHOST\n";
        break;

    case REMEDY:
        std::cout << "MEET REMEDY\n";
        break;

    case MAIDEN_KISS:
        std::cout << "MEET MAIDEN_KISS\n";
        break;

    case PHOENIX_DOWN:
        std::cout << "MEET PHOENIX_DOWN\n";
        break;

    case MERLIN:
        std::cout << "MEET MERLIN\n";
        break;

    case ASCLEPIUS:
        std::cout << "MEET ASCLEPIUS\n";
        break;

    case BOWSER:
        std::cout << "MEET BOWSER\n";
        break;

    default:
        break;
    }
}

void display(knight *knight)
{
    cout << "HP=" << knight->HP
         << ", level=" << knight->level
         << ", remedy=" << knight->remedy
         << ", maidenkiss=" << knight->maidenkiss
         << ", phoenixdown=" << knight->phoenixdown
         << ", rescue=" << knight->rescue << endl;
}

void battle(int *event_index, knight *knight, enemy *enemy)
{
    int b = *event_index % 10;
    enemy->level = *event_index > 6 ? (b > 5 ? b : 5) : b;
    printf("Enemy LevelO: %d\n", enemy->level);

    switch (compareLevel(knight, enemy))
    {
    case GREATER:
        // LEVEL UP KNIGHT
        if (knight->level < 10)
        {
            if (enemy->id == 1)
            {
                knight->level += 1;
            }
            else if (enemy->id == 2)
            {
                knight->level += 2;
            }
        }

        if (knight->level > 10)
            knight->level = 10;

        knight->rescue = -1;
        break;

    case LESS:
        // CAL ENEMY HP
        if (enemy->id == 1)
        {
            enemy->realDamge = enemy->baseDamge * enemy->level * 10;
            knight->HP = knight->HP - enemy->realDamge;
            // CAL KNIGHT HP
            if (knight->HP <= 0)
            {
                printf("knight's HP < 0\n");
                if (knight->phoenixdown > 0)
                {
                    usePhoenixDown(knight);
                    knight->rescue = -1;
                    break;
                }
                else
                {
                    knight->rescue = 0;
                    break;
                }
            }
            knight->rescue = -1;
        }
        else if (enemy->id == 2)
        {
            if (knight->id == 2 or knight->id == 3)
            {
                printf("knight already a frog or being tiny\n");
                break;
            }

            if (enemy->name == SHAMAN)
            {

                printf("Turn knight to tiny\n");
                knight->id = 2;
                knight->tiny_lasted = 3;

                // HEX ENEMY
                if (knight->HP < 5)
                {
                    knight->HP = 1;
                }
                else
                {
                    knight->HP = knight->HP / 5;
                }

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
                    knight->id = 1; // normal
                    knight->HP = knight->MAX_HP;
                }
                break;
            }

            if (enemy->name == VAJISH)
            {
                printf("Turn knight to frog with level 1\n");
                knight->id = 3;
                knight->old_level = knight->level;
                knight->level = 1;

                if (knight->maidenkiss > 0)
                {
                    useMaidenKiss(knight);
                }
                break;
            }
        }

        break;

    case EQUAL:
        printf("FIGHT EVEN\n");
        break;

    default:
        break;
    }
}

void useMaidenKiss(knight *knight)
{
    printf("knight uses maiden kiss");
    knight->maidenkiss--;
    knight->id = 1; // normal
    knight->level = knight->old_level;
}

void usePhoenixDown(knight *knight)
{
    printf("knight has Phoenix Down\n");
    knight->phoenixdown--;
    knight->HP = knight->MAX_HP;
}

void useRemedy(knight *knight)
{
    printf("knight uses remedy\n");
    knight->remedy--;
    knight->id = 1; // normal condition
    knight->HP *= 5;
}

/// @brief
/// @param knight
/// @param enemy
/// @return fight results greater = 21, less = -21, equal = 20
int compareLevel(knight *knight, enemy *enemy)
{
    if (knight->level > enemy->level)
    {
        printf("knight level > enemy level\n");
        return GREATER;
    }
    else if (knight->level < enemy->level)
    {
        printf("knight level < enemy level\n");
        return LESS;
    }

    else if (knight->level == enemy->level)
    {
        printf("knight level = enemy level\n");
        return EQUAL;
    }
    else
    {
        printf("WTF IS THIS???\n");
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
        if (std::abs(fib - num) <= std::abs(fibonacci(i + 1) - num))
        {
            return fib; // found nearest Fibonacci number
        }
        i++;
    }
}