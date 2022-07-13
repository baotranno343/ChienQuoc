
// 程序：为 makenpc.c 准备杂物表

#define TEXT_FILE       __DIR__ "list.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string *line, name;
        int id, i, size;

        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( sscanf( line[i], "%d %s", id, name ) )
                {
                        log_file( LIST_LOG, sprintf( @LONG
        "%s" : "\"/item/%02d/%04d\"",
LONG
, name, id / 100, id ) );
                }
        }

        tell_user( me, "请查看 /log/list.txt 文件。" );

        return 1;
}
