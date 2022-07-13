
#define CPP_FILE        __DIR__ "65y.cc"
#define HTM_FILE        __DIR__ "65x.htm"
#define TEXT_FILE       __DIR__ "65y.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit, type;
        int id, pic1, pic2, level, value, lasting, dp, pp, hp, mp, rate1, rate2, rate3, color1, color2;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "# 敏捷帽子(男)\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %s %d %d %d %d %d %d %d %d %d%% %d%% %x %x %s",
                        id, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, rate1, rate2, rate3, color1, color2, type ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        switch( type )
                        {
                  case "平帽" : type = "M_PINGMAO";  break;
                case "武生帽" : type = "M_WUSHENGMAO";  break;
                  case "道冠" : type = "M_DAOGUAN";  break;
                  case "毡帽" : type = "M_ZHANMAO";  break;
                  case "皮帽" : type = "M_PIMAO";  break;
                case "紫金冠" : type = "M_ZIJINGUAN";  break;
                  case "缨盔" : type = "M_YINGKUI";  break;
                  case "战盔" : type = "M_ZHANKUI";  break;
                        }

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, name, pic1, pic2, unit, level, value, lasting, dp, pp, hp, mp, rate1, rate2, rate3, type, color2, color1, name ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, level, "男", "唐　门<BR>云梦泽", dp, pp, lasting / 100, lasting / 100, value ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
