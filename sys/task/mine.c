#include <ansi.h>
#include <task.h>
#define MAX_MINE 	8
// 函数：生成二进制码
void SAVE_BINARY() { }
mapping mpScene = ([
		281: ({
		({45, 133}),
		({46, 170}),
		({62, 122}),
		({67, 187}),
		({70, 131}),
		({76, 111}),
		({81, 184}),
		({87, 101}),
		({87, 122}),
		({90, 192}),
		({103, 87}),
		({104, 179}),
		({111, 127}),
		({119, 165}),
		({127, 99 }),
		({136, 129}),
		({160, 52 }),
		({176, 78 }),
		({184, 44 }),
		({189, 68 }),
		({198, 19 }),
		({200, 106}),
		({215, 28 }),
		({223, 61 }),
		({229, 60 }),
		({237, 45 }),
		({252, 53 }),
		({254, 55 }),
				}), 
		283: ({				
		({41, 146}),
		({46, 152}),
		({50, 132}),
		({63, 176}),
		({65, 122}),
		({69, 164}),
		({79, 140}),
		({83, 157}),
		({86, 127}),
		({89, 144}),
		({96, 125}),
		({99, 114}),
		({109, 107}),
		({113, 123}),
		({132, 93}),
		({136, 99}),
		({141, 81}),
		({166, 72}),
		({177, 38}),
		({177, 49}),
		({188, 28}),
		({194, 37}),
		({199, 26}),
		({199, 64}),
		({218, 54}),
			}), 
		]);            
mapping mpMine = ([]);
void create()
{
	call_out("check_mine",10);
}

void check_mine()
{
	int *nScene,i,size,j,count,*nXy;
	object *nMine,npc,*nTmp;
	mixed *nPlace;
	
	remove_call_out("check_mine");
	call_out("check_mine",300);

	if ( !mapp(mpMine) )
		mpMine = ([]);
	nScene = keys(mpScene);
	for(i=0,size=sizeof(nScene);i<size;i++)
	{
		nMine = mpMine[nScene[i]];
		if ( !arrayp(nMine) )
			nMine = ({});
		nTmp = ({});
		for(count=sizeof(nMine),j=0;j<count;j++)
		{
			if ( objectp(nMine[j]) )
				continue;
			nTmp += ({ nMine[j] });	
		}
		nMine -= nTmp;	
		nPlace = mpScene[nScene[i]];
		for(j=0,count = MAX_MINE - sizeof(nMine);j<count;j++)
		{
			npc = new("npc/00/2002");
			if ( !npc )
				return ;
			nXy = nPlace[random(sizeof(nPlace))];
			nPlace -= ({nXy});
			npc->add_to_scene(nScene[i],nXy[0],nXy[1]);
			nMine += ({npc});
		}
		mpMine[nScene[i]] = nMine;
	}
}

void dest_obj(int scene ,int i)
{
	object *nTmp,npc;
	
	nTmp = mpMine[scene];
	if ( !arrayp(nTmp) )
		return ;
	npc = nTmp[i];
	if ( !objectp(npc) )
		return ;	

	npc->remove_from_scene();
	destruct(npc);
}


















