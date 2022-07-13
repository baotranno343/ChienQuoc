
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <effect.h>
#include <time.h>
string send_task_intro(object who, int iFlag, int iTask, int iKind);

mapping mpTaskList = (["Nhiệm Vụ Chỉ Dẫn":([1:({TASK_NEWBIE_00, 1, 2, TID_NEWBIE_00, "Sứ Mệnh Đưa Thư"})]),
						   "Tân Thủ Thôn":([3:({TASK_NEWBIE_01, 3, 4, TID_NEWBIE_01, "合作事宜"}),
												6:({TASK_NEWBIE_01, 10, 11, TID_NEWBIE_01, "探望病人"}),
												7:({TASK_NEWBIE_01, 12, 13, TID_NEWBIE_01, "飞鸽传书"}),
												9:({TASK_NEWBIE_01, 17, 18, TID_NEWBIE_01, "破损的铁锹"}),
											   10:({TASK_NEWBIE_01, 19, 20, TID_NEWBIE_01, "牛二报恩"}),
											   11:({TASK_NEWBIE_01, 21, 22, TID_NEWBIE_01, "牛二的苦恼"}),
											   12:({TASK_NEWBIE_01, 1, 2, TID_NEWBIE_01, "老村长的委托"}),
											   13:({TASK_NEWBIE_01, 23, 24, TID_NEWBIE_01, "锻炼的机会"}),
											   17:({TASK_NEWBIE_02, 10, 11, TID_NEWBIE_01, "找智慧老人谈谈"}),
											   18:({TASK_NEWBIE_02, 12, 13, TID_NEWBIE_01, "丢失的手镯"}),
											   23:({TASK_37, 13, 14, TID_NEWBIE_01, "门派向导的恩怨"}),
											   24:({TASK_40, 24, 25, TID_NEWBIE_01, "头疼的毛病(1)"}),
											   26:({TASK_40, 28, 29, TID_NEWBIE_01, "头疼的毛病(3)"}),
											   27:({TASK_41, 4, 5, TID_NEWBIE_01, "疑难杂症(1)"}),
											   29:({TASK_41, 9, 10, TID_NEWBIE_01, "疑难杂症(3)"}),
											   33:({TASK_41, 11, 12, TID_NEWBIE_01, "运箱子"}),
											   34:({TASK_40, 20, 21, TID_NEWBIE_01, "孤独"}),
											   35:({TASK_40, 22, 23, TID_NEWBIE_01, "食物的来源"}),
											  102:({TASK_48, 4, 5, TID_NEWBIE_01, "合作事宜"}),
											  103:({TASK_48, 6, 7, TID_NEWBIE_01, "Kinh Nghiệm Tìm Báu Vật"}),
											  105:({TASK_48, 11, 12, TID_NEWBIE_01, "探望病人"}),
											  106:({TASK_48, 13, 14, TID_NEWBIE_01, "飞鸽传书"}),
											  109:({TASK_48, 21, 22, TID_NEWBIE_01, "疑难杂症(1)"}),
											  111:({TASK_48, 26, 27, TID_NEWBIE_01, "疑难杂症(3)"}),
											  113:({TASK_49, 1, 2, TID_NEWBIE_01, "头疼的毛病(1)"}),
											  114:({TASK_49, 3, 4, TID_NEWBIE_01, "头疼的毛病(2)"}),
											  115:({TASK_49, 4, 5, TID_NEWBIE_01, "头疼的毛病(3)"}),
											  117:({TASK_49, 9, 10, TID_NEWBIE_01, "丢失的手镯"}),
											  118:({TASK_49, 11, 12, TID_NEWBIE_01, "门派向导的恩怨"}),
											  119:({TASK_2_00, 10, 11, TID_NEWBIE_01, "王捕头的美差"}),
]),
							   "Chu Quốc":([
											   //					1: ({TASK_NEWBIE_00,11,12,TID_ZHOUGUO,"王捕头的美差"}),
											   //					2: ({TASK_NEWBIE_00,13,14,TID_ZHOUGUO,"找尉迟老镖头谈谈"}),
											   3:({TASK_NEWBIE_00, 9, 10, TID_ZHOUGUO, "拜访师爷"}),
											   9:({TASK_40, 3, 4, TID_ZHOUGUO, "四面楚歌(5)"}),
											  10:({TASK_40, 5, 6, TID_ZHOUGUO, "Tù Và Lập Bang"}),
											  13:({TASK_40, 13, 14, TID_ZHOUGUO, "Thỉnh Cầu Vua Giúp Đỡ"}),
											  14:({TASK_40, 15, 16, TID_ZHOUGUO, "Chế tạo Tù Và Đế Vương"}),
											  15:({TASK_49, 13, 14, TID_ZHOUGUO, "一探虚实"}),
											  16:({TASK_2_00, 12, 13, TID_ZHOUGUO, "拜访师爷"}),
											  17:({TASK_2_00, 14, 15, TID_ZHOUGUO, "找尉迟老镖头谈谈"}),
											  18:({TASK_2_00, 16, 17, TID_ZHOUGUO, "拜访左丘明"}),
											  19:({TASK_2_00, 18, 19, TID_ZHOUGUO, "拜访周王"}),
											  22:({TASK_2_00, 26, 27, TID_ZHOUGUO, "给楚管家的口信"}),
]),
								"Sở Quốc":([9:({TASK_NEWBIE_03, 22, 23, TID_CHUGUO, "亡羊补牢(1)"}),
											  12:({TASK_07, 28, 29, TID_CHUGUO, "唤醒记忆"}),
											  31:({TASK_24, 15, 16, TID_CHUGUO, "茉莉花茶(4)"}),
											  32:({TASK_32, 29, 30, TID_CHUGUO, "祖父的遗产(2)"}),
											  42:({TASK_37, 15, 16, TID_CHUGUO, "收购珠宝"}),
											  43:({TASK_37, 17, 18, TID_CHUGUO, "韩总管的帮助"}),
											  44:({TASK_37, 25, 26, TID_CHUGUO, "带口信给齐国使节"}),
											  45:({TASK_38, 19, 20, TID_CHUGUO, "遗忘的佩剑"}),
											  46:({TASK_39, 7, 8, TID_CHUGUO, "交好"}),
]),
							   "Hàn Quốc":([3:({TASK_04, 7, 8, TID_HANGUO, "御史的烦恼"}),
											   4:({TASK_04, 9, 10, TID_HANGUO, "出使重任"}),
											   6:({TASK_04, 13, 14, TID_HANGUO, "户籍密件"}),
											   7:({TASK_04, 15, 16, TID_HANGUO, "神奇的彩衣"}),
											   8:({TASK_04, 17, 18, TID_HANGUO, "翡翠珠串"}),
											   9:({TASK_04, 19, 20, TID_HANGUO, "工匠的苦恼"}),
											  10:({TASK_04, 21, 22, TID_HANGUO, "工匠的愿望"}),
											  15:({TASK_04, 29, 30, TID_HANGUO, "将军之难"}),
											  16:({TASK_25, 4, 5, TID_HANGUO, "索取宝图"}),
											  18:({TASK_25, 9, 10, TID_HANGUO, "寻根问底"}),
											  21:({TASK_25, 17, 18, TID_HANGUO, "出谋献策"}),
											  24:({TASK_25, 25, 26, TID_HANGUO, "上奏韩王"}),
											  25:({TASK_25, 27, 28, TID_HANGUO, "与楚联盟"}),
											  26:({TASK_25, 29, 30, TID_HANGUO, "内政官的心事"}),
											  27:({TASK_26, 1, 2, TID_HANGUO, "寻求帮助"}),
											  28:({TASK_26, 3, 4, TID_HANGUO, "御史的建议"}),
											  29:({TASK_26, 5, 6, TID_HANGUO, "指明方向"}),
											  31:({TASK_26, 10, 11, TID_HANGUO, "商人哭诉"}),
											  32:({TASK_26, 12, 13, TID_HANGUO, "御史的担心"}),
											  35:({TASK_26, 20, 21, TID_HANGUO, "寻人避难"}),
											  36:({TASK_26, 22, 23, TID_HANGUO, "百姓的好心"}),
											  37:({TASK_26, 24, 25, TID_HANGUO, "乐师的无奈"}),
											  40:({TASK_26, 29, 30, TID_HANGUO, "上奏韩王"}),
											  45:({TASK_23, 4, 5, TID_HANGUO, "游魂(1)"}),
											  47:({TASK_23, 25, 26, TID_HANGUO, "武士的爱情(2)"}),
											  48:({TASK_37, 19, 20, TID_HANGUO, "崔大官人的请柬"}),
											  49:({TASK_38, 9, 10, TID_HANGUO, "助人为乐"}),
											  50:({TASK_38, 13, 14, TID_HANGUO, "身世之谜"}),
]),
							  "Ngụy Quốc":([5:({TASK_07, 4, 9, TID_WEIGUO, "去燕的盘缠"}),
											  36:({TASK_31, 16, 17, TID_WEIGUO, "秘密(1)"}),
											  37:({TASK_33, 25, 26, TID_WEIGUO, "打探消息"}),
											  41:({TASK_34, 7, 8, TID_WEIGUO, "魏国百姓"}),
											  42:({TASK_34, 9, 10, TID_WEIGUO, "了解情况"}),
											  45:({TASK_34, 17, 18, TID_WEIGUO, "官府备案"}),
											  46:({TASK_34, 19, 20, TID_WEIGUO, "奏请王命"}),
											  47:({TASK_34, 21, 22, TID_WEIGUO, "姻缘之路1"}),
											  48:({TASK_34, 23, 24, TID_WEIGUO, "姻缘之路2"}),
											  51:({TASK_35, 1, 2, TID_WEIGUO, "姻缘之路5"}),
											  52:({TASK_35, 3, 4, TID_WEIGUO, "探访奇事"}),
											  53:({TASK_35, 5, 6, TID_WEIGUO, "探访奇事"}),
											  56:({TASK_35, 13, 14, TID_WEIGUO, "解除奇事"}),
											  57:({TASK_35, 15, 16, TID_WEIGUO, "探明原因"}),
											  60:({TASK_35, 23, 24, TID_WEIGUO, "通报情况"}),
											  61:({TASK_35, 25, 26, TID_WEIGUO, "禀告魏王"}),
											  65:({TASK_37, 21, 22, TID_WEIGUO, "家庭聚会"}),
											  66:({TASK_37, 23, 24, TID_WEIGUO, "临终委托"}),
											  67:({TASK_38, 21, 22, TID_WEIGUO, "换份工作"}),
											  68:({TASK_39, 5, 6, TID_WEIGUO, "手巧的工匠"}),
]),
								"Tề Quốc":([1:({TASK_09, 19, 20, TID_QIGUO, "唇亡齿寒(1)"}),
											   2:({TASK_09, 21, 22, TID_QIGUO, "唇亡齿寒(2)"}),
											   4:({TASK_09, 26, 27, TID_QIGUO, "唇亡齿寒(4)"}),
											   8:({TASK_10, 1, 2, TID_QIGUO, "带信给管仲(3)"}),
											  10:({TASK_10, 6, 7, TID_QIGUO, "带话给程风(2)"}),
											  15:({TASK_24, 7, 8, TID_QIGUO, "茉莉花茶(1)"}),
											  25:({TASK_28, 29, 30, TID_QIGUO, "询问原因"}),
											  26:({TASK_29, 16, 17, TID_QIGUO, "打听消息"}),
											  28:({TASK_29, 21, 22, TID_QIGUO, "水落石出"}),
											  30:({TASK_29, 26, 27, TID_QIGUO, "探访将军"}),
											  31:({TASK_30, 1, 2, TID_QIGUO, "将军信函"}),
											  32:({TASK_30, 3, 4, TID_QIGUO, "民间探访"}),
											  35:({TASK_30, 8, 9, TID_QIGUO, "询查原因"}),
											  36:({TASK_30, 10, 11, TID_QIGUO, "明辨是非"}),
											  39:({TASK_30, 18, 19, TID_QIGUO, "驯服恶霸"}),
											  40:({TASK_30, 20, 21, TID_QIGUO, "深入民间"}),
											  41:({TASK_30, 22, 23, TID_QIGUO, "商人诉苦"}),
											  44:({TASK_24, 29, 30, TID_QIGUO, "禀告齐王"}),
											  45:({TASK_31, 1, 2, TID_QIGUO, "询问小贩"}),
											  48:({TASK_31, 9, 10, TID_QIGUO, "告知内政官"}),
											  49:({TASK_31, 11, 12, TID_QIGUO, "通告百姓"}),
											  61:({TASK_36, 29, 30, TID_QIGUO, "肖独贵(2)"}),
											  63:({TASK_40, 1, 2, TID_QIGUO, "四面楚歌(3)"}),
											  65:({TASK_44, 16, 17, TID_QIGUO, "热心的建议(2)"}),
											  71:({
													 TASK_45,
													 13,
													 14,
													 TID_QIGUO,
													 "无上的荣耀(3)",
												 }),
											  72:({TASK_37, 27, 28, TID_QIGUO, "种庄稼的锄头"}),
											  73:({TASK_37, 29, 30, TID_QIGUO, "交换心得"}),
											  74:({TASK_38, 11, 12, TID_QIGUO, "答谢"}),
											  75:({TASK_38, 17, 18, TID_QIGUO, "询问价格"}),
											  76:({TASK_38, 23, 24, TID_QIGUO, "讨好"}),
											  77:({TASK_38, 25, 26, TID_QIGUO, "挑战"}),
]),
							   "Tần Quốc":([4:({TASK_11, 4, 5, TID_QINGUO, "情锁秦宫(2)"}),
											   6:({TASK_11, 9, 10, TID_QINGUO, "情锁秦宫(4)"}),
											   8:({TASK_10, 29, 30, TID_QINGUO, "兄弟情深"}),
											   9:({TASK_18, 28, 29, TID_QINGUO, "贺礼"}),
											  10:({TASK_19, 5, 6, TID_QINGUO, "大葫芦(3)"}),
											  12:({TASK_18, 19, 20, TID_QINGUO, "大展神威(2)"}),
											  13:({TASK_18, 20, 21, TID_QINGUO, "大展神威(3)"}),
											  22:({TASK_19, 22, 23, TID_QINGUO, "追捕逃犯"}),
											  23:({TASK_20, 19, 20, TID_QINGUO, "探听虚实"}),
											  27:({TASK_21, 1, 2, TID_QINGUO, "破土动工"}),
											  28:({TASK_21, 3, 4, TID_QINGUO, "打听消息"}),
											  30:({TASK_21, 8, 9, TID_QINGUO, "降旨修墓"}),
											  32:({TASK_21, 13, 14, TID_QINGUO, "寻求支持"}),
											  33:({TASK_21, 15, 16, TID_QINGUO, "准备出使"}),
											  35:({TASK_21, 20, 21, TID_QINGUO, "出使信函"}),
											  36:({TASK_21, 22, 23, TID_QINGUO, "面见赵王"}),
											  37:({TASK_21, 24, 25, TID_QINGUO, "回奏秦王"}),
											  38:({TASK_21, 26, 27, TID_QINGUO, "秦将辟谣"}),
											  40:({TASK_22, 1, 2, TID_QINGUO, "陈述冤情"}),
											  41:({TASK_22, 3, 4, TID_QINGUO, "明辨是非"}),
											  43:({TASK_22, 8, 9, TID_QINGUO, "道听途说"}),
											  46:({TASK_22, 16, 17, TID_QINGUO, "劝谏秦王"}),
											  51:({TASK_20, 13, 14, TID_QINGUO, "重阳节(2)"}),
											  52:({TASK_20, 14, 15, TID_QINGUO, "重阳节(3)"}),
											  54:({TASK_19, 1, 2, TID_QINGUO, "大葫芦(1)"}),
											  64:({TASK_46, 1, 2, TID_QINGUO, "刀魂传说1"}),
											  66:({TASK_46, 6, 7, TID_QINGUO, "刀魂传说3"}),
											  68:({TASK_46, 11, 12, TID_QINGUO, "刀魂传说5"}),
											  69:({TASK_46, 13, 14, TID_QINGUO, "平阳之乱1"}),
											  73:({TASK_46, 24, 25, TID_QINGUO, "平阳之乱5"}),
											  74:({TASK_46, 26, 27, TID_QINGUO, "炼药之路1"}),
											  76:({TASK_47, 1, 2, TID_QINGUO, "炼药之路3"}),
											  78:({TASK_47, 6, 7, TID_QINGUO, "炼药之路5"}),
											  79:({TASK_47, 8, 9, TID_QINGUO, "破除谣言1"}),
											  80:({TASK_47, 10, 11, TID_QINGUO, "破除谣言2"}),
											  82:({TASK_47, 15, 16, TID_QINGUO, "破除谣言4"}),
											  83:({TASK_47, 17, 18, TID_QINGUO, "破除谣言5"}),
											  84:({TASK_47, 19, 20, TID_QINGUO, "索取神剑1"}),
											  85:({TASK_47, 21, 22, TID_QINGUO, "索取神剑2"}),
											  88:({TASK_47, 29, 30, TID_QINGUO, "索取神剑5"}),
											  89:({TASK_36, 9, 10, TID_QINGUO, "完美宝石(4)"}),
											  90:({TASK_38, 1, 2, TID_QINGUO, "紫葡萄"}),
											  91:({TASK_38, 7, 8, TID_QINGUO, "韩总管的托付"}),
											  92:({TASK_38, 27, 28, TID_QINGUO, "恩怨"}),
											  93:({TASK_39, 1, 2, TID_QINGUO, "求份差事"}),
											  94:({TASK_39, 3, 4, TID_QINGUO, "嘱托之事"}),
]),
							   "Yên Quốc":([17:({TASK_11, 14, 15, TID_YANGUO, "无奈的求助(1)"}),
											  27:({TASK_14, 13, 14, TID_YANGUO, "浑仪(3)"}),
											  30:({TASK_15, 7, 8, TID_YANGUO, "Căn bệnh của Phu Nhân(1)"}),
											  35:({TASK_16, 1, 2, TID_YANGUO, "合伙做生意"}),
											  38:({TASK_27, 14, 15, TID_YANGUO, "燕王爱珍玩(3)"}),
											  54:({TASK_38, 3, 4, TID_YANGUO, "丢失的夜明珠"}),
]),
							 "Triệu Quốc":([3:({
												  TASK_11,
												  22,
												  23,
												  TID_ZHAOGUO,
												  "无奈的求助(4)",
											  }),
											   8:({
													 TASK_16,
													 6,
													 7,
													 TID_ZHAOGUO,
													 "出使秦国",
												 }),
											  36:({
													 TASK_19,
													 24,
													 25,
													 TID_ZHAOGUO,
													 "赵姬",
												 }),
											  38:({
													 TASK_19,
													 29,
													 30,
													 TID_ZHAOGUO,
													 "宝剑",
												 }),
											  42:({
													 TASK_27,
													 10,
													 11,
													 TID_ZHAOGUO,
													 "燕王好珍玩(1)",
												 }),
											  48:({
													 TASK_28,
													 10,
													 11,
													 TID_ZHAOGUO,
													 "木箱的秘密(2)",
												 }),
											  49:({
													 TASK_28,
													 12,
													 13,
													 TID_ZHAOGUO,
													 "木箱的秘密(3)",
												 }),
											  54:({
													 TASK_32,
													 4,
													 5,
													 TID_ZHAOGUO,
													 "使节的差事(1)",
												 }),
											  56:({
													 TASK_32,
													 9,
													 10,
													 TID_ZHAOGUO,
													 "论语",
												 }),
											  57:({
													 TASK_36,
													 1,
													 2,
													 TID_ZHAOGUO,
													 "完美宝石(1)",
												 }),
											  58:({
													 TASK_39,
													 23,
													 24,
													 TID_ZHAOGUO,
													 "四面楚歌(1)",
												 }),
											  61:({
													 TASK_45,
													 21,
													 22,
													 TID_ZHAOGUO,
													 "求医(2)",
												 }),
											  64:({
													 TASK_38,
													 5,
													 6,
													 TID_ZHAOGUO,
													 "打造武器",
												 }),
											  65:({
													 TASK_38,
													 15,
													 16,
													 TID_ZHAOGUO,
													 "弟弟的问候",
												 }),
											  66:({
													 TASK_38,
													 29,
													 30,
													 TID_ZHAOGUO,
													 "挖掘人才",
												 }),
											  67:({
													 TASK_39,
													 9,
													 10,
													 TID_ZHAOGUO,
													 "心愿",
												 }),
											  68:({
													 TASK_41,
													 16,
													 17,
													 TID_ZHAOGUO,
													 "询问原由",
												 }),
											  69:({
													 TASK_41,
													 18,
													 19,
													 TID_ZHAOGUO,
													 "打探下落",
												 }),
											  72:({
													 TASK_41,
													 26,
													 27,
													 TID_ZHAOGUO,
													 "上奏赵王",
												 }),
											  73:({
													 TASK_42,
													 1,
													 2,
													 TID_ZHAOGUO,
													 "询问消息",
												 }),
											  74:({
													 TASK_42,
													 3,
													 4,
													 TID_ZHAOGUO,
													 "询问战果",
												 }),
											  75:({
													 TASK_42,
													 5,
													 6,
													 TID_ZHAOGUO,
													 "询查战报",
												 }),
											  78:({
													 TASK_42,
													 10,
													 11,
													 TID_ZHAOGUO,
													 "询查原因",
												 }),
											  82:({
													 TASK_42,
													 21,
													 22,
													 TID_ZHAOGUO,
													 "禀报赵王",
												 }),
											  83:({
													 TASK_42,
													 23,
													 24,
													 TID_ZHAOGUO,
													 "探访民情",
												 }),
											  85:({
													 TASK_43,
													 1,
													 2,
													 TID_ZHAOGUO,
													 "陈述实情",
												 }),
											  87:({
													 TASK_43,
													 3,
													 4,
													 TID_ZHAOGUO,
													 "施行仁政",
												 }),
											  88:({
													 TASK_43,
													 5,
													 6,
													 TID_ZHAOGUO,
													 "询察起因",
												 }),
											  89:({
													 TASK_43,
													 7,
													 8,
													 TID_ZHAOGUO,
													 "查访知情人",
												 }),
											  92:({
													 TASK_43,
													 14,
													 16,
													 TID_ZHAOGUO,
													 "Hoàn thành使命",
												 }),
]),
								"Mao Sơn":([1:({
												  TASK_23,
												  6,
												  7,
												  TID_MAOSHAN,
												  "游魂(2)",
											  }),
											  6:({
													TASK_23,
													20,
													21,
													TID_MAOSHAN,
													"游魂(7)",
												}),
]),
						   "Vân Mộng Cốc":([3:({
												  TASK_45,
												  29,
												  30,
												  TID_YUNMENZE,
												  "求医(5)",
											  }),
]),
]);

mapping mpTaskList1 = (["Sở Quốc":([11:({TASK_07, 25, 26, 27, TID_CHUGUO, "三片羽毛", "三片羽毛(Hoàn thành)"}),
									  13:({TASK_08, 1, 2, 3, TID_CHUGUO, "守卫的衣服", "守卫的衣服(Hoàn thành)"}),
									  14:({TASK_08, 4, 5, 6, TID_CHUGUO, "山谷解迷", "山谷解迷(Hoàn thành)"}),
									  15:({TASK_08, 7, 8, 9, TID_CHUGUO, "沼泽寻宝", "沼泽寻宝(Hoàn thành)"}),
									  16:({TASK_08, 10, 11, 12, TID_CHUGUO, "沼泽惊魂", "沼泽惊魂(Hoàn thành)"}),
									  17:({TASK_08, 13, 14, 15, TID_CHUGUO, "湖泊奇闻", "湖泊奇闻(Hoàn thành)"}),
									  18:({TASK_08, 16, 17, 18, TID_CHUGUO, "龙骨坡的灵光", "龙骨坡的灵光(Hoàn thành)"}),
									  19:({TASK_08, 19, 20, 21, TID_CHUGUO, "迷途知返", "迷途知返(Hoàn thành)"}),
									  20:({TASK_08, 22, 23, 24, TID_CHUGUO, "苍梧道的迷魂", "苍梧道的迷魂(Hoàn thành)"}),
									  21:({TASK_08, 25, 26, 27, TID_CHUGUO, "湘妃林的鬼火", "湘妃林的鬼火(Hoàn thành)"}),
									  22:({TASK_08, 28, 29, 30, TID_CHUGUO, "九道谷里的宝物", "九道谷里的宝物(Hoàn thành)"}),
									  23:({TASK_09, 1, 2, 3, TID_CHUGUO, "大孤山脚里的哭声", "大孤山脚里的哭声(Hoàn thành)"}),
									  24:({TASK_09, 4, 5, 6, TID_CHUGUO, "湖口村的悬案", "湖口村的悬案(Hoàn thành)"}),
									  25:({TASK_09, 7, 8, 9, TID_CHUGUO, "珠丘的秘密", "珠丘的秘密(Hoàn thành)"}),
									  26:({TASK_09, 10, 11, 12, TID_CHUGUO, "湖口村的血迹", "湖口村的血迹(Hoàn thành)"}),
									  27:({TASK_09, 13, 14, 15, TID_CHUGUO, "龙骨坡的遗骸", "龙骨坡的遗骸(Hoàn thành)"}),
									  28:({TASK_09, 16, 17, 18, TID_CHUGUO, "山道里的鬼火", "山道里的鬼火(Hoàn thành)"}),
									  29:({TASK_24, 9, 10, 11, TID_CHUGUO, "茉莉花茶(2)", "茉莉花茶(2)(Hoàn thành)"}),
									  30:({TASK_24, 12, 13, 14, TID_CHUGUO, "茉莉花茶(3)", "茉莉花茶(3)(Hoàn thành)"}),
									  33:({TASK_33, 1, 2, 3, TID_CHUGUO, "祖父的遗产(3)", "祖父的遗产(3)(Hoàn thành)"}),
									  34:({TASK_33, 4, 5, 6, TID_CHUGUO, "祖父的遗产(4)", "祖父的遗产(4)(Hoàn thành)"}),
									  35:({TASK_33, 7, 8, 9, TID_CHUGUO, "多管闲事", "多管闲事(Hoàn thành)"}),
									  36:({TASK_33, 10, 11, 12, TID_CHUGUO, "铁观音茶", "铁观音茶(Hoàn thành)"}),
									  37:({TASK_33, 13, 14, 15, TID_CHUGUO, "玫瑰花", "玫瑰花(Hoàn thành)"}),
									  38:({TASK_33, 16, 17, 18, TID_CHUGUO, "惩戒梁少", "惩戒梁少(Hoàn thành)"}),
									  39:({TASK_33, 19, 20, 21, TID_CHUGUO, "保持距离", "保持距离(Hoàn thành)"}),
									  40:({TASK_33, 22, 23, 24, TID_CHUGUO, "源起于食物", "源起于食物(Hoàn thành)"}),
									  41:({TASK_45, 15, 16, 17, TID_CHUGUO, "万众敬仰", "万众敬仰(Hoàn thành)"}),
]),
					   "Hàn Quốc":([1:({TASK_04, 1, 2, 3, TID_HANGUO, "失窃的库银", "失窃的库银(Hoàn thành)"}),
										2:({TASK_04, 4, 5, 6, TID_HANGUO, "内政官的烦恼", "内政官的烦恼(Hoàn thành)"}),
									   11:({TASK_04, 23, 24, 25, TID_HANGUO, "惩恶扬善", "惩恶扬善(Hoàn thành)"}),
									   12:({TASK_04, 26, 27, 28, TID_HANGUO, "追捕重犯", "追捕重犯(Hoàn thành)"}),
									   13:({TASK_05, 1, 2, 3, TID_HANGUO, "解救工匠", "解救工匠(Hoàn thành)"}),
									   14:({TASK_05, 4, 5, 6, TID_HANGUO, "明正刑典", "明正刑典(Hoàn thành)"}),
									   17:({TASK_25, 6, 7, 8, TID_HANGUO, "清除威胁", "清除威胁(Hoàn thành)"}),
									   19:({TASK_25, 11, 12, 13, TID_HANGUO, "证明自己", "证明自己(Hoàn thành)"}),
									   20:({TASK_25, 14, 15, 16, TID_HANGUO, "揭开宝藏之迷", "揭开宝藏之迷(Hoàn thành)"}),
									   22:({TASK_25, 19, 20, 21, TID_HANGUO, "挑战自己", "挑战自己(Hoàn thành)"}),
									   23:({TASK_25, 22, 23, 24, TID_HANGUO, "清除奸贼", "清除奸贼(Hoàn thành)"}),
									   30:({TASK_26, 7, 8, 9, TID_HANGUO, "最后的考验", "最后的考验(Hoàn thành)"}),
									   33:({TASK_26, 14, 15, 16, TID_HANGUO, "试探实力", "试探实力(Hoàn thành)"}),
									   34:({TASK_26, 17, 18, 19, TID_HANGUO, "为民除害", "为民除害(Hoàn thành)"}),
									   38:({TASK_26, 26, 27, 28, TID_HANGUO, "寻求方法", "寻求方法(Hoàn thành)"}),
									   39:({TASK_27, 1, 2, 3, TID_HANGUO, "防止泄密", "防止泄密(Hoàn thành)"}),
									   41:({TASK_22, 21, 22, 23, TID_HANGUO, "烹鱼的佐料", "烹鱼的佐料(Hoàn thành)"}),
									   42:({TASK_22, 24, 25, 26, TID_HANGUO, "金钩桂饵", "金钩桂饵(Hoàn thành)"}),
									   43:({TASK_22, 27, 28, 29, TID_HANGUO, "害人的水鬼", "害人的水鬼(Hoàn thành)"}),
									   44:({TASK_23, 1, 2, 3, TID_HANGUO, "泄密之灾", "泄密之灾(Hoàn thành)"}),
									   46:({TASK_23, 22, 23, 24, TID_HANGUO, "武士的爱情(1)", "武士的爱情(1)(Hoàn thành)"}),
									  101:({TASK_2_01, 7, 8, 9, TID_HANGUO, "千里寻亲", "千里寻亲(Hoàn thành)"}),
]),
					  "Ngụy Quốc":([1:({TASK_06, 22, 23, 24, TID_WEIGUO, "纱纤小姐的发绳", "纱纤小姐的发绳(Hoàn thành)"}),
									   2:({TASK_06, 25, 26, 27, TID_WEIGUO, "罪恶的土匪", "罪恶的土匪(Hoàn thành)"}),
									   3:({TASK_06, 28, 29, 30, TID_WEIGUO, "偷鸡贼", "偷鸡贼(Hoàn thành)"}),
									   4:({TASK_07, 1, 2, 3, TID_WEIGUO, "送给丁兄的酒", "送给丁兄的酒(Hoàn thành)"}),
									   6:({TASK_07, 6, 7, 8, TID_WEIGUO, "换盘缠的芍药", "换盘缠的芍药(Hoàn thành)"}),
									   7:({TASK_07, 10, 11, 12, TID_WEIGUO, "梦的困扰", "梦的困扰(Hoàn thành)"}),
									   8:({TASK_07, 13, 14, 15, TID_WEIGUO, "魏管家的劫难(1)", "魏管家的劫难(1)(Hoàn thành)"}),
									   9:({TASK_07, 16, 17, 18, TID_WEIGUO, "魏管家的劫难(2)", "魏管家的劫难(2)(Hoàn thành)"}),
									  10:({TASK_07, 19, 20, 21, TID_WEIGUO, "魏管家的劫难(3)", "魏管家的劫难(3)(Hoàn thành)"}),
									  11:({TASK_05, 10, 11, 12, TID_WEIGUO, "锻造之路", "锻造之路(Hoàn thành)"}),
									  12:({TASK_05, 13, 14, 15, TID_WEIGUO, "神秘的传说", "神秘的传说(Hoàn thành)"}),
									  13:({TASK_05, 7, 8, 9, TID_WEIGUO, "招摇撞骗", "招摇撞骗(Hoàn thành)"}),
									  14:({TASK_05, 16, 17, 18, TID_WEIGUO, "英雄的磨练", "英雄的磨练(Hoàn thành)"}),
									  15:({TASK_05, 19, 20, 21, TID_WEIGUO, "裁缝的梦想", "裁缝的梦想(Hoàn thành)"}),
									  16:({TASK_05, 22, 23, 24, TID_WEIGUO, "沉默的剑魂", "沉默的剑魂(Hoàn thành)"}),
									  17:({TASK_05, 25, 26, 27, TID_WEIGUO, "遗忘的誓言", "遗忘的誓言(Hoàn thành)"}),
									  18:({TASK_05, 28, 29, 30, TID_WEIGUO, "传闻的宝藏", "传闻的宝藏(Hoàn thành)"}),
									  19:({TASK_06, 1, 2, 3, TID_WEIGUO, "哭泣的冤魂", "哭泣的冤魂(Hoàn thành)"}),
									  20:({TASK_06, 4, 5, 6, TID_WEIGUO, "狂妄的匪徒", "狂妄的匪徒(Hoàn thành)"}),
									  21:({TASK_06, 7, 8, 9, TID_WEIGUO, "英雄梦", "英雄梦(Hoàn thành)"}),
									  22:({TASK_06, 10, 11, 12, TID_WEIGUO, "遥远的梦想", "遥远的梦想(Hoàn thành)"}),
									  23:({TASK_06, 13, 14, 15, TID_WEIGUO, "巨鹿传说", "巨鹿传说(Hoàn thành)"}),
									  24:({TASK_06, 16, 17, 18, TID_WEIGUO, "山谷里的回音", "山谷里的回音(Hoàn thành)"}),
									  25:({TASK_06, 19, 20, 21, TID_WEIGUO, "神灵的怨恨", "神灵的怨恨(Hoàn thành)"}),
									  26:({TASK_07, 22, 23, 24, TID_WEIGUO, "挑剔的晚餐", "挑剔的晚餐(Hoàn thành)"}),
									  27:({TASK_19, 3, 4, 5, TID_WEIGUO, "大葫芦(2)", "大葫芦(2)(Hoàn thành)"}),
									  29:({TASK_24, 1, 2, 3, TID_WEIGUO, "武士的爱情(4)", "武士的爱情(4)(Hoàn thành)"}),
									  30:({TASK_28, 23, 24, 25, TID_WEIGUO, "古墓里的玉", "古墓里的玉(Hoàn thành)"}),
									  31:({TASK_29, 4, 5, 6, TID_WEIGUO, "救人于危难", "救人于危难(Hoàn thành)"}),
									  32:({TASK_29, 7, 8, 9, TID_WEIGUO, "石狮", "石狮(Hoàn thành)"}),
									  33:({TASK_29, 10, 11, 12, TID_WEIGUO, "绑匪的条件", "绑匪的条件(Hoàn thành)"}),
									  34:({TASK_29, 13, 14, 15, TID_WEIGUO, "成为守卫的条件", "成为守卫的条件(Hoàn thành)"}),
									  35:({TASK_31, 13, 14, 15, TID_WEIGUO, "通缉犯", "通缉犯(Hoàn thành)"}),
									  38:({TASK_33, 27, 28, 29, TID_WEIGUO, "证明实力", "证明实力(Hoàn thành)"}),
									  39:({TASK_34, 1, 2, 3, TID_WEIGUO, "接受请求", "接受请求(Hoàn thành)"}),
									  40:({TASK_34, 4, 5, 6, TID_WEIGUO, "Kinh Nghiệm Tìm Báu Vật", "Kinh Nghiệm Tìm Báu Vật (Hoàn thành)"}),
									  43:({TASK_34, 11, 12, 13, TID_WEIGUO, "证实自己", "证实自己(Hoàn thành)"}),
									  44:({TASK_34, 14, 15, 16, TID_WEIGUO, "除掉骗子", "除掉骗子(Hoàn thành)"}),
									  49:({TASK_34, 25, 26, 27, TID_WEIGUO, "姻缘之路3", "姻缘之路3(Hoàn thành)"}),
									  50:({TASK_34, 28, 29, 30, TID_WEIGUO, "姻缘之路4", "姻缘之路4(Hoàn thành)"}),
									  54:({TASK_35, 7, 8, 9, TID_WEIGUO, "试练身手", "试练身手(Hoàn thành)"}),
									  55:({TASK_35, 10, 11, 12, TID_WEIGUO, "追杀贼匪", "追杀贼匪(Hoàn thành)"}),
									  58:({TASK_35, 17, 18, 19, TID_WEIGUO, "勇闯虚陵洞", "勇闯虚陵洞(Hoàn thành)"}),
									  59:({TASK_35, 20, 21, 22, TID_WEIGUO, "铲除祸源", "铲除祸源(Hoàn thành)"}),
									  62:({TASK_44, 4, 5, 6, TID_WEIGUO, "漂亮的床(1)", "漂亮的床(1)(Hoàn thành)"}),
									  63:({TASK_44, 7, 8, 9, TID_WEIGUO, "漂亮的床(2)", "漂亮的床(2)(Hoàn thành)"}),
									  64:({TASK_44, 10, 11, 12, TID_WEIGUO, "漂亮的床(3)", "漂亮的床(3)(Hoàn thành)"}),
]),
						"Tề Quốc":([3:({TASK_09, 23, 24, 25, TID_QIGUO, "唇亡齿寒(3)", "唇亡齿寒(3)(Hoàn thành)"}),
										5:({TASK_09, 28, 29, 30, TID_QIGUO, "欺诈的天罚", "欺诈的天罚(Hoàn thành)"}),
										6:({TASK_13, 16, 17, 18, TID_QIGUO, "Gian Tế Sơn Nhung Tộc (1)", "Gian Tế Sơn Nhung Tộc (1)(Hoàn thành)"}),
										7:({TASK_13, 19, 20, 21, TID_QIGUO, "孤竹族使节(2)", "孤竹族使节(2)(Hoàn thành)"}),
										9:({TASK_10, 3, 4, 5, TID_QIGUO, "索取菜种(1)", "索取菜种(1)(Hoàn thành)"}),
									   11:({TASK_10, 8, 9, 10, TID_QIGUO, "丢失的黑棋子", "丢失的黑棋子(Hoàn thành)"}),
									   12:({TASK_10, 11, 12, 13, TID_QIGUO, "商人的生意经", "商人的生意经(Hoàn thành)"}),
									   14:({TASK_24, 4, 5, 6, TID_QIGUO, "罐中妖", "罐中妖(Hoàn thành)"}),
									   16:({TASK_24, 17, 18, 19, TID_QIGUO, "搜寻官印", "搜寻官印(Hoàn thành)"}),
									   17:({TASK_24, 20, 21, 22, TID_QIGUO, "该死的冤魂", "该死的冤魂(Hoàn thành)"}),
									   18:({TASK_24, 23, 24, 25, TID_QIGUO, "有备无患", "有备无患(Hoàn thành)"}),
									   19:({TASK_24, 26, 27, 28, TID_QIGUO, "可怕的发现", "可怕的发现(Hoàn thành)"}),
									   20:({TASK_25, 1, 2, 3, TID_QIGUO, "决定性的打击", "决定性的打击(Hoàn thành)"}),
									   21:({TASK_27, 4, 5, 6, TID_QIGUO, "侍卫亡灵", "侍卫亡灵(Hoàn thành)"}),
									   22:({TASK_27, 19, 20, 21, TID_QIGUO, "灵谷洞之旅", "灵谷洞之旅(Hoàn thành)"}),
									   23:({TASK_27, 22, 23, 24, TID_QIGUO, "悔恨的守卫", "悔恨的守卫(Hoàn thành)"}),
									   24:({TASK_27, 25, 26, 27, TID_QIGUO, "拭目以待", "拭目以待(Hoàn thành)"}),
									   27:({TASK_29, 18, 19, 20, TID_QIGUO, "接受考验", "接受考验(Hoàn thành)"}),
									   29:({TASK_29, 23, 24, 25, TID_QIGUO, "寻找宝物", "寻找宝物(Hoàn thành)"}),
									   33:({TASK_29, 28, 29, 30, TID_QIGUO, "考验自己", "考验自己(Hoàn thành)"}),
									   34:({TASK_30, 5, 6, 7, TID_QIGUO, "失而复得", "失而复得(Hoàn thành)"}),
									   37:({TASK_30, 12, 13, 14, TID_QIGUO, "威慑对手", "威慑对手(Hoàn thành)"}),
									   38:({TASK_30, 15, 16, 17, TID_QIGUO, "铲除祸害", "铲除祸害(Hoàn thành)"}),
									   42:({TASK_30, 24, 25, 26, TID_QIGUO, "独闯古墓", "独闯古墓(Hoàn thành)"}),
									   43:({TASK_30, 27, 28, 29, TID_QIGUO, "除掉恶匪", "除掉恶匪(Hoàn thành)"}),
									   46:({TASK_31, 3, 4, 5, TID_QIGUO, "解除疑惑", "解除疑惑(Hoàn thành)"}),
									   47:({TASK_31, 6, 7, 8, TID_QIGUO, "除掉恶霸", "除掉恶霸(Hoàn thành)"}),
									   50:({TASK_35, 27, 28, 29, TID_QIGUO, "罐中妖与罐中仙", "罐中妖与罐中仙(Hoàn thành)"}),
									   51:({TASK_36, 3, 4, 5, TID_QIGUO, "完美宝石(2)", "完美宝石(2)(Hoàn thành)"}),
									   52:({TASK_36, 6, 7, 8, TID_QIGUO, "完美宝石(3)", "完美宝石(3)(Hoàn thành)"}),
									   53:({TASK_36, 11, 12, 13, TID_QIGUO, "临危不惧", "临危不惧(Hoàn thành)"}),
									   54:({TASK_36, 14, 15, 16, TID_QIGUO, "瘟疫之灾", "瘟疫之灾(Hoàn thành)"}),
									   55:({TASK_36, 17, 18, 19, TID_QIGUO, "涅磐", "涅磐(Hoàn thành)"}),
									   56:({TASK_36, 20, 21, 22, TID_QIGUO, "远征", "远征(Hoàn thành)"}),
									   57:({TASK_36, 23, 24, 25, TID_QIGUO, "叛徒", "叛徒(Hoàn thành)"}),
									   58:({TASK_36, 26, 27, 28, TID_QIGUO, "大齐的崛起", "大齐的崛起(Hoàn thành)"}),
									   59:({TASK_37, 1, 2, 3, TID_QIGUO, "攻破天门阵", "攻破天门阵(Hoàn thành)"}),
									   60:({TASK_37, 4, 5, 6, TID_QIGUO, "肖独贵(1)", "肖独贵(1)(Hoàn thành)"}),
									   62:({TASK_39, 25, 26, 27, TID_QIGUO, "四面楚歌(2)", "四面楚歌(2)(Hoàn thành)"}),
									   64:({TASK_44, 13, 14, 15, TID_QIGUO, "热心的建议(1)", "热心的建议(1)(Hoàn thành)"}),
									   66:({TASK_44, 24, 25, 26, TID_QIGUO, "人情冷暖(1)", "人情冷暖(1)(Hoàn thành)"}),
									   67:({TASK_44, 27, 28, 29, TID_QIGUO, "人情冷暖(2)", "人情冷暖(2)(Hoàn thành)"}),
									   68:({TASK_45, 1, 2, 3, TID_QIGUO, "人情冷暖(3)", "人情冷暖(3)(Hoàn thành)"}),
									   69:({TASK_45, 7, 8, 9, TID_QIGUO, "无上的荣耀(1)", "无上的荣耀(1)(Hoàn thành)"}),
									   70:({TASK_45, 10, 11, 12, TID_QIGUO, "无上的荣耀(2)", "无上的荣耀(2)(Hoàn thành)"}),
									  103:({TASK_2_00, 7, 8, 9, TID_QIGUO, "怨鬼之灵", "怨鬼之灵(Hoàn thành)"}),
]),
					   "Tần Quốc":([1:({TASK_10, 20, 21, 22, TID_QINGUO, "逃跑的壮丁", "逃跑的壮丁(Hoàn thành)"}),
										2:({TASK_10, 23, 24, 25, TID_QINGUO, "叛乱的苦役", "叛乱的苦役(Hoàn thành)"}),
										3:({TASK_11, 1, 2, 3, TID_QINGUO, "情锁秦宫(1)", "情锁秦宫(1)(Hoàn thành)"}),
										5:({TASK_11, 6, 7, 8, TID_QINGUO, "情锁秦宫(3)", "情锁秦宫(3)(Hoàn thành)"}),
										7:({TASK_11, 11, 12, 13, TID_QINGUO, "魔晴石", "魔晴石(Hoàn thành)"}),
									   11:({TASK_18, 16, 17, 18, TID_QINGUO, "大展神威(1)", "大展神威(1)(Hoàn thành)"}),
									   14:({TASK_18, 22, 23, 24, TID_QINGUO, "大展神威(4)", "大展神威(4)(Hoàn thành)"}),
									   15:({TASK_18, 25, 26, 27, TID_QINGUO, "大展神威(5)", "大展神威(5)(Hoàn thành)"}),
									   16:({TASK_10, 14, 15, 16, TID_QINGUO, "狩猎计划", "狩猎计划(Hoàn thành)"}),
									   17:({TASK_10, 17, 18, 19, TID_QINGUO, "寻找菜谱", "寻找菜谱(Hoàn thành)"}),
									   18:({TASK_19, 7, 8, 9, TID_QINGUO, "大葫芦(4)", "大葫芦(4)(Hoàn thành)"}),
									   19:({TASK_19, 10, 11, 12, TID_QINGUO, "大葫芦(5)", "大葫芦(5)(Hoàn thành)"}),
									   20:({TASK_19, 13, 14, 15, TID_QINGUO, "无耻的叛徒", "无耻的叛徒(Hoàn thành)"}),
									   21:({TASK_19, 19, 20, 21, TID_QINGUO, "追捕逃犯", "追捕逃犯(Hoàn thành)"}),
									   24:({TASK_20, 21, 22, 23, TID_QINGUO, "宫殿图纸", "宫殿图纸(Hoàn thành)"}),
									   25:({TASK_20, 24, 25, 26, TID_QINGUO, "千年红木", "千年红木(Hoàn thành)"}),
									   26:({TASK_20, 27, 28, 29, TID_QINGUO, "扫清障碍", "扫清障碍(Hoàn thành)"}),
									   29:({TASK_21, 5, 6, 7, TID_QINGUO, "修造之难", "修造之难(Hoàn thành)"}),
									   31:({TASK_21, 10, 11, 12, TID_QINGUO, "铲除恶霸", "铲除恶霸(Hoàn thành)"}),
									   34:({TASK_21, 17, 18, 19, TID_QINGUO, "出使之难", "出使之难(Hoàn thành)"}),
									   39:({TASK_21, 28, 29, 30, TID_QINGUO, "诽谤真凶", "诽谤真凶(Hoàn thành)"}),
									   42:({TASK_22, 5, 6, 7, TID_QINGUO, "真相大白", "真相大白(Hoàn thành)"}),
									   44:({TASK_22, 10, 11, 12, TID_QINGUO, "证实传闻", "证实传闻(Hoàn thành)"}),
									   45:({TASK_22, 13, 14, 15, TID_QINGUO, "牵连之罪", "牵连之罪(Hoàn thành)"}),
									   47:({TASK_22, 18, 19, 20, TID_QINGUO, "上书之难", "上书之难(Hoàn thành)"}),
									   48:({TASK_20, 4, 5, 6, TID_QINGUO, "杀人恶魔", "杀人恶魔(Hoàn thành)"}),
									   49:({TASK_20, 7, 8, 9, TID_QINGUO, "雄黄酒", "雄黄酒(Hoàn thành)"}),
									   50:({TASK_20, 10, 11, 12, TID_QINGUO, "重阳节(1)", "重阳节(1)(Hoàn thành)"}),
									   53:({TASK_20, 16, 17, 18, TID_QINGUO, "重阳节(4)", "重阳节(4)(Hoàn thành)"}),
									   55:({TASK_39, 11, 12, 13, TID_QINGUO, "控制数量", "控制数量(Hoàn thành)"}),
									   56:({TASK_39, 14, 15, 16, TID_QINGUO, "究根问底(1)", "究根问底(1)(Hoàn thành)"}),
									   57:({TASK_39, 17, 18, 19, TID_QINGUO, "究根问底(2)", "究根问底(2)(Hoàn thành)"}),
									   58:({TASK_39, 20, 21, 22, TID_QINGUO, "究根问底(3)", "究根问底(3)(Hoàn thành)"}),
									   59:({TASK_43, 17, 18, 19, TID_QINGUO, "朋友的帮助", "朋友的帮助(Hoàn thành)"}),
									   60:({TASK_43, 23, 24, 25, TID_QINGUO, "黎明前的黑暗", "黎明前的黑暗(Hoàn thành)"}),
									   61:({TASK_44, 18, 19, 20, TID_QINGUO, "热心的建议(3)", "热心的建议(3)(Hoàn thành)"}),
									   62:({TASK_44, 21, 22, 23, TID_QINGUO, "热心的建议(4)", "热心的建议(4)(Hoàn thành)"}),
									   63:({TASK_45, 4, 5, 6, TID_QINGUO, "天寒地冻", "天寒地冻(Hoàn thành)"}),
									   65:({TASK_46, 3, 4, 5, TID_QINGUO, "刀魂传说2", "刀魂传说2(Hoàn thành)"}),
									   67:({TASK_46, 8, 9, 10, TID_QINGUO, "刀魂传说4", "刀魂传说4(Hoàn thành)"}),
									   70:({TASK_46, 15, 16, 17, TID_QINGUO, "平阳之乱2", "平阳之乱2(Hoàn thành)"}),
									   71:({TASK_46, 18, 19, 20, TID_QINGUO, "平阳之乱3", "平阳之乱3(Hoàn thành)"}),
									   72:({TASK_46, 21, 22, 23, TID_QINGUO, "平阳之乱4", "平阳之乱4(Hoàn thành)"}),
									   75:({TASK_46, 28, 29, 30, TID_QINGUO, "炼药之路2", "炼药之路2(Hoàn thành)"}),
									   77:({TASK_47, 3, 4, 5, TID_QINGUO, "炼药之路4", "炼药之路4(Hoàn thành)"}),
									   81:({TASK_47, 12, 13, 14, TID_QINGUO, "破除谣言3", "破除谣言3(Hoàn thành)"}),
									   86:({TASK_47, 23, 24, 25, TID_QINGUO, "索取神剑3", "索取神剑3(Hoàn thành)"}),
									   87:({TASK_47, 26, 27, 28, TID_QINGUO, "索取神剑4", "索取神剑4(Hoàn thành)"}),
									  101:({TASK_2_00, 1, 2, 3, TID_QINGUO, "Tiêu diệt 叛军", "Tiêu diệt 叛军(Hoàn thành)"}),
									  102:({TASK_2_00, 28, 29, 30, TID_QINGUO, "大肆破坏", "大肆破坏(Hoàn thành)"}),
									  103:({TASK_2_01, 1, 2, 3, TID_QINGUO, "魂兮归来", "魂兮归来(Hoàn thành)"}),
]),
					   "Yên Quốc":([1:({TASK_12, 1, 2, 3, TID_YANGUO, "郑国渠的阴风", "郑国渠的阴风(Hoàn thành)"}),
									   2:({TASK_12, 4, 5, 6, TID_YANGUO, "忍气吞声", "忍气吞声(Hoàn thành)"}),
									   3:({TASK_12, 7, 8, 9, TID_YANGUO, "河道传说", "河道传说(Hoàn thành)"}),
									   4:({TASK_12, 10, 11, 12, TID_YANGUO, "河道惊魂", "河道惊魂(Hoàn thành)"}),
									   5:({TASK_12, 13, 14, 15, TID_YANGUO, "程风的烦恼", "程风的烦恼(Hoàn thành)"}),
									   6:({TASK_12, 16, 17, 18, TID_YANGUO, "梦中奇闻", "梦中奇闻(Hoàn thành)"}),
									   7:({TASK_12, 19, 20, 21, TID_YANGUO, "郑国渠里的哭声", "郑国渠里的哭声(Hoàn thành)"}),
									   8:({TASK_12, 22, 23, 24, TID_YANGUO, "河道霸王", "河道霸王(Hoàn thành)"}),
									   9:({TASK_12, 25, 26, 27, TID_YANGUO, "河道冤魂", "河道冤魂(Hoàn thành)"}),
									  10:({TASK_12, 28, 29, 30, TID_YANGUO, "众说纷纭", "众说纷纭(Hoàn thành)"}),
									  11:({TASK_13, 1, 2, 3, TID_YANGUO, "心事重重", "心事重重(Hoàn thành)"}),
									  12:({TASK_13, 4, 5, 6, TID_YANGUO, "寒丝传说", "寒丝传说(Hoàn thành)"}),
									  13:({TASK_13, 7, 8, 9, TID_YANGUO, "可怕的预言", "可怕的预言(Hoàn thành)"}),
									  14:({TASK_13, 10, 11, 12, TID_YANGUO, "明镜传说", "明镜传说(Hoàn thành)"}),
									  15:({TASK_13, 13, 14, 15, TID_YANGUO, "绝世神兵", "绝世神兵(Hoàn thành)"}),
									  16:({TASK_10, 26, 27, 28, TID_YANGUO, "千年之劫", "千年之劫(Hoàn thành)"}),
									  18:({TASK_11, 24, 25, 26, TID_YANGUO, "挑战", "挑战(Hoàn thành)"}),
									  19:({TASK_11, 27, 28, 29, TID_YANGUO, "研究石头", "研究石头(Hoàn thành)"}),
									  20:({TASK_13, 22, 23, 24, TID_YANGUO, "泥雕", "泥雕(Hoàn thành)"}),
									  21:({TASK_13, 25, 26, 27, TID_YANGUO, "业余爱好", "业余爱好(Hoàn thành)"}),
									  22:({TASK_13, 28, 29, 30, TID_YANGUO, "安全隐患", "安全隐患(Hoàn thành)"}),
									  23:({TASK_14, 1, 2, 3, TID_YANGUO, "报仇雪恨", "报仇雪恨(Hoàn thành)"}),
									  24:({TASK_14, 4, 5, 6, TID_YANGUO, "Bảo thạch quý hiếm", "Bảo thạch quý hiếm(Hoàn thành)"}),
									  25:({TASK_14, 7, 8, 9, TID_YANGUO, "浑仪(1)", "浑仪(1)(Hoàn thành)"}),
									  26:({TASK_14, 10, 11, 12, TID_YANGUO, "浑仪(2)", "浑仪(2)(Hoàn thành)"}),
									  28:({TASK_14, 15, 16, 17, TID_YANGUO, "二胡", "二胡(Hoàn thành)"}),
									  29:({TASK_14, 18, 19, 20, TID_YANGUO, "偷钱的笨熊", "偷钱的笨熊(Hoàn thành)"}),
									  31:({TASK_15, 9, 10, 11, TID_YANGUO, "Căn bệnh của Phu Nhân(2)", "Căn bệnh của Phu Nhân(2)(Hoàn thành)"}),
									  32:({TASK_15, 12, 13, 14, TID_YANGUO, "Căn bệnh của Phu Nhân(3)", "Căn bệnh của Phu Nhân(3)(Hoàn thành)"}),
									  33:({TASK_15, 15, 16, 17, TID_YANGUO, "饰品店", "饰品店(Hoàn thành)"}),
									  34:({TASK_15, 18, 19, 20, TID_YANGUO, "爱吃辣的客人", "爱吃辣的客人(Hoàn thành)"}),
									  36:({TASK_16, 11, 12, 13, TID_YANGUO, "逍遥法外", "逍遥法外(Hoàn thành)"}),
									  37:({TASK_27, 12, 13, 14, TID_YANGUO, "燕王好珍玩(2)", "燕王好珍玩(2)(Hoàn thành)"}),
									  39:({TASK_31, 18, 19, 20, TID_YANGUO, "妖魔鬼怪", "妖魔鬼怪(Hoàn thành)"}),
									  39:({TASK_31, 18, 19, 20, TID_YANGUO, "秘密(2)", "秘密(2)(Hoàn thành)"}),
									  40:({TASK_31, 21, 22, 23, TID_YANGUO, "秘密(3)", "秘密(3)(Hoàn thành)"}),
									  41:({TASK_31, 24, 25, 26, TID_YANGUO, "秘密(4)", "秘密(4)(Hoàn thành)"}),
									  42:({TASK_31, 27, 28, 29, TID_YANGUO, "援助", "援助(Hoàn thành)"}),
									  43:({TASK_32, 1, 2, 3, TID_YANGUO, "单刀", "单刀(Hoàn thành)"}),
									  44:({TASK_32, 11, 12, 13, TID_YANGUO, "净化灵魂", "净化灵魂(Hoàn thành)"}),
									  45:({TASK_32, 14, 15, 16, TID_YANGUO, "收集大枣", "收集大枣(Hoàn thành)"}),
									  46:({TASK_32, 17, 18, 19, TID_YANGUO, "堕落的力量", "堕落的力量(Hoàn thành)"}),
									  47:({TASK_32, 20, 21, 22, TID_YANGUO, "罪恶的源泉", "罪恶的源泉(Hoàn thành)"}),
									  48:({TASK_32, 23, 24, 25, TID_YANGUO, "格杀勿论", "格杀勿论(Hoàn thành)"}),
									  49:({TASK_32, 26, 27, 28, TID_YANGUO, "祖父的遗产(1)", "祖父的遗产(1)(Hoàn thành)"}),
									  50:({TASK_43, 20, 21, 22, TID_YANGUO, "军营的补给", "军营的补给(Hoàn thành)"}),
									  51:({TASK_44, 1, 2, 3, TID_YANGUO, "黑暗笼罩", "黑暗笼罩(Hoàn thành)"}),
									  53:({TASK_32, 6, 7, 8, TID_YANGUO, "使节的差事(2)", "使节的差事(2)(Hoàn thành)"}),
]),
					 "Triệu Quốc":([1:({TASK_11, 16, 17, 18, TID_ZHAOGUO, "无奈的求助(2)", "无奈的求助(2)(Hoàn thành)"}),
										2:({TASK_11, 19, 20, 21, TID_ZHAOGUO, "无奈的求助(3)", "无奈的求助(3)(Hoàn thành)"}),
										4:({TASK_15, 21, 22, 23, TID_ZHAOGUO, "找寻童年乐趣", "找寻童年乐趣(Hoàn thành)"}),
										5:({TASK_15, 24, 25, 26, TID_ZHAOGUO, "Sản xuất công cụ", "Sản xuất công cụ(Hoàn thành)"}),
										6:({TASK_15, 27, 28, 29, TID_ZHAOGUO, "除恶惩凶", "除恶惩凶(Hoàn thành)"}),
										7:({TASK_16, 3, 4, 5, TID_ZHAOGUO, "拦路狗", "拦路狗(Hoàn thành)"}),
										9:({TASK_16, 8, 9, 10, TID_ZHAOGUO, "紧缩开支", "紧缩开支(Hoàn thành)"}),
									   10:({TASK_14, 21, 22, 23, TID_ZHAOGUO, "长城泪", "长城泪(Hoàn thành)"}),
									   11:({TASK_14, 24, 25, 26, TID_ZHAOGUO, "脚夫的烦恼", "脚夫的烦恼(Hoàn thành)"}),
									   12:({TASK_14, 27, 28, 29, TID_ZHAOGUO, "长城惊魂", "长城惊魂(Hoàn thành)"}),
									   13:({TASK_15, 1, 2, 3, TID_ZHAOGUO, "长城恶霸", "长城恶霸(Hoàn thành)"}),
									   14:({TASK_15, 4, 5, 6, TID_ZHAOGUO, "佳酿美酒", "佳酿美酒(Hoàn thành)"}),
									   15:({TASK_16, 14, 15, 16, TID_ZHAOGUO, "长城上的哭泣", "长城上的哭泣(Hoàn thành)"}),
									   16:({TASK_16, 17, 18, 19, TID_ZHAOGUO, "恶魔来临", "恶魔来临(Hoàn thành)"}),
									   17:({TASK_16, 20, 21, 22, TID_ZHAOGUO, "临终寄托", "临终寄托(Hoàn thành)"}),
									   18:({TASK_16, 23, 24, 25, TID_ZHAOGUO, "神衣传说", "神衣传说(Hoàn thành)"}),
									   19:({TASK_16, 26, 27, 28, TID_ZHAOGUO, "千里神行", "千里神行(Hoàn thành)"}),
									   20:({TASK_17, 1, 2, 3, TID_ZHAOGUO, "夜空中的灵光", "夜空中的灵光(Hoàn thành)"}),
									   21:({TASK_17, 4, 5, 6, TID_ZHAOGUO, "夜空中的响声", "夜空中的响声(Hoàn thành)"}),
									   22:({TASK_17, 7, 8, 9, TID_ZHAOGUO, "夜半钟声", "夜半钟声(Hoàn thành)"}),
									   23:({TASK_17, 10, 11, 12, TID_ZHAOGUO, "烽火台上的烟雾", "烽火台上的烟雾(Hoàn thành)"}),
									   24:({TASK_17, 13, 14, 15, TID_ZHAOGUO, "奇异之光", "奇异之光(Hoàn thành)"}),
									   25:({TASK_17, 16, 17, 18, TID_ZHAOGUO, "孤魂怨叹", "孤魂怨叹(Hoàn thành)"}),
									   26:({TASK_17, 19, 20, 21, TID_ZHAOGUO, "长城奇遇", "长城奇遇(Hoàn thành)"}),
									   27:({TASK_17, 22, 23, 24, TID_ZHAOGUO, "神秘的荧光", "神秘的荧光(Hoàn thành)"}),
									   28:({TASK_17, 25, 26, 27, TID_ZHAOGUO, "打家劫舍", "打家劫舍(Hoàn thành)"}),
									   29:({TASK_17, 28, 29, 30, TID_ZHAOGUO, "脚夫留言", "脚夫留言(Hoàn thành)"}),
									   30:({TASK_18, 1, 2, 3, TID_ZHAOGUO, "管家的苦恼", "管家的苦恼(Hoàn thành)"}),
									   31:({TASK_18, 4, 5, 6, TID_ZHAOGUO, "叛国之徒", "叛国之徒(Hoàn thành)"}),
									   32:({TASK_18, 7, 8, 9, TID_ZHAOGUO, "流浪奇遇", "流浪奇遇(Hoàn thành)"}),
									   33:({TASK_18, 10, 11, 12, TID_ZHAOGUO, "守卫的遗憾", "守卫的遗憾(Hoàn thành)"}),
									   34:({TASK_18, 13, 14, 15, TID_ZHAOGUO, "长城上的烟火", "长城上的烟火(Hoàn thành)"}),
									   35:({TASK_19, 16, 17, 18, TID_ZHAOGUO, "赵国的美酒", "赵国的美酒(Hoàn thành)"}),
									   37:({TASK_19, 26, 27, 28, TID_ZHAOGUO, "合适的礼物", "合适的礼物(Hoàn thành)"}),
									   39:({TASK_20, 1, 2, 3, TID_ZHAOGUO, "清场", "清场(Hoàn thành)"}),
									   40:({TASK_23, 27, 28, 29, TID_ZHAOGUO, "武士的爱情(3)", "武士的爱情(3)(Hoàn thành)"}),
									   41:({TASK_27, 7, 8, 9, TID_ZHAOGUO, "万人坑的骷髅", "万人坑的骷髅(Hoàn thành)"}),
									   43:({TASK_27, 16, 17, 18, TID_ZHAOGUO, "燕王爱珍玩(4)", "燕王爱珍玩(4)(Hoàn thành)"}),
									   44:({TASK_27, 28, 29, 30, TID_ZHAOGUO, "鹿角", "鹿角(Hoàn thành)"}),
									   45:({TASK_28, 1, 2, 3, TID_ZHAOGUO, "雕刻", "雕刻(Hoàn thành)"}),
									   46:({TASK_28, 4, 5, 6, TID_ZHAOGUO, "深入牧场", "深入牧场(Hoàn thành)"}),
									   47:({TASK_28, 7, 8, 9, TID_ZHAOGUO, "木箱的秘密(1)", "木箱的秘密(1)(Hoàn thành)"}),
									   50:({TASK_28, 17, 18, 19, TID_ZHAOGUO, "不安的魂魄", "不安的魂魄(Hoàn thành)"}),
									   51:({TASK_28, 20, 21, 22, TID_ZHAOGUO, "最后一战", "最后一战(Hoàn thành)"}),
									   52:({TASK_28, 26, 27, 28, TID_ZHAOGUO, "证明实力", "证明实力(Hoàn thành)"}),
									   53:({TASK_29, 1, 2, 3, TID_ZHAOGUO, "秘密行动", "秘密行动(Hoàn thành)"}),
									   59:({TASK_43, 26, 27, 28, TID_ZHAOGUO, "权力的象征", "权力的象征(Hoàn thành)"}),
									   60:({TASK_45, 18, 19, 20, TID_ZHAOGUO, "求医(1)", "求医(1)(Hoàn thành)"}),
									   70:({TASK_41, 20, 21, 22, TID_ZHAOGUO, "试探实力", "试探实力(Hoàn thành)"}),
									   71:({TASK_41, 23, 24, 25, TID_ZHAOGUO, "天门探险", "天门探险(Hoàn thành)"}),
									   76:({TASK_41, 28, 29, 30, TID_ZHAOGUO, "勇闯天门阵", "勇闯天门阵(Hoàn thành)"}),
									   77:({TASK_42, 7, 8, 9, TID_ZHAOGUO, "搜寻战报", "搜寻战报(Hoàn thành)"}),
									   79:({TASK_42, 12, 13, 14, TID_ZHAOGUO, "Thủ Thuật Nhỏ", "Thủ Thuật Nhỏ (Hoàn thành)"}),
									   80:({TASK_42, 15, 16, 17, TID_ZHAOGUO, "除掉刺客", "除掉刺客(Hoàn thành)"}),
									   81:({TASK_42, 18, 19, 20, TID_ZHAOGUO, "寻回地图", "寻回地图(Hoàn thành)"}),
									   84:({TASK_42, 25, 26, 27, TID_ZHAOGUO, "为民除害", "为民除害(Hoàn thành)"}),
									   86:({TASK_42, 28, 29, 30, TID_ZHAOGUO, "枉法之徒", "枉法之徒(Hoàn thành)"}),
									   90:({TASK_43, 9, 10, 11, TID_ZHAOGUO, "解除威胁", "解除威胁(Hoàn thành)"}),
									   91:({TASK_43, 12, 13, 14, TID_ZHAOGUO, "寻回名单", "寻回名单(Hoàn thành)"}),
									  101:({TASK_2_01, 10, 11, 12, TID_ZHAOGUO, "收集机关构件", "收集机关构件(Hoàn thành)"}),

]),
						"Mao Sơn":([2:({TASK_23, 8, 9, 10, TID_MAOSHAN, "游魂(3)", "游魂(3)(Hoàn thành)"}),
									  3:({TASK_23, 11, 12, 13, TID_MAOSHAN, "游魂(4)", "游魂(4)(Hoàn thành)"}),
									  4:({TASK_23, 14, 15, 16, TID_MAOSHAN, "游魂(5)", "游魂(5)(Hoàn thành)"}),
									  5:({TASK_23, 17, 18, 19, TID_MAOSHAN, "游魂(6)", "游魂(6)(Hoàn thành)"}),
]),
					   "Chu Quốc":([7:({TASK_28, 14, 15, 16, TID_ZHOUGUO, "木箱的秘密(4)", "木箱的秘密(4)(Hoàn thành)"}),
										8:({TASK_39, 28, 29, 30, TID_ZHOUGUO, "四面楚歌(4)", "四面楚歌(4)(Hoàn thành)"}),
									   11:({TASK_40, 7, 8, 9, TID_ZHOUGUO, "Thẻ Tre Bị Mất", "Thẻ Tre Bị Mất (Hoàn thành)"}),
									   12:({TASK_40, 10, 11, 12, TID_ZHOUGUO, "Sừng Trâu Vàng", "Sừng Trâu Vàng (Hoàn thành)"}),
									   20:({TASK_2_00, 20, 21, 22, TID_ZHOUGUO, "访问生活技能师傅", "访问生活技能师傅(Hoàn thành)"}),
									   21:({TASK_2_00, 23, 24, 25, TID_ZHOUGUO, "访问周国名士", "访问周国名士(Hoàn thành)"}),
									  102:({TASK_2_00, 4, 5, 6, TID_ZHOUGUO, "邪恶的厨师", "邪恶的厨师(Hoàn thành)"}),
									  103:({TASK_2_01, 4, 5, 6, TID_ZHOUGUO, "机关密图", "机关密图(Hoàn thành)"}),
]),
				   "Đông Hải Đảo":([1:({TASK_37, 7, 8, 9, TID_DONGHAIDAO, "肖独贵(3)", "肖独贵(3)(Hoàn thành)"}),
									  2:({TASK_37, 10, 11, 12, TID_DONGHAIDAO, "肖独贵(4)", "肖独贵(4)(Hoàn thành)"}),
]),
				   "Tân Thủ Thôn":([25:({TASK_40, 26, 27, 28, TID_NEWBIE_01, "头疼的毛病(2)", "头疼的毛病(2)(Hoàn thành)"}),
									   28:({TASK_41, 6, 7, 8, TID_NEWBIE_01, "疑难杂症(2)", "疑难杂症(2)(Hoàn thành)"}),
									   30:({TASK_41, 13, 14, 15, TID_NEWBIE_01, "装饰房屋", "装饰房屋(Hoàn thành)"}),
									   31:({TASK_41, 1, 2, 3, TID_NEWBIE_01, "妖言惑众", "妖言惑众(Hoàn thành)"}),
									   32:({TASK_40, 17, 18, 19, TID_NEWBIE_01, "锻炼自己", "锻炼自己(Hoàn thành)"}),
									   44:({TASK_NEWBIE_02, 18, 19, 20, TID_NEWBIE_01, "酿酒的原材料", "酿酒的原材料(Hoàn thành)"}),
									   45:({TASK_49, 15, 16, 17, TID_NEWBIE_01, "蚂蚁带来的烦恼", "蚂蚁带来的烦恼(Hoàn thành)"}),
									   46:({TASK_49, 18, 19, 20, TID_NEWBIE_01, "偷吃的小野兔", "偷吃的小野兔(Hoàn thành)"}),
									   47:({TASK_49, 21, 22, 23, TID_NEWBIE_01, "消灭稻草人", "消灭稻草人(Hoàn thành)"}),
									   48:({TASK_49, 24, 25, 26, TID_NEWBIE_01, "行路难", "行路难(Hoàn thành)"}),
									  101:({TASK_48, 1, 2, 3, TID_NEWBIE_01, "Thủ Thuật Nhỏ", "Thủ Thuật Nhỏ (Hoàn thành)"}),
									  104:({TASK_48, 8, 9, 10, TID_NEWBIE_01, "Gia Tộc Ngọc Bội", "Gia Tộc Ngọc Bội (Hoàn thành)"}),
									  107:({TASK_48, 15, 16, 17, TID_NEWBIE_01, "修理店老板的铁锤", "修理店老板的铁锤(Hoàn thành)"}),
									  108:({TASK_48, 18, 19, 20, TID_NEWBIE_01, "妖言惑众", "妖言惑众(Hoàn thành)"}),
									  110:({TASK_48, 23, 24, 25, TID_NEWBIE_01, "疑难杂症(2)", "疑难杂症(2)(Hoàn thành)"}),
									  112:({TASK_48, 28, 29, 30, TID_NEWBIE_01, "装饰房屋", "装饰房屋(Hoàn thành)"}),
									  116:({TASK_49, 6, 7, 8, TID_NEWBIE_01, "当铺老板的交易", "当铺老板的交易(Hoàn thành)"}),

]),
				   "Vân Mộng Cốc":([1:({TASK_45, 23, 24, 25, TID_YUNMENZE, "求医(3)", "求医(3)(Hoàn thành)"}),
									  2:({TASK_45, 26, 27, 28, TID_YUNMENZE, "求医(4)", "求医(4)(Hoàn thành)"}),
]),
]);
mapping mpTaskDesc = ([]);

// 函数:生成二进制码
void SAVE_BINARY() {}

void create()
{
	object obj;
	string file = "/quest/taskdesc.c";
	if (obj = find_object(file))
	{
		obj->before_destruct();
		destruct(obj);
	}
	load_object(file);
	mpTaskDesc = file->get_taskdesc();
}
// 函数:教训NPC 任务
void kill_legend_npc(object me, object who)
{
	string name;
	int level, count;

	level = me->get_level();
	name = who->get_name();

	if (me->get_legend(TASK_NEWBIE_00, 6) && !me->get_legend(TASK_NEWBIE_00, 7))
	{
		if (name == "Bù Nhìn")
		{
			me->add_save("newbie_5", 1);
			count = me->get_save("newbie_5");
			send_user(me, "%c%s", '!', sprintf("小试身手任务Hoàn thành%d/8", count));
			if (count >= 8)
			{
				me->delete_save("newbie_5");
				me->set_legend(TASK_NEWBIE_00, 7);
				send_user(me, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 2, "Thủ Thuật Nhỏ (Hoàn thành)");
			}
			else
				send_user(me, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 2, "Thủ Thuật Nhỏ");
			USER_TASK_D->send_task_intro(me, 2, TID_NEWBIE_01, 2);
			return;
		}
	}
}
//任务树
void get_task_list(object who)
{
	object npc, item;
	string id, *name1;
	int iFlag, i, size, *nId, j, count, iLegend;
	mixed *nTmp;
	int x;
	x = (time() - 4 * 24 * 3600 + 8 * 3600) / (7 * 24 * 3600);
	if (who->get_save_2("double_time.week") != x)
	{
		who->set_save_2("double_time.week", x);
		who->set_save_2("double_time.time", 0);	  //双
		who->set_save_2("double_time.time1", 0);  //战国令
		who->set_save_2("double_time.time2", 0);  //战国号角
		who->set_save_2("double_time.time3", 0);  //额外换取的3小时双倍时间
		who->set_save_2("double_time.freeze", 0); //冻结的双倍时间
	}

	if (who->get("tasklist") == 0)
	{
		who->set("tasklist", 1);
		send_user(who, "%c%c", 0x51, 0);
	}
	else
	{
		if (who->get_quest("escort.biaowang"))
		{
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 3, "");
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_ESCORT, "Nhiệm vụ áp tiêu");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 3, "镖王争霸战");
		}
		//		if ( who->get_save_2("51cuanye.time") )
		//		{
		//			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,1,"" );
		//			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_WUYIHUODONG,"五一活动" );
		//			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,1,"极限穿越" );
		//		}
		//		if ( who->get_save_2("51tiandao.accept") )
		//		{
		//			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"" );
		//			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_WUYIHUODONG,"五一活动" );
		//			if ( who->get_save_2("51tiandao.amount") < 100 )
		//				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"天道酬勤" );
		//			else
		//				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"天道酬勤(Hoàn thành)" );
		//		}
		return;
	}
	//	if ( who->get_save_2("51cuanye.time") )
	//	{
	//		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_WUYIHUODONG,"五一活动" );
	//		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,1,"极限穿越" );
	//	}
	//	if ( who->get_save_2("51tiandao.accept") )
	//	{
	//		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_WUYIHUODONG,"五一活动" );
	//		if ( who->get_save_2("51tiandao.amount") < 100 )
	//			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"天道酬勤" );
	//		else
	//			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"天道酬勤(Hoàn thành)" );
	//	}
	if ((i = who->get_save("dodolook")) && i < 4)
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_DODOLOOK, "寻找dodolook");
		if (i == 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DODOLOOK, 1, "拜访魏昭王");
		else if (i == 2)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DODOLOOK, 2, "寻回玉玺");
		else if (i == 3)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DODOLOOK, 3, "寻回玉玺(Hoàn thành)");
	}
	if (who->get_save_2("dodolook_task.npcid"))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_YUANFEN, "缘分对对碰");
		if (who->get_save_2("dodolook_task.finish"))
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_YUANFEN, 1, "消灭噬情魔(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_YUANFEN, 1, "消灭噬情魔");
	}
	if (stringp(who->get_save_2("dapang.name")))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_DAPANG, "大胖任务");
		if (who->get_save_2("dapang.count") < who->get_save_2("dapang.total"))
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "杀20只" + who->get_save_2("dapang.name"));
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "杀20只" + who->get_save_2("dapang.name") + "(Hoàn thành)");
	}
	if (gone_time(who->get_login_time()) + who->get_game_time() < who->get_double_time() || who->get_save_2("double_time.freeze") > 0)
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi");
	}
	if (get_effect(who, EFFECT_MAGIC_CARD))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 2, "Thời Gian Biến Thân");
	}
	if (who->get_save_2("insurance.timeover") > time())
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 3, "Thời Gian Bảo Hiểm");
	}
	if (who->get_cashkhoa())
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
		//send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 4, "Ngân Lượng Khóa");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 4, "Ngân Lượng Khóa");
	}
	if (who->get_save_2("refine.status") == 1)
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_REFINE, "Nhiệm vụ Thu Yêu");
		if (who->get_save_2("refine.count") >= 450)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_REFINE, 1, "Nhiệm vụ Hồ Lô Thu Yêu(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_REFINE, 1, "Nhiệm vụ Hồ Lô Thu Yêu");
	}
	if (who->get_save_2("cantuong.status") == 1)
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_CANTUONG, "Nâng cấp Thần Binh");
		if (who->get_save_2("cantuong.count") >= 10000 &&
			who->get_save_2("cantuong.hv") >= 1 &&
			who->get_save_2("cantuong.agbd") >= 1 &&
			who->get_save_2("cantuong.uvdtq") >= 1 &&
			who->get_save_2("cantuong.ktl") >= 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ");
	}
	if (who->get_task("criminal.bonus") || (stringp(id = who->get_task("criminal")) && (npc = find_char(id)) && npc->is_criminal())) // 30 分钟
	{

		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_CRIMINAL, "Đoạt Bảo Nhiệm Vụ");
		if (who->get_task("criminal.bonus"))
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CRIMINAL, 1, "Tiêu diệt Đào Phạm(Đã hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CRIMINAL, 1, "Tiêu diệt Đào Phạm");
	}
	if (who->get_save_2("marrytask"))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_HONGNIANG, "Hồng Nương Nhiệm Vụ");
		if (who->get_save_2("marrytask.finish"))
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_HONGNIANG, 1, "Giáo huấn Ác Bá(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_HONGNIANG, 1, "Giáo huấn Ác Bá");
	}

	if (who->get_save_2("master_hide"))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_MASTER_HIDE, "Nhiệm Vụ Sư Môn");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER_HIDE, 1, "Nhiệm vụ Ẩn Tàng");
	}

	TASK_ROBBER_D->send_task_list(who);
	TASK_BANDITI_D->send_task_list(who);
	TASK_BANDITI_D->send_gold_task_list(who);
	TASK_THIEF_D->send_task_list(who);
	"/sys/party/valentine"->send_task_list(who);
	"/sys/party/qixi"->send_task_list(who);
	TASK_ESCORT_D->send_task_list(who);
	"/sys/sys/manager"->send_task_list(who);
	if (who->get_save_2("chain.type") > 0)
	{
		CHAIN_D->send_task_list(who, who->get_save_2("chain.type"));
	}
	if (who->get_fam_name())
	{
		if (who->get_save_2("mastertask.type") > 0)
		{
			TASK_MASTER_D->send_task_list(who, who->get_save_2("mastertask.type"));
		}
		//		if (who->get_save_2("masterfight.status")>0)
		//                {
		//			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_MASTERFIGHT,"师门挑战任务" );
		//			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_MASTERFIGHT,1,"挑战任务" );
		//		}
	}

	//以下为剧情任务
	name1 = keys(mpTaskList);
	for (i = 0, size = sizeof(name1); i < size; i++)
	{
		nId = keys(mpTaskList[name1[i]]);
		for (j = 0, count = sizeof(nId); j < count; j++)
		{

			nTmp = mpTaskList[name1[i]][nId[j]];
			if (who->get_legend(nTmp[0], nTmp[1]) && !who->get_legend(nTmp[0], nTmp[2]))
			{
				send_user(who, "%c%c%c%w%s", 0x51, 2, 1, nTmp[3], name1[i]);
				send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, nTmp[3], nId[j], nTmp[4]);
				iLegend++;
			}
		}
	}

	name1 = keys(mpTaskList1);
	for (i = 0, size = sizeof(name1); i < size; i++)
	{
		nId = keys(mpTaskList1[name1[i]]);
		for (j = 0, count = sizeof(nId); j < count; j++)
		{
			nTmp = mpTaskList1[name1[i]][nId[j]];
			if (who->get_legend(nTmp[0], nTmp[1]) && !who->get_legend(nTmp[0], nTmp[3]))
			{
				send_user(who, "%c%c%c%w%s", 0x51, 2, 1, nTmp[4], name1[i]);
				if (who->get_legend(nTmp[0], nTmp[2]))
					send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, nTmp[4], nId[j], nTmp[6]);
				else
					send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, nTmp[4], nId[j], nTmp[5]);
				iLegend++;
			}
		}
	}
	if (who->get_legend(TASK_NEWBIE_00, 3) && !who->get_legend(TASK_NEWBIE_00, 5))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (who->get_legend(TASK_NEWBIE_00, 4))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 1, "神仙爷爷的嘱托(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 1, "神仙爷爷的嘱托");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_00, 6) && !who->get_legend(TASK_NEWBIE_00, 8))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (who->get_legend(TASK_NEWBIE_00, 7))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 2, "小试身手(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 2, "小试身手");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_01, 5) && !who->get_legend(TASK_NEWBIE_01, 6))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (!objectp(item = present("Tàng Bảo Đồ", who, 1, MAX_CARRY)) || item->is_xunbao() != 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 4, "Kinh Nghiệm Tìm Báu Vật");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 4, "Kinh Nghiệm Tìm Báu Vật (Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_01, 7) && (!who->get_legend(TASK_NEWBIE_01, 8) || !who->get_legend(TASK_NEWBIE_01, 9)))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 5, "Gia Tộc Ngọc Bội");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_01, 14) && (!who->get_legend(TASK_NEWBIE_01, 15) || !who->get_legend(TASK_NEWBIE_01, 16)))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (!who->get_legend(TASK_NEWBIE_01, 15))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 8, "修理店老板的铁锤");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 8, "修理店老板的铁锤(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_02, 1) && (!who->get_legend(TASK_NEWBIE_02, 2) || !who->get_legend(TASK_NEWBIE_02, 3)))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (!who->get_legend(TASK_NEWBIE_02, 2))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 14, "当铺老板的交易");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 14, "当铺老板的交易(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_02, 4) && (!who->get_legend(TASK_NEWBIE_02, 5) || !who->get_legend(TASK_NEWBIE_02, 6)))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (!who->get_legend(TASK_NEWBIE_02, 5))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 15, "讨厌的山鸡");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 15, "讨厌的山鸡(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_02, 7) && (!who->get_legend(TASK_NEWBIE_02, 8) || !who->get_legend(TASK_NEWBIE_02, 9)))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (!who->get_legend(TASK_NEWBIE_02, 8))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 16, "小鸡咕咕");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 16, "小鸡咕咕(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_00, 17) && !who->get_legend(TASK_NEWBIE_00, 19))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (who->get_legend(TASK_NEWBIE_00, 18))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 19, "稻草人的委托(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 19, "稻草人的委托");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_02, 14) && !who->get_legend(TASK_NEWBIE_02, 16))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (!who->get_legend(TASK_NEWBIE_02, 15))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 20, "惩治恶将");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 20, "惩治恶将(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_02, 17) && !who->get_legend(TASK_NEWBIE_02, 20))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
		if (!who->get_legend(TASK_NEWBIE_02, 20))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 21, "百步仙");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 21, "百步仙(Hoàn thành)");
		iLegend++;
	}
	//if ( who->get_legend(TASK_NEWBIE_02, 28) && !who->get_legend(TASK_NEWBIE_02, 30) )
	//{
	//send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
	//if ( !who->get_legend(TASK_NEWBIE_02, 29) )
	//	send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,22,"正义之战" );
	//else
	//	send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,22,"正义之战(Hoàn thành)" );
	//iLegend++;
	//}
	//	if ( who->get_legend(TASK_NEWBIE_02, 18) && !who->get_legend(TASK_NEWBIE_02, 20) )
	//	{
	//		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_BAQIU,"巴丘" );
	//		if ( !who->get_legend(TASK_NEWBIE_02, 19) )
	//			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_BAQIU,1,"酿酒的原材料" );
	//		else
	//			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_BAQIU,1,"酿酒的原材料(Hoàn thành)" );
	//		iLegend++;
	//	}
	if (who->get_legend(TASK_NEWBIE_02, 22) && !who->get_legend(TASK_NEWBIE_02, 23))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_HUANJIAO, "幽谷");
		send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_HUANJIAO, 1, "夫妻间的争吵");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_02, 24) && !who->get_legend(TASK_NEWBIE_02, 25))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_YEWAI, "清溪");
		if (who->get_save_2("xiaomao_fengmi") >= 3)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YEWAI, 1, "美味的蜜糖(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YEWAI, 1, "美味的蜜糖");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_02, 26) && !who->get_legend(TASK_NEWBIE_02, 27))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_YEWAI, "清溪");
		if (who->get_save_2("xiaomifeng") >= 8)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YEWAI, 2, "乱蛰人的小蜜蜂(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YEWAI, 2, "乱蛰人的小蜜蜂");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 1) && !who->get_legend(TASK_NEWBIE_03, 2))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_CHUGUO, "Sở Quốc");
		if (!objectp(present("钱老九的货物", who, 1, MAX_CARRY)))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 1, "取回货物");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 1, "取回货物(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 3) && !who->get_legend(TASK_NEWBIE_03, 4))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_CHUGUO, "Sở Quốc");
		if (!objectp(item = present("珍珠项链", who, 1, MAX_CARRY)) || item->is_xianglian() != 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 2, "心上人的礼物");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 2, "心上人的礼物(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 5) && !who->get_legend(TASK_NEWBIE_03, 6))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_CHUGUO, "Sở Quốc");
		if (who->get_save_2("sijiaose") < 18)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 3, "消灭四脚蛇");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 3, "消灭四脚蛇(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 7) && !who->get_legend(TASK_NEWBIE_03, 8))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_CHUGUO, "Sở Quốc");
		if (who->get_save_2("xuantieshi") < 3)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 4, "打造惊世之剑");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 4, "打造惊世之剑(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 9) && !who->get_legend(TASK_NEWBIE_03, 10))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_CHUGUO, "Sở Quốc");
		if (!who->get_save_2("bandiangou"))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 5, "斑点狗的血液");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 5, "斑点狗的血液(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 11) && !who->get_legend(TASK_NEWBIE_03, 14))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_CHUGUO, "Sở Quốc");
		if (!who->get_legend(TASK_NEWBIE_03, 12))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 7, "买椟还珠(1)");
		else if (who->get_legend(TASK_NEWBIE_03, 13))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 8, "买椟还珠(2)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 15) && !who->get_legend(TASK_NEWBIE_03, 16))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_ZHOUGUO, "Chu Quốc");
		if (who->get_save_2("gongsumutou") >= 20)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 4, "买椟还珠(3)(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 4, "买椟还珠(3)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 17) && !who->get_legend(TASK_NEWBIE_03, 18))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_ZHOUGUO, "Chu Quốc");
		if (who->get_save_2("gongsupaozi"))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 5, "买椟还珠(4)(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 5, "买椟还珠(4)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 18) && !who->get_legend(TASK_NEWBIE_03, 19))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_ZHOUGUO, "Chu Quốc");
		send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 6, "买椟还珠(5)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 20) && !who->get_legend(TASK_NEWBIE_03, 21))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_CHUGUO, "Sở Quốc");
		if (who->get_save_2("souweisoujiao") < 20)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 10, "孝顺的守卫");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_CHUGUO, 10, "孝顺的守卫(Hoàn thành)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 24) && !who->get_legend(TASK_NEWBIE_03, 25))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_DONGTINGHU, "洞庭湖");
		if (who->get_save_2("zxganliang") >= 20)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_DONGTINGHU, 1, "亡羊补牢(2)(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_DONGTINGHU, 1, "亡羊补牢(2)");
		iLegend++;
	}
	if (who->get_legend(TASK_NEWBIE_03, 26) && !who->get_legend(TASK_NEWBIE_03, 28))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_DONGTINGHU, "洞庭湖");
		if (who->get_legend(TASK_NEWBIE_03, 27))
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_DONGTINGHU, 2, "亡羊补牢(3)(Hoàn thành)");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_DONGTINGHU, 2, "亡羊补牢(3)");
		iLegend++;
	}
	if (who->get_legend(TASK_04, 11) && !who->get_legend(TASK_04, 12))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_HANGUO, "Hàn Quốc");
		if (who->get_save_2("nzdujiaosou") < 20)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_HANGUO, 5, "宫廷的喧闹");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_HANGUO, 5, "宫廷的喧闹(Hoàn thành)");
		iLegend++;
	}
	who->set_save_2("task.story", iLegend); //已经接的剧情任务总数
	return;
}

string send_task_intro(object who, int iFlag, int iTask, int iKind)
{
	int time, x, y, z, status, tasktype = 3, lefttime, task_jq;
	string result, id, name;
	object map, npc, me, item;
	mixed *mxTmp;
	string *npc_info;

	if (mapp(mpTaskDesc[iFlag]) && mapp(mpTaskDesc[iFlag][iTask]) && stringp(mpTaskDesc[iFlag][iTask][iKind]))
	{
		tasktype = 1;
		result = mpTaskDesc[iFlag][iTask][iKind];
	}
	if (stringp(result))
	{
		if (tasktype == 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 3, iTask, iKind, result);
		else if (tasktype == 4) //有任务时间的
		{
			if (lefttime < 0)
				send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, iTask, iKind, "已无剩余时间");
			else
				send_user(who, "%c%c%c%w%w%d%s", 0x51, 1, 4, iTask, iKind, lefttime, result);
		}
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, iTask, iKind, result);
		return result;
	}
	if (iFlag == 1 && iTask == TID_WUYIHUODONG)
	{
		if (iKind == 1)
		{
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    找到东海岛东北方的" HIR "极限穿越审查官\n" BLK "    任务时间:" HIR "花费了%d分钟\n" BLK "miêu tả nhiệm vụ:\n" BLK "    从齐国出发,穿越东海渔村,到达东海岛,去寻找一个名为极限穿越审查官的人,记得找一个高级玩家带着你过去吧,不然,你会抵抗不了那里怪物的攻击!\n" BLK "    拿好这张“极限穿越证明书”,去交给东海岛东北方的极限穿越审查官,你就能拿到他给你的奖励了!\n" BLK "    越快到达目的地,拿到的奖励会越多!\n" BLK "任务奖励:\n" BLK "    战国劳动奖章", gone_time(who->get_save_2("51cuanye.time")) / 60);
		}
		else if (iKind == 2 || iKind == 3)
		{
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    杀100只高于自己等级5级之内的怪\n" BLK "  %d/100\n" BLK "miêu tả nhiệm vụ:\n" BLK "    一分耕耘,一分收获,只要辛苦劳动就会收获丰硕的果实,拿好试炼石,杀满100只高于自己等级5级之内的怪,你就可以回新手村找五一活动指派员领取奖励了.\n" BLK "   切记,一定是高于自己等级5级之内的怪物.\n" BLK "任务奖励:\n" BLK "    战国劳动奖章×3", who->get_save_2("51tiandao.amount"));
		}
	}
	else if (iFlag == 1 && iTask == TID_DODOLOOK)
	{
		if (iKind == 1)
			result = BLK "mục đích nhiệm vụ:\n" BLK "    与魏昭王交谈一下 \n" BLK "miêu tả nhiệm vụ:\n" BLK "    据闻有人在魏国看到过dodolook的行踪,你前去打探一下.倘若寻不到的话,你就去拜访下魏昭王,说不定就是魏昭王把她抓起来了!\n" BLK "任务奖励:\n" BLK "    经验:1000\n" BLK "    潜能:50\n" BLK "    金钱:1000\n" BLK "    物品:行军散5个";
		else if (iKind == 2 || iKind == 3)
			result = BLK "mục đích nhiệm vụ:\n" BLK "    去楚方城寻回玉玺并交给魏昭王\n" BLK "miêu tả nhiệm vụ:\n" BLK "    接受魏昭王的考验:魏昭王的玉玺丢了,如果你能去(楚方城2)帮魏昭王寻回遗失的玉玺,魏昭王将给你一个信物,它将会给你带来意想不到的惊喜.\n" BLK "任务奖励:\n" BLK "    经验:2000\n" BLK "    潜能:50\n" BLK "    金钱:2000\n" BLK "    物品:行军散5个、正气散5个";
	}
	else if (iFlag == 1 && iTask == TID_YUANFEN && who->get_save_2("dodolook_task.npcid"))
	{
		if (!who->get_save_2("dodolook_task.finish"))
		{
			tasktype = 4;
			lefttime = 3600 - gone_time(who->get_save_2("dodolook_task.time"));
			if (lefttime <= 0)
				result = BLK "任务失败";
			else
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    帮助dodolook消灭%s (0/1) \n" BLK "剩余时间%s分钟\n" BLK "miêu tả nhiệm vụ:\n" BLK "    最近%s国(%d,%d)有一个%s,它作祟不知将多少缠绵情侣之间的真爱一点点吞噬掉,你们的任务就是合力消灭他,为人世间的有缘人扫除天敌.任务Hoàn thành后告之dodolook一下!", who->get_save_2("dodolook_task.name"), "%d", who->get_save_2("dodolook_task.country"), who->get_save_2("dodolook_task.x"), who->get_save_2("dodolook_task.y"), who->get_save_2("dodolook_task.name"));
		}
		else
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    帮助dodolook消灭%s (1/1) \n" BLK "miêu tả nhiệm vụ:\n" BLK "    最近%s国(%d,%d)有一个%s,它作祟不知将多少缠绵情侣之间的真爱一点点吞噬掉,你们的任务就是合力消灭他,为人世间的有缘人扫除天敌.任务Hoàn thành后告之dodolook一下!", who->get_save_2("dodolook_task.name"), who->get_save_2("dodolook_task.country"), who->get_save_2("dodolook_task.x"), who->get_save_2("dodolook_task.y"), who->get_save_2("dodolook_task.name"));
	}
	else if (iFlag == 1 && iTask == TID_DAPANG)
	{
		if (who->get_save_2("dapang.count") < who->get_save_2("dapang.total"))
		{
			tasktype = 4;
			lefttime = 1800 - gone_time(who->get_save_2("dapang.time"));
			if (lefttime <= 0)
				result = BLK "任务失败";
			else
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    杀20只%s并告知大胖一声\n" BLK "    %s %d/20\n" BLK "miêu tả nhiệm vụ:\n" BLK "    如今天下世道纷乱不堪,妖魔鬼怪四出肆虐,此乃天理不容.为拯救苍生,你前去" HIR "杀20只%s" BLK ",只望以此来警示那些蠢蠢欲动的妖孽,Hoàn thành此使命还望告知大胖一声.据说" HIR "%s" BLK ".\n" BLK "Còn thừa %s phút\n" BLK "任务奖励:3000金 1000经验 200潜能", name = who->get_save_2("dapang.name"), name, who->get_save_2("dapang.count"), name, who->get_save_2("dapang.where"), "%d");
		}
		else
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    杀20只%s并告知大胖一声\n" BLK "    %s %d/20\n" BLK "miêu tả nhiệm vụ:\n" BLK "    如今天下世道纷乱不堪,妖魔鬼怪四出肆虐,此乃天理不容.为拯救苍生,你前去" HIR "杀20只%s" BLK ",只望以此来警示那些蠢蠢欲动的妖孽,Hoàn thành此使命还望告知大胖一声.据说" HIR "%s" BLK ".\n" BLK "任务奖励:3000金 1000经验 200潜能", name = who->get_save_2("dapang.name"), name, who->get_save_2("dapang.count"), name, who->get_save_2("dapang.where"));
	}
	else if (iFlag == 1 && iTask == TID_REFINE)
	{
		tasktype = 4;
		result = "/sys/user/refine"->send_task_intro(who);
	}
	else if (iFlag == 1 && iTask == TID_CANTUONG)
	{
		tasktype = 4;
		result = "/sys/user/cantuong"->send_task_intro(who);
	}
	else if (iFlag == 1 && iTask == 1)
	{
		if (iKind == 1)
		{
			tasktype = 4;
			if (who->get_save_2("double_time.freeze") > 0)
			{
				lefttime = 0;
				result = sprintf(BLK "Bạn đã đông cứng %d phút thời gian nhân đôi", who->get_save_2("double_time.freeze") / 60);
			}
			else
			{
				lefttime = who->get_double_time() - gone_time(who->get_login_time()) - who->get_game_time();
				result = BLK "Thời gian Kinh nghiệm gấp đôi của bạn còn %d phút";
			}
		}
		else if (iKind == 2)
		{
			tasktype = 4;
			lefttime = get_effect_3(who, EFFECT_MAGIC_CARD);
			result = BLK "Hiệu quả biến thân của bạn còn %d phút";
		}
		else if (iKind == 3 && (lefttime = who->get_save_2("insurance.timeover")) > time())
		{
			mxTmp = localtime(lefttime);
			result = sprintf(BLK "Bảo hiểm sẽ hết hạn vào %d năm %d tháng %d ngày %d giờ", mxTmp[TIME_YEAR], mxTmp[TIME_MON] + 1, mxTmp[TIME_MDAY], mxTmp[TIME_HOUR]);
		}
		else if (iKind == 4)
		{
			//tasktype = 1;
			if (who->get_cashkhoa())
			{
				result = sprintf(BLK "Bạn hiện đang có: %d ngân lượng khóa", who->get_cashkhoa());
			}
		}
	}
	else if (iFlag == 1 && iTask == TID_CRIMINAL && iKind == 1)
	{
		if (who->get_task("criminal.bonus"))
		{
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Tiêu diệt Đào Phạm vừa tẩu thoát khỏi ngục\n" BLK "    Tiêu diệt %s: 1/1.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Trước đó vài ngày có gió bão lớn, làm thiệt hại nhiều vách tường của nhà ngục, làm cho Đào phạm có cơ hội chạy trốn, nghe thám tử hồi báo " HIR "%s " BLK " đang núp ở " HIR "%s (%d,%d) " BLK ", nếu ngươi có thể giúp ta tiêu diệt đào phạm thì đại vương sẽ trọng thưởng\n" BLK "Phần thưởng: 1500 lượng\n",
							 who->get_task("criminal.name"), who->get_task("criminal.name"), who->get_task("criminal.map"), who->get_task("criminal.x"), who->get_task("criminal.y"));
		}
		else if (stringp(id = who->get_task("criminal")) && (npc = find_char(id)) && npc->is_criminal()) // 30 分钟
		{
			tasktype = 4;
			lefttime = 1800 - gone_time(npc->get("birthday"));
			map = get_map_object(get_z(npc));
			name = map ? map->get_name() : "Bản đồ vô danh";
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Tiêu diệt Đào Phạm vừa tẩu thoát khỏi ngục\n" BLK "    Tiêu diệt %s: 0/1 (Thời gian còn %s phút).\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Trước đó vài ngày có gió bão lớn, làm thiệt hại nhiều vách tường của nhà ngục, làm cho Đào phạm có cơ hội chạy trốn, nghe thám tử hồi báo " HIR "%s " BLK " đang núp ở " HIR "%s (%d,%d) " BLK ", nếu ngươi có thể giúp ta tiêu diệt đào phạm thì đại vương sẽ trọng thưởng\n" BLK "Phần thưởng: 1500 lượng\n",
							 npc->get_name(), "%d", npc->get_name(), name, who->get_task("criminal.x"), who->get_task("criminal.y"));
		}
	}
	else if (iFlag == 1 && iTask == TID_ROBBER && iKind == 1)
	{
		if (who->get_task("robber.bonus"))
		{
			result = sprintf(BLK "Tiêu diệt %s (Lượt thứ %d)\n" BLK "mục đích nhiệm vụ:\n" BLK "    Giúp Sư Gia tiêu diệt " HIR "%s" BLK ".\n" BLK "    Tiêu diệt %s: 1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Gần đây có tên tội phạm " HIR "%s" BLK " ở " HIR "%s" BLK " làm đủ mọi chuyện ác, hung hăng ngang ngược\n" BLK "    Hiện tại Nha Môn phòng thủ không đủ, ngươi hãy đi tiêu diệt hắn giùm ta, ta sẽ trọng thưởng\n" BLK "phần thưởng nhiệm vụ:" HIR "500 lượng",
							 who->get_task("robber.name"), who->get_task("robber#") + 1, who->get_task("robber.name"), who->get_task("robber.name"), who->get_task("robber.name"), who->get_task("robber.map"));
		}
		else if (stringp(id = who->get_task("robber")) && (npc = find_char(id)) && npc->is_robber()) // 60 分钟
		{
			tasktype = 4;
			lefttime = 3600 - gone_time(npc->get("birthday"));
			map = get_map_object(get_z(npc));
			name = map ? map->get_name() : "Bản đồ vô danh";
			result = sprintf(BLK "Tiêu diệt %s (Lượt thứ %d)\n" BLK "mục đích nhiệm vụ:\n" BLK "    Giúp Sư Gia tiêu diệt " HIR "%s" BLK ".\n" BLK "    Tiêu diệt %s: 0/1 (Thời gian còn %s phút)\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Gần đây có tên tội phạm " HIR "%s" BLK " ở " HIR "%s" BLK " làm đủ mọi chuyện ác, hung hăng ngang ngược\n" BLK "    Hiện tại Nha Môn phòng thủ không đủ, ngươi hãy đi tiêu diệt hắn giùm ta, ta sẽ trọng thưởng\n" BLK "phần thưởng nhiệm vụ:" HIR "500 lượng",
							 npc->get_name(), who->get_task("robber#") + 1, npc->get_name(), npc->get_name(),
							 "%d", npc->get_name(), name);
		}
	}
	else if (iFlag == 1 && iTask == TID_BANDITI && iKind)
	{
		switch (iKind)
		{
		case 1:
			if (stringp(id = who->get_task("banditi")) && (npc = find_char(id)) && npc->is_banditi()) // 30 分钟
			{
				z = npc->get("xy.z");
				x = npc->get("xy.x");
				y = npc->get("xy.y");
				tasktype = 4;
				lefttime = 1800 - gone_time(npc->get("birthday"));
				map = get_map_object(get_z(npc));
				name = map ? map->get_name() : "Bản đồ vô danh";
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Tiêu diệt ở " HIR "%s(%d,%d)" BLK " vùng thường lui tới " HIR "%s" BLK ".\n" BLK "%s : 0/1  (Còn thừa %s phút).\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Nghe nói ở " HIR "%s(%d,%d)" BLK " vùng phụ cận có đạo tặc %s có ý định cướp bóc thôn ta, hy vọng đại hiệp ra tay trương trợ !",
								 name, x, y, npc->get_name(), npc->get_name(), "%d", name, x, y, npc->get_name());
			}
			else if (who->get_task("banditi_bonus"))
			{
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Tiêu diệt ở " HIR "%s(%d,%d)" BLK " vùng thường lui tới " HIR "%s" BLK ".\n" BLK "%s : 1/1.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Nghe nói ở " HIR "%s(%d,%d)" BLK " vùng phụ cận có đạo tặc " HIR "%s" BLK " có ý định cướp bóc thôn ta, hy vọng đại hiệp ra tay trương trợ !",
								 who->get_task("banditi_map"), who->get_task("banditi_x"), who->get_task("banditi_y"), who->get_task("banditi_name"), who->get_task("banditi_name"), who->get_task("banditi_map"), who->get_task("banditi_x"), who->get_task("banditi_y"), who->get_task("banditi_name"));
			}
			break;
		case 2:
			if (stringp(id = who->get_task("warrior")) && (npc = find_char(id)) && npc->is_warrior()) // 30 分钟
			{
				z = npc->get("xy.z");
				x = npc->get("xy.x");
				y = npc->get("xy.y");
				tasktype = 4;
				lefttime = 600 - gone_time(npc->get("birthday"));
				map = get_map_object(get_z(npc));
				name = map ? map->get_name() : "Bản đồ vô danh";
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Tiêu diệt ở " HIR "%s(%d,%d)" BLK " vùng thường lui tới " HIR "%s" BLK ", lấy được Hoàng Kim Thánh Y.\n" BLK "    Hoàng Kim Thánh Y: 0/1  (Còn thừa %s phút).\n" BLK "Nhiệm vụ hoàn thành : Vệ Đội Trưởng ở Tân Thủ Thôn\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Vệ Đội Trưởng mỗi lần nằm mơ đều thấy mình hoá thành Hoàng Kim Thánh Đấu Sĩ, để hoàn thành giấc mộng hắn triệu tập quần hùng đi tìm giúp, nghe nói Hoàng Kim Thánh Y đang trong tay của một tên Đạo Tặc, nếu đánh bại hắn có thể có được Hoàng Kim Thánh Y",
								 name, x, y, npc->get_name(), "%d");
			}
			else if (who->get_task("warrior_bonus"))
			{
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Tiêu diệt ở " HIR "%s(%d,%d)" BLK " vùng thường lui tới " HIR "%s" BLK ", lấy được Hoàng Kim Thánh Y.\n" BLK "    Hoàng Kim Thánh Y: 1/1\n" BLK "Nhiệm vụ hoàn thành : Vệ Đội Trưởng ở Tân Thủ Thôn\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Vệ Đội Trưởng mỗi lần nằm mơ đều thấy mình hoá thành Hoàng Kim Thánh Đấu Sĩ, để hoàn thành giấc mộng hắn triệu tập quần hùng đi tìm giúp, nghe nói Hoàng Kim Thánh Y đang trong tay của một tên Đạo Tặc, nếu đánh bại hắn có thể có được Hoàng Kim Thánh Y",
								 who->get_task("warrior_map"), who->get_task("warrior_x"), who->get_task("warrior_y"), who->get_task("warrior_name"));
			}
			break;
		}
	}
	else if (iFlag == 1 && iTask == TID_THIEF && iKind)
	{
		if (iKind == who->get_quest("thief.bonus"))
		{
			switch (iKind)
			{
			case 1:
				x = who->get_quest("thief.x");
				y = who->get_quest("thief.y");
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Đến " HIR "%s" BLK " ở " HIR "%d,%d" BLK "vùng, đem " HIR "%s" BLK " giáo huấn(Lượt thứ %d )\n" BLK "Giáo huấn %s: 1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Lão thôn trưởng đêm qua lại lại có một tên %s ăn trộm, tuy không mất gì nghiệm trọng, nhưng không thêt tha thứ\n" BLK "    %s ở tại %s (%d,%d) vùng thường lui tới, ngươi hãy đi giáo huấn %s một chút", id = who->get_quest("thief.map"), x, y, name = who->get_quest("thief.name"), who->get_quest("thief.count") + 1, name, name, name, id, x, y, name);
				break;
			case 4:
				x = who->get_quest("thief.x");
				y = who->get_quest("thief.y");
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Đuổi bắt đào phạm chạy trốn đến " HIR "%s(%d,%d)" BLK " vùng phụ cận " HIR "%s" BLK ", đem về Vật Phẩm bị mất(Lượt thứ %d )\n" BLK "Vật phẩm bị mất: 1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Kẻ trộm %s đêm qua lại xuất hiện!Hắn đã cướp sạch những vật phẩm quý giá!Theo hồi báo cấp dưới nhìn thấy %s ở %s (%d,%d) vùng phụ cận.Nếu %s có thể giúp ta lấy lại vật phẩm bị mất ta sẽ trọng thưởng", id = who->get_quest("thief.map"), x, y, name = who->get_quest("thief.name"), who->get_quest("thief.count") + 1, name, name, id, x, y, NPC_RANK_D->get_respect_2(who));
				break;
			}
		}
		else if (iKind == who->get_quest("thief.flag"))
		{
			switch (iKind)
			{
			case 1:																							 // 2. 失窃任务(人物)
				if (stringp(id = who->get_quest("thief.thief")) && (npc = find_char(id)) && npc->is_thief()) // 30 分钟
				{
					z = who->get_quest("thief.z");
					x = who->get_quest("thief.x");
					y = who->get_quest("thief.y");
					tasktype = 4;
					lefttime = 1800 - gone_time(who->get_quest("thief.time"));
					map = get_map_object(z);
					name = map ? map->get_name() : "Bản đồ vô danh";
					result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Đến " HIR "%s" BLK " ở " HIR "%d,%d" BLK " vùng phụ cận, đem" HIR "%s" BLK " giáo huấn.Thời gian còn %s phút(Lượt thứ %d )\n" BLK "Giáo huấn %s: 0/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Lão thôn tưởng nói đêm qua lại xuất hiện 1 tên %s ăn trộm, tuy không mất gì đáng giá nhưng không thể tha thứ\n" BLK "    %s ở tại %s (%d,%d) vùng thường lui tới, ngươi hãy đi giáo huấn %s một chút", name, x, y, id = npc->get_name(), "%d", who->get_quest("thief.count") + 1, id, id, id, name, x, y, id);
				}
				break;

			case 2: // 1. 失窃任务(物品)
				lefttime = 1800 - gone_time(who->get_quest("thief.time"));
				if (lefttime < 0)
					lefttime = 1;
				tasktype = 4;
				z = who->get_quest("thief.z");
				x = who->get_quest("thief.x");
				y = who->get_quest("thief.y");
				map = get_map_object(z);
				name = map ? map->get_name() : "Bản đồ vô danh";
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Đến " HIR "%s" BLK " ở " HIR "%d,%d" BLK " vùng phụ cận, giúp Bát Cô tìm " HIR "%s" BLK ",Thời gian còn %s phút(Lượt thứ %d )\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Bát Cô ngồi tâm sự kể lể bị mất một vật quý\n" BLK "    Lần này Bát Cô bị mất %s,theo nàng miêu tả rớt tại %s (%d,%d) vùng phụ cận\n" BLK "    Như thế nào ？%s có muốn giúp ta tìm lại vật phẩm này không ？", name, x, y, id = who->get_quest("thief.thief"), "%d", who->get_quest("thief.count") + 1, id, name, x, y, NPC_RANK_D->get_respect_2(who));
				break;

			case 3: // 5. 寻物任务
					//			                if( ( time = 1800 - gone_time( who->get_quest("thief.time") ) ) > 0 )    // 15 分钟
					//			                {
				result = sprintf(BLK "Mục tiêu nhiệm vụ:\n" BLK " Giúp Vương Bộ Đầu mua " HIR " %s " BLK ". (Lượt thứ %d )\n" BLK "Miêu tả nhiệm vụ:\n" BLK " %s , ta vốn muốn mua về %s , nhưng vì công vụ trói buộc bản thân không thể tự do đi mua được , ngươi có thể giúp ta một tay không?\n", id = who->get_quest("thief.thief"), who->get_quest("thief.count") + 1, who->get_name(), id);
				//			                }
				break;

			case 4:																							 // 3. 失窃任务(人物)
				if (stringp(id = who->get_quest("thief.thief")) && (npc = find_char(id)) && npc->is_thief()) // 15 分钟
				{
					z = who->get_quest("thief.z");
					x = who->get_quest("thief.x");
					y = who->get_quest("thief.y");
					tasktype = 4;
					lefttime = 1800 - gone_time(who->get_quest("thief.time"));
					map = get_map_object(z);
					name = map ? map->get_name() : "Bản đồ vô danh";
					result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Đuổi bắt Đào phạm đến " HIR "%s(%d,%d)" BLK " vùng phụ cận " HIR "%s" BLK ", đem vật phẩm quý giá trở về .Thời gian còn %s phút(Lượt thứ %d )\n" BLK "Vật Phẩm bị mất:0/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Kẻ trộm %s đêm qua lại xuất hiện!Hắn đã cướp sạch những vật phẩm quý giá!Theo cấp dưới báo nhìn thấy %s ở %s (%d,%d).Nếu %s có thể giúp ta tìm lại vật phẩm bị mất, ta sẽ trọng thưởng", id = map->get_name(), x, y, name = npc->get_name(), "%d", who->get_quest("thief.count") + 1, name, name, id, x, y, NPC_RANK_D->get_respect_2(who));
				}
				break;
			}
		}
	}

	else if (iFlag == 1 && iTask == TID_VALENTINE && iKind)
	{
		if (iKind == who->get_quest("valentine.flag"))
		{
			switch (iKind)
			{
			case 1:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    找唐门的唐老爷子求取神秘的种子\n" BLK "miêu tả nhiệm vụ:\n" BLK "    2月14是一个很神奇的日子,据说在这期间内,心怀爱意的小伙子凭借自己的诚心和实力,就有可能得到不同寓意的玫瑰.你想得到玫瑰的话,就去找唐老爷子求取传说中神秘的种子吧!顺便帮我把这个包裹带给唐老爷子,记住这个包裹可是千万不能打开的喔!\n" BLK "任务奖励:经验500");
				break;
			case 2:
				lefttime = 1800 - gone_time(who->get_quest("valentine.time"));
				if (lefttime < 0)
					lefttime = 1;
				tasktype = 4;
				x = who->get_quest("valentine.x");
				y = who->get_quest("valentine.y");
				z = who->get_quest("valentine.z");

				map = get_map_object(z);
				name = map ? map->get_name() : "Bản đồ vô danh";
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去%s国(%d,%d)杀飞贼拿到神秘的种子,任务剩余时间%s分钟.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    你带来的包裹唐老爷子已经收下了,但是仅有的一袋神秘种子在几日前已经被偷走了,据我们的线报称偷走种子的贼似乎在%s国(%d,%d)出没.如果你能拿回种子,自然就归你了!\n" BLK "任务奖励:经验500 潜能10", name, x, y, "%d", name, x, y);
				break;
			case 3:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    将神秘的种子交给月老,并询问他有关开花之事.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    好不容易才拿到了神秘的种子,赶紧去交给周国的月老吧.\n" BLK "任务奖励:经验500");
				break;
			case 4:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    询问新手村智慧老人关于种子开花之事.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    月老说新手村的智慧老人能知百事,通天下,你不妨去问问他,或许他知道要怎么做才能让种子开花.\n" BLK "任务奖励:经验500 潜能10");
				break;
			case 5:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去找到桃花源的忘情婆婆\n" BLK "miêu tả nhiệm vụ:\n" BLK "    2月14是一个很神奇的日子,据说在这期间内,心怀爱意的小伙子凭借自己的诚心和实力,就有可能得到不同寓意的玫瑰.看来你也是一位怀抱着诚意来的姑娘,那么,你去桃花源找到忘情婆婆吧,她会告诉你怎样才能得到巧克力的!\n" BLK "任务奖励:经验500");
				break;
			case 6:
				lefttime = 1800 - gone_time(who->get_quest("valentine.time"));
				if (lefttime < 0)
					lefttime = 1;
				tasktype = 4;
				x = who->get_quest("valentine.x");
				y = who->get_quest("valentine.y");
				z = who->get_quest("valentine.z");

				map = get_map_object(z);
				name = map ? map->get_name() : "Bản đồ vô danh";
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去%s国(%d,%d)给忘情婆婆找来胭脂、梳子、头钗,任务剩余时间%s分钟.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    唉,想当年忘情婆婆也是万人迷的天使级少女啊,情人节快到了,她也想打扮一下呢,你去一趟%s国(%d,%d),去城外找找那些流氓,他们身上或许就带着用来讨好女孩子的胭脂、梳子和头钗.\n" BLK "任务奖励:经验500 潜能10", name, x, y, "%d", name, x, y);
				break;
			case 7:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    将巧克力豆交给红娘.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    情人节最重要的一点就是男生送女生玫瑰花,女生送男生巧克力!忘情婆婆给了你巧克力豆,红娘应该知道怎样把巧克力豆做成巧克力,你去问问她吧!\n" BLK "任务奖励:经验500");
				break;
			case 8:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    询问巧克力精灵做巧克力的方法.\n" BLK "miêu tả nhiệm vụ:\n" BLK "    红娘说在新手村外的西北方有一个万丈深渊,这悬崖旁生活着一个巧克力精灵,它一定会知道巧克力的做法,你赶紧起程去吧!\n" BLK "任务奖励:经验500 潜能10");
				break;
			}
		}
	}
	else if (iFlag == 1 && iTask == TID_QIXI && iKind)
	{
		if (iKind == who->get_save_2("qixi.flag"))
		{
			switch (iKind)
			{
				/*				case 1:
					result = sprintf(BLK"mục đích nhiệm vụ:\n"BLK"    领取号码牌,与有缘人一起去找月老\n" BLK"miêu tả nhiệm vụ:\n"BLK"    上天给了牛郎织女一次机会,只要抓住这次机会,那么他们以后就不用再隔河相望了,他们需要一对有缘人的帮助,所以,只要找到与我的"HIR "号码牌"BLK"相同号码的有缘人,我们就能给他们帮助了,因此,我决定赶快找到我的有缘人,然后再去向"HIR "月老"BLK"打听一下情况.\n"BLK"任务奖励:\n"BLK"    经验 2000");        
					break;*/
			case 3:
				if (who->get_gender() == 1)
					result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    打探王母娘娘行踪\n" BLK "miêu tả nhiệm vụ:\n" BLK "    原来牛郎和织女天河相隔是因为王母娘娘,但是要帮助他们首先必须要找到王母娘娘才行,据说有个喜欢" HIR "云游" BLK "的人见过王母娘娘,不知道是不是真的,先过去打听一下.我先询问一下队伍中的" HIR "有缘人" BLK ",把提示信息综合起来说不定能 lấy được 新的线索.\n" BLK "任务奖励:\n" BLK "    金钱 500\n" BLK "    经验 50");
				else
					result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    打探王母娘娘行踪\n" BLK "miêu tả nhiệm vụ:\n" BLK "    原来牛郎和织女天河相隔是因为王母娘娘,但是要帮助他们首先必须要找到王母娘娘才行,据说有个卖珍稀品的" HIR "商人" BLK "见过王母娘娘,不知道是不是真的,先过去打听一下.我先询问一下队伍中的" HIR "有缘人" BLK ",把提示信息综合起来说不定能 lấy được 新的线索.\n" BLK "任务奖励:\n" BLK "    金钱 500\n" BLK "    经验 50");
				break;
				/*				case 5:
					if (who->get_gender() == 1)
						result = sprintf(BLK"mục đích nhiệm vụ:\n"BLK"    找寻王母娘娘\n" BLK"miêu tả nhiệm vụ:\n"BLK"    据服装店老板说,有一个十分喜欢"HIR "云游"BLK"的人无意间提到曾经见过王母娘娘,看来只要找到这个人就能知晓王母娘娘的下落了.最好问一下"HIR "同伴"BLK"有没有线索\n"BLK"任务奖励:\n"BLK"    金钱 5000\n"BLK"    经验 3000");
					else
						result = sprintf(BLK"mục đích nhiệm vụ:\n"BLK"    找寻王母娘娘\n" BLK"miêu tả nhiệm vụ:\n"BLK"    据服装店老板说,有一个卖珍稀品的"HIR "商人"BLK"无意间提到曾经见过王母娘娘,看来只要找到这个人就能知晓王母娘娘的下落了.最好问一下"HIR "同伴"BLK"有没有线索\n"BLK"任务奖励:\n"BLK"    金钱 5000\n"BLK"    经验 3000");
					break;
				case 7:
					result = sprintf(BLK"mục đích nhiệm vụ:\n"BLK"    找寻王母娘娘\n" BLK"miêu tả nhiệm vụ:\n"BLK"    据云游商人说,王母娘娘曾经现身昆仑"HIR "瑶池"BLK".以昆仑浓厚的灵气,王母娘娘一定会在那里多呆一段时间的.现在赶过去,说不定就能找到王母娘娘.\n"BLK"任务奖励:\n"BLK"    金钱 5000\n"BLK"    经验 3000");
					break;*/
			case 9:
				lefttime = 1800 - gone_time(who->get_save_2("qixi.time"));
				//					if ( lefttime < 0 )
				//						lefttime = 1;
				tasktype = 4;
				x = who->get_save_2("qixi.x");
				y = who->get_save_2("qixi.y");
				z = who->get_save_2("qixi.z");

				map = get_map_object(z);
				name = map ? map->get_name() : "Bản đồ vô danh";
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    击败灵兽,获取灵药,任务剩余时间%s分钟.\n" BLK "    灵药(0/1)\n" BLK "miêu tả nhiệm vụ:\n" BLK "    找到云游商人的时候,王母娘娘刚好不在,云游商人说只要为他采集一味灵药,就会告诉王母娘娘行踪. 听说在%s国(%d,%d)有这种灵药,不如去走一趟吧,娘娘说灵药有强大的灵兽守护,那我先去做好准备,然后再过去.\n" BLK "任务奖励:\n" BLK "    金钱 500\n" BLK "    经验 50", "%d", name, x, y);
				break;
			case 10:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    击败灵兽,获取灵药.\n" BLK "    灵药(1/1)\n" BLK "miêu tả nhiệm vụ:\n" BLK "    已经Hoàn thành,回去找云游商人吧!");
				break;
			case 12:
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    将王母娘娘赐予的仙丹给牛郎织女\n" BLK "miêu tả nhiệm vụ:\n" BLK "    经过千辛万苦,终于将王母娘娘需要的灵药采了回来,王母娘娘给了我们仙丹,她说只要将仙丹给(ALT+G)" HIR "牛郎和织女" BLK ",他们以后就能幸福的生活在一起了,嗯!相信他们已经等急了,我还是赶快给他们送去吧.\n" BLK "任务奖励:\n" BLK "    金钱 50000\n" BLK "    经验 50000\n" BLK "    情比金坚戒");
				break;
			}
		}
	}
	else if (iFlag == 1 && iTask == TID_ESCORT && iKind && iKind == who->get_quest("escort.flag"))
	{

		if (iKind == 1) // 1. Nhiệm vụ áp tiêu(物品)
		{
			tasktype = 4;
			lefttime = 2400 - gone_time(who->get_quest("escort.time")); // 40 分钟

			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Vận chuyển Vật phẩm quý giá đến %s giao cho %s (Còn thừa %s phút)\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Trước đó vài ngày có người uỷ thác ta đem rương bạc tới " HIR "%s Quốc " BLK " giao cho " HIR "%s " BLK ", ta thật sự không rảnh rổi, ngươi hãy đi đi !\n", name = who->get_quest("escort.city"), id = who->get_quest("escort.name"), "%d", name, id);
		}
		else if (iKind == 2) // 2. Nhiệm vụ áp tiêu(人物)
		{
			tasktype = 4;
			lefttime = 2400 - gone_time(who->get_quest("escort.time"));

			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    Hộ tống %s đến " HIR "%s" BLK " (Còn thừa %s phút)\n" BLK "miêu tả nhiệm vụ:\n" BLK "    Vị đại nhân này là " HIR "%s " BLK " thân hữu, hắn hy vọng có thể nhìn thấy thân hữu, nhưng do đường xá xa xôi và hiểm ác, mà hắn thì không biết võ công, cho nên ngươi hãy hộ tống hắn đi " HIR "%s Quốc (%d,%d) ở %s" BLK ".\n", who->get_quest("escort.npcname"), name = who->get_quest("escort.name"), "%d", name, who->get_quest("escort.city"), who->get_quest("escort.x"), who->get_quest("escort.y"), name);
		}
		else if (iKind == 3)
		{
			lefttime = gone_time(who->get_quest("escort.time"));
			npc_info = who->get_quest("escort.npcinfo");
			if (!arrayp(npc_info))
			{
				result = BLK "任务失败!请放弃任务!";
			}
			else
				result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    护送镖王小超人到%s%s处\n" BLK "任务时间:" HIR "花费了%d分%d秒\n" BLK "任务Hoàn thành人:%s\n" BLK "miêu tả nhiệm vụ:\n" BLK "    欢迎你参加本届小超人杯“镖王争霸战”,这是速度与运气的竞争,智慧与技术的比拼,大奖在向你招手,荣誉在你头顶盘旋!是不是真正的战国镖王,只有试过才知道.\n" BLK "    尉迟老镖头让你尽快把镖王小超人送到%s的%s(%s)处,Hoàn thành时间越短越能拿到更好的奖励.赶快去吧!\n" BLK "任务奖励:\n" BLK "    3分钟之内Hoàn thành任务奖励55000金\n" BLK "    3分钟至4分钟Hoàn thành任务奖励45000金\n" BLK "    4分钟以上Hoàn thành任务奖励30000金\n", npc_info[0], npc_info[1], lefttime / 60, lefttime % 60, npc_info[0], npc_info[0], npc_info[1], npc_info[2]);
		}
	}
	else if (iFlag == 1 && who->get_save_2("marrytask") && iTask == TID_HONGNIANG && iKind == 1)
	{
		tasktype = 4;
		lefttime = 3600 - gone_time(who->get_save_2("marrytask.time"));
		result = sprintf(BLK "mục đích nhiệm vụ:\n    " BLK "Trợ giúp Hồng Nương giáo huấn %s ( còn thừa thời gian %s phút )\n" BLK "miêu tả nhiệm vụ:\n    " BLK "%s quốc (%d,%d) có một tên %s, tự xưng “Thiên hạ đệ nhất”. Hắn hạn Hồng Nương trong vòng 3 ngày rời đi chu quốc, ba ngày sau nếu thấy Hồng Nương còn đang ở đó, hắn sẽ dẫn người tới tạp Hồng Nương chiêu bài. Ngươi tiến đến đem hắn giáo huấn một đốn, miễn cho hắn như thế càn rỡ!\n" BLK "Phần thưởng nhiệm vụ : Khóa Đồng Tâm", who->get_save_2("marrytask.name"), "%d", who->get_save_2("marrytask.country"), who->get_save_2("marrytask.x1"), who->get_save_2("marrytask.y1"), who->get_save_2("marrytask.name"));
	}
	else if (iFlag == 1 && who->get_save_2("master_hide") && iTask == TID_MASTER_HIDE && iKind == 1)
	{
		tasktype = 4;
		lefttime = 2400 - gone_time(who->get_save_2("master_hide.time"));
		result = sprintf(BLK "Nhiệm vụ:\n    " BLK "Tiêu diệt %s (Thời gian còn %s phút)\n" BLK "Nhiệm vụ miêu tả:\n    " BLK "Gần đây Tây Vực phái đến một Người tự xưng là Thiên Hạ Vô Địch %s, thật là kiêu ngạo, hắn còn dám đến Bổn môn khiêu khích đòi gây chiến, nếu không tiêu diệt hắn thì sẽ khiến thiên hạ chê cười.Sư phụ lệnh ngươi đến %s Quốc (%d,%d) tiêu diệt hắn rồi báo cho Sư phụ biết !\n" BLK "Phần thưởng nhiệm vụ:\n" BLK "    Ngân lượng:1500000 \n" BLK "    Kinh nghiệm:%d \n" BLK "    Tiềm năng:%d\n", who->get_save_2("master_hide.name"), "%d", who->get_save_2("master_hide.name"), who->get_save_2("master_hide.country"), who->get_save_2("master_hide.x1"), who->get_save_2("master_hide.y1"), who->get_save_2("master_hide.exp"), who->get_save_2("master_hide.potential"));
	}
	else if (iFlag == 1 && who->get_fam_name() && iTask == TID_MASTER && iKind > 0 && iKind == who->get_save_2("mastertask.type"))
	{
		TASK_MASTER_D->send_task_intro(who);
	}
	else if (iFlag == 1 && iTask == TID_CHAIN)
	{
		CHAIN_D->send_task_intro(who);
	}
	else if (iFlag == 2 && iTask == TID_ZHOUGUO && iKind == 15)
	{
		tasktype = 4;
		task_jq = 2;
		lefttime = 2400 - gone_time(who->get_quest("escort.time"));
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "   将镖银送往韩国城外梨花村里的马大汉(还剩余%s分钟)\n" BLK "任务Hoàn thành人:\n" HIR "    韩国城外梨花村的马大汉\n" BLK "miêu tả nhiệm vụ:\n" BLK "    尉迟老镖头那本是可以提供给你们一个赚钱的机会,可近些日子,有一些无能无德之鼠辈,打着给他帮忙的旗号,从他那骗走了不少镖银,所以,以后凡是想在尉迟老镖头那里运镖的人,都得先通过他的测试这一关.\n" BLK "    你先替他把这镖银运到韩城外梨花村的马大汉处,这次他不收你的押金,但你切记,在运镖过程中是不能使用驿站或道具法术等传送功能,否则你的任务就会失败!\n" BLK "任务奖励:\n" BLK "    金钱:60000", "%d");
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_00 && iKind)
	{
		tasktype = 1;
		//        	result =  sprintf(BLK "mục đích nhiệm vụ:\n"BLK"    到达新手村之后,将百合仙子的信件交给新手村的神仙爷爷.神仙爷爷就在新手村的村口.从天坛下去之后,沿着青石小径一直走就可以找到.\n" BLK "任务Hoàn thành人:\n"BLK"    新手村神仙爷爷\n"BLK "miêu tả nhiệm vụ:\n"BLK"    做人做仙都得善良,懂得知恩图报,小仙女没有来仙灵岛之前,神仙爷爷非常照顾他,她现在托我送信给神仙爷爷,应该是挂念他了吧,神仙爷爷一定也非常的想念小仙女,真为他们的亲情感动.\n" BLK "任务奖励:\n" BLK "    经验:200点\n" BLK "    潜能:20\n" BLK "    金钱:500\n" BLK "    半小时双倍经验\n");
		result = sprintf(BLK "Mục tiêu nhiệm vụ:\n" BLK " Mỗi đại hiệp đến Tân Thủ Thôn đều đến báo với Thần Tiên Gia Gia. Thần Tiên Gia Gia chính là cổng vào của Tân Thủ Thôn. Sau khi từ Thiên Đàn xuống, đi dọc theo con đường nhỏ đá xanh đi thẳng là có thể đến.\n" BLK "Người hoàn thành nhiệm vụ: \n" BLK " Thần Tiên Gia Gia ở Tân Thủ Thôn \n" BLK "Miêu tả nhiệm vụ:\n" BLK " Hoan nghênh ngươi đã đến Chiến Quốc, đây là Tân Thủ Thôn, mỗi đại hiệp đến thôn này đều phải báo cho Thần Tiên Gia Gia biết, Thần Tiên Gia Gia chính là cổng vào của Tân Thủ Thôn. Sau khi từ Thiên Đàn xuống, đi dọc theo con đường nhỏ đá xanh đi thẳng là có thể đến.\n" BLK "Phần thưởng nhiệm vụ:\n" BLK " Kinh nghiệm: 20\n" BLK " Tiềm năng: 20\n" BLK "500 lượng\n" BLK "Nửa tiếng gấp đôi Kinh nghiệm\n ");
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 1)
	{
		tasktype = 1;
		if (!who->get_legend(TASK_NEWBIE_00, 4))
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    在武器店老板处索取一柄木剑\n" BLK "木剑 0/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    刚刚来到这个村子,还不太熟悉新手村的环境.神仙爷爷告诉我,顺着他身旁的这条青石小径一直往上走,过了当铺,就到武器店了,等找到武器店老板,他会给我要的东西.要到了得赶快把这些东西交给神仙爷爷,他急着用呢!\n" BLK "奖励选择:初学者木刀、长木棍、竹矛\n");
		if (who->get_legend(TASK_NEWBIE_00, 4) && !who->get_legend(TASK_NEWBIE_00, 5))
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    在武器店老板处索取一柄木剑\n" BLK "木剑1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    刚刚来到这个村子,还不太熟悉新手村的环境.神仙爷爷告诉我,顺着他身旁的这条青石小径一直往上走,过了当铺,就到武器店了,等找到武器店老板,他会给我要的东西.要到了得赶快把这些东西交给神仙爷爷,他急着用呢!\n" BLK "奖励选择:初学者木刀、长木棍、竹矛\n");
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 2)
	{
		tasktype = 1;
		if (who->get_legend(TASK_NEWBIE_00, 3))
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去新手村外杀5只" HIR "小山鸡" BLK "后向" HIR "武器店老板" BLK "汇报\n" BLK "    小山鸡 5/5\n" BLK "任务Hoàn thành人:\n" BLK "    新手村武器店老板\n" BLK "miêu tả nhiệm vụ:\n" BLK "    在这个新手村外,分布着一些很奇怪的动物,他们不像普通的小鸡、小兔、稻草人一样的友善,他们会攻击人,除掉这些怪物是我们一直以来在做的事情.现在,如果我能够除掉5只小山鸡,一定会拿到很多的奖励!\n" BLK "    他说武器店老板会很乐意给我一些东西的,叫我杀完后去找武器店老板.\n" BLK "任务奖励:\n" BLK "    经验:350点\n" BLK "    潜能:30点\n" BLK "    金钱:800\n" BLK "    物品:桔子×5\n");
		else
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去新手村外杀5只" HIR "小山鸡" BLK "后向" HIR "武器店老板" BLK "汇报\n" BLK "    小山鸡 %d/5\n" BLK "任务Hoàn thành人:\n" BLK "    新手村武器店老板\n" BLK "miêu tả nhiệm vụ:\n" BLK "    在这个新手村外,分布着一些很奇怪的动物,他们不像普通的小鸡、小兔、稻草人一样的友善,他们会攻击人,除掉这些怪物是我们一直以来在做的事情.现在,如果我能够除掉5只小山鸡,一定会拿到很多的奖励!\n" BLK "    他说武器店老板会很乐意给我一些东西的,叫我杀完后去找武器店老板.\n" BLK "任务奖励:\n" BLK "    经验:350点\n" BLK "    潜能:30点\n" BLK "    金钱:800\n" BLK "    物品:桔子×5\n", who->get_save_2("new_sj"));
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 4)
	{
		tasktype = 1;
		if (who->get_legend(TASK_NEWBIE_01, 5))
		{
			if (!objectp(item = present("Tàng Bảo Đồ", who, 1, MAX_CARRY)) || item->is_xunbao() != 1)
				result = BLK "mục đích nhiệm vụ:\n" BLK "    去新手村外的最东边,找到藏宝图.\n" BLK "Tàng Bảo Đồ  0/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    首先我要找到一张藏宝图,它应该就在新手村最东边的瀑布旁,那儿还有个陈老头,我怀疑陈老头是故意安排在那监视我的,心里有点寒寒的,我得提防着他.想想,还真有点刺激!等我找到藏宝图后,回到防具店老板那里,他会告诉我下一条线索!\n" BLK "任务奖励:\n" BLK "    120点经验\n" BLK "    10点潜能";
			else
				result = BLK "mục đích nhiệm vụ:\n" BLK "    去新手村外的最东边,找到藏宝图.\n" BLK "Tàng Bảo Đồ  1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    首先我要找到一张藏宝图,它应该就在新手村最东边的瀑布旁,那儿还有个陈老头,我怀疑陈老头是故意安排在那监视我的,心里有点寒寒的,我得提防着他.想想,还真有点刺激!等我找到藏宝图后,回到防具店老板那里,他会告诉我下一条线索!\n" BLK "任务奖励:\n" BLK "    120点经验\n" BLK "    10点潜能";
		}
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 5)
	{
		tasktype = 1;
		if (who->get_legend(TASK_NEWBIE_01, 7) && !who->get_legend(TASK_NEWBIE_01, 8))
			result = BLK "mục đích nhiệm vụ:\n" BLK "    利用藏宝图找到家族玉佩\n" BLK "家族玉佩  0/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    防具店老板叫我拿着手上的藏宝图一直向南走,到清溪最突出那个岛上好好找找,就在草丛里(88,62),找到那里,就可以挖宝了!这个任务比找到藏宝图的奖励会更多,所以,我愿意接受这个挑战.等我找到宝物后,去找药店老板,他会给我想要的东西!\n" BLK "任务奖励:\n" BLK "    200点经验\n" BLK "    40点潜能\n" BLK "    1000金\n" BLK "    行军散×10";
		else if (who->get_legend(TASK_NEWBIE_01, 7) && who->get_legend(TASK_NEWBIE_01, 8))
			result = BLK "mục đích nhiệm vụ:\n" BLK "    利用藏宝图找到家族玉佩\n" BLK "家族玉佩  1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    防具店老板叫我拿着手上的藏宝图一直向南走,到清溪最突出那个岛上好好找找,就在草丛里(88,62),找到那里,就可以挖宝了!这个任务比找到藏宝图的奖励会更多,所以,我愿意接受这个挑战.等我找到宝物后,去找药店老板,他会给我想要的东西!\n" BLK "任务奖励:\n" BLK "    200点经验\n" BLK "    40点潜能\n" BLK "    1000金\n" BLK "    行军散×10";
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 8)
	{
		tasktype = 1;
		if (who->get_legend(TASK_NEWBIE_01, 14) && !who->get_legend(TASK_NEWBIE_01, 16))
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去新手村外杀小野兔,拿到铁锤,交给修理店老板\n" BLK "铁锤:%d/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    杂货店老板答应了修理店老板,给他找到一把铁锤,据他打听来的消息,分布在新手村外、幽谷、清溪的小野兔身上带着铁锤,但是对于我来说,他们的力量有点强大,所以这对我来说可是个大的挑战,我喜欢挑战!\n" BLK "任务奖励:\n" BLK "    300经验\n" BLK "    50点潜能\n" BLK "    2500金\n" BLK "    5正气散", who->get_legend(TASK_NEWBIE_01, 15) ? 1 : 0);
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 14)
	{
		tasktype = 1;
		if (who->get_legend(TASK_NEWBIE_02, 1) && (!who->get_legend(TASK_NEWBIE_02, 2) || !who->get_legend(TASK_NEWBIE_02, 3)))
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去新手村外杀野兔,拿到火焰石,把火焰石交给当铺老板\n" BLK "火焰石:%d/5\n" BLK "miêu tả nhiệm vụ:\n" BLK "    刚从仙灵岛来到这儿,还真需要一些行军散,这些都是对我的气血非常有用的.对吗？既然当铺老板很愿意给我一些行军散,虽然他叫我帮他弄5个火焰石来,但是这些都难不倒我!只要去新手村外杀掉那些讨厌的野兔,就可能会有火焰石了.\n" BLK "任务奖励:行军散10包,经验100点", who->get_save_2("huoyanshi"));
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 15)
	{
		tasktype = 1;
		if (who->get_legend(TASK_NEWBIE_02, 4) && (!who->get_legend(TASK_NEWBIE_02, 5) || !who->get_legend(TASK_NEWBIE_02, 6)))
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    杀死10只小山鸡\n" BLK "小山鸡 %d/10\n" BLK "miêu tả nhiệm vụ:\n" BLK "    村外的那些山鸡太可恶了,昨天居然跑到村子里的店铺偷吃!武器店老板气坏了,叫我去帮他杀死那帮盗贼.他叫我顺着这条路一直走,只要出了这个村子,我就能见到那些可恶的山鸡了.只要我能杀死10只小山鸡,他会给我很多奖励哦!\n" BLK "任务奖励:经验110点,潜能10点,600金,长木剑、布拳套(二选一)", who->get_save_2("newbie_sanji"));
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 16)
	{
		tasktype = 1;
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    给小鸡咕咕找到它爱吃的饲料\n" BLK "小鸡饲料 %d/1\n" BLK "任务Hoàn thành人:新手村的小鸡咕咕\n" BLK "miêu tả nhiệm vụ:\n" BLK "    小鸡咕咕十分兴奋地在我面前拍打着翅膀,好像是期待着我给它某些东西一样.是肚子饿了吗？\n" BLK "    也许我该到村外转转,说不定能找到小鸡喜欢的饲料也说不定.听说" HIR "去往巴丘路上的刘大叔" BLK "就有小鸡咕咕爱吃的饲料.\n" BLK "任务奖励:100点经验\n" BLK "          5个桔子", who->get_legend(TASK_NEWBIE_02, 8) ? 1 : 0);
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 19)
	{
		tasktype = 1;
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    帮那个奇怪的稻草人找一个能替代他脑袋的灵石回来.\n" BLK "灵石:%d/1\n" BLK "任务Hoàn thành人:新手村的" HIR "奇怪的稻草人\n" BLK "miêu tả nhiệm vụ:\n" BLK "    稻草人整个身体除了一堆稻草外就只有布片和木杆.因此常常遭到那些该死的乌鸦嘲笑没大脑.稻草人虽然十分生气,但却不得不承认这是事实.如果它也像人类一样有一个大脑的话,那些乌鸦也不敢再嘲笑它了.\n" BLK "    稻草人曾经听说" HIR "清溪的丁大叔" BLK "在长白天池中取到了不少的灵石,如果用将那些灵石作为其脑袋的话应该相当不错.可惜稻草人没有脚,不能自己亲自去.如果我能帮它的忙,稻草人会十分感激我.\n" BLK "任务奖励:180点经验\n" BLK "          30点潜能", who->get_legend(TASK_NEWBIE_00, 18) ? 1 : 0);
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 20)
	{
		tasktype = 1;
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    杀死清溪的恶将胡\n" BLK "恶将胡 %d/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    老村长果然是尽心尽力,这恶将胡仗着自己家有钱有势,勾结地方官府,欺压百姓,至今逍遥法外.我要替天行道,杀死恶将胡.恶将胡就在清溪的清溪北野,最东边的地方.\n" BLK "任务奖励:550点经验、60点潜能、2600金、10个桔子", who->get_legend(TASK_NEWBIE_02, 15) ? 1 : 0);
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 21)
	{
		tasktype = 1;
		if (!who->get_legend(TASK_NEWBIE_02, 20))
			result = BLK "mục đích nhiệm vụ:\n" BLK "    将天下名酒“百步仙”带给陈老头\n" BLK "百步仙 0/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    据说有一壶天下名酒‘百步仙’就收藏在李老汉的家中.陈老头多次登门讨酒,但都遭到了拒绝.也许我能帮上陈老头的忙,将酒讨回来.\n" BLK "    李老汉就在村子的正北方,在去往巴丘的路上很容易就能找到.\n" BLK "任务奖励:200经验,3000金,5张回城符";
		else
			result = BLK "mục đích nhiệm vụ:\n" BLK "    将天下名酒“百步仙”带给陈老头\n" BLK "百步仙 1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    据说有一壶天下名酒‘百步仙’就收藏在李老汉的家中.陈老头多次登门讨酒,但都遭到了拒绝.也许我能帮上陈老头的忙,将酒讨回来.\n" BLK "    李老汉就在村子的正北方,在去往巴丘的路上很容易就能找到.\n" BLK "任务奖励:200经验,3000金,5张回城符";
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01 && iKind == 22)
	{
		tasktype = 1;
		if (!who->get_legend(TASK_NEWBIE_02, 29))
			result = BLK "mục đích nhiệm vụ:\n" BLK "    消灭恶霸李麻子,然后回黄大叔处复命.\n" BLK "恶霸李麻子 0/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    那黄大叔居然是一个密探,真了不起,他找到了恶霸李麻子,但是身份特殊,自己不能露脸,所以请我帮这个忙,我也算是个正义之士,就帮了他这个忙吧!恶霸李麻子在新手村外的蝴蝶岗,地方不大,很容易就找得到,到时候黄大叔还会给我丰厚的报酬!\n" BLK "任务奖励:600点经验,50点潜能,1500金";
		else
			result = BLK "mục đích nhiệm vụ:\n" BLK "    消灭恶霸李麻子,然后回黄大叔处复命.\n" BLK "恶霸李麻子 1/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    那黄大叔居然是一个密探,真了不起,他找到了恶霸李麻子,但是身份特殊,自己不能露脸,所以请我帮这个忙,我也算是个正义之士,就帮了他这个忙吧!恶霸李麻子在新手村外的蝴蝶岗,地方不大,很容易就找得到,到时候黄大叔还会给我丰厚的报酬!\n" BLK "任务奖励:600点经验,50点潜能,1500金";
	}
	else if (iFlag == 2 && iTask == TID_NEWBIE_01)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	//        else
	//        if ( iFlag==2 && iTask == TID_BAQIU && iKind==1 )
	//        {
	//        	tasktype = 1;
	//		if ( !who->get_legend(TASK_NEWBIE_02, 19) )
	//	        	result = sprintf(BLK"mục đích nhiệm vụ:\n"BLK"    帮李老汉寻找5根小麦,藉此交换他手中的名酒“百步仙”\n"BLK"小麦 %d/5\n"BLK"miêu tả nhiệm vụ:\n"BLK"    在苦苦的哀求下,顽固的李老汉终于同意交出他珍藏的名酒“百步仙”.但是他所提出的条件便是用巴丘附近的子母蛙拥有的小麦来交换.也许我该到巴丘一带看看,说不定会有所收获.\n"BLK"任务奖励:220点经验,10点潜能,名酒百步仙",who->get_save_2("baqiu_xiaomai"));
	//	        else
	//	        	result = BLK"mục đích nhiệm vụ:\n"BLK"    帮李老汉寻找5根小麦,藉此交换他手中的名酒“百步仙”\n"BLK"小麦 5/5\n"BLK"miêu tả nhiệm vụ:\n"BLK"    在苦苦的哀求下,顽固的李老汉终于同意交出他珍藏的名酒“百步仙”.但是他所提出的条件便是用巴丘附近的子母蛙拥有的小麦来交换.也许我该到巴丘一带看看,说不定会有所收获.\n"BLK"任务奖励:220点经验,10点潜能,名酒百步仙";
	//        }
	else if (iFlag == 2 && iTask == TID_HUANJIAO && iKind == 1)
	{
		tasktype = 1;
		result = BLK "mục đích nhiệm vụ:\n" BLK "    找到孟大伯,并劝他回家\n" BLK "miêu tả nhiệm vụ:\n" BLK "    孟氏和孟大伯为搬家的问题吵了一架,孟大伯早上出门后一直没回来,现在也到了该吃饭的时候了,孟大伯肯定一个人在外面抽闷烟,不想回家.唉,夫妻间哪能没有一点矛盾呢,我去劝劝他,让他早点回来吧.\n" BLK "任务奖励:150点经验,20点潜能";
	}
	else if (iFlag == 2 && iTask == TID_YEWAI && iKind == 1)
	{
		tasktype = 1;
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    找到3罐蜜糖交给李小毛\n" BLK "蜜糖:%d/3\n" BLK "任务Hoàn thành人:" HIR "清溪的李小毛\n" BLK "miêu tả nhiệm vụ:\n" BLK "    小朋友都这么可爱,喜欢吃甜甜的东西,我小时候也是一样哦,蜂蜜真的好甜哦,既然他从来没吃过,那我就帮他去找几罐吧." HIR "清溪和幽谷" BLK "附近的" HIR "蜜蜂" BLK "都会随身带些蜜糖在身上,应该很容易就能取得.\n" BLK "任务奖励:380点经验\n" BLK "          20点潜能\n" BLK "          8只桔子", who->get_save_2("xiaomao_fengmi"));
	}
	else if (iFlag == 2 && iTask == TID_YEWAI && iKind == 2)
	{
		tasktype = 1;
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    消灭8只小蜜蜂\n" BLK "小蜜蜂 %d/8\n" BLK "miêu tả nhiệm vụ:\n" BLK "    蹊跷……整个清溪弥漫着一种神秘的气氛……那些平日和善的小蜜蜂突然成群结队的攻击周围的行人、百姓,他们的毒性与攻击力似乎提升了不少,在他们背后是不是有神秘的组织操纵着,还是他们已经被迷惑了心智？当务之急还是得消灭他们,不然会造成更大的伤亡.看来孔老头应该知道点内幕.\n" BLK "任务奖励:370点经验,30点潜能,2000金,5包辟毒散", who->get_save_2("xiaomifeng"));
	}
	else if (iFlag == 2 && iTask == TID_CHUGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_ZHOUGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_DONGTINGHU && iKind == 1)
	{
		tasktype = 1;
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    给庄辛找到20包干粮\n" BLK "干粮 %d/20\n" BLK "任务Hoàn thành人:" HIR "庄辛" BLK "miêu tả nhiệm vụ:\n" BLK "    庄辛劝说楚王考烈王不再重用身边四臣,而被楚王考烈王驳回,便与楚王考烈王达成协议,暂迁至赵国居住,但一路上风餐露宿,需要充饥的干粮,听说上庸关的刀兵、剑兵囤储了一批.\n" BLK "任务奖励:经验900点,潜能40点,1000金", who->get_save_2("zxganliang"));
	}
	else if (iFlag == 2 && iTask == TID_DONGTINGHU && iKind == 2)
	{
		tasktype = 1;
		result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    杀掉%s\n" BLK "任务Hoàn thành人:" HIR "楚国大将军项燕\n" BLK "miêu tả nhiệm vụ:\n" BLK "    庄辛劝说楚王考烈王不再重用身边四臣,而被楚王考烈王驳回,便与楚王考烈王达成协议,暂迁至赵国居住,庄辛本想近日内即起程,结果大王省悟,令庄辛杀掉只知奢侈淫乐的%s,庄辛委托我去做此事,看来我得尽快替他办好!那%s就在%s.杀死他后报告给楚国大将军就是了!大王一定会按功行赏的.\n" BLK "任务奖励:经验900点,潜能100点,1800金,10级武器", name = who->get_save_2("zxkillnpc"), name, name, who->get_save_2("zxkillnpc1"));
	}
	else if (iFlag == 2 && iTask == TID_HANGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_WEIGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 1 && iTask == TID_ORG)
	{
		tasktype = 2;
		result = "/sys/sys/manager"->get_task_str(who, iKind);
	}
	else if (iFlag == 2 && iTask == TID_QIGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_QINGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_YANGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_ZHAOGUO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_DONGHAIDAO)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_YUNMENZE)
	{
		tasktype = 1;
		result = "quest/taskdesc"->get_task_str(who, iTask, iKind);
	}
	else if (iFlag == 2 && iTask == TID_MAOSHAN)
	{
		tasktype = 1;
		if (iKind == 2)
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    去弯道2找到镜子,交给茅真人\n" BLK "镜子 %d/1\n" BLK "miêu tả nhiệm vụ:\n" BLK "    韩王安中了一种已经被茅山禁止很多年的邪术---游魂之术.普天之下只有茅山的茅真人才可以解这种邪术.茅真人要作法解开这邪术还需要一件已经遗失多时的镜子,这镜子就在弯道2附近.我得赶快去把这面镜子找回来,如果韩王安梦中游魂的次数达到二十一次的话,韩王安的生命也就完结了,所以我已经没有什么时间了. \n    路途凶险,我最好是结伴而行.\n" BLK "任务奖励:经验16000 潜能260 金钱17000", who->get_legend(TASK_23, 9) ? 1 : 0);
		else if (iKind == 5)
			result = sprintf(BLK "mục đích nhiệm vụ:\n" BLK "    杀掉20只恶灵,回来向茅真人复命\n" BLK "恶灵 %d/20\n" BLK "miêu tả nhiệm vụ:\n" BLK "    终于把马宁杀掉了,虽然已经破解了游魂之术,但是还必须把韩王安之前丢失的20个灵魂吸回来,韩王安才可以得教.韩王安的灵魂被封在灵谷洞最底层的恶灵身上.杀掉那20个恶灵,让茅真人用之前我找回来的镜子把韩王安的灵魂吸回来.\n" BLK "任务奖励:经验17000 潜能280 金钱19000", who->get_save_2("mzreling"));
	}
	if (stringp(result))
	{
		if (tasktype == 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 3, iTask, iKind, result);
		else if (tasktype == 4) //有任务时间的
		{
			if (task_jq == 2)
			{
				if (lefttime < 0)
					send_user(who, "%c%c%c%w%w%s", 0x51, 2, 3, iTask, iKind, "已无剩余时间");
				else
					send_user(who, "%c%c%c%w%w%d%s", 0x51, 2, 4, iTask, iKind, lefttime, result);
			}
			else
			{
				if (lefttime < 0)
					send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, iTask, iKind, "已无剩余时间");
				else
					send_user(who, "%c%c%c%w%w%d%s", 0x51, 1, 4, iTask, iKind, lefttime, result);
			}
		}
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, iTask, iKind, result);
	}
	return result;
}

void get_task_intro(object who, string arg)
{
	int iFlag, iTask, iKind;

	if (sscanf(arg, "%d %d %d", iFlag, iTask, iKind) != 3)
		return;
	send_task_intro(who, iFlag, iTask, iKind);
}
void task_giveup(object who, string arg)
{
	int iType, iTask, iKind;
	object npc, item;

	if (sscanf(arg, "%d %d %d", iType, iTask, iKind) != 3)
		return;
	if (iType == 1 && iTask == TID_WUYIHUODONG)
	{
		if (iKind == 1)
		{
			if (item = present("极限穿越证明书", who, 1, MAX_CARRY))
			{
				item->remove_from_user();
				destruct(item);
			}
			who->delete_save_2("51cuanye.time");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_WUYIHUODONG, 1, "");
		}
		else if (iKind == 2)
		{
			if (item = present("试炼石", who, 1, MAX_CARRY))
			{
				item->remove_from_user();
				destruct(item);
			}
			who->delete_save_2("51tiandao.accept");
			who->delete_save_2("51tiandao.amount");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_WUYIHUODONG, 2, "");
		}
	}
	else if (iType == 1 && iTask == TID_YUANFEN)
	{
		"npc/party/dodolook"->task_giveup(who);
	}
	else if (iType == 1 && iTask == TID_DAPANG)
	{
		who->delete_save_2("dapang");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "");
	}
	else if (iType == 1 && iTask == TID_BANDITI && iKind == 1)
	{
		TASK_BANDITI_D->task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_BANDITI && iKind == 2)
	{
		TASK_BANDITI_D->gold_task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_THIEF)
	{
		TASK_THIEF_D->task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_VALENTINE)
	{
		"/sys/party/valentine"->task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_QIXI)
	{
		"/sys/party/qixi"->task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_REFINE)
	{
		"/sys/user/refine"->task_giveup(who);
	}
	else if (iType == 1 && iTask == TID_ORG)
	{
		"/sys/sys/manager"->task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_CRIMINAL && iKind == 1)
	{
		"npc/00/8006"->task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_ROBBER && iKind == 1)
	{
		TASK_ROBBER_D->task_giveup(who, iKind);
	}
	else if (iType == 1 && iTask == TID_MASTER)
	{
		TASK_MASTER_D->task_giveup(who);
	}
	else if (iType == 1 && iTask == TID_CHAIN)
	{
		CHAIN_D->task_giveup(who);
	}
	else if (iType == 1 && iTask == TID_ESCORT)
	{
		TASK_ESCORT_D->task_giveup(who);
	}
	else if (iType == 2)
		TASK_LEGEND_D->task_giveup(who, iType, iTask, iKind);
	else if (iType == 1 && iTask == TID_MASTERFIGHT && iKind == 1)
	{
		who->delete_save_2("masterfight");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTERFIGHT, 1, "");
	}
	else if (iType == 1 && who->get_save_2("marrytask") && !who->get_save_2("marrytask.finish") && iTask == TID_HONGNIANG && iKind == 1)
	{
		if (objectp(npc = find_char(who->get_save_2("marrytask.target"))) && npc->is_marry_task())
		{
			npc->remove_from_scene();
			destruct(npc);
		}
		who->delete_save_2("marrytask");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_HONGNIANG, 1, "");
	}
	else if (iType == 1 && who->get_save_2("master_hide") && iTask == TID_MASTER_HIDE && iKind == 1)
	{
		"sys/task/master"->master_hide_giveup(who, npc);
	}
}
