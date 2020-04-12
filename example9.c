//this example shows non-looped vertical scroll in the most primitive form
//it just puts random tiles on each new row, metatiles and tile attributes aren't used
//it would be impractical for a real game, but it shows the basics
//horizontal mirroring (gives 32x60 nametable layout) is used to hide the changing row

#include "neslib.h"


static unsigned char update_list[3+32+1];


//these macro are needed to simplify defining update list constants

#define NTADR(x,y)	((NAMETABLE_A|((y)<<5)|x))

#define MSB(x)		(((x)>>8))
#define LSB(x)		(((x)&0xff))



void main(void)
{
	static unsigned char i,row;
	static int y;
	static unsigned int adr;

	pal_col(1,0x30);//set while color
	
	y=0;
	
	update_list[0]=0x20|NT_UPD_HORZ;//horizontal update sequence, dummy address
	update_list[1]=0x00;
	update_list[2]=32;//update sequence is 32 tiles wide
	update_list[3+32]=NT_UPD_EOF;
	
	set_vram_update(update_list);

	ppu_on_all();//enable rendering
	
	while(1)
	{
		scroll(0,y);//scroll value will be applied on the next nmi

		if(!(y&7))//put new row every 8 pixels
		{
			row=(y>>3)+59;//get row number for update, it is shifted just above the visible part of the screen
			
			if(row>=60) row-=60;//keep the row number within the limits
			
			adr=row<<5;//convert Y from pixels to tiles (row=y/8), then to nametable offset (offset=row*32)
			
			if(adr<960) adr=adr|NAMETABLE_A; else adr=(adr-960)|NAMETABLE_C;//add base address of one of two nametables
			
			update_list[0]=MSB(adr)|NT_UPD_HORZ;//set the address
			update_list[1]=LSB(adr);
			
			for(i=0;i<32;++i) update_list[3+i]=0x10+(rand8()&7);//fill row buffer with random tiles
		}

		--y;//next pixel
		
		if(y<0) y=240*2-1;//keep Y within the total height of two nametables

		ppu_wait_nmi();
	}
}
