
class Join
{
        string Id;     // 帐号
        string Name;   // 姓名
        int Gender;    // 性别
        int Level;     // 等级
        string Family; // 门派
        int Time;      // 申请时间
        int Photo;     // 头像
}

private mapping Joins = ([]); // 申请名单
private
static object me = this_object();
// --------------------------------------
// -------------------------------------------------------------

// 函数：获取申请人数据
mapping get_join_dbase()
{

        return copy(Joins);
}

// 函数：获取申请人数量
int sizeof_join_dbase()
{

        return sizeof(Joins);
}

// 函数：获取申请人标识
string *get_all_join()
{

        return mapp(Joins) ? keys(Joins) : ({});
}

// 函数：初始申请人数据
void init_join_dbase()
{

        Joins = ([]);
}

// -----------------------

// 函数：获取申请人帐号
string
get_join_id(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return "";
        return ((class Join)Joins[name])->Id;
}

// 函数：获取申请人姓名
string get_join_name(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return "";
        return ((class Join)Joins[name])->Name;
}

// 函数：获取申请人性别
int get_join_gender(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return 0;
        return ((class Join)Joins[name])->Gender;
}

// 函数：获取申请人等级
int get_join_level(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return 0;
        return ((class Join)Joins[name])->Level;
}

// 函数：获取申请人门派
string get_join_family(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return "";
        return ((class Join)Joins[name])->Family;
}

// 函数：获取申请人申请时间
int get_join_time(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return 0;
        return ((class Join)Joins[name])->Time;
}

// 函数：获取申请人职业
int get_photo(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return 0;
        return ((class Join)Joins[name])->Photo;
}

// -------------------------------------------------------------

// 函数：设置申请人帐号
string set_join_id(int number, string id)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                Joins[name] = new (class Join);
        ((class Join)Joins[name])->Id = id;

        return ((class Join)Joins[name])->Id;
}

// 函数：设置申请人姓名
string set_join_name(int number, string name2)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                Joins[name] = new (class Join);
        ((class Join)Joins[name])->Name = name2;

        return ((class Join)Joins[name])->Name;
}

// 函数：设置申请人性别
int set_join_gender(int number, int flag)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                Joins[name] = new (class Join);
        ((class Join)Joins[name])->Gender = flag;

        return ((class Join)Joins[name])->Gender;
}

// 函数：设置申请人等级
int set_join_level(int number, int point)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                Joins[name] = new (class Join);
        ((class Join)Joins[name])->Level = point;

        return ((class Join)Joins[name])->Level;
}

// 函数：设置申请人门派
string set_join_family(int number, string name2)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                Joins[name] = new (class Join);
        ((class Join)Joins[name])->Family = name2;

        return ((class Join)Joins[name])->Family;
}

// 函数：设置申请人申请时间
int set_join_time(int number, int time)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                Joins[name] = new (class Join);
        ((class Join)Joins[name])->Time = time;

        return ((class Join)Joins[name])->Time;
}

// 函数：设置申请人职业
int set_photo(int number, int photo)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                Joins[name] = new (class Join);
        ((class Join)Joins[name])->Photo = photo;

        return ((class Join)Joins[name])->Photo;
}

// -------------------------------------------------------------

// 函数：设置申请人信息

void init_join_info(int number, string id, string name2, int gender, int level, string family, int Photo, int time)
{
        class Join info;
        string name = sprintf("%d", number);

        info = new (class Join);

        info->Id = id;
        info->Name = name2;
        info->Gender = gender;
        info->Level = level;
        info->Family = family;
        info->Photo = Photo;
        info->Time = time;

        Joins[name] = info;
}

// 函数：删除申请人信息
void delete_join_info(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Joins[name]))
                return;
        map_delete(Joins, name);
}
