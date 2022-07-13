
#define CPP_FILE        __DIR__ "8008.cc"
#define TEXT_FILE       __DIR__ "8008.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, xy, city, city2;
        int id, pic, z, x, y, d, i, size;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        log_file( LIST_LOG, "# 典狱官\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %s %d %s", id, name, pic, city, z, xy ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        xy = replace_string(xy, "，", ",");
                        if( sscanf( xy, "%d,%d,%d", x, y, d ) )
                                log_file( LIST_LOG, sprintf("%d-%d,%d,%d:/npc/city/%04d\n", z, x, y, d, id ) );
                        else    tell_user(me, "ERR: %04d 坐标: %s", id, xy);

                        switch( city )
                        {
                  case "齐国" : city2 = "CITY_QI";  break;
                  case "韩国" : city2 = "CITY_HAN";  break;
                  case "赵国" : city2 = "CITY_ZHAO";  break;
                  case "魏国" : city2 = "CITY_WEI";  break;
                  case "秦国" : city2 = "CITY_QIN";  break;
                  case "楚国" : city2 = "CITY_CHU";  break;
                  case "燕国" : city2 = "CITY_YAN";  break;
                      default : tell_user(me, "%04d 国家: %s", id, city);  break;
                        }

                        log_file( file, sprintf( cpp, pic, name, city, city2, city2, city2 ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件及 /log/list.txt 的坐标点。" );

        return 1;       
}
