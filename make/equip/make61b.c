
#define CPP_FILE        __DIR__ "61b.cc"
#define HTM_FILE        __DIR__ "60b.htm"
#define TEXT_FILE       __DIR__ "61b.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit, type;
        int id, pic1, pic2, level, value, lasting, dp, pp, hp, mp, color1, color2, color3, color4;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "# 基本衣服(女)\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %s %d %d %d %d %d %d %d %x %x %x %x %s", 
                        id, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, color1, color2, color3, color4, type ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        switch( type )
                        {
                  case "布衣" : type = "F_BUYI";  break;
                  case "劲装" : type = "F_JINZHUANG";  break;
                  case "背子" : type = "F_BEIZI";  break;
                  case "襦裙" : type = "F_RUQUN";  break;
                  case "皮甲" : type = "F_PIJIA";  break;
                  case "软甲" : type = "F_RUANJIA";  break;
                  case "铠甲" : type = "F_KAIJIA";  break;
                  case "战甲" : type = "F_ZHANJIA";  break;
                        }

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, type, color2, color1, color4, color3, name ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, level, "女", "无", dp, pp, hp, mp, lasting / 100, lasting / 100, value ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
