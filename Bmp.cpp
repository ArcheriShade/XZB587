#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>

BITMAPINFO* lpBitsInfo = NULL;

//�ļ���ȡ
BOOL LoadBmpFile(char* BmpFileName) {
	FILE* fp;
	BITMAPFILEHEADER bmpFileHeader;		//�ļ�ͷ�ṹ
	BITMAPINFOHEADER bmpInfo;			//��Ϣͷ�ṹ

	if ((fp = fopen(BmpFileName, "rb")) == NULL)
		return FALSE;

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//�����ļ�ͷ��Ϣ
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, fp);		//������Ϣͷ��Ϣ

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int lineBytes = (width*bmpInfo.biBitCount + 31)/32*4;		//ÿһ������ռ���ֽ���

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

	fseek(fp, 14, SEEK_SET);				//ƫ�Ƶ�14���ֽڴ�С����Ϣͷ
	fread((char*)lpBitsInfo, size, 1, fp);	//����Ϣͷ����ɫ���ͼ�����ݶ����ڴ�

	lpBitsInfo->bmiHeader.biClrUsed = numColors;	//ˢ���õ�����ɫ��

	fclose(fp);

	return TRUE;
}

BOOL gray() {
	//׼����Ҫ����Ϣ
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int lineBytes = (width*lpBitsInfo->bmiHeader.biBitCount + 31)/32*4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	//�µı�ʾ��ɫ��λ�����µ�ʹ����ɫ�����ҶȻ��ֵı���
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

	//�����С
	int newLineBytes = (width*newBiBitCount + 31)/32*4;
	long size = 40 + newPaletteSize*4 + newLineBytes*height;
	BITMAPINFO* newLpBitsInfo = (BITMAPINFO*)malloc(size);
	if (NULL == newLpBitsInfo) {
		AfxMessageBox("�ڴ����ʧ�ܣ�");
		return FALSE;
	}

	//Ϊ�·���Ŀռ�������Ϣ
	int i, j, avg;
	if (24 == lpBitsInfo->bmiHeader.biBitCount) {				//�����24λ���ͼ��
		memcpy(newLpBitsInfo, lpBitsInfo, 40);					//������Ϣͷ
		newLpBitsInfo->bmiHeader.biBitCount = newBiBitCount;	//���»Ҷ�ͼ����ɫλ��
		newLpBitsInfo->bmiHeader.biClrUsed = newPaletteSize;	//�����»Ҷ�ͼ���ɫ���С��

		//�����ɫ������
		for (i = 0; i < (newLpBitsInfo->bmiHeader.biClrUsed); i++) {
			newLpBitsInfo->bmiColors[i].rgbRed = i;
			newLpBitsInfo->bmiColors[i].rgbGreen = i;
			newLpBitsInfo->bmiColors[i].rgbBlue = i;
			newLpBitsInfo->bmiColors[i].rgbReserved = 0;
		}

		//����ͼ������
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
		//Ϊ�·���Ŀռ�������Ϣ
		memcpy(newLpBitsInfo, lpBitsInfo, size);
		//���µ�ɫ������
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

	//�ͷž��ڴ棬����ָ��
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

		int head = 0;	//��ɫ���һ����ɫ
		int mid = 1<<(lpBitsInfo->bmiHeader.biBitCount - 1);	//��ɫ���м���ɫ
		int end = (1<<(lpBitsInfo->bmiHeader.biBitCount)) - 1;	//��ɫ�����һ����ɫ
		rHead = lpBitsInfo->bmiColors[head].rgbRed;
		gHead = lpBitsInfo->bmiColors[head].rgbGreen;
		bHead = lpBitsInfo->bmiColors[head].rgbBlue;
		rMid = lpBitsInfo->bmiColors[mid].rgbRed;
		gMid = lpBitsInfo->bmiColors[mid].rgbGreen;
		bMid = lpBitsInfo->bmiColors[mid].rgbBlue;
		rEnd = lpBitsInfo->bmiColors[end].rgbRed;
		gEnd = lpBitsInfo->bmiColors[end].rgbGreen;
		bEnd = lpBitsInfo->bmiColors[end].rgbBlue;

		boolHead = (rHead == gHead && gHead == bHead);		//�жϵ�һ����ɫ�ǻ�ɫ
		if (1 == lpBitsInfo->bmiHeader.biBitCount)			//����Ƕ�ֵͼ��
			boolMid = TRUE;
		else 
			boolMid = (rMid == gMid && gMid == bMid);		//�жϵڶ�����ɫ�ǻ�ɫ
		boolEnd = (rEnd == gEnd && gEnd == bEnd);			//�жϵ�������ɫ�ǻ�ɫ

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
			sprintf(str, "�Ҷ�ֵ��%d", *pixel);
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
			sprintf(str, "�Ҷ�ֵ��%d", lpBitsInfo->bmiColors[bv].rgbBlue);
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
			strcpy(str, "������");
		else 
			strcpy(str, "ǰ����");
		break;
	}
}

DWORD H[256];
void Histogram() {
	// ����ͬλ����ɫ��ֱ��ͼ����ɫֱ��ͼ��
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

void pixelOperation();	//�����㺯��