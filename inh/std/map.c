
inherit "/inh/std/scene";

private
static int SizeXY;

private
static int Fighter; // 怪物数量    // 150
private
static int AddAmount; // 新增总数

private
static string *fileFighter = ({}); // 怪物文件
private
static string *fileBOSS = ({}); // 怪物文件(小BOSS)

private
static int *FighterRate = ({}); // 怪物的分配比例

private
static int *dbDie = ({}); // 死亡的怪物

private
static object *dbFighter = ({}); // 怪物数组
private
static object *dbCaster = ({}); // 怪物数组(远程攻击)
private
static object *dbBOSS = ({}); // 怪物数组(小BOSS)
int hoiSinh = 0;
int set_hoiSinh(int i)
{
        return hoiSinh = i;
}
get_hoiSinh()
{
        return hoiSinh;
}
// -------------------------------------------------------------

// 函数：设置出怪点总数
int set_sizeof_xy(int total)
{
        Fighter = total;
        return SizeXY = total;
}

// 函数：获取怪物数量
int get_fighter_amount() { return Fighter; }

// 函数：设置怪物数量
int set_fighter_amount(int total)
{
        if (total > 500)
                total = 500;
        return Fighter = range_value(total, SizeXY, SizeXY * 3);
}

// 函数：增加怪物数量
int add_fighter_amount(int total) { return set_fighter_amount(Fighter + total); }

// 函数：获取新增总数(怪物)
int get_add_amount() { return AddAmount; }

// 函数：设置新增总数(怪物)
int set_add_amount(int total) { return AddAmount = total; }

// 函数：增加新增总数(怪物)
int add_add_amount(int total) { return set_add_amount(AddAmount + total); }

// -------------------------------------------------------------

// 函数：获取怪物文件
string *get_fighter_file() { return copy(fileFighter); }

// 函数：获取怪物文件(小BOSS)
string *get_boss_file() { return copy(fileBOSS); }

// 函数：获取怪物文件尺寸
int sizeof_fighter_file() { return sizeof(fileFighter); }

// 函数：获取怪物文件尺寸(小BOSS)
int sizeof_boss_file() { return sizeof(fileBOSS); }

// 函数：设置怪物文件
string *set_fighter_file(string *file) { return fileFighter = file; }

// 设置怪物比例
int *set_fight_rate(int *rate) { return FighterRate = rate; }

int *get_fight_rate() { return FighterRate; }

// 函数：设置怪物文件(小BOSS)
string *set_boss_file(string *file) { return fileBOSS = file; }

// -------------------------------------------------------------

// 函数：获取怪物数组
object *get_fighter_dbase()
{
        dbFighter -= ({0});
        return copy(dbFighter);
}

// 函数：获取怪物数组(远程攻击)
object *get_caster_dbase()
{
        dbCaster -= ({0});
        return copy(dbCaster);
}

// 函数：获取怪物数组(小BOSS)
object *get_boss_dbase()
{
        dbBOSS -= ({0});
        return copy(dbBOSS);
}

// -------------------------------------------------------------

// 函数：获取怪物数组尺寸
int sizeof_fighter_dbase()
{
        dbFighter -= ({0});
        return sizeof(dbFighter);
}

// 函数：获取怪物数组尺寸(远程攻击)
int sizeof_caster_dbase()
{
        dbCaster -= ({0});
        return sizeof(dbCaster);
}

// 函数：获取怪物数组尺寸(小BOSS)
int sizeof_boss_dbase()
{
        dbBOSS -= ({0});
        return sizeof(dbBOSS);
}

// -------------------------------------------------------------

// 函数：增加怪物数据
void add_fighter(object npc) { dbFighter = dbFighter + ({npc}) - ({0}); }

// 函数：删除怪物数据
void delete_fighter(object npc) { dbFighter -= ({npc, 0}); }

// 函数：增加怪物数据(远程攻击)
void add_caster(object npc) { dbCaster = dbCaster + ({npc}) - ({0}); }

// 函数：删除怪物数据(远程攻击)
void delete_caster(object npc) { dbCaster -= ({npc, 0}); }

// 函数：增加怪物数据(小BOSS)
void add_boss(object npc) { dbBOSS = dbBOSS + ({npc}) - ({0}); }

// 函数：删除怪物数据(小BOSS)
void delete_boss(object npc) { dbBOSS -= ({npc, 0}); } // 用于迷魂

// 记录第几类npc死亡了
void add_die(int type)
{
        int size;
        if (type < 0)
                return;
        if (type >= sizeof_fighter_file())
                return;
        size = sizeof(dbDie);
        while (type >= size)
        {
                dbDie += ({0});
        }
        dbDie[type]++;
}

int *get_die() { return dbDie; }

int *init_die() { return dbDie = ({}); }

// -------------------------------------------------------------

// 函数：消除之前处理
void before_destruct()
{
        mapping officer;
        object map, *char, npc;
        string *key;
        int i, size;

        map = this_object();

        if (mapp(officer = map->get_npc_dbase()))
        {
                size = sizeof(key = keys(officer));
                for (i = 0; i < size; i++)
                        if (objectp(npc = officer[key[i]]))
                        {
                                npc->remove_from_scene();
                                destruct(npc);
                        }
        }

        if (arrayp(char = map->get_fighter_dbase())) // caster 为 fighter 子集，勿须清理
        {
                for (i = 0, size = sizeof(char); i < size; i++)
                        if (objectp(npc = char[i]))
                        {
                                npc->remove_from_scene();
                                destruct(npc);
                        }
        }
        if (arrayp(char = map->get_boss_dbase()))
        {
                for (i = 0, size = sizeof(char); i < size; i++)
                        if (objectp(npc = char[i]))
                        {
                                npc->remove_from_scene();
                                destruct(npc);
                        }
        }

        if (arrayp(char = map->get_reset_dbase()))
        {
                for (i = 0, size = sizeof(char); i < size; i++)
                        if (objectp(npc = char[i]))
                        {
                                npc->remove_from_scene();
                                destruct(npc);
                        }
        }
}
//进入场景处理
void enter_scene(object who)
{
        QUEST_TIPS->enter_scene_tip(who, this_object());
}