static const char *ClassId    = "$Id:  $";
static const char *TagName    = "$Name:  $";
static const char *CvsPath    = "$Source:  $";
static const char *SvnPath    = "$HeadURL: $";
static const char *HttpServer = "http://www.esrf.fr/computing/cs/tango/tango_doc/ds_doc/";
//+=============================================================================
//
// file :        Andor3Class.cpp
//
// description : C++ source for the Andor3Class. A singleton
//               class derived from DeviceClass. It implements the
//               command list and all properties and methods required
//               by the Andor3 once per process.
//
// project :     TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
//
// $Log:  $
//
// copyleft :   European Synchrotron Radiation Facility
//              BP 220, Grenoble 38043
//              FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================


#include <tango.h>

#include <Andor3.h>
#include <Andor3Class.h>


//+----------------------------------------------------------------------------
/**
 *	Create Andor3Class singleton and return it in a C function for Python usage
 */
//+----------------------------------------------------------------------------
extern "C" {
#ifdef WIN32

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_Andor3_class(const char *name) {
		return Andor3_ns::Andor3Class::init(name);
	}
}


namespace Andor3_ns
{


//
//----------------------------------------------------------------
//	Initialize pointer for singleton pattern
//----------------------------------------------------------------
//
Andor3Class *Andor3Class::_instance = NULL;

//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::Andor3Class(string &s)
// 
// description : 	constructor for the Andor3Class
//
// in : - s : The class name
//
//-----------------------------------------------------------------------------
Andor3Class::Andor3Class(string &s):DeviceClass(s)
{

	cout2 << "Entering Andor3Class constructor" << endl;
	set_default_property();
	get_class_property();
	write_class_property();
	
	cout2 << "Leaving Andor3Class constructor" << endl;

}
//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::~Andor3Class()
// 
// description : 	destructor for the Andor3Class
//
//-----------------------------------------------------------------------------
Andor3Class::~Andor3Class()
{
	_instance = NULL;
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::instance
// 
// description : 	Create the object if not already done. Otherwise, just
//			return a pointer to the object
//
// in : - name : The class name
//
//-----------------------------------------------------------------------------
Andor3Class *Andor3Class::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new Andor3Class(s);
		}
		catch (bad_alloc)
		{
			throw;
		}		
	}		
	return _instance;
}

Andor3Class *Andor3Class::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::command_factory
// 
// description : 	Create the command object(s) and store them in the 
//			command list
//
//-----------------------------------------------------------------------------
void Andor3Class::command_factory()
{

	//	add polling if any
	for (unsigned int i=0 ; i<command_list.size(); i++)
	{
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::get_class_property
// 
// description : 	Get the class property for specified name.
//
// in :		string	name : The property name
//
//+----------------------------------------------------------------------------
Tango::DbDatum Andor3Class::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::get_default_device_property()
// 
// description : 	Return the default value for device property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum Andor3Class::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::get_default_class_property()
// 
// description : 	Return the default value for class property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum Andor3Class::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::device_factory
// 
// description : 	Create the device object(s) and store them in the 
//			device list
//
// in :		Tango::DevVarStringArray *devlist_ptr : The device name list
//
//-----------------------------------------------------------------------------
void Andor3Class::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{

	//	Create all devices.(Automatic code generation)
	//-------------------------------------------------------------
	for (unsigned long i=0 ; i < devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
						
		// Create devices and add it into the device list
		//----------------------------------------------------
		device_list.push_back(new Andor3(this, (*devlist_ptr)[i]));							 

		// Export device to the outside world
		// Check before if database used.
		//---------------------------------------------
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(device_list.back());
		else
			export_device(device_list.back(), (*devlist_ptr)[i]);
	}
	//	End of Automatic code generation
	//-------------------------------------------------------------

}
//+----------------------------------------------------------------------------
//	Method: Andor3Class::attribute_factory(vector<Tango::Attr *> &att_list)
//-----------------------------------------------------------------------------
void Andor3Class::attribute_factory(vector<Tango::Attr *> &att_list)
{
	//	Attribute : adcGain
	adcGainAttrib	*adc_gain = new adcGainAttrib();
	Tango::UserDefaultAttrProp	adc_gain_prop;
	adc_gain_prop.set_label("ADC Gain");
	adc_gain_prop.set_unit(" ");
	adc_gain_prop.set_max_value("7");
	adc_gain_prop.set_min_value("0");
	adc_gain_prop.set_description("ADC Gain:\nGain1 = 0, Gain2 = 1, Gain3 = 2, Gain4 = 3, Gain1_Gain3 = 4, Gain1_Gain4 = 5, Gain2_Gain3 = 6, Gain2_Gain4 = 7");
	adc_gain->set_default_properties(adc_gain_prop);
	adc_gain->set_memorized();
	adc_gain->set_memorized_init(true);
	att_list.push_back(adc_gain);

	//	Attribute : adcGainStr
	adcGainStrAttrib	*adc_gain_str = new adcGainStrAttrib();
	Tango::UserDefaultAttrProp	adc_gain_str_prop;
	adc_gain_str_prop.set_label("ADC Gain Str");
	adc_gain_str_prop.set_unit(" ");
	adc_gain_str_prop.set_max_value("7");
	adc_gain_str_prop.set_min_value("0");
	adc_gain_str_prop.set_description("ADC Gain Str");
	adc_gain_str->set_default_properties(adc_gain_str_prop);
	att_list.push_back(adc_gain_str);

	//	Attribute : adcRate
	adcRateAttrib	*adc_rate = new adcRateAttrib();
	Tango::UserDefaultAttrProp	adc_rate_prop;
	adc_rate_prop.set_label("ADC Rate");
	adc_rate_prop.set_unit(" ");
	adc_rate_prop.set_max_value("3");
	adc_rate_prop.set_min_value("0");
	adc_rate_prop.set_description("ADC Rate: (Read Out Rate)\nMHz10 = 0, MHz100 = 1, MHz200 = 2, MHz280 = 3");
	adc_rate->set_default_properties(adc_rate_prop);
	adc_rate->set_memorized();
	adc_rate->set_memorized_init(true);
	att_list.push_back(adc_rate);

	//	Attribute : adcRateStr
	adcRateStrAttrib	*adc_rate_str = new adcRateStrAttrib();
	Tango::UserDefaultAttrProp	adc_rate_str_prop;
	adc_rate_str_prop.set_label("Adc Rate Str");
	adc_rate_str_prop.set_description("Adc Rate Str: Adc Rate in string format");
	adc_rate_str->set_default_properties(adc_rate_str_prop);
	att_list.push_back(adc_rate_str);

	//	Attribute : electronicShutterMode
	electronicShutterModeAttrib	*electronic_shutter_mode = new electronicShutterModeAttrib();
	Tango::UserDefaultAttrProp	electronic_shutter_mode_prop;
	electronic_shutter_mode_prop.set_label("Electronic Shutter Mode");
	electronic_shutter_mode_prop.set_unit(" ");
	electronic_shutter_mode_prop.set_max_value("3");
	electronic_shutter_mode_prop.set_min_value("0");
	electronic_shutter_mode_prop.set_description("Electronic Shutter Mode:\nRolling = 0, Global = 1");
	electronic_shutter_mode->set_default_properties(electronic_shutter_mode_prop);
	electronic_shutter_mode->set_memorized();
	electronic_shutter_mode->set_memorized_init(true);
	att_list.push_back(electronic_shutter_mode);

	//	Attribute : temperatureSP
	temperatureSPAttrib	*temperature_sp = new temperatureSPAttrib();
	Tango::UserDefaultAttrProp	temperature_sp_prop;
	temperature_sp_prop.set_label("Temperature SP");
	temperature_sp_prop.set_unit("�C");
	temperature_sp_prop.set_description("Temperature SP");
	temperature_sp->set_default_properties(temperature_sp_prop);
	att_list.push_back(temperature_sp);

	//	Attribute : temperature
	temperatureAttrib	*temperature = new temperatureAttrib();
	Tango::UserDefaultAttrProp	temperature_prop;
	temperature_prop.set_label("Temperature");
	temperature_prop.set_unit("�C");
	temperature_prop.set_description("Temperature");
	temperature->set_default_properties(temperature_prop);
	att_list.push_back(temperature);

	//	Attribute : cooler
	coolerAttrib	*cooler = new coolerAttrib();
	Tango::UserDefaultAttrProp	cooler_prop;
	cooler_prop.set_label("Cooler");
	cooler_prop.set_unit(" ");
	cooler_prop.set_description("Cooler : ON/OFF");
	cooler->set_default_properties(cooler_prop);
	//cooler->set_memorized();
	//cooler->set_memorized_init(true);
	att_list.push_back(cooler);

	//	Attribute : coolingStatus
	coolingStatusAttrib	*cooling_status = new coolingStatusAttrib();
	Tango::UserDefaultAttrProp	cooling_status_prop;
	cooling_status_prop.set_label("Cooling Status");
	cooling_status->set_default_properties(cooling_status_prop);
	att_list.push_back(cooling_status);

	//	End of Automatic code generation
	//-------------------------------------------------------------
}


//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::get_class_property()
// 
// description : 	Read the class properties from database.
//
//-----------------------------------------------------------------------------
void Andor3Class::get_class_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read class properties from database.(Automatic code generation)
	//------------------------------------------------------------------

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_class()->get_property(cl_prop);
	Tango::DbDatum	def_prop;
	int	i = -1;


	//	End of Automatic code generation
	//------------------------------------------------------------------

}

//+----------------------------------------------------------------------------
//
// method : 	Andor3Class::set_default_property
// 
// description: Set default property (class and device) for wizard.
//              For each property, add to wizard property name and description
//              If default value has been set, add it to wizard property and
//              store it in a DbDatum.
//
//-----------------------------------------------------------------------------
void Andor3Class::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;

	vector<string>	vect_data;
	//	Set Default Class Properties
	//	Set Default Device Properties
	prop_name = "BitFlowPath";
	prop_desc = "Path of the bitflow";
	prop_def  = "/no/path/defined";
	vect_data.clear();
	vect_data.push_back("/no/path/defined");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "CameraNumber";
	prop_desc = "Camera Number for the Andor driver (ie: DeviceIndex)";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

}
//+----------------------------------------------------------------------------
//
// method : 		Andor3Class::write_class_property
// 
// description : 	Set class description as property in database
//
//-----------------------------------------------------------------------------
void Andor3Class::write_class_property()
{
	//	First time, check if database used
	//--------------------------------------------
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("Specific class for Andor3 detector");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("This class is the specific Lima device for the Andor3 cameras (Neo,...)");
	description << str_desc;
	data.push_back(description);
		
	//	put cvs or svn location
	string	filename(classname);
	filename += "Class.cpp";
	
	// Create a string with the class ID to
	// get the string into the binary
	string	class_id(ClassId);
	
	// check for cvs information
	string	src_path(CvsPath);
	start = src_path.find("/");
	if (start!=string::npos)
	{
		end   = src_path.find(filename);
		if (end>start)
		{
			string	strloc = src_path.substr(start, end-start);
			//	Check if specific repository
			start = strloc.find("/cvsroot/");
			if (start!=string::npos && start>0)
			{
				string	repository = strloc.substr(0, start);
				if (repository.find("/segfs/")!=string::npos)
					strloc = "ESRF:" + strloc.substr(start, strloc.length()-start);
			}
			Tango::DbDatum	cvs_loc("cvs_location");
			cvs_loc << strloc;
			data.push_back(cvs_loc);
		}
	}
	// check for svn information
	else
	{
		string	src_path(SvnPath);
		start = src_path.find("://");
		if (start!=string::npos)
		{
			end = src_path.find(filename);
			if (end>start)
			{
				header = "$HeadURL: ";
				start = header.length();
				string	strloc = src_path.substr(start, (end-start));
				
				Tango::DbDatum	svn_loc("svn_location");
				svn_loc << strloc;
				data.push_back(svn_loc);
			}
		}
	}

	//	Get CVS or SVN revision tag
	
	// CVS tag
	string	tagname(TagName);
	header = "$Name: ";
	start = header.length();
	string	endstr(" $");
	
	end   = tagname.find(endstr);
	if (end!=string::npos && end>start)
	{
		string	strtag = tagname.substr(start, end-start);
		Tango::DbDatum	cvs_tag("cvs_tag");
		cvs_tag << strtag;
		data.push_back(cvs_tag);
	}
	
	// SVN tag
	string	svnpath(SvnPath);
	header = "$HeadURL: ";
	start = header.length();
	
	end   = svnpath.find(endstr);
	if (end!=string::npos && end>start)
	{
		string	strloc = svnpath.substr(start, end-start);
		
		string tagstr ("/tags/");
		start = strloc.find(tagstr);
		if ( start!=string::npos )
		{
			start = start + tagstr.length();
			end   = strloc.find(filename);
			string	strtag = strloc.substr(start, end-start-1);
			
			Tango::DbDatum	svn_tag("svn_tag");
			svn_tag << strtag;
			data.push_back(svn_tag);
		}
	}

	//	Get URL location
	string	httpServ(HttpServer);
	if (httpServ.length()>0)
	{
		Tango::DbDatum	db_doc_url("doc_url");
		db_doc_url << httpServ;
		data.push_back(db_doc_url);
	}

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("Device_4Impl");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	//--------------------------------------------
	get_db_class()->put_property(data);
}

}	// namespace
