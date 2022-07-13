
#include <skill.h>
int *allexp = ({
    20,
    67,
    117,
    173,
    238,
    319,
    424,
    562,
    747,
    992,
    1313,
    1730,
    2264,
    2939,
    3780,
    4816,
    6080,
    7606,
    9430,
    11594,
    14140,
    17115,
    20569,
    24554,
    29127,
    34347,
    40278,
    46986,
    54543,
    63021,
    72500,
    83061,
    94791,
    107779,
    122119,
    137911,
    155257,
    174264,
    195045,
    217714,
    242393,
    269209,
    298290,
    329773,
    363797,
    400509,
    440058,
    482600,
    528296,
    577312,
    629820,
    685997,
    746026,
    810096,
    878400,
    951140,
    1028520,
    1110752,
    1198056,
    1290655,
    1388780,
    1492667,
    1602560,
    1718709,
    1841369,
    1970804,
    2107283,
    2251082,
    2402486,
    2561784,
    2729273,
    2905259,
    3090051,
    3283971,
    3487343,
    3700501,
    3923787,
    4265911,
    4626841,
    5012040,
    5422758,
    5860290,
    6325978,
    6821212,
    7347434,
    7906134,
    8498854,
    9127189,
    9792788,
    10497355,
    11242652,
    12030494,
    12862760,
    13741386,
    14668369,
    15645769,
    16675711,
    17760381,
    18902036,
    20102996,
    21365653,
    22692468,
    24085972,
    25548771,
    27083544,
    28693044,
    30380103,
    32147630,
    33998614,
    35936124,
    37963314,
    40083417,
    42299756,
    44615739,
    47034861,
    49560708,
    52196958,
    54947378,
    57815833,
    60806282,
    63922782,
    67169487,
    70550654,
    74070638,
    77733903,
    81545012,
    85508640,
    89629567,
    93912683,
    98362992,
    102985609,
    107785765,
    112768806,
    117940200,
    123305531,
    128870506,
    134640956,
    140622838,
    146822234,
    153245355,
    159898544,
    166788275,
    173921157,
    181303933,
    188943487,
    196846839,
    205021153,
    213473734,
    222212035,
    231243654,
    240576338,
});
int host_type;
// 函数：生成二进制码
void SAVE_BINARY() {}

private
int *Level, *LevelBil;
private
int *Level_1, *LevelBil_1;
private
int *Level_2, *LevelBil_2;

int get_level_exp(int life, int level);

// 函数：构造函数
void create()
{
        int i, k, n;

        host_type = MAIN_D->get_host_type();

        Level = allocate(160);
        LevelBil = allocate(160);
        Level_1 = allocate(160);
        LevelBil_1 = allocate(160);
        Level_2 = allocate(160);
        LevelBil_2 = allocate(160);

        for (i = 0; i < 160; i++)
        {
                k = get_level_exp(0, i);
                n = k;
                LevelBil[i] = n / BILLION_NUMBER;
                Level[i] = n % BILLION_NUMBER;
                n = k * 3 / 2;
                LevelBil_1[i] = n / BILLION_NUMBER;
                Level_1[i] = n % BILLION_NUMBER;
                n = k * 2;
                LevelBil_2[i] = n / BILLION_NUMBER;
                Level_2[i] = n % BILLION_NUMBER;

                if (i > 0)
                {
                        LevelBil[i] += LevelBil[i - 1];
                        Level[i] += Level[i - 1];
                        LevelBil[i] += Level[i] / BILLION_NUMBER;
                        Level[i] %= BILLION_NUMBER;
                        LevelBil_1[i] += LevelBil_1[i - 1];
                        Level_1[i] += Level_1[i - 1];
                        LevelBil_1[i] += Level_1[i] / BILLION_NUMBER;
                        Level_1[i] %= BILLION_NUMBER;
                        LevelBil_2[i] += LevelBil_2[i - 1];
                        Level_2[i] += Level_2[i - 1];
                        LevelBil_2[i] += Level_2[i] / BILLION_NUMBER;
                        Level_2[i] %= BILLION_NUMBER;
                }
        }
}

// 函数：获取等级对应经验
int get_level_exp_high(int life, int level)
{
        level = range_value(level, 0, NPC->get_max_char_level());

        switch (life)
        {
        case 0:
                return LevelBil[level];
        case 1:
                return LevelBil_1[level];
        default:
                return LevelBil_2[level];
        }
}

// 函数：获取等级对应经验
int get_level_exp_low(int life, int level)
{
        level = range_value(level, 0, NPC->get_max_char_level());

        switch (life)
        {
        case 0:
                return Level[level];
        case 1:
                return Level_1[level];
        default:
                return Level_2[level];
        }
}

// 函数：获取升级所需经验
int get_level_exp(int life, int level)
{
        int exp;
        exp = level * level * level * level / 15 + (level + 1) * 100;
        if (exp * level < exp)
                exp = exp + exp / 100 * level;
        else
                exp = exp + exp * level / 100;
        exp += 1;
        if (level <= 76)
                exp -= 80 + 55 * level;
        if (level > 150)
                level = 150;
        if (host_type != 2)
                exp = allexp[level];
        switch (life)
        {
        case 0:
                return exp;
        case 1:
                return exp * 3 / 2;
        default:
                return exp * 2;
        }
}

// 函数：获取人物等级
int get_level(object who)
{
        int *level, *level_bil;
        int exp, bil_exp;
        int start, end, middle, flag;

        switch (who->get_reincarnation())
        {
        case 0:
                level = Level;
                level_bil = LevelBil;
                break;
        case 1:
                level = Level_1;
                level_bil = LevelBil_1;
                break;
        default:
                level = Level_2;
                level_bil = LevelBil_2;
                break;
        }
        exp = who->get_exp();
        bil_exp = who->get_billion_exp();

        start = 0;
        end = NPC->get_max_char_level();
        while (start <= end)
        {
                middle = (start + end) / 2;
                flag = intcmp(bil_exp, exp, level_bil[middle], level[middle]);
                if (flag < 0)
                {
                        if (end < 1)
                                return 0;
                        end = middle - 1;
                }
                else if (flag == 0)
                        return middle + 1; // 实际等级：下标 + 1
                else if (flag > 0)
                {
                        if (intcmp(bil_exp, exp, level_bil[middle + 1], level[middle + 1]) < 0)
                                return middle + 1;
                        if (start >= NPC->get_max_char_level())
                                return NPC->get_max_char_level();
                        else
                                start = middle + 1;
                }
        }

        return middle + 1;
}

// 函数：重算升级经验
void recount_user_level(object who)
{
        int *level_int, *level_bil;
        int level, exp;

        switch (who->get_reincarnation())
        {
        case 0:
                level_int = Level;
                level_bil = LevelBil;
                break;
        case 1:
                level_int = Level_1;
                level_bil = LevelBil_1;
                break;
        default:
                level_int = Level_2;
                level_bil = LevelBil_2;
                break;
        }
        exp = who->get_exp() % BILLION_NUMBER;

        level = get_level(who);
        if (level != who->get_level())
        {
                who->set_level(level);
                who->count_gift();

                if (level < 1)
                        who->set_upgrade_exp(exp);
                else
                        who->set_upgrade_exp(exp - level_int[level - 1]);
                if (who->get_login_flag() >= 3)
                        send_user(who, "%c%c%w%d%d", 0x3d, 40, who->get_billion_exp(), who->get_exp(), who->get_upgrade_exp());
        }
}

// 函数：获取玩家当前经验的上限
int get_upgrade_exp_limit(object me)
{
        int max;
        max = get_level_exp(me->get_reincarnation(), me->get_level());
        if (max > MAX_NUMBER / 10) //防止经验上限超过MAX_NUMBER
                max = MAX_NUMBER / 10;
        return max * 10;
}