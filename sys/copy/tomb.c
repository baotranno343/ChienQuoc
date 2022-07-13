//骊山陵墓
#include <map.h>
#include <ansi.h>
#include <npc.h>
#include <skill.h>

//怪物的刷新座标
//上层陵墓
mapping mpNpc = ([ 
	"0001"	: ({ ({271, 253}),({273, 255}),({280, 244}),({281, 248}),({301, 253}),({315, 222}),({317, 246}),({319, 223}),({321, 243}),({329, 232}), }),
	"0002"	: ({ ({211, 234}),({216, 248}),({230, 245}),({232, 258}),({254, 265}),({336, 199}),({339, 186}),({361, 202}), }),
	"0003"	: ({ ({214, 231}),({219, 246}),({246, 258}),({331, 176}),({332, 186}),({339, 198}),({343, 185}),({355, 179}),({359, 198}),}),
	"0004"	: ({ ({216, 234}),({226, 247}),({229, 259}),({243, 257}),({252, 263}),({327, 186}),({329, 177}),({337, 196}),({351, 181}),}),
	"0005"	: ({ ({176, 103}),({201, 88 }),({216, 93 }),({227, 106}),({246, 114}),({285, 143}),({293, 152}),({314, 162}),}),
	"0006"	: ({ ({175, 107}),({200, 92 }),({220, 92 }),({236, 103}),({242, 116}),({250, 113}),({260, 122}),({270, 135}),({280, 144}),({296, 149}),({311, 161}),}),
	"0007"	: ({ ({174, 110}),({190, 108}),({195, 105}),({197, 89 }),({211, 94 }),({232, 105}),({256, 125}),({273, 132}),({311, 157}),}),
	"0009"	: ({ ({188, 122}),({199, 132}),({210, 107}),({215, 141}),({223, 117}),({226, 133}),({244, 140}),({245, 147}),({250, 146}),({257, 163}),({258, 156}),({263, 163}),({278, 172}),({284, 172}),({284, 179}),}),
	]);
//下层陵墓
mapping mpNpc1 = ([ 
	"0008"	: ({ ({58, 49  }),({62, 63  }),({69, 40  }),({78, 34  }),({88, 29  }),({93, 109 }),({95, 25  }),({96, 105 }),({153, 151}),({154, 132}),({161, 126}),({166, 134}),({198, 154}),({209, 140}),}),
	"0005"	: ({ ({170, 153}),({176, 142}),({195, 142}),({213, 155}),({224, 154}),}),
	"0006"	: ({ ({169, 157}),({193, 138}),({213, 151}),({228, 156}),({230, 169}),}),
	"0007"	: ({ ({166, 154}),({173, 143}),({192, 145}),({224, 159}),({233, 169}),}),
	"0010"	: ({ ({84, 59  }),({85, 73  }),({87, 62  }),({90, 75  }),({97, 85  }),({110, 109}),({111, 46 }),({112, 97 }),({114, 95 }),({117, 43 }),({118, 39 }),({118, 116}),({119, 120}),({132, 127}),({141, 138}),({177, 123}),({183, 109}),({186, 111}),	}),
	"0011"	: ({ ({87, 78  }),({100, 81 }),({107, 112}),({108, 96 }),({114, 46 }),({116, 122}),({130, 130}),({138, 137}),({180, 121}),}),
	]);	

mixed *nMine = ({
	({53,50 }),({59,41 }),({84,77 }),({88,22 }),({88,67 }),({89,64 }),({96,57 }),
	({101,53}),({101,115}),({102,16}),({108,122}),({112,22}),({115,107}),({117,127}),
	({121,91}),({123,31}),({130,35}),({151,43}),({157,186}),({170,197}),({175,161}),
	({177,159}),({184,102}),({193,112}),({202,156}),({220,147}),({222,148}),({225,151}),
});
mapping mpMine = ([
	"npc/00/yin.c" : 2,
	"npc/00/jtie.c" : 2,
	"npc/00/jin.c" : 2,
]);
mixed *nDrug1 = ({
	({173,96}),({174,97}),({178,118}),({179,118}),({213,177}),({248,199}),({251,129}),
	({278,174}),({279,173}),({320,170}),({378,193}),({379,193}),
});
mixed *nDrug2 = ({
	({68,71 }),({105,51}),({113,57}),({117,102}),({126,60}),({135,140}),({142,178}),
	({148,148}),({160,156}),({177,94}),({178,150}),({179,192}),({196,151}),({198,117}),
	({207,137}),({213,109}),({228,154}),({231,177}),
});
mapping mpDrug1 = ([
	"npc/00/herb12.c" : 2,
	"npc/00/herb13.c" : 2,
	"npc/00/herb14.c" : 1,
	"npc/00/herb15.c" : 1,
]);
mapping mpDrug2 = ([
	"npc/00/herb12.c" : 1,
	"npc/00/herb13.c" : 1,
	"npc/00/herb14.c" : 1,
	"npc/00/herb15.c" : 1,
	"npc/00/herb16.c" : 2,
	"npc/00/herb17.c" : 2,
	"npc/00/herb18.c" : 2,
]);
mixed *nBox1 = ({
	({187,123}),({187,236}),({215,142}),({216,129}),({225,266}),
	({226,136}),({239,148}),({253,209}),({276,190}),({344,168}),
});
mixed *nBox2 = ({
	({92,108 }),({100,26}),({143,49}),({147,173}),
	({186,91}),({193,85}),({194,176}),({224,177}),
});

mixed *nGate = ({
	({324,170}),({325,169}),({326,168}),({327,167}),	
	});
void close_gate(object map);

// 函数：生成二进制码
void SAVE_BINARY() { }

int new_copy_scene(object who, object me,string cMap,int *nPoint1,int *nPoint2,int tomb_flag)
{
	int i,z,tId;
	object map;
	
	tId = who->get_team_id();
	if ( !tId )
		return 0;
	z = COPY_CTROL->new_scene(0,cMap,0);
	if ( !z )
		return 0;
	if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
		return;
	TEAM_D->add_copy_scene(tId,tomb_flag,map);
	i = map->get_client_id();
	map->set("entrance1",nPoint1);
	map->set("entrance2",nPoint2);
	map->set("copy_id",tId);
	return z;
}


//创建上层陵墓
object new_copy_tomb1(object me, object who)
{
	int tId,z,x,y,*nP,i,size,j,count;
	mapping mpTmp;
	object map,npc,*nNpc;
	string *nTmp;
	mixed *mxTmp;
	
	tId = who->get_team_id();
	if ( !tId )
		return 0;
	z = new_copy_scene(who,me,"/map/copy/702",({334,258}),({165,107}),COPY_TOMB1);
	if ( !z )
		return 0;
	if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
		return 0;
	map->reset();	
	//出口NPC
	npc = new("npc/copy/0006");
	npc->add_to_scene(map->get_id(),336,263,2);
	npc = new("npc/copy/0007");	//Cơ Quan Thạch Sư
	npc->add_to_scene(map->get_id(),166,108,2);
	npc->set("map",map);
	npc = new("npc/copy/0011");	//机关石
	npc->add_to_scene(map->get_id(),236,207,2);
	npc->set("map",map);

	//路标
	npc = new("npc/copy/0012");
	npc->add_to_scene(map->get_id(),314,248,4);
	npc = new("npc/copy/0013");
	npc->add_to_scene(map->get_id(),196,105,2);
	
	//草药
	nTmp = keys(mpDrug1);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		for(j=0,count=mpDrug1[nTmp[i]];j<count;j++)
		{
			npc = new(nTmp[i]);	
			if ( !npc )
				continue;
			npc->set("never_refresh",1);
			nP = nDrug1[random(sizeof(nDrug1))];
			npc->add_to_scene(z,nP[0],nP[1]);
		}	
	}		
	//铁质宝箱
	for(i=0;i<3;i++)
	{
		npc = new("npc/00/box2");
		if ( npc )
		{
			nP = nBox1[random(sizeof(nBox1))];
			npc->add_to_scene(z,nP[0],nP[1]);		
		}
	}
	//普通NPC
	nNpc = ({});
	nTmp = keys(mpNpc);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		mxTmp = mpNpc[nTmp[i]];
		for(j=0,count=sizeof(mxTmp);j<count;j++)
		{
			npc = new("npc/copy/lishan/"+nTmp[i]);
			if ( !npc )
				continue;
			npc->set("copy_map_add_exp",1);
			npc->add_to_scene(z,mxTmp[j][0],mxTmp[j][1]);
			npc->set_start_place(sprintf("%d",mxTmp[j][0]*1000+mxTmp[j][1] ));
			nNpc += ({npc});
		}
	}
	map->set("tomb_npc",nNpc);	
	//巡逻怪
	npc = new("npc/copy/lishan/0001");
	npc->add_to_scene(map->get_id(),289,246,4);
	npc->set_start_point(289,246);
	npc->set_target_point(309,226);
	npc->set("copy_map_add_exp",1);
	npc->set_walk_status(1);
	//boss
	npc = new("npc/boss/0012");
	npc->add_to_scene(map->get_id(),224,217,4);
	npc->set("map",map);

	npc = new("npc/boss/0013");
	npc->add_to_scene(map->get_id(),208,123,4);
	npc->set("map",map);	
	return map;
}

//创建下层陵墓
object new_copy_tomb2(object me, object who)
{
	int tId,z,x,y,*nP,i,size,j,count;
	mapping mpTmp;
	object map,npc;
	string *nTmp;
	mixed *mxTmp;
	
	tId = who->get_team_id();
	if ( !tId )
		return 0;
	z = new_copy_scene(who,me,"/map/copy/703",({242,180}),({142,59}),COPY_TOMB2);
	if ( !z )
		return 0;
	if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
		return 0;
	map->reset();	
	//出口NPC
	npc = new("npc/copy/0008");
	npc->add_to_scene(map->get_id(),241,183,2);
	npc = new("npc/copy/0009");
	npc->add_to_scene(map->get_id(),137,62,2);
	//矿石
	nTmp = keys(mpMine);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		for(j=0,count=mpMine[nTmp[i]];j<count;j++)
		{
			npc = new(nTmp[i]);	
			if ( !npc )
				continue;
			npc->set("never_refresh",1);
			nP = nMine[random(sizeof(nMine))];
			npc->add_to_scene(z,nP[0],nP[1]);
		}	
	}
	//草药
	nTmp = keys(mpDrug2);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		for(j=0,count=mpDrug2[nTmp[i]];j<count;j++)
		{
			npc = new(nTmp[i]);	
			if ( !npc )
				continue;
			npc->set("never_refresh",1);
			nP = nDrug2[random(sizeof(nDrug1))];
			npc->add_to_scene(z,nP[0],nP[1]);
		}	
	}
	//铁质宝箱
	for(i=0;i<2;i++)
	{
		npc = new("npc/00/box2");
		if ( npc )
		{
			nP = nBox2[random(sizeof(nBox2))];
			npc->add_to_scene(z,nP[0],nP[1]);		
		}
	}
	//普通NPC
	nTmp = keys(mpNpc1);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		mxTmp = mpNpc1[nTmp[i]];
		for(j=0,count=sizeof(mxTmp);j<count;j++)
		{
			npc = new("npc/copy/lishan/"+nTmp[i]);
			if ( !npc )
				continue;
			npc->set("copy_map_add_exp",1);
			npc->add_to_scene(z,mxTmp[j][0],mxTmp[j][1]);
			npc->set_start_place(sprintf("%d",mxTmp[j][0]*1000+mxTmp[j][1] ));
		}
	}		
	//巡逻怪
	npc = new("npc/copy/lishan/0011");
	npc->add_to_scene(map->get_id(),68,60,4);
	npc->set_start_point(68,60);
	npc->set_target_point(95,33);
	npc->set("copy_map_add_exp",1);
	npc->set_walk_status(1);

	npc = new("npc/copy/lishan/0010");
	npc->add_to_scene(map->get_id(),70,62,4);
	npc->set_start_point(70,62);
	npc->set_target_point(97,35);
	npc->set_walk_status(1);
	//boss
	npc = new("npc/boss/0009");
	npc->add_to_scene(map->get_id(),141,53,4);
	npc->set("map",map);

	npc = new("npc/boss/0010");
	npc->add_to_scene(map->get_id(),204,98,4);
	npc->set("map",map);

	npc = new("npc/boss/0011");
	npc->add_to_scene(map->get_id(),166,180,4);
	npc->set("map",map);
	
//	npc = new("npc/boss/0024");
//	npc->add_to_scene(map->get_id(),206,99,4);
//	npc->set("map",map);
	
	return map;
}

//创建总监工书房
object new_copy_tomb3(object me, object who)
{
	int tId,z,x,y,*nP,i,size,j,count;
	mapping mpTmp;
	object map,npc;
	string *nTmp;
	
	tId = who->get_team_id();
	if ( !tId )
		return 0;
	z = new_copy_scene(who,me,"/map/copy/704",({42,38}),({42,38}),COPY_TOMB3);
	if ( !z )
		return 0;
	if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
		return 0;
	map->reset();	
	//出口NPC
	npc = new("npc/copy/0010");
	npc->add_to_scene(map->get_id(),39,39,2);
	//boss
	npc = new("npc/boss/0014");
	npc->add_to_scene(map->get_id(),31,25,4);
	npc->set("map",map);	
	//
	npc = new("npc/00/2011");
	npc->add_to_scene(map->get_id(),31,23,2);

	return map;
}

void close_gate(object map)
{
	int z,i,size,*nP;
	object npc;

	npc = new("npc/copy/0011");
	if ( !npc )
		return ;
	z = map->get_id();
	npc->add_to_scene(z,324,169);
	for(i=0,size=sizeof(nGate);i<size;i++)
	{
		nP = nGate[i];
		set_block(z, nP[0], nP[1], MAP_BLOCK);	
	}
	return ;	
}

int open_gate(object me, object who)
{
	int z,i,size,*nP;
	object item;
	
	item = present("机关石门钥匙", who, 1, MAX_CARRY);
	if ( !item || !item->is_jiguan() )
	{
		send_user(who,"%c%s",'!',"你没有机关石门钥匙！");
		return 0;
	}
	item->remove_from_user();
	destruct(item);
	z = get_z(me);
	for(i=0,size=sizeof(nGate);i<size;i++)
	{
		nP = nGate[i];
		remove_block(z, nP[0], nP[1], MAP_BLOCK);	
	}
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9413, 1, OVER_BODY, PF_ONCE );
	me->remove_from_scence();
	destruct(me);
	return 1;
}