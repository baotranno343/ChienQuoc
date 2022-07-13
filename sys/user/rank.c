
#include <ansi.h>
#include <equip.h>

// 函数:生成二进制码
void SAVE_BINARY() { }

string *RankTable = ({
        HIW "Trói Gà Không Chặt" NOR, HIB "Trói Gà Không Chặt" NOR, HIY "Trói Gà Không Chặt" NOR,
        HIW "Tứ Cố Vô Thân" NOR, HIB "Tứ Cố Vô Thân" NOR, HIY "Tứ Cố Vô Thân" NOR,
        HIW "Thư Sinh Vô Dụng" NOR, HIB "Thư Sinh Vô Dụng" NOR, HIY "Thư Sinh Vô Dụng" NOR,
        HIW "Tài Hèn Sức Mọn" NOR, HIB "Tài Hèn Sức Mọn" NOR, HIY "Tài Hèn Sức Mọn" NOR,
        HIW "Vô Danh Tiểu Tốt" NOR, HIB "Vô Danh Tiểu Tốt" NOR, HIY "Vô Danh Tiểu Tốt" NOR,
        HIW "Phàm Phu Tục Tử" NOR, HIB "Phàm Phu Tục Tử" NOR, HIY "Phàm Phu Tục Tử" NOR,
        HIW "Mong Manh Đệ Tử" NOR, HIB "Mong Manh Đệ Tử" NOR, HIY "Mong Manh Đệ Tử" NOR,
        HIW "Ngây Thơ Thiếu Hiệp" NOR, HIB "Ngây Thơ Thiếu Hiệp" NOR, HIY "Ngây Thơ Thiếu Hiệp" NOR,
        HIW "Tầm Thường Tiên Sinh" NOR, HIB "Tầm Thường Tiên Sinh" NOR, HIY "Tầm Thường Tiên Sinh" NOR,
        HIW "Tung Tăng Hành Hiệp" NOR, HIB "Tung Tăng Hành Hiệp" NOR, HIY "Tung Tăng Hành Hiệp" NOR,
        HIW "Bon Chen Đại Hiệp" NOR, HIB "Bon Chen Đại Hiệp" NOR, HIY "Bon Chen Đại Hiệp" NOR,
        HIW "Lận Đận Cao Thủ" NOR, HIB "Lận Đận Cao Thủ" NOR, HIY "Lận Đận Cao Thủ" NOR,
        HIW "Độc Cô Cầu Hòa" NOR, HIB "Độc Cô Cầu Hòa" NOR, HIY "Độc Cô Cầu Hòa" NOR,
        HIW "Thấu Tình Đạt Lí" NOR, HIB "Thấu Tình Đạt Lí" NOR, HIY "Thấu Tình Đạt Lí" NOR,
        HIW "Tế Thế Công Minh" NOR, HIB "Tế Thế Công Minh" NOR, HIY "Tế Thế Công Minh" NOR,
        HIW "Thỏa Chí Bình Sinh" NOR, HIB "Thỏa Chí Bình Sinh" NOR, HIY "Thỏa Chí Bình Sinh" NOR,
        HIW "Đa Mưu Túc Trí" NOR, HIB "Đa Mưu Túc Trí" NOR, HIY "Đa Mưu Túc Trí" NOR,
        HIW "Lãnh Đạo Quần Hùng" NOR, HIB "Lãnh Đạo Quần Hùng" NOR, HIY "Lãnh Đạo Quần Hùng" NOR,
        HIW "Vô Cùng Thần Kỳ" NOR, HIB "Vô Cùng Thần Kỳ" NOR, HIY "Vô Cùng Thần Kỳ" NOR,
        HIW "Xuất Quỷ Nhập Thần" NOR, HIB "Xuất Quỷ Nhập Thần" NOR, HIY "Xuất Quỷ Nhập Thần" NOR,
        HIW "Nhất Đại Tông Sư" NOR, HIB "Nhất Đại Tông Sư" NOR, HIY "Nhất Đại Tông Sư" NOR,
        HIW "Ngạo Thế Cao Nhân" NOR, HIB "Ngạo Thế Cao Nhân" NOR, HIY "Ngạo Thế Cao Nhân" NOR,
        HIW "Thần Công Cái Thế" NOR, HIB "Thần Công Cái Thế" NOR, HIY "Thần Công Cái Thế" NOR,
        HIW "Đệ Nhất Cao Thủ" NOR, HIB "Đệ Nhất Cao Thủ" NOR, HIY "Đệ Nhất Cao Thủ" NOR,
        HIW "Độc Nhất Vô Nhị" NOR, HIB "Độc Nhất Vô Nhị" NOR, HIY "Độc Nhất Vô Nhị" NOR,
        HIW "Coi Trời Bằng Vung" NOR, HIB "Coi Trời Bằng Vung" NOR, HIY "Coi Trời Bằng Vung" NOR,
        HIW "Cái Thế Kỳ Tài" NOR, HIB "Cái Thế Kỳ Tài" NOR, HIY "Cái Thế Kỳ Tài" NOR,
        HIW "Thân Thủ Bất Phàm" NOR, HIB "Thân Thủ Bất Phàm" NOR, HIY "Thân Thủ Bất Phàm" NOR,
        HIW "Kinh Thế Hãi Tục" NOR, HIB "Kinh Thế Hãi Tục" NOR, HIY "Kinh Thế Hãi Tục" NOR,
        HIW "Chân Nhân Bất Lộ Tướng" NOR, HIB "Chân Nhân Bất Lộ Tướng" NOR, HIY "Chân Nhân Bất Lộ Tướng" NOR,
        HIW "Vô Tiền Khoáng Hậu" NOR, HIB "Vô Tiền Khoáng Hậu" NOR, HIY "Vô Tiền Khoáng Hậu" NOR,
        HIW "Thâm Bất Khả Trắc" NOR, HIB "Thâm Bất Khả Trắc" NOR, HIY "Thâm Bất Khả Trắc" NOR,
        HIW "Xuất Quỷ Nhập Thần" NOR, HIB "Xuất Quỷ Nhập Thần" NOR, HIY "Xuất Quỷ Nhập Thần" NOR,
        HIW "Vang Danh Thiên Hạ" NOR, HIB "Vang Danh Thiên Hạ" NOR, HIY "Vang Danh Thiên Hạ" NOR,
        HIW "Tiên Nhân Hạ Phàm" NOR, HIB "Tiên Nhân Hạ Phàm" NOR, HIY "Tiên Nhân Hạ Phàm" NOR,
        HIW "Thiên Nhân Hợp Nhất" NOR, HIB "Thiên Nhân Hợp Nhất" NOR, HIY "Thiên Nhân Hợp Nhất" NOR,
        HIW "Thần Thông Quảng Đại" NOR, HIB "Thần Thông Quảng Đại" NOR, HIY "Thần Thông Quảng Đại" NOR,
        HIW "Bình Thường Vô Vị" NOR, HIB "Bình Thường Vô Vị" NOR, HIY "Bình Thường Vô Vị" NOR,
});

mapping mpTimeRank = ([
	1 : ({ 8, "Phần Thưởng Sơ Cấp" }),
	2 : ({ 10, "Phần Thưởng Sơ Cấp" }),
	3 : ({ 12, "Phần Thưởng Sơ Cấp" }),
	4 : ({ 14, "Phần Thưởng Sơ Cấp" }),
	5 : ({ 16, "Phần Thưởng Sơ Cấp" }),
	6 : ({ 18, "Phần Thưởng Trung Cấp" }),
	7 : ({ 20, "Phần Thưởng Sơ Cấp" }),
	8 : ({ 22, "Phần Thưởng Trung Cấp" }),
	9 : ({ 24, "Phần Thưởng Trung Cấp" }),
	10 : ({ 26, "Phần Thưởng Trung Cấp" }),
	11 : ({ 28, "Phần Thưởng Trung Cấp" }),
	12 : ({ 30, "Phần Thưởng Trung Cấp" }),
	13 : ({ 32, "Phần Thưởng Trung Cấp" }),
	14 : ({ 34, "Phần Thưởng Trung Cấp" }),
	15 : ({ 36, "Phần Thưởng Trung Cấp" }),
	16 : ({ 38, "Phần Thưởng Cao Cấp" }),
	17 : ({ 40, "Phần Thưởng Trung Cấp" }),
	18 : ({ 42, "Phần Thưởng Cao Cấp" }),
	19 : ({ 44, "Phần Thưởng Trung Cấp" }),
	20 : ({ 46, "Phần Thưởng Cao Cấp" }),
	21 : ({ 48, "Phần Thưởng Trung Cấp" }),
	22 : ({ 50, "Phần Thưởng Cao Cấp" }),
	23 : ({ 52, "Phần Thưởng Cao Cấp" }),
	24 : ({ 54, "Phần Thưởng Cao Cấp" }),
	25 : ({ 56, "Phần Thưởng Cao Cấp" }),
	26 : ({ 58, "Phần Thưởng Cao Cấp" }),
	27 : ({ 60, "Phần Thưởng Đặc Cấp" }),
	28 : ({ 62, "Phần Thưởng Cao Cấp" }),
	29 : ({ 64, "Phần Thưởng Đặc Cấp" }),
	30 : ({ 66, "Phần Thưởng Cao Cấp" }),
	31 : ({ 68, "Phần Thưởng Đặc Cấp" }),
	32 : ({ 70, "Phần Thưởng Đặc Cấp" }),
	33 : ({ 72, "Phần Thưởng Đặc Cấp" }),
	34 : ({ 74, "Phần Thưởng Cao Cấp" }),
	35 : ({ 76, "Phần Thưởng Đặc Cấp" }),
	36 : ({ 78, "Phần Thưởng Đặc Cấp" }),
	37 : ({ 80, "Phần Thưởng Đặc Cấp" }),
	38 : ({ 82, "Phần Thưởng Đặc Cấp" }),
	39 : ({ 84, "Phần Thưởng Cao Cấp" }),
	40 : ({ 86, "Phần Thưởng Đặc Cấp" }),
	41 : ({ 88, "Phần Thưởng Đặc Cấp" }),
	42 : ({ 90, "Phần Thưởng Đặc Cấp" }),
	43 : ({ 92, "Phần Thưởng Đặc Cấp" }),
	44 : ({ 94, "Phần Thưởng Đặc Cấp" }),
	45 : ({ 96, "Phần Thưởng Đặc Cấp" }),
	46 : ({ 98, "Phần Thưởng Đặc Cấp" }),
	47 : ({ 100, "Phần Thưởng Đặc Cấp" }),
	48 : ({ 102, "Phần Thưởng Đặc Cấp" }),
	49 : ({ 104, "Phần Thưởng Đặc Cấp" }),
	50 : ({ 106, "Phần Thưởng Đặc Cấp" }),
	51 : ({ 108, "Phần Thưởng Đặc Cấp" }),
	52 : ({ 110, "Phần Thưởng Đặc Cấp" }),
	53 : ({ 112, "Phần Thưởng Đặc Cấp" }),
	54 : ({ 114, "Phần Thưởng Đặc Cấp" }),
	55 : ({ 116, "Phần Thưởng Đặc Cấp" }),
	56 : ({ 118, "Phần Thưởng Đặc Cấp" }),
	57 : ({ 120, "Phần Thưởng Đặc Cấp" }),
	58 : ({ 122, "Phần Thưởng Đặc Cấp" }),
	59 : ({ 124, "Phần Thưởng Đặc Cấp" }),
	60 : ({ 126, "Phần Thưởng Đặc Cấp" }),
	61 : ({ 128, "Phần Thưởng Đặc Cấp" }),
	62 : ({ 130, "Phần Thưởng Đặc Cấp" }),
	63 : ({ 132, "Phần Thưởng Đặc Cấp" }),
	64 : ({ 134, "Phần Thưởng Đặc Cấp" }),
	65 : ({ 136, "Phần Thưởng Đặc Cấp" }),
	66 : ({ 138, "Phần Thưởng Đặc Cấp" }),
	67 : ({ 140, "Phần Thưởng Đặc Cấp" }),
	68 : ({ 142, "Phần Thưởng Đặc Cấp" }),
	69 : ({ 144, "Phần Thưởng Đặc Cấp" }),
	70 : ({ 146, "Phần Thưởng Đặc Cấp" }),
	71 : ({ 148, "Phần Thưởng Đặc Cấp" }),
	72 : ({ 150, "Phần Thưởng Đặc Cấp" }),
	73 : ({ 152, "Phần Thưởng Đặc Cấp" }),
	74 : ({ 154, "Phần Thưởng Đặc Cấp" }),
	75 : ({ 156, "Phần Thưởng Đặc Cấp" }),
	76 : ({ 158, "Phần Thưởng Đặc Cấp" }),
	77 : ({ 160, "Phần Thưởng Đặc Cấp" }),
	78 : ({ 162, "Phần Thưởng Đặc Cấp" }),
	79 : ({ 164, "Phần Thưởng Đặc Cấp" }),
	80 : ({ 166, "Phần Thưởng Đặc Cấp" }),
	81 : ({ 168, "Phần Thưởng Đặc Cấp" }),

]);
int sizeof_rank = sizeof(RankTable);
string *nFamily = ({"Đào Hoa Nguyên","Thục Sơn","Cấm Vệ Quân","Đường Môn","Mao Sơn","Côn Luân","Vân Mộng Cốc"});

// 函数:获得能力称谓
string get_rank( object who )
{
        int ap, cp;

        if( !objectp(who) ) return "";

        ap = who->get_ap();
        cp = who->get_cp();
        if( cp > ap ) ap = cp;

        ap = range_value( ap / 30, 0, sizeof_rank - 1 );

        return RankTable[ap];
}

//根据时间获取修为等级
int check_online_level(int hour)
{
	int i,size,*nTmp,level,count;
	mixed *mxTmp;
	
	nTmp = sort_array(keys(mpTimeRank),1);	//升序
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		level = nTmp[i];
		mxTmp = mpTimeRank[level];
		count += mxTmp[0];
		if ( count < hour )
			continue;
		if ( count == hour )
			break;
		level --;
		break;
	}
	return level;
}
//
void send_friend_info(object me,int level)
{
        object who;
        mapping Friends;
        string *key,acount,cTmp;
        int i, size,id;

	Friends = me->get_friend_dbase();
        size = sizeof( key = keys(Friends) );
        if( size ) key = sort_array(key, 1);
        cTmp = sprintf(/*BLK */"Chu Vương:\nNghe nói %s tăng thêm một tu vị，đã đạt tới cấp %d. Hãy chúc mừng hắn đi！",me->get_name(),level);
        for( i = 0; i < size; i ++ )
        {
        	id = to_int(key[i]);
                acount = me->get_friend_id(id);
		MAILBOX->sys_mail(acount,id,cTmp);
        }
}
//修为系统
void online_rank(object who,int flag)
{
	int i,level,hour,level1;
	
	if ( "sys/sys/count"->get_new_story() == 0 )
		return ;
	if ( flag == 0 )
	{
		if ( !who->get_save_2("online_rank.time") )	//初始化
		{
			who->set_save_2("online_rank.time",who->get_game_time());
			hour = who->get_game_time()/3600;
			level = check_online_level(hour);
			who->set_save_2("online_rank.level",level);
			USER_ENERGY_D->count_max_hp(who);
		}
		else if ( who->get_save_2("online_rank.time") < who->get_game_time() )	//校正时间
		{
			who->set_save_2("online_rank.time",who->get_game_time());
		}
		else if ( who->get_save_2("online_rank.time") > who->get_game_time() )	//校正时间
		{
			who->set_game_time(who->get_save_2("online_rank.time"));
		}
		who->set_save_2("online_rank.start",time());
		
		return ;
	}
	else if ( flag == 1 )
	{
		i = who->get_save_2("online_rank.start");
		if ( !i )
		{
			who->set_save_2("online_rank.start",time());
			return ;
		}
		i = gone_time(i);
		hour = who->add_save_2("online_rank.time",i)/3600;
		who->set_save_2("online_rank.start",time());
		level = who->get_save_2("online_rank.level");
		level1 = check_online_level(hour);
		if ( level >= level1 )
			return ;
		//修为升级
		who->set_save_2("online_rank.level",level1);
		send_user(who,"%c%c%c",0xA2,10,level1);
		USER_ENERGY_D->count_max_hp(who);
		MAILBOX->sys_mail(who->get_id(),who->get_number(),/*BLK*/"Chu Vương:\nChúc mừng bạn đã tăng thêm một tu vị, có thể đến tìm ta ở Chu để nhận lễ vật !");
		if ( (level1 % 27) == 0 )
			send_friend_info(who,level1);
	}
		
}
//
varargs int give_item(object who, string cName,int color,int level)
{
	int p;
	object item;
	
	item = new(cName);
	if ( !item )
		return 0;
	p = item->move(who,-1);
	if ( !p )
	{
		send_user(who,"%c%s",'!',"Hành trang không đủ chỗ");
		destruct(item);
		return 0;
	}
	if ( color == 1 )
		ITEM_EQUIP_D->init_equip_prop_1(item);
	else if ( color == 3 )
		ITEM_EQUIP_D->init_equip_prop_3(item);

	if ( level )
		item->set_level(level);
	item->add_to_user(p);
	send_user(who,"%c%s",';',sprintf("Nhận lễ vật thành công ! bạn nhận được "HIR "%s",item->get_name()));
	return 1;
}
//Phần Thưởng Sơ Cấp
int get_bonus1(object who)
{
	int ret,exp;

	if ( random(2) )
	{
		switch(random(4))
		{
		default:
		case 0:
			ret = give_item(who,"/item/std/6002",0);	//乾坤袋
			break;
		case 1:
			ret = give_item(who,"item/08/0013",0);		//绑定的战国令
			break;
		case 2:
			ret = give_item(who,BOOK_FILE->get_book_file(),0);	//随机进阶技能书
			break;
		case 3:
			ret = give_item(who,COLLECT_FILE->get_collect_file(),0);	//随机收藏品
			break;
		}
		
	}
	else
	{
		switch(random(6))
		{
		default:
		case 0:
			ret = give_item(who,"/item/final/15/1504",0);	//初级法攻
			break;
		case 1:
			ret = give_item(who,"/item/final/15/1502",0);		//初级物攻
			break;
		case 2:
			exp = 100000;
			ret = 1;
			break;
		case 3:
			exp = 80000;
			ret = 1;
			break;
		case 4:
			exp = 60000;
			ret = 1;
			break;			
		case 5:
			ret = give_item(who,"item/44/4404",0);	//玉灵液
			break;
		}		
		
	}
	if ( exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",';',sprintf("Nhận lễ vật thành công! bạn nhận được %d Kinh nghiệm",exp));
	}
	return ret;
}
//Phần Thưởng Trung Cấp
int get_bonus2(object who)
{
	int ret,exp;
        string *nTmp,tmp;

	if ( random(2) )
	{
		switch(random(5))
		{
		default:
		case 0:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,50,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//50级随机蓝色装备
			break;
		case 1:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,60,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//60级随机蓝色装备
			break;
		case 2:
			ret = give_item(who,"quest/product2"->get_random_level_product(50,50));	//50级随机蓝色图纸
			break;
		case 3:
			ret = give_item(who,"quest/product2"->get_random_level_product(60,60));	//60级随机蓝色图纸
			break;
		case 4:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,50,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,3);	//50级随机金色腰带
			break;
		}
	}
	else
	{
		switch(random(14))
		{
		default:
		case 0:
			//随机高级药品
			switch(random(9))
			{
			default:
			case 0:
				ret = give_item(who,"item/91/9125");
				break;	
			case 1:
				ret = give_item(who,"item/91/9150");
				break;
			case 2:
				ret = give_item(who,"item/91/9160");
				break;
			case 3:
				ret = give_item(who,"item/91/9161");
				break;
			case 4:
				ret = give_item(who,"item/91/9162");
				break;	
			case 5:
				ret = give_item(who,"item/91/9163");
				break;
			case 6:
				ret = give_item(who,"item/91/9164");
				break;
			case 7:
				ret = give_item(who,"item/91/9165");
				break;
			case 8:
				ret = give_item(who,"item/std/0088");
				break;
				
			}
			break;
		case 1:
			ret = give_item(who,STONE_FILE->get_diamond_file(),0,1);	//1级晶石
			break;
		case 2:
			ret = give_item(who,"item/44/4488");	//基础宠物技能丹
			break;	
		case 3:
			ret = give_item(who,sprintf("item/std/%d",8001+random(4)));	//随机残缺藏宝图
			break;	
		case 4:
			ret = give_item(who,"item/91/9167");	//紫参丹
			break;	
		case 5:
			ret = give_item(who,"item/44/4404",0);	//玉灵液
			break;
		case 6:
			ret = give_item(who,"/item/final/15/1504",0);	//初级法攻
			break;
		case 7:
			ret = give_item(who,"/item/final/15/1502",0);		//初级物攻
			break;
		case 8:
			exp = 200000;
			ret = 1;
			break;
		case 9:
			exp = 250000;
			ret = 1;
			break;
		case 10:
			exp = 300000;
			ret = 1;
			break;			
		case 11:
			ret = give_item(who,"item/08/0013",0);		//绑定的战国令
			break;
		case 12:
			ret = give_item(who,"item/91/9178",0);		//复生丹
			break;
		case 13:
			ret = give_item(who,"item/sell/0044",0);	//济世宝玉
			break;
		}		
	}
	if ( exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",';',sprintf("Nhận lễ vật thành công! bạn nhận được %d Kinh nghiệm",exp));
	}
	return ret;
}
//Phần Thưởng Cao Cấp
int get_bonus3(object who)
{
	int ret,exp;
        string *nTmp,tmp;
	if ( random(2) )
	{
		switch(random(13))
		{
		default:
		case 0:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,70,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//70级蓝色装备
			break;
		case 1:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,80,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//80级随机蓝色装备
			break;
		case 2:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,90,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//90级随机蓝色装备
			break;
		case 3:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,70,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//70级随机蓝色武器
			break;
		case 4:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,80,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//80级随机蓝色武器
			break;
		case 5:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,70,HEAD_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,3);	//70级随机金色帽子
			break;
		case 6:
			ret = give_item(who,"quest/product2"->get_random_level_product(70,70));	//70级随机蓝色装备图纸
			break;
		case 7:
			ret = give_item(who,"quest/product2"->get_random_level_product(80,80));	//80级随机蓝色图纸
			break;
		case 8:
			ret = give_item(who,"quest/product2"->get_random_level_product(90,90));	//90级随机蓝色图纸
			break;
		case 9:
			ret = give_item(who,"/item/std/6002",0);	//乾坤袋
			break;
		case 10:
			ret = give_item(who,"item/08/0013",0);		//绑定的战国令
			break;
		case 11:
			ret = give_item(who,BOOK_FILE->get_book_file(),0);	//随机进阶技能书
			break;
		case 12:
			ret = give_item(who,COLLECT_FILE->get_collect_file(),0);	//随机收藏品
			break;
		}
	}
	else
	{
		switch(random(15))
		{
		default:
		case 0:
			//随机高级药品
			switch(random(9))
			{
			default:
			case 0:
				ret = give_item(who,"item/91/9125");
				break;	
			case 1:
				ret = give_item(who,"item/91/9150");
				break;
			case 2:
				ret = give_item(who,"item/91/9160");
				break;
			case 3:
				ret = give_item(who,"item/91/9161");
				break;
			case 4:
				ret = give_item(who,"item/91/9162");
				break;	
			case 5:
				ret = give_item(who,"item/91/9163");
				break;
			case 6:
				ret = give_item(who,"item/91/9164");
				break;
			case 7:
				ret = give_item(who,"item/91/9165");
				break;
			case 8:
				ret = give_item(who,"item/std/0088");
				break;
				
			}
			break;
			break;
		case 1:
			ret = give_item(who,STONE_FILE->get_diamond_file(),0,1);	//1级晶石
			break;
		case 2:
			ret = give_item(who,"item/44/4488");	//基础宠物技能丹
			break;	
		case 3:
			ret = give_item(who,sprintf("item/std/%d",8001+random(4)));	//随机残缺藏宝图
			break;	
		case 4:
			ret = give_item(who,"item/91/9167");	//紫参丹
			break;	
		case 5:
			ret = give_item(who,"item/44/4404",0);	//玉灵液
			break;
		case 6:
			ret = give_item(who,"/item/final/15/1504",0);	//初级法攻
			break;
		case 7:
			ret = give_item(who,"/item/final/15/1502",0);		//初级物攻
			break;
		case 8:
			exp = 600000;
			ret = 1;
			break;
		case 9:
			exp = 700000;
			ret = 1;
			break;
		case 10:
			exp = 800000;
			ret = 1;
			break;			
		case 11:
			ret = give_item(who,"item/08/0013",0);		//绑定的战国令
			break;
		case 12:
			ret = give_item(who,"item/91/9178",0);		//复生丹
			break;
		case 13:
			ret = give_item(who,"item/sell/0044",0);	//济世宝玉
			break;
		case 14:
			ret = give_item(who,sprintf("item/sell/%04d",15+random(5)),0);//洗点丸
			break;
		}		
	}
	if ( exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",';',sprintf("Nhận lễ vật thành công! bạn nhận được %d Kinh nghiệm",exp));
	}
	return ret;
}
//Phần Thưởng Đặc Cấp
int get_bonus4(object who)
{
	int ret,exp;
        string *nTmp,tmp;

	if ( random(2) )
	{
		switch(random(14))
		{
		default:
		case 0:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,100,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//100级蓝色装备
			break;
		case 1:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,110,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//110级随机蓝色装备
			break;
		case 2:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,120,HEAD_TYPE+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//120级随机蓝色装备
			break;
		case 3:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,100,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//100级随机蓝色武器
			break;
		case 4:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,110,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,1);	//110级随机蓝色武器
			break;
		case 5:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,100,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,3);	//100级随机金色武器
			break;
		case 6:
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,110,BOOTS_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			ret = give_item(who,tmp,3);	//110级随机金色鞋子
			break;
		case 7:
			ret = give_item(who,"quest/product2"->get_random_level_product(100,100));	//100级随机蓝色装备图纸
			break;
		case 8:
			ret = give_item(who,"quest/product2"->get_random_level_product(110,110));	//110级随机蓝色图纸
			break;
		case 9:
			ret = give_item(who,"quest/product2"->get_random_level_product(120,120));	//120级随机蓝色图纸
			break;
		case 10:
			ret = give_item(who,"/item/std/6002",0);	//乾坤袋
			break;
		case 11:
			ret = give_item(who,"item/08/0013",0);		//绑定的战国令
			break;
		case 12:
			ret = give_item(who,BOOK_FILE->get_book_file(),0);	//随机进阶技能书
			break;
		case 13:
			ret = give_item(who,COLLECT_FILE->get_collect_file(),0);	//随机收藏品
			break;
		}
	}
	else
	{
		switch(random(15))
		{
		default:
		case 0:
			//随机高级药品
			switch(random(9))
			{
			default:
			case 0:
				ret = give_item(who,"item/91/9125");
				break;	
			case 1:
				ret = give_item(who,"item/91/9150");
				break;
			case 2:
				ret = give_item(who,"item/91/9160");
				break;
			case 3:
				ret = give_item(who,"item/91/9161");
				break;
			case 4:
				ret = give_item(who,"item/91/9162");
				break;	
			case 5:
				ret = give_item(who,"item/91/9163");
				break;
			case 6:
				ret = give_item(who,"item/91/9164");
				break;
			case 7:
				ret = give_item(who,"item/91/9165");
				break;
			case 8:
				ret = give_item(who,"item/std/0088");
				break;
			}
			break;
			break;
		case 1:
			ret = give_item(who,STONE_FILE->get_diamond_file(),0,1);	//1级晶石
			break;
		case 2:
			ret = give_item(who,"item/44/4488");	//基础宠物技能丹
			break;	
		case 3:
			ret = give_item(who,sprintf("item/std/%d",8001+random(4)));	//随机残缺藏宝图
			break;	
		case 4:
			ret = give_item(who,"item/91/9167");	//紫参丹
			break;	
		case 5:
			ret = give_item(who,"item/44/4404",0);	//玉灵液
			break;
		case 6:
			ret = give_item(who,"/item/final/15/1504",0);	//初级法攻
			break;
		case 7:
			ret = give_item(who,"/item/final/15/1502",0);		//初级物攻
			break;
		case 8:
			exp = 1000000;
			ret = 1;
			break;
		case 9:
			exp = 1100000;
			ret = 1;
			break;
		case 10:
			exp = 1200000;
			ret = 1;
			break;			
		case 11:
			ret = give_item(who,"item/08/0013",0);		//绑定的战国令
			break;
		case 12:
			ret = give_item(who,"item/91/9178",0);		//复生丹
			break;
		case 13:
			ret = give_item(who,"item/sell/0044",0);	//济世宝玉
			break;
		case 14:
			ret = give_item(who,sprintf("item/sell/%04d",15+random(5)),0);//洗点丸
			break;
		}		
	}
	if ( exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",';',sprintf("Nhận lễ vật thành công! bạn nhận được %d Kinh nghiệm",exp));
	}
	return ret;
}
//领取修为奖励
void get_rank_bonus(object who,object me)
{
	int level,ret;
	string cTmp;
	
	level = who->get_save_2("online_rank.level");
	if ( !level )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    Bạn chưa có tu vị !\n"ESC"Rời khỏi", me->get_name(), ) );
		return ;	
	}	
	if ( level == who->get_save_2("online_rank.bonus") )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    Bạn đã nhận lễ vật rồi !\n"ESC"Rời khỏi", me->get_name(), ) );
		return ;	
	}
	cTmp = mpTimeRank[level][1];
	switch(cTmp)
	{
	default:
	case "Phần Thưởng Sơ Cấp":
		ret = get_bonus1(who);
		break;	
	case "Phần Thưởng Trung Cấp":
		ret = get_bonus2(who);
		break;	
	case "Phần Thưởng Cao Cấp":
		ret = get_bonus3(who);
		break;
	case "Phần Thưởng Đặc Cấp":
		ret = get_bonus4(who);
		break;	
	}
	if ( !ret )
		return ;
	who->set_save_2("online_rank.bonus",level);
}
//获取友好关系
string get_friend_desc(int i )
{
	string result;
	if ( i > 5000 )
		result = "Quân Tử Chi Giao";
	else if ( i > 3500 )
		result = "Tình Như Thủ Túc";
	else if ( i > 1800 )
		result = "Bạn Tri Kỉ";
	else if ( i > 800 )
		result = "Hài Nội Tri Kỉ";
	else if ( i > 200 )
		result = "Bình Thuỷ Tương Phùng";
	else 
		result = "Bằng Hữu Bình Thường";	
	return result;	
}
