static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         MarCCD.cpp
//
// description :  C++ source for the MarCCD and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                MarCCD are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
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
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name|  Method name
//	----------------------------------------
//  State   |  dev_state()
//  Status  |  dev_status()
//
//===================================================================


#include <tango.h>
#include <PogoHelper.h>
#include <MarCCD.h>
#include <MarCCDClass.h>

namespace MarCCD_ns
{

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::MarCCD(string &s)
// 
// description : 	constructor for simulated MarCCD
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name 
//
//-----------------------------------------------------------------------------
MarCCD::MarCCD(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
	init_device();
}

MarCCD::MarCCD(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
	init_device();
}

MarCCD::MarCCD(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		MarCCD::delete_device()
// 
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void MarCCD::delete_device()
{
	//	Delete device allocated objects
	//DELETE_SCALAR_ATTRIBUTE(attr_threshold_read);
	//DELETE_DEVSTRING_ATTRIBUTE(attr_gain_read);
	
	//!!!! ONLY LimaDetector device can do this !!!!
	//if(m_ct!=0)
	//{
	//	ControlFactory::instance().reset("MarCCD");
	//	m_ct = 0;
	//}
}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::init_device()
// 
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void MarCCD::init_device()
{
	INFO_STREAM << "MarCCD::MarCCD() create device " << device_name << endl;

	// Initialise variables to default values
	//--------------------------------------------
	get_device_property();
	//CREATE_SCALAR_ATTRIBUTE(attr_threshold_read);
	//CREATE_DEVSTRING_ATTRIBUTE(attr_gain_read,MAX_ATTRIBUTE_STRING_LENGTH);
	
	m_is_device_initialized = false;
	m_status_message.str("");
	
	try
	{
		//- get the main object used to pilot the lima framework
		//in fact LimaDetector is create the singleton control objet
		//so this call, will only return existing object, no need to give it the ip !!
		m_ct = ControlFactory::instance().get_control("MarCCD");
		if( !m_ct )
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the lima control object !" << std::endl;
std::cout<<"MarCCD::init_device -> Initialization Failed : Unable to get the lima control object !" << std::endl;
			m_status_message <<"Initialization Failed : Unable to get the lima control object !" << std::endl;
			m_is_device_initialized = false;
			set_state(Tango::INIT);		
			return;			
		}
		
		//- get interface to specific camera
		m_hw = dynamic_cast<Marccd::Interface*>(m_ct->hwInterface());
		if( !m_hw )
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin !" << std::endl;
std::cout<<"MarCCD::init_device -> Initialization Failed : Unable to get the interface of camera plugin !" << std::endl;
			m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin !" << std::endl;
			m_is_device_initialized = false;
			set_state(Tango::INIT);		
			return;			
		}
		
	}
	catch(Exception& e)
	{
		INFO_STREAM<<"Initialization Failed : " << e.getErrMsg() << std::endl;
std::cout<<"MarCCD::init_device -> Initialization Failed -> e.getErrMsg : " << e.getErrMsg() << std::endl;
		m_status_message <<"Initialization Failed : " << e.getErrMsg( ) << std::endl;
		m_is_device_initialized = false;
		set_state(Tango::INIT);		
		return;
	}
	catch(...)
	{
		INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
std::cout<<"MarCCD::init_device -> Initialization Failed : UNKNOWN"<<endl;
		m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
		set_state(Tango::INIT);
		m_is_device_initialized = false;
		return;
	}
	m_is_device_initialized = true;
	set_state(Tango::STANDBY);	
	this->dev_state();	
}


//+----------------------------------------------------------------------------
//
// method : 		MarCCD::get_device_property()
// 
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void MarCCD::get_device_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read device properties from database.(Automatic code generation)
	//------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("DetectorIP"));
	dev_prop.push_back(Tango::DbDatum("DetectorPort"));
	dev_prop.push_back(Tango::DbDatum("FullImagePathName"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	MarCCDClass	*ds_class =
		(static_cast<MarCCDClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize DetectorIP from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorIP;
	else {
		//	Try to initialize DetectorIP from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorIP;
	}
	//	And try to extract DetectorIP value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorIP;

	//	Try to initialize DetectorPort from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorPort;
	else {
		//	Try to initialize DetectorPort from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorPort;
	}
	//	And try to extract DetectorPort value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorPort;

	//	Try to initialize FullImagePathName from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  fullImagePathName;
	else {
		//	Try to initialize FullImagePathName from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  fullImagePathName;
	}
	//	And try to extract FullImagePathName value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  fullImagePathName;



	//	End of Automatic code generation
	//------------------------------------------------------------------

}
//+----------------------------------------------------------------------------
//
// method : 		MarCCD::always_executed_hook()
// 
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void MarCCD::always_executed_hook()
{
	//- get the main object used to pilot the lima framework
	//in fact LimaCCD is create the singleton control objet
	//so this call, will only return existing object, no need to give it the ip !!
	m_ct = ControlFactory::instance().get_control("MarCCD");
	
	//- get interface to specific detector
	if( m_ct )
		m_hw = dynamic_cast<Marccd::Interface*>(m_ct->hwInterface());
}
//+----------------------------------------------------------------------------
//
// method : 		MarCCD::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
//void MarCCD::read_attr_hardware(vector<long> &attr_list)
//{
//	DEBUG_STREAM << "MarCCD::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
//	//	Add your own code here
//}
//+----------------------------------------------------------------------------
//
// method : 		MarCCD::write_threshold
// 
// description : 	Write threshold attribute values to hardware.
//
//-----------------------------------------------------------------------------
//void MarCCD::write_threshold(Tango::WAttribute &attr)
//{
//	DEBUG_STREAM << "MarCCD::write_threshold(Tango::WAttribute &attr) entering... "<< endl;
//	try
//	{
//		attr.get_write_value(attr_threshold_write);
//		//m_hw->setThresholdGain(attr_threshold_write, m_hw->getGain());
//	
//	}
//	catch(Tango::DevFailed& df)
//	{
//		ERROR_STREAM << df << endl;
//        //- rethrow exception
//        Tango::Except::re_throw_exception(df,
//					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
//					static_cast<const char*> (string(df.errors[0].desc).c_str()),
//                    static_cast<const char*> ("MarCCD::write_threshold"));
//	}	
//	catch(Exception& e)
//	{
//		ERROR_STREAM << e.getErrMsg() << endl;
//        //- throw exception
//        Tango::Except::throw_exception(
//					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
//					static_cast<const char*> (e.getErrMsg().c_str()),
//                    static_cast<const char*> ("MarCCD::write_threshold"));		
//	}		
//}


//+----------------------------------------------------------------------------
//
// method : 		MarCCD::read_threshold
// 
// description : 	Extract real attribute values for threshold acquisition result.
//
//-----------------------------------------------------------------------------
//void MarCCD::read_threshold(Tango::Attribute &attr)
//{
//	DEBUG_STREAM << "MarCCD::read_threshold(Tango::Attribute &attr) entering... "<< endl;
//	try
//	{
//		//*attr_threshold_read = m_hw->getThreshold();
//		attr.set_value(attr_threshold_read);
//	
//	}
//	catch(Tango::DevFailed& df)
//	{
//		ERROR_STREAM << df << endl;
//        //- rethrow exception
//        Tango::Except::re_throw_exception(df,
//					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
//					static_cast<const char*> (string(df.errors[0].desc).c_str()),
//                    static_cast<const char*> ("MarCCD::read_threshold"));
//	}	
//	catch(Exception& e)
//	{
//		ERROR_STREAM << e.getErrMsg() << endl;
//        //- throw exception
//        Tango::Except::throw_exception(
//					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
//					static_cast<const char*> (e.getErrMsg().c_str()),
//                    static_cast<const char*> ("MarCCD::read_threshold"));		
//	}		
//}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::write_gain
// 
// description : 	Write gain attribute values to hardware.
//
//-----------------------------------------------------------------------------
//void MarCCD::write_gain(Tango::WAttribute &attr)
//{
//	DEBUG_STREAM << "MarCCD::write_gain(Tango::WAttribute &attr) entering... "<< endl;
	//try
	//{
	//	m_gain = *attr_gain_read;
	//	string previous = m_gain;
	//	attr.get_write_value(attr_gain_write);
	//	string current = attr_gain_write;
	//	if(current.compare("LOW")!=0 && current.compare("MID")!=0 && current.compare("HIGH")!=0 && current.compare("UHIGH")!=0)
	//	{
	//		m_gain = previous;			
	//		attr_gain_write = new char [m_gain.size()+1];
	//		strcpy (attr_gain_write, m_gain.c_str());
	//		
	//		Tango::Except::throw_exception(	(const char*) ("CONFIGURATION_ERROR"),
	//										(const char*) ("Available Gain values are: \n- LOW \n- MID \n- HIGH \n- UHIGH"),
	//										(const char*) ("MarCCD::write_gain"));
	//	}

	//	//- THIS IS AN AVAILABLE TRIGER MODE
	//	m_gain = attr_gain_write;
	//
	//	Marccd::Gain new_gain;
	//	if(m_gain.compare("LOW")==0)
	//		new_gain = Communication::LOW;
	//	else if(m_gain.compare("MID")==0)
	//		new_gain = Communication::MID;
	//	else if(m_gain.compare("HIGH")==0)
	//		new_gain = Communication::HIGH;
	//	else			
	//		new_gain = Communication::ULTRA_HIGH;

	//	//m_hw->setThresholdGain(m_hw->getThreshold(), new_gain);
	//}
	//catch(Tango::DevFailed& df)
	//{
	//	ERROR_STREAM << df << endl;
 //       //- rethrow exception
 //       Tango::Except::re_throw_exception(df,
	//				static_cast<const char*> ("TANGO_DEVICE_ERROR"),
	//				static_cast<const char*> (string(df.errors[0].desc).c_str()),
 //                   static_cast<const char*> ("MarCCD::write_gain"));
	//}	
	//catch(Exception& e)
	//{
	//	ERROR_STREAM << e.getErrMsg() << endl;
 //       //- throw exception
 //       Tango::Except::throw_exception(
	//				static_cast<const char*> ("TANGO_DEVICE_ERROR"),
	//				static_cast<const char*> (e.getErrMsg().c_str()),
 //                   static_cast<const char*> ("MarCCD::write_gain"));		
	//}		
//}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::read_gain
// 
// description : 	Extract real attribute values for gain acquisition result.
//
//-----------------------------------------------------------------------------
//void MarCCD::read_gain(Tango::Attribute &attr)
//{
//	DEBUG_STREAM << "MarCCD::read_gain(Tango::Attribute &attr) entering... "<< endl;
	//try
	//{
	//	Communication::Gain current_gain = m_hw->getGain();
	//	switch (current_gain)
	//	{
	//		case Communication::LOW 	: strcpy(*attr_gain_read, "LOW")	;	break;
	//		case Communication::MID 	: strcpy(*attr_gain_read, "MID")	;	break;
	//		case Communication::HIGH	: strcpy(*attr_gain_read, "HIGH")	;	break;
	//		default /*ULTRA_HIGH*/		: strcpy(*attr_gain_read, "UHIGH")	;	break;
	//	}
	//	
	//	attr.set_value(attr_gain_read);
	//}
	//catch(Tango::DevFailed& df)
	//{
	//	ERROR_STREAM << df << endl;
 //       //- rethrow exception
 //       Tango::Except::re_throw_exception(df,
	//				static_cast<const char*> ("TANGO_DEVICE_ERROR"),
	//				static_cast<const char*> (string(df.errors[0].desc).c_str()),
 //                   static_cast<const char*> ("MarCCD::read_gain"));
	//}	
	//catch(Exception& e)
	//{
	//	ERROR_STREAM << e.getErrMsg() << endl;
 //       //- throw exception
 //       Tango::Except::throw_exception(
	//				static_cast<const char*> ("TANGO_DEVICE_ERROR"),
	//				static_cast<const char*> (e.getErrMsg().c_str()),
 //                   static_cast<const char*> ("MarCCD::read_gain"));		
	//}	
//}

//+------------------------------------------------------------------
/**
 *	method:	MarCCD::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState MarCCD::dev_state()
{
	Tango::DevState	argout = DeviceImpl::dev_state();
	DEBUG_STREAM << "MarCCD::dev_state(): entering... !" << endl;	
	//	Add your own code to control device here
	stringstream    DeviceStatus;
	DeviceStatus 	<< "";
	Tango::DevState DeviceState	= Tango::STANDBY;
	if( !m_is_device_initialized )
	{
		DeviceState			= Tango::INIT;
		DeviceStatus		<< m_status_message.str();
std::cout << "MarCCD::dev_state -> !m_is_device_initialized." << std::endl;
	}
	else if ( !m_ct )
	{
		DeviceState			= Tango::INIT;
		DeviceStatus		<<"Initialization Failed : Unable to get the lima control object !\n\n";				
std::cout << "MarCCD::dev_state -> !m_ct." << std::endl;
	}
	else
	{
		CtControl::Status status;
		m_ct->getStatus(status);
		if (status.AcquisitionStatus == lima::AcqReady)
		{
			DeviceState=Tango::STANDBY;
			DeviceStatus<<"MarCCD::Waiting for Request ...\n"<<endl;
		}		
		else if(status.AcquisitionStatus == lima::AcqRunning)
		{
			DeviceState=Tango::RUNNING;
			DeviceStatus<<"MarCCD::Acquisition is Running ...\n"<<endl;
		}
		else
		{
			DeviceState=Tango::FAULT;//FAULT
			DeviceStatus<<"MarCCD::Acquisition is in Fault\n"<<endl;
		}
	}
	
	set_state(DeviceState);
	set_status(DeviceStatus.str());
//std::cout << "MarCCD::dev_state() -> DeviceStatus = " << DeviceStatus.str() << std::endl;
	argout = DeviceState;
	return argout;
}


//+------------------------------------------------------------------
/**
 *	method:	MarCCD::set_threshold_and_gain
 *
 *	description:	method to execute "SetThresholdAndGain"
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
//void MarCCD::set_threshold_and_gain(const Tango::DevVarLongStringArray *argin)
//{
//	DEBUG_STREAM << "MarCCD::set_threshold_and_gain(): entering... !" << endl;
//
//	//	Add your own code to control device here
//
//}

//+------------------------------------------------------------------
/**
 *	method:	MarCCD::set_mx_settings
 *
 *	description:	method to execute "SetMxSettings"
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
//void MarCCD::set_mx_settings(Tango::DevString argin)
//{
//	DEBUG_STREAM << "MarCCD::set_mx_settings(): entering... !" << endl;
//
//	//	Add your own code to control device here
//	try
//	{
//		std::string str_cmd_to_send = argin;
//		//m_hw->setMxSettings(str_cmd_to_send);
//	}
//	catch(Tango::DevFailed& df)
//	{
//		ERROR_STREAM << df << endl;
//        //- rethrow exception
//        Tango::Except::re_throw_exception(df,
//					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
//					static_cast<const char*> (string(df.errors[0].desc).c_str()),
//                    static_cast<const char*> ("MarCCD::set_mx_settings"));
//	}	
//	catch(Exception& e)
//	{
//		ERROR_STREAM << e.getErrMsg() << endl;
//        //- throw exception
//        Tango::Except::throw_exception(
//					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
//					static_cast<const char*> (e.getErrMsg().c_str()),
//                    static_cast<const char*> ("MarCCD::set_mx_settings"));		
//	}	
//
//}



}	//	namespace
