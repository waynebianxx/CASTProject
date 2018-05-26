#pragma once

#include <atlimage.h>

typedef union
{
	UINT8 m_AllData[19];
	struct
	{
		UINT8 m_HeadIdent[3];//文件头标识,3Byte
		UINT8 m_HeadLen[2];//文件头长度,2Byte
		UINT8 m_FileFmt[3];//文件格式,3Byte
		UINT8 m_DataBitWidth[2];//数据位宽,2Byte
		UINT8 m_HeadReserv[3];//文件头预留,3Byte
		UINT8 m_ImgWidth[3];//图像宽度,3Byte
		UINT8 m_ImgHeight[3];//图像高度,3Byte
	}HEAD_INFO;
}HEAD_INFO;

typedef union
{
	UINT8 m_AllData[158];
	struct
	{
		UINT8 m_PackHeadPos[2];//辅助数据包头位置，2bytes
		UINT8 m_DataWidth[2];//辅助数据宽度，2bytes
		UINT8 m_DataLength[2];//辅助数据长度，2bytes
		UINT8 m_ProjIdent[8];//项目标识，8bytes
		UINT8 m_FrameCnt[8];//帧计数，8bytes
		UINT8 m_LineCnt[8];//行技术，8bytes
		UINT8 m_BroadTime[8];//广播时间，8bytes
		UINT8 m_PixStPos[2];//有效像元起始位置，2bytes
		UINT8 m_PixEdPos[2];//有效像元终止位置，2bytes
		UINT8 m_ProjName[8];//项目名称，8bytes
		UINT8 m_SaveTime[6];//存图时间，6bytes
		UINT8 m_DevModel[8];//器件型号，8bytes
		UINT8 m_DevQuant;//器件数量，1byte
		UINT8 m_DevNum;//器件编号，1byte
		UINT8 m_SpecsecNum;//谱段编号，1byte
		UINT8 m_DataOrder[4];//数据顺序，4bytes
		UINT8 m_SplicPixQuant[2];//拼接区像元数，2bytes
		UINT8 m_LightRadLevel;//光源辐亮度等级，1byte
		UINT8 m_DevLevel[11];//器件级数，11bytes
		UINT8 m_IntgTime[5];//积分时间，5bytes
		UINT8 m_Gain[11];//增益，11bytes
		UINT8 m_Alg1Switch[4];//Algorithm1 Switch，4bytes
		UINT8 m_Alg2Switch[4];//Algorithm2 Switch，4bytes
		UINT8 m_Alg3Switch[4];//Algorithm3 Switch，4bytes
		UINT8 m_Alg4Switch[4];//Algorithm4 Switch，4bytes
		UINT8 m_Alg5Switch[4];//Algorithm5 Switch，4bytes
		UINT8 m_Alg6Switch[4];//Algorithm6 Switch，4bytes
		UINT8 m_Alg7Switch[4];//Algorithm7 Switch，4bytes
		UINT8 m_Alg8Switch[4];//Algorithm8 Switch，4bytes
		UINT8 m_Sp1SgTapPQ;//Spectrum 1 Single Tap Pixel Quantity，
		UINT8 m_Sp1Tap1PPos[2];//Spectrum 1 Tap1 Dark Pixel Start Position，
		UINT8 m_Sp1Tap2PPos[2];//Spectrum 1 Tap2 Dark Pixel Start Position，
		UINT8 m_Sp2SgTapPQ;//Spectrum 2 Single Tap Pixel Quantity，
		UINT8 m_Sp2Tap1PPos[2];//Spectrum 2 Tap1 Dark Pixel Start Position，
		UINT8 m_Sp2Tap2PPos[2];//Spectrum 2 Tap2 Dark Pixel Start Position，
		UINT8 m_Sp3SgTapPQ;//Spectrum 3 Single Tap Pixel Quantity，
		UINT8 m_Sp3Tap1PPos[2];//Spectrum 3 Tap1 Dark Pixel Start Position，
		UINT8 m_Sp3Tap2PPos[2];//Spectrum 3 Tap2 Dark Pixel Start Position
		UINT8 m_Sp4SgTapPQ;//Spectrum 4 Single Tap Pixel Quantity
		UINT8 m_Sp4Tap1PPos[2];//Spectrum 4 Tap1 Dark Pixel Start Position
		UINT8 m_Sp4Tap2PPos[2];//Spectrum 4 Tap2 Dark Pixel Start Position
		UINT8 m_Sp5SgTapPQ;//Spectrum 5 Single Tap Pixel Quantity
		UINT8 m_Sp5Tap1PPos[2];//Spectrum 5 Tap1 Dark Pixel Start Position
		UINT8 m_Sp5Tap2PPos[2];//Spectrum 5 Tap2 Dark Pixel Start Position
	}SubData;
}AUXIL_DATA;

typedef union
{
	UINT32 m_PixV;
	struct
	{
		UINT32 m_R : 8;
		UINT32 m_G : 8;
		UINT32 m_B : 8;
		UINT32 m_A : 8;
	}RGBA;
}PIXEL_PACK;

typedef enum
{
	from15to8,
	from14to7,
	from13to6,
	from12to5,
	from11to4,
	from10to3,
	from9to2,
	from8to1,
	from7to0
}BIT_RANGE;

class CAST_IMG
{
public:
	CAST_IMG();
	~CAST_IMG();
public:
	void* m_pData;//whole file data
	void* m_pImgData;//real image data
	int m_ImgW;
	int m_ImgH;
	int m_BPP;//Byte Per Pixel
	int m_LinePitch;//line pitch
	AUXIL_DATA m_AuxData;
	HEAD_INFO m_HeadData;
	CImage cimg;
	void LoadFile(const char* pFileName);
	void DataCfg();
	inline BYTE GetPixValue(int x, int y) const {
		return *((BYTE*)m_pImgData + y*m_LinePitch + x);
	};
	int CreateCImg();
	int CopyDataToCImg(BIT_RANGE bitRange);
};