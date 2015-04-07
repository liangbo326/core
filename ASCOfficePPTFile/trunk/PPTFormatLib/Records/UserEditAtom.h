#pragma once
#include "../Reader/Records.h"

class CRecordUserEditAtom : public CUnknownRecord
{
public:
	DWORD m_nLastSlideIdRef;

	USHORT m_nVersion;			// must be 0x0000
	BYTE m_nMinorVersion;		// must be 0x00
	BYTE m_nMajorVersion;		// must be 0x03

	DWORD m_nOffsetLastEdit;    // offset to prev UserEditAtom (0 - if no)

	DWORD m_nOffsetPersistDirectory;	// offset to PersistDirectoryAtom in PPTDocStream (for this user)

	DWORD m_nOffsetDocPersistIdRef;		// offset to PersistObjectDirectory in DocContainer must be 0x00000001

	DWORD m_nPersistIdSeed;				// for next

	USHORT m_nLastView;

public:
	
	CRecordUserEditAtom()
	{
	}

	~CRecordUserEditAtom()
	{
	}

	virtual void ReadFromStream(SRecordHeader & oHeader, POLE::Stream* pStream)
	{
		m_oHeader = oHeader;
		
		m_nLastSlideIdRef = StreamUtils::ReadDWORD(pStream);

		m_nVersion = StreamUtils::ReadWORD(pStream);
		m_nMinorVersion = StreamUtils::ReadBYTE(pStream);
		m_nMajorVersion = StreamUtils::ReadBYTE(pStream);

		m_nOffsetLastEdit = StreamUtils::ReadDWORD(pStream);
		m_nOffsetPersistDirectory = StreamUtils::ReadDWORD(pStream);
		m_nOffsetDocPersistIdRef = StreamUtils::ReadDWORD(pStream);

		m_nPersistIdSeed = StreamUtils::ReadDWORD(pStream);
		m_nLastView = StreamUtils::ReadWORD(pStream);

		StreamUtils::StreamSkip(m_oHeader.RecLen - 22, pStream);
	}
	virtual CString ToString()
	{
		XmlUtils::CXmlWriter oWriter;
		CString strName = GetRecordName((DWORD)m_oHeader.RecType);
		
		oWriter.WriteNodeBegin(strName, TRUE);
		oWriter.WriteAttribute(_T("length"), CDirectory::ToString(m_oHeader.RecLen));
		oWriter.WriteAttribute(_T("type"), CDirectory::ToString(m_oHeader.RecType));
		oWriter.WriteAttribute(_T("instance"), CDirectory::ToString(m_oHeader.RecInstance));

		oWriter.WriteNodeEnd(strName, TRUE, FALSE);
		
		CDirectory::WriteValueToNode(_T("LastSlideIdRef"), m_nLastSlideIdRef, &oWriter);
		CDirectory::WriteValueToNode(_T("OffsetLastEdit"), m_nOffsetLastEdit, &oWriter);
		CDirectory::WriteValueToNode(_T("OffsetPersistDirectory"), m_nOffsetPersistDirectory, &oWriter);
		CDirectory::WriteValueToNode(_T("OffsetDocPersistIdRef"), m_nOffsetDocPersistIdRef, &oWriter);

		oWriter.WriteNodeEnd(strName);

		return oWriter.GetXmlString();
	}

	CRecordUserEditAtom& operator =(const CRecordUserEditAtom& oSrc)
	{
		m_nLastSlideIdRef = oSrc.m_nLastSlideIdRef;

		m_nVersion = oSrc.m_nVersion;
		m_nMinorVersion = oSrc.m_nMinorVersion;
		m_nMajorVersion = oSrc.m_nMajorVersion;

		m_nOffsetLastEdit = oSrc.m_nOffsetLastEdit;

		m_nOffsetPersistDirectory = oSrc.m_nOffsetPersistDirectory;

		m_nOffsetDocPersistIdRef = oSrc.m_nOffsetDocPersistIdRef;
		m_nPersistIdSeed = oSrc.m_nPersistIdSeed;

		m_nLastView = oSrc.m_nLastView;
		return (*this);
	}
};