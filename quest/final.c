
//final.c 获取某一等级的生活技能物品
//等级 种类 门派 性格

#include <skill.h>
#include <equip.h>

//item/final/60文件夹下的文件
mapping type_60 = ([
	20:	({"/60/1020","/60/2020","/60/3020","/60/4020","/60/5020","/60/6020","/60/7020",}),
	25:	({}),
	30:	({"/60/1030","/60/2030","/60/3030","/60/4030","/60/5030","/60/6030","/60/7030",}),                                     
	35:	({"/60/1035","/60/2035","/60/3035","/60/4035","/60/5035","/60/6035","/60/7035","9035",}),
	40:	({"/60/1040","/60/2040","/60/3040","/60/4040","/60/5040","/60/6040","/60/7040",}),
	45:	({"/60/1045","/60/2045","/60/3045","/60/4045","/60/5045","/60/6045","/60/7045",}),
	50:	({"/60/1050","/60/2050","/60/3050","/60/4050","/60/5050","/60/6050","/60/7050",}),
	55:	({"/60/1055","/60/2055","/60/3055","/60/4055","/60/5055","/60/6055","/60/7055",}),
	60:	({"/60/1060","/60/2060","/60/3060","/60/4060","/60/5060","/60/6060","/60/7060",}),
	65:	({"/60/1065","/60/2065","/60/3065","/60/4065","/60/5065","/60/6065","/60/7065",}),
	70:	({"/60/1070","/60/2070","/60/3070","/60/4070","/60/5070","/60/6070","/60/7070",}),
	75:	({"/60/1075","/60/2075","/60/3075","/60/4075","/60/5075","/60/6075","/60/7075",}),
	80:	({"/60/1080","/60/2080","/60/3080","/60/4080","/60/5080","/60/6080","/60/7080",}),
	85:	({"/60/1085","/60/2085","/60/3085","/60/4085","/60/5085","/60/6085","/60/7085",}),
	90:	({"/60/1090","/60/2090","/60/3090","/60/4090","/60/5090","/60/6090","/60/7090",}),
	95:	({"/60/1095","/60/2095","/60/3095","/60/4095","/60/5095","/60/6095","/60/7095",}),
	100:	({"/60/1100","/60/2100","/60/3100","/60/4100","/60/5100","/60/6100","/60/7100",}),
	105:	({"/60/1105","/60/2105","/60/3105","/60/4105","/60/5105","/60/6105","/60/7105",}),
	110:	({"/60/1110","/60/2110","/60/3110","/60/4110","/60/5110","/60/6110","/60/7110",}),
	115:	({"/60/1115","/60/2115","/60/3115","/60/4115","/60/5115","/60/6115","/60/7115",}),
	119:	({"/60/1119","/60/2119","/60/3119","/60/4119","/60/5119","/60/6119","/60/7119",}),
	120:	({"/60/1120","/60/2120","/60/3120","/60/4120","/60/5120","/60/6120","/60/7120",}),
		]);

//item/final/65文件夹下的文件	           
mapping type_65 = ([
	20:	({"/65/1020","/65/2020","/65/3020","/65/4020","/65/5020","/65/6020","/65/7020",}),
	25:	({}),
	30:	({"/65/1030","/65/2030","/65/3030","/65/4030","/65/5030","/65/6030","/65/7030",}),
	35:	({}),
	40:	({"/65/1040","/65/2040","/65/3040","/65/4040","/65/5040","/65/6040","/65/7040",}),
	45:	({"/65/1045","/65/2045","/65/3045","/65/4045","/65/5045","/65/6045","/65/7045",}),
	50:	({"/65/1050","/65/2050","/65/3050","/65/4050","/65/5050","/65/6050","/65/7050",}),
	55:	({"/65/1055","/65/2055","/65/3055","/65/4055","/65/5055","/65/6055","/65/7055",}),
	60:	({"/65/1060","/65/2060","/65/3060","/65/4060","/65/5060","/65/6060","/65/7060",}),
	65:	({"/65/1065","/65/2065","/65/3065","/65/4065","/65/5065","/65/6065","/65/7065",}),
	70:	({"/65/1070","/65/2070","/65/3070","/65/4070","/65/5070","/65/6070","/65/7070",}),
	75:	({"/65/1075","/65/2075","/65/3075","/65/4075","/65/5075","/65/6075","/65/7075",}),
	80:	({"/65/1080","/65/2080","/65/3080","/65/4080","/65/5080","/65/6080","/65/7080",}),
	85:	({"/65/1085","/65/2085","/65/3085","/65/4085","/65/5085","/65/6085","/65/7085",}),
	90:	({"/65/1090","/65/2090","/65/3090","/65/4090","/65/5090","/65/6090","/65/7090",}),
	95:	({"/65/1095","/65/2095","/65/3095","/65/4095","/65/5095","/65/6095","/65/7095",}),
	100:	({"/65/1100","/65/2100","/65/3100","/65/4100","/65/5100","/65/6100","/65/7100",}),
	105:	({"/65/1105","/65/2105","/65/3105","/65/4105","/65/5105","/65/6105","/65/7105",}),
	110:	({"/65/1110","/65/2110","/65/3110","/65/4110","/65/5110","/65/6110","/65/7110",}),
	115:	({"/65/1115","/65/2115","/65/3115","/65/4115","/65/5115","/65/6115","/65/7115",}),
	119:	({"/65/1119","/65/2119","/65/3119","/65/4119","/65/5119","/65/6119","/65/7119",}),
	120:	({"/65/1120","/65/2120","/65/3120","/65/4120","/65/5120","/65/6120","/65/7120",}),
		]);
		
//item/final/70文件夹下的文件		
mapping type_70 = ([
	20:	({"/70/1020",}),
	25:	({}),	
	30:	({"/70/1030",}),
	35:	({"/70/1035",}),
	40:	({"/70/1040",}),
	45:	({"/70/1045",}),
	50:	({"/70/1050",}),
	55:	({"/70/1055",}),
	60:	({"/70/1060",}),
	65:	({"/70/1065",}),
	70:	({"/70/1070",}),
	75:	({"/70/1075",}),
	80:	({"/70/1080",}),
	85:	({"/70/1085",}),
	90:	({"/70/1090",}),
	95:	({"/70/1095",}),
	100:	({"/70/1100",}),
	105:	({"/70/1105",}),
	110:	({"/70/1110",}),
	115:	({"/70/1115",}),
	119:	({}),
	120:	({"/70/1120",}),
		]);
		
		
		
//item/final/71文件夹下的文件		
mapping type_71 = ([
	20:	({"/71/1020",}),
	25:	({}),	
	30:	({"/71/1030",}),
	35:	({"/71/1035",}),
	40:	({"/71/1040",}),
	45:	({"/71/1045",}),
	50:	({"/71/1050",}),
	55:	({"/71/1055",}),
	60:	({"/71/1060",}),
	65:	({"/71/1065",}),
	70:	({"/71/1070",}),
	75:	({"/71/1075",}),
	80:	({"/71/1080",}),
	85:	({"/71/1085",}),
	90:	({"/71/1090",}),
	95:	({"/71/1095",}),
	100:	({"/71/1100",}),
	105:	({"/71/1105",}),
	110:	({"/71/1110",}),
	115:	({"/71/1115",}),
	119:	({}),
	120:	({"/71/1120",}),
		]);
		
//item/final/72文件夹下的文件		
mapping type_72 = ([
	20:	({"/72/1020",}),
	25:	({}),	
	30:	({"/72/1030",}),
	35:	({"/72/1035",}),
	40:	({"/72/1040",}),
	45:	({"/72/1045",}),
	50:	({"/72/1050",}),
	55:	({"/72/1055",}),
	60:	({"/72/1060",}),
	65:	({"/72/1065",}),
	70:	({"/72/1070",}),
	75:	({"/72/1075",}),
	80:	({"/72/1080",}),
	85:	({"/72/1085",}),
	90:	({"/72/1090",}),
	95:	({"/72/1095",}),
	100:	({"/72/1100",}),
	105:	({"/72/1105",}),
	110:	({"/72/1110",}),
	115:	({"/72/1115",}),
	119:	({}),
	120:	({"/72/1120",}),
		]);
		
//item/final/73文件夹下的文件		
mapping type_73 = ([
	20:	({}),
	25:	({}),	
	30:	({"/73/1030",}),
	35:	({}),
	40:	({}),
	45:	({}),
	50:	({}),
	55:	({}),
	60:	({}),
	65:	({}),
	70:	({}),
	75:	({}),
	80:	({}),
	85:	({}),
	90:	({}),
	95:	({}),
	100:	({}),
	105:	({}),
	110:	({}),
	115:	({}),
	119:	({}),
	120:	({}),
		]);
        
        
//item/final/74文件夹下的文件       
mapping type_74 = ([
	20:	({"/74/1020",}),
	25:	({}),	
	30:	({"/74/1030",}),
	35:	({"/74/1035",}),
	40:	({"/74/1040",}),
	45:	({"/74/1045",}),
	50:	({"/74/1050",}),
	55:	({"/74/1055",}),
	60:	({"/74/1060",}),
	65:	({"/74/1065",}),
	70:	({"/74/1070",}),
	75:	({"/74/1075",}),
	80:	({"/74/1080",}),
	85:	({"/74/1085",}),
	90:	({"/74/1090",}),
	95:	({"/74/1095",}),
	100:	({"/74/1100",}),
	105:	({"/74/1105",}),
	110:	({"/74/1110",}),
	115:	({"/74/1115",}),
	119:	({}),
	120:	({"/74/1120",}),
		]);
		
//item/final/75文件夹下的文件		
mapping type_75 = ([
	20:	({"/75/1020",}),
	25:	({}),	
	30:	({"/75/1030",}),
	35:	({"/75/1035",}),
	40:	({"/75/1040",}),
	45:	({"/75/1045",}),
	50:	({"/75/1050",}),
	55:	({"/75/1055",}),
	60:	({"/75/1060",}),
	65:	({"/75/1065",}),
	70:	({"/75/1070",}),
	75:	({"/75/1075",}),
	80:	({"/75/1080",}),
	85:	({"/75/1085",}),
	90:	({"/75/1090",}),
	95:	({"/75/1095",}),
	100:	({"/75/1100",}),
	105:	({"/75/1105",}),
	110:	({"/75/1110",}),
	115:	({"/75/1115",}),
	119:	({}),
	120:	({"/75/1120",}),
		]);

//item/final/76文件夹下的文件		
mapping type_76 = ([
	20:	({"/76/1020",}),
	25:	({}),	
	30:	({"/76/1030",}),
	35:	({"/76/1035",}),
	40:	({"/76/1040",}),
	45:	({"/76/1045",}),
	50:	({"/76/1050",}),
	55:	({"/76/1055",}),
	60:	({"/76/1060",}),
	65:	({"/76/1065",}),
	70:	({"/76/1070",}),
	75:	({"/76/1075",}),
	80:	({"/76/1080",}),
	85:	({"/76/1085",}),
	90:	({"/76/1090",}),
	95:	({"/76/1095",}),
	100:	({"/76/1100",}),
	105:	({"/76/1105",}),
	110:	({"/76/1110",}),
	115:	({"/76/1115",}),
	119:	({}),
	120:	({"/76/1120",}),
		]);
		

//item/final/86文件夹下的文件		
mapping type_86 = ([
	20:	({"/86/1020","/86/2020","/86/3020","/86/4020","/86/5020","/86/6020","/86/7020",}),
	25:	({"/86/1025","/86/2025","/86/3025","/86/4025","/86/5025","/86/6025","/86/7025",}),
	30:	({"/86/1030","/86/2030","/86/3030","/86/4030","/86/5030","/86/6030","/86/7030",}),                                     
	35:	({"/86/1035","/86/2035","/86/3035","/86/4035","/86/5035","/86/6035","/86/7035",}),
	40:	({"/86/1040","/86/2040","/86/3040","/86/4040","/86/5040","/86/6040","/86/7040",}),
	45:	({"/86/1045","/86/2045","/86/3045","/86/4045","/86/5045","/86/6045","/86/7045",}),
	50:	({"/86/1050","/86/2050","/86/3050","/86/4050","/86/5050","/86/6050","/86/7050",}),
	55:	({"/86/1055","/86/2055","/86/3055","/86/4055","/86/5055","/86/6055","/86/7055",}),
	60:	({"/86/1060","/86/2060","/86/3060","/86/4060","/86/5060","/86/6060","/86/7060",}),
	65:	({"/86/1065","/86/2065","/86/3065","/86/4065","/86/5065","/86/6065","/86/7065",}),
	70:	({"/86/1070","/86/2070","/86/3070","/86/4070","/86/5070","/86/6070","/86/7070",}),
	75:	({"/86/1075","/86/2075","/86/3075","/86/4075","/86/5075","/86/6075","/86/7075",}),
	80:	({"/86/1080","/86/2080","/86/3080","/86/4080","/86/5080","/86/6080","/86/7080",}),
	85:	({"/86/1085","/86/2085","/86/3085","/86/4085","/86/5085","/86/6085","/86/7085",}),
	90:	({"/86/1090","/86/2090","/86/3090","/86/4090","/86/5090","/86/6090","/86/7090",}),
	95:	({"/86/1095","/86/2095","/86/3095","/86/4095","/86/5095","/86/6095","/86/7095",}),
	100:	({"/86/1100","/86/2100","/86/3100","/86/4100","/86/5100","/86/6100","/86/7100",}),
	105:	({"/86/1105","/86/2105","/86/3105","/86/4105","/86/5105","/86/6105","/86/7105",}),
	110:	({"/86/1110","/86/2110","/86/3110","/86/4110","/86/5110","/86/6110","/86/7110",}),
	115:	({"/86/1115","/86/2115","/86/3115","/86/4115","/86/5115","/86/6115","/86/7115",}),
	119:	({"/86/1119","/86/2119","/86/3119","/86/4119","/86/5119","/86/6119","/86/7119",}),
	120:	({"/86/1120","/86/2120","/86/3120","/86/4120","/86/5120","/86/6120","/86/7120",}),
		]);
		
//item/final/88文件夹下的文件		
mapping type_88 = ([
	20:({"/88/1020","/88/2020","/88/3020","/88/4020","/88/5020","/88/6020","/88/7020",}),
	25:({}),
	30:({"/88/1030","/88/2030","/88/3030","/88/4030","/88/5030","/88/6030","/88/7030",}),                                     
	35:({}),
	40:({"/88/1040","/88/2040","/88/3040","/88/4040","/88/5040","/88/6040","/88/7040",}),
	45:({"/88/1045","/88/2045","/88/3045","/88/4045","/88/5045","/88/6045","/88/7045",}),
	50:({"/88/1050","/88/2050","/88/3050","/88/4050","/88/5050","/88/6050","/88/7050",}),
	55:({"/88/1055","/88/2055","/88/3055","/88/4055","/88/5055","/88/6055","/88/7055",}),
	60:({"/88/1060","/88/2060","/88/3060","/88/4060","/88/5060","/88/6060","/88/7060",}),
	65:({"/88/1065","/88/2065","/88/3065","/88/4065","/88/5065","/88/6065","/88/7065",}),
	70:({"/88/1070","/88/2070","/88/3070","/88/4070","/88/5070","/88/6070","/88/7070",}),
	75:({"/88/1075","/88/2075","/88/3075","/88/4075","/88/5075","/88/6075","/88/7075",}),
	80:({"/88/1080","/88/2080","/88/3080","/88/4080","/88/5080","/88/6080","/88/7080",}),
	85:({"/88/1085","/88/2085","/88/3085","/88/4085","/88/5085","/88/6085","/88/7085",}),
	90:({"/88/1090","/88/2090","/88/3090","/88/4090","/88/5090","/88/6090","/88/7090",}),
	95:({"/88/1095","/88/2095","/88/3095","/88/4095","/88/5095","/88/6095","/88/7095",}),
	100:({"/88/1100","/88/2100","/88/3100","/88/4100","/88/5100","/88/6100","/88/7100",}),
	105:({"/88/1105","/88/2105","/88/3105","/88/4105","/88/5105","/88/6105","/88/7105",}),
	110:({"/88/1110","/88/2110","/88/3110","/88/4110","/88/5110","/88/6110","/88/7110",}),
	115:({"/88/1115","/88/2115","/88/3115","/88/4115","/88/5115","/88/6115","/88/7115",}),
	119:({"/88/1119","/88/2119","/88/3119","/88/4119","/88/5119","/88/6119","/88/7119",}),
	120:({"/88/1120","/88/2120","/88/3120","/88/4120","/88/5120","/88/6120","/88/7120",}),
	]);
		
//等级
int* lv_num = ({20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,119,120,});

int sizeof_lv_num = sizeof(lv_num);
	
				
//种类
mapping* mapp_type = ({type_60,type_65,type_70,type_71,type_72,type_73,type_74,type_75,type_76,
	type_86,type_88,});

int sizeof_type = sizeof(mapp_type);

//类型索引
int *i_type = ({
	1,  
	2, 
	3,
	4,
	5,
	6,
	7 ,
	8 ,
	9 ,
	10,
	11,
});

int sizeof_i_type = sizeof(i_type);


//门派
string *str_fam = ({
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
});       

int sizeof_fam = sizeof(str_fam);

//从字符串数组中随机一个数组
string rand_str(string *p_str)
{
	int i = sizeof(p_str);
	if(i != 0){return "/item/final"+ p_str[random(i)];}
	else{return "/item/final/73/1030";}
}

//获取某类型字符串数组
string * type_str(int type)
{
	int i;
	string * p_str = ({});
	for(i = 0;i<sizeof_lv_num;i++)
	{
		p_str += mapp_type[type][lv_num[i]];
	}
	return p_str;
}

//获取某类型中某等级的字符串数组
string * type_lv_str(int type,int lv)
{
	string * p_str = ({});
	if(lv<20){lv=20;}
	if(lv>120){lv=120;}
	if(lv != 119){lv = lv/5*5;}
	p_str += mapp_type[type][lv];
	return p_str;
}

//获取某类型中某等级段的字符串数组
string * type_lv_str2(int type,int lv1,int lv2)
{
	int i,lv;
	string *p_str = ({});
	
	if(lv1>lv2){i=lv1;lv1 = lv2;lv2 = i;}//换位
	if(lv1>120){return type_lv_str(type,120);}
	if(lv2<20){return type_lv_str(type,20);}
	if(lv1<20){lv1=20;}
	if(lv2>120){lv2=120;}
	if(lv1<=119&&lv2>=119){p_str += type_lv_str(type,119);}
	for(lv = lv1/5*5;lv<=lv2;lv+=5)
	{
		p_str += type_lv_str(type,lv);
	}
	return p_str;
}

//获取某种门派字符串数组
string * fam_str(int fam)
{
	int i,lv;
	string *p_str = ({});
	for(i=0;i<sizeof_lv_num;i++)
	{
		if(sizeof(type_60[lv_num[i]])!=0)//那个等级有这么多项
		{
			p_str += ({type_60[lv_num[i]][fam-1]});
		}
		if(sizeof(type_65[lv_num[i]])!=0)//那个等级有这么多项
		{
			p_str += ({type_65[lv_num[i]][fam-1]});
		}
		if(sizeof(type_86[lv_num[i]])!=0)//那个等级有这么多项
		{
			p_str += ({type_86[lv_num[i]][fam-1]});
		}
		if(sizeof(type_88[lv_num[i]])!=0)//那个等级有这么多项
		{
			p_str += ({type_88[lv_num[i]][fam-1]});
		}
	}
	if(fam = 6){p_str += ({"/60/9035"});}
	
	return p_str;
}

//获取全部字符串数组
string *all_str()
{
	int i,j;
	string *p_str = ({});
	for(i=0;i<sizeof_type;i++)
	{
		for(j=0;j<sizeof_lv_num;j++)
		{
			p_str += mapp_type[i][lv_num[j]];
		}
	}
	return p_str;
}


//获取某门派中某等级的字符串数组
string *fam_lv_str(int fam, int lv)
{
	int i;
	string *p_str = ({});
	//容错处理
	if(lv<20){lv=20;}
	if(lv>120){lv=120;}
	if(lv != 119){lv = lv/5*5;}
	
	if(sizeof(type_60[lv])!=0)//那个等级有这么多项
	{
		p_str += ({type_60[lv][fam-1]});
	}
	if(sizeof(type_65[lv])!=0)//那个等级有这么多项
	{
		p_str += ({type_65[lv][fam-1]});
	}
	if(sizeof(type_86[lv])!=0)//那个等级有这么多项
	{
		p_str += ({type_86[lv][fam-1]});
	}
	if(sizeof(type_88[lv])!=0)//那个等级有这么多项
	{
		p_str += ({type_88[lv][fam-1]});
	}
	if(fam == 6 && lv == 35){p_str += ({"/60/9035"});}
	
	return p_str;
}
	
//获取某门派中某等级段的字符串数组
string *fam_lv_str2(int fam, int lv1,int lv2)
{
	int i,lv;
	string *p_str = ({});
	
	if(lv1>lv2){i=lv1;lv1 = lv2;lv2 = i;}//换位
	if(lv1>120){return fam_lv_str(fam,120);}
	if(lv2<20){return fam_lv_str(fam,20);}
	if(lv1<20){lv1=20;}
	if(lv2>120){lv2=120;}
	if(lv1<=119&&lv2>=119){p_str += fam_lv_str(fam,119);}
	for(lv = lv1/5*5;lv<=lv2;lv+=5)
	{
		for(i=0;i<sizeof_type;i++)
		{
			p_str += fam_lv_str(fam,lv);
		}
	}
	return p_str;
}


//获取某门派、类型的字符串数组
string *fam_type_str(int fam,int type)
{
	int i,lv;
	string *p_str = ({});
	for(lv=0;lv<sizeof_lv_num;i++)
	{
		if(sizeof(mapp_type[type][lv])!=0)
		{
			p_str += ({mapp_type[type][lv][fam-1]});
		}
	}
	if(type == 0 && fam == 6){p_str += ({"/60/9035"});}
	
	return p_str;
}

//获取某门派、类型、等级的字符串数组
string* fam_type_lv_str(int fam,int type,int lv)
{
	string *p_str = ({});
	//容错处理
	if(lv<20){lv=20;}
	if(lv>120){lv=120;}
	if(lv != 119){lv = lv/5*5;}
		
	if(sizeof(mapp_type[type][lv])!=0)
	{
		p_str += ({mapp_type[type][lv][fam-1]});
	}
	if(type == 0 && fam == 6 && lv == 35){p_str += ({"/60/9035"});}
	
	return p_str;
}

//获取某门派、类型、等级段的字符串数组
string *fam_type_lv_str2(int fam,int type,int lv1,int lv2)
{
	int i,lv;
	string *p_str = ({});
	
	if(lv1>lv2){i=lv1;lv1=lv2;lv2=i;}//换位
	if(lv1>120){return fam_lv_str(fam,120);}
	if(lv2<20){return fam_lv_str(fam,20);}
	if(lv1<20){lv1=20;}
	if(lv2>120){lv2=120;}
	if(lv1<=119&&lv2>=119){p_str += fam_type_lv_str(fam,type,119);}
	for(lv = lv1/5*5;lv<=lv2;lv+=5)
	{
		for(i=0;i<sizeof_type;i++)
		{
			p_str += fam_type_lv_str(fam,type,lv);
		}
	}
	return p_str;
}
	
string file_final_lv(int lv)//根据等级生成物品
{
	int i;
	string *p_str = ({});
	if(lv<20){lv=20;}
	if(lv>120){lv=120;}
	if(lv != 119){lv = lv/5*5;}
	for(i=0;i<sizeof_type;i++)
	{
		p_str += mapp_type[i][lv];
	}
	return rand_str(p_str);
}

string file_final_lv2(int lv1, int lv2)//根据等级段生成物品
{
	int i,lv;
	string *p_str = ({});
	
	if(lv1>lv2){i=lv1;lv1 = lv2;lv2 = i;}//换位
	if(lv1>120){return file_final_lv(120);}
	if(lv2<20){return file_final_lv(20);}
	if(lv1<20){lv1=20;}
	if(lv2>120){lv2=120;}
	if(lv1<=119&&lv2>=119){p_str += mapp_type[i][119];}
	for(lv = lv1/5*5;lv<=lv2;lv+=5)
	{
		for(i=0;i<sizeof_type;i++)
		{
			p_str += mapp_type[i][lv];
		}
	}
	return rand_str(p_str);	
}


string file_final_type(int type)//根据类型生成物品
{             
	int i,lv;
	string *p_str = ({});
	switch(type)
	{
	default:
		p_str += all_str();
		break;
	case ARMOR_TYPE:
		p_str = type_str(0);
		break;
	case HEAD_TYPE:
		p_str = type_str(1);
		break;
	case UNARMED:
		p_str = type_str(2);
		break;
	case THROWING:
		p_str = type_str(3);
		break;
	case BLADE:
		p_str = type_str(4);
		break;
	case SWORD:
		p_str = type_str(5);
		break;
	case SPEAR:
		p_str = type_str(6);
		break;
	case STICK:
		p_str = type_str(7);
		break;
	case SWORD:
		p_str = type_str(8);
		break;
	case NECK_TYPE:
		p_str = type_str(9);
		break;
	case BOOTS_TYPE:
		p_str = type_str(10);
		break;
	}
	return rand_str(p_str);
}


string file_final_fam(string fam)//根据门派生成物品
{
	string *p_str = ({});
	switch(fam)
	{
	default:
		p_str += all_str();
		break;
	case FAMILY_1:
		p_str += fam_str(1);
		p_str += type_str(2);
		break;
	case FAMILY_2:
		p_str += fam_str(2);
		p_str += type_str(4);
		break;
	case FAMILY_3:
		p_str += fam_str(3);
		p_str += type_str(6);
		p_str += type_str(7);
		break;
	case FAMILY_4:
		p_str += fam_str(4);
		p_str += type_str(3);
		p_str += type_str(5);
		break;
	case FAMILY_5:
		p_str += fam_str(5);
		break;
	case FAMILY_6:
		p_str += fam_str(6);
		break;
	case FAMILY_7:
		p_str += fam_str(7);
		break;
	case "无":
		p_str += type_str(8);
		break;
	}
	return rand_str(p_str);
}


string file_final_fam_lv(string fam,int lv)//根据门派、等级生成物品
{
	string *p_str = ({});
	if(lv<20){lv=20;}
	if(lv>120){lv=120;}
	if(lv != 119){lv = lv/5*5;}
	
	switch(fam)
	{
	default:
		return file_final_lv(lv);
		break;
	case FAMILY_1:
		p_str += fam_lv_str(1,lv);
		p_str += type_lv_str(2,lv);
		break;
	case FAMILY_2:
		p_str += fam_lv_str(2,lv);
		p_str += type_lv_str(4,lv);
		break;
	case FAMILY_3:
		p_str += fam_lv_str(3,lv);
		p_str += type_lv_str(6,lv);
		p_str += type_lv_str(7,lv);
		break;
	case FAMILY_4:
		p_str += fam_lv_str(4,lv);
		p_str += type_lv_str(3,lv);
		p_str += type_lv_str(5,lv);
		break;
	case FAMILY_5:
		p_str += fam_lv_str(5,lv);
		break;
	case FAMILY_6:
		p_str += fam_lv_str(6,lv);
		break;
	case FAMILY_7:
		p_str += fam_lv_str(7,lv);
		break;
	case "无":
		p_str += type_lv_str(8,lv);
		break;
	}
	return rand_str(p_str);
}

string file_final_fam_lv2(string fam,int lv1,int lv2)//根据门派、等级段生成物品
{
	string *p_str = ({});
	
	switch(fam)
	{
	default:
		return file_final_lv2(lv1,lv2);
		break;
	case FAMILY_1:
		p_str += fam_lv_str2(1,lv1,lv2);
		p_str += type_lv_str2(2,lv1,lv2);
		break;
	case FAMILY_2:
		p_str += fam_lv_str2(2,lv1,lv2);
		p_str += type_lv_str2(4,lv1,lv2);
		break;
	case FAMILY_3:
		p_str += fam_lv_str2(3,lv1,lv2);
		p_str += type_lv_str2(6,lv1,lv2);
		p_str += type_lv_str2(7,lv1,lv2);
		break;
	case FAMILY_4:
		p_str += fam_lv_str2(4,lv1,lv2);
		p_str += type_lv_str2(3,lv1,lv2);
		p_str += type_lv_str2(5,lv1,lv2);
		break;
	case FAMILY_5:
		p_str += fam_lv_str2(5,lv1,lv2);
		break;
	case FAMILY_6:
		p_str += fam_lv_str2(6,lv1,lv2);
		break;
	case FAMILY_7:
		p_str += fam_lv_str2(7,lv1,lv2);
		break;
	case "无":
		p_str += type_lv_str2(8,lv1,lv2);
		break;
	}
	return rand_str(p_str);
}


//根据类型和等级生成物品
string file_final_type_lv(int type,int lv)
{
	string *p_str = ({});
	switch(type)
	{
	default:
		p_str += all_str();
		break;
	case ARMOR_TYPE:
		p_str = type_lv_str(0,lv);
		break;
	case HEAD_TYPE:
		p_str = type_lv_str(1,lv);
		break;
	case UNARMED:
		p_str = type_lv_str(2,lv);
		break;
	case THROWING:
		p_str = type_lv_str(3,lv);
		break;
	case BLADE:
		p_str = type_lv_str(4,lv);
		break;
	case SWORD:
		p_str = type_lv_str(5,lv);
		break;
	case SPEAR:
		p_str = type_lv_str(6,lv);
		break;
	case STICK:
		p_str = type_lv_str(7,lv);
		break;
	case SWORD:
		p_str = type_lv_str(8,lv);
		break;
	case NECK_TYPE:
		p_str = type_lv_str(9,lv);
		break;
	case BOOTS_TYPE:
		p_str = type_lv_str(10,lv);
		break;
	}
	return rand_str(p_str);
}

//根据类型和等级段生成物品
string file_final_type_lv2(int type,int lv1,int lv2)
{
	string *p_str = ({});
	switch(type)
	{
	default:
		p_str += all_str();
		break;
	case ARMOR_TYPE:
		p_str = type_lv_str2(0,lv1,lv2);
		break;
	case HEAD_TYPE:
		p_str = type_lv_str2(1,lv1,lv2);
		break;
	case UNARMED:
		p_str = type_lv_str2(2,lv1,lv2);
		break;
	case THROWING:
		p_str = type_lv_str2(3,lv1,lv2);
		break;
	case BLADE:
		p_str = type_lv_str2(4,lv1,lv2);
		break;
	case SWORD:
		p_str = type_lv_str2(5,lv1,lv2);
		break;
	case SPEAR:
		p_str = type_lv_str2(6,lv1,lv2);
		break;
	case STICK:
		p_str = type_lv_str2(7,lv1,lv2);
		break;
	case SWORD:
		p_str = type_lv_str2(8,lv1,lv2);
		break;
	case NECK_TYPE:
		p_str = type_lv_str2(9,lv1,lv2);
		break;
	case BOOTS_TYPE:
		p_str = type_lv_str2(10,lv1,lv2);
		break;
	}
	return rand_str(p_str);
}

//根据类型和门派生成物品
string file_final_fam_type(string fam,int type)
{
	string *p_str = ({});
	switch(fam)
	{
	default:
		p_str += all_str();
		break;
	case FAMILY_1:
		if(type>1 && type<9){if(type == 2){p_str += type_str(type);}}
		else{p_str += fam_type_str(1,type);}	
		break;
	case FAMILY_2:
		if(type>1 && type<9){if(type == 4){p_str += type_str(type);}}
		else{p_str += fam_type_str(2,type);}
		break;
	case FAMILY_3:
		if(type>1 && type<9){if(type == 6 || type == 7){p_str += type_str(type);}}
		else{p_str += fam_type_str(3,type);}
		break;
	case FAMILY_4:
		if(type>1 && type<9){if(type == 3 || type == 5){p_str += type_str(type);}}
		else
		{p_str += fam_type_str(4,type);}
		break;
	case FAMILY_5:
		if(!(type>1 && type<9)){p_str += fam_type_str(5,type);}
		break;
	case FAMILY_6:
		if(!(type>1 && type<9)){p_str += fam_type_str(6,type);}
		break;
	case FAMILY_7:
		if(!(type>1 && type<9)){p_str += fam_type_str(7,type);}
		break;
	case "无":
		if(!(type>1 && type<9)){p_str += fam_type_str(8,type);}
		break;
	}
	return rand_str(p_str);
}

//根据门派、类型、等级生成物品

string file_final_fam_type_lv(string fam,int type,int lv)
{
	
	string *p_str = ({});
	switch(type)
	{
	default:
		type = random(11);
		break;
	case ARMOR_TYPE:
		type = 0;
		break;
	case HEAD_TYPE:
		type = 1;
		break;
	case UNARMED:
		type = 2;
		break;
	case THROWING:
		type = 3;
		break;
	case BLADE:
		type = 4;
		break;
	case SWORD:
		type = 5;
		break;
	case SPEAR:
		type = 6;
		break;
	case STICK:
		type = 7;
		break;
	case SWORD:
		type = 8;
		break;
	case NECK_TYPE:
		type = 9;
		break;
	case BOOTS_TYPE:
		type = 10;
		break;
	}
	
	switch(fam)
	{
	default:
		p_str += all_str();
		break;
	case FAMILY_1:
		if(type>1 && type<9){if(type == 2){p_str += type_lv_str(type,lv);}}
		else{p_str += fam_type_lv_str(1,type,lv);}
		break;
	case FAMILY_2:
		if(type>1 && type<9){if(type == 4){p_str += type_lv_str(type,lv);}}
		else{p_str += fam_type_lv_str(2,type,lv);}
		break;
	case FAMILY_3:
		if(type>1 && type<9){if(type == 6 || type == 7){p_str += type_lv_str(type,lv);}}
		else{p_str += fam_type_lv_str(3,type,lv);}
		break;
	case FAMILY_4:
		if(type>1 && type<9){if(type == 3 || type == 5){p_str += type_lv_str(type,lv);}}
		else
		{p_str += fam_type_lv_str(4,type,lv);}
		break;
	case FAMILY_5:
		if(!(type>1 && type<9)){p_str += fam_type_lv_str(5,type,lv);}
		break;
	case FAMILY_6:
		if(!(type>1 && type<9)){p_str += fam_type_lv_str(6,type,lv);}
		break;
	case FAMILY_7:
		if(!(type>1 && type<9)){p_str += fam_type_lv_str(7,type,lv);}
		break;
	case "无":
		if(!(type>1 && type<9)){p_str += fam_type_lv_str(8,type,lv);}
		break;
	}
	return rand_str(p_str);	
}


//根据门派、类型、等级段生成物品

string file_final_fam_type_lv2(string fam,int type,int lv1,int lv2)
{
	string *p_str = ({});
	
	switch(type)
	{
	default:
		type = random(11);
		break;
	case ARMOR_TYPE:
		type = 0;
		break;
	case HEAD_TYPE:
		type = 1;
		break;
	case UNARMED:
		type = 2;
		break;
	case THROWING:
		type = 3;
		break;
	case BLADE:
		type = 4;
		break;
	case SWORD:
		type = 5;
		break;
	case SPEAR:
		type = 6;
		break;
	case STICK:
		type = 7;
		break;
	case SWORD:
		type = 8;
		break;
	case NECK_TYPE:
		type = 9;
		break;
	case BOOTS_TYPE:
		type = 10;
		break;
	}
	
	switch(fam)
	{
	default:
		p_str += all_str();
		break;
	case FAMILY_1:
		if(type>1 && type<9){if(type == 2){p_str += type_lv_str2(type,lv1,lv2);}}
		else{p_str += fam_type_lv_str2(1,type,lv1,lv2);}
		break;
	case FAMILY_2:
		if(type>1 && type<9){if(type == 4){p_str += type_lv_str2(type,lv1,lv2);}}
		else{p_str += fam_type_lv_str2(2,type,lv1,lv2);}
		break;
	case FAMILY_3:
		if(type>1 && type<9){if(type == 6 || type == 7){p_str += type_lv_str2(type,lv1,lv2);}}
		else{p_str += fam_type_lv_str2(3,type,lv1,lv2);}
		break;
	case FAMILY_4:
		if(type>1 && type<9){if(type == 3 || type == 5){p_str += type_lv_str2(type,lv1,lv2);}}
		else
		{p_str += fam_type_lv_str2(4,type,lv1,lv2);}
		break;
	case FAMILY_5:
		if(!(type>1 && type<9)){p_str += fam_type_lv_str2(5,type,lv1,lv2);}
		break;
	case FAMILY_6:
		if(!(type>1 && type<9)){p_str += fam_type_lv_str2(6,type,lv1,lv2);}
		break;
	case FAMILY_7:
		if(!(type>1 && type<9)){p_str += fam_type_lv_str2(7,type,lv1,lv2);}
		break;
	case "无":
		if(!(type>1 && type<9)){p_str += fam_type_lv_str2(8,type,lv1,lv2);}
		break;
	}
	return rand_str(p_str);	
}

//对外函数 不需要的参数string 用“”，int 用 -1;
string file_final(string fam,int type,int lv1,int lv2)
{
	int f=1,t=1,v1=1,v2=1;
	string str;
	string *p_str = ({});
	
	if(fam == ""){f=0;}
	if(type == -1){t = 0;}
	if(lv1 == -1){v1= 0;}
	if(lv2 == -1){v2= 0;}
		
	
		
	switch(sprintf("%d%d%d%d",f,t,v1,v2))
	{
	default:
		p_str += all_str();
		break;
	case "0000":
		p_str += all_str();
		break;
	case "1000":
		return file_final_fam(fam);
		break;
	case "0100":
		return file_final_type(type);
		break;
	case "0010":
		return file_final_lv(lv1);
		break;
	case "0001":
		return file_final_lv2(0,lv2);
		break;
	case "1100":
		return file_final_fam_type(fam,type);
		break;
	case "1010":
		return file_final_fam_lv(fam,lv1);
		break;
	case "1001":
		return file_final_fam_lv2(fam,0,lv2);
		break;
	case "0110":
		return file_final_type_lv(type,lv1);
		break;
	case "0101":
		return file_final_type_lv2(type,0,lv2);
		break;
	case "0011":
		return file_final_lv2(lv1,lv2);
		break;
	case "1110":
		return file_final_fam_type_lv(fam,type,lv1);
		break;
	case "1101":
		return file_final_fam_type_lv2(fam,type,0,lv2);
		break;
	case "1011":
		return file_final_fam_lv2(fam,lv1,lv2);
		break;
	case "0111":
		return file_final_type_lv2(type,lv1,lv2);
		break;
	case "1111":
		return file_final_fam_type_lv2(fam,type,lv1,lv2);
		break;
	}
	return rand_str(p_str);
}
		