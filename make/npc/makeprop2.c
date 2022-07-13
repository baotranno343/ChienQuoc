
#define TEXT_FILE       __DIR__ "prop2.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string *line;
        int level, exp;
        int i, size;

        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ )
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %d", level, exp ) )
                {
                        if( i % 10 == 0 ) log_file( LIST_LOG, "\n        " );
                        log_file( LIST_LOG, sprintf( "%d, ", exp ) );
                }
        }

        tell_user( me, "请查看 /log/list.txt 文件。" );

        return 1;       
}
