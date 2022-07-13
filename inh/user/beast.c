//宠物(召唤兽)相关
#include <effect.h>
#define PET_NPC "npc/std/pet"
private static int iMaxBeastAmount;		//携带最多的召唤兽
private static object *AllBeast;		//宠物对象的指针数组,暂时未用
private string *BeastInfo;			//存储宠物存盘文件的数组
void send_beast_list();
void hide_beast(string arg);

//初始化
void init_beast()
{
	iMaxBeastAmount = USER_BEAST_D->max_carry(this_object());
}
//取携带宠物最大数量
int get_beast_max_amount()	{return iMaxBeastAmount;};
//取携带召唤兽的数量
int get_beast_amount()	{return sizeof(BeastInfo);};

//发送宠物列表
void send_beast_list()
{
	int i,size;
	object pet;
	size = sizeof(AllBeast);
	if ( !size )
		return ;
	for(i=0;i<size;i++)
	{
		if ( !objectp(pet=AllBeast[i]) )
			continue;
		pet->send_info();
	}
}

//获取所拥有的宠物
object *get_all_beast() { return copy(AllBeast);}
//保存所有宠物的属性
void save_beast()
{
	int i,size;
	
	for(i=0,size=sizeof(AllBeast);i<size;i++)
	{
		if ( !objectp(AllBeast[i]) )
			continue;
		AllBeast[i]->save();	
	}
}
//增加宠物属性
int add_beast(object pet)
{
	string Id;
	object me = this_object();
	if ( !arrayp(BeastInfo) )
		BeastInfo = ({});
	if ( !arrayp(AllBeast) )
		AllBeast = ({});
	Id = pet->get_pet_id();
	if ( !Id )
		return 0;
	BeastInfo += ({Id});
	AllBeast += ({pet});
	pet->save();
	"/quest/help"->send_help_tips(me, 15);
	return 1;	
}
//进入游戏时恢复宠物
void restore_beast()
{
	int i,size,j;
	object pet,me;
	
	size=sizeof(BeastInfo);
	if ( !size )
		return ;
	AllBeast = ({});
	me = this_object();
	for(i=0;i<size;i++)
	{
		if ( !stringp(BeastInfo[i]) )
			continue;
		pet = new(PET_NPC);
		if ( !pet )
			return;
		pet->set_owner(me);	//不设无法restore
		pet->set_pet_id(BeastInfo[i]);
		j = pet->restore();
		if ( !j )
		{
			destruct(pet);
			continue;	
		}
		pet->set_owner(me);	//必须
		pet->set_pet_id(BeastInfo[i]);
		j = NPC_PET_D->set_pet_info(pet);
		if ( !j )
		{
			destruct(pet);
			continue;	
		}
		if ( get_effect(pet, EFFECT_MAGIC_CARD) )	//取消变身的效果
			set_effect_2(pet, EFFECT_MAGIC_CARD, 1,1);

		AllBeast += ({pet});
	}
	send_beast_list();
}

//删除宠物信息
void remove_beast(object pet)
{
	string file,id;
	
	AllBeast -= ({ pet });
	file = pet->get_save_file();
	id = pet->get_pet_id();
	if ( !file || !id )
		return ;
	if ( !pet->get("reserve_pet") )	//不是寄存的，删除！
		rm(file);
	if ( sizeof(BeastInfo) )
	{
		BeastInfo -= ({id});
	}

}


// 函数：消除之前处理
void destruct_all_pet()
{
	int i,size;
	object me=this_object(),pet;
	
	for(i=0,size=sizeof(AllBeast);i<size;i++)
	{
		if ( !objectp(pet=AllBeast[i]) )
			continue;
		if ( pet->get("show") )
			pet->remove_from_scene();
		destruct(pet);
	}
}


//测试用
void show_all_beast(int id)
{
	int i,size;
	object me;
	
	me=find_char(sprintf("%d",id));
	if ( !me )
		me=this_object() ;
	for(i=0,size=sizeof(AllBeast);i<size;i++)
	{
		if ( !objectp(AllBeast[i]) )
			continue;
		tell_user(me,"%x#",getoid(AllBeast[i]));
	}
}
