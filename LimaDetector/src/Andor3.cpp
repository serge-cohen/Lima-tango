static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         Andor3.cpp
//
// description :  C++ source for the Andor3 and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                Andor3 are implemented in this file.
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
#ifdef WIN32
#include <tango.h>
#include <PogoHelper.h>
#endif

#include <Andor3.h>
#include <Andor3Class.h>

#ifndef WIN32
#include "tango.h"
#include <PogoHelper.h>
#endif

namespace Andor3_ns
{

//+----------------------------------------------------------------------------
//
// method : 		Andor3::Andor3(string &s)
//
// description : 	constructor for simulated Andor3
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name
//
//-----------------------------------------------------------------------------
Andor3::Andor3(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
	init_device();
}

Andor3::Andor3(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
	init_device();
}

Andor3::Andor3(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		Andor3::delete_device()
//
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void Andor3::delete_device()
{
	//	Delete device allocated objects
    INFO_STREAM << "Andor3::delete_device() delete device " << device_name << endl;

    DELETE_SCALAR_ATTRIBUTE(attr_adcGain_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_adcGainStr_read);
    DELETE_SCALAR_ATTRIBUTE(attr_adcRate_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_adcRateStr_read);
    DELETE_SCALAR_ATTRIBUTE(attr_electronicShutterMode_read);
    DELETE_SCALAR_ATTRIBUTE(attr_electronicShutterModeStr_read);
    DELETE_SCALAR_ATTRIBUTE(attr_temperatureSP_read);
    DELETE_SCALAR_ATTRIBUTE(attr_temperature_read);
    DELETE_SCALAR_ATTRIBUTE(attr_cooler_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_coolingStatus_read);

    //!!!! ONLY LimaDetector device can do this !!!!
    //if(m_ct!=0)
    //{
    //    ControlFactory::instance().reset("Andor3");
    //    m_ct = 0;
    //}
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::init_device()
//
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void Andor3::init_device()
{
	INFO_STREAM << "Andor3::init_device() create device " << device_name << endl;

	// Initialise variables to default values
	//--------------------------------------------
	get_device_property();

    CREATE_SCALAR_ATTRIBUTE(attr_adcGain_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_adcGainStr_read,MAX_STRING_LENGTH);
    CREATE_SCALAR_ATTRIBUTE(attr_adcRate_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_adcRateStr_read,MAX_STRING_LENGTH);
    CREATE_SCALAR_ATTRIBUTE(attr_electronicShutterMode_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_electronicShutterModeStr_read, MAX_STRING_LENGTH);
    CREATE_SCALAR_ATTRIBUTE(attr_temperatureSP_read);
    CREATE_SCALAR_ATTRIBUTE(attr_temperature_read);
    CREATE_SCALAR_ATTRIBUTE(attr_cooler_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_coolingStatus_read,MAX_STRING_LENGTH);

    //By default INIT, need to ensure that all objets are OK before set the device to STANDBY
    set_state(Tango::INIT);
    m_is_device_initialized = false;
    m_status_message.str("");

    try
    {
        //- get the main object used to pilot the lima framework
        //in fact LimaDetector is create the singleton control objet
        //so this call, will only return existing object, no need to give it the ip !!
        m_ct = ControlFactory::instance().get_control("Andor3");

        //- get interface to specific camera
        m_hw = dynamic_cast<lima::Andor3::Interface*> (m_ct->hwInterface());
        if (m_hw == 0)
        {
            INFO_STREAM << "Initialization Failed : Unable to get the interface of camera plugin !" << std::endl;
            m_status_message << "Initialization Failed : Unable to get the interface of camera plugin !" << std::endl;
            m_is_device_initialized = false;
            set_state(Tango::FAULT);
            return;
        }

        //- get camera to specific detector
		m_camera = &(m_hw->getCamera());
		if(m_camera == 0)
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the camera of plugin !"<<endl;
			m_status_message <<"Initialization Failed : Unable to get the camera object !"<< endl;
			m_is_device_initialized = false;
			set_state(Tango::FAULT);
			return;
		}

    }
    catch (Exception& e)
    {
        INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << std::endl;
        m_status_message << "Initialization Failed : " << e.getErrMsg() << std::endl;
        m_is_device_initialized = false;
        set_state(Tango::FAULT);
        return;
    }
    catch (...)
    {
        INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
        m_status_message << "Initialization Failed : UNKNOWN" << endl;
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
    m_is_device_initialized = true;
    set_state(Tango::STANDBY);
    this->dev_state();
}


//+----------------------------------------------------------------------------
//
// method : 		Andor3::get_device_property()
//
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void Andor3::get_device_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read device properties from database.(Automatic code generation)
	//------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("BitFlowPath"));
	dev_prop.push_back(Tango::DbDatum("CameraNumber"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	Andor3Class	*ds_class =
		(static_cast<Andor3Class *>(get_device_class()));
	int	i = -1;

	//	Try to initialize BitFlowPath from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  bitFlowPath;
	else {
		//	Try to initialize BitFlowPath from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  bitFlowPath;
	}
	//	And try to extract BitFlowPath value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  bitFlowPath;

	//	Try to initialize CameraNumber from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  cameraNumber;
	else {
		//	Try to initialize CameraNumber from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  cameraNumber;
	}
	//	And try to extract CameraNumber value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  cameraNumber;



	//	End of Automatic code generation
	//------------------------------------------------------------------

    create_property_if_empty(dev_prop,"/no/path/defined","BitFlowPath");
    create_property_if_empty(dev_prop,"0","CameraNumber");

}
//+----------------------------------------------------------------------------
//
// method : 		Andor3::always_executed_hook()
//
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void Andor3::always_executed_hook()
{
    DEBUG_STREAM << "Andor3::always_executed_hook() entering... " << endl;
    try
    {
        m_status_message.str("");
        //- get the singleton control objet used to pilot the lima framework
        m_ct = ControlFactory::instance().get_control("Andor3");

        //- get interface to specific detector
        if (m_ct != 0)
            m_hw = dynamic_cast<lima::Andor3::Interface*> (m_ct->hwInterface());

        //- get camera to specific detector
		m_camera = &(m_hw->getCamera());

        this->dev_state();

    }
    catch (Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
    catch (...)
    {
        ERROR_STREAM << "Initialization Failed : UNKNOWN" << endl;
        m_status_message << "Initialization Failed : UNKNOWN" << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }

}
//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_attr_hardware
//
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void Andor3::read_attr_hardware(vector<long> &attr_list)
{
	DEBUG_STREAM << "Andor3::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
	//	Add your own code here
}
//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_adcGainStr
//
// description : 	Extract real attribute values for adcGainStr acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_adcGainStr(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_adcGainStr(Tango::Attribute &attr) entering... "<< endl;

	std::string    the_adc_gain_str;
        m_hw->getAdcGainString(the_adc_gain_str);
        try {
          strcpy(*attr_adcGainStr_read, the_adc_gain_str.c_str());
          attr.set_value(attr_adcGainStr_read);
        }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_adcGainStr"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_adcGainStr"));
    }

}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_adcRateStr
//
// description : 	Extract real attribute values for adcRateStr acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_adcRateStr(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_adcRateStr(Tango::Attribute &attr) entering... "<< endl;

	std::string    the_adc_rate_str;
	m_hw->getAdcRateString(the_adc_rate_str);
	try {
	  strcpy(*attr_adcRateStr_read, the_adc_rate_str.c_str());
	  attr.set_value(attr_adcRateStr_read);
	}
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_adcRateStr"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_adcRateStr"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_electronicShutterModeStr
//
// description : 	Extract real attribute values for electronicShutterModeStr acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_electronicShutterModeStr(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_electronicShutterModeStr(Tango::Attribute &attr) entering... "<< endl;

	std::string    the_electronic_shutter_str;
	m_hw->getElectronicShutterModeString(the_electronic_shutter_str);
	try {
	  strcpy(*attr_electronicShutterModeStr_read, the_electronic_shutter_str.c_str());
	  attr.set_value(attr_electronicShutterModeStr_read);
	}
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_electronicShutterModeStr"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_electronicShutterModeStr"));
    }
}


//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_adcGain
//
// description : 	Extract real attribute values for adcGain acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_adcGain(Tango::Attribute &attr)
{
#warning proper conversion/cast (also shutter and rate)
	DEBUG_STREAM << "Andor3::read_adcGain(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        m_hw->getAdcGain((lima::Andor3::Camera::A3_Gain&)*attr_adcGain_read);
        attr.set_value(attr_adcGain_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_adcGain"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_adcGain"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::write_adcGain
//
// description : 	Write adcGain attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Andor3::write_adcGain(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Andor3::write_adcGain(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_adcGain_write);
	lima::Andor3::Camera::A3_Gain the_gain = static_cast<lima::Andor3::Camera::A3_Gain>(attr_adcGain_write);
        m_hw->setAdcGain(the_gain);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::write_adcGain"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("Andor3::write_adcGain"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_adcRate
//
// description : 	Extract real attribute values for adcRate acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_adcRate(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_adcRate(Tango::Attribute &attr) entering... "<< endl;

    try
    {
		m_hw->getAdcRate((lima::Andor3::Camera::A3_ReadOutRate&)*attr_adcRate_read);
        attr.set_value(attr_adcRate_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_adcRate"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_adcRate"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::write_adcRate
//
// description : 	Write adcRate attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Andor3::write_adcRate(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Andor3::write_adcRate(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_adcRate_write);
	lima::Andor3::Camera::A3_ReadOutRate the_rate = static_cast<lima::Andor3::Camera::A3_ReadOutRate>(attr_adcRate_write);
        m_hw->setAdcRate(the_rate);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::write_adcRate"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("Andor3::write_adcRate"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_electronicShutterMode
//
// description : 	Extract real attribute values for electronicShutterMode acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_electronicShutterMode(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_electronicShutterMode(Tango::Attribute &attr) entering... "<< endl;

    try
    {
		m_hw->getElectronicShutterMode((lima::Andor3::Camera::A3_ShutterMode&)*attr_electronicShutterMode_read);
        attr.set_value(attr_electronicShutterMode_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_electronicShutterMode"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_electronicShutterMode"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::write_electronicShutterMode
//
// description : 	Write electronicShutterMode attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Andor3::write_electronicShutterMode(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Andor3::write_electronicShutterMode(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_electronicShutterMode_write);
	lima::Andor3::Camera::A3_ShutterMode   the_sm = static_cast<lima::Andor3::Camera::A3_ShutterMode>(attr_electronicShutterMode_write);
        m_hw->setElectronicShutterMode(the_sm);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::write_electronicShutterMode"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("Andor3::write_electronicShutterMode"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_temperatureSP
//
// description : 	Extract real attribute values for temperatureSP acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_temperatureSP(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_temperatureSP(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        double temperature_sp = 0;
		m_camera->getTemperatureSP(temperature_sp);
        *attr_temperatureSP_read = temperature_sp;
        attr.set_value(attr_temperatureSP_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_temperatureSP"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_temperatureSP"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::write_temperatureSP
//
// description : 	Write temperatureSP attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Andor3::write_temperatureSP(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Andor3::write_temperatureSP(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_temperatureSP_write);
        m_camera->setTemperatureSP(attr_temperatureSP_write);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::write_temperatureSP"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("Andor3::write_temperatureSP"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_temperature
//
// description : 	Extract real attribute values for temperature acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_temperature(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_temperature(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        double temperature = 0;
		m_camera->getTemperature(temperature);
        *attr_temperature_read = temperature;
        attr.set_value(attr_temperature_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_temperature"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_temperature"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_cooler
//
// description : 	Extract real attribute values for cooler acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_cooler(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_cooler(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        bool cooler = false;
		m_camera->getCooler(cooler);
        *attr_cooler_read = cooler;
        attr.set_value(attr_cooler_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_cooler"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_cooler"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::write_cooler
//
// description : 	Write cooler attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Andor3::write_cooler(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Andor3::write_cooler(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_cooler_write);
        m_camera->setCooler(attr_cooler_write);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::write_cooler"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("Andor3::write_cooler"));
    }

}

//+----------------------------------------------------------------------------
//
// method : 		Andor3::read_coolingStatus
//
// description : 	Extract real attribute values for coolingStatus acquisition result.
//
//-----------------------------------------------------------------------------
void Andor3::read_coolingStatus(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Andor3::read_coolingStatus(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        std::string cooling_status;
		m_camera->getCoolingStatus(cooling_status);

        strcpy(*attr_coolingStatus_read, cooling_status.c_str());

        attr.set_value(attr_coolingStatus_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("Andor3::read_coolingStatus"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("Andor3::read_coolingStatus"));
    }
}


//+------------------------------------------------------------------
/**
 *	method:	Andor3::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState Andor3::dev_state()
{
	Tango::DevState	argout = DeviceImpl::dev_state();
	DEBUG_STREAM << "Andor3::dev_state(): entering... !" << endl;

	//	Add your own code to control device here

    stringstream DeviceStatus;
    DeviceStatus << "";
    Tango::DevState DeviceState = Tango::STANDBY;
    if (!m_is_device_initialized)
    {
        DeviceState = Tango::FAULT;
        DeviceStatus << m_status_message.str();
    }
    else
    {
        //state&status are retrieved from specific device
        DeviceState = ControlFactory::instance().get_state();
        DeviceStatus << ControlFactory::instance().get_status();
    }

    set_state(DeviceState);
    set_status(DeviceStatus.str());

	argout = DeviceState;
	return argout;
}

/*-------------------------------------------------------------------------
//       Andor3::create_property_if_empty
/-------------------------------------------------------------------------*/
template <class T>
void Andor3::create_property_if_empty(Tango::DbData& dev_prop,T value,string property_name)
{
    int iPropertyIndex = find_index_from_property_name(dev_prop,property_name);
    if (iPropertyIndex == -1) return;
    if (dev_prop[iPropertyIndex].is_empty())
    {
        Tango::DbDatum current_value(dev_prop[iPropertyIndex].name);
        current_value << value;
        Tango::DbData db_data;
        db_data.push_back(current_value);

        try
        {
            get_db_device()->put_property(db_data);
        }
        catch(Tango::DevFailed &df)
        {
            string message= "Error in storing " + property_name + " in Configuration DataBase ";
            LOG_ERROR((message));
            ERROR_STREAM<<df<<endl;
            //- rethrow exception
            Tango::Except::re_throw_exception(df,
                        static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                        static_cast<const char*> (string(df.errors[0].desc).c_str()),
                        static_cast<const char*> ("Andor3::create_property_if_empty"));
        }
    }
}


/*-------------------------------------------------------------------------
//       Andor3::find_index_from_property_name
/-------------------------------------------------------------------------*/
int Andor3::find_index_from_property_name(Tango::DbData& dev_prop, string property_name)
{
    size_t iNbProperties = dev_prop.size();
    unsigned int i;
    for (i=0;i<iNbProperties;i++)
    {
        string sPropertyName(dev_prop[i].name);
        if (sPropertyName == property_name) return i;
    }
    if (i == iNbProperties) return -1;
    return i;
}




}	//	namespace
