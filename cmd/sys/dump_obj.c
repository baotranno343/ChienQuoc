mapping mpFile = ([]);
// 函数：命令处理
int main( object me, string arg )
{
	int i,size;
	object item,*inv,*nObj;
	string file,cTmp="",*tmp;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        mpFile = ([]);
	nObj = objects();
	for(i=0,size=sizeof(nObj);i<size;i++)
	{
		item = nObj[i];
		if ( !item )
			continue;
		if ( get_z(item) )
			continue;
		file = get_file_name(item);
		mpFile[file] = mpFile[file] +1;
	}
	tmp = keys(mpFile);
	for(i=0,size=sizeof(tmp);i<size;i++)
	{
		cTmp += sprintf("%s %d\n",tmp[i],mpFile[tmp[i]]);
	}
	log_file("dump_obj.txt",sprintf("\ndump begin size %d\n",size));
	log_file("dump_obj.txt",cTmp);
	
	return 1;
}
