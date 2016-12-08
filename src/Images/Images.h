#pragma once

/**
 * Simple class representing built-in textures
 */
typedef struct IMAGE {
	const char*		name;
	unsigned int  	width;
	unsigned int  	height;
	unsigned int  	bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char* 	pixel_data;
} Image;