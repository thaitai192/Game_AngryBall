#ifndef __DEFINE_H__
#define __DEFINE_H__

#define RGB_RGBA(x) (x==24)?GL_RGB:GL_RGBA

const unsigned char MOVE_FORWARD	=	1<<0;
const unsigned char MOVE_BACKWARD	=	1<<1;
const unsigned char MOVE_LEFT		=	1<<2;
const unsigned char MOVE_RIGHT		=	1<<3;

const unsigned char ROTATION_UP		=	1<<4;
const unsigned char ROTATION_DOWN	=	1<<5;
const unsigned char ROTATION_LEFT	=	1<<6;
const unsigned char ROTATION_RIGHT	=	1<<7;

#endif