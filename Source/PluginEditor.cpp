/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
JuceTemplateAudioProcessorEditor::JuceTemplateAudioProcessorEditor (JuceTemplateAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (sliderFc = new Slider ("Fc"));
    sliderFc->setRange (50, 5000, 0);
    sliderFc->setSliderStyle (Slider::LinearHorizontal);
    sliderFc->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderFc->addListener (this);

    addAndMakeVisible (sliderRC = new Slider ("Distortion"));
    sliderRC->setRange (0, 6, 0);
    sliderRC->setSliderStyle (Slider::LinearHorizontal);
    sliderRC->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderRC->addListener (this);

    addAndMakeVisible (lblR = new Label ("R",
                                         TRANS("R")));
    lblR->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblR->setJustificationType (Justification::centredLeft);
    lblR->setEditable (false, false, false);
    lblR->setColour (TextEditor::textColourId, Colours::black);
    lblR->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblC = new Label ("C",
                                         TRANS("C")));
    lblC->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblC->setJustificationType (Justification::centredLeft);
    lblC->setEditable (false, false, false);
    lblC->setColour (TextEditor::textColourId, Colours::black);
    lblC->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtR = new TextEditor ("R"));
    txtR->setMultiLine (false);
    txtR->setReturnKeyStartsNewLine (false);
    txtR->setReadOnly (true);
    txtR->setScrollbarsShown (false);
    txtR->setCaretVisible (false);
    txtR->setPopupMenuEnabled (false);
    txtR->setText (String());

    addAndMakeVisible (txtC = new TextEditor ("C"));
    txtC->setMultiLine (false);
    txtC->setReturnKeyStartsNewLine (false);
    txtC->setReadOnly (true);
    txtC->setScrollbarsShown (false);
    txtC->setCaretVisible (false);
    txtC->setPopupMenuEnabled (false);
    txtC->setText (String());


    //[UserPreSize]
    sliderFc->setSkewFactorFromMidPoint(500.);
    sliderRC->setSkewFactorFromMidPoint(3.);
    //[/UserPreSize]

    setSize (250, 140);


    //[Constructor] You can add your own custom stuff here..
    sliderFc->setValue(500.);
    sliderRC->setValue(3.);
    //[/Constructor]
}

JuceTemplateAudioProcessorEditor::~JuceTemplateAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sliderFc = nullptr;
    sliderRC = nullptr;
    lblR = nullptr;
    lblC = nullptr;
    txtR = nullptr;
    txtC = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void JuceTemplateAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JuceTemplateAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    sliderFc->setBounds (8, 8, 240, 24);
    sliderRC->setBounds (8, 40, 240, 24);
    lblR->setBounds (8, 72, 24, 24);
    lblC->setBounds (8, 104, 24, 24);
    txtR->setBounds (32, 72, 150, 24);
    txtC->setBounds (32, 104, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JuceTemplateAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    char str[50];
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderFc)
    {
        //[UserSliderCode_sliderFc] -- add your slider handling code here..
        double fc = sliderFc->getValue();
        float normalized = (fc - 50) / (5000 - 50);
        processor.setParameter(normalized * (20e3 - 100) + 100, 0);
//        processor.R = sqrt(RC/(2*M_PI*fc));
//        processor.C = sqrt(1./(2*M_PI*fc*RC));
//        sprintf(str,"%.1e",processor.R);
//        txtR->setText(str);
//        sprintf(str,"%.1e",processor.C);
        //txtC->setText(str);
        //[/UserSliderCode_sliderFc]
    }
    else if (sliderThatWasMoved == sliderRC)
    {
        //[UserSliderCode_sliderRC] -- add your slider handling code here..
        double fc = sliderFc->getValue();
        double RC = pow(10.0,(sliderRC->getValue()));
//        processor.R = sqrt(RC/(2*M_PI*fc));
//        processor.C = sqrt(1./(2*M_PI*fc*RC));
//        sprintf(str,"%.1e",processor.R);
//        txtR->setText(str);
//        sprintf(str,"%.1e",processor.C);
        //txtC->setText(str);
        //[/UserSliderCode_sliderRC]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JuceTemplateAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor"
                 constructorParams="JuceTemplateAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor(&amp;p), processor(p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="250" initialHeight="140">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="Fc" id="7e094da79667b628" memberName="sliderFc" virtualName=""
          explicitFocusOrder="0" pos="8 8 240 24" min="50" max="5000" int="0"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="Distortion" id="4790b9f95affbe6d" memberName="sliderRC"
          virtualName="" explicitFocusOrder="0" pos="8 40 240 24" min="0"
          max="6" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="R" id="309015366ea4b01e" memberName="lblR" virtualName=""
         explicitFocusOrder="0" pos="8 72 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="R" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="C" id="e24a935d9c5fdf42" memberName="lblC" virtualName=""
         explicitFocusOrder="0" pos="8 104 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="C" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="R" id="1bbf6f618906b5ca" memberName="txtR" virtualName=""
              explicitFocusOrder="0" pos="32 72 150 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="0" caret="0" popupmenu="0"/>
  <TEXTEDITOR name="C" id="55c16beb2ccd1e93" memberName="txtC" virtualName=""
              explicitFocusOrder="0" pos="32 104 150 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="0" caret="0" popupmenu="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
