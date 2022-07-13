
#include <city.h>
#include <equip.h>

private
string *UsersId = ({});

private
int *UsersNumber = ({});

void SAVE_BINARY() {}

string get_save_file()
{
        return "data/user.dat";
}
// 函数：构造处理
void create()
{
        //  save_object(get_save_file());
}

int *get_usernumber()
{
        restore_object(get_save_file());
        return copy(UsersNumber);
}
void add_usernumber(int id)
{
        restore_object(get_save_file());
        UsersNumber = UsersNumber - ({id, 0}) + ({id});
        save_object(get_save_file());
}
void sub_usernumber(int id)
{
        restore_object(get_save_file());
        UsersNumber = UsersNumber - ({id, 0});
        save_object(get_save_file());
}

void sub_allnumber(string id)
{
        object obj;
        int i, num;
        string Owner;
        if (sscanf(id, "%s#%d", Owner, i) != 2)
                Owner = id;
        obj = new ("/inh/user/list");
        if (!obj)
                return;
        obj->set_owner(Owner);
        obj->restore();
        restore_object(get_save_file());
        for (i = 0; i < 6; i++)
        {
                if (num = obj->get_save_2(sprintf("%d.number", i + 1)))
                // if ((num = obj->get_save_2(sprintf("%d.number", i + 1))) > 0)
                {
                        UsersNumber -= ({num});
                }
        }
        save_object(get_save_file());
        destruct(obj);
}
int checknumber(int id)
{
        get_usernumber();
        return member_array(id, UsersNumber);
}
// -------------------------------------------------------------
string *get_userid()
{
        restore_object(get_save_file());
        return copy(UsersId);
}
void add_userid(string id)
{
        int n;
        string id2;
        restore_object(get_save_file());
        if (sscanf(id, "%s#%d", id2, n) != 2)
                id2 = id;
        UsersId = UsersId - ({id2, 0}) + ({id2});
        save_object(get_save_file());
}
void sub_userid(string id)
{
        int n;
        string id2;
        restore_object(get_save_file());
        if (sscanf(id, "%s#%d", id2, n) != 2)
                id2 = id;
        UsersId = UsersId - ({id2, 0});
        save_object(get_save_file());
}

int checkid(string id)
{

        get_userid();
        return member_array(id, UsersId);
}
int checkid2(string id)
{
        string kenh;
        if (file_exist(sprintf("isLogin/%s.dat", id)))
        {
                kenh = read_file(sprintf("isLogin/%s.dat", id));
                if (kenh[0] >= '0' && kenh[0] <= '9')
                {
                        return to_int(kenh);
                }
        }
        return 0;
}
void locid(string id)
{
        object *alluser, *user, who;
        int i;
        alluser = users();
        alluser -= ({0});
        if (arrayp(alluser) // 获取所有玩家  children(USER) - ({ load_object(USER) })
            && sizeof(alluser) > 0 && arrayp(user = filter_array(alluser, (
                                                                              : $1->get_real_id() == $2:),
                                                                 id)) // 判断ＩＤ吻合(除自己外)
            && sizeof(user))                                          // 用户个数大于０
        {
                for (i = 0; i < sizeof(user); i++)
                {
                        who = user[i];
                        if (!who)
                                continue;
                        who->save();
                        "/cmd/base/quit"->main(who, "");
                }
        }
}
void locid2(string id)
{
        object *alluser, *user, who;
        int i;
        alluser = users();
        alluser -= ({0});
        if (arrayp(alluser) // 获取所有玩家  children(USER) - ({ load_object(USER) })
            && sizeof(alluser) > 0 && arrayp(user = filter_array(alluser, (
                                                                              : $1->get_real_id() == $2:),
                                                                 id)) // 判断ＩＤ吻合(除自己外)
            && sizeof(user))                                          // 用户个数大于０
        {
                return;
        }
        rm(sprintf("isLogin/%s.dat", id));
        return;
}
void kicknumber(int id)
{
        object who;
        if (who = find_player(sprintf("%d", id)))
        {
                who->save();
                "/cmd/base/quit"->main(who, "");
        }
}
// void add_id_number_file(int number, string id)
// {
//         string list = sprintf("listId/list_%d.txt", number / 1000);
//         ghi_file(list, sprintf("\n%s", id));
//         return;
// }
// int check_id_from_number(int number)
// {
//         int i, sofile = number / 1000;
//         string *data, string list = sprintf("listId/list_%d.txt", number / 1000);

//         if (!find_any_char(sprintf("%d", number)))
//         {
//                 data = explode(read_file(list), "\n");
//                 if (data[number - (sofile * 1000)] != "")
//                 {
//                         re
//                 }
//         }
//         return 0;
// }
// int check_id_kenh_online(int number)
// {
//         string kenh;
//         if (file_exist(sprintf("isNumber/%d.dat", number)))
//         {
//                 kenh = read_file(sprintf("isNumber/%d.dat", number));
//                 if (kenh[0] >= '0' && kenh[0] <= '9')
//                 {
//                         return to_int(kenh);
//                 }
//         }
//         return 0;
// }
// int check_id_online(int number)
// {
//         string *line, *data;
//         int i;
//         if (!find_any_char(sprintf("%d", number)))
//         {
//                 if (checknumber(number) != -1)
//                         return 1;
//         }
//         return 0;
// }
string numberToId(int number)
{
        string id;
        if (file_exist(sprintf("data/numberToId/%d.dat", number)))
        {
                id = read_file(sprintf("data/numberToId/%d.dat", number));
                if (id != "")
                        return id;
        }
        return "";
}
int check_id_online(int number)
{
        string kenh, id;
        if (!find_any_char(sprintf("%d", number)))
        {
                if ((id = numberToId(number)) != "")
                        if (file_exist(sprintf("isLogin/%s.dat", id)))
                        {
                                kenh = read_file(sprintf("isLogin/%s.dat", id));
                                if (kenh[0] >= '0' && kenh[0] <= '9')
                                {
                                        return to_int(kenh);
                                }
                        }
        }
        return 0;
}
