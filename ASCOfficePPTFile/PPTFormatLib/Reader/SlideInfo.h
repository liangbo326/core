#pragma once
#include "../../../ASCOfficePPTXFile/Editor/Drawing/Document.h"

class CElementInfo
{
public:
	int		m_lOffsetTextStyle;
	int		m_lOffsetTextProp;
	POLE::Stream*	m_pStream;

	int		m_lPersistIndex;

	int		m_lMasterTextType;
	int		m_lMasterPlaceholderType;

public:
	CElementInfo()
	{
		m_lOffsetTextStyle	= -1;
		m_lOffsetTextProp	= -1;
		m_lPersistIndex		= -1;
		m_pStream			= NULL;

		m_lMasterTextType			= -1;
		m_lMasterPlaceholderType	= -1;
	}
	CElementInfo(const CElementInfo& oSrc)
	{
		*this = oSrc;
	}
	CElementInfo& operator=(const CElementInfo& oSrc)
	{
		m_lOffsetTextStyle	= oSrc.m_lOffsetTextStyle;
		m_lOffsetTextProp	= oSrc.m_lOffsetTextProp;
		m_lPersistIndex		= oSrc.m_lPersistIndex;
		m_pStream			= oSrc.m_pStream;

		m_lMasterTextType			= oSrc.m_lMasterTextType;
		m_lMasterPlaceholderType	= oSrc.m_lMasterPlaceholderType;

		return *this;
	}
	~CElementInfo()
	{
	}
};

class CSlideInfo
{
public:
	std::vector<CTextFullSettings>						m_arTextPlaceHolders;
	std::map<LONG, CElementInfo>						m_mapElements;
    std::vector<int>*									m_parEmptyPictures;
	std::map<int, std::wstring>*						m_mapFilePictures;
	nullable_base<NSPresentationEditor::CTextStyles>	m_pStyles[9];

public:
	CSlideInfo()
	{
	}
	~CSlideInfo()
	{
	}

	CSlideInfo(const CSlideInfo& oSrc)
	{
		*this = oSrc;
	}
	CSlideInfo& operator=(const CSlideInfo& oSrc)
	{
		m_arTextPlaceHolders = oSrc.m_arTextPlaceHolders;

		m_parEmptyPictures	= oSrc.m_parEmptyPictures;
		m_mapFilePictures	= oSrc.m_mapFilePictures;
	
		for (int i = 0; i < 9; ++i)
		{
			m_pStyles[i] = oSrc.m_pStyles[i];
		}

		m_mapElements = oSrc.m_mapElements;

		return *this;
	}

	std::wstring GetFileNamePicture(DWORD lIndex)
	{
		std::map<int, std::wstring>::iterator pic = m_mapFilePictures->find(lIndex);

		if (pic != m_mapFilePictures->end())
		{
			return pic->second;
		}
		return _T("");
	}

	int GetIndexPicture(int lIndex)
	{
		if (NULL == m_parEmptyPictures)
			return -1;
		if ( m_parEmptyPictures->size() < 1 )
			return -1;

		lIndex -= 1;

		if (lIndex < 0) lIndex = 0;
		
		if(lIndex >= 0 && lIndex < m_parEmptyPictures->size())
		{
			return m_parEmptyPictures->at(lIndex);
		}
		else
		{
			return m_parEmptyPictures->at(0);//???
		}
	}
};
