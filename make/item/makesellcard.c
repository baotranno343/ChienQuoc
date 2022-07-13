#define CPP_FILE        __DIR__ "sell_magic_card.cc"
#define TEXT_FILE       __DIR__ "sell_magic_card.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, xy, city;
        string *good = ({ "", "", "", "", "", "", "", "", "", "" });
        int *list = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int id, pic, z, x, y, d, i, j, size,sell,count;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        log_file( LIST_LOG, "# 变身卡\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                name = "";x=0;y=0;id=0;xy="";
                if( sscanf( line[i], "%s %d %d %s %d %d %d", 
                        name,x,id,xy,sell,y,count) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        log_file( file, sprintf( cpp,sell,sell,name,x,x,y,id,3600,xy, ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件及" );

        return 1;       
}

