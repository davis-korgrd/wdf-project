/*
  ==============================================================================

    CompressorSubmodules.cpp
    Created: 21 Jun 2017 4:22:41pm
    Author:  Davis

  ==============================================================================
*/

#include "CompressorSubmodules.h"

using namespace wdfOnePoleHPF;

//-----------------------------------------------------------------------------------
//---------------------------- Helper Virtual Class ---------------------------------
//-----------------------------------------------------------------------------------
int wdfSubmodule::setRootMatrData(matData* rootMats, double* Rp)
{
    if (rootMats->Emat.is_empty())
    {
        return -1;
    }
    if (rootMats->Emat.n_cols != 1)
    {
        return -1;
    }
    if (rootMats->Emat.n_rows != 1)
    {
        return -1;
    }
    
    rootMats->Emat.at(0,0) = 1;
    
    
    //------------------------- F matrix -------------------------
    if (rootMats->Fmat.is_empty())
    {
        return -1;
    }
    if (rootMats->Fmat.n_cols != 1)
    {
        return -1;
    }
    if (rootMats->Fmat.n_rows != 1)
    {
        return -1;
    }
    
    rootMats->Fmat.at(0,0) = -Rp[0];
    
    
    //------------------------- M matrix -------------------------
    if (rootMats->Mmat.is_empty())
    {
        return -1;
    }
    if (rootMats->Mmat.n_cols != 1)
    {
        return -1;
    }
    if (rootMats->Mmat.n_rows != 1)
    {
        return -1;
    }
    
    rootMats->Mmat.at(0,0) = 1;
    
    //------------------------- N matrix -------------------------
    if (rootMats->Nmat.is_empty())
    {
        return -1;
    }
    if (rootMats->Nmat.n_cols != 1)
    {
        return -1;
    }
    if (rootMats->Nmat.n_rows != 1)
    {
        return -1;
    }
    
    rootMats->Nmat.at(0,0) = -2*Rp[0];
    
    //nowTime = String::formatted(("%012.9f"), (float)(Time::getMillisecondCounterHiRes() - startupTime));
    //myLogger->writeToLog("\n->"+nowTime+" ms: End setRootMatrixData. Duration: "+String(nowTime)+" ms");
    
    return 0;
}

void wdfSubmodule::setInputValue(double signalIn) {}

double wdfSubmodule::getOutputValue() {return 0;}

void wdfSubmodule::setParam(size_t paramID, double paramValue) {}

//-----------------------------------------------------------------------------------
//------------------------- One Pole High Pass Filter -------------------------------
//-----------------------------------------------------------------------------------
wdfOnePoleHighPass::wdfOnePoleHighPass()
{
    m_InputSource.reset(new wdfIdealVSource(1.));
    m_Cap.reset(new wdfTerminatedCap(1.,1.));
    m_Res.reset(new wdfTerminatedRes(2e3));
    m_SeriesAdapter.reset(new wdfTerminatedSeries(m_Res.get(),m_Cap.get()));
    
    m_Cap.get()->prevA = 0.0000;
    
    subtreeCount = 1;
    subtreeEntryNodes = new wdfTreeNode*[subtreeCount];
    subtreeEntryNodes[0] = m_SeriesAdapter.get();
    
    root.reset( new wdfRootSimple(m_InputSource.get()) );
    Rp = new double[subtreeCount] ();
}

wdfOnePoleHighPass::~wdfOnePoleHighPass()
{}

void wdfOnePoleHighPass::processSample(float sampleIn, float & sampleOut)
{
    m_InputSource->Vs = sampleIn;
    cycleWave();
    sampleOut = (float)m_Res->upPort->getPortVoltage();
}

void wdfOnePoleHighPass::reset()
{
    m_Cap.get()->prevA = 0;
    initTree();
}

const char* wdfOnePoleHighPass::getTreeIdentifier()
{
    return m_sTreeName.c_str();
}

// Setters and Getters
void wdfOnePoleHighPass::setResComponentVal(float resVal, bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        m_fResComponentVal = resVal;
        m_Res->R = resVal;
    }
}

void wdfOnePoleHighPass::setCapComponentVal(float capVal, bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        m_fCapComponentVal = capVal;
        m_Cap->C = capVal;
    }
}

float wdfOnePoleHighPass::getResComponentVal(bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        return m_fResComponentVal;
    }
    return 0;
}

float wdfOnePoleHighPass::getCapComponentVal(bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        return m_fCapComponentVal;
    }
    return 0;
}
