
#define TEXT_FILE       __DIR__ "pet.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
	int i,size,level,con,str,cps,mp,ma,md,dod,dex,as,ms,life,ski,j,count,tmp4,iLev;
	string cTmp,*nTmp,name,file,tmp,tmp1,cSki,*nTmp1,tmp3,cKind;

        nTmp = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(nTmp);
        file = "make/beastinfo.txt";
	rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
        log_file(file,"mapping mpBeastInfo = ([ \n");
        tmp = "";
        for( i = 0; i < size; i ++ )
	{ 
//		if ( (j = sscanf(nTmp[i],"%s %d %d %d %d %d %d %d %d %d %d %d %d %s",name,level,con,str,cps,mp,ma,md,dex,as,ms,life,ski,cSki)) != 12 )
//			continue;
		name=0;level=0;con=0;str=0;cps=0;mp=0;ma=0;md=0;dex=0;as=0;ms=0;life=0;ski=0;cSki=0;iLev=0;cKind=0;
		sscanf(nTmp[i],"%s %d %d %d %d %d %d %d %d %s %d %d %d %d %d %s",name,level,con,str,cps,mp,ma,md,dex,cKind,iLev,as,ms,life,ski,cSki) ;
		if ( !name )
			continue;
//tell_user(find_char("971"),"%s %s",cKind, cSki);
		if ( stringp(cSki) )
		{
			nTmp1 = explode(cSki," ");
			cSki = "";
			count=sizeof(nTmp1);
			for(j=0;j<count;j++)
			{
				tmp4 = "quest/pet"->get_beast_skill(nTmp1[j]);
				if ( !tmp4 )
					continue;
				cSki += sprintf("%d,",tmp4);
			}
		}
		else
			cSki = "";
		tmp1 = sprintf( "\"%s\" : ([\"level\":%d,\"con\":%d,\"str\":%d,\"cps\":%d,\"mp\":%d,\"ma\":%d,\"md\":%d,\"dex\":%d,\"att_spe\":%d,\"walk_spe\":%d,\"life\":%d ,\"max_ski\":%d,\"skill\": ({%s}),\"iLev\":%d,\"cKind\":\"%s\"]),", name,level,con,str,cps,mp,ma,md,dex,as,ms,life,ski,cSki,iLev,cKind);
		tmp += "		"+tmp1 + "\n";
	}
        log_file(file,tmp+"\n		]); \n");

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}

