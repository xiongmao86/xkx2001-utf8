//Cracked by Roath
// room: /d/city/beijiao3.c
// Jay 7/4/96
#include <ansi.h>;
inherit ROOM;

void create()
{

        set("short", HIG"草地"NOR);
        set("long", 
"这里是一遍绿茵茵的"+HIG"草地"NOR+"，像是一方绿色的毯子铺在地上。草丛中开着一些
不知名的小花，有"+HIR"红"NOR+"的、"+HIY"黄"NOR+"的，还有"+MAG"紫"NOR+"的。花瓣上、草叶上的"+HIC"露珠"NOR+"闪着晶莹的光。
东面是扬州城的北门。\n"
        );

        set("objects", ([
            "/d/wudang/npc/yetu" : 2,
        ]));


        set("exits", ([
                "east" : __DIR__"beimen",
                "west" : __DIR__"beijiao4",
        ]));
        set("outdoors","city");
        set("resource/grass", 1);
        set("cost", 2);
        setup();
        replace_program(ROOM);
}
