#include "Images.h"

extern unsigned char ImageCarData[];
extern unsigned char ImageFloorData[];
extern unsigned char ImageMchData[];
extern unsigned char ImageTreeData[];

Image ImageCar = {
	"car",
	128, 128, 3,
	ImageCarData,
};

Image ImageFloor = {
	"floor",
	128, 128, 3,
	ImageFloorData,
};

Image ImageMch = {
	"mch",
	128, 128, 3,
	ImageMchData
};

Image ImageTree = {
	"tree",
	128, 128, 3,
	ImageTreeData
};