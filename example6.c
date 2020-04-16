//this example shows virtual brightness control
//press up or down to change background brightness,
//press left or right to change sprite brightness

#include "neslib.h"

#include "test_nam.h"	//packed nametable data



const unsigned char palBG [16]={ 0x0f,0x21,0x10,0x30,0x0f,0x14,0x21,0x31,0x0f,0x29,0x16,0x26,0x0f,0x09,0x19,0x29 };
const unsigned char palSpr[16]={ 0x0f,0x17,0x27,0x37,0x0f,0x11,0x21,0x31,0x0f,0x15,0x25,0x35,0x0f,0x19,0x29,0x39 };



void main(void)
{
	static unsigned char i,bg_bright,spr_bright;

	//rendering is disabled at the startup, and palette is all black

	pal_bg(palBG);//set background palette
	pal_spr(palSpr);//set sprite palette

	vram_adr(NAMETABLE_A);//unpack nametable into VRAM
	vram_unrle(test_nam);

	for(i=0;i<64;++i)//display random sprites
	{
		oam_spr(rand8(),rand8(),0x40,rand8()&3,i<<2);
	}

	ppu_on_all();//enable rendering

	bg_bright=4;//normal bright
	spr_bright=4;

	while(1)
	{
		pal_bg_bright(bg_bright);
		pal_spr_bright(spr_bright);

		ppu_wait_frame();

		i=pad_trigger(0);

		if(i&PAD_UP)    if(bg_bright<8) ++bg_bright;
		if(i&PAD_DOWN)  if(bg_bright>0) --bg_bright;

		if(i&PAD_RIGHT) if(spr_bright<8) ++spr_bright;
		if(i&PAD_LEFT)  if(spr_bright>0) --spr_bright;
	}
}