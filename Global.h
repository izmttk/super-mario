#pragma once
#ifndef  _GLOBAL_H_
#define _GLOBAL_H_
#define WINDOWS_WIDTH 700
#define WINDOWS_HEIGHT 504

#define unit_length 36

#define DEBUG
#ifdef DEBUG
#include<iostream>
#include<cstdio>
using namespace std;
#endif

#define RIGHT 0
#define LEFT 1

#include<graphics.h>
void rotateFlip(IMAGE* img);


#endif