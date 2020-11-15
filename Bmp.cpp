#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>

BITMAPINFO* lpBitsInfo = NULL;

//文件读取
BOOL LoadBmpFile(char* BmpFileName) {
	FILE* fp;
	BITMAPFILEHEADER bmpFileHeader;		//文件头结构
	BITMAPINFOHEADER bmpInfo;			//信息头结构

	if ((fp = fopen(BmpFileName, "rb")) == NULL)
		return FALSE;

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读出文件头信息
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, fp);		//读出信息头信息

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int lineBytes = (width*bmpInfo.biBitCount + 31)/32*4;		//每一行像素占的字节数

	DWORD numColors = bmpInfo.biClrUsed;
	numColors = 0;
	if (bmpInfo.biClrUsed == 0) {
		switch (bmpInfo.biBitCount) {
			case 1: numColors = 2; break;
			case 4: numColors = 16; break;
			case 8: numColors = 256; break;
			case 24: numColors = 0; break;
		}
	}
	else
		numColors = bmpInfo.biClrUsed;

	long size = 40 + numColors*4 + lineBytes*height;
	if (!(lpBitsInfo = (BITMAPINFO*)malloc(size)))
		return FALSE;

	fseek(fp, 14, SEEK_SET);				//偏移掉14个字节大小的信息头
	fread((char*)lpBitsInfo, size, 1, fp);	//将信息头、调色板和图像数据读入内存

	lpBitsInfo->bmiHeader.biClrUsed = numColors;	//刷新用到的颜色数

	fclose(fp);

	return TRUE;
}

BOOL gray() {
	//准备必要的信息
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int lineBytes = (width*lpBitsInfo->bmiHeader.biBitCount + 31)/32*4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	//新的表示颜色的位数、新的使用颜色数、灰度划分的倍率
	int newBiBitCount, newPaletteSize;
	switch (lpBitsInfo->bmiHeader.biBitCount) {
	case 1:
		newBiBitCount = 1;
		newPaletteSize = 2;
		break;
	case 4:
		newBiBitCount = 4;
		newPaletteSize = 16;
		break;
	case 8:
		newBiBitCount = 8;
		newPaletteSize = 256;
		break;
	case 24:
		newBiBitCount = 8;
		newPaletteSize = 256;
		break;
	}

	//分配大小
	int newLineBytes = (width*newBiBitCount + 31)/32*4;
	long size = 40 + newPaletteSize*4 + newLineBytes*height;
	BITMAPINFO* newLpBitsInfo = (BITMAPINFO*)malloc(size);
	if (NULL == newLpBitsInfo) {
		AfxMessageBox("内存分配失败！");
		return FALSE;
	}

	//为新分配的空间填入信息
	int i, j, avg;
	if (24 == lpBitsInfo->bmiHeader.biBitCount) {				//如果是24位真彩图像
		memcpy(newLpBitsInfo, lpBitsInfo, 40);					//填入信息头
		newLpBitsInfo->bmiHeader.biBitCount = newBiBitCount;	//更新灰度图像颜色位数
		newLpBitsInfo->bmiHeader.biClrUsed = newPaletteSize;	//【更新灰度图像调色板大小】

		//填入调色板内容
		for (i = 0; i < (newLpBitsInfo->bmiHeader.biClrUsed); i++) {
			newLpBitsInfo->bmiColors[i].rgbRed = i;
			newLpBitsInfo->bmiColors[i].rgbGreen = i;
			newLpBitsInfo->bmiColors[i].rgbBlue = i;
			newLpBitsInfo->bmiColors[i].rgbReserved = 0;
		}

		//更新图像数据
		BYTE* newLpBits = (BYTE*)&newLpBitsInfo->bmiColors[newLpBitsInfo->bmiHeader.biClrUsed];
		BYTE *pPixelR, *pPixelG, *pPixelB, *newPixel;
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				pPixelB = lpBits + lineBytes*(height - 1 - i) + j*3;
				pPixelG = pPixelB + 1;
				pPixelR = pPixelG + 1;
				avg = (*pPixelR + *pPixelG + *pPixelB)/3;

				newPixel = newLpBits + newLineBytes*(height - 1 - i) + j;
				*newPixel = avg;
			}
		}
	}
	else {
		//为新分配的空间填入信息
		memcpy(newLpBitsInfo, lpBitsInfo, size);
		//更新调色板数据
		int r, g, b;
		for (i = 0; i < newPaletteSize; i++) {
			r = newLpBitsInfo->bmiColors[i].rgbRed;
			g = newLpBitsInfo->bmiColors[i].rgbGreen;
			b = newLpBitsInfo->bmiColors[i].rgbBlue;
			avg = (r + g + b)/3;
			newLpBitsInfo->bmiColors[i].rgbRed = avg;
			newLpBitsInfo->bmiColors[i].rgbGreen = avg;
			newLpBitsInfo->bmiColors[i].rgbBlue = avg;
		}
	}

	//释放旧内存，更新指针
	BITMAPINFO* temp = lpBitsInfo;
	lpBitsInfo = newLpBitsInfo;
	free(temp);
	
	return true;
}

BOOL isGray() {
	if (24 == lpBitsInfo->bmiHeader.biBitCount)
		return FALSE;
	else {
		int rHead, gHead, bHead, rMid, gMid, bMid, rEnd, gEnd, bEnd;
		BOOL boolHead, boolMid, boolEnd;

		int head = 0;	//调色板第一个颜色
		int mid = 1<<(lpBitsInfo->bmiHeader.biBitCount - 1);	//调色板中间颜色
		int end = (1<<(lpBitsInfo->bmiHeader.biBitCount)) - 1;	//调色板最后一个颜色
		rHead = lpBitsInfo->bmiColors[head].rgbRed;
		gHead = lpBitsInfo->bmiColors[head].rgbGreen;
		bHead = lpBitsInfo->bmiColors[head].rgbBlue;
		rMid = lpBitsInfo->bmiColors[mid].rgbRed;
		gMid = lpBitsInfo->bmiColors[mid].rgbGreen;
		bMid = lpBitsInfo->bmiColors[mid].rgbBlue;
		rEnd = lpBitsInfo->bmiColors[end].rgbRed;
		gEnd = lpBitsInfo->bmiColors[end].rgbGreen;
		bEnd = lpBitsInfo->bmiColors[end].rgbBlue;

		boolHead = (rHead == gHead && gHead == bHead);		//判断第一个颜色是灰色
		if (1 == lpBitsInfo->bmiHeader.biBitCount)			//如果是二值图像
			boolMid = TRUE;
		else 
			boolMid = (rMid == gMid && gMid == bMid);		//判断第二个颜色是灰色
		boolEnd = (rEnd == gEnd && gEnd == bEnd);			//判断第三个颜色是灰色

		if (boolHead && boolMid && boolEnd)
			return TRUE;
		else
			return FALSE;
	}
}

void pixel(int i, int j, char* str) {
	if (NULL == lpBitsInfo)
		return;

	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int lineBytes = (width*lpBitsInfo->bmiHeader.biBitCount + 31)/32*4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	if (i >= width || j >= height)
		return;
	
	BYTE *pixel, bv;
	int r, g ,b;

	switch (lpBitsInfo->bmiHeader.biBitCount) {
	case 8:
		pixel = lpBits + lineBytes * (height - 1 - i) + j;
		if (isGray())
			sprintf(str, "灰度值：%d", *pixel);
		else {
			r = lpBitsInfo->bmiColors[*pixel].rgbRed;
			g = lpBitsInfo->bmiColors[*pixel].rgbGreen;
			b = lpBitsInfo->bmiColors[*pixel].rgbBlue;
			sprintf(str, "RGB(%d,%d,%d)", r, g, b);
		}
		break;
	case 24:
		pixel = lpBits + lineBytes*(height - 1 - i) + j*3;
		r = *pixel;
		g = *(pixel + 1);
		b = *(pixel + 2);
		sprintf(str, "RGB(%d,%d,%d)", r, g, b);
		break;
	case 4:
		bv = *(lpBits + lineBytes*(height - 1 - i) + j/2);
		if (0 == j%2)
			bv = bv>>4;
		else
			bv = bv&15;
		if (isGray()) {
			sprintf(str, "灰度值：%d", lpBitsInfo->bmiColors[bv].rgbBlue);
		}
		else {
			r = lpBitsInfo->bmiColors[bv].rgbRed;
			g = lpBitsInfo->bmiColors[bv].rgbGreen;
			b = lpBitsInfo->bmiColors[bv].rgbBlue;
			sprintf(str, "RGB(%d,%d,%d)", r, g, b);
		}
		break;
	case 1:
		bv = *(lpBits + lineBytes*(height - 1 - i) + j/8) & (1<<(7 - j%8));
		if (0 == bv)
			strcpy(str, "背景点");
		else 
			strcpy(str, "前景点");
		break;
	}
}

DWORD H[256];
void Histogram() {
	// 【不同位数颜色的直方图、彩色直方图】
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int lineBytes = (width*lpBitsInfo->bmiHeader.biBitCount + 31)/32*4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i, j;
	BYTE* pixel;

	for (i = 0; i < 256; i++)
		H[i] = 0;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			pixel = lpBits + lineBytes*(height - 1 - i) + j;
			H[*pixel]++;
		}
	}	
}

void pixelOperation();	//点运算函数