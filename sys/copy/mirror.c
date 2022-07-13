#include <map.h>
#include <ansi.h>
#include <npc.h>
#define MIRROR_NPC "npc/copy/00011"
#define MIRROR_NPC1 "npc/copy/00012"

static mapping mpScene = ([003:({82, 119}),									  //012:({111,52}),013:({148,217}),014:({74,73}),015:({131,28}),
						   041:({146, 127}),								  //043:({189,173}),
						   091:({220, 76}), 092:({232, 85}), 093:({200, 60}), //112:({148,174}),
						   117:({74, 141}), 118:({52, 113}), 119:({103, 163}), 131:({64, 61}), 133:({57, 136}),
						   134:({109, 168}), 135:({135, 163}), //155:({128,41}),161:({142,201}),
						   211:({158, 143}),				   //243:({166,184}),251:({228,29}),264:({48,118}),
															   //	266:({224,136}),271:({185,47}),281:({26,152}),282:({167,58}),284:({57,35}),
						   311:({94, 45}), 312:({60, 55}), 313:({73, 46}), 381:({239, 94}), 383:({218, 94}),
						   385:({207, 90}), //503:({63,105}),505:({62,101}),512:({156,28}),514:({231,177}),
											//	521:({59,143}),524:({34,125}),525:({106,81}),526:({66,102}),527:({36,125}),
											//	528:({185,47}),529:({132,62}),530:({240,83}),
]);
mapping mpShap = (["空手":({
							  0050,
							  0051,
							  0101,
							  0102,
							  0302,
							  0150,
							  0500,
							  0100,
							  0152,
							  0101,
							  0052,
							  0201,
							  0901,
							  0250,
							  0200,
							  0201,
							  5209,
							  1000,
							  0251,
							  0250,
							  0600,
							  0552,
							  8012,
							  0651,
							  0901,
							  0801,
							  0300,
							  0301,
							  0150,
							  0303,
							  0350,
							  0351,
							  0352,
							  8010,
							  0304,
							  0500,
							  0102,
							  0152,
							  0400,
							  0401,
							  0450,
							  0451,
							  0452,
							  0301,
							  0500,
							  0502,
							  0350,
							  0550,
							  0551,
							  0552,
							  0600,
							  0601,
							  0650,
							  0651,
							  1000,
							  8010,
							  4135,
							  0752,
							  0902,
							  0751,
							  4131,
							  0750,
							  0800,
							  0801,
							  0802,
							  4134,
							  0700,
							  0701,
							  0850,
							  0852,
							  0851,
							  0800,
							  0801,
							  0751,
							  0752,
							  0951,
							  0952,
							  0954,
							  0702,
							  1050,
							  4132,
							  4133,
							  1051,
							  1052,
							  1100,
							  1101,
							  1102,
						  }),
				   "暗器":({0202, 0652, 0602, 0652, 1001, 0853, 0950}),
				   "五雷":({0900, 0901, 0702, 0901, 0900, 0900, 0953, 0402}),
]);
mapping mpNpc = (["Kính Yêu Kỉ Quốc":(["kind":"无", "strong":"正常", "level":35, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4042", "/item/40/4041"}), 3500:({"/item/41/4111", "/item/91/9111"}), ])]),
				 "Kính Yêu Ngu Quốc":(["kind":"无", "strong":"正常", "level":40, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4046"}), 3500:({"/item/stuff/0144"}), ])]),
				"Kính Yêu Quắc Quốc":(["kind":"无", "strong":"正常", "level":45, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4048"}), 3500:({"/item/41/4107"}), ])]),
				"Kính Yêu Thái Quốc":(["kind":"无", "strong":"正常", "level":50, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4037", "/item/40/4016"}), 3500:({"/item/41/4111", "/item/41/4101", "/item/91/9111"}), ])]),
				"Kính Yêu Cảnh Quốc":(["kind":"无", "strong":"正常", "level":55, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4052", "/item/40/4030", "/item/40/4031"}), 3500:({"/item/32/3285"}), ])]),
				  "Kính Yêu Ba Quốc":(["kind":"无", "strong":"正常", "level":60, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4053"}), 3500:({"/item/stuff/0144", "/item/stuff/0171"}), ])]),
				"Kính Yêu Trần Quốc":(["kind":"无", "strong":"正常", "level":65, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4053"}), 3500:({"/item/stuff/0049"}), ])]),
				 "Kính Yêu Bội Quốc":(["kind":"无", "strong":"正常", "level":70, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4057"}), 3500:({"/item/91/9101"}), ])]),
				  "Kính Yêu Vệ Quốc":(["kind":"无", "strong":"正常", "level":75, "rand":3, "weapon":"空手", "spe":3, "droprate":([3000:({"/item/40/4058"}), 3500:({"/item/41/4110", "/item/stuff/0032"}), ])]),
			   "Kính Yêu Lương Quốc":(["kind":"无", "strong":"正常", "level":80, "rand":3, "weapon":"空手", "spe":3, "droprate":([2000:({"/item/40/4034", "/item/40/4062", "/item/40/4061"}), 2500:({"/item/stuff/0032"}), ])]),
				  "Kính Yêu Lỗ Quốc":(["kind":"无", "strong":"正常", "level":85, "rand":3, "weapon":"空手", "spe":3, "droprate":([2000:({"/item/40/4069", "/item/40/4070"}), 2500:({"/item/stuff/0130"}), ])]),
			   "Kính Yêu Trịnh Quốc":(["kind":"无", "strong":"正常", "level":90, "rand":3, "weapon":"空手", "spe":3, "droprate":([2000:({"/item/40/4060", "/item/40/4065", "/item/40/4032"}), 2500:({"/item/stuff/0032", "/item/stuff/0130", "/item/stuff/0187"}), ])]),
				"Kính Yêu Việt Quốc":(["kind":"无", "strong":"正常", "level":95, "rand":3, "weapon":"空手", "spe":3, "droprate":([2000:({"/item/40/4074"}), 2500:({"/item/stuff/0187"}), ])]),
				 "Kính Yêu Ngô Quốc":(["kind":"无", "strong":"正常", "level":100, "rand":3, "weapon":"空手", "spe":3, "droprate":([2000:({"/item/40/4076"}), 2500:({"/item/91/9135", "/item/stuff/0176"}), ])]),
				 "Kính Yêu Tấn Quốc":(["kind":"无", "strong":"正常", "level":105, "rand":3, "weapon":"空手", "spe":3, "droprate":([2000:({"/item/40/4078"}), 2500:({"/item/stuff/0049"}), ])]),
				  "Kính Yêu Ác Mộng":(["kind":"无", "strong":"强壮", "level":120, "rand":3, "weapon":"空手", "spe":3, "droprate":([200:({"/item/test/pyktanthu"}), 2000:({"/item/40/4078"}), 2500:({"/item/stuff/0049"}), ])]),
				   "Kính Ma Kỉ Quốc":(["kind":"无", "strong":"正常", "level":35, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4043", "/item/40/4044"}), 3500:({"/item/32/3283", "/item/stuff/0190", "/item/stuff/0188"}), ])]),
				  "Kính Ma Ngu Quốc":(["kind":"无", "strong":"正常", "level":40, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4046"}), 3500:({"/item/stuff/0171"}), ])]),
				 "Kính Ma Quắc Quốc":(["kind":"无", "strong":"正常", "level":45, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4048"}), 3500:({"/item/stuff/0144", "/item/stuff/0171"}), ])]),
				 "Kính Ma Thái Quốc":(["kind":"无", "strong":"正常", "level":50, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4034"}), 3500:({"/item/41/4106", "/item/stuff/0169", "/item/41/4105", "/item/41/4101"}), ])]),
				 "Kính Ma Cảnh Quốc":(["kind":"无", "strong":"正常", "level":55, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4052", "/item/40/4030", "/item/40/4031"}), 3500:({"/item/stuff/0144", "/item/stuff/0171"}), ])]),
				   "Kính Ma Ba Quốc":(["kind":"无", "strong":"正常", "level":60, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4054"}), 3500:({"/item/stuff/0144", "/item/stuff/0171"}), ])]),
				 "Kính Ma Trần Quốc":(["kind":"无", "strong":"正常", "level":65, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4056"}), 3500:({"/item/stuff/0148"}), ])]),
				  "Kính Ma Bội Quốc":(["kind":"无", "strong":"正常", "level":70, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({}), 3500:({"/item/stuff/0148"}), ])]),
				   "Kính Ma Vệ Quốc":(["kind":"无", "strong":"正常", "level":75, "rand":3, "weapon":"暗器", "spe":4, "droprate":([3000:({"/item/40/4034", "/item/40/4060"}), 3500:({"/item/stuff/0160", "/item/91/9101"}), ])]),
				"Kính Ma Lương Quốc":(["kind":"无", "strong":"正常", "level":80, "rand":3, "weapon":"暗器", "spe":4, "droprate":([2000:({"/item/40/4064", "/item/40/4065", "/item/40/4066"}), 2500:({"/item/41/4109"}), ])]),
				   "Kính Ma Lỗ Quốc":(["kind":"无", "strong":"正常", "level":85, "rand":3, "weapon":"暗器", "spe":4, "droprate":([2000:({"/item/40/4063"}), 2500:({"/item/stuff/0053"}), ])]),
				"Kính Ma Trịnh Quốc":(["kind":"无", "strong":"正常", "level":90, "rand":3, "weapon":"暗器", "spe":4, "droprate":([2000:({"/item/40/4034", "/item/40/4071", "/item/40/4072"}), 2500:({"/item/stuff/0032", "/item/stuff/0187"}), ])]),
				 "Kính Ma Việt Quốc":(["kind":"无", "strong":"正常", "level":95, "rand":3, "weapon":"暗器", "spe":4, "droprate":([2000:({"/item/40/4074"}), 2500:({"/item/91/9140", "/item/stuff/0028"}), ])]),
				  "Kính Ma Ngô Quốc":(["kind":"无", "strong":"正常", "level":100, "rand":3, "weapon":"暗器", "spe":4, "droprate":([2000:({"/item/40/4047", "/item/40/4077"}), 2500:({"/item/91/9135", "/item/stuff/0176"}), ])]),
				  "Kính Ma Tấn Quốc":(["kind":"无", "strong":"正常", "level":105, "rand":3, "weapon":"暗器", "spe":4, "droprate":([2000:({"/item/40/4079"}), 2500:({}), ])]),
				   "Kính Ma Ác Mộng":(["kind":"无", "strong":"强壮", "level":120, "rand":3, "weapon":"暗器", "spe":4, "droprate":([200:({"/item/test/pyktanthu"}), 2000:({"/item/40/4079"}), 2500:({}), ])]),
				  "Kính Qủy Kỉ Quốc":(["kind":"无", "strong":"正常", "level":35, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4011", "/item/40/4045"}), 3500:({"/item/41/4106", "/item/stuff/0169", "/item/41/4105", "/item/41/4101"}), ])]),
				 "Kính Qủy Ngu Quốc":(["kind":"无", "strong":"正常", "level":40, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4046"}), 3500:({"/item/stuff/0044"}), ])]),
				"Kính Qủy Quắc Quốc":(["kind":"无", "strong":"正常", "level":45, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4048"}), 3500:({"/item/stuff/0144", "/item/stuff/0171"}), ])]),
				"Kính Qủy Thái Quốc":(["kind":"无", "strong":"正常", "level":50, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4051", "/item/40/4050"}), 3500:({"/item/41/4110", "/item/91/9111", "/item/stuff/0032"}), ])]),
				"Kính Qủy Cảnh Quốc":(["kind":"无", "strong":"正常", "level":55, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4052", "/item/40/4030", "/item/40/4031"}), 3500:({"/item/stuff/0144", "/item/stuff/0171"}), ])]),
				  "Kính Qủy Ba Quốc":(["kind":"无", "strong":"正常", "level":60, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4055"}), 3500:({"/item/stuff/0144", "/item/stuff/0171"}), ])]),
				"Kính Qủy Trần Quốc":(["kind":"无", "strong":"正常", "level":65, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4055"}), 3500:({"/item/stuff/0049"}), ])]),
				 "Kính Qủy Bội Quốc":(["kind":"无", "strong":"正常", "level":70, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({}), 3500:({"/item/stuff/0148"}), ])]),
				  "Kính Qủy Vệ Quốc":(["kind":"无", "strong":"正常", "level":75, "rand":3, "weapon":"五雷", "spe":4, "droprate":([3000:({"/item/40/4034", "/item/40/4059"}), 3500:({"/item/91/9111", "/item/41/4111"}), ])]),
			   "Kính Qủy Lương Quốc":(["kind":"无", "strong":"正常", "level":80, "rand":3, "weapon":"五雷", "spe":4, "droprate":([2000:({"/item/40/4034", "/item/40/4067"}), 2500:({"/item/stuff/0053", "/item/stuff/0130"}), ])]),
				  "Kính Qủy Lỗ Quốc":(["kind":"无", "strong":"正常", "level":85, "rand":3, "weapon":"五雷", "spe":4, "droprate":([2000:({"/item/40/4068"}), 2500:({"/item/stuff/0051"}), ])]),
			   "Kính Qủy Trịnh Quốc":(["kind":"无", "strong":"正常", "level":90, "rand":3, "weapon":"五雷", "spe":4, "droprate":([2000:({"/item/40/4034", "/item/40/4071", "/item/40/4060"}), 2500:({"/item/stuff/0130", "/item/stuff/0187"}), ])]),
				"Kính Qủy Việt Quốc":(["kind":"无", "strong":"正常", "level":95, "rand":3, "weapon":"五雷", "spe":4, "droprate":([2000:({"/item/40/4074"}), 2500:({"/item/stuff/0106", "/item/41/4111"}), ])]),
				 "Kính Qủy Ngô Quốc":(["kind":"无", "strong":"正常", "level":100, "rand":3, "weapon":"五雷", "spe":4, "droprate":([2000:({}), 2500:({"/item/91/9135", "/item/stuff/0176"}), ])]),
				 "Kính Qủy Tấn Quốc":(["kind":"无", "strong":"正常", "level":105, "rand":3, "weapon":"五雷", "spe":4, "droprate":([2000:({"/item/40/4075"}), 2500:({"/item/91/9140"}), ])]),
				  "Kính Qủy Ác Mộng":(["kind":"无", "strong":"强壮", "level":120, "rand":3, "weapon":"五雷", "spe":4, "droprate":([200:({"/item/test/pyktanthu"}), 300:({"/item/test/tuibikipnm"}), 2000:({"/item/40/4075"}), 2500:({"/item/91/9140"}), ])]),

]);
mapping mpBoss = ([35:(["file":"/npc/copy/0101", "attr":({"亡灵", "厉害", "空手"})]),
				   40:(["file":"/npc/copy/0102", "attr":({"亡灵", "厉害", "空手"})]),
				   45:(["file":"/npc/copy/0103", "attr":({"亡灵", "厉害", "五雷"})]),
				   50:(["file":"/npc/copy/0104", "attr":({"亡灵", "厉害", "空手"})]),
				   55:(["file":"/npc/copy/0105", "attr":({"亡灵", "厉害", "五雷"})]),
				   60:(["file":"/npc/copy/0106", "attr":({"亡灵", "厉害", "空手"})]),
				   65:(["file":"/npc/copy/0107", "attr":({"亡灵", "厉害", "空手"})]),
				   70:(["file":"/npc/copy/0108", "attr":({"亡灵", "厉害", "暗器"})]),
				   75:(["file":"/npc/copy/0109", "attr":({"亡灵", "厉害", "空手"})]),
				   80:(["file":"/npc/copy/0110", "attr":({"亡灵", "强壮", "暗器"})]),
				   85:(["file":"/npc/copy/0111", "attr":({"亡灵", "强壮", "空手"})]),
				   90:(["file":"/npc/copy/0112", "attr":({"亡灵", "强壮", "空手"})]),
				   95:(["file":"/npc/copy/0113", "attr":({"亡灵", "强壮", "空手"})]),
				  100:(["file":"/npc/copy/0114", "attr":({"亡灵", "强壮", "五雷"})]),
				  105:(["file":"/npc/copy/0115", "attr":({"亡灵", "强壮", "五雷"})]),
				  120:(["file":"/npc/copy/0115", "attr":({"亡灵", "残暴", "五雷"})]),
]);
mapping mpName = ([]);
int new_copy(object me, object who, int level);
int new_copy_npc(int tId, int z, int level, int amount);
int generate_copy_npc(int tId, int z, int level, string cKind);

// 函数:生成二进制码
void SAVE_BINARY() {}

void create()
{
	int i, size;
	string *nName;
	mapping mpTmp;

	nName = keys(mpNpc);
	for (i = 0, size = sizeof(nName); i < size; i++)
	{
		mpTmp = mpNpc[nName[i]];
		if (!mpName[mpTmp["level"]])
			mpName[mpTmp["level"]] = ([]);
		mpName[mpTmp["level"]][mpTmp["weapon"]] = nName[i];
	}
}

int new_copy_scene(object who, object me)
{
	int *nScene, i, size, d, *nXy, z, tId;
	object map, npc;

	tId = who->get_team_id();
	if (!tId)
		return 0;
	nScene = keys(mpScene);
	size = sizeof(nScene);
	d = nScene[random(size)];
	nXy = mpScene[d];
	z = COPY_CTROL->new_scene(d, "/map/copy/0001", "Chiến Quốc Trận");
	if (!z)
		return 0;
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return;
	TEAM_D->add_copy_scene(tId, COPY_MIRROR, map);

	npc = new (MIRROR_NPC1);
	i = map->get_client_id();
	nXy = mpScene[i];
	npc->add_to_scene(z, nXy[0], nXy[1], 3);
	map->set("exit", nXy);
	map->set("copy_id", tId);
	if (me->get("pykacmong"))
	{
		map->set("pykacmong", 1);
		me->delete ("pykacmong");
	}
	//tell_user(find_char("971"),"%d %d %d %d",map->get_id(),map->get_client_id(),nXy[0],nXy[1]);
	return z;
}

int accept_object(object me, object who, object item)
{
	int level, tId;
	mapping mpTmp;
	object map;

	if (!who->is_leader())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Ngươi nói muốn đi vào Phong Yêu Kính ? Hãy bảo đội trưởng của ngươi đưa cho ta trang bị, sau đó các ngươi có thẻ vào Phong Yêu Kính rồi !!\n" ESC "Rời khỏi");
		return -99;
	}
	if (who->get_level() < 35)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n Đẳng cấp của ngươi chưa đạt 35!\n" ESC "Hiểu"));
		return -99;
	}
	tId = who->get_team_id();
	if (!item->get_equip_type())
		return 0;

	level = item->get_level();
	if (level < 35)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Hãy đưa cho ta 1 trang bị lam kim cấp 35 trở lên mới có thẻ vào được !!  \n" ESC "Rời khỏi");
		return -99;
	}
	if (level > 85)
		level = 85;
	level += 20;
	if (level > who->get_level())
		level = who->get_level();

	if (item->get_item_color() == 3)
	{
		//PYK Ác Mộng
		// send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Không được dùng trang bị tử kim để đi Phòng Yêu Kinh!!\n" ESC "Ta hiểu rồi");
		// return -99;
		level = 120;
	}
	level = level / 5 * 5;
	if (!mapp(mpTmp = mpName[level]) || (item->get_item_color() != 1 && item->get_item_color() != 2 && item->get_item_color() != 3))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Trang bị này không đủ sức để mở của Phong Yêu Kính, ngươi hãy đưa cho ta 1 trang bị lam kim cấp 35 trở lên mới có thẻ vào được !!\n" ESC "Ta hiểu rồi");
		return -99;
	}

	map = TEAM_D->get_copy_scene(tId, COPY_MIRROR);
	if (map)
	{
		if (item->get_item_color() == 3)
		{

			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    Ta có thể đem trang bị này đốt đi, để làm chất xúc tác, ngươi muốn như vậy phải không ?\n" ESC HIR "Xác nhận tạo Phòng Yêu Kinh Ác Mộng\ntalk %x# accept.%x#\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
		}
		else
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    Ta có thể đem trang bị này đốt đi, để làm chất xúc tác, ngươi muốn như vậy phải không ?\n" ESC "Xác nhận\ntalk %x# accept.%x#\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
		}

		return -99;
	}
	if (item->get_item_color() == 3)
	{

		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    Sau khi đem trang bị này thêu đốt làm chất xúc tác thì có thể tiến vào Phong Yêu Kính, ngươi xác nhận muốn thêu phải không ?\n" ESC HIR "Đúng vậy, mở Phòng Yêu Kính Ác Mộng\ntalk %x# accept.%x#\n" ESC "Không phải, ta nhầm rồi", getoid(me), getoid(item)));
	}
	else
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    Sau khi đem trang bị này thêu đốt làm chất xúc tác thì có thể tiến vào Phong Yêu Kính, ngươi xác nhận muốn thêu phải không ?\n" ESC "Đúng vậy, ta muốn đi\ntalk %x# accept.%x#\n" ESC "Không phải, ta nhầm rồi", getoid(me), getoid(item)));
	}

	return -99;
}

void do_accept(object me, object who, string arg)
{
	int level, tId, i, size;
	mapping mpTmp;
	object item, map, *member, *tmp;

	if (!objectp(item = present(arg, who, 1, MAX_CARRY * 4)))
		return;
	if (!who->is_leader())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n Ngươi muốn vào Phong Yêu Kính , đội trưởng của Ngươi đại diện đem trang bị đưa cho ta, sau đó Ngươi trực tiếp nói với ta là muốn vào Phong Yêu Kính .\n" ESC "Rời khỏi");
		return;
	}
	tId = who->get_team_id();
	if (!item->get_equip_type() || !tId)
		return 0;
	level = item->get_level();
	if (level < 35)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n   Hãy đưa cho ta 1 trang bị lam kim cấp 35 trở lên mới có thẻ vào được !!  \n" ESC "Rời khỏi");
		return;
	}
	if (level > 85)
		level = 85;
	level += 20;
	if (level > who->get_level())
		level = who->get_level();
	level = level / 5 * 5;
	if (!mapp(mpTmp = mpName[level]) || (item->get_item_color() != 1 && item->get_item_color() != 2 && item->get_item_color() != 3))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Trang bị này không đủ sức để mở của Phong Yêu Kính, ngươi hãy đưa cho ta 1 trang bị lam kim cấp 35 trở lên mới có thẻ vào được !!\n" ESC "Ta hiểu rồi");
		return;
	}
	member = who->get_team();
	map = TEAM_D->get_copy_scene(tId, COPY_MIRROR);
	if (map) //消除旧的副本
	{
		tmp = ({});
		for (i = 0, size = sizeof(member); i < size; i++)
		{
			if (!member[i] || member[i] == who || distance_between(me, member[i]) > 30)
				continue;
			tmp += ({member[i]});
			send_user(member[i], "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    Đội trưởng của ngươi muốn mở Phong Yêu Kính, ngươi đồng ý không ?\n" ESC "Đồng ý\ntalk %x# query.1\n" ESC "Không đồng ý\ntalk %x# query.2", getoid(me), getoid(me)));
		}
		if (sizeof(tmp))
		{
			me->set_2(sprintf("%d.item", tId), arg);
			me->set_2(sprintf("%d.team", tId), tmp);
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Xin đợi thành viên khác trả lời\n");
			return;
		}
		else
			COPY_MAP->destruct_virtual_map(map, map->get_id());
	}
	if (item->get_item_color() == 3)
	{
		me->set("pykacmong", 1);
		level = 120;
	}
	item->remove_from_user();
	destruct(item);

	if (new_copy(me, who, level) != 1)
		return;
	send_user(member, "%c%c%d%s", 0x43, 7, 0, HIY "Đội nhóm các ngươi đã mở Phong Yêu Kính");
	send_user(member, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    Đội nhóm các ngươi đã mở Phong Yêu Kính, ngươi muốn lập tức tiến vào Phong Yêu Kính ??\n" ESC "Đúng vậy, ta muốn vào\ntalk %x# welcome.7#\n" ESC "Chút nữa rồi đi", getoid(me)));
}
//创建新副本
int new_copy(object me, object who, int level)
{
	int tId, z;
	mapping mpTmp;
	object map;

	tId = who->get_team_id();
	if (!tId)
		return 0;
	if (!mapp(mpTmp = mpName[level]))
		return 0;
	z = new_copy_scene(who, me);
	if (!z)
		return 0;
	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return 0;
	new_copy_npc(tId, z, level, 200);
	map->set("copy_npc_amount", 500);
	map->set("copy_level", level);
	return 1;
}
//生成副本怪
int new_copy_npc(int tId, int z, int level, int amount)
{
	int i, size, iShape, *nShape, rand, iLev, p, x, y, iAtt, iCast, count;
	object npc, map, *nObj = ({});
	string name, *attrib, *nKind, cKind;
	mapping mpTmp;

	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return 0;
	nKind = ({
		"空手",
		"暗器",
		"五雷",
	});
	foreach (cKind in nKind)
	{
		nShape = mpShap[cKind];
		iShape = nShape[random(sizeof(nShape))];
		name = mpName[level][cKind];
		mpTmp = mpNpc[name];
		if (!mapp(mpTmp))
			return 0;
		rand = mpTmp["rand"];
		attrib = ({mpTmp["kind"], mpTmp["strong"], mpTmp["weapon"]});
		// if (map->get("pykacmong"))
		// {
		// 	attrib = ({mpTmp["kind"], "强壮", mpTmp["weapon"]});
		// }
		iAtt = 0;
		iCast = 0;
		if (cKind == "空手")
			size = amount * 4 / 10;
		else if (cKind == "五雷")
		{
			iAtt = 1;
			iCast = 1;
			size = amount * 3 / 10;
		}
		else if (cKind == "暗器")
		{
			iAtt = 2;
			iCast = 1;
			size = amount * 3 / 10;
		}
		for (i = 0; i < size; i++)
		{
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				continue;
			x = (p % 1000000) / 1000;
			y = p % 1000;

			npc = new (MIRROR_NPC);
			npc->set("copy_type", cKind);
			npc->set_name(name);
			npc->set_char_picid(iShape);
			iLev = level + random(rand);
			npc->set_level(iLev);
			npc->set("team_id", tId);
			NPC_ENERGY_D->init_npc(npc, iLev, attrib);
			npc->set_char_type(FIGHTER_TYPE);
			npc->set_attack(iAtt);
			npc->set_caster(iCast);
			//npc->set_head_color(0x2);
			if (!map->get("pykacmong"))
			{
				npc->set_head_color(0x2);
			}
			//npc->set_head_color(0x6186);
			npc->add_to_scene(z, x, y);
			count++;
		}
	}
	map->add("scene_npc_amount", count);
}
//副本怪死亡处理
void npc_die(object npc, object who)
{
	int tId, z, i, size, rate, *nRate, p, x, y, count, j, level, rate1;
	object map, npc1, *nObj, item, *member;
	string name, *nFile, file;
	mapping mpTmp;

	tId = npc->get("team_id");
	name = npc->get_name();
	map = TEAM_D->get_copy_scene(tId, COPY_MIRROR);
	if (!map)
		return;
	map->add("copy_npc_die", 1);
	//出现新的怪
	if (map->get("scene_npc_amount") < map->get("copy_npc_amount") && npc->get("copy_type"))
	{
		generate_copy_npc(tId, map->get_id(), map->get("copy_level"), npc->get("copy_type"));
	}
	z = map->get_id();
	//BOSS出现
	if (!map->get("copy_boss") && (map->get("copy_npc_die") * 100 / map->get("copy_npc_amount") >= 85))
	{
		p = efun::get_xy_point(z, IS_CHAR_BLOCK);
		if (p)
		{
			level = map->get("copy_level");
			mpTmp = mpBoss[level];
			if (mapp(mpTmp))
			{
				npc1 = new (mpTmp["file"]);
				npc1->set("team_id", tId);

				NPC_ENERGY_D->init_npc(npc1, npc1->get_level(), mpTmp["attr"]);

				if (npc1->get_level() < 75)
					npc1->add_max_hp(npc1->get_max_hp() * 3);
				else
					npc1->add_max_hp(npc1->get_max_hp());
				npc1->add_to_scene(z, (p % 1000000) / 1000, p % 1000);
				member = who->get_team();
				member -= ({0});
				for (i = 0, size = sizeof(member); i < size; i++)
				{
					if (get_z(member[i]) != z)
						continue;
					send_user(member[i], "%c%s", ';', HIY "Bùm! Rầm! Rầm! Xung quanh đây dường như xuất hiện một con Yêu ma lớn.");
				}
				map->set("copy_boss", 1);
			}
		}
	}
	//大BOSS出现
	if (!map->get("big_copy_boss") && (map->get("copy_npc_die") == map->get("copy_npc_amount")))
	{
		p = efun::get_xy_point(z, IS_CHAR_BLOCK);
		if (p)
		{
			level = map->get("copy_level") + 5;
			rate = random(3);

			if (map->get("pykacmong"))
			{
				if (rate == 0)
					npc1 = new ("npc/boss/0017_2");
				else if (rate == 1)
					npc1 = new ("npc/boss/0018_2");
				if (rate == 2)
					npc1 = new ("npc/boss/0019_2");
			}
			else
			{
				if (rate == 0)
					npc1 = new ("npc/boss/0017");
				else if (rate == 1)
					npc1 = new ("npc/boss/0018");
				if (rate == 2)
					npc1 = new ("npc/boss/0019");
			}
			npc1->set("team_id", tId);
			npc1->set_fight_status(level);
			npc1->add_to_scene(z, (p % 1000000) / 1000, p % 1000);
			member = who->get_team();
			member -= ({0});
			for (i = 0, size = sizeof(member); i < size; i++)
			{
				if (get_z(member[i]) != z)
					continue;
				send_user(member[i], "%c%s", ';', sprintf(HIY "Thiên hư địa chuyển, Ta %s hôm nay lại xuống nhân gian, nhất định phải đại náo 1 trận !!", npc1->get_name()));
			}
			map->set("big_copy_boss", 1);
		}
	}
	x = get_x(npc);
	y = get_y(npc);
	if (tId != who->get_team_id())
		return;
	rate1 = npc->correct_drop_rate(npc->get_level() - who->get_level()) * who->get_online_rate() / 100;
	//	//掉干将宝石
	//	rate = random(1000);
	//	if ( "sys/sys/count"->get_new_story() && (rate1==100) && !rate && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	//	{
	//		item = new("item/08/0015");
	//		TEAM_D->drop_item(item,who);
	//		item->add_to_scene(z, p / 1000, p % 1000);
	//	}
	//掉物品
	mpTmp = mpNpc[name];
	if (!mpTmp || !(mpTmp = mpTmp["droprate"]))
		return;
	nRate = sort_array(keys(mpTmp), 0);
	p = random(100);
	count = (p > 2) ? 1 : (p > 0) ? 2
								  : 8;
	for (j = 0; j < count; j++)
	{
		p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
		if (!p)
			continue;
		rate = random(10000);
		for (i = 0, size = sizeof(nRate); i < size; i++)
		{
			if (rate >= nRate[i] * rate1 / 100)
				continue;
			nFile = mpTmp[nRate[i]];
			if (!sizeof(nFile))
				break;
			file = nFile[random(sizeof(nFile))];
			item = new (file);
			if (!item)
				break;
			TEAM_D->drop_item(item, who);
			item->add_to_scene(z, p / 1000, p % 1000);
			break;
		}
	}
}
//询问是否Đồng ý重置副本
void do_query(object me, object who, string arg)
{
	int tId, flag, level;
	object *tmp, leader, item, *member, map;
	string id;
	mapping mpTmp;

	if (!arg)
		return;
	tId = who->get_team_id();
	if (!tId)
		return;
	if (!arrayp(tmp = me->get_2(sprintf("%d.team", tId))))
		return;
	if (member_array(who, tmp) == -1)
		return;
	flag = to_int(arg);
	leader = find_char(who->get_leader());
	if (!leader)
		return;
	if (flag != 1)
	{
		me->delete_2(sprintf("%d", tId));
		send_user(leader, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    %s Không đồng ý tiến vào Phong Yêu Kính\n", who->get_name()));
		return;
	}
	tmp -= ({who});
	if (sizeof(tmp))
	{
		me->set_2(sprintf("%d.team", tId), tmp);
		return;
	}
	id = me->get_2(sprintf("%d.item", tId));
	me->delete_2(sprintf("%d", tId));
	if (!objectp(item = present(id, leader, 1, MAX_CARRY * 4)))
		return;
	if (!item->get_equip_type())
		return 0;
	level = item->get_level();
	if (level > 105)
		level = 105;

	if (item->get_item_color() == 3)
	{
		// PYK ác Mộng
		// send_user(leader, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Không được dùng trang bị tử kim để đi phòng yêu kính\n" ESC "Ta hiểu rồi");
		// return;
		level = 120;
	}
	level = level / 5 * 5;
	if (!mapp(mpTmp = mpName[level]) || (item->get_item_color() != 1 && item->get_item_color() != 2 && item->get_item_color() != 3))
	{
		send_user(leader, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tả Khâu Minh:\n    Trang bị của ngươi không đủ lực lượng để tiền vào Phong Yêu Kính, hãy đổi 1 trang bị lam kim cấp 35 trở lên !!\n" ESC "Ta hiểu rồi");
		return;
	}
	member = who->get_team();
	map = TEAM_D->get_copy_scene(tId, COPY_MIRROR);
	if (map) //消除旧的副本
	{
		COPY_MAP->destruct_virtual_map(map, map->get_id());
	}
	item->remove_from_user();
	destruct(item);

	if (new_copy(me, leader, level) != 1)
		return;
	send_user(member, "%c%c%d%s", 0x43, 7, 0, HIY "Đội nhóm các ngươi đã mở Phong Yêu Kính");
	send_user(member, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Tả Khâu Minh:\n    Đội nhóm các ngươi đã mở Phong Yêu Kính, ngươi muốn lập tức tiến vào Phong Yêu Kính ??\n" ESC "Đúng vậy, ta muốn vào\ntalk %x# welcome.7#\n" ESC "Chút nữa rồi đi", getoid(me)));
}
//生成一只副本怪
int generate_copy_npc(int tId, int z, int level, string cKind)
{
	int i, size, iShape, *nShape, rand, iLev, p, x, y, iAtt, iCast;
	object npc, map, *nObj = ({});
	string name, *attrib, *nKind;
	mapping mpTmp;

	if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
		return 0;
	nShape = mpShap[cKind];
	iShape = nShape[random(sizeof(nShape))];
	name = mpName[level][cKind];
	mpTmp = mpNpc[name];
	if (!mapp(mpTmp))
		return 0;
	rand = mpTmp["rand"];
	attrib = ({mpTmp["kind"], mpTmp["strong"], mpTmp["weapon"]});
	// if (map->get("pykacmong"))
	// {
	// 	attrib = ({mpTmp["kind"], "强壮", mpTmp["weapon"]});
	// }
	iAtt = 0;
	iCast = 0;
	if (cKind == "五雷")
	{
		iAtt = 1;
		iCast = 1;
	}
	else if (cKind == "暗器")
	{
		iAtt = 2;
		iCast = 1;
	}
	if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
		return 0;
	x = (p % 1000000) / 1000;
	y = p % 1000;
	npc = new (MIRROR_NPC);
	npc->set_name(name);
	npc->set_char_picid(iShape);
	iLev = level + random(rand);
	npc->set_level(iLev);
	npc->set("team_id", tId);
	NPC_ENERGY_D->init_npc(npc, iLev, attrib);
	npc->set_char_type(FIGHTER_TYPE);
	npc->set_attack(iAtt);
	npc->set_caster(iCast);

	if (!map->get("pykacmong"))
	{
		npc->set_head_color(0x2);
	}

	npc->add_to_scene(z, x, y);
	npc->set("copy_type", cKind);
	map->add("scene_npc_amount", 1);
	return 1;
}
//小BOSS掉神器材料
void drop_shenqi(object me, object who)
{
	int x, y, z, p, rate;
	object item;

	//	if ( !"sys/sys/count"->get_new_story() || random100() > 100 )
	if (!"sys/sys/count"->get_new_story() || random100() >= 10)
		return;
	rate = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
	//   if ( random100() > 100 )
	if (random100() >= rate)
		return;
	x = get_x(me);
	y = get_y(me);
	z = get_z(me);
	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
		return;
	item = new (sprintf("item/%d/1075", 70 + random(6)));
	if (!item)
		return;
	TEAM_D->drop_item(item, who);
	item->add_to_scene(z, p / 1000, p % 1000);
}