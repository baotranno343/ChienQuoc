
#include <equip.h>
int sub_time;

// 函数：判断是否玩家
int is_player(object who) { return who->get_security_class() <= 1; }

// 函数：判断是否ＧＭ
int is_gm(object who)
{
        if (who->get("is_gm"))
                return 1;
        return who->get_security_class() == 2;
}

// 函数：判断是否ＧＭ
int is_gm3(object who) { return who->get_security_class() == 3; }

// 函数：判断是否ＧＭ
int is_gm2(object who) { return who->get_security_class() == 4; }

// 函数：判断是否大神
int is_god(object who) { return who->get_security_class() == 5; }

// 函数：获取用户等级
string get_class(object who)
{
        switch (who->get_security_class())
        {
        case 1:
                return PLAYER_CLASS;
        case 2:
                return GM_CLASS;
        case 3:
                return GM3_CLASS;
        case 4:
                return GM2_CLASS;
        case 5:
                return GOD_CLASS;
        default:
                return NPC_CLASS;
        }
}

// -------------------------------------------------------------

// 函数：检查文件是否存在
int file_exist(string file) { return file_size(file) > 0; }

// 函数：检查目录是否存在
int directory_exist(string path) { return file_size(path) == -2; }

// 函数：检查用户是否存在
int user_exist(string id)
{
        if (!id)
                return 0;
        return file_size(sprintf("data/%c/%c/%c/%s/user" SAVE_EXTENSION, id[0], id[1], id[2], id)) > 0;
}

// 函数：获取绝对路径
string absolute_path(object me, string path) { return FILE_D->resolve_path(me->get_cwd(), path); }

// 函数：记录日志文件
int log_file(string file, string log) { return efun::log_file("log/" + file, log); }

// 函数：记录日志文件
int ghi_file(string file, string log) { return efun::log_file(file, log); }

// 函数：删除文件中注释行
string *update_file(string file)
{
        string *line;
        int i, size;

        if (!file_exist(file))
                return 0;

        line = explode(read_file(file), "\n");
        for (i = 0, size = sizeof(line); i < size; i++)
        {
                if (line[i][0] == '#')
                        line[i] = 0;
                else if (line[i][ < 1] <= ' ')
                        line[i] = line[i][0.. < 2]; // UNIX 格式
        }

        return line;
}

// 函数：检查是否中文字串 (放开限制)
int is_chinese(string name)
{
        int i, size = strlen(name);

        if (size < 1)
                return 0;
        for (i = 0; i < size; i++)
                if (name[i] == '`' || name[i] == ';' || name[i] == ',' || name[i] == ' ' || name[i] == '\'' || name[i] == '"' || name[i] == '%')
                        return 0;
        //                if( name[i] < 128 || name[i] > 255 ) return 0;

        return 1;
}

// -------------------------------------------------------------

// 函数：寻找指定物体(用于GM指令)
object find_any_object(string what)
{
        object me, *inv, item;
        int i, size;

        if (!stringp(what) || what == "")
                return 0;

        me = this_player();
        if (what == "me")
                return me;
        if (sscanf(what, "(%d)", i))
                switch (i)
                {
                case HEAD_TYPE:
                        return me->get_equip(HEAD_TYPE);
                case NECK_TYPE:
                        return me->get_equip(NECK_TYPE);
                case WEAPON_TYPE:
                        return me->get_equip(WEAPON_TYPE);
                case ARMOR_TYPE:
                        return me->get_equip(ARMOR_TYPE);
                case WAIST_TYPE:
                        return me->get_equip(WAIST_TYPE);
                case BOOTS_TYPE:
                        return me->get_equip(BOOTS_TYPE);
                case HAND_TYPE:
                        return me->get_equip(HAND_TYPE);
                default:
                        return number_present(me, i, 0, 0);
                }
        if (item = present(what, me, 0, 0))
                return item;
        if (item = find_player(what))
                return item;
        if (item = find_living(what))
                return item;
        if (item = load_object(absolute_path(me, what)))
                return item;
        if (item = load_object(what))
                return item;

        inv = me->get_all_equip();
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (objectp(inv[i]) && inv[i]->id(what))
                        return inv[i];
        inv = get_range_object_2(me, 5, ITEM_TYPE);
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (objectp(inv[i]) && inv[i]->id(what))
                        return inv[i];
        inv = get_scene_object_2(me, CHAR_TYPE);
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (objectp(inv[i]) && inv[i]->id(what))
                        return inv[i];
        inv = get_range_object_2(me, 5, SEAL_TYPE);
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (objectp(inv[i]) && inv[i]->id(what))
                        return inv[i];

        return 0;
}

// 函数：寻找玩家物体(用于GM指令get from)
object find_user_item(string what, object who)
{
        object *inv, item;
        int i, size;

        if (!stringp(what) || what == "")
                return 0;

        if (sscanf(what, "(%d)", i))
                switch (i)
                {
                case HEAD_TYPE:
                        return who->get_equip(HEAD_TYPE);
                case NECK_TYPE:
                        return who->get_equip(NECK_TYPE);
                case WEAPON_TYPE:
                        return who->get_equip(WEAPON_TYPE);
                case ARMOR_TYPE:
                        return who->get_equip(ARMOR_TYPE);
                case WAIST_TYPE:
                        return who->get_equip(WAIST_TYPE);
                case BOOTS_TYPE:
                        return who->get_equip(BOOTS_TYPE);
                case HAND_TYPE:
                        return who->get_equip(HAND_TYPE);
                default:
                        return number_present(who, i, 0, 0);
                }
        if (item = present(what, who, 0, 0))
                return item;
        inv = who->get_all_equip();
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (objectp(inv[i]) && inv[i]->id(what))
                        return inv[i];

        return 0;
}

// 函数：寻找指定人物(用于GM指令)
object find_any_char(string what)
{
        object *inv, who, me;
        int i, size;

        if (!stringp(what) || what == "")
                return 0;

        me = this_player();
        if (what == "me")
                return me;
        if (what[ < 1] != '#' && objectp(who = find_player(what)))
                return who;
        if (what[ < 1] == '#' && objectp(who = find_living(what)))
                return who;
        if (!me)
                return 0;
        inv = get_scene_object_2(me, CHAR_TYPE);
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (objectp(inv[i]) && inv[i]->id(what))
                        return inv[i];

        return 0;
}

// 函数：寻找指定人物
object find_char(string what)
{
        if (!stringp(what) || what == "")
                return 0;
        return what[ < 1] == '#' ? find_living(what) : find_player(what);
}

//根据日历时间生成标准时间秒数
int mktime(int year, int mon, int day, int hour, int min, int sec)
{
        if (0 >= (mon -= 2))
        {                  /* 1..12 -> 11,12,1..10 */
                mon += 12; /* Puts Feb last since it has leap day */
                year -= 1;
        }

        return (((
                     (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + day) +
                     year * 365 - 719499) *
                     24 +
                 hour /* now have hours */
                 ) * 60 +
                min /* now have minutes */
                ) * 60 +
               sec      /* finally seconds */
               - 28800; /*调整时区*/
}

string rawurlencode2(string code)
{
        string *input, *output, ret;
        int i, size, begin, end;
        input = ({});
        output = ({});
        ret = "";
        size = strlen(code);
        if (size == 0)
                return ret;
        for (i = 0; i < size; i += 20)
        {
                begin = i;
                end = begin + 20;
                if (end > size)
                        end = size;
                end--;
                input += ({code[begin..end]});
        }
        size = sizeof(input);
        for (i = 0; i < size; i++)
        {
                output += ({rawurlencode(input[i])});
        }
        for (i = 0; i < size; i++)
                ret = ret + output[i];
        return ret;
}

/*
string md5(string a)
{
	return a;
}

string short_time_2()
{
	return "19991122";
}
*/
//可以设置的相对的游戏时间
int get_party_time()
{
        return time() - sub_time;
}
int set_party_time(int year, int mon, int day, int hour, int min, int sec)
{
        sub_time = time() - mktime(year, mon, day, hour, min, sec);
        return time() - sub_time;
}