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
#include "tango.h"

#include "HwInterface.h"
#include "CtControl.h"
#include "CtImage.h"
#include "CtAcquisition.h"
#include <Andor3Camera.h>
#include <Andor3Interface.h>
#include "Factory.h"

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
