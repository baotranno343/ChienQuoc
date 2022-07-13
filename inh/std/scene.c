
inherit DBASE_F;

private
static int Reset = -1; // 复位次数(分钟)    // 0
private
static int Clean = 2; // 复位时间(分钟)    // 10

private
static mapping mpXY = ([]); // NPC 定义
private
static mapping mpNPC = ([]); // NPC 数组

private
static object *dbReset = ({}); // 刷新数组

// 函数：场景识别函数
int is_scene() { return 1; }

// -------------------------------------------------------------

// 函数：获取复位次数
int get_reset_time() { return Reset; }

// 函数：设置复位次数
int set_reset_time(int time) { return Reset = time; }

// 函数：增加复位次数
int add_reset_time(int time) { return set_reset_time(Reset + time); }

// 函数：获取复位时间
int get_clean_time() { return Clean; }

// 函数：设置复位时间
int set_clean_time(int time) { return Clean = range_value(time, 1, 100); }

// 函数：增加复位时间
int add_clean_time(int time) { return set_clean_time(Clean + time); }

// -------------------------------------------------------------

// 函数：获取NPC 定义
mapping get_xy_dbase() { return copy(mpXY); }

// 函数：获取NPC 数据集
mapping get_npc_dbase() { return copy(mpNPC); }

// 函数：获取刷新数组
object *get_reset_dbase()
{
    dbReset -= ({0});
    return copy(dbReset);
}

// -------------------------------------------------------------

// 函数：获取NPC 数据尺寸
int sizeof_npc_dbase() { return sizeof(mpNPC); }

// 函数：获取刷新数组尺寸
int sizeof_reset_dbase()
{
    dbReset -= ({0});
    return sizeof(dbReset);
}

// -------------------------------------------------------------

// 函数：增加NPC 定义
void set_xy_define(string key, mixed value) { return mpXY[key] = value; }

// 函数：获取NPC 数据
mixed get_npc_object(string key) { return mpNPC[key]; }

// 函数：增加NPC 数据
void add_npc(string key, mixed value) { return mpNPC[key] = value; }

// 函数：增加复位数据
void add_reset(object npc) { dbReset = dbReset + ({npc}) - ({0}); }
