#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>
#include <public.h>
#include <action.h>
#include <task.h>

inherit DBASE_F;
inherit SAVE_F;

void update_danhhieuvst(object player);
void update_vst(object player);
void vst(object player,object npc);
void org_title(string cName,int flag);
string get_bangphai();
void SAVE_BINARY() { }
string get_save_file()	{ return "data/vosongthanh"SAVE_EXTENSION;}

void vst(object player,object npc)
{
	int index,pos,name_size,id,i,size,flag; 
	object map,*nPlayer,oPlayer;	
       	string tenbang,tenbangcu;
 
			restore();
			if ( player->get_org_name()=="" )
			{
				send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("Quan Viên Vô Song Thành:\nNgươi chưa gia nhập Bang phái nào, không thể chiếm lĩnh !\n"ESC"Xác nhận" ));
				return ;	
			}
			if ( TASK_LEGEND_D->check_task_item_amount(player,"Cờ Hiệu Vô Song Thành") < 1 )
			{
				send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("Quan Viên Vô Song Thành:\nMuốn chiếm lĩnh được Vô Song Thành ngươi phải có Cờ Hiệu Vô Song Thành trên người, nhưng ta nhìn trên người ngươi không có, vậy ngươi muốn làm gì đây ???\n"ESC"Xác nhận" ));
				return ;	
			}
	map = get_map_object(get_z(npc));		
	nPlayer = map->get_all_user();
	size = sizeof(nPlayer);
	if ( !size )
		return ;
	for(i=0;i<size;i++)
	{
		oPlayer = nPlayer[i];
		if ( oPlayer && oPlayer->get_org_name() == player->get_org_name() )
			continue;
		if ( oPlayer->is_die() )
			continue;
		flag = -1;			
		break;	
	}
	if ( flag == -1 )
	{
		send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf("%s:\n Vô Song Cung vẫn còn bang phái khác, không thể chiếm lĩnh!\n"ESC"Thoát",npc->get_name()));
		return ;	
	}
			TASK_LEGEND_D->check_task_item1(player,"Cờ Hiệu Vô Song Thành",1);
			tenbang = player->get_org_name();
			tenbangcu = get_save_2("bangphai");
			set_save_2("bangphai",tenbang);
			save();
			org_title(tenbang,1);
			org_title(tenbangcu,0);
send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("Bạn đã giúp %s chiếm lĩnh thành công Vô Song Thành !!!\n"ESC"Xác nhận", player->get_org_name()));			
send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIR "Trận chiến tranh đoạt Vô Song Thành đã kết thúc, Bang phái "HIY"%s"HIR " với tài trí và sự lãnh đạo của bang chủ đã thành công chiếm lĩnh Vô Song Thành!!!",player->get_org_name()) );						
send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIR "Trận chiến tranh đoạt Vô Song Thành đã kết thúc, Bang phái "HIY"%s"HIR " với tài trí và sự lãnh đạo của bang chủ đã thành công chiếm lĩnh Vô Song Thành!!!",player->get_org_name()) );						
send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIR "Trận chiến tranh đoạt Vô Song Thành đã kết thúc, Bang phái "HIY"%s"HIR " với tài trí và sự lãnh đạo của bang chủ đã thành công chiếm lĩnh Vô Song Thành!!!",player->get_org_name()) );						
}
//Danh hiệu VST
void check_org_title(object who)
{
	object file;
	restore();
	if ( who->get_org_name() == get_save_2("bangphai") )	
	{
		if ( who->get_org_position() == ORG_MASTER )
		{
			if ( !who->have_title("Z888") )
			{
				who->add_title("Z888");
			//	if( file = load_object( SKILL->get_skill_file(0099) ) ) file->can_perform(who);
			}	
			if ( who->have_title("Z889") )
				who->delete_title("Z889");
			if( file = load_object( SKILL->get_skill_file(0099) ) ) file->can_perform(who);	
		}
		else
		{
			if ( who->have_title("Z888") )
				who->delete_title("Z888");
			if ( !who->have_title("Z889") )
				who->add_title("Z889");
		}	
	}
	else
	{
		if ( who->have_title("Z888") )
		{
			who->delete_title("Z888");
			if( file = load_object( SKILL->get_skill_file(0099) ) ) file->remove_perform(who);
		}	
		if ( who->have_title("Z889") )
			who->delete_title("Z889");
	}
}
//Check danh hiệu VST
void org_title(string cName,int flag)
{
	int i,size;
	object orgnpc,who,file;
	string cTmp,*nName;

	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", cName ) );
	if (!objectp(orgnpc))
		return ;
	size = orgnpc->sizeof_member_dbase();
	nName = orgnpc->get_all_member();
	for(i=0;i<size;i++)
	{
		who = find_char(nName[i]);
		if ( !who )
			continue;
		check_org_title(who);
		if ( flag )
		{
			if ( who->get_org_position() == ORG_MASTER )
				{
				who->show_title("Z888");
				if( file = load_object( SKILL->get_skill_file(0099) ) ) file->can_perform(who);
				}
			else
				who->show_title("Z889");
		}
	}	
}
//Check tên bang đã chiếm lĩnh
string get_bangphai()	
{
	string tenbang;
	restore();
	tenbang = get_save_2("bangphai");
	return tenbang?tenbang:"";
}
//add mở khoá
int add_mokhoa(int i)
{
	restore();
	add_save_2("mokhoa",i);
	set_save_2("bangphai",get_save_2("bangphai"));
	save();
	return i;	
}
//check mở khoá
int get_mokhoa()
{
	int abc;
	restore();
	abc = get_save_2("mokhoa");
	return abc?abc:0;	
}
void do_hoatdongkhoa(int sec)
{
	int i,size,tId,p,x,y;
	object *member,npc,map;
	string id;
	sec = sec-1;
	map = get_map_object(889);
	if (!map) return;
	member = map->get_all_user();

	if ( sec > 0 )
	{
		for(i=0,size=sizeof(member);i<size;i++)
		{
			write_user(member[i], sprintf(HIR "Sau %d giây, bạn sẽ bị chuyển ra Vô Song Thành.",sec));
		}

		call_out("do_hoatdongkhoa",1,sec);
	}
	else
	{
		for(i=0,size=sizeof(member);i<size;i++)
		{
			if( p = get_jumpin(888, -1) )
			{	
                x = p/1000, y = p % 1000;
                member[i]->add_to_scene(888, x, y, get_d(member[i]));
			}
		}
			"/sys/party/vst3"->add_mokhoa(- "/sys/party/vst3"->get_mokhoa());
			"/sys/party/vst3"->do_hoatdongkhoa2(300);

	}		
}
void do_hoatdongkhoa2(int sec)
{
		sec--;
		if ( sec > 0 )
		{
		call_out("do_hoatdongkhoa2",1,sec);
		}
		else
		{	
			"/sys/party/vst3"->set_mokhoa1(0);
			"/sys/party/vst3"->set_mokhoa2(0);
			"/sys/party/vst3"->set_mokhoa3(0);
			USER_D->user_channel(sprintf(HIY "Khoá Vô Song Cung 1 "HIR " đã "HIY"Tắt "HIR "!" ));
			USER_D->user_channel(sprintf(HIY "Khoá Vô Song Cung 2 "HIR " đã "HIY"Tắt "HIR "!" ));
			USER_D->user_channel(sprintf(HIY "Khoá Vô Song Cung 3 "HIR " đã "HIY"Tắt "HIR "!" ));
		}		
}
//set mở khoá 1
int set_mokhoa1(int i)
{
	restore();
	set_save_2("khoa1",i);
	set_save_2("bangphai",get_save_2("bangphai"));
	save();
	return i;	
}
//set mở khoá 2
int set_mokhoa2(int i)
{
	restore();
	set_save_2("khoa2",i);
	set_save_2("bangphai",get_save_2("bangphai"));
	save();
	return i;	
}
//set mở khoá 3
int set_mokhoa3(int i)
{
	restore();
	set_save_2("khoa3",i);
	set_save_2("bangphai",get_save_2("bangphai"));
	save();
	return i;	
}
//check khoá 1
int get_mokhoa1()
{
	int abc;
	restore();
	abc = get_save_2("khoa1");
	return abc?abc:0;	
}
//check khoá 2
int get_mokhoa2()
{
	int abc;
	restore();
	abc = get_save_2("khoa2");
	return abc?abc:0;	
}
//check khoá 3
int get_mokhoa3()
{
	int abc;
	restore();
	abc = get_save_2("khoa3");
	return abc?abc:0;	
}