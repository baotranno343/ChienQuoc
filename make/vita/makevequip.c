
#define CPP_FILE        __DIR__ "vequip.cc"
#define HTM_FILE        __DIR__ "std.htm"
#define TEXT_FILE       __DIR__ "vequip.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, type, fam, type2;
        int id, num, pic, level, showlevel, value, lasting, ap, dp, cp, pp, sp;
        int i, size, olddir, dir, oldid, famtype, final;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        olddir = 0; oldid = 0;
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %s %d %s %d %d %d %d %d %d %d %d", 
                        type, final, name, pic, fam, level, value, lasting, ap, dp, cp, pp, sp ) )
                {
                	switch(type)
                	{
                	case "衣服":
                		dir = 60;
                		type = "ARMOR";
                		break;
                	case "帽子":
                		dir = 65;
                		type = "HEAD";
                		break;
                	case "鞋子":
                	case "鞋":
                		dir=88;
                		type = "BOOTS";
                		break;
                	case "项链":
                		dir = 86;
                		type = "NECK";
                		break;
                	case "腰带":
                		dir = 87;
                		type = "WAIST";
                		break;
                	}
                	switch(fam)
                	{
                	case "无门派":
                		famtype = 8;
                		break;
                	default:
                		// 法剑，法术门派可以装备
                		famtype = 9;
                		break;
                	case "桃花源":
                		famtype = 1;
                		break;
                	case "蜀山":
                		famtype = 2;
                		break;
                	case "禁卫军":
                		famtype = 3;
                		break;
                	case "唐门":
                		famtype = 4;
                		break;
                	case "茅山":
                		famtype = 5;
                		break;
                	case "昆仑山":
                		famtype = 6;
                		break;
                	case "云梦泽":
                		famtype = 7;
                		break;
                	}
                	if (olddir!=dir)
                	{
                		mkdir(sprintf(LOG_DIR+"make/%d", dir));
                		olddir = dir;
                	}
                	id = famtype* 1000+ level;
                        file = sprintf("make/%02d/%04d.c", dir, id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf(cpp, type, famtype, final, name, pic, pic, level, value, lasting, ap, dp, cp, pp, sp, name ) );
                        file = LOG_DIR + file;  file->do_nothing();                        
                        log_file( LIST_LOG, sprintf("\"%s\": \"\\\"/item/final/%02d/%04d\\\"\", \n", name+fam, dir, id) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
