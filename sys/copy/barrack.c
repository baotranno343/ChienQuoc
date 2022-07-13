//周国天牢

#include <map.h>
#include <ansi.h>
#include <npc.h>
//怪物的刷新座标
mapping mpNpc = (["0450":({205082, 206110, 225067}),
				  "0451":({
							 170122,
							 180112,
							 190117,
							 194102,
							 217077,
						 }),
				  "0452":({
							 186116,
							 191100,
							 207085,
							 210114,
						 }),
				  "0421":({
							 219098,
							 221098,
							 222096,
							 239100,
							 240102,
							 242101,
						 }),
				  "0470":({
							 119139,
							 121100,
							 136102,
							 138087,
							 146111,
							 155103,
							 141158,
						 }),
				  "0472":({117142, 121163, 123103, 133101, 144140, 147144, 157136, 169133, 172114, 136159, 138083}),
				  "0462":({115145, 117165, 124085, 135085, 136097, 143114, 157132, 169113, 125100, 139161, 157100, 167136}),
				  "0463":({62152, 68151, 79130, 82140, 86161, 87141, 91153, 104144, 105147, 128177, 132174}),
				  "0465":({65157, 73129, 76126, 84161, 86136, 93151}),
]);

mixed *nMine = ({
	({34, 139}),
	({46, 131}),
	({59, 148}),
	({63, 160}),
	({72, 176}),
	({77, 140}),
	({78, 121}),
	({80, 105}),
	({97, 100}),
	({98, 136}),
	({102, 164}),
	({102, 189}),
	({110, 161}),
	({115, 153}),
	({119, 159}),
	({124, 183}),
	({133, 171}),
	({134, 70}),
	({143, 175}),
	({150, 151}),
	({153, 166}),
	({157, 150}),
	({163, 157}),
	({173, 150}),
	({181, 142}),
	({189, 138}),
	({192, 132}),
	({204, 127}),
	({215, 117}),
	({238, 108}),
	({246, 73}),
	({247, 101}),
});

mixed *nDrug = ({
	({43, 140}),
	({63, 158}),
	({66, 117}),
	({73, 183}),
	({80, 109}),
	({90, 188}),
	({95, 136}),
	({105, 112}),
	({123, 180}),
	({134, 73}),
	({134, 121}),
	({141, 64}),
	({141, 170}),
	({150, 161}),
	({151, 86}),
	({156, 140}),
	({161, 96}),
	({164, 145}),
	({173, 107}),
	({174, 138}),
	({182, 127}),
	({183, 34}),
	({198, 115}),
	({200, 127}),
	({204, 100}),
	({206, 76}),
	({215, 95}),
	({216, 90}),
	({222, 100}),
	({231, 110}),
	({233, 93}),
	({234, 76}),
	({234, 109}),
	({237, 85}),
	({245, 93}),
});

mixed *nBox = ({
	({47, 140}),
	({64, 127}),
	({115, 80}),
	({137, 129}),
	({138, 176}),
	({148, 55}),
	({249, 75}),
	({253, 80}),
});

mapping mpMine = (["npc/00/tie.c":2,
				  "npc/00/jtie.c":2,
				   "npc/00/jin.c":1,
]);

mapping mpDrug = (["npc/00/herb9.c":2,
				  "npc/00/herb10.c":2,
				  "npc/00/herb11.c":2,
				  "npc/00/herb12.c":2,
				  "npc/00/herb13.c":2,
				  "npc/00/herb14.c":2,
				  "npc/00/herb15.c":2,
				  "npc/00/herb16.c":2,
				  "npc/00/herb17.c":2,
]);

// 函数：生成二进制码
void SAVE_BINARY() {}

int new_copy_scene(object who, object me)
{
	int i, z, tId;
	object map;

	tId = who->get_team_id();
	if (!tId)
		return 0;
	z = COPY_CTROL->new_scene(0, "/map/copy/701", 0);
	if (!z)
		return 0;
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return;
	TEAM_D->add_copy_scene(tId, COPY_BARRACK, map);
	i = map->get_client_id();
	map->set("entrance", ({230, 45}));
	map->set("copy_id", tId);
	//tell_user(find_char("971"),"%d %d %d %d",map->get_id(),map->get_client_id(),nXy[0],nXy[1]);
	return z;
}

//创建新副本
object new_copy(object me, object who)
{
	int tId, z, x, y, *nP, i, size, j, count;
	mapping mpTmp;
	object map, npc;
	string *nTmp;

	tId = who->get_team_id();
	if (!tId)
		return 0;
	z = new_copy_scene(who, me);
	if (!z)
		return 0;
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return 0;
	map->reset();
	//出口NPC
	npc = new ("npc/copy/0004");
	npc->add_to_scene(map->get_id(), 235, 45, 5);
	//普通NPC
	nTmp = keys(mpNpc);
	for (i = 0, size = sizeof(nTmp); i < size; i++)
	{
		nP = mpNpc[nTmp[i]];
		for (j = 0, count = sizeof(nP); j < count; j++)
		{
			npc = new ("npc/copy/" + nTmp[i]);
			if (!npc)
				continue;
			npc->set("copy_map_add_exp", 1);
			npc->add_to_scene(z, nP[j] / 1000, nP[j] % 1000);
			npc->set_start_place(sprintf("%d", nP[j]));
		}
	}
	//矿石
	nTmp = keys(mpMine);
	for (i = 0, size = sizeof(nTmp); i < size; i++)
	{
		for (j = 0, count = mpMine[nTmp[i]]; j < count; j++)
		{
			npc = new (nTmp[i]);
			if (!npc)
				continue;
			npc->set("never_refresh", 1);
			nP = nMine[random(sizeof(nMine))];
			npc->add_to_scene(z, nP[0], nP[1]);
		}
	}
	//草药
	nTmp = keys(mpDrug);
	for (i = 0, size = sizeof(nTmp); i < size; i++)
	{
		for (j = 0, count = mpDrug[nTmp[i]]; j < count; j++)
		{
			npc = new (nTmp[i]);
			if (!npc)
				continue;
			npc->set("never_refresh", 1);
			nP = nDrug[random(sizeof(nDrug))];
			npc->add_to_scene(z, nP[0], nP[1]);
		}
	}
	//铁质宝箱
	npc = new ("npc/00/box2");
	if (npc)
	{
		nP = nBox[random(sizeof(nBox))];
		npc->add_to_scene(z, nP[0], nP[1]);
	}
	//巡逻怪
	npc = new ("npc/copy/0472");
	npc->add_to_scene(map->get_id(), 124, 159, 4);
	npc->set_start_point(124, 159);
	npc->set_target_point(138, 145);
	npc->set("copy_map_add_exp", 1);
	npc->set_walk_status(1);

	npc = new ("npc/copy/0462");
	npc->add_to_scene(map->get_id(), 126, 161, 4);
	npc->set_start_point(126, 161);
	npc->set_target_point(140, 147);
	npc->set("copy_map_add_exp", 1);
	npc->set_walk_status(1);

	npc = new ("npc/copy/0463");
	npc->add_to_scene(map->get_id(), 88, 114, 4);
	npc->set_start_point(88, 114);
	npc->set_target_point(113, 139);
	npc->set("copy_map_add_exp", 1);
	npc->set_walk_status(1);

	npc = new ("npc/copy/0465");
	npc->add_to_scene(map->get_id(), 89, 112, 4);
	npc->set_start_point(89, 112);
	npc->set_target_point(114, 137);
	npc->set("copy_map_add_exp", 1);
	npc->set_walk_status(1);

	//马鬼
	//	npc = new("npc/boss/0023");
	//	npc->add_to_scene(map->get_id(),169,138,4);
	//马鬼
	npc = new ("npc/boss/0008");
	npc->add_to_scene(map->get_id(), 245, 83, 4);
	//梁兴
	npc = new ("npc/boss/0004");
	npc->add_to_scene(map->get_id(), 123, 89, 4);
	//燕十三
	npc = new ("npc/boss/0006");
	npc->add_to_scene(map->get_id(), 130, 175, 4);
	//司邪
	npc = new ("npc/boss/0005");
	npc->add_to_scene(map->get_id(), 61, 133, 8);
	return map;
}
