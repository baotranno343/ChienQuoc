inherit DBASE_F;
inherit SAVE_F;

#define TIME_INTERVAL 10
#include <ansi.h>
#define MAX_TIMES 2
mapping mpList=([]);
int max = 10;
int index;

string get_save_file()	{ return "data/gonggao"SAVE_EXTENSION;}

void create()
{
	restore();
	call_out("announce",3);
}

//增加公告
void add_msg(object who,string arg)
{
	int i,size=max+1,min,count;
	if ( sscanf(arg, "%d %d %s", min,count,arg) != 3 )
		return ;
	if ( !mapp(mpList) )
		mpList = ([]);
	for(i=1;i<size;i++)
	{
		if ( mapp(mpList[i]) )
			continue;
		mpList[i] = ([ "time" : 60*min, "msg" : arg, "count":count ]);	//间隔时间,消息,次数
		tell_user(who, "%c%s", '>', "公告增加成功!");
		save();
		return ;			
	}
	tell_user(who, "%c%s", '>', "公告已经满了,请先删除无用的公告!");
}

void del_msg(object who,string arg)
{
	int i;

	i = to_int(arg);
	if ( i < 1 || i > max )
		return ;
	map_delete(mpList, i);
	save();
	tell_user(who, "%c%s", '>', sprintf("已经删除第%d条公告!",i));
}

void list_msg(object who)
{
	int i,size=max+1;
	tell_user(who, "%c%s", '>', "公告列表:");
	for(i=1;i<size;i++)
	{
		if ( !mapp(mpList[i]) )
			continue;
		tell_user(who,"%c%s",'>',sprintf("%d. %s",i,mpList[i]["msg"]));
	}
}

void help_msg(object who)
{
	tell_user(who,"%c%s",'>',"增加公告: gonggao add 时间间隔(分钟) 播放次数(0为无限) 消息");
	tell_user(who,"%c%s",'>',"列出所有公告: gonggao list");
	tell_user(who,"%c%s",'>',"删除公告: gonggao del 序号");
}
void announce()
{
	int i,size=max+1,now,iSave;
	remove_call_out("announce");
	call_out("announce",TIME_INTERVAL);
	if ( sizeof(mpList)==0 )
		return;
	now = time();
	if( index == 0 || index >= max )
		index = 1;
	for(i=index;i<size;i++)
	{
		index = i;
		if ( !mapp(mpList[i]) )
			continue;
		if ( now-mpList[i]["lasttime"] < mpList[i]["time"] )
			continue;
		mpList[i]["lasttime"] = now;
		CHAT_D->sys_channel(0,HIY+mpList[i]["msg"]);
		mpList[i]["count"]--;
		if ( mpList[i]["count"] == 0 )
			map_delete(mpList,i);
		iSave++;		
		if ( iSave >= MAX_TIMES )
			break;
	}
//CHAT_D->sys_channel(0,ctime(time()));
	if ( iSave ) save();	
}

// 函数：命令处理
int main( object me, string arg )
{
        string com,arg1;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if ( !stringp(arg) || arg=="")
        {
        	help_msg(me);
        	return 1;
        }

	if ( sscanf(arg, "%s %s", com, arg1) != 2 )
		com = arg;

	if ( com == "add" )
		add_msg(me,arg1);
	else if ( com == "list" )
		list_msg(me);
	else if ( com == "del" )
		del_msg(me,arg1);
	else
		help_msg(me);

        return 1;
}