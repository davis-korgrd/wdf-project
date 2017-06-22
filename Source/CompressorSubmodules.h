/*
  ==============================================================================

    CompressorSubmodules.h
    Created: 21 Jun 2017 4:22:41pm
    Author:  Davis

  ==============================================================================
*/

#pragma once

#include "rt-wdf.h"

using namespace arma;

namespace wdfSubmodule
{
    class wdfSubmoduleBase : public wdfTree
    {
    public:
        virtual int         setRootMatrData(matData* rootMats, double* Rp);
        virtual void        setInputValue(double signalIn);
        virtual double      getOutputValue();
        virtual const char* getTreeIdentifier();
        virtual void        setParam(size_t paramID, double paramValue);
        
    protected:
        std::string m_sTreeName = "";
    };
    
    class wdfOnePoleHighPass : public wdfSubmoduleBase
    {
    public:
        wdfOnePoleHighPass();
        ~wdfOnePoleHighPass();
        
        void        processSample(float sampleIn, float & sampleOut);
        void        reset();
        
        void        setResComponentVal(float resVal, bool isNormalized = 0);
        void        setCapComponentVal(float capVal, bool isNormalized = 0);
        float       getResComponentVal(bool isNormalized = 0);
        float       getCapComponentVal(bool isNormalized = 0);


        enum
        {
            kIndexResistor,
            kIndexCapacitor,
            kIndexNumParams
        };
        
    private:
        //-----------------------------------------------------------------------------------
        //------------------------------------ POD ------------------------------------------
        //-----------------------------------------------------------------------------------
        
        // Parameter values for resistor and capacitor. These are intended as actual component values,
        // not values normalized to 0 - 1.
        float m_fResComponentVal;
        float m_fCapComponentVal;
        
        //-----------------------------------------------------------------------------------
        //---------------------------------- CLASSES ----------------------------------------
        //-----------------------------------------------------------------------------------
        
        // Model filter input as an ideal voltage source (as such, it must be the root of the tree)
        std::unique_ptr<wdfIdealVSource> m_pInputSource;
        
        // WDF model of a capacitor
        std::unique_ptr<wdfTerminatedCap> m_pCap;
        
        // WDF model of a resistor
        std::unique_ptr<wdfTerminatedRes> m_pRes;
        
        // WDF series adapter. Necessary for connecting the resistive source to the capacitor
        std::unique_ptr<wdfTerminatedSeries> m_pSeriesAdapter;
    };
    
    class wdfGainProcessor : public wdfSubmoduleBase
    {
    public:
        wdfGainProcessor();
        ~wdfGainProcessor();
        
        void        processSample(float sampleIn, float & sampleOut);
        void        reset();
        
    private:
        //-----------------------------------------------------------------------------------
        //------------------------------------ POD ------------------------------------------
        //-----------------------------------------------------------------------------------
        
        // Parameter values for resistor and capacitor. These are intended as actual component values,
        // not values normalized to 0 - 1.
        float m_fResComponentVal;
        float m_fCapComponentVal;
        enum
        {
            kParallelAdapterTreeLevel1,
            kParallelAdapterTreeLevel2,
            kParallelAdapterNumAdapters
        };
        
        //-----------------------------------------------------------------------------------
        //---------------------------------- CLASSES ----------------------------------------
        //-----------------------------------------------------------------------------------
        
        // Model filter input as an ideal voltage source (as such, it must be the root of the tree)
        std::unique_ptr<wdfTerminatedResVSource> m_pInputSource;
        
        // WDF model of a capacitor
        std::unique_ptr<wdfTerminatedCap> m_pCap;
        
        // WDF model of a resistor
        std::unique_ptr<wdfTerminatedRes> m_pRes;
        
        // Light-sensitive resistor
        std::unique_ptr<wdfUnterminatedRes> m_pLdr;
        
        // WDF series adapter. Necessary for connecting the resistive source to the capacitor
        std::unique_ptr<wdfTerminatedParallel> m_pParallelAdapters[kParallelAdapterNumAdapters];
    };
    
    class wdfEnvelopeFollower : public wdfSubmoduleBase
    {
    public:
        wdfEnvelopeFollower();
        ~wdfEnvelopeFollower();

    private:
        //-----------------------------------------------------------------------------------
        //---------------------------------- CLASSES ----------------------------------------
        //-----------------------------------------------------------------------------------
        
        // Model filter input as an ideal voltage source (as such, it must be the root of the tree)
        std::unique_ptr<wdfTerminatedResVSource> m_pInputSource;
        
        // WDF model of a capacitor
        std::unique_ptr<wdfTerminatedCap> m_pCap;
        
        // WDF model of a resistor
        std::unique_ptr<wdfTerminatedRes> m_pRes;
        
        // WDF series adapter. Necessary for connecting the resistive source to the capacitor
        std::unique_ptr<wdfTerminatedSeries> m_SeriesAdapter;
//        std::string m_sTreeName = "Envelope Follower";
    };
}
