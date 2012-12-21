//-----------------------------------------------------
// Objective:   Assembly File Manager parses assembly files in a folder
//
// History:     2012/10/6 - B. Fung (Created)
// 
//-----------------------------------------------------

#pragma once

#include "CSParam.h"

class CCSDatabaseMgr;
class CCSTokenRefMgr;

class CCSOperandsMap : public CCSMapStringToInt
{
public:
    CCSOperandsMap() {};
    virtual ~CCSOperandsMap() {};
    int getOperandIdx(const CString& operand);
};

class CCSAssemblyFileMgr
{
public:
    CCSAssemblyFileMgr(CCSDatabaseMgr* pDBMgr, CCSTokenRefMgr* pTokenRefMgr);
    virtual ~CCSAssemblyFileMgr();
    
    inline CCSDatabaseMgr* getDBMgr() const { return m_pDBMgr; };
    inline CCSTokenRefMgr* getTokenRefMgr() const { return m_pTokenRefMgr; };

    inline CCSOperandsMap* getOpMems() { return &m_opMems; };
    inline CCSOperandsMap* getOpRegs() { return &m_opRegs; };
    inline CCSOperandsMap* getOpVals() { return &m_opVals; };

    // functions for manipulating reading assembly files
    bool openRawAssemblyFile(LPCTSTR assemblyFilePath);
    bool getRawAssemblyFileLineStr(CString& str);
    void closeRawAssemblyFile();

    bool parseFolder(LPCTSTR folderPath, const CCSParam& param, bool bConstructFeaturesOnly);
    bool createAssemblyFile(LPCTSTR content, CString& newAssemblyFilePath);
    bool constructBasicFeatures();
    bool addGlobalFeatureIfNew(LPCTSTR featureName);

    CStringArray m_globalFeatures;
    CCSIntArray m_medians;

private:    
    bool parseFunctions(CCSAssemblyFile* pAssemblyFile, const CCSParam& param);
    bool constructMnemonicFeatures();
    bool constructOpTypeFeatures();
    bool constructMnemonicOpType0Features();
    bool constructOpType0Type1Features();
    bool addGlobalFeature(LPCTSTR featureName);

    Int64u m_nTotalFiles;
    Int64u m_nTotalFunctions;
    Int64u m_nTotalRegions;

    CCSOperandsMap m_opMems;        // map string to index
    CCSOperandsMap m_opRegs;        // map string to index, e.g, [eax,0][edx,1]
    CCSOperandsMap m_opVals;        // map string to index

    CStdioFile* m_pRawAssemblyFile;     // raw assembly file. Only one raw file can be opened at a time.

    CCSDatabaseMgr* m_pDBMgr;
    CCSTokenRefMgr* m_pTokenRefMgr;
};


