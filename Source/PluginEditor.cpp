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

    addAndMakeVisible (sliderSustain = new Slider ("Sustain"));
    sliderSustain->setRange (0, 1, 0);
    sliderSustain->setSliderStyle (Slider::LinearHorizontal);
    sliderSustain->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderSustain->addListener (this);

    addAndMakeVisible (sliderLevel = new Slider ("Level"));
    sliderLevel->setRange (0, 1, 0);
    sliderLevel->setSliderStyle (Slider::LinearHorizontal);
    sliderLevel->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderLevel->addListener (this);

    addAndMakeVisible (lblR = new Label ("Sustain",
                                         TRANS("Sustain")));
    lblR->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblR->setJustificationType (Justification::centredLeft);
    lblR->setEditable (false, false, false);
    lblR->setColour (TextEditor::textColourId, Colours::black);
    lblR->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblC = new Label ("Level",
                                         TRANS("Level")));
    lblC->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblC->setJustificationType (Justification::centredLeft);
    lblC->setEditable (false, false, false);
    lblC->setColour (TextEditor::textColourId, Colours::black);
    lblC->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

//    addAndMakeVisible (txtR = new TextEditor ("R"));
//    txtR->setMultiLine (false);
//    txtR->setReturnKeyStartsNewLine (false);
//    txtR->setReadOnly (true);
//    txtR->setScrollbarsShown (false);
//    txtR->setCaretVisible (false);
//    txtR->setPopupMenuEnabled (false);
//    txtR->setText (String());
//
//    addAndMakeVisible (txtC = new TextEditor ("C"));
//    txtC->setMultiLine (false);
//    txtC->setReturnKeyStartsNewLine (false);
//    txtC->setReadOnly (true);
//    txtC->setScrollbarsShown (false);
//    txtC->setCaretVisible (false);
//    txtC->setPopupMenuEnabled (false);
//    txtC->setText (String());


    //[UserPreSize]
//    sliderSustain->setSkewFactorFromMidPoint(500.);
//    sliderLevel->setSkewFactorFromMidPoint(3.);
    //[/UserPreSize]

    setSize (250, 140);


    //[Constructor] You can add your own custom stuff here..
    sliderSustain->setValue(0.5);
    sliderLevel->setValue(1.);
    //[/Constructor]
}

JuceTemplateAudioProcessorEditor::~JuceTemplateAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sliderSustain = nullptr;
    sliderLevel = nullptr;
    lblR = nullptr;
    lblC = nullptr;


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

    sliderSustain->setBounds (8, 40, 240, 24);
    sliderLevel->setBounds (8, 100, 240, 24);
    lblR->setBounds (8, 10, 240, 24);
    lblC->setBounds (8, 70, 240, 24);
//    txtR->setBounds (32, 72, 150, 24);
//    txtC->setBounds (32, 104, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JuceTemplateAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    char str[50];
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderSustain)
    {
        //[UserSliderCode_sliderSustain] -- add your slider handling code here..
        processor.setParameter(sliderSustain->getValue() * (100e3) + 10e3, 0);
//        processor.R = sqrt(RC/(2*M_PI*fc));
//        processor.C = sqrt(1./(2*M_PI*fc*RC));
//        sprintf(str,"%.1e",processor.R);
//        txtR->setText(str);
//        sprintf(str,"%.1e",processor.C);
        //txtC->setText(str);
        //[/UserSliderCode_sliderSustain]
    }
    else if (sliderThatWasMoved == sliderLevel)
    {
        //[UserSliderCode_sliderLevel] -- add your slider handling code here..
        processor.setParameter(sliderLevel->getValue(), 1);
//        processor.R = sqrt(RC/(2*M_PI*fc));
//        processor.C = sqrt(1./(2*M_PI*fc*RC));
//        sprintf(str,"%.1e",processor.R);
//        txtR->setText(str);
//        sprintf(str,"%.1e",processor.C);
        //txtC->setText(str);
        //[/UserSliderCode_sliderLevel]
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
  <SLIDER name="Sustain" id="7e094da79667b628" memberName="sliderSustain" virtualName=""
          explicitFocusOrder="0" pos="8 8 240 24" min="0" max="1" int="0"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="Level" id="4790b9f95affbe6d" memberName="sliderLevel"
          virtualName="" explicitFocusOrder="0" pos="8 40 240 24" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
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
