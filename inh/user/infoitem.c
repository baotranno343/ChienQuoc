
// 当铺存储物品

private
int Id; // 当铺标识
// private
// string Owner; // 当铺主人标识
private
mapping Infoitem = ([]); // 典当数据资料

int restore();

// -------------------------------------------------------------

// 函数：获取当铺标识
int get_id() { return Id; }

// 函数：设置当铺标识
int set_id(int id) { return Id = id; }

// // 函数：获取用户标识
// string get_owner() { return Owner; }

// // 函数：设置用户标识
// int set_owner(string id)
// {
//         Owner = id;
//         if (!user_exist(Owner))
//                 return 0;
//         return restore();
// }

// 函数：获取典当数据
mapping get_Infoitem() { return copy(Infoitem); }

// 函数：设置典当数据
void set_Infoitem(string key, string value)
{
        if (!mapp(Infoitem))
                Infoitem = ([]);
        Infoitem[key] = value;
}

// 函数：删除典当数据
void delete_Infoitem(string key) { map_delete(Infoitem, key); }

// -------------------------------------------------------------

// 函数：取存盘文件名
string get_save_file()
{
        if (!Id)
                return 0;
        return sprintf("data/infoitem/%d" SAVE_EXTENSION, Id);
}

// 函数：保存物体资料

int save()
{
        string file = get_save_file();
        if (!stringp(file))
                return 0;
        return save_object(file);
}

// 函数：载入物体资料
int restore()
{
        string file = get_save_file();
        if (!stringp(file))
                return 0;
        return restore_object(file);
}

int delete ()
{
        rm(get_save_file());
}