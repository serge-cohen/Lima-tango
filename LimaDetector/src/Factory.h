#ifndef _FACTORY_H_
#define _FACTORY_H_


//- Workaround for the RGB24 bug
#ifdef WIN32
#include <tango.h>
#endif

#include <Singleton.h>

#include <HwInterface.h>
#include <CtControl.h>
#include "Debug.h"
#include <yat/threading/Mutex.h>

#ifndef WIN32
#include <tango.h>
#endif

#ifdef SIMULATOR_ENABLED
#include <SimulatorInterface.h>
#endif

#ifdef AVIEX_ENABLED  
#include <AviexCamera.h>
#include <AviexDetInfoCtrlObj.h>
#include <AviexSyncCtrlObj.h>
#include <AviexRoiCtrlObj.h>
#include <AviexBinCtrlObj.h>
#include <AviexInterface.h>
#endif

#ifdef BASLER_ENABLED  
#include <BaslerInterface.h>
#endif

#ifdef XPAD_ENABLED
#include <XpadInterface.h>
#endif

#ifdef PILATUS_ENABLED
#include <PilatusInterface.h>
#endif

#ifdef MARCCD_ENABLED
#include <MarccdInterface.h>
#endif

#ifdef ADSC_ENABLED
#include <AdscInterface.h>
#endif

#ifdef PROSILICA_ENABLED
#include <ProsilicaInterface.h>
#include <ProsilicaCamera.h>
#include <ProsilicaDetInfoCtrlObj.h>
#include <ProsilicaBufferCtrlObj.h>
#include <ProsilicaVideoCtrlObj.h>
#include <ProsilicaSyncCtrlObj.h>   
#endif

#ifdef PRINCETON_ENABLED
#include <RoperScientificCamera.h>
#include <RoperScientificBinCtrlObj.h>
#include <RoperScientificDetInfoCtrlObj.h>
#include <RoperScientificRoiCtrlObj.h>
#include <RoperScientificSyncCtrlObj.h>   
#include <RoperScientificInterface.h>
#endif

#ifdef PCO_ENABLED
    #include <Pco.h>
    #include <PcoBufferCtrlObj.h>
    #include <PcoCamera.h>
    #include <PcoCameraUtils.h>
    #include <PcoDetInfoCtrlObj.h>
    #include <PcoInterface.h>
    #include <PcoSyncCtrlObj.h>   
#endif

#ifdef PERKINELMER_ENABLED
    #include <PerkinElmerBinCtrlObj.h>
    #include <PerkinElmerCompatibility.h>
    #include <PerkinElmerDetInfoCtrlObj.h>
    #include <PerkinElmerInterface.h>
    #include <PerkinElmerSyncCtrlObj.h>    
#endif

#ifdef ANDOR3_ENABLED
    #include <Andor3BinCtrlObj.h>
    #include <Andor3Camera.h>
    #include <Andor3DetInfoCtrlObj.h>
    #include <Andor3Interface.h>
    #include <Andor3RoiCtrlObj.h>
    #include <Andor3SyncCtrlObj.h>    
#endif



using namespace lima;

class ControlFactory : public Singleton<ControlFactory>
{
 public:

    CtControl* get_control(const std::string& detector_type);
    void reset(const std::string& detector_type);
    //init the specific device, necessary when user call Init on generic device
    void init_specific_device(const std::string& detector_type);
    //get the state in a AutoMutex lock
    Tango::DevState get_state(void);
    //get the status in a AutoMutex lock
    std::string get_status(void);
    //fix the state in a AutoMutex lock
    void set_state(Tango::DevState state);
    //fix the status in a AutoMutex lock
    void set_status(const std::string& status);

private:
	void initialize_pointers();
#ifdef SIMULATOR_ENABLED
    Simulator::Camera* my_camera_simulator;
    Simulator::Interface* my_interface_simulator;
#endif

#ifdef AVIEX_ENABLED  
    Aviex::Camera* my_camera_aviex;
    Aviex::Interface* my_interface_aviex;
#endif
    
#ifdef BASLER_ENABLED  
    Basler::Camera* my_camera_basler;
    Basler::Interface* my_interface_basler;
#endif

#ifdef XPAD_ENABLED
    Xpad::Camera* my_camera_xpad;
    Xpad::Interface* my_interface_xpad;
#endif

#ifdef PILATUS_ENABLED      
    Pilatus::Camera* my_camera_pilatus;
    Pilatus::Interface* my_interface_pilatus;
#endif

#ifdef MARCCD_ENABLED      
    Marccd::Camera* my_camera_marccd;
    Marccd::Interface* my_interface_marccd;
#endif

#ifdef ADSC_ENABLED      
    Adsc::Camera* my_camera_adsc;
    Adsc::Interface* my_interface_adsc;
#endif

#ifdef PROSILICA_ENABLED      
    Prosilica::Camera* my_camera_prosilica;
    Prosilica::Interface* my_interface_prosilica;
#endif

#ifdef PRINCETON_ENABLED
    RoperScientific::Camera* my_camera_princeton;
    RoperScientific::Interface* my_interface_princeton;
#endif

#ifdef PCO_ENABLED
    Pco::Camera* my_camera_pco;
    Pco::Interface* my_interface_pco;
#endif

#ifdef PERKINELMER_ENABLED
	PerkinElmer::Interface*        my_interface_perkinelmer;
#endif

#ifdef ANDOR3_ENABLED
    Andor3::Camera* my_camera_andor3;
    Andor3::Interface* my_interface_andor3;
#endif

	CtControl*                     my_control;
	static bool                    is_created;
	std::string                    my_server_name;  
	std::string                    my_device_name;
	Tango::DevState				   my_state;
	stringstream				   my_status;

    //lock the singleton acess
    yat::Mutex object_lock;

    //lock the singleton acess
    yat::Mutex object_state_lock;

};

#endif

