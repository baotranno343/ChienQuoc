
#define TEXT_FILE       __DIR__ "mirror_npc.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
	int i,size,level,j,count,m,n,rate,spe,rand,color,num;
	string *nTmp,*nTmp1,file,tmp,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,items,itemrate,tmp7;
	string name,strong,weapon,cNpc,cKind;
	
        nTmp = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(nTmp);
        file = "make/mirror_npc.txt";
	rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
        log_file(file,"mapping mpNpc = ([ \n");
        tmp = "";
        for( i = 0; i < size; i ++ )
	{ 
		if ( sscanf(nTmp[i],"%s %s %s %d %s %s %s %d %d %s %d %s",name,tmp1,tmp2,color,cKind,strong,tmp5,level,rand,weapon,spe,items) != 12 )
			continue;
		nTmp1 = explode(items," ");
		count = sizeof(nTmp1);
		itemrate = "";
		num=0;
		for(j=0;j<count;j++)
		{
			tmp6 = "";
			if ( rate=to_int(nTmp1[j]) )
			{
				for(m=j+1;m<count;m++)
				{
					if ( to_int(nTmp1[m]) )
						break;
					if ( sizeof(tmp6) )
						tmp6 += ",";
					tmp7 = "/make/item/itemlist"->get_item_file( nTmp1[m] );
					if( tmp7 == "" ) tell_user(me, "ERR: %s,%s", name,nTmp1[m]);
					tmp6 += tmp7;
				}	
				num += rate;
				tmp6 = sprintf("%d : ({ %s }),",num,tmp6);
			}

			itemrate += tmp6;
		}
		if ( sizeof(itemrate) )
			itemrate = sprintf("\"droprate\" : ([ %s ])",itemrate);
		tmp +=sprintf("	\"%s\" : ([ \"kind\" : \"%s\", \"strong\" : \"%s\", \"level\" : %d, \"rand\" : %d, \"weapon\" : \"%s\",\"spe\" : %d, %s]),\n",name,cKind,strong,level,rand,weapon,spe,itemrate);
	}
        log_file(file,tmp+"\n		]); \n");

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}

