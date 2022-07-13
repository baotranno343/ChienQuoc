
#define CPP_FILE        __DIR__ "vweapon.cc"
#define HTM_FILE        __DIR__ "std.htm"
#define TEXT_FILE       __DIR__ "vweapon.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, type, fam, type2;
        int id, num, pic, level, showlevel, value, lasting, ap, dp, cp, sp;
        int i, size, olddir, dir, oldid, famtype, final;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        olddir = 0; oldid = 0;
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %s %d %s %d %d %d %d %d %d %d", 
                        type, final, name, pic, fam, level, value, lasting, ap, dp, cp, sp ) )
                {
                	showlevel = level / 10 + 1;
                	switch(type)
                	{
                	case "刀":
                		dir = 72;
                		type2 = "刀法";
                		type = "BLADE";
                		break;
                	case "枪":
                		dir = 74;
                		type2 = "枪法";
                		type = "SPEAR";
                		break;
                	case "剑":
                		dir=76;
                		type2 = "剑法";
                		type = "SWORD";
                		break;
                	case "棍":
                		dir = 75;
                		type2 = "棍法";
                		type = "STICK";
                		break;
                	case "拳套":
                		dir = 70;
                		type2 = "拳法";
                		type = "UNARMED";
                		break;
                	case "暗器":
                		dir = 71;
                		type2 = "暗器";
                		type = "THROWING";
                		break;
                	}
                	switch(fam)
                	{
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
                	if (fam=="无门派") id = level;
                	else id = 1000+ level;
                	oldid = id;
                        file = sprintf("make/%02d/%04d.c", dir, id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, (dir==71)?"MISSILE":"WEAPON", famtype, final, name, pic, pic, level, value, lasting, ap, dp, cp, sp, type, showlevel, type2 ) );
                        file = LOG_DIR + file;  file->do_nothing();                        
                        log_file( LIST_LOG, sprintf("\"%s\": \"\\\"/item/final/%02d/%04d\\\"\", \n", name, dir, id) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
