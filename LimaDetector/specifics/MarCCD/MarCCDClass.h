//=============================================================================
//
// file :         MarCCDClass.h
//
// description :  Include for the MarCCDClass root class.
//                This class is the singleton class for
//                the Pilatus device class.
//                It contains all properties and methods which the 
//                Pilatus requires only once e.g. the commands.
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

#ifndef _MarCCDCLASS_H
#define _MarCCDCLASS_H

#ifdef WIN32
#include "tango.h"
#endif

#include <MarCCD.h>

#ifndef WIN32
#include "tango.h"
#endif


namespace MarCCD_ns
{//=====================================
//	Define classes for attributes
//=====================================
class waitFileOnDiskTimeAttrib: public Tango::Attr
{
public:
	waitFileOnDiskTimeAttrib():Attr("waitFileOnDiskTime", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~waitFileOnDiskTimeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<MarCCD *>(dev))->read_waitFileOnDiskTime(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<MarCCD *>(dev))->write_waitFileOnDiskTime(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<MarCCD *>(dev))->is_waitFileOnDiskTime_allowed(ty);}
};

class imageIndexAttrib: public Tango::Attr
{
public:
	imageIndexAttrib():Attr("imageIndex", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~imageIndexAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<MarCCD *>(dev))->read_imageIndex(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<MarCCD *>(dev))->write_imageIndex(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<MarCCD *>(dev))->is_imageIndex_allowed(ty);}
};

class imageNameAttrib: public Tango::Attr
{
public:
	imageNameAttrib():Attr("imageName", Tango::DEV_STRING, Tango::READ_WRITE) {};
	~imageNameAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<MarCCD *>(dev))->read_imageName(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<MarCCD *>(dev))->write_imageName(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<MarCCD *>(dev))->is_imageName_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
class TakeBackgroundCmd : public Tango::Command
{
public:
	TakeBackgroundCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	TakeBackgroundCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~TakeBackgroundCmd() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<MarCCD *>(dev))->is_TakeBackground_allowed(any);}
};



//
// The MarCCDClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	MarCCDClass : public Tango::DeviceClass
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
	static MarCCDClass *init(const char *);
	static MarCCDClass *instance();
	~MarCCDClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	MarCCDClass(string &);
	static MarCCDClass *_instance;
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


}	//	namespace MarCCD_ns

#endif // _MARCCDCLASS_H