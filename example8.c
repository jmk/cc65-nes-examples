//this example shows music and sound effects use

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
	static unsigned char i,pause;

	pause=FALSE;
	
	pal_col(1,0x30);//set while color
	
	put_str(NTADR_A(2,2),"MUSIC ANS SFX EXAMPLE");
	put_str(NTADR_A(2,4),"A     TO PLAY MUSIC");
	put_str(NTADR_A(2,5),"B     TO STOP MUSIC");
	put_str(NTADR_A(2,6),"START TO PAUSE MUSIC");
	put_str(NTADR_A(2,8),"D-PAD TO PLAY SFX");
	
	ppu_on_all();//enable rendering
	
	while(1)
	{
		ppu_wait_frame();
		
		i=pad_trigger(0);
		
		if(i&PAD_A)
		{
			music_play(0);
			pause=FALSE;
		}
		
		if(i&PAD_B)
		{
			music_stop();
			pause=FALSE;
		}
		
		if(i&PAD_START)
		{
			pause^=TRUE;
			music_pause(pause);
		}
		
		if(i&PAD_LEFT)  sfx_play(0,0);
		if(i&PAD_RIGHT) sfx_play(1,1);
		if(i&PAD_UP)    sfx_play(2,2);
		if(i&PAD_DOWN)  sfx_play(3,3);
	}
}