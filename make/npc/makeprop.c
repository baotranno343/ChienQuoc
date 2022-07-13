
#define TEXT_FILE       __DIR__ "prop.txt"
#define LIST_LOG        "list.txt"

int *array_hp, *array_mp, *array_ap, *array_dp, *array_cp, *array_pp, *array_sp, *array_speed, *array_speed2;

// 函数：命令处理
int main( object me, string arg )
{
        string *line;
        int level, hp, mp, ap, dp, cp, pp, sp, speed, speed2;
        int max, i, size;

        array_hp = allocate(200);
        array_mp = allocate(200);
        array_ap = allocate(200);
        array_dp = allocate(200);
        array_cp = allocate(200);
        array_pp = allocate(200);
        array_sp = allocate(200);
        array_speed = allocate(200);
        array_speed2 = allocate(200);
 
        line = explode( read_file( TEXT_FILE ), "\n" );

        max = 0;
        size = sizeof(line);
        for( i = 0; i < size; i ++ )
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %d %d %d %d %d %d %d %d %d", level, hp, mp, ap, dp, cp, pp, sp, speed, speed2 ) )
                {
                        array_hp[level] = hp;
                        array_mp[level] = mp;
                        array_ap[level] = ap;
                        array_dp[level] = dp;
                        array_cp[level] = cp;
                        array_pp[level] = pp;
                        array_sp[level] = sp;
                        array_speed[level] = speed;
                        array_speed2[level] = speed2;
                }
                if( level > max ) max = level;
        }

        log_file( LIST_LOG, sprintf( @LONG
private int *HP = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_hp[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *MP = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_mp[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *AP = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_ap[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *DP = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_dp[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *CP = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_cp[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *PP = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_pp[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *SP = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_sp[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *Speed = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_speed[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        log_file( LIST_LOG, sprintf( @LONG
private int *Speed2 = ({
LONG ) );
        for( i = 0; i <= max; i ++ )
        {
                if( i % 10 == 0 ) log_file( LIST_LOG, "        " );
                log_file( LIST_LOG, sprintf( "%d, ", array_speed2[i] ) );
                if( i % 10 == 9 ) log_file( LIST_LOG, "\n" );
        }
        log_file( LIST_LOG, sprintf( @LONG

});

LONG ) );

        tell_user( me, "请查看 /log/list.txt 文件。" );

        return 1;       
}
