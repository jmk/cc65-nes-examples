//this example shows how to set up a palette and use 8x8 HW sprites
//also shows how fast (or slow) C code is

#include "neslib.h"


//general purpose vars

static unsigned char i,j;
static unsigned char spr;

//total number of balls on the screen
//since there are 64 HW sprites, it is absolute max

#define BALLS_MAX	64

//balls parameters

static unsigned char ball_x[BALLS_MAX];
static unsigned char ball_y[BALLS_MAX];
static unsigned char ball_dx[BALLS_MAX];
static unsigned char ball_dy[BALLS_MAX];


//palette for balls, there are four sets for different ball colors

const unsigned char palSprites[16]={
	0x0f,0x17,0x27,0x37,
	0x0f,0x11,0x21,0x31,
	0x0f,0x15,0x25,0x35,
	0x0f,0x19,0x29,0x39
};



void main(void)
{
	pal_spr(palSprites);//set palette for sprites

	ppu_on_all();//enable rendering

	//initialize balls parameters

	for(i=0;i<BALLS_MAX;++i)
	{
		//starting coordinates

		ball_x[i]=rand8();
		ball_y[i]=rand8();

		//direction bits

		j=rand8();

		//horizontal speed -3..-3, excluding 0
		spr=1+(rand8()%3);
		ball_dx[i]=j&1?-spr:spr;

		//vertical speed

		spr=1+(rand8()%3);
		ball_dy[i]=j&2?-spr:spr;
	}

	
	//now the main loop

	while(1)
	{
		ppu_wait_frame();//wait for next TV frame

		spr=0;

		for(i=0;i<BALLS_MAX;++i)
		{
			//set a sprite for current ball

			spr=oam_spr(ball_x[i],ball_y[i],0x40,i&3,spr);//0x40 is tile number, i&3 is palette

			//move the ball

			ball_x[i]+=ball_dx[i];
			ball_y[i]+=ball_dy[i];

			//bounce the ball off the edges

			if(ball_x[i]>=(256-8)) ball_dx[i]=-ball_dx[i];
			if(ball_y[i]>=(240-8)) ball_dy[i]=-ball_dy[i];
		}
	}
}