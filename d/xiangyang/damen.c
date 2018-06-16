//Cracked by Roath
// Room: /d/xiangyang/damen.c

inherit ROOM;

void create()
{
	set("short", "郭府大门");
	set("long", @LONG
这里就是镇守襄阳的大侠郭靖的府邸，红柱碧瓦，规模宏大，
古朴淡雅。蒙古大军攻城正急，郭府上下无不谨慎戒备。向南是一
路青石铺地，直通大厅。
LONG
	);
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"dating",
  "north" : __DIR__"jzjie4",
]));

	setup();
	replace_program(ROOM);
}
