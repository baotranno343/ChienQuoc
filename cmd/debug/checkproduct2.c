
inherit DBASE_F;
inherit SAVE_F;

// 函数：命令处理
int main( object me, string arg )
{
        mixed *dfile, *dfile2, *dfile3;
        string path, file, path2, path3, path4;
        int i, j, k, size, size2, size3, level;
        object obj = this_object();
        int * list;

        if( is_player(me) )
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
	for (i=3;i<=12;i++)
	{
		obj->delete_save(sprintf("%d", i*10));
	}
	if( !arg ) arg = ".";

        path = "/item/product";    // 获取绝对路径
        if( directory_exist(path) && path[<1] != '/' ) path += "/";

        dfile = get_dir(path, -1);    // 获取文件列表

        if( !( size = sizeof(dfile) ) )
        {
//                notify( "无法找到这个文件。" );
		return 1;
	}

        tell_user( me, "Mục Lục: %s size=%d", path, size );

        for( i = 0; i < size; i ++ )    // 遍历所有文件
        {
        	path2 = path + dfile[i][0];
        	if (path2[<4..<1] == ".svn") continue;
        	if (path2->get_product_exp()>0) continue;
        	if (path2->get_item_color()!=1) continue;
		level = path2->get_product_level();
		level = level/10*10;
		list = obj->get_save(sprintf("%d", level));
		if (list==0) list = ({ });
		list += ({ path2->get_product_skill()*100+path2->get_product_type() });
		obj->set_save(sprintf("%d", level), list);
tell_user(me, sprintf("skill=%d, level=%d product=%d", path2->get_product_skill(), level, path2->get_product_type() ) )	;	
        }

        return 1;
}
