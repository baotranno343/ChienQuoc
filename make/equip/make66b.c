
#define CPP_FILE        __DIR__ "66b.cc"
#define HTM_FILE        __DIR__ "65b.htm"
#define TEXT_FILE       __DIR__ "66b.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit, type;
        int id, pic1, pic2, level, value, lasting, dp, pp, hp, mp, color1, color2;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "# 基本帽子(女)\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %s %d %d %d %d %d %d %d %x %x %s",
                        id, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, color1, color2, type ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        switch( type )
                        {
                  case "平帽" : type = "F_PINGMAO";  break;
                case "武生帽" : type = "F_WUSHENGMAO";  break;
                  case "道冠" : type = "F_DAOGUAN";  break;
                  case "纱帽" : type = "F_SHAMAO";  break;
                  case "皮帽" : type = "F_PIMAO";  break;
                case "紫金冠" : type = "F_ZIJINGUAN";  break;
                  case "缨盔" : type = "F_YINGKUI";  break;
                  case "战盔" : type = "F_ZHANKUI";  break;
                        }

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, type, color2, color1, name ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, level, "女", "无", dp, pp, hp, mp, lasting / 100, lasting / 100, value ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
