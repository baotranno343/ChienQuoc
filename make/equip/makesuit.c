
#define CPP_FILE        __DIR__ "suit.cc"
#define HTM_FILE        __DIR__ "suit.htm"
#define TEXT_FILE       __DIR__ "suit1.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, type, fam, type2,cKind,desc;
        int id, num, pic, level, showlevel, value, lasting, ap, dp, cp, pp, sp,hp,mp;
        int i, size, olddir, dir, oldid, famtype, final,suits;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        olddir = 0; oldid = 0;
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %d %s %s %d %d %s %s %d %d %d %d %d %d %d %d %s", 
                	suits,pic,name,cKind,value,lasting,fam,type,level,dp,pp,ap,cp,hp,mp,sp,desc) )
                {
                	switch(type)
                	{
                	case "头":
                		dir = 55;
                		type = "HEAD";
                		break;
                	case "衣服":
                		dir = 56;
                		type = "ARMOR";
                		break;
                	case "项链":
                		dir = 57;
                		type = "NECK";
                		break;
                	case "腰带":
                		dir = 58;
                		type = "WAIST";
                		break;
                	case "鞋":
                		dir=59;
                		type = "BOOTS";
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
                	case "昆仑":
                	case "昆仑山":
                		famtype = 6;
                		break;
                	case "云梦":
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
                        log_file( file, sprintf(cpp, type, suits,famtype, cKind,name, pic, pic, level, value, lasting, ap, dp, cp, pp, sp, hp, mp, name,desc ) );
                        file = LOG_DIR + file;  file->do_nothing();                        
                        log_file( LIST_LOG, sprintf("\"%s\": \"\\\"/item/final/%02d/%04d\\\"\", \n", name+fam, dir, id) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
