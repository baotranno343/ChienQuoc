#include <npc.h>
#include <ansi.h>
#include <cmd.h>
#include <effect.h>
#include <public.h>
#include <map.h>

#define FILE_MAP "map/copy/705"
#define FILE_SENDER "npc/party/0042"
#define FILE_GUAI "npc/boss/00083"
#define FILE_BOSS "npc/boss/00082"
#define CHECK_TIME "sys/party/gumu_check_time"

#define DEBUG(who, arg) ;	   //tell_user(who,arg);
#define DEBUG2(who, z, x, y) ; //who->add_to_scene(z,x,y);

inherit OFFICER;

object *Map;
mapping zoubiao = ([1:({96, 52}),
					2:({100, 52}), 3:({104, 54}), 4:({103, 59}), 5:({98, 59}), 6:({95, 61}), 7:({93, 66}), 8:({92, 70}), 9:({90, 74}), 10:({87, 77}),
				   11:({82, 79}), 12:({82, 84}), 13:({86, 86}), 14:({92, 86}), 15:({97, 86}), 16:({101, 84}), 17:({100, 89}), 18:({97, 92}), 19:({100, 94}), 20:({103, 90}),
				   21:({107, 91}), 22:({105, 95}), 23:({101, 97}), 24:({98, 97}), 25:({96, 99}), 26:({103, 101}), 27:({102, 104}), 28:({101, 107}), 29:({106, 107}), 30:({105, 111}),
				   31:({108, 111}), 32:({111, 113}), 33:({110, 117}), 34:({115, 115}), 35:({116, 119}), 36:({119, 119}), 37:({122, 117}), 38:({121, 121}), 39:({124, 121}), 40:({125, 121}),
				   41:({124, 123}), 42:({124, 125}), 43:({127, 123}), 44:({128, 121}), 45:({130, 121}), 46:({129, 124}), 47:({128, 127}), 48:({130, 124}), 49:({133, 122}), 50:({133, 125}),
				   51:({132, 128}), 52:({135, 127}), 53:({136, 125}), 54:({138, 123}), 55:({140, 121}), 56:({140, 125}), 57:({139, 130}), 58:({140, 130}), 59:({143, 126}), 60:({144, 124}),
				   61:({144, 122}), 62:({147, 125}), 63:({146, 130}), 64:({147, 129}), 65:({147, 124}), 66:({147, 126}), 67:({147, 128}), 68:({146, 131}), 69:({150, 128}), 70:({150, 126}),
				   71:({151, 122}), 72:({151, 124}), 73:({149, 127}), 74:({150, 130}), 75:({152, 129}), 76:({154, 126}), 77:({154, 123}), 78:({155, 120}), 79:({155, 124}), 80:({154, 128}),
				   81:({154, 130}), 82:({154, 131}), 83:({156, 128}), 84:({157, 124}), 85:({157, 126}), 86:({158, 130}), 87:({157, 133}), 88:({159, 131}), 89:({160, 130}), 90:({161, 127}),
				   91:({162, 124}), 92:({162, 122}), 93:({163, 121}), 94:({163, 120}), 95:({164, 124}), 96:({163, 128}), 97:({164, 131}), 98:({164, 129}), 99:({165, 126}), 100:({165, 124}),
				  101:({163, 121}), 102:({164, 119}), 103:({166, 123}), 104:({166, 126}), 105:({167, 128}), 106:({169, 127}), 107:({168, 124}), 108:({168, 122}), 109:({170, 124}), 110:({171, 127}),
				  111:({173, 127}), 112:({174, 125}), 113:({174, 124}), 114:({174, 120}), 115:({175, 117}), 116:({177, 117}), 117:({177, 120}), 118:({176, 123}), 119:({175, 126}), 120:({175, 129}),
				  121:({177, 129}), 122:({177, 128}), 123:({178, 126}), 124:({179, 123}), 125:({179, 120}), 126:({180, 117}), 127:({181, 120}), 128:({180, 123}), 129:({180, 125}), 130:({178, 128}),
				  131:({178, 132}), 132:({180, 130}), 133:({181, 127}), 134:({182, 125}), 135:({184, 125}), 136:({184, 123}), 137:({184, 127}), 138:({185, 130}), 139:({186, 129}), 140:({187, 127}),
				  141:({190, 126}), 142:({189, 128}), 143:({190, 131}), 144:({193, 129}), 145:({194, 127}), 146:({197, 125}), 147:({197, 128}), 148:({197, 131}), 149:({195, 135}), 150:({198, 134}),
				  151:({202, 132}), 152:({203, 130}), 153:({206, 127}), 154:({209, 123}), 155:({209, 127}), 156:({209, 131}), 157:({207, 135}), 158:({204, 137}), 159:({201, 140}), 160:({204, 139}),
				  161:({208, 135}), 162:({211, 131}), 163:({212, 136}), 164:({210, 140}), 165:({208, 144}), 166:({206, 148}), 167:({209, 146}), 168:({212, 144}), 169:({215, 141}), 170:({217, 138}),
				  171:({219, 135}), 172:({221, 132}), 173:({222, 135}), 174:({226, 135}), 175:({231, 132}), 176:({226, 136}), 177:({223, 139}), 178:({220, 141}), 179:({217, 144}), 180:({214, 145}),
				  181:({212, 149}), 182:({211, 153}), 183:({209, 155}), 184:({206, 159}), 185:({209, 160}), 186:({205, 160}), 187:({193, 166}), 188:({198, 168}), 189:({201, 166}), 190:({204, 163}),
				  191:({204, 166}), 192:({206, 166}), 193:({205, 169}), 194:({207, 169}), 195:({206, 172}), 196:({212, 179}), 197:({215, 183}), 198:({218, 193}), 199:({223, 199}), 200:({226, 204}),

]);
int new_copy_scene(object who, object me);
int new_copy_npc(int z, int level);
int new_copy(object who, object me);
//int add_npc(int z,int x,int y,int level);

// 函数：生成二进制码
void SAVE_BINARY() {}

int add_npc(object who, int z, int x, int y, int level);
int add_boss(object who, int z, int x, int y, int level);
//int add_boss(int z,int x,int y,int level);

void create()
{
	Map = ({});
	setup();
}
void do_look(object who, object me)
{
	string result;
	if (!(CHECK_TIME->get_gumu_party_open()))
		return;
	if (!(CHECK_TIME->get_gumu_open()))
	{
		result = sprintf(me->get_name() + ":\nTương truyền để tưởng nhớ một vị đại tướng của Tần Quốc qua đời, Tần Vương đã ban thưởng những báu vật kỳ lạ để tuẫn táng theo vị đại tướng này. Tin tức về các kì trân dị bảo đã thu hút vô số anh hùng hảo hán đến thám hiểm, tuy nhiên kết cục không ai phá vỡ được Thạch Dũng Trận bên trong Cổ Mộ và đều ra về tay không. Ngươi có muốn thử sức mình không? ( Hãy đến tìm tai để được đến Cổ Mộ mỗi ngày từ 20: 30 đến 22:00).\n");
		result += sprintf(ESC "Rời khỏi");
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
		return;
	}
	result = sprintf(me->get_name() + ":\nTương truyền để tưởng nhớ một vị đại tướng của Tần Quốc qua đời, Tần Vương đã ban thưởng những báu vật kỳ lạ để tuẫn táng theo vị đại tướng này. Tin tức về các kì trân dị bảo đã thu hút vô số anh hùng hảo hán đến thám hiểm, tuy nhiên kết cục không ai phá vỡ được Thạch Dũng Trận bên trong Cổ Mộ và đều ra về tay không. Ngươi có muốn thử sức mình không?\n");
	result += sprintf(ESC "Thám hiểm Cổ mộ\ntalk %x# welcome.1\n", getoid(me));
	result += sprintf(ESC "Rời khỏi");
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
}

void do_welcome(object me, object who, string arg)
{
	int i, flag, size, x, y, z, p, tid;
	int level = 0;
	string result;
	object map, *team;

	who->set_time("time", 0);
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		team = who->get_team();
		size = sizeof(team);
		if (!(CHECK_TIME->get_gumu_party_open()))
			return;
		if (!(CHECK_TIME->get_gumu_open()))
			return;
		if (!who->is_leader())
		{
			result = sprintf(me->get_name() + ":\n    Hãy gọi đội trưởng tới gặp ta !\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}

		if (size < 0)
		{
			result = sprintf(me->get_name() + ":\n    Lập tổ đội rồi mới đến gặp ta !\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}

		for (i = 0; i < size; i++)
		{
			if (!objectp(team[i]))
				continue;
			if (!inside_screen_2(me, team[i]))
			{
				result = sprintf(me->get_name() + ":\n    Hãy gọi tất cả thành viên trong nhóm đến gặp ta !\n");
				result += sprintf(ESC "Rời khỏi");
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
				return;
			}
			if (team[i]->get_level() < 60)
			{
				result = sprintf(me->get_name() + ":\n    Thành viên trong nhóm ngươi " HIR "%s " NOR "cấp bậc chưa đủ 60 cấp !\n", team[i]->get_name());
				result += sprintf(ESC "Rời khỏi");
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
				return;
			}
		}
		// if (!who->get("checkpointsuccess"))
		// {
		// 	//result = sprintf("Bạn hãy nhập mã xác minh\n" ESC "1\n" ESC "\ncheckpoint\n");
		// 	//result = sprintf("Bạn hãy nhập mã xác minh\n" ESC "%c\n" ESC "\ncheckpoint\n", 1);
		// 	//send_user(who, "%c%c%s", 0x59, 1, result);
		// 	"/cmd/user/checkpoint"->main(who);
		// 	return;
		// }
		if (!new_copy(who, me) == 1)
			return;
		tid = who->get("team_id");
		map = TEAM_D->get_copy_scene(tid, COPY_GUMU);
		if (map)
		{
			z = map->get_id();
			x = 102;
			y = 62;
			if (!p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
				return;
			x = (p % 1000000) / 1000;
			y = p % 1000;

			for (i = 0; i < sizeof(team); i++)
			{
				team[i]->set("me_die", 1);
				send_user(team[i], "%c%c%w%s", 0x5a, 0, 3, "Đang di chuyển……");
				team[i]->set_2("travel.z", z);
				team[i]->set_2("travel.p", p);
				team[i]->set("map", map);
				set_effect(team[i], EFFECT_TRAVEL, 3);
				//					team[i]->add_to_scene(z,x,y,3);
				if (is_god(team[i]))
				{
					DEBUG(team[i], sprintf("测试--do_look z=%d,level=%d", z, map->get("copy_level")));
				}
			}
		}
		break;
	}
}
//创建新的虚拟场景395并把NPC放入指定位置(94,54)处;
int new_copy_scene(object who, object me)
{
	int z, d, tid, i, size;
	object map, npc, *team;
	d = 395;
	tid = who->get_team_id();
	if (!tid)
		return 0;
	team = who->get_team();
	size = sizeof(team);
	z = COPY_CTROL->new_scene(d, FILE_MAP, "Cổ Mộ");
	if (!z)
		return 0;
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return 0;
	TEAM_D->add_copy_scene(tid, COPY_GUMU, map);
	map->set("copy_id", 1);
	map->set("gumu_map", 1);
	Map += ({map});
	npc = new (FILE_SENDER); //新建一副本NPC-->场景传送人
	if (!npc)
		return 0;
	npc->add_to_scene(z, 94, 52, 3);
	for (i = 0; i < size; i++)
	{
		team[i]->set("team_id", tid);
		map->set_owner(team[i]);
	}
	return z;
}
// 生成副本第一个怪并把放入第一个指定位置(78,81)
int new_copy_npc(int z, int level)
{
	int key, *xy, ap, hp;
	object map, npc;

	key = 1;
	xy = zoubiao[key];
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return 0;
	npc = new (FILE_GUAI);
	if (!npc)
		return 0;
	npc->set_level(level);
	NPC_ENERGY_D->init_level(npc, level);
	npc->set_fight_status(level);
	//	npc->set_name(sprintf("Thủ Mộ Thạch Dũng %d ",key));
	npc->add_to_scene(z, xy[0], xy[1], 3);
	map->set("copy_npc_sum", 200);
	map->add("copy_npc_count", 1);
	DEBUG(this_player(), sprintf("测试--new_copy_npc->copy_npc_count=%d", map->get("copy_npc_count")));
	return 1;
}
//生成虚拟场景。
int new_copy(object who, object me)
{
	int i, tid, size, z;
	int level = 0;
	object *team, map;
	//求出队伍的平均级别
	tid = who->get_team_id();
	if (!tid)
		return 0;
	if (!team = who->get_team())
		return 0;
	for (i = 0, size = sizeof(team); i < size; i++)
		level += team[i]->get_level();
	level = level / size;

	z = new_copy_scene(who, me);
	if (!z)
		return 0;
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return 0;
	if (!new_copy_npc(z, level))
		return 0;
	map->set("copy_level", level);
	return 1;
}
//npc  死亡处理
void npc_die(object who, object me)
{
	int z, level, key, *xy, i, size, count, tid;
	string result;
	object map, *team = ({});

	team = who->get_team();
	if (!team)
		team = ({who});
	size = sizeof(team);
	tid = who->get("team_id");
	DEBUG(who, sprintf("tid=%d", tid));
	map = who->get("map");
	//	map=TEAM_D->get_copy_scene(tid,COPY_GUMU);
	if (!map)
		return;
	z = map->get_id();
	DEBUG(who, sprintf("z=%d", z));
	level = map->get("copy_level");
	map->add("kill_npc_count", 1);
	key = map->get("kill_npc_count");
	count = map->get("copy_npc_count");
	for (i = 0; i < size; i++)
	{
		send_user(team[i], "%c%s", '!', sprintf("Đã tiêu diệt được：" HIY " %d/200", key));
		DEBUG(team[i], sprintf("测试--npc_die key=%d", key));
		DEBUG(team[i], sprintf("测试--npc_die kill_npc_count=%d", key));
	}
	if ((count > 0 && count < 50) || (count > 50 && count < 100) ||
		(count > 100 && count < 150) || (count > 150 && count < 200))
	{
		xy = zoubiao[key + 1];
		__FILE__->add_npc(who, z, xy[0], xy[1], level);
		for (i = 0; i < size; i++)
		{
			DEBUG(team[i], sprintf("测试--下一个NPC key=%d x=%d y=%d", key + 1, xy[0], xy[1]));
			DEBUG2(team[i], map->get_id(), xy[0] + 1, xy[1] + 1);
		}
	}
	if (count == 50 || count == 100 || count == 150)
	{
		xy = zoubiao[key + 1];
		__FILE__->add_npc(who, z, xy[0], xy[1], level);
		for (i = 0; i < size; i++)
		{
			DEBUG(team[i], sprintf("测试--下一个NPC key=%d x=%d y=%d", key + 1, xy[0], xy[1]));
			DEBUG2(team[i], map->get_id(), xy[0] + 1, xy[1] + 1);
		}
		xy = zoubiao[key + 2];
		__FILE__->add_npc(who, z, xy[0], xy[1], level);
		for (i = 0; i < size; i++)
		{
			DEBUG(team[i], sprintf("测试--下一个NPC key=%d x=%d y=%d", key + 1, xy[0], xy[1]));
			DEBUG2(team[i], map->get_id(), xy[0] + 1, xy[1] + 1);
		}
	}
	if (count == 200)
	{
		if (!(key == map->get("copy_npc_sum")))
			return;
		for (i = 0; i < size; i++)
		{
			send_user(team[i], "%c%s", '!', HIY "Thủ Mộ Thạch Tướng đã tỉnh dậy !");
		}
		xy = zoubiao[key];
		__FILE__->add_boss(who, z, xy[0], xy[1], level);
	}
}

int add_npc(object who, int z, int x, int y, int level) //加入小怪
{
	int ap, hp, i, size, tid;
	object map, npc, *team;

	//who=this_player();
	tid = who->get("team_id");
	DEBUG(who, "add_npc test");
	//if(!map=TEAM_D->get_copy_scene(tid,COPY_GUMU)) return;
	if (!map = who->get("map"))
		return;
	if (!(map->get("copy_npc_count") <= map->get("copy_npc_sum")))
	{
		send_user(who, "%c%s", '!', HIY "Thủ Mộ Thạch Tướng đã tỉnh dậy !");
		return;
	}
	npc = new (FILE_GUAI);
	if (!npc)
		return 0;
	npc->set_level(level);
	NPC_ENERGY_D->init_level(npc, level);
	npc->set_fight_status(level);
	map->add("copy_npc_count", 1);
	//npc->set_name(sprintf("Thủ Mộ Thạch Dũng %d ",map->get("copy_npc_count")));	//用于测试
	npc->add_to_scene(z, x, y, 3);
	return 1;
}

//int new_scene(int d, string mapname,string name) //新增副本场景
//{
//	int z;
//	object map;
//	if( ( z = find_map_flag(COPY_MAP_BEGIN, COPY_MAP_END, 0) ) > 0 )
//	{
//		init_virtual_map(z, d);
//		map = new(mapname);
//		if(!map) return;
//		map->set_client_id(d);
//		map->set("gumu_map",1);
//		set_map_object( map, map->set_id(z) );
//		Map+=({map});
//	}
//	return z;
//}

int add_boss(object who, int z, int x, int y, int level) //加入大boss
{
	int ap, hp, rate, type, tid;
	object map, npc;
	//who=this_player();
	tid = who->get("team_id");
	//if(!map=TEAM_D->get_copy_scene(tid,COPY_GUMU)) return;
	if (!map = who->get("map"))
		return;
	rate = random100();
	npc = new (FILE_BOSS);
	if (!npc)
		return;
	if (rate < 20)
		type = 1;
	else if (rate < 40)
		type = 2;
	else if (rate < 60)
		type = 3;
	else if (rate < 70)
		type = 4;
	else if (rate < 90)
		type = 5;
	else
		type = 6;

	npc->set_level(level);
	NPC_ENERGY_D->init_level(npc, level);
	npc->set_fight_status(type, level);
	npc->add_to_scene(z, x, y, 3, 9413);
	return 1;
}

//24:00时退出还在古墓的所有玩家
void player_exit()
{
	int i, j, size1, size2, x, y, z, p;
	object *member;
	x = 276;
	y = 163;
	z = 80;
	if (!Map)
		return;
	size1 = sizeof(Map);
	for (i = 0; i < size1; i++)
	{
		member = FILE_MAP->get_all_user(Map[i]);
		if ((size2 = sizeof(member)) < 1)
			continue;
		for (j = 0; j < size2; j++)
		{
			if (!p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
				return;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			send_user(member[j], "%c%s", '!', HIY "Ngươi đã vượt qua thời gian thám hiểm !");
			call_out("send_player", 3, member[j]);
		}
	}
}

void send_player(object who)
{
	int x, y, z, p;
	z = 80;
	x = 276;
	y = 163;
	if (!p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
		return;
	x = (p % 1000000) / 1000;
	y = p % 1000;
	who->add_to_scene(z, x, y);
}

object *delete_map(object map)
{
	Map -= ({map});
	return Map;
}
