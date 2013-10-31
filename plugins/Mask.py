############################################################################
# This file is part of LImA, a Library for Image Acquisition
#
# Copyright (C) : 2009-2011
# European Synchrotron Radiation Facility
# BP 220, Grenoble 38043
# FRANCE
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
############################################################################
import PyTango

from Lima import Core
from Utils import getDataFromFile,BasePostProcess

class MaskDeviceServer(BasePostProcess) :
    MASK_TASK_NAME = 'MaskTask'

    def __init__(self,cl,name) :
        self.__maskTask = None
        self.__maskImage = Core.Processlib.Data()
        
        self.__Type = {'STANDARD' : 0,
                       'DUMMY' : 1}

        BasePostProcess.__init__(self,cl,name)
        MaskDeviceServer.init_device(self)

    def set_state(self,state) :
	if(state == PyTango.DevState.OFF) :
	    if(self.__maskTask) :
		self.__maskTask = None
		ctControl = _control_ref()
		extOpt = ctControl.externalOperation()
		extOpt.delOp(self.MASK_TASK_NAME)
	elif(state == PyTango.DevState.ON) :
	    if not self.__maskTask:
                ctControl = _control_ref()
                extOpt = ctControl.externalOperation()
                self.__maskTask = extOpt.addOp(Core.MASK,
                                               self.MASK_TASK_NAME,
                                               self._runLevel)
                self.__maskTask.setMaskImage(self.__maskImage)
	PyTango.Device_4Impl.set_state(self,state)

    def setMaskImage(self,filepath) :
        self.__maskImage = getDataFromFile(filepath)
        if(self.__maskTask) :
            self.__maskTask.setMaskImage(self.__maskImage)

#------------------------------------------------------------------
#    getAttrStringValueList command:
#
#    Description: return a list of authorized values if any
#    argout: DevVarStringArray   
#------------------------------------------------------------------
    def getAttrStringValueList(self, attr_name):
        valueList = []
        dict_name = '_' + self.__class__.__name__ + '__' + ''.join([x.title() for x in attr_name.split('_')])
        d = getattr(self,dict_name,None)
        if d:
            valueList = d.keys()
        return valueList

    def write_type(self,attr) :
        data = attr.get_write_value()
        t = _getDictValue(self.__Type,data)
        self.__maskTask.setType(t)

    def read_type(self,attr) :
        t = self.__maskTask.getType()
        attr.set_value(_getDictKey(self.__Type,t))
        
def _getDictKey(dict, value):
    try:
        ind = dict.values().index(value)                            
    except ValueError:
        return None
    return dict.keys()[ind]

def _getDictValue(dict, key):
    try:
        value = dict[key.upper()]
    except KeyError:
        return None
    return value

class MaskDeviceServerClass(PyTango.DeviceClass) :
        #	 Class Properties
    class_property_list = {
	}


    #	 Device Properties
    device_property_list = {
	}


    #	 Command definitions
    cmd_list = {
        'setMaskImage':
        [[PyTango.DevString,"Full path of mask image file"],
         [PyTango.DevVoid,""]],
        'getAttrStringValueList':
        [[PyTango.DevString, "Attribute name"],
         [PyTango.DevVarStringArray, "Authorized String value list"]],
	'Start':
	[[PyTango.DevVoid,""],
	 [PyTango.DevVoid,""]],
	'Stop':
	[[PyTango.DevVoid,""],
	 [PyTango.DevVoid,""]],
	}


    #	 Attribute definitions
    attr_list = {
	'RunLevel':
	    [[PyTango.DevLong,
	    PyTango.SCALAR,
	    PyTango.READ_WRITE]],
        'type':
        [[PyTango.DevString,
          PyTango.SCALAR,
          PyTango.READ_WRITE]],
        }


#------------------------------------------------------------------
#    RoiCounterDeviceServerClass Constructor
#------------------------------------------------------------------
    def __init__(self, name):
	PyTango.DeviceClass.__init__(self, name)
	self.set_type(name);

_control_ref = None
def set_control_ref(control_class_ref) :
    global _control_ref
    _control_ref= control_class_ref

def get_tango_specific_class_n_device() :
   return MaskDeviceServerClass,MaskDeviceServer
