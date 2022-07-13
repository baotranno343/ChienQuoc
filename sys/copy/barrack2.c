//周国天牢
// Barrack 2 =>>> Phá Thien Trận

#include <map.h>
#include <ansi.h>
#include <npc.h>
//怪物的刷新座标

// 函数：生成二进制码
void SAVE_BINARY() {}

int new_copy_scene(object who, object me)
{
	int i, z, tId;
	object map;

	tId = who->get_team_id();
	if (!tId)
		return 0;
	z = COPY_CTROL->new_scene(0, "/map/copy/ai1", 0);
	if (!z)
		return 0;
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return;
	TEAM_D->add_copy_scene(tId, COPY_BARRACK2, map);
	i = map->get_client_id();
	map->set("entrance", ({39, 30}));
	map->set("copy_id", tId);
	return z;
}

//创建新副本
object new_copy(object me, object who, int tang)
{
	int tId, z, x, y, *nP, i, size, j, count, level;
	mapping mpTmp;
	object map, npc, *team;
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
	///////////////////////
	team = who->get_team();
	size = sizeof(team);
	for (i = 0; i < size; i++)
	{
		level = level + team[i]->get_level();
	}
	level = level / size;
	npc = new (sprintf("npc/copy/boss%d", tang));
	npc->set_level(level);
	npc->add_to_scene(map->get_id(), 42, 32, 8);
	return map;
}
