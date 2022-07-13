
#define CPP_FILE        __DIR__ "shenshou.cc"
#define HTM_FILE        __DIR__ "shenshou.htm"
#define TEXT_FILE       __DIR__ "shenshou.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit,desc;
        int id, pic1, pic2, combined, value;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %d %d %s %d %s", 
                        name,pic1,pic2,value,unit,combined,desc ) )
                {
                        file = sprintf("make/%04d.c", 800+i );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        log_file( file, sprintf(cpp,name,pic1,pic2,pic1,value,desc,"%c%c%w%s","%x#"));
                        file = LOG_DIR + file;  file->do_nothing();

                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
