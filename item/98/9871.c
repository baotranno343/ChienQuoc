#include <ansi.h>
inherit ITEM;
inherit COMBINED;
void target(object who,string arg);
// 函数：构造处理
void create()
{
        set_name("Công Văn Truy Nã");//缉捕公文
        set_picid_1(9815);
        set_picid_2(9815);
        set_unit("张");
        set_value(500);
        set_amount(1);
        
	set_2( "use", ([
                "target"          : (: target :),
                	]) );
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Công văn dùng để xác định vị trí tội phạm."; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	int type,i,size;
	string buf="",robber,*team;
	object obj;

	robber = who->get_task("robber");
	if ( stringp(robber) )
	{
		obj = find_any_char(robber);
		if ( objectp(obj) && obj->is_robber() )
		{
			buf = sprintf(ESC"%s\nuse %x# target.1\n",obj->get_name(),getoid(item));			
		}
	}
	robber = who->get_task("criminal");
	if ( stringp(robber) )
	{

		obj = find_any_char(robber);
		if ( objectp(obj) && obj->is_criminal() )
		{
			buf += sprintf(ESC"%s\nuse %x# target.2\n",obj->get_name(),getoid(item));			
		}
	}
	robber = who->get_save_2("mastertask.target");
	if ( stringp(robber) )
	{
		type = who->get_save_2("mastertask.type");
		if ( type == 8 || type == 9 || type == 13 || type == 12 )
		{	
			team = explode(robber,"|");
			for(i=0,size=sizeof(team);i<size;i++)
			{
				obj = find_any_char(team[i]);
				if ( objectp(obj) && obj->get("user") == who->get_number() )
				{
					buf += sprintf(ESC"%s\nuse %x# target.3.%d\n",obj->get_name(),getoid(item),i);			
				}				
			}
						

		}
	}
	i = who->get_save_2("dodolook_task.npcid");
	if ( i )
	{
		obj = find_any_char(sprintf("%x#",i));
		if ( objectp(obj) && obj->is_dodolook() )
		{
			buf = sprintf(ESC"%s\nuse %x# target.4\n",obj->get_name(),getoid(item));			
		}
	}
	i = who->get_save_2("master_hide.npcid");
	if ( i )
	{
		obj = find_any_char(sprintf("%x#",i));
		if ( objectp(obj) && obj->is_master_hide_task() )
		{
			buf = sprintf(ESC"%s\nuse %x# target.5\n",obj->get_name(),getoid(item));			
		}
	}



	if ( sizeof(buf) )
	{
		buf = "Bạn muốn tìm vị trí của ai ?\n"+
			buf + ESC "Rời khỏi.\nCLOSE\n";
		send_user( who, "%c%c%w%s", ':',3,0,buf);
	}
	return 0;	
}

void target(object who,string arg)
{
	int i,j,z;
	string robber,*team;
	object obj;
	
	if ( sscanf(arg,"%d.%d",i,j) != 2 )
		i = to_int(arg);
	switch(i)
	{
	case 1:
		robber = who->get_task("robber");
		if ( !stringp(robber) )
			return ;
		obj = find_char(robber);
		if ( !obj || obj->is_robber()==0)
			return;
		z = get_z(obj);
		who->set_mtask_xy(z,get_x(obj), get_y(obj),getoid(obj),obj->get_name());
		if( z == get_z(who) )
			who->send_mtask_xy(z);
		break;
	case 2:
		robber = who->get_task("criminal");
		if ( !stringp(robber) )
			return ;
		obj = find_char(robber);
		if ( !obj || obj->is_criminal()==0)
			return;
		z = get_z(obj);
		who->set_mtask_xy(z,get_x(obj), get_y(obj),getoid(obj),obj->get_name());
		if( z == get_z(who) )
			who->send_mtask_xy(z);
		break;		
	case 3:
		robber = who->get_save_2("mastertask.target");
		if ( !stringp(robber) )
			return ;
		team = explode(robber,"|");
		if ( j >= sizeof(team) )
			return;
		robber = team[j];
		obj = find_char(robber);
		if ( !obj || obj->get("user") != who->get_number() )
			return;
		z = get_z(obj);
		who->set_mtask_xy(z,get_x(obj), get_y(obj),getoid(obj),obj->get_name());
		if( z == get_z(who) )
			who->send_mtask_xy(z);
		break;	
	case 4:
		i = who->get_save_2("dodolook_task.npcid");
		if ( !i )
			return ;
		obj = find_char(sprintf("%x#",i));
		if ( !obj || obj->is_dodolook()==0)
			return;
		z = get_z(obj);
		who->set_mtask_xy(z,get_x(obj), get_y(obj),getoid(obj),obj->get_name());
		if( z == get_z(who) )
			who->send_mtask_xy(z);
		break;			
	case 5:
		i = who->get_save_2("master_hide.npcid");
		if ( !i )
			return ;
		obj = find_char(sprintf("%x#",i));
		if ( !obj || obj->is_master_hide_task()==0)
			return;
		z = get_z(obj);
		who->set_mtask_xy(z,get_x(obj), get_y(obj),getoid(obj),obj->get_name());
		if( z == get_z(who) )
			who->send_mtask_xy(z);
		break;		
	default:
		return;	
	}
	if ( get_amount() <= 1 )
	{
        	remove_from_user();
        	destruct(this_object());
        }
        else
        	add_amount(-1);
        send_user(who,"%c%s",';',"Đã tìm ra vị trí, hãy nhấn ALT+D để xem vị trí chấm vàng trên bản đồ.");	
}