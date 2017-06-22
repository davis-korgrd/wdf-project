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

namespace wdfOnePoleHPF
{
    class wdfSubmodule : public wdfTree
    {
    public:
        virtual int         setRootMatrData(matData* rootMats, double* Rp);
        virtual void        setInputValue(double signalIn);
        virtual double      getOutputValue();
        virtual const char* getTreeIdentifier() = 0;
        virtual void        setParam(size_t paramID, double paramValue);
    };
    
    class wdfOnePoleHighPass : public wdfSubmodule
    {
    public:
        wdfOnePoleHighPass();
        ~wdfOnePoleHighPass();
        
        void        processSample(float input, float & output);
        void        reset();
        
        void        setResComponentVal(float resVal, bool isNormalized = 0);
        void        setCapComponentVal(float capVal, bool isNormalized = 0);
        float       getResComponentVal(bool isNormalized = 0);
        float       getCapComponentVal(bool isNormalized = 0);
        
        // Inherited methods
        const char* getTreeIdentifier();

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
        std::unique_ptr<wdfIdealVSource> m_InputSource;
        
        // WDF model of a capacitor
        std::unique_ptr<wdfTerminatedCap> m_Cap;
        
        // WDF model of a resistor
        std::unique_ptr<wdfTerminatedRes> m_Res;
        
        // WDF series adapter. Necessary for connecting the resistive source to the capacitor
        std::unique_ptr<wdfTerminatedSeries> m_SeriesAdapter;
        std::string m_sTreeName = "High Pass";
    };
    
    class wdfEnvelopeFollower
    {
        
    };
    
    class wdfGainProcessor
    {
        
    };
}
