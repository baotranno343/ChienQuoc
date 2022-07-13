#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg) 
{

    int p, cap, chiso, i;
	string result,arg2,arg3,ngoc;
    object item, item1, who;
		if( is_player(me) ) 
        {
            write_user(me, ECHO "Bạn không đủ quyền hạn !");
			return 1;
        }

		if( !arg ) return 1;
		if (arg==0) return 1;
		if( sscanf(arg, "%s %s %d", arg2 , arg3, chiso ) != 3 ) return 1;
			if( arg2 && !( item = find_any_object(arg2) ) )
			{
                write_user(me, ECHO "Không tìm thấy vật phẩm này !");
				return 1;
			}
		if( !item->is_equip() )
		{
			write_user(me, ECHO "Chỉ có thể sửa đổi chỉ số của trang bị và vũ khí !");
			return 1;
		}
		if( item->is_equip())
		{
			i=item->get_equip_type();
			if ( i!=WEAPON_TYPE&&i!=ARMOR_TYPE&&i!=HEAD_TYPE&&i!=BOOTS_TYPE&&i!=WAIST_TYPE&&i!=NECK_TYPE&&i!=BACK_TYPE) 
			{
				write_user(me, ECHO "Chỉ có thể sửa đổi chỉ số của trang bị và vũ khí !");
				return 1;
			}
		}
	switch ( arg3 )
	{
	case "ngoaicong":
			item->set("ap",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Ngoại Công của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "noicong":
			item->set("cp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Nội Công của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "ngoaikhang":
			item->set("dp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Ngoại Kháng của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "noikhang":
			item->set("pp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Nội Kháng của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "khihuyet":
			item->set("hp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Khí Huyết của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "phapluc":
			item->set("mp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Pháp Lực của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "thanthu":
			item->set("sp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Thân Thủ của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "chinhxac":
			item->set("!%",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Chính Xác của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;	
	case "trungphapthuat":
			item->set("c!%",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Trúng Pháp Thuật của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "trungamkhi":
			item->set("t!%",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Trúng Ám Khí của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "tylethanthu":
			item->set("?%",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tỷ Lệ Thân Thủ của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "tylethanthu2":
			item->set("c?%",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tỷ Lệ Né Nội Công của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "baokich":
			item->set("double",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Bạo Kích của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "baokich2":
			item->set("double2",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Bạo Kích Khảm Nạm của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;		
	case "ngoaicong2":
			item->set("app",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tăng cường Ngoại Công của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "noicong2":
			item->set("cpp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tăng cường Nội Công của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "ngoaikhang2":
			item->set("dpp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tăng cường Ngoại Kháng của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "noikhang2":
			item->set("ppp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tăng cường Nội Kháng của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "khihuyet2":
			item->set("hpp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tăng cường Khí Huyết của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "phapluc2":
			item->set("mpp",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Tăng cường Pháp Lực của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "htkh":
			item->set("hp*",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Hấp Thụ Khí Huyết của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;
	case "htpl":
			item->set("mp*",chiso);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn đã sửa chỉ số Hấp Thụ Pháp Lực của %s thành %d.", item->get_name(), chiso ));
			return 1;
			break;		
	case "pp":	
			if ( !item->is_nangcap() ) return 1;
			ngoc = item->get("make");
			if ( strlen(ngoc) >=10 ) return 1;
			if(ngoc==0) ngoc="";
			ngoc += "b";
			item->set("make",ngoc);
			item->add("ap",150);	
			item->add("pp",150);	
			item->add("hp",400);	
			item->add("mp",400);	
			item->add("sp",50);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn nhận được %s + %d.", item->get_name(), strlen(item->get("make")) ));
			return 1;
			break;	
	case "canh":	
			if ( !item->is_nangcap() ) return 1;
			ngoc = item->get("make");
			if ( strlen(ngoc) >=10 ) return 1;
			if(ngoc==0) ngoc="";
			ngoc += "b";
			item->set("make",ngoc);
			item->add("cp",150);	
			item->add("dp",150);	
			item->add("hp",400);	
			item->add("mp",400);	
			item->add("double",250);
			item->add("sp",5);
			item->add_to_user(get_d(item));
			send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
			write_user(me, sprintf(ECHO"Bạn nhận được %s + %d.", item->get_name(), strlen(item->get("make")) ));
			return 1;
			break;		
	}		
		
	return 1;
} 