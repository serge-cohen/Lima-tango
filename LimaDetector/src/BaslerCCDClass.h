//=============================================================================
//
// file :         BaslerCCDClass.h
//
// description :  Include for the BaslerCCDClass root class.
//                This class is the singleton class for
//                the BaslerCCD device class.
//                It contains all properties and methods which the 
//                BaslerCCD requires only once e.g. the commands.
//			
// project :      TANGO Device Server
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
// copyleft :     European Synchrotron Radiation Facility
//                BP 220, Grenoble 38043
//                FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifdef WIN32
#include "tango.h"
#endif

#ifndef _BASLERCCDCLASS_H
#define _BASLERCCDCLASS_H

#include <BaslerCCD.h>

#ifndef WIN32
#include "tango.h"
#endif

namespace BaslerCCD_ns
{//=====================================
//	Define classes for attributes
//=====================================
class autoGainAttrib: public Tango::Attr
{
public:
	autoGainAttrib():Attr("autoGain", Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~autoGainAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_autoGain(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<BaslerCCD *>(dev))->write_autoGain(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_autoGain_allowed(ty);}
};

class gainAttrib: public Tango::Attr
{
public:
	gainAttrib():Attr("gain", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~gainAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_gain(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<BaslerCCD *>(dev))->write_gain(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_gain_allowed(ty);}
};

class temperatureAttrib: public Tango::Attr
{
public:
	temperatureAttrib():Attr("temperature", Tango::DEV_DOUBLE, Tango::READ) {};
	~temperatureAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_temperature(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_temperature_allowed(ty);}
};

class frameRateAttrib: public Tango::Attr
{
public:
	frameRateAttrib():Attr("frameRate", Tango::DEV_DOUBLE, Tango::READ) {};
	~frameRateAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_frameRate(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_frameRate_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
//
// The BaslerCCDClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	BaslerCCDClass : public Tango::DeviceClass
{
public:
//	properties member data

//	add your own data members here
//------------------------------------

public:
	Tango::DbData	cl_prop;
	Tango::DbData	cl_def_prop;
	Tango::DbData	dev_def_prop;

//	Method prototypes
	static BaslerCCDClass *init(const char *);
	static BaslerCCDClass *instance();
	~BaslerCCDClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	BaslerCCDClass(string &);
	static BaslerCCDClass *_instance;
	void command_factory();
	void get_class_property();
	void attribute_factory(vector<Tango::Attr *> &);
	void write_class_property();
	void set_default_property();
	string get_cvstag();
	string get_cvsroot();

private:
	void device_factory(const Tango::DevVarStringArray *);
};


}	//	namespace BaslerCCD_ns

#endif // _BASLERCCDCLASS_H
