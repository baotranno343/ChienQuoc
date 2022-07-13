
#define CPP_FILE        __DIR__ "collect.cc"
#define TEXT_FILE       __DIR__ "collect.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, xy;
        string item, *item2, result, result2;
        int id, pic, exp, pot, gift, r1, r2, r3, f1, f2;
        int z, x, y, d, flag, i, j, size, size2;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        log_file( LIST_LOG, "# 收集任务\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %s %d %d %d %d %d %d %d %d %s", id, name, pic, z, xy, exp, pot, gift, r1, r2, r3, f1, f2, item ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        xy = replace_string(xy, "，", ",");
                        if( sscanf( xy, "%d,%d,%d", x, y, d ) )
                                log_file( LIST_LOG, sprintf("%d-%d,%d,%d:/npc/10/%04d\n", z, x, y, d, id ) );
                        else    tell_user(me, "ERR: %04d 坐标: %s", id, xy);

                        item2 = ({ });
                        item2 = explode( item, "、" );
//                      item2 = sort_array( item2, 1 );
                        size2 = sizeof(item2);

                        result = "";  result2 = "";

                        for( j = 0; j < size2; j ++ )
                        {
                                if( j == 0 )
                                {
                                        result += sprintf( @LONG
objectp( item%d = present("%s", who, 1, MAX_CARRY) )
LONG
, j + 1, item2[j] );
                                }
                                else
                                {
                                        result += sprintf( @LONG
                        &&      objectp( item%d = present("%s", who, 1, MAX_CARRY) )
LONG
, j + 1, item2[j] );
                                }
                                result2 += sprintf( @LONG
                                item%d->remove_from_user();  destruct(item%d);
LONG
, j + 1, j + 1 );
                        }

                        log_file( file, sprintf( cpp, pic, name,  
                                f1, f2, f1, f2+1, f1, f2+2, f1, f2+3, f1, f2+4, 
                                f1 * 100 + f2 + 1,    // 询问任务
                                f1, f2, f1, f2+1, f1, f2+2, f1, f2+3, f1, f2+4, f1, f2+5, 
                                result, result2,
                                f1 * 100 + f2 + 4,    // 刚完成任务
                                f1, f2+1, f1, f2+1, f1, f2+3, f1, f2+3, f1, f2+5, f1, f2+5, 
                                exp, pot, gift, r1, r2, r3,
                                f1 * 100 + f2 + 3,    // 没完成任务
                                f1 * 100 + f2 + 5,    // 完成任务
                                f1 * 100 + f2,    // 等级不够
                                f1, f2, f1, f2+1, f1, f2+2, f1, f2+3, f1, f2+4, 
                                f1 * 100 + f2 + 2,    // 答应任务
                                f1, f2, f1, f2, f1, f2+2, f1, f2+2, f1, f2+4, f1, f2+4 ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 文件及 /log/list.txt 坐标点。" );

        return 1;       
}
