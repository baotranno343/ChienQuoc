
#define CPP_FILE        __DIR__ "0002.cc"
#define TEXT_FILE       __DIR__ "0002.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, city, xy;
        string item, *item2, result, result2;
        int id, pic, z, x, y, d, i, j, size, size2;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        log_file( LIST_LOG, "# 老板、小贩\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %s %d %s %s", id, name, pic, item, z, xy, city ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        xy = replace_string(xy, "，", ",");
                        if( sscanf( xy, "%d,%d,%d", x, y, d ) )
                                log_file( LIST_LOG, sprintf("%d-%d,%d,%d:/npc/base/%04d\n", z, x, y, d, id ) );
                        else    tell_user(me, "ERR: %04d 坐标: %s", id, xy);

                        item2 = ({ });
                        item2 = explode( item, "、" );
                        size2 = sizeof(item2);

                        for( j = 0, result2 = ""; j < size2; j ++ )
                        {
                                result = "/make/item/itemlist"->get_item_file( item2[j] );    // 要维护物品列表！

                                if( result == "" ) tell_user(me, "%04d 货物: %s", id, item2[j]);
                                result2 += sprintf( @LONG
                "%02d" : %s,
LONG
, j+1, result );
                        }

                        log_file( file, sprintf( cpp, pic, name, city, result2 ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件及 /log/list.txt 的坐标点。" );

        return 1;       
}
