/*
  ==============================================================================

    CompressorSubmodules.cpp
    Created: 21 Jun 2017 4:22:41pm
    Author:  Davis

    Eichas & Zölzer paper used for LDR reference:
    Modeling of an Optocoupler-Based Audio Dynamic Range Control Circuit
    http://proceedings.spiedigitallibrary.org/proceeding.aspx?articleid=2565611
  ==============================================================================
*/

#include "CompressorSubmodules.h"

using namespace wdfSubmodule;

//-----------------------------------------------------------------------------------
//---------------------------- Helper Virtual Class ---------------------------------
//-----------------------------------------------------------------------------------
int wdfSubmoduleBase::setRootMatrData(matData* rootMats, double* Rp)
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

void wdfSubmoduleBase::setInputValue(double signalIn) {}

double wdfSubmoduleBase::getOutputValue() {return 0;}

void wdfSubmoduleBase::setParam(size_t paramID, double paramValue) {}

const char* wdfSubmoduleBase::getTreeIdentifier()
{
    return m_sTreeName.c_str();
}

//-----------------------------------------------------------------------------------
//------------------------- One Pole High Pass Filter -------------------------------
//-----------------------------------------------------------------------------------
//
// WDF TREE:
// [] = component
// () = adapter
//
//          [ideal voltage source (input)]
//                       |
//                    (series)
//                    |      |
//             [resistor]   [cap]
//
wdfOnePoleHighPass::wdfOnePoleHighPass()
{
    m_pInputSource.reset(new wdfIdealVSource(1.));
    m_pCap.reset(new wdfTerminatedCap(1.,1.));
    m_pRes.reset(new wdfTerminatedRes(1e3));
    m_pSeriesAdapter.reset(new wdfTerminatedSeries(m_pRes.get(),m_pCap.get()));
    
    m_pCap.get()->prevA = 0.0000;
    
    subtreeCount = 1;
    subtreeEntryNodes = new wdfTreeNode*[subtreeCount];
    subtreeEntryNodes[0] = m_pSeriesAdapter.get();
    
    root.reset( new wdfRootSimple(m_pInputSource.get()) );
    Rp = new double[subtreeCount] ();
    
    m_sTreeName = "High Pass";
}

wdfOnePoleHighPass::~wdfOnePoleHighPass()
{}

void wdfOnePoleHighPass::processSample(float sampleIn, float & sampleOut)
{
    m_pInputSource->Vs = sampleIn;
    cycleWave();
    sampleOut = (float)m_pRes->upPort->getPortVoltage();
}

void wdfOnePoleHighPass::reset()
{
    m_pCap.get()->prevA = 0;
    initTree();
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
        m_pRes->R = resVal;
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
        m_pCap->C = capVal;
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

//-----------------------------------------------------------------------------------
//------------------------------- GAIN PROCESSOR ------------------------------------
//-----------------------------------------------------------------------------------
//
// WDF TREE:
// [] = component
// () = adapter
//
//                            [LDR]
//                              |
//                          (parallel)
//                          |       |
//                      (parallel) [cap]
//                      |       |
//[resistive source (input)]   [resistor]
//
wdfGainProcessor::wdfGainProcessor()
{
    m_pInputSource.reset(new wdfTerminatedResVSource(0.,1.));
    m_pCap.reset(new wdfTerminatedCap(1.,1.));
    m_pRes.reset(new wdfTerminatedRes(1e3));
    m_pLdr.reset(new wdfUnterminatedRes(1e3));
    
    // initialize adapter moving from bottom (widest part) of tree to top (narrowest part)
    m_pParallelAdapters[kParallelAdapterTreeLevel2].reset(new wdfTerminatedParallel(m_pInputSource.get(), m_pRes.get()));
    m_pParallelAdapters[kParallelAdapterTreeLevel1].reset(new wdfTerminatedParallel(m_pParallelAdapters[kParallelAdapterTreeLevel2].get(),
                                                                                    m_pCap.get()));
    
    m_pCap.get()->prevA = 0.0000;
    
    subtreeCount = 2;
    subtreeEntryNodes = new wdfTreeNode*[subtreeCount];
    subtreeEntryNodes[0] = m_pParallelAdapters[kParallelAdapterTreeLevel1].get();
    subtreeEntryNodes[1] = m_pParallelAdapters[kParallelAdapterTreeLevel2].get();
    
    root.reset(new wdfRootSimple(m_pLdr.get()));
    Rp = new double[subtreeCount] ();
    
    m_sTreeName = "Gain Processor";
}

wdfGainProcessor::~wdfGainProcessor() {}

void wdfGainProcessor::processSample(float sampleIn, float & sampleOut)
{
    m_pInputSource->Vs = sampleIn;
    cycleWave();
    sampleOut = (float)m_pRes->upPort->getPortVoltage();
}

void wdfGainProcessor::reset()
{
    m_pCap.get()->prevA = 0;
    initTree();
}

// Setters and Getters
void wdfGainProcessor::setResComponentVal(float resVal, bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        m_fResComponentVal = resVal;
        m_pRes->R = resVal;
    }
}

void wdfGainProcessor::setCapComponentVal(float capVal, bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        m_fCapComponentVal = capVal;
        m_pCap->C = capVal;
    }
}

float wdfGainProcessor::getResComponentVal(bool isNormalized)
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

float wdfGainProcessor::getCapComponentVal(bool isNormalized)
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

void wdfGainProcessor::setLdrComponentVal(float ldrVal)
{
    // input is current off of diode from envelope follower, LDR curve is roughly logarithmic, so:
    // normalize --> take log --> multiply against resistor range
    
    // assume max current is about 50mA (datasheet gives 40 as upper range, empirical test gives 50 as an approximate value
    const float maxCurrent = 50e-3;
    
    // resistance values come from datasheet and Eichas & Zölzer paper
    const float maxResistance = 1e6;
    const float minResistance = 100;
    
    if(ldrVal < 0) ldrVal *= -1;
    const float normalizedCurrent = ldrVal / maxCurrent;
    
    // LDR curve looks roughly logarithmic. For easy of use, log function shifted to intercept (0,1) and (1,0)
    const float logVal = log(normalizedCurrent);
    
    m_fLdrComponentVal = logVal * (maxResistance - minResistance) + minResistance;
}

float wdfGainProcessor::getLdrComponentVal()
{
    return m_fLdrComponentVal;
}
//-----------------------------------------------------------------------------------
//----------------------------- ENVELOPE FOLLOWER -----------------------------------
//-----------------------------------------------------------------------------------
//
// WDF TREE:
// [] = component
// () = adapter
//
//                                               [LED]
//                                                 |
//                                             (series)
//                                             |      |
//                                      (series)     [resistor 2]
//                                      |      |
//                              (parallel)    [cap]
//                              |        |
// [Resistive voltage source (input)]   [resistor 1]
//
wdfEnvelopeFollower::wdfEnvelopeFollower()
{
    m_pInputSource.reset(new wdfTerminatedResVSource(0.,1.));
    m_pCap.reset(new wdfTerminatedCap(1.,1.));
    m_pR1.reset(new wdfTerminatedRes(1e3));
    m_pR2.reset(new wdfTerminatedRes(1e3));
    
    // initialize adapter moving from bottom (widest part) of tree to top (narrowest part)
    m_pParallelAdapter.reset(new wdfTerminatedParallel(m_pInputSource.get(), m_pR1.get()));
    m_pSeriesAdapters[kSeriesAdapterTreeLevel2].reset(new wdfTerminatedSeries(m_pParallelAdapter.get(), m_pCap.get()));
    m_pSeriesAdapters[kSeriesAdapterTreeLevel1].reset(new wdfTerminatedSeries(m_pSeriesAdapters[kSeriesAdapterTreeLevel2].get(),
                                                                              m_pR2.get()));
    
    m_pCap.get()->prevA = 0.0000;
    
    subtreeCount = 3;
    subtreeEntryNodes = new wdfTreeNode*[subtreeCount];
    subtreeEntryNodes[0] = m_pSeriesAdapters[kSeriesAdapterTreeLevel1].get();
    subtreeEntryNodes[1] = m_pSeriesAdapters[kSeriesAdapterTreeLevel2].get();
    subtreeEntryNodes[2] = m_pParallelAdapter.get();
    
    root.reset(new wdfRootNL(subtreeCount, {DIODE}, 1));
    Rp = new double[subtreeCount] ();
    m_sTreeName = "Gain Processor";
}

wdfEnvelopeFollower::~wdfEnvelopeFollower(){}

// RETURNS A CONTROL VOLTAGE, NOT AUDIO 
void wdfEnvelopeFollower::processSample(float sampleIn, float &sampleOut)
{
    m_pInputSource->Vs = sampleIn;
    cycleWave();
    sampleOut = (float)m_pSeriesAdapters[kSeriesAdapterTreeLevel1]->upPort->getPortCurrent();
}

void wdfEnvelopeFollower::reset()
{
    m_pCap.get()->prevA = 0;
    initTree();
}

// Setters and Getters
void wdfEnvelopeFollower::setR1ComponentVal(float r1Val, bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        m_fR1ComponentVal = r1Val;
        m_pR1->R = r1Val;
    }
}

void wdfEnvelopeFollower::setR2ComponentVal(float r2Val, bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        m_fR2ComponentVal = r2Val;
        m_pR2->R = r2Val;
    }
}

void wdfEnvelopeFollower::setCapComponentVal(float capVal, bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        m_fCapComponentVal = capVal;
        m_pCap->C = capVal;
    }
}

float wdfEnvelopeFollower::getR1ComponentVal(bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        return m_fR1ComponentVal;
    }
    return 0;
}

float wdfEnvelopeFollower::getR2ComponentVal(bool isNormalized)
{
    if(isNormalized)
    {
        
    }
    else
    {
        return m_fR2ComponentVal;
    }
    return 0;
}

float wdfEnvelopeFollower::getCapComponentVal(bool isNormalized)
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
