
#define HTM_FILE        __DIR__ "30.htm"
#define TEXT_FILE       __DIR__ "mid_product.txt"
#define LIST_LOG        "list.txt"
#define LIST_LOG_2      "list2.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file,tmp="";
        int id, pic1, pic2, combined, value;
        int i, size,rr;
	mapping mpTmp=([]);
	string name1,name2,name3,r1,r2,r3;
        line = explode( read_file( TEXT_FILE ), "\n" );
	
	file = "make/item/itemlist";
        size = sizeof(line);
        tmp = "\n([\n";
        for( i = 0; i < size; i ++ ) 
        {
        	name1="";
        	name2="";
        	name3="";
        	r1=r2=r3=0;
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %s %d %s %d", 
                         name1,r1,name2,r2,name3,r3) )
                {

                	tmp += sprintf("%19s : %3d, %19s : %3d, %19s : %3d,\n",file->get_item_file(name1),r1,file->get_item_file(name2),r2,file->get_item_file(name3),r3);
                	rr += r1 + r2 + r3;
                	if ( sizeof(name1) && mpTmp[name1] )
                		tell_user(me,name1);
                	if ( sizeof(name1) && mpTmp[name2] )
                		tell_user(me,name2);
                	if ( sizeof(name1) && mpTmp[name3] )
                		tell_user(me,name3);
                	mpTmp[name1] = r1;
                	mpTmp[name2] = r2;
                	mpTmp[name3] = r3;
                }
        }
	tell_user(me,"rate %d %d",rr,sizeof(mpTmp));
        tmp += "\n])\n";
        log_file("make/mid_product.txt",tmp);

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
