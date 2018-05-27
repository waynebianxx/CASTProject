#include "stdafx.h"
#include "../include/CAST_SrcData.h"
#include <stdio.h>

CAST_IMG::CAST_IMG()
{
	m_pData = NULL;
	m_pImgData = NULL;
}


CAST_IMG::~CAST_IMG()
{
	if (m_pData != NULL)
		delete[]m_pData;
	if (!cimg.IsNull())
		cimg.Destroy();
}

void CAST_IMG::ReadFile(const char* pFileName, BYTE*& pData)
{
	//read file
	FILE* pF = nullptr;
	errno_t err;
	if ((err = fopen_s(&pF, pFileName, "r")) == NULL)
	{
		fseek(pF, 0L, SEEK_END);
		UINT32 fLen = ftell(pF);
		fseek(pF, 0L, SEEK_SET);
		pData = new BYTE[fLen];
		fread(pData, 1, fLen, pF);
		fclose(pF);
	}
	return;
}

void CAST_IMG::LoadFile(const char* pFileName)
{
	//read file
	FILE* pF = nullptr;
	errno_t err;
	if ((err = fopen_s(&pF, pFileName, "r")) == NULL)
	{
		fseek(pF, 0L, SEEK_END);
		UINT32 fLen = ftell(pF);
		fseek(pF, 0L, SEEK_SET);
		if (m_pData != NULL)
			delete[]m_pData;
		m_pData = new BYTE[fLen];
		fread(m_pData, 1, fLen, pF);
		fclose(pF);
		DataCfg();
	}
	else
		return;
}

void CAST_IMG::DataCfg()
{
	//copy head info and parse auxli data
	m_pImgData = (BYTE*)m_pData + 32;
	m_ImgW = 6192;
	m_ImgH = 1024;
	m_BPP = 2;//16bit
	m_LinePitch = m_ImgW*m_BPP;
}

int CAST_IMG::CreateCImg(int& CImgW, int& CImgH)
{
	if (!cimg.IsNull())
		cimg.Destroy();
	m_CImgW = CImgW;
	m_CImgH = CImgH;
	cimg.Create(m_CImgW, m_CImgH, 8);
	RGBQUAD* ColorTable;
	int MaxColors = 256;
	ColorTable = new RGBQUAD[MaxColors];
	cimg.GetColorTable(0, MaxColors, ColorTable);
	for (int i = 0; i != MaxColors; ++i)
	{
		ColorTable[i].rgbBlue = (BYTE)i;
		ColorTable[i].rgbGreen = (BYTE)i;
		ColorTable[i].rgbRed = (BYTE)i;
	}
	cimg.SetColorTable(0, MaxColors, ColorTable);
	delete[]ColorTable;
	return 1;
}

int CAST_IMG::CopyDataToCImg(void* pData, int& ImgW, int& ImgH, BIT_RANGE bitRange)
{
	if (cimg.IsNull())
		return 0;
	if ((ImgW != m_CImgW) || (ImgH != m_CImgH))
		CreateCImg(ImgW,ImgH);
	BYTE* pImg=NULL;
	//show reverse
//	BYTE *pImg = (BYTE *)cimg.GetBits();
// 	int step = cimg.GetPitch();
//  	if (step < 0)
//  	{
//  		pImg = pImg + step*(m_CImgH - 1);
//  		step = 0 - step;
//  	}
	UINT16* pSrc = (UINT16*)pData;
	int shiftBit = 8 - bitRange;
	UINT32 srcIdx = 0, dstIdx = 0;
	for (int i = 0; i != m_CImgH; ++i)
	{
		//maybe show reverse
// 		dstIdx = i*step;
// 		for (int j = 0; j != m_CImgW; ++j)
// 			*(pImg + dstIdx + j) = pSrc[srcIdx++] >> shiftBit;
		pImg = (BYTE*)cimg.GetPixelAddress(0, i);
		for (int j = 0; j != m_CImgW; ++j)
			pImg[j] = pSrc[srcIdx++] >> shiftBit;
	}
	return 1;
}