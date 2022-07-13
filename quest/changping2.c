
// 函数：获取出怪坐标
int get_comrade_point( int z, int flag )
{
        int x, y;

        switch( flag )
        {
      case 10 : x =  99;  y =  36;  break;    // 攻击方(跳转10)
      default : x =  73;  y =  57;  break;    // 攻击方(跳转11)
      case 12 : x =  45;  y =  80;  break;    // 攻击方(跳转12)

      case 15 : x = 201;  y = 112;  break;    // 防守方(跳转15)
      case 16 : x = 174;  y = 134;  break;    // 防守方(跳转16)
      case 17 : x = 147;  y = 156;  break;    // 防守方(跳转17)
        }

        return x * 1000 + y;
}

// 函数：获取总管坐标
int get_manager_point( int z, int flag )
{
        int x, y;

        switch( flag )
        {
      default : x =  54;  y =  45;  break;    // 攻击方(总管)
       case 2 : x = 187;  y = 144;  break;    // 防守方(总管)

      case 11 : x =  38;  y =  75;  break;    // 攻击方(商人)
      case 12 : x = 208;  y = 123;  break;    // 防守方(商人)
        }

        return x * 1000 + y;
}

// 函数：获取总管坐标
int get_valid_manager_xy( int z, int flag )
{
        int p = get_manager_point(z, flag);
        return get_valid_xy( z, p / 1000, p % 1000, IS_CHAR_BLOCK );
}

// 变量：箭塔地点列表

string *AttackTower_Org0 = ({    // 帮派战场：攻击方基本箭塔
        "68,57",
        "71,55",
        "73,53",
        "68,54",
        "70,52",
        "49,75",
        "50,74",
        "51,73",
        "94,41",
        "96,40",
        "97,38",
        // "119,41",
        // "73,42",
        // "64,43",
        // "101,43",
        // "57,45",
        // "64,45",
        // "103,45",
        // "79,46",
        // "55,47",
        // "80,47",
        // "66,48",
        // "65,49",
        // "64,50",
        // "110,50",
        // "63,51",
        // "53,52",
        // "55,52",
        // "62,52",
        // "74,54",
        // "79,55",
        // "72,56",
        // "70,58",
        // "47,59",
        // "83,59",
        // "62,60",
        // "49,61",
        // "63,61",
        // "71,61",
        // "46,62",
        // "92,64",
        // "75,65",
        // "50,67",
        // "52,69",
        // "84,72",
        // "37,73",
        // "40,74",
        // "38,76",
        // "52,76",
        // "54,78",
        // "56,80",
        // "40,81",
        // "45,85",
        // "50,89",
        // "63,89",
        // "57,95",
});

string *AttackTower_Org1 = ({    // 帮派战场：攻击方１级箭塔
        "73,63",
        "81,57",
        "50,79",
        "56,75",
        "96,44",
        "102,40",
        // "60,39",
        // "84,41",
        // "69,46",
        // "92,47",
        // "47,49",
        // "69,50",
        // "97,50",
        // "87,51",
        // "44,52",
        // "66,53",
        // "59,54",
        // "41,55",
        // "63,55",
        // "89,56",
        // "54,63",
        // "43,66",
        // "64,68",
        // "69,71",
        // "43,72",
        // "59,72",
        // "34,76",
        // "61,77",
        // "37,79",
});

string *AttackTower_Org2 = ({    // 帮派战场：攻击方２级箭塔
        "47,75",
        "51,71",
        "96,36",
        "92,40",
        // "80,50",
        // "85,56",
        // "81,57",
        // "66,61",
        // "73,63",
        // "70,67",
        // "51,72",
        // "57,77",
        // "42,83",
        // "47,87",
});

string *AttackTower_Org3 = ({    // 帮派战场：攻击方３级箭塔
        "66,56",
        "72,51",
        // "77,36",
        // "52,41",
        // "56,41",
        // "59,44",
        // "51,45",
        // "58,47",
        // "54,48",
        // "90,50",
        // "30,57",
        // "34,60",
        // "37,63",
        // "62,71",
});

string *AttackTower_Org4 = ({    // 帮派战场：攻击方４级箭塔
        "60,45",
        "64,48",
        "59,52",
        "55,49",
        // "39,49",
});

string *DefenseTower_Org0 = ({    // 帮派战场：防御方基本箭塔
        "168,136",
        "170,134",
        "172,132",
        "171,137",
        "173,135",
        "143,148",
        "145,147",
        "147,146",
        "189,114",
        "191,113",
        "193,112",
        // "206,121",
        // "196,123",
        // "156,125",
        // "198,125",
        // "174,126",
        // "178,129",
        // "183,130",
        // "184,131",
        // "164,132",
        // "176,134",
        // "168,136",
        // "174,136",
        // "187,136",
        // "189,136",
        // "172,138",
        // "183,138",
        // "182,139",
        // "131,140",
        // "181,140",
        // "180,141",
        // "168,142",
        // "179,142",
        // "187,142",
        // "169,143",
        // "185,144",
        // "126,145",
        // "146,147",
        // "179,147",
        // "148,149",
        // "179,149",
        // "150,151",
        // "156,151",
        // "165,151",
        // "135,152",
        // "157,152",
        // "163,153",
        // "166,154",
        // "140,156",
        // "152,158",
        // "145,160",
        // "150,160",
        // "153,161",
        // "203,120",
        // "203,134",
        // "203,137",
        
});

string *DefenseTower_Org1 = ({    // 帮派战场：防御方１级箭塔
        "170,126",
        "160,132",
        "193,108",
        "186,113",
        "146,143",
        "139,148",
        // "184,125",
        // "191,128",
        // "200,128",
        // "181,135",
        // "184,135",
        // "197,136",
        // "179,137",
        // "159,138",
        // "195,138",
        // "177,139",
        // "193,140",
        // "160,143",
        // "177,143",
        // "150,144",
        // "156,146",
        // "166,148",
        // "181,152",
        // "179,154",
        // "155,156",
        // "159,156",
        // "177,156",
        // "148,163",
        // "151,165",
});

string *DefenseTower_Org2 = ({    // 帮派战场：防御方２级箭塔
        "145,152",
        "151,148",
        "190,118",
        "197,113",
        // "178,126",
        // "176,128",
        // "181,130",
        // "166,134",
        // "163,137",
        // "168,139",
        // "150,147",
        // "153,151",
        // "137,154",
        // "142,158",
});

string *DefenseTower_Org3 = ({    // 帮派战场：防御方３级箭塔
        "175,133",
        "169,138",
        // "211,133",
        // "214,136",
        // "185,141",
        // "189,141",
        // "157,143",
        // "191,143",
        // "185,145",
        // "187,147",
        // "190,147",
        // "166,158",
        // "170,161",
        // "174,164",
});

string *DefenseTower_Org4 = ({    // 帮派战场：防御方４级箭塔
        "189,153",
        "185,147",
        "191,142",
        "195,146",
        // "181,165",
});

// 函数：获取箭塔坐标
string *get_tower_array( int z, int flag )
{
        switch( flag )
        {
      default : return AttackTower_Org0;    // 攻击方(基本箭塔)
       case 1 : return AttackTower_Org1;    // 攻击方(１级箭塔)
       case 2 : return AttackTower_Org2;    // 攻击方(２级箭塔)
       case 3 : return AttackTower_Org3;    // 攻击方(３级箭塔)
       case 4 : return AttackTower_Org4;    // 攻击方(４级箭塔)

       case 5 : return DefenseTower_Org0;    // 防守方(基本箭塔)
       case 6 : return DefenseTower_Org1;    // 防守方(１级箭塔)
       case 7 : return DefenseTower_Org2;    // 防守方(２级箭塔)
       case 8 : return DefenseTower_Org3;    // 防守方(３级箭塔)
       case 9 : return DefenseTower_Org4;    // 防守方(４级箭塔)
        }
}
