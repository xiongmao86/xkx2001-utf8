//Cracked by Roath
// Room: /d/beijing/west/hubianxiaodao1.c

inherit ROOM;

void create()
{
	set("short", "湖边小道");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"zhonghaixian",
  "east" : __DIR__"zhonghaibeian",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
