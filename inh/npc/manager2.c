
class Member
{
        string Id;      // 帐号
        string Name;    // 姓名
        int Photo;      // 头像
        int Gender;     // 性别
        int Level;      // 等级
        string Family;  // 门派
        string Rank;    // 职务
        int Time;       // 入帮时间
        int Quit;       // 离线时间(在线时，该值为０)
        int Gold;       // 捐款
        int contrib;    // 帮派贡献度
        int allcontrib; // 帮派贡献度的总数
}

private mapping Members = ([]); // 帮众名单
private
static object me = this_object();

// -------------------------------------------------------------

// 函数：获取帮众数据
mapping get_member_dbase()
{

        return copy(Members);
}

// 函数：获取帮众数量
int sizeof_member_dbase()
{

        return sizeof(Members);
}

// 函数：获取帮众标识
string *get_all_member()
{

        return mapp(Members) ? keys(Members) : ({});
}

// 函数：初始帮众数据
void init_member_dbase()
{

        Members = ([]);
}

// -------------------------------------------------------------

// 函数：获取帮众帐号
string get_member_id(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Id;
}

// 函数：获取帮众姓名
string get_member_name(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Name;
}

// 函数：获取帮众头像
int get_member_photo(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Photo;
}

// 函数：获取帮众性别
int get_member_gender(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Gender;
}

// 函数：获取帮众等级
int get_member_level(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Level;
}

// 函数：获取帮众门派
string get_member_family(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Family;
}

// 函数：获取帮众职务
string get_member_rank(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Rank;
}

// 函数：获取帮众入帮时间
int get_member_time(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Time;
}

// 函数：获取帮众离线时间
int get_member_quit(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Quit;
}

// 函数：获取帮众捐款
int get_member_gold(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->Gold;
}

// 函数：获取帮众贡献度
int get_member_contribute(int number)
{

        string name = sprintf("%d", number);
        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->contrib;
}

// 函数：获取帮众贡献度
int get_member_all_contribute(int number)
{

        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return 0;
        return ((class Member)Members[name])->allcontrib;
}

// -------------------------------------------------------------

// 函数：设置帮众帐号
string set_member_id(int number, string id)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Id = id;

        return ((class Member)Members[name])->Id;
}

// 函数：设置帮众姓名
string set_member_name(int number, string name2)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Name = name2;

        return ((class Member)Members[name])->Name;
}

// 函数：设置帮众头像
int set_member_photo(int number, int photo)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Photo = photo;

        return ((class Member)Members[name])->Photo;
}

// 函数：设置帮众性别
int set_member_gender(int number, int flag)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Gender = flag;

        return ((class Member)Members[name])->Gender;
}

// 函数：设置帮众等级
int set_member_level(int number, int point)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Level = point;

        return ((class Member)Members[name])->Level;
}

// 函数：设置帮众门派
string set_member_family(int number, string name2)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Family = name2;

        return ((class Member)Members[name])->Family;
}

// 函数：设置帮众职务
string set_member_rank(int number, string name2)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Rank = name2;

        return ((class Member)Members[name])->Rank;
}

// 函数：设置帮众入帮时间
int set_member_time(int number, int time)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Time = time;

        return ((class Member)Members[name])->Time;
}

// 函数：设置帮众离线时间
int set_member_quit(int number, int time)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Quit = time;

        return ((class Member)Members[name])->Quit;
}

// 函数：设置帮众捐款
int set_member_gold(int number, int point)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        ((class Member)Members[name])->Gold = range_value(point, 0, MAX_NUMBER);

        return ((class Member)Members[name])->Gold;
}

// 函数：设置帮众贡献度
int set_member_contribute(int number, int point)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                Members[name] = new (class Member);
        if (point > ((class Member)Members[name])->contrib)
                ((class Member)Members[name])->allcontrib += (point - ((class Member)Members[name])->contrib);
        ((class Member)Members[name])->contrib = range_value(point, 0, MAX_NUMBER);

        return ((class Member)Members[name])->contrib;
}

// -------------------------------------------------------------

// 函数：设置帮众信息
void init_member_info(int number, string id, string name2, int photo, int gender, int level, string family, string rank, int time, int time2)
{
        class Member info;
        string name = sprintf("%d", number);

        info = new (class Member);

        info->Id = id;
        info->Name = name2;
        info->Photo = photo;
        info->Gender = gender;
        info->Level = level;
        info->Family = family;
        info->Rank = rank;
        info->Gold = 0;
        info->Time = time;
        info->Quit = time2;
        Members[name] = info;
}

// 函数：删除帮众信息
void delete_member_info(int number)
{
        string name = sprintf("%d", number);

        if (undefinedp(Members[name]))
                return;
        map_delete(Members, name);
}
