#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() {return 100 ;}
int get_item_value_2() {return 100 ;}

// 函数：构造处理
void create()
{
        set_name("Set HS");
        set_picid_1(4980);
        set_picid_2(4981);
		set_level(10);
        set_value(10000);
		set_save("tienxu",20);
}

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "Nhận set HS.";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int gender,family,type,i,k,l,m,n,q,w,a,s,d;
	object item,item1,item2,item3,item4,item5,item6,item7,item8,item9,item10;
	string cTmp,cFile,p;
	gender = who->get_gender() == 1 ? 1 : 2;

	if(USER_INVENTORY_D->get_free_count(who) < 5 )
	{
	        send_user(who,"%c%s",'!',"Hành trang không đủ chỗ.");
    		return 0;
	}
	TASK_LEGEND_D->check_task_item1(who,"Set HS",1);
	TASK_LEGEND_D->check_task_item2(who,"Set HS",1);
	TASK_LEGEND_D->check_task_item3(who,"Set HS",1); 
	TASK_LEGEND_D->check_task_item4(who,"Set HS",1);
	TASK_LEGEND_D->check_task_item5(who,"Set HS",1);
	
		
		item1 = new("item/huyetlong/2/ao");
	k = item1->move2(who,-1);
		item1->add_to_user(k);	
	
	item2 = new("item/huyetlong/2/giay");
	l = item2->move2(who,-1);
		item2->add_to_user(l);	
       
		item3 = new("item/huyetlong/2/non");
	m = item3->move2(who,-1);
		item3->add_to_user(m);


       item4 = new("item/huyetlong/2/hanglien");	   
	n = item4->move2(who,-1);
		item4->add_to_user(n);

		
       item5 = new("item/huyetlong/2/yeudoi");		
	q = item5->move2(who,-1);
		item5->add_to_user(q);

}