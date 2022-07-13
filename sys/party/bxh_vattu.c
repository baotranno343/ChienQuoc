#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>
#include <public.h>
#include <action.h>

inherit DBASE_F;
inherit SAVE_F;

void update_bxh_vattu(object player);
void bxh_vattu(object player,object npc);
void SAVE_BINARY() { }
string get_save_file()	{ return "data/bangxephangvattu"SAVE_EXTENSION;}

void bxh_vattu(object player,object npc)
{
	int index,pos,name_size,id;  
       	string tmp="",cmd="",playername,ben,playerid,result,blank="";
       	blank = repeat_string(" ",12); 
	restore();
	for(index = 1; index<=10;index++)
	{
		id = get_save_2(sprintf("luu.%d",index));
		if(!id)
		{
			tmp = sprintf(" ""%2d: %s ",index,"Chưa cập nhật.");
			tmp+="\n";
		}
		else
		{
			playername = get_save_2(sprintf("nguoichoi.%d.ten",id));		
			playerid = get_save_2(sprintf("nguoichoi.%d.id",id));
			ben = sprintf("%c+%d,%s=%d%c-", '\t', 0x000000, playername, playerid, '\t');	
			name_size = strlen(ben);
			if(name_size<=12)
			{
				ben+= repeat_string(" ",12-name_size);
			}
			switch(index)
			{
			case 1:
				tmp = sprintf(" ""R""%2d: %12s (%d) %10s Tích luỹ: %d"NOR,1,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));					
				break;
			case 2:
				tmp = sprintf(" ""M""%2d: %12s (%d) %10s Tích luỹ: %d"NOR,2,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));					
				break;
			case 3:
				tmp = sprintf(" ""B""%2d: %12s (%d) %10s Tích luỹ: %d"NOR,3,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));			
				break;
			case 4:
				tmp = sprintf(" ""%2d: %12s (%d) %10s Tích luỹ: %d",4,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));			
				break;		
			case 5:
				tmp = sprintf(" ""%2d: %12s (%d) %10s Tích luỹ: %d",5,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));	
				break;	
			case 6:
				tmp = sprintf(" ""%2d: %12s (%d) %10s Tích luỹ: %d",6,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));	
				break;	
			case 7:
				tmp = sprintf(" ""%2d: %12s (%d) %10s Tích luỹ: %d",7,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));	
				break;
			case 8:
				tmp = sprintf(" ""%2d: %12s (%d) %10s Tích luỹ: %d",8,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));	
				break;	
			case 9:
				tmp = sprintf(" ""%2d: %12s (%d) %10s Tích luỹ: %d",9,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));	
				break;	
			case 10:
				tmp = sprintf(" ""%2d: %12s (%d) %10s Tích luỹ: %d",10,ben,playerid," ",get_save_2(sprintf("nguoichoi.%d.vt",id)));	
				break;	
			}	
			tmp+="\n";
		}
		cmd+=tmp;
		
	}
		result=sprintf(sprintf("Điểm tích luỹ Vật tư của bạn là %d. \n",player->get_save("vattuabc"))+cmd);
		result+=sprintf(ESC "Xác nhận\nCLOSE\n");
		result+=sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),result);
}
void update_bxh_vattu(object player)
{
	int size,index,pos,oldid,id1,amount,i,phai;
	int id = player->get_number();
	string name = player->get_name();
	amount = player->get_save("vattuabc");
	if(get_save_2(sprintf("nguoichoi.%d",id)))
	{
		if(get_save_2(sprintf("nguoichoi.%d.ten",id))== name)
		{
			set_save_2(sprintf("nguoichoi.%d.vt",id),amount);
			set_save_2(sprintf("nguoichoi.%d.id",id),id);
			pos = get_save_2(sprintf("nguoichoi.%d.hang",id));
		}
	}
	else if((size = get_save_2(sprintf("luu.soluong"))) < 10)
	{
			pos = size+1;
			set_save_2("luu.soluong",pos);
			set_save_2(sprintf("luu.%d",pos),id);
			set_save_2(sprintf("nguoichoi.%d.ten",id),name);
			set_save_2(sprintf("nguoichoi.%d.hang",id),pos);
			set_save_2(sprintf("nguoichoi.%d.vt",id),amount);
			set_save_2(sprintf("nguoichoi.%d.id",id),id);
	}
	else 
	{
		oldid = get_save_2(sprintf("luu.%d",size));
		if(get_save_2(sprintf("nguoichoi.%d.vt",oldid))< amount)
		{
			pos = size;
			delete_save_2(sprintf("nguoichoi.%d",oldid));
			set_save_2(sprintf("luu.%d",pos),id);
			set_save_2(sprintf("nguoichoi.%d.ten",id),name);
			set_save_2(sprintf("nguoichoi.%d.hang",id),pos);
			set_save_2(sprintf("nguoichoi.%d.vt",id),amount);
			set_save_2(sprintf("nguoichoi.%d.id",id),id);
			set_save_2("luu.soluong",pos);		
		}
	}
	if(pos)
	{
		for(index = pos; index > 1; index--)
		{
			id = get_save_2(sprintf("luu.%d",index));
			id1 = get_save_2(sprintf("luu.%d",index-1));
			if(get_save_2(sprintf("nguoichoi.%d.vt",id1))>= get_save_2(sprintf("nguoichoi.%d.vt",id)))
			{
				break;
			}
			set_save_2(sprintf("luu.%d",index),id1);			
			set_save_2(sprintf("nguoichoi.%d.hang",id1),index);
			set_save_2(sprintf("luu.%d",index-1),id);
			set_save_2(sprintf("nguoichoi.%d.hang",id),index-1);	
		}
		save();
	}
	//save();
}