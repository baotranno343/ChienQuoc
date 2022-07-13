
#include <ansi.h>
#include <time.h>

class Friend
{
        string Id;
        string Name;
        int Type;
        int Notify;
        int Gender;
        int Level;
        int City;
        string Org;
        string Family;
}

private mapping Friends = ([]);

private
static mapping Mail = ([]); // 发信人数组

// -------------------------------------------------------------

// 函数：获取好友名单
mapping get_friend_dbase() { return copy(Friends); }

// 函数：初始好友名单
void init_friend_dbase() { Friends = ([]); }

// -------------------------------------------------------------

// 函数：增加好友名单
void add_friend(object who, int type)
{
        object me = this_object();
        class Friend note;
        int id = me->get_number();
        string result;
        string key = sprintf("%d", who->get_number());
        int flag;
        if (Friends == 0)
                init_friend_dbase();
        if (undefinedp(Friends[key]))
        {
                note = new (class Friend);
                flag = 1;
        }
        else
        {
                note = Friends[key];
                flag = 0;
                //              send_user( me, "%c%c%d", 0x46, 0, who->get_number() );
        }

        note->Id = who->get_id();
        note->Name = who->get_name();
        /*    if (who->get_save_2("marry.id")==me->get_number())
        {
        	if (me->get_gender()==1)
        		note->Name = sprintf("            %s(Nương tử)", who->get_name());
        	//	note->Name = sprintf("%s (Bà xã)", who->get_name());
        	else
        		note->Name = sprintf("            %s(Tướng công)", who->get_name());
        	//	note->Name = sprintf("%s (Ông xã)", who->get_name());
        }
        else
        if (who->get_save_2("baishi.tudi.id")==me->get_number())
        	note->Name = sprintf("            %s(Sư phụ)", who->get_name());
        //	note->Name = sprintf("%s (Sư phụ)", who->get_name());
		else
        if (who->get_save_2("baishi.shifu.id")==me->get_number())
        	note->Name = sprintf("            %s(Đệ tử)", who->get_name());	        	
        //	note->Name = sprintf("%s (Đệ tử)", who->get_name());
		else*/
        if (who->is_user())
                note->Name = sprintf("            %s", who->get_name());
        note->Type = type;
        //      note->Notify = 0;
        note->Gender = who->get_gender();
        note->Level = who->get_level();
        note->Family = who->get_fam_name();
        if (who->get_org_position() > 0)
                note->Org = who->get_org_name();
        else
                note->Org = "";
        switch (who->get_city_name())
        {
        case "Tề Quốc":
                note->City = 1;
                break;
        case "Hàn Quốc":
                note->City = 2;
                break;
        case "Triệu Quốc":
                note->City = 3;
                break;
        case "Ngụy Quốc":
                note->City = 4;
                break;
        case "Tần Quốc":
                note->City = 5;
                break;
        case "Sở Quốc":
                note->City = 6;
                break;
        case "Yên Quốc":
                note->City = 7;
                break;
        default:
                note->City = 0;
                break;
        }
        Friends[key] = note;

        result = sprintf("%-6s%-10s%s", "", "", note->Name);
        send_user(me, "%c%c%d%c%c%c%c%w%s", 0x46, 1,
                  who->get_number(), note->Type, note->Notify, note->Gender, note->City, note->Level, result);

        if (flag)
        {
                me->delete_friend_degree(id);
                who->delete_friend_degree(me->get_number());
                write_user(who, ECHO " %s ( %d ) thêm bạn vào thành hảo bằng hữu.", me->get_name(), me->get_number());
                send_user(who, "%c%s", '!', sprintf(HIY " %s ( %d ) " NOR "thêm bạn vào thành hảo bằng hữu.", me->get_name(), me->get_number()));
        }
}

// 函数：是否通知好友
int is_notify_friend(int id)
{
        string key = sprintf("%d", id);
        if (undefinedp(Friends[key]))
                return 0;
        return ((class Friend)Friends[key])->Notify;
}

// 函数：设置通知好友
void set_notify(int id, int type)
{
        object who;
        class Friend note;
        string key = sprintf("%d", id);
        string result;

        if (undefinedp(Friends[key]))
                return;

        note = Friends[key];

        //      send_user( this_object(), "%c%c%d", 0x46, 0, id );

        if (who = find_player(key))
        {
                note->Id = who->get_id();
                note->Name = who->get_name();
                //              note->Type = 0;
                note->Gender = who->get_gender();
                note->Level = who->get_level();
                note->Family = who->get_fam_name();
                if (who->get_org_position() > 0)
                        note->Org = who->get_org_name();
                else
                        note->Org = "";
                switch (who->get_city_name())
                {
                case "Tề Quốc":
                        note->City = 1;
                        break;
                case "Hàn Quốc":
                        note->City = 2;
                        break;
                case "Triệu Quốc":
                        note->City = 3;
                        break;
                case "Ngụy Quốc":
                        note->City = 4;
                        break;
                case "Tần Quốc":
                        note->City = 5;
                        break;
                case "Sở Quốc":
                        note->City = 6;
                        break;
                case "Yên Quốc":
                        note->City = 7;
                        break;
                default:
                        note->City = 0;
                        break;
                }
        }

        note->Notify = type;
        Friends[key] = note;
        result = sprintf("%-6s%-10s%s", "", "", note->Name);
        send_user(this_object(), "%c%c%d%c%c%c%c%w%s", 0x46, 1,
                  id, note->Type, note->Notify, note->Gender, note->City, note->Level, result);
}

// 函数：删除好友名单
void remove_friend(int number)
{
        int flag;
        string key = sprintf("%d", number);
        class Friend note;
        object who, me = this_object();
        if (Friends == 0)
                init_friend_dbase();
        if (undefinedp(Friends[key]))
                return;
        note = Friends[key];
        //清除友好度
        this_object()->delete_friend_degree(number);
        who = find_char(key);
        if (!who)
        {
                if (!user_exist(note->Id))
                {
                        flag = -1;
                }
                else
                {
                        who = new (USER);
                        who->set_id(note->Id);
                        if (!who->restore())
                                destruct(who);
                        else
                                flag = 1; //restore的
                }
        }
        if (who)
        {
                who->delete_friend_degree(this_object()->get_number());
                if (flag == 1)
                        who->save();
        }
        if (flag == 1)
                destruct(who);
        map_delete(Friends, key);
        send_user(this_object(), "%c%c%d", 0x46, 0, number);
}

// 函数：获取好友标识
string get_friend_id(int id)
{
        string key = sprintf("%d", id);
        //   string key = sprintf( "           %d", id );
        if (undefinedp(Friends[key]))
                return 0;
        return ((class Friend)Friends[key])->Id;
}

// 函数：获取好友姓名
string get_friend_name(int id)
{
        string key = sprintf("%d", id);
        //   string key = sprintf( "           %d", id );
        if (undefinedp(Friends[key]))
                return 0;
        return ((class Friend)Friends[key])->Name;
}

// 函数：发消息给好友
void send_to_friend(int flag)
{
        object me, who;
        string *key;
        int id, i, size;

        me = this_object();
        id = me->get_number();
        size = sizeof(key = keys(Friends));

        if (!flag)
                for (i = 0; i < size; i++)
                {
                        if (((class Friend)Friends[key[i]])->Notify && objectp(who = find_player(key[i])))
                        {
                                send_user(who, "%c%c%d", 0x46, 8, id);
                        }
                }
        else
                for (i = 0; i < size; i++)
                {
                        if (((class Friend)Friends[key[i]])->Notify && objectp(who = find_player(key[i])))
                        {
                                send_user(who, "%c%c%d", 0x46, 9, id);
                                send_user(who, "%c%c%d%s", 0x4d, 0xff, me->get_number(),
                                          sprintf(HIY "%s(%d) " NOR "đăng nhập.", me->get_name(), me->get_number()));
                        }
                }
}

// 函数：发消息给好友
void receive_friends()
{
        object me, who;
        class Friend note;
        string *key, result, result2;
        int id, id1, i, size, max_degree;

        me = this_object();
        id = me->get_number();

        size = sizeof(key = keys(Friends));
        if (size)
                key = sort_array(key, 1);
        result = sprintf("%-6s%-10s%s", "", "", "Vạn Sự Thông");
        send_user(me, "%c%c%d%c%c%c%c%w%s", 0x46, 1, 0, 0, 0, 2, 8, 100, result);
        result2 = sprintf("Bằng hữu của bạn %s(%d) đã đăng nhập", me->get_name(), id);
        for (i = 0; i < size; i++)
        {
                note = Friends[key[i]];
                if (objectp(who = find_player(key[i])))
                {
                        me->add_friend(who, 0);
                        send_user(me, "%c%c%d", 0x46, 9, to_int(key[i]));
                        if (who->get_vip())
                                send_user(me, "%c%c%d", 0x46, 10, to_int(key[i]));
                        if (who->get_friend_id(id))
                        {
                                who->add_friend(me, 0);
                                send_user(who, "%c%c%d", 0x46, 9, id);
                                if (me->get_vip())
                                        send_user(who, "%c%c%d", 0x46, 10, id);
                                send_user(who, "%c%c%d%s", 0x43, 10, 0, HIR + result2); // get_scene_object_2(me, USER_TYPE)
                        }
                }
                else
                {
                        result = sprintf("%-10s", note->Name);
                        send_user(me, "%c%c%d%c%c%c%c%w%s", 0x46, 1, to_int(key[i]),
                                  note->Type, note->Notify, note->Gender, note->City, note->Level, result);
                }
                //友好度
                id1 = to_int(key[i]);
                send_user(me, "%c%c%d%d%d%s", 0x46, 12, id1,
                          me->get_friend_degree(id1), max_degree = me->get_friend_max_degree(id1), USER_RANK_D->get_friend_desc(max_degree));
        }
}

// 函数：发消息给好友
void leave_friends()
{
        object me, who;
        class Friend note;
        string *key, result;
        int id, i, size;

        me = this_object();
        id = me->get_number();
        if (Friends == 0)
                init_friend_dbase();
        size = sizeof(key = keys(Friends));
        if (size)
                key = sort_array(key, 1);

        result = sprintf("Bằng hữu của bạn %s rời mạng.", me->get_name());
        for (i = 0; i < size; i++)
        {
                note = Friends[key[i]];
                if (objectp(who = find_player(key[i])))
                {
                        me->add_friend(who, 0);
                        if (who->get_friend_id(id))
                        {
                                who->add_friend(me, 0);
                                send_user(who, "%c%c%d", 0x46, 8, id);
                                send_user(who, "%c%c%d%s", 0x43, 10, 0, HIR + result); // get_scene_object_2(me, USER_TYPE)
                        }
                }
        }
}

// -------------------------------------------------------------

// 函数：获取发信人标识
string get_mail_id(int number)
{
        string id = sprintf("%d", number);
        if (undefinedp(Mail[id]))
                return 0;
        return Mail[id];
}

// 函数：设置发信人标识
string set_mail_id(int number, string name)
{
        string id;
        if (id = get_friend_id(number))
                return id; // 不需记录好友
        id = sprintf("%d", number);
        return Mail[id] = name; // 过多发信人，数组会过大！
}

void refresh_friend()
{
        object me, who;
        class Friend note;
        string *key;
        int id, i, size, max_degree, id1;

        me = this_object();
        id = me->get_number();

        size = sizeof(key = keys(Friends));
        if (size)
                key = sort_array(key, 1);

        for (i = 0; i < size; i++)
        {
                note = Friends[key[i]];
                if (objectp(who = find_player(key[i])))
                {
                        me->add_friend(who, 0);
                        send_user(me, "%c%c%d", 0x46, 9, to_int(key[i]));
                }
        }
}

// 传回黑名单列表
void send_black()
{
        object me;
        mapping Black;
        string *id;
        int i, size;
        me = this_object();
        Black = me->get_save_2("Black");
        if (Black == 0)
                return;
        id = keys(Black);
        size = sizeof(id);
        if (size == 0)
                return;
        for (i = 0; i < size; i++)
        {
                send_user(me, "%c%c%d%s", 0x20, 1, to_int(id[i]), Black[id[i]]);
        }
}

void add_black(string id, string name)
{
        object me;
        mapping Black;
        string *key;
        int i, size;
        me = this_object();
        i = to_int(id);
        if (i < 1)
        {
                return;
        }
        Black = me->get_save_2("Black");
        if (Black != 0)
        {
                key = keys(Black);
                size = sizeof(key);
                if (size >= 20)
                {
                        notify("Danh sách đen không thể vượt quá 20 người.");
                        return;
                }
        }
        me->set_save_2("Black." + id, name);
        send_user(me, "%c%c%d%s", 0x20, 1, i, name);
}

void del_black(string id)
{
        object me;
        int i;
        i = to_int(id);
        if (i < 1)
                return;
        me = this_object();
        me->delete_save_2("Black." + id);
        send_user(me, "%c%c%d", 0x20, 0, i);
}
//增加友好度,双方一起增加的
int add_friend_degree(int id, int degree)
{
        int i, max;
        object me;
        string key = sprintf("%d", id);
        if (undefinedp(Friends[key]))
                return 0;
        me = this_object();
        max = me->get_save_2(sprintf("friend_info.%d.max_degree", id));
        if (degree > 0)
        {
                max = range_value(max + degree, 0, 10000);
                me->set_save_2(sprintf("friend_info.%d.max_degree", id), max); //最大值
        }
        i = me->get_save_2(sprintf("friend_info.%d.degree", id));
        degree = range_value(i + degree, 0, 10000);
        me->set_save_2(sprintf("friend_info.%d.degree", id), degree);
        //刷新友好度
        send_user(me, "%c%c%d%d%d%s", 0x46, 12, id,
                  degree, max, USER_RANK_D->get_friend_desc(max));
        return degree;
}
//删除友好度
int delete_friend_degree(int id)
{
        object me;
        me = this_object();
        me->delete_save_2(sprintf("friend_info.%d.max_degree", id));
        me->delete_save_2(sprintf("friend_info.%d.degree", id));
        me->delete_save_2(sprintf("friend_info.%d.sub_degree", id));
        if (sizeof(me->delete_save_2(sprintf("friend_info.%d", id))) == 0)
                me->delete_save_2(sprintf("friend_info.%d", id));
        send_user(me, "%c%c%d%d%d%s", 0x46, 12, id, 0, 0, USER_RANK_D->get_friend_desc(0));
        return 1;
}
//获得友好度
int get_friend_degree(int id)
{
        object me;
        string key = sprintf("%d", id);
        if (undefinedp(Friends[key]))
                return 0;
        me = this_object();
        return me->get_save_2(sprintf("friend_info.%d.degree", id));
}
//获取最大友好度
int get_friend_max_degree(int id)
{
        object me;
        string key = sprintf("%d", id);
        if (undefinedp(Friends[key]))
                return 0;
        me = this_object();
        return me->get_save_2(sprintf("friend_info.%d.max_degree", id));
}
//杀怪增加0.1友好度
int inc_friend_sub_degree(int id, int i)
{
        int j;
        object me;
        string key = sprintf("%d", id);
        if (undefinedp(Friends[key]))
                return 0;
        me = this_object();
        i += me->get_save_2(sprintf("friend_info.%d.sub_degree", id));
        j = i % 10;
        i = i / 10;
        me->set_save_2(sprintf("friend_info.%d.sub_degree", id), j);
        if (i)
                add_friend_degree(id, i);
        return 1;
}