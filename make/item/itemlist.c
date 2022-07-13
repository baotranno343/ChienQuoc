
// 变量：物品文件列表
mapping ItemList = ([    // 以下列表由 makelist.c 生成
        "梅花" : "\"/item/30/3001\"",
        "兰花" : "\"/item/30/3002\"",
        "文竹" : "\"/item/30/3003\"",
        "菊花" : "\"/item/30/3004\"",
        "玫瑰花" : "\"/item/30/3005\"",
        "茉莉花" : "\"/item/30/3006\"",
        "牡丹花" : "\"/item/30/3007\"",
        "桃花" : "\"/item/30/3008\"",
        "山茶花" : "\"/item/30/3009\"",
        "芍药花" : "\"/item/30/3010\"",
        "牵牛花" : "\"/item/30/3011\"",
        "大红花" : "\"/item/30/3012\"",
        "水仙花" : "\"/item/30/3013\"",
        "海棠花" : "\"/item/30/3014\"",
        "百合花" : "\"/item/30/3015\"",
        "丁香花" : "\"/item/30/3016\"",
        "红茶" : "\"/item/31/3101\"",
        "绿茶" : "\"/item/31/3102\"",
        "茉莉花茶" : "\"/item/31/3103\"",
        "普洱茶" : "\"/item/31/3104\"",
        "铁观音茶" : "\"/item/31/3105\"",
        "龙井茶" : "\"/item/31/3106\"",
        "云雾茶" : "\"/item/31/3107\"",
        "铁观音茶叶" : "\"/item/31/3115\"",
        "云雾茶叶" : "\"/item/31/3117\"",
        "米酒" : "\"/item/31/3150\"",
        "黄酒" : "\"/item/31/3151\"",
        "老酒" : "\"/item/31/3152\"",
        "烧刀子" : "\"/item/31/3153\"",
        "汾酒" : "\"/item/31/3154\"",
        "杜康酒" : "\"/item/31/3155\"",
        "女儿红" : "\"/item/31/3156\"",
        "西瓜" : "\"/item/32/3280\"",
        "香蕉" : "\"/item/32/3281\"",
        "桔子" : "\"/item/32/3282\"",
        "苹果" : "\"/item/32/3283\"",
        "梨" : "\"/item/32/3284\"",
        "桃子" : "\"/item/32/3285\"",
        "杨梅" : "\"/item/32/3286\"",
        "葡萄" : "\"/item/32/3287\"",
        "龙眼" : "\"/item/32/3288\"",
        "荔枝" : "\"/item/32/3289\"",
        "烧饼" : "\"/item/33/3301\"",
        "煎饼" : "\"/item/33/3302\"",
        "红豆糕" : "\"/item/33/3303\"",
        "绿豆糕" : "\"/item/33/3304\"",
        "牛肉干" : "\"/item/33/3310\"",
        "烤肉串" : "\"/item/33/3311\"",
        "烤番薯" : "\"/item/33/3320\"",
        "豆腐干" : "\"/item/33/3321\"",
        "臭豆腐" : "\"/item/33/3322\"",
        "炒瓜子" : "\"/item/33/3323\"",
        "炒花生" : "\"/item/33/3324\"",
        "冰糖葫芦" : "\"/item/33/3325\"",
        "铁铲" : "\"/item/34/3401\"",
        "锄头" : "\"/item/34/3402\"",
        "铁犁" : "\"/item/34/3403\"",
        "镰刀" : "\"/item/34/3404\"",
        "钉耙" : "\"/item/34/3405\"",
        "草叉" : "\"/item/34/3406\"",
        "铁锤" : "\"/item/34/3410\"",
        "木槌" : "\"/item/34/3411\"",
        "凿子" : "\"/item/34/3412\"",
        "刨子" : "\"/item/34/3413\"",
        "锯子" : "\"/item/34/3414\"",
        "簸箕" : "\"/item/34/3420\"",
        "小木桶" : "\"/item/34/3421\"",
        "柱香" : "\"/item/34/3450\"",
        "蜡烛" : "\"/item/34/3451\"",
        "檀香" : "\"/item/34/3452\"",
        "黄纸" : "\"/item/34/3453\"",
        "纸钱" : "\"/item/34/3454\"",
        "朱砂" : "\"/item/34/3455\"",
        "法笔" : "\"/item/34/3456\"",
        "小香炉" : "\"/item/34/3460\"",
        "鹤嘴炉" : "\"/item/34/3461\"",
        "铁锅" : "\"/item/35/3501\"",
        "陶碗" : "\"/item/35/3502\"",
        "金碗" : "\"/item/35/3503\"",
        "竹筷" : "\"/item/35/3504\"",
        "银筷" : "\"/item/35/3505\"",
        "碟子" : "\"/item/35/3506\"",
        "盘子" : "\"/item/35/3507\"",
        "勺子" : "\"/item/35/3510\"",
        "水瓢" : "\"/item/35/3511\"",
        "菜刀" : "\"/item/35/3512\"",
        "剪刀" : "\"/item/35/3513\"",
        "茶壶" : "\"/item/35/3514\"",
        "打火石" : "\"/item/35/3515\"",
        "胭脂" : "\"/item/35/3550\"",
        "水粉" : "\"/item/35/3551\"",
        "敷面粉" : "\"/item/35/3552\"",
        "红印纸" : "\"/item/35/3553\"",
        "发刷" : "\"/item/35/3560\"",
        "粉扑" : "\"/item/35/3561\"",
        "发夹" : "\"/item/35/3562\"",
        "铜镜" : "\"/item/35/3563\"",
        "手镜" : "\"/item/35/3564\"",
        "锣" : "\"/item/36/3601\"",
        "鼓" : "\"/item/36/3602\"",
        "钹" : "\"/item/36/3603\"",
        "梆子" : "\"/item/36/3604\"",
        "笛子" : "\"/item/36/3605\"",
        "唢呐" : "\"/item/36/3606\"",
        "萧" : "\"/item/36/3607\"",
        "竽" : "\"/item/36/3608\"",
        "筝" : "\"/item/36/3609\"",
        "琵琶" : "\"/item/36/3610\"",
        "二胡" : "\"/item/36/3611\"",
        "“一筒”" : "\"/item/37/3701\"",
        "“二筒”" : "\"/item/37/3702\"",
        "“三筒”" : "\"/item/37/3703\"",
        "“四筒”" : "\"/item/37/3704\"",
        "“五筒”" : "\"/item/37/3705\"",
        "“六筒”" : "\"/item/37/3706\"",
        "“七筒”" : "\"/item/37/3707\"",
        "“八筒”" : "\"/item/37/3708\"",
        "“九筒”" : "\"/item/37/3709\"",
        "“一条”" : "\"/item/37/3711\"",
        "“二条”" : "\"/item/37/3712\"",
        "“三条”" : "\"/item/37/3713\"",
        "“四条”" : "\"/item/37/3714\"",
        "“五条”" : "\"/item/37/3715\"",
        "“六条”" : "\"/item/37/3716\"",
        "“七条”" : "\"/item/37/3717\"",
        "“八条”" : "\"/item/37/3718\"",
        "“九条”" : "\"/item/37/3719\"",
        "“一万”" : "\"/item/37/3721\"",
        "“二万”" : "\"/item/37/3722\"",
        "“三万”" : "\"/item/37/3723\"",
        "“四万”" : "\"/item/37/3724\"",
        "“五万”" : "\"/item/37/3725\"",
        "“六万”" : "\"/item/37/3726\"",
        "“七万”" : "\"/item/37/3727\"",
        "“八万”" : "\"/item/37/3728\"",
        "“九万”" : "\"/item/37/3729\"",
        "“东风”" : "\"/item/37/3731\"",
        "“南风”" : "\"/item/37/3732\"",
        "“西风”" : "\"/item/37/3733\"",
        "“北风”" : "\"/item/37/3734\"",
        "“红中”" : "\"/item/37/3735\"",
        "“发财”" : "\"/item/37/3736\"",
        "“白板”" : "\"/item/37/3737\"",
        "“帅”" : "\"/item/37/3750\"",
        "“仕”" : "\"/item/37/3751\"",
        "“相”" : "\"/item/37/3752\"",
        "“車”" : "\"/item/37/3753\"",
        "“馬”" : "\"/item/37/3754\"",
        "“炮”" : "\"/item/37/3755\"",
        "“兵”" : "\"/item/37/3756\"",
        "“将”" : "\"/item/37/3760\"",
        "“士”" : "\"/item/37/3761\"",
        "“象”" : "\"/item/37/3762\"",
        "“车”" : "\"/item/37/3763\"",
        "“马”" : "\"/item/37/3764\"",
        "“砲”" : "\"/item/37/3765\"",
        "“卒”" : "\"/item/37/3766\"",
        "黑棋子" : "\"/item/37/3780\"",
        "白棋子" : "\"/item/37/3781\"",
        "象棋棋盘" : "\"/item/37/3790\"",
        "象棋残局" : "\"/item/37/3791\"",
        "围棋棋盘" : "\"/item/37/3792\"",
        "围棋残局" : "\"/item/37/3793\"",
        "白纸" : "\"/item/38/3850\"",
        "墨块" : "\"/item/38/3851\"",
        "毛笔" : "\"/item/38/3852\"",
        "砚台" : "\"/item/38/3853\"",
        "信封" : "\"/item/38/3854\"",
        "信件" : "\"/item/38/3855\"",
        "情信" : "\"/item/38/3856\"",
        "王府信件" : "\"/item/38/3857\"",
        "请柬" : "\"/item/38/3858\"",
        "竹子" : "\"/item/49/4901\"",
        "竹蜻蜓" : "\"/item/49/4902\"",
        "小风车" : "\"/item/49/4903\"",
        "小泥人" : "\"/item/49/4904\"",
        "泥块" : "\"/item/49/4905\"",
        "冰块" : "\"/item/49/4906\"",
        "雕刻刀" : "\"/item/49/4907\"",
        "柳条" : "\"/item/49/4908\"",
        "花环" : "\"/item/49/4909\"",
        "木板" : "\"/item/49/4910\"",
        "玉石" : "\"/item/49/4940\"",
        "玉玺" : "\"/item/49/4980\"",
        "官印" : "\"/item/49/4981\"",
        "印章" : "\"/item/49/4982\"",
        "兵符" : "\"/item/49/4983\"",
        "令箭" : "\"/item/49/4984\"",
        "令旗" : "\"/item/49/4985\"",
        "残缺橙晶石" : "\"/item/89/8901\"",
        "残缺烟白晶石" : "\"/item/89/8902\"",
        "残缺灰晶石" : "\"/item/89/8903\"",
        "残缺朱红晶石" : "\"/item/89/8904\"",
        "残缺白晶石" : "\"/item/89/8905\"",
        "残缺玉白晶石" : "\"/item/89/8906\"",
        "残缺碧绿晶石" : "\"/item/89/8907\"",
        "残缺墨玉晶石" : "\"/item/89/8908\"",
        "残缺青晶石" : "\"/item/89/8909\"",
        "残缺绿晶石" : "\"/item/89/8910\"",
        "残缺天青晶石" : "\"/item/89/8911\"",
        "残缺红晶石" : "\"/item/89/8912\"",
        "残缺黑晶石" : "\"/item/89/8913\"",
        "残缺赤红晶石" : "\"/item/89/8914\"",
        "残缺蓝晶石" : "\"/item/89/8915\"",
        "残缺靛青晶石" : "\"/item/89/8916\"",
        "残缺紫红晶石" : "\"/item/89/8917\"",
        "残缺青叶晶石" : "\"/item/89/8918\"",
        "残缺琥珀晶石" : "\"/item/89/8919\"",
        "残缺紫晶石" : "\"/item/89/8920\"",
        "残缺黄晶石" : "\"/item/89/8921\"",
        "残缺玉心" : "\"/item/89/8922\"",
        "残缺补天石" : "\"/item/89/8923\"",
        "行军散" : "\"/item/91/9100\"",
        "活络丸" : "\"/item/91/9101\"",
        "造化丹" : "\"/item/91/9102\"",
        "正气散" : "\"/item/91/9110\"",
        "安神丸" : "\"/item/91/9111\"",
        "补心丹" : "\"/item/91/9112\"",
        "救急丹" : "\"/item/91/9120\"",
        "活心丹" : "\"/item/91/9121\"",
        "再造丸" : "\"/item/91/9125\"",
        "砒霜粉" : "\"/item/91/9130\"",
        "鹤顶红粉" : "\"/item/91/9131\"",
        "萤光粉" : "\"/item/91/9135\"",
        "辟毒散" : "\"/item/91/9140\"",
        "清心丹" : "\"/item/91/9145\"",
        "天王散" : "\"/item/91/9150\"",
        "九转混天丹" : "\"/item/std/0088\"",
        "气脉丹" : "\"/item/91/9160\"",
        "周天丹" : "\"/item/91/9161\"",
        "逍遥散" : "\"/item/91/9162\"",
        "金桑散" : "\"/item/91/9163\"",
        "紫心丹" : "\"/item/91/9164\"",
        "归元丹" : "\"/item/91/9165\"",
        "八仙丹" : "\"/item/91/9166\"",
        "紫参丹" : "\"/item/91/9167\"",
        "培元丹" : "\"/item/91/9170\"",
        "通神丹" : "\"/item/91/9171\"",
        "御风丹" : "\"/item/91/9172\"",
        "保和丹" : "\"/item/91/9173\"",
        "红炎丹" : "\"/item/91/9174\"",
        "玄清丹" : "\"/item/91/9175\"",
        "左归丹" : "\"/item/91/9176\"",

        "大学" : "\"/item/97/9701\"",
        "中庸" : "\"/item/97/9702\"",
        "论语" : "\"/item/97/9703\"",
        "孟子" : "\"/item/97/9704\"",
        "诗经" : "\"/item/97/9705\"",
        "尚书" : "\"/item/97/9706\"",
        "礼记" : "\"/item/97/9707\"",
        "周易" : "\"/item/97/9708\"",
        "春秋" : "\"/item/97/9709\"",
        "轩辕本记" : "\"/item/97/9710\"",
        "十洲记" : "\"/item/97/9711\"",
        "周书" : "\"/item/97/9712\"",
        "九歌" : "\"/item/97/9713\"",
        "天问" : "\"/item/97/9714\"",
        "古镜记" : "\"/item/97/9715\"",
        "归藏" : "\"/item/97/9716\"",
        "龙鱼河图" : "\"/item/97/9717\"",
        "四季图·春" : "\"/item/97/9720\"",
        "四季图·夏" : "\"/item/97/9721\"",
        "四季图·秋" : "\"/item/97/9722\"",
        "四季图·冬" : "\"/item/97/9723\"",
        "写意花草·梅" : "\"/item/97/9724\"",
        "写意花草·兰" : "\"/item/97/9725\"",
        "写意花草·菊" : "\"/item/97/9726\"",
        "写意花草·竹" : "\"/item/97/9727\"",
        "荷塘月色图" : "\"/item/97/9728\"",
        "碧水鸳鸯图" : "\"/item/97/9729\"",
        "云山飞瀑图" : "\"/item/97/9730\"",
        "百凤朝凰图" : "\"/item/97/9731\"",
        "天女散花图" : "\"/item/97/9732\"",
        "白泽图" : "\"/item/97/9733\"",
        "龙纹玉佩" : "\"/item/97/9750\"",
        "凤纹玉佩" : "\"/item/97/9751\"",
        "虎纹玉佩" : "\"/item/97/9752\"",
        "雀纹玉佩" : "\"/item/97/9753\"",
        "鸳鸯玉佩" : "\"/item/97/9754\"",
        "和氏璧" : "\"/item/97/9755\"",
        "青花鱼纹盘" : "\"/item/97/9770\"",
        "青铜古镜" : "\"/item/97/9771\"",

        "海盐" : "\"/item/99/9911\"",
        "桑麻" : "\"/item/99/9912\"",
        "珍珠" : "\"/item/99/9913\"",
        "大枣" : "\"/item/99/9921\"",
        "水果" : "\"/item/99/9922\"",
        "灵芝" : "\"/item/99/9923\"",
        "花椒" : "\"/item/99/9931\"",
        "剌绣" : "\"/item/99/9932\"",
        "玉雕" : "\"/item/99/9933\"",
        "柿饼" : "\"/item/99/9941\"",
        "油漆" : "\"/item/99/9942\"",
        "人参" : "\"/item/99/9943\"",
      "朱砂粉" : "\"/item/99/9951\"",
        "石材" : "\"/item/99/9952\"",
        "银器" : "\"/item/99/9953\"",
        "皮革" : "\"/item/99/9961\"",
        "玳瑁" : "\"/item/99/9962\"",
        "黄金" : "\"/item/99/9963\"",
        "板栗" : "\"/item/99/9971\"",
        "烤鸭" : "\"/item/99/9972\"",
        "漆器" : "\"/item/99/9973\"",

        "符纸" : "\"/item/std/0401\"",    // 以下部分手工输入
        "回城符" : "\"/item/std/0407\"",
        "回门符" : "\"/item/std/0408\"",
        "飞行符" : "\"/item/std/0409\"",
        "僵尸符" : "\"/item/std/0413\"",
        "鹤顶红" : "\"/item/std/5211\"",
        "软筋散" : "\"/item/std/5215\"",
        "迷神散" : "\"/item/std/5216\"",
        "麻沸散" : "\"/item/std/5219\"",
        "阵旗" : "\"/item/std/0591\"",
        "宝石碎片" : "\"/item/std/8900\"",
        "随机技能进阶书" : "BOOK_FILE->get_book_file()",
        "随机秘籍" : "BOOK_FILE->get_book_file_2()",
        "随机残缺宝石" : "sprintf(\"/item/89/%%d\", 8901+random(23))",  
        "随机配方" :  "\"/sys/item/product\"->get_random_product()",             
        "30级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(1)",             
        "40级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(2)",             
        "50级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(8)",             
        "55级随机配方" :  "\"/quest/product2\"->get_random_level_blue_product(55,55)",             
        "60级随机配方" :  "\"/quest/product2\"->get_random_level_product(60,60)",             
        "65级随机配方" :  "\"/quest/product2\"->get_random_level_blue_product(65,65)",             
        "70级随机配方" :  "\"/quest/product2\"->get_random_level_product(70,70)",             
        "75级随机配方" :  "\"/quest/product2\"->get_random_level_blue_product(75,75)",             
        "80级随机配方" :  "\"/quest/product2\"->get_random_level_product(80,80)",             
        "85级随机配方" :  "\"/quest/product2\"->get_random_level_blue_product(85,85)",             
        "90级随机配方" :  "\"/quest/product2\"->get_random_level_product(90,90)",             
        "95级随机配方" :  "\"/quest/product2\"->get_random_level_blue_product(95,95)",             
        "100级随机配方" :  "\"/quest/product2\"->get_random_level_product(100,100)",             
        "105级随机配方" :  "\"/quest/product2\"->get_random_level_blue_product(105,105)",             
        "110级随机配方" :  "\"/quest/product2\"->get_random_level_product(110,110)",             
        "115级随机配方" :  "\"/quest/product2\"->get_random_level_blue_product(115,115)",             
        "120级随机配方" :  "\"/quest/product2\"->get_random_level_product(120,120)",             
        "40-50级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(3)",             
        "40-60级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(7)",             
        "50-80级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(4)",             
        "60-90级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(5)",             
        "80-120级随机配方" :  "\"/sys/item/product\"->get_random_drop_product(6)",             

        "爪00" : "\"/item/70/0002\"",  "爪10" : "\"/item/70/0010\"",  "爪20" : "\"/item/70/0020\"",  "爪30" : "\"/item/70/0030\"",  "爪40" : "\"/item/70/0040\"",  "爪50" : "\"/item/70/0050\"",
        "暗10" : "\"/item/71/0001\"",  "暗10" : "\"/item/71/0010\"",  "暗20" : "\"/item/71/0020\"",  "暗30" : "\"/item/71/0030\"",  "暗40" : "\"/item/71/0040\"",  "暗50" : "\"/item/71/0050\"",
        "刀00" : "\"/item/72/0001\"",  "刀10" : "\"/item/72/0010\"",  "刀20" : "\"/item/72/0020\"",  "刀30" : "\"/item/72/0030\"",  "刀40" : "\"/item/72/0040\"",  "刀50" : "\"/item/72/0050\"",
        "剑00" : "\"/item/76/0002\"",  "剑10" : "\"/item/76/0010\"",  "剑20" : "\"/item/73/0020\"",  "剑30" : "\"/item/73/0030\"",  "剑40" : "\"/item/73/0040\"",  "剑50" : "\"/item/73/0050\"",
        "枪00" : "\"/item/74/0002\"",  "枪10" : "\"/item/74/0010\"",  "枪20" : "\"/item/74/0020\"",  "枪30" : "\"/item/74/0030\"",  "枪40" : "\"/item/74/0040\"",  "枪50" : "\"/item/74/0050\"",
        "棍00" : "\"/item/75/0002\"",  "棍10" : "\"/item/75/0010\"",  "棍20" : "\"/item/75/0020\"",  "棍30" : "\"/item/75/0030\"",  "棍40" : "\"/item/75/0040\"",  "棍50" : "\"/item/75/0050\"",
        "杖00" : "\"/item/76/0001\"",  "杖10" : "\"/item/76/0010\"",  "杖20" : "\"/item/76/0020\"",  "杖30" : "\"/item/76/0030\"",  "杖40" : "\"/item/76/0040\"",  "杖50" : "\"/item/76/0050\"",

        "爪+30" : "\"/item/70/1030\"",  "爪+40" : "\"/item/70/1040\"",  "爪+50" : "\"/item/70/1050\"",
        "暗+30" : "\"/item/71/1030\"",  "暗+40" : "\"/item/71/1040\"",  "暗+50" : "\"/item/71/1050\"",
        "刀+30" : "\"/item/72/1030\"",  "刀+40" : "\"/item/72/1040\"",  "刀+50" : "\"/item/72/1050\"",
        "剑+30" : "\"/item/73/1030\"",  "剑+40" : "\"/item/73/1040\"",  "剑+50" : "\"/item/73/1050\"",
        "枪+30" : "\"/item/74/1030\"",  "枪+40" : "\"/item/74/1040\"",  "枪+50" : "\"/item/74/1050\"",
        "棍+30" : "\"/item/75/1030\"",  "棍+40" : "\"/item/75/1040\"",  "棍+50" : "\"/item/75/1050\"",
        "杖+30" : "\"/item/76/1030\"",  "杖+40" : "\"/item/76/1040\"",  "杖+50" : "\"/item/76/1050\"",

        "M衣00" : "\"/item/60/0001\"",  "M衣10" : "\"/item/60/0010\"",  "M衣20" : "\"/item/60/0020\"",  "M衣30" : "\"/item/60/0030\"",  "M衣40" : "\"/item/60/0040\"",  "M衣50" : "\"/item/60/0050\"",
        "F衣00" : "\"/item/61/0001\"",  "F衣10" : "\"/item/61/0010\"",  "F衣20" : "\"/item/61/0020\"",  "F衣30" : "\"/item/61/0030\"",  "F衣40" : "\"/item/61/0040\"",  "F衣50" : "\"/item/61/0050\"",
        "M帽00" : "\"/item/65/0001\"",  "M帽10" : "\"/item/65/0010\"",  "M帽20" : "\"/item/65/0020\"",  "M帽30" : "\"/item/65/0030\"",  "M帽40" : "\"/item/65/0040\"",  "M帽50" : "\"/item/65/0050\"",
        "F帽00" : "\"/item/66/0001\"",  "F帽10" : "\"/item/66/0010\"",  "F帽20" : "\"/item/66/0020\"",  "F帽30" : "\"/item/66/0030\"",  "F帽40" : "\"/item/66/0040\"",  "F帽50" : "\"/item/66/0050\"",
        "饰00" : "\"/item/86/0001\"",  "饰10" : "\"/item/86/0010\"",  "饰20" : "\"/item/86/0020\"",  "饰30" : "\"/item/86/0030\"",  "饰40" : "\"/item/86/0040\"",  "饰50" : "\"/item/86/0050\"",
        "带00" : "\"/item/87/0001\"",  "带10" : "\"/item/87/0010\"",  "带20" : "\"/item/87/0020\"",  "带30" : "\"/item/87/0030\"",  "带40" : "\"/item/87/0040\"",  "带50" : "\"/item/87/0050\"",
        "鞋00" : "\"/item/88/0001\"",  "鞋10" : "\"/item/88/0010\"",  "鞋20" : "\"/item/88/0020\"",  "鞋30" : "\"/item/88/0030\"",  "鞋40" : "\"/item/88/0040\"",  "鞋50" : "\"/item/88/0050\"",

        "M衣A+30" : "\"/item/60/1030\"",  "M衣A+40" : "\"/item/60/1040\"",  "M衣A+50" : "\"/item/60/1050\"",
        "F衣A+30" : "\"/item/61/1030\"",  "F衣A+40" : "\"/item/61/1040\"",  "F衣A+50" : "\"/item/61/1050\"",
        "M帽A+30" : "\"/item/65/1030\"",  "M帽A+40" : "\"/item/65/1040\"",  "M帽A+50" : "\"/item/65/1050\"",
        "F帽A+30" : "\"/item/66/1030\"",  "F帽A+40" : "\"/item/66/1040\"",  "F帽A+50" : "\"/item/66/1050\"",
        "饰A+30" : "\"/item/86/1030\"",  "饰A+40" : "\"/item/86/1040\"",  "饰A+50" : "\"/item/86/1050\"",
        "带A+30" : "\"/item/87/1030\"",  "带A+40" : "\"/item/87/1040\"",  "带A+50" : "\"/item/87/1050\"",
        "鞋A+30" : "\"/item/88/1030\"",  "鞋A+40" : "\"/item/88/1040\"",  "鞋A+50" : "\"/item/88/1050\"",
        "M衣B+30" : "\"/item/60/2030\"",  "M衣B+40" : "\"/item/60/2040\"",  "M衣B+50" : "\"/item/60/2050\"",
        "F衣B+30" : "\"/item/61/2030\"",  "F衣B+40" : "\"/item/61/2040\"",  "F衣B+50" : "\"/item/61/2050\"",
        "M帽B+30" : "\"/item/65/2030\"",  "M帽B+40" : "\"/item/65/2040\"",  "M帽B+50" : "\"/item/65/2050\"",
        "F帽B+30" : "\"/item/66/2030\"",  "F帽B+40" : "\"/item/66/2040\"",  "F帽B+50" : "\"/item/66/2050\"",
        "饰B+30" : "\"/item/86/2030\"",  "饰B+40" : "\"/item/86/2040\"",  "饰B+50" : "\"/item/86/2050\"",
        "带B+30" : "\"/item/87/2030\"",  "带B+40" : "\"/item/87/2040\"",  "带B+50" : "\"/item/87/2050\"",
        "鞋B+30" : "\"/item/88/2030\"",  "鞋B+40" : "\"/item/88/2040\"",  "鞋B+50" : "\"/item/88/2050\"",
        "M衣C+30" : "\"/item/60/3030\"",  "M衣C+40" : "\"/item/60/3040\"",  "M衣C+50" : "\"/item/60/3050\"",
        "F衣C+30" : "\"/item/61/3030\"",  "F衣C+40" : "\"/item/61/3040\"",  "F衣C+50" : "\"/item/61/3050\"",
        "M帽C+30" : "\"/item/65/3030\"",  "M帽C+40" : "\"/item/65/3040\"",  "M帽C+50" : "\"/item/65/3050\"",
        "F帽C+30" : "\"/item/66/3030\"",  "F帽C+40" : "\"/item/66/3040\"",  "F帽C+50" : "\"/item/66/3050\"",
        "饰C+30" : "\"/item/86/3030\"",  "饰C+40" : "\"/item/86/3040\"",  "饰C+50" : "\"/item/86/3050\"",
        "带C+30" : "\"/item/87/3030\"",  "带C+40" : "\"/item/87/3040\"",  "带C+50" : "\"/item/87/3050\"",
        "鞋C+30" : "\"/item/88/3030\"",  "鞋C+40" : "\"/item/88/3040\"",  "鞋C+50" : "\"/item/88/3050\"",

        "绒球" : "\"/item/41/4101\"",
        "竹筒" : "\"/item/41/4102\"",
        "铜矿石" : "\"/item/41/4103\"",
        "铁矿石" : "\"/item/41/4104\"",
        "熊掌" : "\"/item/41/4105\"",
        "动物皮毛" : "\"/item/41/4106\"",
        "石炭" : "\"/item/41/4107\"",
        "蓝魔之泪" : "\"/item/41/4109\"",
        "摄魂石" : "\"/item/41/4110\"",
        "萤光石" : "\"/item/41/4111\"",
        "荧光石" : "\"/item/41/4111\"",
        "银矿石" : "\"/item/41/4112\"",
        "金矿石" : "\"/item/41/4113\"",
        "寒铁" : "\"/item/41/4119\"",
        "羽毛" : "\"/item/40/4001\"",
        "蛋壳" : "\"/item/40/4002\"",
        "兔眼石" : "\"/item/40/4003\"",
        "稻草" : "\"/item/40/4004\"",
        "蜂翼" : "\"/item/40/4005\"",
        "蚂蚁卵" : "\"/item/40/4006\"",
        "粘液" : "\"/item/40/4007\"",
        "小蝌蚪" : "\"/item/40/4008\"",
        "蚂蚁触角" : "\"/item/40/4009\"",
        "千年草藤" : "\"/item/40/4010\"",
        "螳螂臂" : "\"/item/40/4011\"",
        "螳螂之翼" : "\"/item/40/4012\"",
        "破损的头盔" : "\"/item/40/4013\"",
        "破损的盔甲" : "\"/item/40/4014\"",
        "腰牌" : "\"/item/40/4015\"",
        "鱼骨" : "\"/item/40/4016\"",
        "猴子尾巴" : "\"/item/40/4017\"",
        "狗尾巴" : "\"/item/40/4018\"",
        "蛇之冠" : "\"/item/40/4019\"",
        "甲虫翅膀" : "\"/item/40/4020\"",
        "黄蜂刺" : "\"/item/40/4021\"",
        "拐杖" : "\"/item/40/4022\"",
        "火种" : "\"/item/40/4023\"",
        "珠串" : "\"/item/40/4024\"",
        "奶嘴" : "\"/item/40/4025\"",
        "飞行扇" : "\"/item/40/4026\"",
        "手杖" : "\"/item/40/4027\"",
        "发束" : "\"/item/40/4028\"",
        "狗皮药膏" : "\"/item/40/4029\"",
        "破旧的头盔" : "\"/item/40/4030\"",
        "破旧的盔甲" : "\"/item/40/4031\"",
        "骸骨碎片" : "\"/item/40/4032\"",
        "灯芯" : "\"/item/40/4033\"",
        "死者遗物" : "\"/item/40/4034\"",
        "脚镣" : "\"/item/40/4035\"",
        "蝎尾" : "\"/item/40/4036\"",
        "蜘蛛丝" : "\"/item/40/4037\"",
        "剧毒刺" : "\"/item/40/4038\"",
        "牛筋" : "\"/item/40/4039\"",
        "鼻环" : "\"/item/40/4040\"",
        "水贼头巾" : "\"/item/40/4041\"",
        "蛙蹼" : "\"/item/40/4042\"",
        "闪光的石头" : "\"/item/40/4043\"",
        "蜥蜴尾巴" : "\"/item/40/4044\"",
        "绿色小石头" : "\"/item/40/4045\"",
        "大钳子" : "\"/item/40/4046\"",
        "龟壳" : "\"/item/40/4047\"",
        "破布衣" : "\"/item/40/4048\"",
        "皮带" : "\"/item/40/4049\"",
        "蛛网" : "\"/item/40/4050\"",
        "红色小石头" : "\"/item/40/4051\"",
        "帽缨" : "\"/item/40/4052\"",
        "刀柄" : "\"/item/40/4053\"",
        "剑鞘" : "\"/item/40/4054\"",
        "箭筒" : "\"/item/40/4055\"",
        "枪头" : "\"/item/40/4056\"",
        "鱼叉" : "\"/item/40/4057\"",
        "铜罐" : "\"/item/40/4058\"",
        "黄色小石头" : "\"/item/40/4059\"",
        "腐骨" : "\"/item/40/4060\"",
        "铁骸" : "\"/item/40/4061\"",
        "铜骸" : "\"/item/40/4062\"",
        "僵尸冠" : "\"/item/40/4063\"",
        "骨盾" : "\"/item/40/4064\"",
        "骷髅头" : "\"/item/40/4065\"",
        "桃木钉" : "\"/item/40/4066\"",
        "七色串珠" : "\"/item/40/4067\"",
        "碎玉" : "\"/item/40/4068\"",
        "陶俑之首" : "\"/item/40/4069\"",
        "陶俑之臂" : "\"/item/40/4070\"",
        "锁魔链" : "\"/item/40/4071\"",
        "甲胄" : "\"/item/40/4072\"",
        "魔之心" : "\"/item/40/4073\"",
        "小太极" : "\"/item/40/4074\"",
        "拂尘" : "\"/item/40/4075\"",
        "玉盖" : "\"/item/40/4076\"",
        "长寿石" : "\"/item/40/4077\"",
        "玉束髻" : "\"/item/40/4078\"",
        "火凤之翼" : "\"/item/40/4079\"",
        "寒铁刀柄" : "\"/item/40/4080\"",
        "寒铁剑鞘" : "\"/item/40/4081\"",
        "寒铁枪头" : "\"/item/40/4082\"",
        "缉捕公文": "\"/item/98/9871\"",

	"铜矿"  : "\"/item/stuff/0001\"",
	"锡矿"  : "\"/item/stuff/0002\"",
	"铁矿"  : "\"/item/stuff/0003\"",
	"精铁矿"  : "\"/item/stuff/0004\"",
	"玄铁矿"  : "\"/item/stuff/0005\"",
	"寒铁矿"  : "\"/item/stuff/0006\"",
	"金矿"  : "\"/item/stuff/0007\"",
	"银矿"  : "\"/item/stuff/0008\"",
	"铜锭"  : "\"/item/stuff/0009\"",
	"锡锭"  : "\"/item/stuff/0010\"",
	"铁锭"  : "\"/item/stuff/0011\"",
	"精铁锭"  : "\"/item/stuff/0012\"",
	"玄铁锭"  : "\"/item/stuff/0013\"",
	"寒铁锭"  : "\"/item/stuff/0014\"",
	"金锭"  : "\"/item/stuff/0015\"",
	"银锭"  : "\"/item/stuff/0016\"",
	"木棒"  : "\"/item/stuff/0017\"",
	"松木棒"  : "\"/item/stuff/0018\"",
	"柏木棒"  : "\"/item/stuff/0019\"",
	"桃木棒"  : "\"/item/stuff/0020\"",
	"槐木棒"  : "\"/item/stuff/0021\"",
	"金棒"  : "\"/item/stuff/0022\"",
	"银棒"  : "\"/item/stuff/0023\"",
	"寒铁棒"  : "\"/item/stuff/0024\"",
	"铁棒"  : "\"/item/stuff/0025\"",
	"金之魂"  : "\"/item/stuff/0026\"",
	"木之魂"  : "\"/item/stuff/0027\"",
	"水之魂"  : "\"/item/stuff/0028\"",
	"火之魂"  : "\"/item/stuff/0029\"",
	"土之魂"  : "\"/item/stuff/0030\"",
	"打火石"  : "\"/item/stuff/0031\"",
	"魔晴石"  : "\"/item/stuff/0032\"",
	"魔睛石"  : "\"/item/stuff/0032\"",
	"麻绳"  : "\"/item/stuff/0033\"",
	"棉线"  : "\"/item/stuff/0034\"",
	"丝线"  : "\"/item/stuff/0035\"",
	"纱线"  : "\"/item/stuff/0036\"",
	"金丝"  : "\"/item/stuff/0037\"",
	"铁丝"  : "\"/item/stuff/0038\"",
	"银丝"  : "\"/item/stuff/0039\"",
	"青铜丝"  : "\"/item/stuff/0040\"",
	"精铁丝"  : "\"/item/stuff/0041\"",
	"寒铁丝"  : "\"/item/stuff/0042\"",
	"玄铁丝"  : "\"/item/stuff/0043\"",
	"碎麻布"  : "\"/item/stuff/0044\"",
	"麻布"  : "\"/item/stuff/0045\"",
	"蚕茧"  : "\"/item/stuff/0046\"",
	"蚕丝"  : "\"/item/stuff/0047\"",
	"丝绸"  : "\"/item/stuff/0048\"",
	"碎绫"  : "\"/item/stuff/0049\"",
	"绫"  : "\"/item/stuff/0050\"",
	"碎纱"  : "\"/item/stuff/0051\"",
	"纱"  : "\"/item/stuff/0052\"",
	"碎锦"  : "\"/item/stuff/0053\"",
	"锦"  : "\"/item/stuff/0054\"",
	"橙玉石"  : "\"/item/stuff/0055\"",
	"烟白玉石"  : "\"/item/stuff/0056\"",
	"灰玉石"  : "\"/item/stuff/0057\"",
	"朱红玉石"  : "\"/item/stuff/0058\"",
	"白玉石"  : "\"/item/stuff/0059\"",
	"玉白玉石"  : "\"/item/stuff/0060\"",
	"碧绿玉石"  : "\"/item/stuff/0061\"",
	"墨玉玉石"  : "\"/item/stuff/0062\"",
	"青玉石"  : "\"/item/stuff/0063\"",
	"绿玉石"  : "\"/item/stuff/0064\"",
	"天青玉石"  : "\"/item/stuff/0065\"",
	"红玉石"  : "\"/item/stuff/0066\"",
	"黑玉石"  : "\"/item/stuff/0067\"",
	"赤红玉石"  : "\"/item/stuff/0068\"",
	"蓝玉石"  : "\"/item/stuff/0069\"",
	"靛青玉石"  : "\"/item/stuff/0070\"",
	"紫红玉石"  : "\"/item/stuff/0071\"",
	"青叶玉石"  : "\"/item/stuff/0072\"",
	"琥珀玉石"  : "\"/item/stuff/0073\"",
	"紫玉石"  : "\"/item/stuff/0074\"",
	"黄玉石"  : "\"/item/stuff/0075\"",
	"玉心"  : "\"/item/stuff/0076\"",
	"补天石"  : "\"/item/stuff/0077\"",
	"橙宝石"  : "\"/item/stuff/0078\"",
	"烟白宝石"  : "\"/item/stuff/0079\"",
	"灰宝石"  : "\"/item/stuff/0080\"",
	"朱红宝石"  : "\"/item/stuff/0081\"",
	"白宝石"  : "\"/item/stuff/0082\"",
	"玉白宝石"  : "\"/item/stuff/0083\"",
	"碧绿宝石"  : "\"/item/stuff/0084\"",
	"墨玉宝石"  : "\"/item/stuff/0085\"",
	"青宝石"  : "\"/item/stuff/0086\"",
	"绿宝石"  : "\"/item/stuff/0087\"",
	"天青宝石"  : "\"/item/stuff/0088\"",
	"红宝石"  : "\"/item/stuff/0089\"",
	"黑宝石"  : "\"/item/stuff/0090\"",
	"赤红宝石"  : "\"/item/stuff/0091\"",
	"蓝宝石"  : "\"/item/stuff/0092\"",
	"靛青宝石"  : "\"/item/stuff/0093\"",
	"紫红宝石"  : "\"/item/stuff/0094\"",
	"琥珀宝石"  : "\"/item/stuff/0095\"",
	"青叶宝石"  : "\"/item/stuff/0096\"",
	"紫宝石"  : "\"/item/stuff/0097\"",
	"黄宝石"  : "\"/item/stuff/0098\"",
	"玉白宝石"  : "\"/item/stuff/0083\"",
	"完美玉心"  : "\"/item/stuff/0099\"",
	"完美补天石"  : "\"/item/stuff/0100\"",
	"黄宝石"  : "\"/item/stuff/0098\"",
	"寒铁管"  : "\"/item/stuff/0276\"",
	"寒铁片"  : "\"/item/stuff/0274\"",
	"精铁片"  : "\"/item/stuff/0264\"",
	"松木"  : "\"/item/stuff/0102\"",
	"柏木"  : "\"/item/stuff/0103\"",
	"桃木"  : "\"/item/stuff/0104\"",
	"槐木"  : "\"/item/stuff/0105\"",
	"砒霜"  : "\"/item/stuff/0106\"",
	"板蓝根"  : "\"/item/stuff/0107\"",
	"金银花"  : "\"/item/stuff/0108\"",
	"田七"  : "\"/item/stuff/0109\"",
	"罂粟果"  : "\"/item/stuff/0110\"",
	"野菊"  : "\"/item/stuff/0111\"",
	"黄芪"  : "\"/item/stuff/0112\"",
	"何首乌"  : "\"/item/stuff/0113\"",
	"罗汉果"  : "\"/item/stuff/0114\"",
	"穿心莲"  : "\"/item/stuff/0115\"",
	"黄连"  : "\"/item/stuff/0116\"",
	"洋金花"  : "\"/item/stuff/0117\"",
	"陈皮"  : "\"/item/stuff/0118\"",
	"红枣"  : "\"/item/stuff/0119\"",
	"灵芝草"  : "\"/item/stuff/0120\"",
	"生地"  : "\"/item/stuff/0121\"",
	"桔梗"  : "\"/item/stuff/0122\"",
	"山参"  : "\"/item/stuff/0123\"",
	"甘草"  : "\"/item/stuff/0124\"",
	"白芪"  : "\"/item/stuff/0125\"",
	"当归"  : "\"/item/stuff/0126\"",
	"川贝"  : "\"/item/stuff/0127\"",
	"冬虫草"  : "\"/item/stuff/0128\"",
	"番红花"  : "\"/item/stuff/0129\"",
	"龙骨"  : "\"/item/stuff/0130\"",
	"牛黄"  : "\"/item/stuff/0131\"",
	"鹿茸"  : "\"/item/stuff/0132\"",
	"麝香"  : "\"/item/stuff/0133\"",
	"蟾酥"  : "\"/item/stuff/0134\"",
	"古石灰"  : "\"/item/stuff/0135\"",
	"雄黄"  : "\"/item/stuff/0136\"",
	"吡石"  : "\"/item/stuff/0137\"",
	"砂汞"  : "\"/item/stuff/0138\"",
	"硫磺"  : "\"/item/stuff/0139\"",
	"慈石"  : "\"/item/stuff/0140\"",
	"绿矾"  : "\"/item/stuff/0141\"",
	"水稻"  : "\"/item/stuff/0142\"",
	"麦子"  : "\"/item/stuff/0143\"",
	"玉米"  : "\"/item/stuff/0144\"",
	"小米"  : "\"/item/stuff/0145\"",
	"高粱"  : "\"/item/stuff/0146\"",
	"冬瓜"  : "\"/item/stuff/0147\"",
	"南瓜"  : "\"/item/stuff/0148\"",
	"黄瓜"  : "\"/item/stuff/0149\"",
	"萝卜"  : "\"/item/stuff/0150\"",
	"白菜"  : "\"/item/stuff/0151\"",
	"青菜"  : "\"/item/stuff/0152\"",
	"番薯"  : "\"/item/stuff/0153\"",
	"山药"  : "\"/item/stuff/0154\"",
	"莲藕"  : "\"/item/stuff/0155\"",
	"茄子"  : "\"/item/stuff/0156\"",
	"竹笋"  : "\"/item/stuff/0157\"",
	"蘑菇"  : "\"/item/stuff/0158\"",
	"绿豆"  : "\"/item/stuff/0159\"",
	"黄豆"  : "\"/item/stuff/0160\"",
	"扁豆"  : "\"/item/stuff/0161\"",
	"花生"  : "\"/item/stuff/0162\"",
	"芝麻"  : "\"/item/stuff/0163\"",
	"油菜籽"  : "\"/item/stuff/0164\"",
	"辣椒"  : "\"/item/stuff/0165\"",
	"葱"  : "\"/item/stuff/0166\"",
	"大蒜"  : "\"/item/stuff/0167\"",
	"姜"  : "\"/item/stuff/0168\"",
	"蜂蜜"  : "\"/item/stuff/0169\"",
	"烟草"  : "\"/item/stuff/0170\"",
	"鸡蛋"  : "\"/item/stuff/0171\"",
	"鸭蛋"  : "\"/item/stuff/0172\"",
	"鸟蛋"  : "\"/item/stuff/0173\"",
	"乌龟蛋"  : "\"/item/stuff/0174\"",
	"狮子肉"  : "\"/item/stuff/0175\"",
	"龟肉"  : "\"/item/stuff/0176\"",
	"青蛙肉"  : "\"/item/stuff/0177\"",
	"狗肉"  : "\"/item/stuff/0178\"",
	"猪肉"  : "\"/item/stuff/0179\"",
	"虎肉"  : "\"/item/stuff/0180\"",
	"牛肉"  : "\"/item/stuff/0181\"",
	"熊肉"  : "\"/item/stuff/0182\"",
	"豹子胆"  : "\"/item/stuff/0183\"",
	"狼心"  : "\"/item/stuff/0184\"",
	"狗肺"  : "\"/item/stuff/0185\"",
	"驴肝肺"  : "\"/item/stuff/0186\"",
	"鱼"  : "\"/item/stuff/0187\"",
	"蛇"  : "\"/item/stuff/0188\"",
	"蝎子"  : "\"/item/stuff/0189\"",
	"蛇皮"  : "\"/item/stuff/0190\"",
	"牛皮"  : "\"/item/stuff/0191\"",
	"狼皮"  : "\"/item/stuff/0192\"",
	"豹皮"  : "\"/item/stuff/0193\"",
	"虎皮"  : "\"/item/stuff/0194\"",
	"熊皮"  : "\"/item/stuff/0195\"",
	"铜制机关构件"  : "\"/item/stuff/0196\"",
	"铁制机关构件"  : "\"/item/stuff/0197\"",
	"精铁机关构件"  : "\"/item/stuff/0198\"",
	"青铜机关构件"  : "\"/item/stuff/0199\"",
	"玄铁机关构件"  : "\"/item/stuff/0200\"",
	"寒铁机关构件"  : "\"/item/stuff/0201\"",
	"传动机构"  : "\"/item/stuff/0202\"",
	"瞄准构件"  : "\"/item/stuff/0203\"",
	"永动核心"  : "\"/item/stuff/0204\"",
	"机关构件"  : "\"/item/stuff/0205\"",
	"木轮"  : "\"/item/stuff/0206\"",
	"木制轴承"  : "\"/item/stuff/0207\"",
	"铁制轴承"  : "\"/item/stuff/0208\"",
	"铁轮"  : "\"/item/stuff/0209\"",
	"锯片"  : "\"/item/stuff/0210\"",
	"刀片"  : "\"/item/stuff/0211\"",
	"硝石"  : "\"/item/stuff/0212\"",
	"地瓜"  : "\"/item/stuff/0220\"",
	"乌龟肉"  : "\"/item/stuff/0176\"",
	"劣质宝石矿" : "\"/item/89/8990\"",
	"残缺宝石矿" : "\"/item/89/8991\"",
	"宝石矿" : "\"/item/89/8992\"",
	"精致宝石矿" : "\"/item/89/8993\"",
	"无暇宝石矿" : "\"/item/89/8994\"",
	"完美宝石矿" : "\"/item/89/8995\"",
	"初级宠物技能书" : "\"/item/44/4488\"",
	"元魂": "\"/item/stuff/0309\"",
	"元魄": "\"/item/stuff/0310\"",
	"离魂": "\"/item/stuff/0311\"",
	"离魄": "\"/item/stuff/0312\"",	
	"干将宝石": "\"/item/08/0015\"",	
]);

// 函数：获取物品文件
string get_item_file( string name )
{
        if( undefinedp( ItemList[name] ) ) return "";
        else return ItemList[name];
}









        