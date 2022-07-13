
#define CPP_FILE        __DIR__ "weapon.cc"
#define HTM_FILE        __DIR__ "72.htm"
#define TEXT_FILE       __DIR__ "weapon.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, type, fam, type2;
        int id, num, pic, level, showlevel, value, lasting, ap, dp, cp, sp;
        int i, size, olddir, dir, oldid, famtype;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "# 刀\n\n" );

        size = sizeof(line);
        olddir = 0; oldid = 0;
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %s %d %d %s %d %d %d %d %d %d %d", 
                        type, name, pic, showlevel, fam, level, value, lasting, ap, dp, cp, sp ) )
                {
                	switch(type)
                	{
                	case "BLADE":
                		dir = 72;
                		type2 = "刀法";
                		break;
                	case "SPEAR":
                		dir = 74;
                		type2 = "枪法";
                		break;
                	case "SWORD":
                		switch(fam)
                		{
                		default: dir = 76; break;
                		case "茅山": dir = 77; break;
                		case "昆仑山": dir = 78; break;
                		case "云梦泽": dir = 79; break;
                		}
                		type2 = "剑法";
                		break;
                	case "STICK":
                		dir = 75;
                		type2 = "棍法";
                		break;
                	case "UNARMED":
                		dir = 70;
                		type2 = "拳法";
                		break;
                	case "THROWING":
                		dir = 71;
                		type2 = "暗器";
                		break;
                	}
                	switch(fam)
                	{
                	default:
                		famtype = 8;
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
                	if (id==0) id = 1;
                	if (oldid==id) id = oldid + 1;
                	oldid = id;
                        file = sprintf("make/%02d/%04d.c", dir, id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, (dir==71)?"MISSILE":"WEAPON", famtype, name, pic, pic, level, value, lasting, ap, dp, cp, sp, type, showlevel, type2 ) );
                        file = LOG_DIR + file;  file->do_nothing();                        
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
