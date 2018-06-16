//Cracked by Roath
// 飞来峰
// Dong  11/03/1996.
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{   set("short", "龙泓洞");
    set("long", @LONG
又叫通天洞。在洞口的岩壁上刻有姿态各异，一丈多高的佛像六
尊。左下方有两组浮雕。前一组记述了唐僧取经的故事；後一组为白
马驮经，刻有“竺法阑”，“聂摩腾”字样。东边是下山的路。小路
往上延伸向西北。
LONG);
    set("exits", ([ /* sizeof() == 2 */ 
        "northwest" : __DIR__"feilai2", 			
        "eastdown" : __DIR__"feilai0", 			
                ])
       );
	set("cost", 3);
    setup();
    replace_program(ROOM);
}