
// 函数：命令处理
int main( object me, string arg )
{
        mixed *file, *file2;
        string path, path2, path3;
        int i, j, size, size2, total;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        path = "/sys/";
        file = get_dir(path, -1);

        // 路径合法判断
        if( !( size = sizeof(file) ) ) return 1;
        mkdir("/BIN");
        rmdir("/BIN/sys");
        mkdir("/BIN/sys");

        // 第一层目录
        for( i = 0, total = 0; i < size; i ++ )
        {
                path2 = path + file[i][0];

                if( !directory_exist(path2) && path2[<2..<1] == ".c" ) 
                {
                        load_object(path2);  total ++;
                        continue;
                }
                if (path2[<4..<1] == ".svn") continue;                
		mkdir("/BIN"+path2);
                if( path2[<1] != '/' ) path2 += "/";
                file2 = get_dir(path2, -1);
                if( !( size2 = sizeof(file2) ) ) continue;

                // 第二层目录
                for( j = 0; j < size2; j ++ )
                {
                        path3 = path2 + file2[j][0];

                        if( !directory_exist(path3) && path3[<2..<1] == ".c" ) 
                        {
                                load_object(path3);  total ++;
                                continue;
                        }

                        // 警告：只管两层目录！
                }
        }

        tell_user(me, "%d 文件完成。", total);

        return 1;
}
