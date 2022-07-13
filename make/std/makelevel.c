
#define TEXT_FILE       __DIR__ "level.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string *line;
        int *number, *level, *total;
        int id, point, begin;
        int i, j, k, size;

        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        number = allocate(size);  j = 0;
        level = allocate(size);
        total = allocate(size);  k = 0;  begin = 1;  // 从 1 级开始
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %d", id, point ) )
                {
                        number[j] = id;  level[j] = point / 10;

                        if( begin == level[j] )
                        {
                                total[k] ++;
                        }
                        else
                        {
                                begin = level[j];  k ++;
                                total[k] ++;    // 首个数值
                        }

                        j ++;
                }
        }

        log_file( LIST_LOG, "--- 以下用于 /map/map/xy.c ---\n" );

        for( i = 0, begin = 0; i <= k; i ++ )
        {
                log_file( LIST_LOG, sprintf( @LONG
      case %2d : switch( random(%d) )
                {
LONG
, i, total[i] ) );

                for( j = 0; j < total[i]; j ++ )
                {
                        log_file( LIST_LOG, sprintf( @LONG
               case %d : return %03d000000 + efun::get_xy_point(%03d, flag);
LONG
, j, number[begin], number[begin] ) );
                        begin ++;
                }

                log_file( LIST_LOG, sprintf( @LONG
                }
                break;
LONG
 ) );
        }

        log_file( LIST_LOG, "--- 结束, 记得把最后一个 case 改为 default ---\n\n" );

        log_file( LIST_LOG, "--- 以下用于 /cmd/debug/npc.c ---\n" );

        for( i = 0, begin = 0; i <= k; i ++ )
        {
                log_file( LIST_LOG, sprintf( "     case %3d : id = ({ ", i * 5 ) );

                for( j = 0; j < total[i]; j ++ )
                {
                        log_file( LIST_LOG, sprintf( "%03d, ", number[begin] ) );
                        begin ++;
                }

                log_file( LIST_LOG, sprintf( " });  break;\n" ) );
        }

        log_file( LIST_LOG, "--- 结束, 记得把最后一个 case 改为 default ---\n\n" );

        tell_user( me, "请查看 /log/list.txt。" );

        return 1;       
}
