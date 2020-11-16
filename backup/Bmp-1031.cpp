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

	//fseek(fp, 0, SEEK_SET);

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//�����ļ�ͷ��Ϣ
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, fp);		//������Ϣͷ��Ϣ

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int lineBytes = (width*bmpInfo.biBitCount + 31)/32*4;		//ÿһ������ռ���ֽ���

	// int oo = bmpInfo.biBitCount;
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
	//24λ���ת��Ϊ256λ�Ҷ�
	if (!lpBitsInfo) {
		AfxMessageBox("����δ���κ�ͼ��");
		return FALSE;
	}

	//׼����Ҫ����Ϣ
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int lineBytes = (width*lpBitsInfo->bmiHeader.biBitCount + 31)/32*4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	//�µı�ʾ��ɫ��λ�����µ�ʹ����ɫ�����ҶȻ��ֵı���
	int newBiBitCount, newBiClrUsed, multiScale;
	switch (lpBitsInfo->bmiHeader.biClrUsed) {
	case 0:
		newBiBitCount = 8;
		newBiClrUsed = 256;
		multiScale = 1;
		break;
	case 2:
		newBiBitCount = 1;
		newBiClrUsed = 2;
		multiScale = 255;
		break;
	case 16:
		newBiBitCount = 4;
		newBiClrUsed = 16;
		multiScale = 17;
		break;
	case 256:
		newBiBitCount = 8;
		newBiClrUsed = 256;
		multiScale = 1;
		break;
	}

	//�����С
	int newLineBytes = (width*newBiBitCount + 31)/32*4;
	long size = 40 + newBiClrUsed*4 + newLineBytes*height;
	BITMAPINFO* newLpBitsInfo = (BITMAPINFO*)malloc(size);
	if (NULL == newLpBitsInfo) {
		AfxMessageBox("�ڴ����ʧ�ܣ�");
		return FALSE;
	}

	//Ϊ�·���Ŀռ�������Ϣ
	memcpy(newLpBitsInfo, lpBitsInfo, 40);					//������Ϣͷ
	newLpBitsInfo->bmiHeader.biBitCount = newBiBitCount;	//���»Ҷ�ͼ����ɫλ��
	newLpBitsInfo->bmiHeader.biClrUsed = newBiClrUsed;		//���»Ҷ�ͼ���ɫ���С

	//�����ɫ������
	int i, j;
	for (i = 0; i < (newLpBitsInfo->bmiHeader.biClrUsed); i++) {
		newLpBitsInfo->bmiColors[i].rgbRed = i*multiScale;
		newLpBitsInfo->bmiColors[i].rgbGreen = i*multiScale;
		newLpBitsInfo->bmiColors[i].rgbBlue = i*multiScale;
		newLpBitsInfo->bmiColors[i].rgbReserved = 0;
	}

	//����ͼ������
	BYTE* newLpBits = (BYTE*)&newLpBitsInfo->bmiColors[newLpBitsInfo->bmiHeader.biClrUsed];
	BYTE *pixel, *pPixelR, *pPixelG, *pPixelB, *newPixel, bv;
	int pixelR, pixelG, pixelB, avg;
	switch (lpBitsInfo->bmiHeader.biClrUsed) {
	case 0:
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
		break;
	// case 2:
	// 	for (i = 0; i < height; i++) {
	// 		for (j = 0; j < width; j++) {
	// 			bv = *(lpBits + lineBytes*(height - 1 - i) + j/8) & (1<<(7 - j%8));
	// 			pixelB = lpBitsInfo->bmiColors[bv].rgbBlue;
	// 			pixelG = lpBitsInfo->bmiColors[bv].rgbGreen;
	// 			pixelR = lpBitsInfo->bmiColors[bv].rgbRed;
	// 			avg = (pixelR + pixelG + pixelB)/3;

	// 			newPixel = lpBits + lineBytes*(height - 1 - i) + j/8;
	// 			if (0 == j%8) {
	// 				*newPixel = (avg<128 ? 0 : 1);
	// 				*newPixel = (*newPixel)<<7;
	// 			}
	// 			else
	// 				*newPixel += (avg<128 ? 0 : 1)<<(7 - j%8);
	// 			int kk = 0;
	// 		}
	// 	}
	// 	break;
	case 16:
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				bv = *(lpBits + lineBytes*(height - 1 - i) + j/2);
				if (0 == j%2)
					bv = bv>>4;
				else
					bv = bv&15;
				pixelB = lpBitsInfo->bmiColors[bv].rgbBlue;
				pixelG = lpBitsInfo->bmiColors[bv].rgbGreen;
				pixelR = lpBitsInfo->bmiColors[bv].rgbRed;
				avg = (pixelR + pixelG + pixelB)/3;

				newPixel = newLpBits + newLineBytes*(height - 1 - i) + j/2;
				if (0 == j%2) {
					*newPixel = avg%multiScale;
					*newPixel = (*newPixel)<<4;
				}
				else
					*newPixel += avg%multiScale;
			}
		}
		break;
	case 256:
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				pixel = lpBits + lineBytes*(height - 1 - i) + j;
				pixelB = lpBitsInfo->bmiColors[*pixel].rgbBlue;
				pixelG = lpBitsInfo->bmiColors[*pixel].rgbGreen;
				pixelR = lpBitsInfo->bmiColors[*pixel].rgbRed;
				avg = (pixelR + pixelG + pixelB)/3;

				newPixel = newLpBits + newLineBytes*(height - 1 - i) + j;
				*newPixel = avg;
			}	
		}
		break;
	default:
		break;
	}

	//�ͷž��ڴ棬����ָ��
	BITMAPINFO* temp = lpBitsInfo;
	lpBitsInfo = newLpBitsInfo;
	free(temp);
	
	//AfxMessageBox("pass");
	return true;
}

BOOL isGray() {
	int rHead, gHead, bHead, rMid, gMid, bMid, rEnd, gEnd, bEnd;
	BOOL boolHead, boolMid, boolEnd;

	switch(lpBitsInfo->bmiHeader.biBitCount) {
		case 8:
			rHead = lpBitsInfo->bmiColors[0].rgbRed;
			gHead = lpBitsInfo->bmiColors[0].rgbGreen;
			bHead = lpBitsInfo->bmiColors[0].rgbBlue;
			rMid = lpBitsInfo->bmiColors[128].rgbRed;
			gMid = lpBitsInfo->bmiColors[128].rgbGreen;
			bMid = lpBitsInfo->bmiColors[128].rgbBlue;
			rEnd = lpBitsInfo->bmiColors[255].rgbRed;
			gEnd = lpBitsInfo->bmiColors[255].rgbGreen;
			bEnd = lpBitsInfo->bmiColors[255].rgbBlue;

			boolHead = (rHead == gHead && gHead == bHead);
			boolMid = (rMid == gMid && gMid == bMid);
			boolEnd = (rEnd == gEnd && gEnd == bEnd);

			if (boolHead && boolMid && boolEnd)
				return TRUE;
			break;

		case 4:
			rHead = lpBitsInfo->bmiColors[0].rgbRed;
			gHead = lpBitsInfo->bmiColors[0].rgbGreen;
			bHead = lpBitsInfo->bmiColors[0].rgbBlue;
			rMid = lpBitsInfo->bmiColors[8].rgbRed;
			gMid = lpBitsInfo->bmiColors[8].rgbGreen;
			bMid = lpBitsInfo->bmiColors[8].rgbBlue;
			rEnd = lpBitsInfo->bmiColors[15].rgbRed;
			gEnd = lpBitsInfo->bmiColors[15].rgbGreen;
			bEnd = lpBitsInfo->bmiColors[15].rgbBlue;

			boolHead = (rHead == gHead && gHead == bHead);
			boolMid = (rMid == gMid && gMid == bMid);
			boolEnd = (rEnd == gEnd && gEnd == bEnd);

			if (boolHead && boolMid && boolEnd)
				return TRUE;
			break;
	}
	return FALSE;
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