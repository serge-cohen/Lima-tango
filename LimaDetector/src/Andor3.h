//=============================================================================
//
// file :        Andor3.h
//
// description : Include for the Andor3 class.
//
// project :	Specific class for Andor3 detector
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
// copyleft :    Synchrotron SOLEIL 
//               L'Orme des merisiers - Saint Aubin
//		 BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifndef _ANDOR3_H
#define _ANDOR3_H


//using namespace Tango;

/**
 * @author	$Author:  $
 * @version	$Revision:  $
 */

 //	Add your own constant definitions here.
 //-----------------------------------------------
#ifdef WIN32
#include "tango.h"
#endif

#undef RGB24

#include "HwInterface.h"
#include "CtControl.h"
#include "CtImage.h"
#include "CtAcquisition.h"
#include <Andor3Camera.h>
#include <Andor3Interface.h>
#include "Factory.h"

#ifndef WIN32
#include "tango.h"
#endif


const size_t MAX_STRING_LENGTH = 256;

using namespace std;


namespace Andor3_ns
{

/**
 * Class Description:
 * This class is the specific Lima device for the Andor3 cameras (Neo,...)
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::FAULT :
*  Tango::RUNNING :
 */


class Andor3: public Tango::Device_4Impl
{
public :
	//	Add your own data members here
	//-----------------------------------------


	//	Here is the Start of the automatic code generation part
	//-------------------------------------------------------------	
/**
 *	@name attributes
 *	Attribute member data.
 */
//@{
		Tango::DevUShort	*attr_adcGain_read;
		Tango::DevUShort	attr_adcGain_write;
		Tango::DevString	*attr_adcGainStr_read;
		Tango::DevUShort	*attr_adcRate_read;
		Tango::DevUShort	attr_adcRate_write;
		Tango::DevString	*attr_adcRateStr_read;
		Tango::DevUShort	*attr_electronicShutterMode_read;
		Tango::DevUShort	attr_electronicShutterMode_write;
		Tango::DevDouble	*attr_temperatureSP_read;
		Tango::DevDouble	attr_temperatureSP_write;
		Tango::DevDouble	*attr_temperature_read;
		Tango::DevBoolean	*attr_cooler_read;
		Tango::DevBoolean	attr_cooler_write;
		Tango::DevString	*attr_coolingStatus_read;
		Tango::DevString	*attr_electronicShutterModeStr_read;
		Tango::DevBoolean	*attr_bufferOverflow_read;
		Tango::DevBoolean	attr_bufferOverflow_write;
		Tango::DevLong	*attr_fanSpeed_read;
		Tango::DevLong	attr_fanSpeed_write;
		Tango::DevBoolean	*attr_overlap_read;
		Tango::DevBoolean	attr_overlap_write;
		Tango::DevBoolean	*attr_spuriousNoiseFilter_read;
		Tango::DevBoolean	attr_spuriousNoiseFilter_write;
		Tango::DevBoolean	*attr_syncTriggering_read;
		Tango::DevBoolean	attr_syncTriggering_write;
		Tango::DevLong	*attr_simpleGainControl_read;
		Tango::DevLong	attr_simpleGainControl_write;
		Tango::DevString	*attr_simpleGainControlStr_read;
		Tango::DevDouble	*attr_bytesPerPixel_read;
		Tango::DevString	*attr_firmwareVersion_read;
		Tango::DevDouble	*attr_frameRate_read;
		Tango::DevDouble	*attr_frameRateMax_read;
		Tango::DevDouble	*attr_frameRateMin_read;
		Tango::DevBoolean	*attr_fullRoiControl_read;
		Tango::DevLong	*attr_imageSize_read;
		Tango::DevDouble	*attr_maxFrameRateTransfer_read;
		Tango::DevDouble	*attr_readoutTime_read;
		Tango::DevString	*attr_serialNumber_read;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
/**
 *	Path of the bitflow
 */
	string	bitFlowPath;
/**
 *	Camera Number for the Andor driver (ie: DeviceIndex)
 */
	Tango::DevLong	cameraNumber;
//@}

/**
 *	@name Device properties
 *	Device property member data.
 */
//@{
//@}

/**@name Constructors
 * Miscellaneous constructors */
//@{
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	Andor3(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	Andor3(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device name
 *	@param d	Device description.
 */
	Andor3(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */	
	~Andor3() {delete_device();};
/**
 *	will be called at device destruction or at init command.
 */
	void delete_device();
//@}

	
/**@name Miscellaneous methods */
//@{
/**
 *	Initialize the device
 */
	virtual void init_device();
/**
 *	Always executed method before execution command method.
 */
	virtual void always_executed_hook();

//@}

/**
 * @name Andor3 methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for adcGain acquisition result.
 */
	virtual void read_adcGain(Tango::Attribute &attr);
/**
 *	Write adcGain attribute values to hardware.
 */
	virtual void write_adcGain(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for adcGainStr acquisition result.
 */
	virtual void read_adcGainStr(Tango::Attribute &attr);
/**
 *	Extract real attribute values for adcRate acquisition result.
 */
	virtual void read_adcRate(Tango::Attribute &attr);
/**
 *	Write adcRate attribute values to hardware.
 */
	virtual void write_adcRate(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for adcRateStr acquisition result.
 */
	virtual void read_adcRateStr(Tango::Attribute &attr);
/**
 *	Extract real attribute values for electronicShutterMode acquisition result.
 */
	virtual void read_electronicShutterMode(Tango::Attribute &attr);
/**
 *	Write electronicShutterMode attribute values to hardware.
 */
	virtual void write_electronicShutterMode(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for temperatureSP acquisition result.
 */
	virtual void read_temperatureSP(Tango::Attribute &attr);
/**
 *	Write temperatureSP attribute values to hardware.
 */
	virtual void write_temperatureSP(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for temperature acquisition result.
 */
	virtual void read_temperature(Tango::Attribute &attr);
/**
 *	Extract real attribute values for cooler acquisition result.
 */
	virtual void read_cooler(Tango::Attribute &attr);
/**
 *	Write cooler attribute values to hardware.
 */
	virtual void write_cooler(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for coolingStatus acquisition result.
 */
	virtual void read_coolingStatus(Tango::Attribute &attr);
/**
 *	Extract real attribute values for electronicShutterModeStr acquisition result.
 */
	virtual void read_electronicShutterModeStr(Tango::Attribute &attr);
/**
 *	Extract real attribute values for bufferOverflow acquisition result.
 */
	virtual void read_bufferOverflow(Tango::Attribute &attr);
/**
 *	Write bufferOverflow attribute values to hardware.
 */
	virtual void write_bufferOverflow(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for fanSpeed acquisition result.
 */
	virtual void read_fanSpeed(Tango::Attribute &attr);
/**
 *	Write fanSpeed attribute values to hardware.
 */
	virtual void write_fanSpeed(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for overlap acquisition result.
 */
	virtual void read_overlap(Tango::Attribute &attr);
/**
 *	Write overlap attribute values to hardware.
 */
	virtual void write_overlap(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for spuriousNoiseFilter acquisition result.
 */
	virtual void read_spuriousNoiseFilter(Tango::Attribute &attr);
/**
 *	Write spuriousNoiseFilter attribute values to hardware.
 */
	virtual void write_spuriousNoiseFilter(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for syncTriggering acquisition result.
 */
	virtual void read_syncTriggering(Tango::Attribute &attr);
/**
 *	Write syncTriggering attribute values to hardware.
 */
	virtual void write_syncTriggering(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for simpleGainControl acquisition result.
 */
	virtual void read_simpleGainControl(Tango::Attribute &attr);
/**
 *	Write simpleGainControl attribute values to hardware.
 */
	virtual void write_simpleGainControl(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for simpleGainControlStr acquisition result.
 */
	virtual void read_simpleGainControlStr(Tango::Attribute &attr);
/**
 *	Extract real attribute values for bytesPerPixel acquisition result.
 */
	virtual void read_bytesPerPixel(Tango::Attribute &attr);
/**
 *	Extract real attribute values for firmwareVersion acquisition result.
 */
	virtual void read_firmwareVersion(Tango::Attribute &attr);
/**
 *	Extract real attribute values for frameRate acquisition result.
 */
	virtual void read_frameRate(Tango::Attribute &attr);
/**
 *	Extract real attribute values for frameRateMax acquisition result.
 */
	virtual void read_frameRateMax(Tango::Attribute &attr);
/**
 *	Extract real attribute values for frameRateMin acquisition result.
 */
	virtual void read_frameRateMin(Tango::Attribute &attr);
/**
 *	Extract real attribute values for fullRoiControl acquisition result.
 */
	virtual void read_fullRoiControl(Tango::Attribute &attr);
/**
 *	Extract real attribute values for imageSize acquisition result.
 */
	virtual void read_imageSize(Tango::Attribute &attr);
/**
 *	Extract real attribute values for maxFrameRateTransfer acquisition result.
 */
	virtual void read_maxFrameRateTransfer(Tango::Attribute &attr);
/**
 *	Extract real attribute values for readoutTime acquisition result.
 */
	virtual void read_readoutTime(Tango::Attribute &attr);
/**
 *	Extract real attribute values for serialNumber acquisition result.
 */
	virtual void read_serialNumber(Tango::Attribute &attr);
/**
 *	Read/Write allowed for adcGain attribute.
 */
	virtual bool is_adcGain_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for adcGainStr attribute.
 */
	virtual bool is_adcGainStr_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for adcRate attribute.
 */
	virtual bool is_adcRate_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for adcRateStr attribute.
 */
	virtual bool is_adcRateStr_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for electronicShutterMode attribute.
 */
	virtual bool is_electronicShutterMode_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for temperatureSP attribute.
 */
	virtual bool is_temperatureSP_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for temperature attribute.
 */
	virtual bool is_temperature_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for cooler attribute.
 */
	virtual bool is_cooler_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for coolingStatus attribute.
 */
	virtual bool is_coolingStatus_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for electronicShutterModeStr attribute.
 */
	virtual bool is_electronicShutterModeStr_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for bufferOverflow attribute.
 */
	virtual bool is_bufferOverflow_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for fanSpeed attribute.
 */
	virtual bool is_fanSpeed_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for overlap attribute.
 */
	virtual bool is_overlap_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for spuriousNoiseFilter attribute.
 */
	virtual bool is_spuriousNoiseFilter_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for syncTriggering attribute.
 */
	virtual bool is_syncTriggering_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for simpleGainControl attribute.
 */
	virtual bool is_simpleGainControl_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for simpleGainControlStr attribute.
 */
	virtual bool is_simpleGainControlStr_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for bytesPerPixel attribute.
 */
	virtual bool is_bytesPerPixel_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for firmwareVersion attribute.
 */
	virtual bool is_firmwareVersion_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for frameRate attribute.
 */
	virtual bool is_frameRate_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for frameRateMax attribute.
 */
	virtual bool is_frameRateMax_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for frameRateMin attribute.
 */
	virtual bool is_frameRateMin_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for fullRoiControl attribute.
 */
	virtual bool is_fullRoiControl_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for imageSize attribute.
 */
	virtual bool is_imageSize_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for maxFrameRateTransfer attribute.
 */
	virtual bool is_maxFrameRateTransfer_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for readoutTime attribute.
 */
	virtual bool is_readoutTime_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for serialNumber attribute.
 */
	virtual bool is_serialNumber_allowed(Tango::AttReqType type);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

	//	Here is the end of the automatic code generation part
	//-------------------------------------------------------------	

    // return true if the device is correctly initialized in init_device
	bool is_device_initialized() { return m_is_device_initialized ;};



protected :	
	//	Add your own data members here
	//-----------------------------------------

    //- Store the values into the property
    //- Properties stuff    
    int find_index_from_property_name(Tango::DbData& dev_prop, string property_name);
    template <class T>
    void create_property_if_empty(Tango::DbData& dev_prop,T value, string property_name);    
    template <class T>
    void set_property(string property_name, T value);
    template <class T>
    T get_property(string property_name) ;
	
    //state & status stuff
	bool m_is_device_initialized ;
	std::stringstream m_status_message;
	
	//LIMA objects
	lima::Andor3::Interface*		m_hw;
	lima::CtControl*				m_ct;	
    lima::Andor3::Camera*           m_camera;
};

}	// namespace_ns

#endif	// _ANDOR3_H
