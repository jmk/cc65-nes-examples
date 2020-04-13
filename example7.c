//this example shows background scrolling and screen split using the sprite 0 hit flag
//(non-transparent part of the sprite 0 overlaps non-transparent part of the background)

#include "neslib.h"

#include "bgsplit_nam.h"	//packed nametable data

const unsigned char palette[16]={ 0x0f,0x16,0x27,0x38,0x0f,0x01,0x21,0x11,0x0f,0x19,0x29,0x3a,0x0f,0x09,0x19,0x29 }; //palette data


void main(void)
{
	static unsigned char top_x,bottom_x;
	
	//rendering is disabled at the startup, and palette is all black
	
	pal_bg(palette);//set background palette from an array
	pal_spr(palette);//set the same palette for sprites

	vram_adr(NAMETABLE_A);//unpack nametable into VRAM
	vram_unrle(bgsplit_nam);

	oam_spr(0,111,0x42,0,0);//put sprite at the screen split point
	
	ppu_on_all();//enable rendering

	top_x=0;
	bottom_x=0;
	
	while(1)
	{
		scroll(top_x,0);//set normal scroll, it'll be applied at beginning of a TV frame
		
		ppu_wait_nmi();//not ppu_wait_frame, because every 6th frame would not have the split
		
		split(bottom_x,0);//set scroll below the screen split point
		
		++top_x;
		--bottom_x;
	}
}