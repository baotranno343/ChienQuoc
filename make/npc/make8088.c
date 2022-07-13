
#define CPP_FILE        __DIR__ "8088.cc"
#define TEXT_FILE       __DIR__ "8088.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, xy, city;
        string *good = ({ "", "", "", "", "", "", "", "", "", "" });
        int *list = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int id, pic, z, x, y, d, i, j, size;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        log_file( LIST_LOG, "# 商人(080.npc)\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %s %s %d %s %d %s %d %d %s", 
                        id, name, pic, city, good[1], list[1], good[2], list[2], good[3], list[3], z, xy ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        xy = replace_string(xy, "，", ",");
                        if( sscanf( xy, "%d,%d,%d", x, y, d ) )
                                log_file( LIST_LOG, sprintf("%d-%d,%d,%d:/npc/city/%04d\n", z, x, y, d, id ) );
                        else    tell_user(me, "ERR: %04d 坐标: %s", id, xy);

                        for( j = 1; j <= 3; j ++ )
                        {
                                good[j+5] = "/make/item/itemlist"->get_item_file( good[j] );    // 要维护物品列表！
                                if( good[j+5] == "" ) tell_user(me, "%04d 货物: %s", id, good[j]);
                        }

                        log_file( file, sprintf( cpp, pic, name, city, 
                                good[6], good[7], good[8], list[1], list[2], list[3] ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件及 /log/list.txt 的坐标点。" );

        return 1;       
}
