
#define CPP_FILE        __DIR__ "60z.cc"
#define HTM_FILE        __DIR__ "60x.htm"
#define TEXT_FILE       __DIR__ "60z.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit, type;
        int id, pic1, pic2, level, value, lasting, dp, pp, hp, mp, rate, color1, color2, color3, color4;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "# 法术衣服(男)\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %s %d %d %d %d %d %d %d %d%% %x %x %x %x %s", 
                        id, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, rate, color1, color2, color3, color4, type ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        switch( type )
                        {
                  case "布衣" : type = "M_BUYI";  break;
                  case "劲装" : type = "M_JINZHUANG";  break;
                  case "长袍" : type = "M_CHANGPAO";  break;
                  case "官袍" : type = "M_GUANPAO";  break;
                  case "皮甲" : type = "M_PIJIA";  break;
                  case "软甲" : type = "M_RUANJIA";  break;
                  case "铠甲" : type = "M_KAIJIA";  break;
                  case "战甲" : type = "M_ZHANJIA";  break;
                        }

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, rate, type, color2, color1, color4, color3, name ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, level, "男", "茅　山<BR>昆仑山", dp, pp, lasting / 100, lasting / 100, value ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
