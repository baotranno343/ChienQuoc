
#define CPP_FILE        __DIR__ "cloth.cc"
#define HTM_FILE        __DIR__ "60b.htm"
#define TEXT_FILE       __DIR__ "cloth.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, type, fam, type2, sex;
        int id, num, pic, level, value, lasting, dp, pp, armor;
        int i, size, olddir, dir, oldid, famtype;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "# 衣服\n\n" );

        size = sizeof(line);
        olddir = 0; oldid = 0;
        for( i = 0; i < size; i ++ )
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %s %s %d %d %d %d %d",
                        name, pic,  fam, sex, level, value, lasting, dp, pp ) )
                {
                	switch(sex)
                	{
                	case "男":
                		dir = 60;
                		break;
			default:
                		dir = 61;
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
                	else id = 1000*famtype+ level;
                	if (id==0) id = 1;
                	if (oldid==id) id = oldid + 1;
                	oldid = id;
                        file = sprintf("make/%02d/%04d.c", dir, id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
			armor = level /13;
			if (armor >8) armor = 8;
			if (sex=="女") armor += 20;
                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, famtype, name, pic, pic, level, value, lasting, dp, pp, sex=="男"?1:2, armor, name ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;
}
