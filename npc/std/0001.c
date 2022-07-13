#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>

inherit OFFICER;
#define PET_NPC "npc/std/pet"

// 函数：获取人物造型
int get_char_picid() { return 6009; }
void do_welcome(string arg);
void do_reserve(string arg);
void do_release(string arg);

// 函数：构造处理
void create()
{
        set_name("Bảo Thú Đại Phu");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
                 "reserve"         : (: do_reserve :),
                 "release"         : (: do_release :),
        ]) );
        setup();
}

void do_look(object who)
{
	do_welcome("99");
	
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,id,i,size,iCash;
       	object who, *nPet,pet,item_q2;
       	string cTmp,*nTmp;
       	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
        	nPet = who->get_all_beast();
        	size = sizeof(nPet);
        	if ( !size )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    你的宠物呢？\n"ESC"离开",);
        		return ;	
        	}
        	for(i=0;i<size;i++)
        	{
        		pet = nPet[i];
        		iCash += pet->get_max_hp() - pet->get_hp() + pet->get_max_mp() - pet->get_mp();
        	}
        	if ( !iCash )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu:\n Bảo Thú của bạn đều rất khỏe mạnh!\n"ESC"Rời khỏi",);
        		return ;	
        	}
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu:\n Bảo Thú của bạn bệnh nặng đấy! ! Xem ra cần phải được Trị Liệu bệnh bệnh chăm sóc. Yên tâm đi! ! tôi sẽ không thu tiền lung tung đâu, tôi sẽ căn cứ và mức độ nặng nhẹ căn bệnh của Bảo Thú mà lấy tiền, lần Trị Liệu bệnh bệnh này cần phải tốn %d vàng.\n"ESC"Chấp nhận\ntalk %x# welcome.11\n"ESC"Rời khỏi",iCash,id));
        	break;	
        case 2:
        	nPet = who->get_all_beast();
        	size = sizeof(nPet);
        	if ( !size )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    你的宠物呢？\n"ESC"离开",);
        		return ;	
        	}
        	for(i=0;i<size;i++)
        	{
        		pet = nPet[i];
        		iCash += (100-pet->get_faith())*45;
        	}
        	if ( !iCash )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    你的宠物都很忠心啊！\n"ESC"离开",);
        		return ;	
        	}
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu:\n Bảo Thú của bạn xem ra không nghe lời kêu gọi của bạn! ! Xem ra độ trung thành của Bảo Thú bạn thấp xuống rồi. Tôi có thể thuần dưỡng Bảo Thú của bạn ngoan ngoãn đâu vào đấy, có cần tôi giúp đỡ không? Chi phí thuần dưỡng lần này là %d vàng.\n"ESC"Chấp nhận\ntalk %x# welcome.21\n"ESC"Rời khỏi",iCash,id));
        	break;	
        case 11:
        	nPet = who->get_all_beast();
        	size = sizeof(nPet);
        	if ( !size )	return;
        	for(i=0;i<size;i++)
        	{
        		pet = nPet[i];
        		iCash += pet->get_max_hp() - pet->get_hp() + pet->get_max_mp() - pet->get_mp();
        	}
        	if ( who->get_cash() < iCash )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu：\n    虽然不是给人治病，但也不能不收钱吧～！你还是想想办法再来吧～！\n"ESC"离开",));
        		return ;	
        	}
        	who->add_cash(-iCash);
        	for(i=0;i<size;i++)
        	{
        		pet = nPet[i];
        		pet->set_hp(pet->get_max_hp());
        		pet->set_mp(pet->get_max_mp());
        	}
        	break;
        case 21:
        	nPet = who->get_all_beast();
        	size = sizeof(nPet);
        	if ( !size )	return;
        	for(i=0;i<size;i++)
        	{
        		pet = nPet[i];
        		iCash += (100-pet->get_faith())*45;
        	}
        	if ( who->get_cash() < iCash )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu：\n    不要开玩笑了～！你怎么会没钱呢？没钱还能养的起宠物？呵呵～！把钱带够再来找我吧！\n"ESC"离开",));
        		return ;	
        	}
        	who->add_cash(-iCash);
        	for(i=0;i<size;i++)
        	{
        		pet = nPet[i];
        		pet->set_faith(100);
        	}
        	break;
        case 33:
        	if ( (size=sizeof(who->get_save_2("reserve_pet"))) >= 3 )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    寄存数量已达到上限！\n"ESC"离开",);
        		return ;
        	}
        	cTmp = sprintf(" %s \n Đừng có xem thường bổn nhân, ngoài việc phục vụ Trị Liệu bệnh cho Bảo Thú ra, bổn nhân còn đặc biệt cung cấp dịch vụ ký gửi Bảo Thú, mời lựa chọn Bảo Thú mà bạn muốn gửi:( %d /3)\n",me->get_name(),size);
		nPet = who->get_all_beast();
        	size = sizeof(nPet);
        	if ( !size )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    你好像还没有捕抓任何宠物哦。想抓一只宠物的话只要在杂货店购买"HIR"乾坤绳"NOR"后，对着怪物使用便可以了。\n"ESC"离开",);
        		return ;
        	}
        	for(i=0;i<size;i++)
        	{
        		if ( !objectp(pet=nPet[i]) )
        			continue;
        		cTmp += sprintf(ESC"%s %s %d cấp\ntalk %x# reserve.%x#\n",pet->get_blood()?HIG:"",pet->get_name(),pet->get_level(),id,getoid(pet));	
        	}
        	cTmp += ESC"Rời khỏi";
        	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),cTmp);
        	break;
        case 44:
        	if ( (size=sizeof(who->get_save_2("reserve_pet"))) == 0 )
        	{
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    你并没有在我这里寄存过宠物啊！\n"ESC"离开",);
        		return ;
        	}
        	nTmp = keys(who->get_save_2("reserve_pet"));
        	cTmp = sprintf(" %s \n Mời lựa chọn Bảo Thú mà bạn muốn lãnh ra:( %d /3):\n",me->get_name(),size);
        	for(i=0;i<size;i++)
        	{
        		cTmp += sprintf(ESC"%s %s %d cấp\ntalk %x# release.%s\n",who->get_save_2(sprintf("reserve_pet.%s.baobao",nTmp[i]))?HIG:"",who->get_save_2(sprintf("reserve_pet.%s.name",nTmp[i])),who->get_save_2(sprintf("reserve_pet.%s.level",nTmp[i])),id,nTmp[i]);	
        		
        	}
        	cTmp += ESC"Rời khỏi";
        	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),cTmp);
        	break;
        case 99:
        	
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu:\n Bạn nhìn cho rõ nhé! ! Tôi không phải là bác sĩ chữa bệnh cho người, nếu như Bảo Thú của bạn bị bệnh, có lẽ tôi còn có một vài cách, nào! để tôi khám cho Bảo Thú của bạn xem nào! !\n"ESC"Trị Liệu bệnh cho Bảo Thú\ntalk %x# welcome.1\n"ESC"Thuần dưỡng Bảo Thú\ntalk %x# welcome.2\n"ESC"Gửi Bảo Thú\ntalk %x# welcome.33\n"ESC"Lãnh Bảo Thú\ntalk %x# welcome.44\n"ESC HIY"Thỏ Ngọc\ntalk %x# welcome.100\n"ESC HIY"Thu Thập Bánh Trung Thu\ntalk %x# welcome.101\n"ESC"Rời khỏi",id,id,id,id,id,id));
        	break;	
        case 100:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu:\n    Lễ Trung Thu, các Thỏ Ngọc bí mật xuống hạ giới mang Bánh Trung Thu về cho Hằng Nga, nhưng không may các chú thỏ đã quên cách trở về, hãy giúp tôi thu thập lại Bánh Trung Thu và Thỏ để gửi về cho Hằng Nga nhé. Để bắt thỏ phải sử dụng Dây Bắt Thỏ. Có thể tìm thấy chúng ở ngoại thành 7 nước, Tân Thủ Thôn và U Cốc.\n"ESC"Tìm thấy Thỏ Ngọc\ntalk %x# welcome.101\n"ESC"Chế tạo dây bắt thỏ\ntalk %x# welcome.111\n"ESC"Thoát ra",id,id));
        	break;
        case 101:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu:\n    Sự kiện trung thu đã kết thúc, tôi không thể đổi cho bạn được, hãy giữ lại như là một kỷ niệm đẹp nhé.\n"));
        	break;
        case 111:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu:\n    Sự kiện Tết Trung Thu đã bắt đầu, nếu bạn đã tìm thấy những sợi dây bắt Thỏ, sau đó hãy đưa cho tôi nhanh!\n"ESC"Đổi giải thưởng\ntalk %x# welcome.112\n"ESC"Thoát ra",id));
        	break;
        case 112:
			if( !objectp(present("Dây Bắt Thỏ", who, 1, MAX_CARRY) ) )
				{
					send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Bảo Thú Đại Phu:\n    Bạn ko có bất cứ dây bắt thỏ nào!\n"));
				}
			break;
        }

}
//寄存宠物
void do_reserve( string arg )
{
        object me = this_object();
        __FILE__ ->do_reserve2(me, arg);
}

void do_reserve2( object me, string arg )
{
	int size;
	string pet_id;
	object pet,who;
	
	who = this_player();
	
	pet = find_char(arg);
	if ( !pet )
		return ;
	if ( USER_BEAST_D->is_pet(who,pet) != 1 )
		return ;
	if ( (size=sizeof(who->get_save_2("reserve_pet"))) >= 3 )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    寄存数量已达到上限！\n"ESC"离开",);
		return ;
	}
	pet_id = pet->get_pet_id();
	if ( !sizeof(pet_id) )
		return ;
	who->set_save_2(sprintf("reserve_pet.%s.name",pet_id),pet->get_name());
	who->set_save_2(sprintf("reserve_pet.%s.firstname",pet_id),pet->get_firstname());
	who->set_save_2(sprintf("reserve_pet.%s.level",pet_id),pet->get_level());
	who->set_save_2(sprintf("reserve_pet.%s.baobao",pet_id),pet->get_blood());
	pet->set("reserve_pet",1); //!!
	USER_BEAST_D->destruct_pet(who,pet);
	send_user(who,"%c%s",'!',"你寄存了一只宠物");

}
//取出寄存的宠物
void do_release( string arg )
{
        object me = this_object();
        __FILE__ ->do_release2(me, arg);
}

void do_release2( object me, string arg )
{
	mapping mpTmp;
	int size,j;
	object pet,who;
	
	who = this_player();	
	mpTmp = who->get_save_2(sprintf("reserve_pet.%s",arg));
	if ( !mpTmp )
		return ;
	if ( who->get_beast_amount() >= who->get_beast_max_amount() )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Bảo Thú Đại Phu：\n    当前你所携带的宠物数量已达到上限！\n"ESC"离开",);
		return ;
	}

	pet = new(PET_NPC);
	if ( !pet )
		return;
	pet->set_owner(who);	//不设无法restore
	pet->set_pet_id(arg);
	j = pet->restore();
	if ( !j )
	{
		destruct(pet);
		return;	
	}
	pet->set_owner(who);	//必须
	pet->set_pet_id(arg);
	j = NPC_PET_D->set_pet_info(pet);
	if ( !j )
	{
		destruct(pet);
		return ;	
	}
	if ( !who->add_beast(pet) )
	{
		destruct(pet);
		return ;
	}
	pet->send_info();
	who->delete_save_2(sprintf("reserve_pet.%s",arg));
	send_user(who,"%c%s",'!',"你取回了一只宠物");
}