
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <map.h>
#include <effect.h>
inherit DBASE_F;
/*
	g 		Di chuyển tới bản đồ
	moi %d	Mời người chơi vào bản đồ
	kick %d	Kick người chơi ra khỏi bản đồ
	hm all	Hồi máu cho tất cả người chơi có trên bản đồ
	hm %d	Hồi máu cho người chơi chỉ định
	bt %d	Thiết lập bất tử cho người chơi chỉ định
	hbt %d 	Huỷ bất tử cho người chơi chỉ định
	xoa		Xoá bỏ bản đồ Thi đấu và đẩy tất cả người chơi ra khỏi Bản đồ
*/

// 函数:命令处理
int main( object me, string arg )
{
	string * key, result, tt;
	object * users, player, who;
	int i, size, z, p, x, y, x0, y0, *maps;
	object map;
        if( is_player(me) && me->get_save("muave")<1 ) 
        {
                notify( "Không đủ quyền hạn" );
		return 1;
        }
        if( !arg )
        {
                if (get("maps")==0)
                {                	
                	send_user( me, "%c%s", ':', "Xác nhận phải mở Bản đồ Thi đấu Chiến Quốc không?\n"
                        	ESC "Chấp nhận\n" + "gmmap taomap\n" +
                        	ESC "Rời khỏi\nCLOSE" );
                	return 1;
				}        
                send_user( me, "%c%s", ':', "Muốn thao tác hoạt động gì?\n"
                	ESC "Tiến tới bản đồ Thi Đấu Đấu Trường\n" + "gmmap g 1\n" +
                	ESC "Tiến tới bản đồ Thi đấu CQMC\n" + "gmmap g 2\n" +
                        ESC "Tải lại bản đồ Thi đấu Chiến Quốc\n" + "gmmap taomap\n" +
                       	ESC HIC"Mời ứng cử viên thi đấu vào Bản đồ\n" + "gmmap moi ?\n" +
               //        	ESC HIG"Mời ứng cử viên vào và thiết lập thành khán giả\n" + "gmmap moi2 ?\n" +
                       	ESC "Đuổi ứng cử viên thi đấu ra khỏi Bản đồ\n" + "gmmap kick ?\n" +
				//		ESC "Đuổi Khán Giả ra khỏi Bản đồ\n" + "gmmap kick2 ?\n" +
                       	ESC "Hồi phục máu cho tất cả ứng cử viên thi đấu\n" + "gmmap hm all\n" +
                       	ESC "Hồi phục máu cho ứng cử viên\n" + "gmmap hm ?\n" +
               //        	ESC "Thiết lập cho khán giả đứng xem\n" + "gmmap bt ?\n" +
               //        	ESC "Thiết lập cho khán giả tham gia thi đấu\n" + "gmmap hbt ?\n" +
                       	ESC HIY"Xoá bỏ bản đồ Thi đấu\n" + "gmmap xoa\n" +
                       	ESC "Rời khỏi\nCLOSE" );		
		return 1;	
        }
        key = explode( arg, " ");
       	size = sizeof(key);
       	maps = get("maps"); 
       	if (size==1)
       	{
       		switch(arg)
       		{
		case "taomap":			
			if (maps==0)
			{
				if( ( z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0) ) > 0 )
				{
					p = 885;
					init_virtual_map(z, p);    // 生成虚拟地图
					map = new( "/inh/std/cqmc" );
					map->set_client_id(p);
					set_map_object( map, map->set_id(z) );
					map->set_owner(me);
					map->set_forbbit(0);
					tell_user(me, "Đã tạo thành công Bản đồ Thi đấu Chiến Quốc!");
					maps = ({ z });
				}
				if( ( z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0) ) > 0 )
				{
					p = 891;
					init_virtual_map(z, p);    // 生成虚拟地图
					map = new( "/inh/std/cqmc" );
					map->set_client_id(p);
					set_map_object( map, map->set_id(z) );
					map->set_owner(me);
					map->set_forbbit(0);
					tell_user(me, "Đã tạo thành công Bản đồ Thi đấu giao hữu!");
					maps += ({ z });
				}
				set("maps", maps);
				return 1;
			}
			map = get_map_object(maps[0]);
			if (map)
			{
				"/inh/std/cqmc"->cleanup_badman(map);
				users = "/inh/std/cqmc"->get_users(map);
				if (sizeof(users))
				{
					foreach (player in users) if( is_player(player) ) player->delete_save("no_fight");						
				}
				map->set_forbbit(0);
				tell_user(me, "Thiết lập thành công!");
			}
			map = get_map_object(maps[1]);
			if (map)
			{
				"/inh/std/cqmc"->cleanup_badman(map);
				users = "/inh/std/cqmc"->get_users(map);
				if (sizeof(users))
				{
					foreach (player in users) if( is_player(player) ) player->delete_save("no_fight");						
				}
				map->set_forbbit(0);
				tell_user(me, "Thiết lập thành công!");
			}			
			break;
		case "xoa":
			if (get("maps")==0) return 1;
			map = get_map_object(maps[0]);
		if (map)
		{
			users = "/inh/std/cqmc"->get_users(map);
			if (sizeof(users))
			{
				foreach (who in users) MAP_D->add_to_void(who);												
			}  
			tell_user(me, "Đã xoá bản đồ Thi đấu Chiến Quốc.");
		}
			map = get_map_object(maps[1]);
		if (map)
		{	
			users = "/inh/std/cqmc"->get_users(map);
			if (sizeof(users))
			{
				foreach (who in users) MAP_D->add_to_void(who);												
			} 
			tell_user(me, "Đã xoá bản đồ Thi đấu giao hữu.");
		}
			if (get("maps")!=0) set("maps",0);
			break;
		case "tt":
			if (get("maps")!=0)
			send_user(me,"%c%s",';',HIC"Bây giờ đang là thời gian Thi đấu Chiến Quốc, bạn có thể mua Vé!");
			else
			send_user(me,"%c%s",';',HIG"Bây giờ không phải là thời gian Thi đấu Chiến Quốc, bạn không thể mua Vé!");
			break;									
       		}
       		return 1;
       	}
       	if (size>2)
       	{
       		notify( "Không thể thực hiện!" );
       		return 1;
       	}
	if (maps==0)
	{
		notify( HIY"Chưa tới thời gian Thi đấu!" );
		return 1;
	}
	z = get_z(me);
	if (z!=maps[0] && z!=maps[1]&& key[0]!="g")		
	{
		notify( "Không thể thực hiện !" );
		return 1;
	}		
	map = get_map_object(z);     
	if (!map)  	
	{
		notify( HIY"Chưa tới thời gian thi đấu!" );
		return 1;
	}	
       	switch(key[0])
       	{
	case "g":	
		z = to_int(key[1]);
		z --;
		if (z<0) z = 0;
		if (z>1) z = 1;
		z = maps[z];
		if (z==0)
		{
			notify( "Không thể tới "+sprintf("%d", z)+" !" );
			return 1;
		}			
		if( p = get_jumpin(z, 1) )
		{
		//	me->set_save("no_fight", 1);
			me->add_to_scene(z, p / 1000, p % 1000, 3);			   		 	
		}
		break;       		
       	case "moi":
       		if (key[1]=="?")
       		{       	
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "Xin nhập ID người chơi bạn muốn mời vào bản đồ:\n"
                        	ESC "gmmap moi %s\n");       					
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "Không tìm thấy người chơi này." );
				return 1;
		        }       
		        if (who->is_npc()&&is_gm(me))	
		        {
		                notify( "Đối phương là NPC." );
				return 1;
		        }
              				
       			z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);
       			if( !p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK) ) return 1;
       			x = p / 1000;  y = p % 1000;
			who->add_to_scene( z, x, y, 3, 40971, 0, 40971, 0 );
			if ( who->get_save("csdvp") < 1 ) {
			who->add_save("csdvp",1);
			}
			tell_user(me, "Đã mời "+who->get_name());
       		}
       		break;
		case "moi2":
       		if (key[1]=="?")
       		{       	
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "Xin nhập ID người chơi bạn muốn mời vào bản đồ ( sẽ thiết lập thành khán giả ):\n"
                        	ESC "gmmap moi2 %s\n");       					
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "Không tìm thấy người chơi này." );
				return 1;
		        }       
		        if (who->is_npc()&&is_gm(me))	
		        {
		                notify( "Đối phương là NPC." );
				return 1;
		        }		        			
       			z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);
       			if( !p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK) ) return 1;
       			x = p / 1000;  y = p % 1000;
			who->add_to_scene( z, x, y, 3, 40971, 0, 40971, 0 );
			tell_user(me, "Đã mời "+who->get_name());
				who->set_no_fight(1);
		        tell_user(me, "Đã thiết lập cho "+who->get_name()+" chế độ Không thể tấn công.");	
				set_effect_2( who, EFFECT_CHAR_INVISIBLE, 3000, 10 );    // 每十秒减血
        		CHAR_CHAR_D->init_loop_perform(who);
	        	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9000, 1, UNDER_FOOT, PF_LOOP );    // 半透明
			set_invisible(who, 1);
			who->set_save("no_visible", 1);
			send_user( who, "%c%c%c", 0x3d, 241, 2 );		
       		}
       		break;	
       	case "kick":
       		if (key[1]=="?")
       		{       	
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "Xin nhập ID người chơi bạn muốn đá ra khỏi bản đồ:\n"
                        	ESC "gmmap kick %s\n");          					
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "Không tìm thấy người chơi này." );
				return 1;
		        }  
		        MAP_D->add_to_void(who);  
             who->delete_save("csdvp",1);				
		        tell_user(me, "Đã đuổi "+who->get_name()+" ra khỏi bản đồ.");	
       		}       	
       		break;
		case "kick2":
       		if (key[1]=="?")
       		{       	
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "Xin nhập ID khán giả bạn muốn đá ra khỏi bản đồ:\n"
                        	ESC "gmmap kick2 %s\n");          					
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "Không tìm thấy người chơi này." );
				return 1;
		        }
       /*         who->set_no_fight(0);
		        tell_user(me, "Đã thiết lập cho "+who->get_name()+" chế độ Có thể tấn công.");	  
				set_effect_2( who, EFFECT_CHAR_INVISIBLE, 0, 0);
			who->set_save("no_visible", 0);
			set_invisible(who, 0);
			CHAR_CHAR_D->init_loop_perform(who);
			send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9000, 1, UNDER_FOOT, PF_STOP );	 */
			
		        MAP_D->add_to_void(who);       		
		        tell_user(me, "Đã đuổi "+who->get_name()+" ra khỏi bản đồ.");	
       		}       	
       		break;
       	case "hm":
       		if (key[1]=="?")
       		{       
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "Xin nhập ID người chơi muốn hồi phục sinh lực:\n"
                        	ESC "gmmap hm %s\n");         						
       		}
       		else
       		if (key[1]=="all")
       		{
			users = "/inh/std/cqmc"->get_users(map);
			if (sizeof(users))
			{
				foreach (who in users)
				{
				        who->set_hp( who->get_max_hp() );
				        who->set_mp( who->get_max_mp() );
				        who->set_yuan( who->get_max_yuan() );						
				}						
			} 
			tell_user(me, "Đã hồi phục sinh lực cho tất cả người chơi.");      			
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "Không tìm thấy người chơi này." );
				return 1;
		        }  
		        who->set_hp( who->get_max_hp() );
		        who->set_mp( who->get_max_mp() );
		        who->set_yuan( who->get_max_yuan() );	
		        tell_user(me, "Đã hồi phục sinh lực cho "+who->get_name()+".");		               			
       		}       	
       		break;
       	case "bt":
       		if (key[1]=="?")
       		{       			
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "Xin nhập ID người chơi bạn muốn cấm tấn công:\n"
                        	ESC "gmmap bt %s\n");         			
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "Không tìm thấy người chơi này." );
				return 1;
		        }  
		       who->set_no_fight(1);	
		        tell_user(me, "Đã thiết lập cho "+who->get_name()+" chế độ Không thể tấn công.");	
				set_effect_2( who, EFFECT_CHAR_INVISIBLE, 3000, 10 );    // 每十秒减血
        		CHAR_CHAR_D->init_loop_perform(who);
	        	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9000, 1, UNDER_FOOT, PF_LOOP );    // 半透明
			set_invisible(who, 1);
			who->set_save("no_visible", 1);
			send_user( who, "%c%c%c", 0x3d, 241, 2 );	
				if ( who->get_save("muave")>0 ) { who->add_cash(-500000); who->delete_save("muave"); }
       		}       	
       		break;
       	case "hbt":
       		if (key[1]=="?")
       		{       		
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "Xin nhập ID người chơi bạn muốn giải trừ Cấm Tấn Công:\n"
                        	ESC "gmmap hbt %s\n");         				
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "Không tìm thấy người chơi này." );
				return 1;
		        }  
		        /*if( is_player(who) ) */ who->set_no_fight(0);
		        tell_user(me, "Đã thiết lập cho "+who->get_name()+" chế độ Có thể tấn công.");	  
				set_effect_2( who, EFFECT_CHAR_INVISIBLE, 0, 0);
			who->set_save("no_visible", 0);
			set_invisible(who, 0);
			CHAR_CHAR_D->init_loop_perform(who);
			send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9000, 1, UNDER_FOOT, PF_STOP );	
       		}       	
       		break;
       	}
       	return 1;
}