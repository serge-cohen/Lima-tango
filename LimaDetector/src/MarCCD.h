//=============================================================================
//
// file :        MarCCD.h
//
// description : Include for the MarCCD class.
//
// project :	
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
#ifndef _MarCCD_H
#define _MarCCD_H


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
#include <MarccdCamera.h>
#include <MarccdInterface.h>
#include "Factory.h"

#define MAX_ATTRIBUTE_STRING_LENGTH 	256

using namespace lima;
using namespace std;

namespace MarCCD_ns
{

/**
 * Class Description:
 * 
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::FAULT :
*  Tango::RUNNING :
 */


class MarCCD: public Tango::Device_4Impl
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
		Tango::DevString	*attr_imageName_read;
		Tango::DevString	attr_imageName_write;
		Tango::DevUShort	*attr_imageIndex_read;
		Tango::DevUShort	attr_imageIndex_write;
		Tango::DevDouble	*attr_waitFileOnDiskTime_read;
		Tango::DevDouble	attr_waitFileOnDiskTime_write;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
/**
 *	Detector IP address
 */
	string	detectorIP;
/**
 *	Detector port number
 */
	Tango::DevULong	detectorPort;
/**
 *	Detector generated image(s) path.
 */
	string	detectorTargetPath;
/**
 *	During acquisition, this is the time before declaring that is no available image returned by detector. (in ms)
 */
	Tango::DevUShort	readerTimeout;
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
	MarCCD(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	MarCCD(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device name
 *	@param d	Device description.
 */
	MarCCD(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */	
	~MarCCD() {delete_device();};
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
 * @name MarCCD methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for imageName acquisition result.
 */
	virtual void read_imageName(Tango::Attribute &attr);
/**
 *	Write imageName attribute values to hardware.
 */
	virtual void write_imageName(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for imageIndex acquisition result.
 */
	virtual void read_imageIndex(Tango::Attribute &attr);
/**
 *	Write imageIndex attribute values to hardware.
 */
	virtual void write_imageIndex(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for waitFileOnDiskTime acquisition result.
 */
	virtual void read_waitFileOnDiskTime(Tango::Attribute &attr);
/**
 *	Write waitFileOnDiskTime attribute values to hardware.
 */
	virtual void write_waitFileOnDiskTime(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for imageName attribute.
 */
	virtual bool is_imageName_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for imageIndex attribute.
 */
	virtual bool is_imageIndex_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for waitFileOnDiskTime attribute.
 */
	virtual bool is_waitFileOnDiskTime_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for TakeBackground command.
 */
	virtual bool is_TakeBackground_allowed(const CORBA::Any &any);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();
/**
 * Command to force the MarCCD detector to get a background frame.
 *	@exception DevFailed
 */
	void	take_background();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

	//	Here is the end of the automatic code generation part
	//-------------------------------------------------------------	
	// return true if the device is correctly initialized in init_device
	bool is_device_initialized(){return m_is_device_initialized;};


protected :	
	//	Add your own data members here
	//-----------------------------------------

        //- Store the values into the property
        //- Properties stuff    
        int                 find_index_from_property_name(Tango::DbData& dev_prop, string property_name);
        template <class T>
        void                create_property_if_empty(Tango::DbData& dev_prop,T value, string property_name);    
        template <class T>
        void                set_property(string property_name, T value);
        template <class T>
        T                   get_property(string property_name) ;
	
	bool 				    m_is_device_initialized ;
	std::stringstream		m_status_message;
	
	//LIMA objects
    Marccd::Camera*         m_camera;
	Marccd::Interface*		m_hw;
	CtControl*				m_ct;	
};

}	// namespace_ns

#endif	// _MarCCD_H
