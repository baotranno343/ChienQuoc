#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;
//inherit COMBINED;

mapping mpInfo = ([

"Kim Tinh" : 	([ "prop" : ({1475,1079,1189,1004,0806,0906,1426}), "ski" : ({"Cao Cấp Hộ Thân Thuẫn","Cao cấp cường công","Cao cấp phục sinh","Cao cấp phi hành thuật"})]),
"Mộc Tinh" : 	([ "prop" : ({1475,1079,1189,1004,0806,0906,1426}), "ski" : ({"Cao Cấp Hộ Thân Thuẫn","Cao cấp cuồng công","Cao cấp bạo kích","Cao cấp phi hành thuật"})]),
"Thuỷ Tinh" : 	([ "prop" : ({1475,1079,1189,1004,0806,0906,1426}), "ski" : ({"Cao Cấp Hộ Tâm Thuẫn","Phúc tinh cao chiếu","Cao cấp nhược điểm công kích","Cao cấp phi hành thuật"})]),
"Hoả Tinh" : 	([ "prop" : ({1330,0876,0991,1194,0970,1070,1240}), "ski" : ({"Cao Cấp Hộ Thân Thuẫn","Cao cấp ngự pháp","Hoả Công","Diệt Thiên Hoả Pháp"})]),
"Thổ Tinh" : 	([ "prop" : ({1330,0876,0991,1194,0970,1070,1240}), "ski" : ({"Cao cấp ngự mệnh thuật","Cao cấp ngự pháp","Lạc Thạch","Phi sa tẩu thạch"})]),
"Quy Tiên Nhân" : 	([ "prop" : ({1330,0876,0991,1194,0970,1070,1240}), "ski" : ({"Cao cấp phục sinh","Cao cấp ngự pháp","Thuỷ Kích","Phiên vân phúc vũ"})]),

]);

mapping mpPet = (["Thạch Sư":0700,"Thạch Hổ":0701,"Đao Dũng":0850,"Cung Tiễn Thạch Dũng":0853,"Thương Dũng":0852,"Kiếm Dũng":0851,]);

int get_item_value() {return 9975 ;}	//价格
int get_item_value_2() {return 9975 ;}	//会员价
int get_item_number() {return 97 ;}	//序号
//int get_item_color() {return 1 ;}
int give_pet(object who, string arg);


// 函数：构造处理
void create()
{
        set_name( "Tân niên sủng vật bao" );
        set_picid_1(3106);
        set_picid_2(3106);
        set_value(100);
        set_record(1);
	set_2( "use", ([
                "pet"          : (: give_pet :),
                	]) );
}

// 函数：获取描述
string get_desc() 
{ 
        return "Qùa tặng đầu năm mới,Mở ra được Pet 4 skill cực kì ngon。";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me,this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me,object item )
{
	int id = getoid(item);
	send_user( me, "%c%c%w%s", ':',3,0,
		sprintf(
			"Bạn hãy Lựa chọn：\n"
			ESC"Kim Tinh（Kĩ năng：Cao Cấp Hộ Thân Thuẫn、Cao cấp cường công、Cao cấp phục sinh、Cao cấp phi hành thuật）\nuse %x# pet.1\n"
			ESC"Mộc Tinh（Kĩ năng：Cao Cấp Hộ Thân Thuẫn、Cao cấp cuồng công、Cao cấp bạo kích、Cao cấp phi hành thuật）\nuse %x# pet.2\n"
			ESC"Thuỷ Tinh（Kĩ năng：Cao Cấp Hộ Tâm Thuẫn、Phúc tinh cao chiếu、Cao cấp nhược điểm công kích、Cao cấp phi hành thuật）\nuse %x# pet.3\n"
			ESC"Hoả Tinh（Kĩ năng：Cao Cấp Hộ Thân Thuẫn、Cao cấp ngự pháp、Hoả Công、Diệt Thiên Hoả Pháp）\nuse %x# pet.4\n"
			ESC"Thổ Tinh（Kĩ năng：Cao cấp ngự mệnh thuật、Cao cấp ngự pháp、Lạc Thạch、Phi sa tẩu thạch）\nuse %x# pet.5\n"
			ESC"Quy Tiên Nhân（Kĩ năng：Cao cấp phục sinh、Cao cấp ngự pháp、Thuỷ Kích、Phiên vân phúc vũ）\nuse %x# pet.6\n"
			ESC"Rời đi",id,id,id,id,id,id)
		
		);
	 
	return 0;	                        
} 

//物品给予玩家
int give_item(object who, string cName, int iAmount)
{
	int p;
	object item;
	
	item = new(cName);
	if ( !objectp(item) )
		return 0;
	if ( item->is_combined() )
		item->set_amount(iAmount>0?iAmount:1);
	p = item->move(who,-1);
	if ( !p )
	{
		destruct(item); 
		return 0;
	}
	item->add_to_user(p);
	return 1;	
}

int give_pet(object who, string arg)
{
	return __FILE__->give_pet_call(who,this_object(),arg);
}

int give_pet_call(object who, object item,string arg)
{
	int i=to_int(arg),picid,*nProp,size,iSki,p,j;
	string cName,*nSki,*nPet;
	object pet;
	mapping mpTmp;

	if ( who->get_beast_amount() + 1 > who->get_beast_max_amount() )
	{
		send_user(who, "%c%s", '!', "Bảo thú đã đầy。");
		return 1;
	}
	if ( USER_INVENTORY_D->count_empty_carry(who) < 14 )
	{
		send_user(who, "%c%s", '!', "Hãy chừa trong hành trang 15 ô trống。");
		return 1;
	}
	item->remove_from_user();
	destruct(item);

	switch(i)
	{
	default:
		cName = "Kim Tinh";
		picid = 0950;
		break;
	case 2:
		cName = "Mộc Tinh";
		picid = 0951;
		break;	
	case 3:
		cName = "Thuỷ Tinh";
		picid = 0952;
		break;	
	case 4:
		cName = "Hoả Tinh";
		picid = 0953;
		break;	
	case 5:
		cName = "Thổ Tinh";
		picid = 0954;
		break;	
	case 6:
		cName = "Quy Tiên Nhân";
		picid = 0402;
		break;									
	}
	pet = USER_BEAST_D->give_pet(who,cName,1,0,picid,0);
	if ( !pet )
		return 1;
	pet->set_save("ignore_level",1);
	pet->init_skill_dbase();
	mpTmp = mpInfo[cName];
	nProp = mpTmp["prop"];
	nSki = mpTmp["ski"];
	pet->set_con_grow(nProp[0]);	
	pet->set_str_grow(nProp[1]);	
	pet->set_cps_grow(nProp[2]);	
	pet->set_mp_grow(nProp[3]);	
	pet->set_ma_grow(nProp[4]);	
	pet->set_md_grow(nProp[5]);	
	pet->set_dex_grow(nProp[6]);
	for(i=0,size=sizeof(nSki);i<size;i++)
	{
		iSki = "quest/pet"->get_beast_skill(nSki[i]);
		pet->set_skill(iSki,1);
	}
		
	NPC_PET_D->set_pet_info(pet);
	pet->set_life(8888);	
	pet->set_hp(pet->get_max_hp());
	pet->set_mp(pet->get_max_mp());
	pet->send_info();

	give_item(who,"/item/44/4404",2);	//玉灵液
	
	for(i=0;i<2;i++)		//精元丹
	{
		item = new("/item/44/4488");
		item->set("special",sprintf("%d","quest/pet"->get_drop_skill1()));
		p = item->move(who,-1);
		if(!p)
		{
			destruct(item);
			return 1;	
		}
		item->add_to_user(p);
	}	
	for(i=1;i<4;i++)		//晶石9颗 1,2,3级各3
	for(j=1;j<4;j++)
	{
		item = new(STONE_FILE->get_diamond_file());
		item->set_level(i);
		p = item->move(who,-1);
		if(!p)
		{
			destruct(item);
			return 1;	
		}
		item->add_to_user(p);
	}
	
	give_item(who,"/item/sell/0008",10);	//速效治愈药水
	give_item(who,"/item/sell/0010",10);	//速效恢复药水
	give_item(who,"/item/sell/0021",1);	//财神符
	
	return 1;
}
