//this example code shows how to put some text in nametable
//it assumes that you have ASCII-encoded font in the CHR tiles $00-$3f
//it also shows how to detect PAL/NTSC video system

#include "neslib.h"



//put a string into the nametable

void put_str(unsigned int adr,const char *str)
{
	vram_adr(adr);

	while(1)
	{
		if(!*str) break;

		vram_put((*str++)-0x20);//-0x20 because ASCII code 0x20 is placed in tile 0 of the CHR
	}
}



void main(void)
{
	//rendering is disabled at the startup, the palette is all black

	pal_col(1,0x30);//set while color

	//you can't put data into vram through vram_put while rendering is enabled
	//so you have to disable rendering to put things like text or a level map
	//into the nametable

	//there is a way to update small number of nametable tiles while rendering
	//is enabled, using set_vram_update and an update list

	put_str(NTADR_A(2,2),"HELLO, WORLD!");
	put_str(NTADR_A(2,6),"THIS CODE PRINTS SOME TEXT");
	put_str(NTADR_A(2,7),"USING ASCII-ENCODED CHARSET");
	put_str(NTADR_A(2,8),"(WITH CAPITAL LETTERS ONLY)");
	put_str(NTADR_A(2,10),"TO USE CHR MORE EFFICIENTLY");
	put_str(NTADR_A(2,11),"YOU'D NEED A CUSTOM ENCODING");
	put_str(NTADR_A(2,12),"AND A CONVERSION TABLE");

	put_str(NTADR_A(2,16),"CURRENT VIDEO MODE IS");

	if(ppu_system()) put_str(NTADR_A(24,16),"NTSC"); else put_str(NTADR_A(24,16),"PAL");

	ppu_on_all();//enable rendering

	while(1);//do nothing, infinite loop
}