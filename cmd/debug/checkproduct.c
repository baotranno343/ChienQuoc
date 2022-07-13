
// 函数：命令处理
int main( object me, string arg )
{
        mixed *dfile, *dfile2, *dfile3;
        string path, file, path2, path3, path4;
        int i, j, k, size, size2, size3;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

	if( !arg ) arg = ".";

        path = "/item";    // 获取绝对路径
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
        	if( path2[<1] != '/' ) path2 += "/";
tell_user( me, "Mục Lục: %s i=%d", path2, i );          
   	
        	dfile2 = get_dir(path2, -1);     	
        	if( !( size2 = sizeof(dfile2) ) ) continue;
        	tell_user( me, "Mục Lục: %s size=%d", path2, size2 );
                // 第二层目录
                for( j = 0; j < size2; j ++ )
                {
                        path3 = path2 + dfile2[j][0];

                        if( !directory_exist(path3) && path3[<2..<1] == ".c" && path3->get_fin_type()>0 ) 
                        {
//                                  log_file("list.txt", sprintf("%s: \"%s\" %s\n", path3->get_name(), path3[0..<3], path3->get_desc()));
                                log_file("list.txt", sprintf("\"%d\": \"%s\", \n", path3->get_fin_type(), path3[0..<3]));
                        }
                        else
                        if( directory_exist(path3))
                        {
		        	if (path3[<4..<1] == ".svn") continue; 
		        	if( path3[<1] != '/' ) path3 += "/";                          	
                        	dfile3 = get_dir(path3, -1);                      	
                        	if( !( size3 = sizeof(dfile3) ) ) continue;
                        	tell_user( me, "Mục Lục: %s size=%d", path3, size3 );
                        	for( k = 0; k < size3; k ++ )
                        	{
                        		path4 = path3 + dfile3[k][0];
                        		if( !directory_exist(path4) && path4[<2..<1] == ".c" && path4->get_fin_type()>0 ) 
                        		{
//                        			log_file("list.txt", sprintf("%s: \"%s\" %s\n", path4->get_name(), path4[0..<3], path4->get_desc()));
                        			log_file("list.txt", sprintf("\"%d\": \"%s\", \n", path4->get_fin_type(), path4[0..<3]));
                        		}
                        	}
                        }
                }  
                reset_eval_cost();      	               
        }

        return 1;
}
