// 玩家列表
inherit SAVE_F;
inherit DBASE_F;

private string Owner;                   // 邮箱主人标识

int save();
int restore();
int receive_mail( mapping mail );

// -------------------------------------------------------------

// 函数：设置用户标识
int set_owner( string id )
{
        Owner = id;
//        if( !user_exist(Owner) ) return 0;
        return restore();
}


// 函数：取存盘文件名
string get_save_file()
{
        if( !Owner || strlen(Owner) < 3 ) return 0;
        return sprintf( "data/%c/%c/%c/%s/list" SAVE_EXTENSION, Owner[0], Owner[1], Owner[2], Owner );
}

// 函数：保存物体资料
int save()
{
        string file = get_save_file();
        if( !stringp(file) ) return 0;
        return save_object(file);
}

// 函数：载入物体资料
int restore()
{
        string file = get_save_file();
        if( !stringp(file) ) return 0;
        return restore_object(file);
}
