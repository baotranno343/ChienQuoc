
// 函数：初始化用户
void init_user( object who )
{

        who->init_skill_0_dbase();
        who->init_skill_1_dbase();
        who->init_skill_2_dbase();
        who->init_legend_3_dbase();

        who->save();    // ##############################
}

// 函数：命令处理
int main( object me, string arg )
{
        object user;
        mixed *file, *file2, *file3, *file4;
        string path, path2, path3, path4;
        int total;
        int i, j, k, l, size, size2, size3, size4;

        if( !arg ) 
        {
                notify( "请输入目录：0～9, a～z。" );
		return 1;
        }
        if( ( arg[0] < 'a' || arg[0] > 'z' ) && ( arg[0] < '0' || arg[0] > '9' ) ) 
        {
                notify( "请输入目录：0～9, a～z。" );
		return 1;
        }

        path = sprintf( "/data/%c/", arg[0] );
        file = get_dir(path, -1);

        total = 0;
        tell_user(me, "清理资料: %s", path);

        // 路径合法判断
        if( !( size = sizeof(file) ) ) 
        {
                if( path[<1] != '/' ) 
                {
                        notify( "没有这个文件。" );
		        return 1;
                }
                if( directory_exist( path[ 1..<2 ] ) ) 
                {
                        notify( "这目录是空的。" );
		        return 1;
                }
                else
                {
                        notify( "没有这个目录。" );
		        return 1;
                }
        }

        // 第二个字母
        for( i = 0; i < size; i ++ )
        {
                path2 = path + file[i][0];
                if( !directory_exist(path2) ) continue;    // break;
                else if( path2[<1] != '/' ) path2 += "/";
                file2 = get_dir(path2, -1);
                if( !( size2 = sizeof(file2) ) ) continue;    // break;

                // 第三个字母
                for( j = 0; j < size2; j ++ )
                {
                        path3 = path2 + file2[j][0];
                        if( !directory_exist(path3) ) continue;    // break;
                        else if( path3[<1] != '/' ) path3 += "/";
                        file3 = get_dir(path3, -1);
                        if( !( size3 = sizeof(file3) ) ) continue;    // break;

                        // 具体的数据
                        for( k = 0; k < size3; k ++ )
                        {
//                              if( !CLASS_D->is_player( file3[k][0] ) ) continue;
                                
                                reset_eval_cost();

                                path4 = path3 + file3[k][0];
                                if( !directory_exist(path4) )
                                {
                                        tell_user(me, "文件有问题: %s", path4);
                                        continue;    // break;
                                }

                                if( path4[<1] != '/' ) path4 += "/";
                                if( !file_exist( path4 + "user.dat" ) )
                                {
/*                                      file4 = get_dir(path4, -1);
                                        if( !( size4 = sizeof(file4) ) ) break;
                                        for( l = 0; l < size4; l ++ ) rm( path4 + file4[l][0] );
                                        rmdir( path4[0..<2] );
                                        tell_user(me, "路径不合法: %s", path4);    */
                                        continue;    // break;
                                }

                                total ++;

                                user = new( USER );
                                user->set_id( file3[k][0] );
                                user->restore();

                                init_user(user);
                                // user->save();    // ##############################


/*                              d = gone_time( user->get_last_on() ) / 3600 / 24;    // Ｘ天没上线
                                e = user->get_exp();
                                e1 = ( d / 30 * d / 30 ) * 50000 - 10000;
                                if( e < e1 ) 
                                {
                                        if( path4[<1] != '/' ) path4 += "/";
                                        file4 = get_dir(path4, -1);
                                        if( !( size4 = sizeof(file4) ) ) break;
                                        for( l = 0; l < size4; l ++ ) rm( path4 + file4[l][0] );
                                        rmdir( path4[0..<2] );
                                }       */

                                destruct(user);
                        }
                }
        }

        tell_user(me, "检查 %d 人，完成！", total);

        return 1;
}
