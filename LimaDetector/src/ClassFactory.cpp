static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :        ClassFactory.cpp
//
// description : C++ source for the class_factory method of the DServer
//               device class. This method is responsible for the creation of
//               all class singleton for a device server. It is called
//               at device server startup
//
// project :     TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL: $
//
// CVS only:
// $Source:  $
// $Log:  $
//
// copyleft :    European Synchrotron Radiation Facility
//               BP 220, Grenoble 38043
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifdef WIN32
#include "tango.h"
#endif
#include <LimaDetectorClass.h>

#ifdef SIMULATOR_ENABLED
#include <SimulatorCCDClass.h>
#endif

#ifdef AVIEX_ENABLED
#include <AviexCCDClass.h>
#endif

#ifdef BASLER_ENABLED
#include <BaslerCCDClass.h>
#endif

#ifdef PILATUS_ENABLED
#include <PilatusPixelDetectorClass.h>
#endif

#ifdef XPAD_ENABLED
#include <XpadPixelDetectorClass.h>
#endif

#ifdef MARCCD_ENABLED
#include <MarCCDClass.h>
#endif

#ifdef ADSC_ENABLED
#include <AdscCCDClass.h>
#endif

#ifdef PROSILICA_ENABLED
#include <ProsilicaCCDClass.h>
#endif

#ifdef PRINCETON_ENABLED
#include <PrincetonCCDClass.h>
#endif

#ifdef PCO_ENABLED
#include <PcoClass.h>
#endif

#ifdef PERKINELMER_ENABLED
#include <PerkinElmerClass.h>
#endif

#ifdef ANDOR3_ENABLED
#include <Andor3Class.h>
#endif

#ifdef VIEWORKSVP_ENABLED
#include <VieworksVPClass.h>
#endif

#ifndef WIN32
#include "tango.h"
#endif

/**
 *	Create LimaDetectorClass singleton and store it in DServer object.
 */

void Tango::DServer::class_factory()
{
    add_class(LimaDetector_ns::LimaDetectorClass::init("LimaDetector"));

#ifdef SIMULATOR_ENABLED
    add_class(SimulatorCCD_ns::SimulatorCCDClass::init("SimulatorCCD"));
#endif

#ifdef AVIEX_ENABLED
    add_class(AviexCCD_ns::AviexCCDClass::init("AviexCCD"));
#endif
    
#ifdef BASLER_ENABLED
    add_class(BaslerCCD_ns::BaslerCCDClass::init("BaslerCCD"));
#endif

#ifdef PILATUS_ENABLED
    add_class(PilatusPixelDetector_ns::PilatusPixelDetectorClass::init("PilatusPixelDetector"));
#endif

#ifdef XPAD_ENABLED	
    add_class(XpadPixelDetector_ns::XpadPixelDetectorClass::init("XpadPixelDetector"));
#endif

#ifdef MARCCD_ENABLED	
    add_class(MarCCD_ns::MarCCDClass::init("MarCCD"));
#endif

#ifdef ADSC_ENABLED	
    add_class(AdscCCD_ns::AdscCCDClass::init("AdscCCD"));
#endif

#ifdef PROSILICA_ENABLED
    add_class(ProsilicaCCD_ns::ProsilicaCCDClass::init("ProsilicaCCD"));
#endif

#ifdef PRINCETON_ENABLED
    add_class(PrincetonCCD_ns::PrincetonCCDClass::init("PrincetonCCD"));
#endif

#ifdef PCO_ENABLED
    add_class(Pco_ns::PcoClass::init("Pco"));
#endif

#ifdef PERKINELMER_ENABLED
    add_class(PerkinElmer_ns::PerkinElmerClass::init("PerkinElmer"));
#endif

#ifdef ANDOR3_ENABLED
    add_class(Andor3_ns::Andor3Class::init("Andor3"));
#endif

#ifdef VIEWORKSVP_ENABLED
    add_class(VieworksVP_ns::VieworksVPClass::init("VieworksVP"));
#endif
}

