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
#=============================================================================
#
# file :        LimaTacoCCDs.py
#
# description : Python source for the LimaTacoCCDs and its commands. 
#                The class is derived from Device. It represents the
#                CORBA servant object which will be accessed from the
#                network. All commands which can be executed on the
#         LimaTacoCCDs are implemented in this file.
#
# project :    TANGO Device Server
#
# copyleft :    European Synchrotron Radiation Facility
#        BP 220, Grenoble 38043
#        FRANCE
#
#=============================================================================
#        This file is generated by seb
#
#      (c) - BLISS - ESRF
#=============================================================================
#

import sys
import PyTango

from Lima import Core

import processlib

import numpy

DevCcdBase			= 0xc180000

# CCD States
DevCcdReady			= DevCcdBase + 1
DevCcdAcquiring			= DevCcdBase + 2
DevCcdFault			= DevCcdBase + 3
DevCcdSaving			= DevCcdBase + 4
DevCcdNotYetInitialised		= DevCcdBase + 5
DevCcdInitializing		= DevCcdBase + 6
DevCcdReadout			= DevCcdBase + 7
DevCcdCorrecting		= DevCcdBase + 8
DevCcdBusy			= DevCcdBase + 9
DevCcdAborting			= DevCcdBase + 10
DevCcdNoRemote			= DevCcdBase + 11

# CCD Errors
DevErrCcdState			= DevCcdBase + 1
DevErrCcdController		= DevCcdBase + 2
DevErrCcdNotEnoughDisk		= DevCcdBase + 3
DevErrCcdNoDirPermission	= DevCcdBase + 4
DevErrCcdNoDirectory		= DevCcdBase + 5
DevErrCcdLongPath		= DevCcdBase + 6
DevErrCcdEmptyPath		= DevCcdBase + 7
DevErrCcdNotAccessible		= DevCcdBase + 8
DevErrCcdNoFilePermission	= DevCcdBase + 9
DevErrCcdFileExist		= DevCcdBase + 10
DevErrCcdCmdNotProc		= DevCcdBase + 11
DevErrCcdCameraModel		= DevCcdBase + 12
DevErrCcdProcessImage		= DevCcdBase + 13

#==================================================================
#   LimaTacoCCDs Class Description:
#
#      This is a device server for the LimaTacoCCDs cameras
#      and implementing the Taco ccd interface
#      for integrating it on the beamline.
#
#==================================================================
#    Device States Description:
#
#   DevState.ON :     ccd is ON, taking pictures
#   DevState.OFF :    ccd is OFF, ready to take pictures
#   DevState.FAULT :  ccd is in FAULT, cannot take pictures
#==================================================================

class LimaTacoCCDs(PyTango.Device_4Impl):

    Core.DEB_CLASS(Core.DebModApplication, 'LimaTacoCCDs')

#--------- Add you global variables here --------------------------
    LiveDisplay  = 1
    StripeConcat = 4
    AutoSave     = 8
    AutoHeader   = 16
    
#------------------------------------------------------------------
#    Device constructor
#------------------------------------------------------------------
    def __init__(self,cl, name):
        PyTango.Device_4Impl.__init__(self,cl,name)
        self.init_device()
        
        self.__bpm_mgr  = processlib.Tasks.BpmManager()
        self.__bpm_task = processlib.Tasks.BpmTask(self.__bpm_mgr)
        
	self.__key_header_delimiter = '='
	self.__entry_header_delimiter = '\n'
        self.__image_number_header_delimiter = ';'
#------------------------------------------------------------------
#    Device destructor
#------------------------------------------------------------------
    def delete_device(self):
        pass

#------------------------------------------------------------------
#    Device initialization
#------------------------------------------------------------------
    def init_device(self):
        self.set_state(PyTango.DevState.ON)
        self.get_device_properties(self.get_device_class())
        try:
            self.ManualAsynchronousWrite = int(self.ManualAsynchronousWrite)
        except:
            self.ManualAsynchronousWrite = 0

#==================================================================
#
#    LimaTacoCCDs read/write attribute methods
#
#==================================================================
#------------------------------------------------------------------
#    Read Attribute Hardware
#------------------------------------------------------------------
    def read_attr_hardware(self,data):
        pass


#==================================================================
#
#    LimaTacoCCDs command methods
#
#==================================================================

#------------------------------------------------------------------
#    TacoState command:
#
#    Description: 
#    argout: DevLong taco state
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def TacoState(self):
        state = self.State()
        if state == PyTango.DevState.OFF:
            return DevCcdReady
        elif state == PyTango.DevState.ON:
            return DevCcdAcquiring
        else:
            return DevCcdFault

#------------------------------------------------------------------
#    State command:
#
#    Description: 
#    argout: DevLong taco state
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def State(self):
        control = _control_ref()
        state = control.getStatus()
        if state.AcquisitionStatus == Core.AcqReady:
            return PyTango.DevState.OFF
        elif state.AcquisitionStatus == Core.AcqRunning:
            return PyTango.DevState.ON
        else:
            return PyTango.DevState.FAULT

#------------------------------------------------------------------
#    DevCcdStart command:
#
#    Description: 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdStart(self):
        control = _control_ref()
        control.prepareAcq()
        control.startAcq()


#------------------------------------------------------------------
#    DevCcdStop command:
#
#    Description: 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdStop(self):
        control = _control_ref()
        control.stopAcq()

#------------------------------------------------------------------
#    DevCcdRead command:
#
#    Description: 
#    argin:    DevVarLongArray 
#    argout: DevVarCharArray 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdRead(self, argin):
        control = _control_ref()
        self._data_cache = control.ReadImage(int(argin[0]))
	dataflat = self._data_cache.buffer.ravel()
	dataflat.dtype=numpy.uint8
	return dataflat


#------------------------------------------------------------------
#    DevCcdReadJpeg command:
#
#    Description: 
#    argin:    DevShort    jpeg compression
#    argout: DevVarCharArray jpeg compressed image
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdReadJpeg(self, argin):
        pass

#------------------------------------------------------------------
#    DevCcdWrite command:
#
#    Description: 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdWrite(self):
	self.DevCcdWriteFile(-1)

#------------------------------------------------------------------
#    DevCcdSetExposure command:
#
#    Description: 
#    argin:    DevFloat    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdSetExposure(self, exp_time):
        deb.Param('Setting exp. time: %s' % exp_time)

        control = _control_ref()
        acq = control.acquisition()
        
        trig_mode = acq.getTriggerMode()
        if exp_time == 0 and trig_mode == Core.ExtTrigSingle:
            acq.setTriggerMode(Core.ExtGate)
        elif exp_time > 0 and trig_mode == Core.ExtGate:
            acq.setTriggerMode(Core.ExtTrigSingle)
        if exp_time > 0. :
	    acq.setAcqExpoTime(exp_time)


#------------------------------------------------------------------
#    DevCcdGetExposure command:
#
#    Description: read ccd exposure
#         
#    argout: DevFloat    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetExposure(self):
        control = _control_ref()
        acq = control.acquisition()
        return acq.getAcqExpoTime()

#------------------------------------------------------------------
#    DevCcdSetRoI command:
#
#    Description: 
#    argin:    DevVarLongArray 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdSetRoI(self, argin):
        roi = Core.Roi(Core.Point(argin[0], argin[1]), Core.Point(argin[2], argin[3]))
        control = _control_ref()
        image = control.image()
        if roi == self.getMaxRoi() :
            roi = Core.Roi()
        image.setRoi(roi)
#------------------------------------------------------------------
#    DevCcdGetRoI command:
#
#    Description: get the region of interest coordinates
#         
#    argout: DevVarLongArray region of interest
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetRoI(self):
        control = _control_ref()
        image = control.image()
        roi = image.getRoi()
        if roi.isEmpty():
            roi = self.getMaxRoi()

        tl = roi.getTopLeft()
        br = roi.getBottomRight()
        return [tl.x, tl.y, br.x, br.y]
    
    @Core.DEB_MEMBER_FUNCT
    def getMaxRoi(self):
        control = _control_ref()
        ct_image = control.image()
        max_roi_size = ct_image.getMaxImageSize()
        max_roi_size /= Core.Point(ct_image.getBin())
        max_roi = Core.Roi(Core.Point(0,0),max_roi_size)
        return max_roi

#------------------------------------------------------------------
#    DevCcdSetFilePar command:
#
#    Description: 
#    argin:    DevVarStringArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdSetFilePar(self, par_arr):
        deb.Param('Setting file pars: %s' % par_arr)
        control = _control_ref()
        saving = control.saving()
        pars = saving.getParameters()
        pars.directory  = par_arr[0]
        pars.prefix     = par_arr[1]
        pars.suffix     = par_arr[2]
        pars.nextNumber = int(par_arr[3])
        index_format    = par_arr[4]
        if par_arr[5] in ['y', 'yes']:
            pars.overwritePolicy = Core.CtSaving.Overwrite
        else:
            pars.overwritePolicy = Core.CtSaving.Abort
        if pars.suffix.lower()[-4:] == '.edf':
            pars.fileFormat = Core.CtSaving.EDF
        elif pars.suffix.lower()[-4:] == '.cbf':
            pars.fileFormat = Core.CtSaving.CBFFormat
        else:
            pars.fileFormat = Core.CtSaving.RAW
        saving.setParameters(pars)

#------------------------------------------------------------------
#    DevCcdGetFilePar command:
#
#    Description: 
#    argout: DevVarStringArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetFilePar(self):
        control = _control_ref()
        saving = control.saving()
        pars = saving.getParameters()
        overwrite = (pars.overwritePolicy == Core.CtSaving.Overwrite)
        over_str = (overwrite and 'yes') or 'no'
        index_format = '%04d'
        arr = [pars.directory, pars.prefix, pars.suffix, pars.nextNumber,
               index_format, over_str]
        par_arr = map(str, arr)
        deb.Return('File pars: %s' % par_arr)
        return par_arr

#------------------------------------------------------------------
#    DevCcdHeader command:
#
#    Description: 
#    argout: DevVarStringArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdHeader(self, header_str):
        deb.Param('Setting file header: %s' % header_str)
        control = _control_ref()
        saving = control.saving()
        header_map = {}
        for line in header_str.split(self.__entry_header_delimiter) :
            token = line.split(self.__key_header_delimiter)
            key = token[0].strip()
            if not key:
                continue
            try:
	        val = '='.join(token[1:]).strip()
	    except ValueError:
		continue
            if val.endswith(';'):
                val = val[:-1]
            header_map[key] = val
        savingMode = saving.getSavingMode()
        if savingMode != Core.CtSaving.AutoHeader:
            saving.setCommonHeader(header_map)
        else:
            imageStatus = control.getImageStatus()
            NextImageSaved = imageStatus.LastImageSaved + 1
            saving.updateFrameHeader(NextImageSaved,header_map);

#------------------------------------------------------------------
#    DevCcdImageHeader command:
#
#    Description: 
#    argout: DevVarStringArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdImageHeader(self, headers_str):
        control = _control_ref()
        saving = control.saving()
        for image_header in headers_str:
            imageIdSepPos = image_header.find(self.__image_number_header_delimiter)
            imageId = int(image_header[:imageIdSepPos])
            header_str = image_header[imageIdSepPos+1:]
            deb.Param('Setting to image %d file header: %s' % (imageId,header_str))
            header_map = {}
            for line in header_str.split(self.__entry_header_delimiter) :
                token = line.split(self.__key_header_delimiter)
                key = token[0].strip()
                if not key:
                    continue
                try:
                    val = '='.join(token[1:]).strip()
                except ValueError:
                    continue
                if val.endswith(';'):
                    val = val[:-1]
                header_map[key] = val
            saving.updateFrameHeader(imageId,header_map)

    @Core.DEB_MEMBER_FUNCT
    def DevCcdHeaderDelimiter(self,delimiter) :
	deb.Param('Setting file header delimiter: %s' % delimiter)
	self.__key_header_delimiter = delimiter[0]
	self.__entry_header_delimiter = delimiter[1]
        if len(delimiter) > 2:
            self.__image_number_header_delimiter = delimiter[2]

#------------------------------------------------------------------
#    DevCcdDepth command:
#
#    Description: read depth of image in bits
#         
#    argout: DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdDepth(self):
        control = _control_ref()
        image = control.image()
        image_type = image.getImageType()
        return Core.FrameDim.getImageTypeDepth(image_type)

#------------------------------------------------------------------
#    DevCcdYSize command:
#
#    Description: get ccd y dimension in pixels
#         
#    argout: DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdYSize(self):
        #frame_dim = self.__getFrameDim()
        #size = frame_dim.getSize()
	control = _control_ref()
        image = control.image()
        size = image.getMaxImageSize()
        return size.getHeight()

#------------------------------------------------------------------
#    DevCcdXSize command:
#
#    Description: get ccd image x dimension in pixels
#         
#    argout: DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdXSize(self):
        #frame_dim = self.__getFrameDim()
        #size = frame_dim.getSize()
	control = _control_ref()
        image = control.image()
        size = image.getMaxImageSize()
        return size.getWidth()

#------------------------------------------------------------------
#    DevCcdReset command:
#
#    Description: reset ccd
#         
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdReset(self):
        control = _control_ref()
        control.reset()
        
#------------------------------------------------------------------
#    DevCcdSetMode command:
#
#    Description: 
#    argin:    DevLong mode
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdSetMode(self, mode):
        deb.Param('Setting mode: %s (0x%x)' % (mode, mode))
        live_display = (mode & self.LiveDisplay) != 0
        self.setLiveDisplay(live_display)
        auto_save = (mode & self.AutoSave) != 0
        auto_header = (mode & self.AutoHeader) != 0
        self.setAutosave(auto_save,auto_header)

#------------------------------------------------------------------
#    DevCcdGetMode command:
#
#    Description: 
#    argout: DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetMode(self):
        mode = 0
        if self.getLiveDisplay():
            mode |= self.LiveDisplay
        if self.getAutosave():
            mode |= self.AutoSave
        deb.Return('Getting mode: %s (0x%x)' % (mode, mode))
        return mode

    @Core.DEB_MEMBER_FUNCT
    def setAutosave(self, autosave_act,auto_header):
	control = _control_ref()
        saving = control.saving()
        deb.Param('Setting autosave active: %s' % autosave_act)
        if autosave_act:
            saving_mode = auto_header and Core.CtSaving.AutoHeader or Core.CtSaving.AutoFrame
        else:
            saving_mode = Core.CtSaving.Manual
        saving.setSavingMode(saving_mode)

    @Core.DEB_MEMBER_FUNCT
    def getAutosave(self):
	control = _control_ref()
        saving = control.saving()
        autosave_act = (saving.getSavingMode() == Core.CtSaving.AutoFrame)
        deb.Return('Getting autosave active: %s' % autosave_act)
        return autosave_act

    @Core.DEB_MEMBER_FUNCT
    def setLiveDisplay(self, livedisplay_act):
        deb.Param('Setting live display active: %s' % livedisplay_act)
	control = _control_ref()
	try:
	    display = control.display()
	    display.setNames('_ccd_ds_', 'limaccd_live')
	    display.setActive(livedisplay_act)
	except AttributeError:
	    pass

    @Core.DEB_MEMBER_FUNCT
    def getLiveDisplay(self):
	control = _control_ref()
	try:
	    display = control.display()
	    livedisplay_act = display.isActive()
	except AttributeError:
	    livedisplay_act = False
        deb.Return('Getting live display active: %s' % livedisplay_act)
        return livedisplay_act


#------------------------------------------------------------------
#    DevCcdWriteFile command:
#
#    Description: 
#    argin:    DevLong frame to write
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdWriteFile(self, frame_nb):
        synchronous = not self.ManualAsynchronousWrite
	control = _control_ref()
        saving = control.saving()
        saving.writeFrame(frame_nb,1,synchronous)

#------------------------------------------------------------------
#    DevCcdGetBin command:
#
#    Description: 
#    argout: DevVarLongArray 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetBin(self):
        control = _control_ref()
        image = control.image()
        bin = image.getBin()
        return [bin.getX(),bin.getY()]

#------------------------------------------------------------------
#    DevCcdSetBin command:
#
#    Description: 
#    argin:    DevVarLongArray 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdSetBin(self, argin):
        bin = Core.Bin(argin[1],argin[0])
        control = _control_ref()
        image = control.image()
        image.setBin(bin)

#------------------------------------------------------------------
#    DevCcdSetFrames command:
#
#    Description: 
#    argin:    DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdSetFrames(self, argin):
        control = _control_ref()
        acquisition = control.acquisition()
        acquisition.setAcqNbFrames(argin)
        
#------------------------------------------------------------------
#    DevCcdGetFrames command:
#
#    Description: 
#    argout: DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetFrames(self):
        control = _control_ref()
        acquisition = control.acquisition()
        return acquisition.getAcqNbFrames()

#------------------------------------------------------------------
#    DevCcdSetTrigger command:
#
#    Description: 
#    argin:    DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdSetTrigger(self, argin):
        control = _control_ref()
        acquisition = control.acquisition()

        triggerMode = None
        if argin == 0:
            triggerMode = Core.IntTrig
        elif argin == 1:
            triggerMode = Core.ExtTrigSingle
        elif argin == 2:
            triggerMode = Core.ExtTrigMult
        elif argin == 3:
	    triggerMode = Core.ExtStartStop
	elif argin == 4:
	    triggerMode = Core.ExtTrigReadout
        else:
            raise Core.Exception,'Invalid ext. trig: %s' % argin

        acquisition.setTriggerMode(triggerMode)
        
#------------------------------------------------------------------
#    DevCcdGetTrigger command:
#
#    Description: 
#    argin:    DevLong 
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetTrigger(self) :
        control = _control_ref()
        acquisition = control.acquisition()
        triggerMode = acquisition.getTriggerMode()
        if triggerMode == Core.IntTrig:
            returnValue = 0
        elif triggerMode == Core.ExtTrigSingle or triggerMode == Core.ExtGate:
            returnValue = 1
        elif triggerMode == Core.ExtTrigMult:
            returnValue = 2
	elif triggerMode == Core.ExtStartStop:
	    returnValue = 3
	elif triggerMode == Core.ExtTrigReadout:
	    returnValue = 4
        else:
            raise Core.Exception, 'Invalid trigger mode: %s' % triggerMode
        return returnValue
#------------------------------------------------------------------
#    DevReadValues command:
#
#    Description: 
#    argout: DevVarDoubleArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevReadValues(self):
        control = _control_ref()
        img_data = control.ReadImage(-1)
        self.__bpm_task.process(img_data)
        bpm_pars = self.__bpm_mgr.getResult(1)
        if bpm_pars.errorCode != self.__bpm_mgr.OK:
            raise Core.Exception,'Error calculating beam params: %d' % bpm_pars.errorCode

        nr_spots = 1
        auto_cal = -1
        exp_time = self.DevCcdGetExposure()
        if exp_time > 0:
            norm_intensity = bpm_pars.beam_intensity / exp_time
        else:
            norm_intensity = 0
        return [nr_spots,
                bpm_pars.beam_intensity,
                bpm_pars.beam_center_x,
                bpm_pars.beam_center_y,
                bpm_pars.beam_fwhm_x,
                bpm_pars.beam_fwhm_y,
                bpm_pars.AOI_max_x - bpm_pars.AOI_min_x,
                bpm_pars.AOI_max_y - bpm_pars.AOI_min_y,
                bpm_pars.max_pixel_value,
                bpm_pars.max_pixel_x,
                bpm_pars.max_pixel_y,
                bpm_pars.AOI_min_x,
                bpm_pars.AOI_min_y,
                bpm_pars.AOI_max_x,
                bpm_pars.AOI_max_y,
                bpm_pars.beam_center_x - bpm_pars.beam_fwhm_x / 2,
                bpm_pars.beam_center_y - bpm_pars.beam_fwhm_y / 2,
                bpm_pars.beam_center_x + bpm_pars.beam_fwhm_x / 2,
                bpm_pars.beam_center_y + bpm_pars.beam_fwhm_y / 2,
                norm_intensity,
                auto_cal]

#------------------------------------------------------------------
#    DevReadSigValues command:
#
#    Description: 
#    argout: DevVarDoubleArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevReadSigValues(self):
        exp_time = self.DevCcdGetExposure()
        threshold = 0
        calib_intensity = -1
        control = _control_ref()
        image = control.image()
        max_dim = image.getMaxImageSize()
        roi = self.DevCcdGetRoI()
        is_live = -1
        ccd_params = [exp_time,
                      threshold,
                      calib_intensity,
                      max_dim.getWidth(),
                      max_dim.getHeight(),
                      roi[0], roi[1], roi[2], roi[3],
                      is_live]
        ccd_params += self.DevReadValues()
        return ccd_params

#------------------------------------------------------------------
#    DevCcdGetLstErrMsg command:
#
#    Description: Get the last error message is mapped to the status of the Tango ccd device
#         
#    argout: DevString    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetLstErrMsg(self):
        return ''                       # not managed yet!


#------------------------------------------------------------------
#    DevCcdGetCurrent command:
#
#    Description: Get the current acquired frame number
#    argout: DevVarDoubleArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevCcdGetCurrent(self):
        control = _control_ref() 
        ct_status = control.getStatus()
        saving = control.saving()
        img_counters = ct_status.ImageCounters
        if saving.getSavingMode() == Core.CtSaving.AutoFrame:
            last_frame_nb = img_counters.LastImageSaved
        else:
            last_frame_nb = img_counters.LastImageAcquired
        nb_frames = last_frame_nb + 1
        deb.Return('Nb of frames: %s' % nb_frames)
        return nb_frames


#------------------------------------------------------------------
#    DevSetDebugFlags command:
#
#    Description: Get the current acquired frame number
#    argout: DevVarDoubleArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevSetDebugFlags(self, deb_flags):
        deb_flags &= 0xffffffff
        deb.Param('Setting debug flags: 0x%08x' % deb_flags)
        Core.DebParams.setTypeFlags((deb_flags   >> 16)  & 0xff)
        Core.DebParams.setModuleFlags((deb_flags >>  0)  & 0xffff)

        deb.Trace('FormatFlags: %s' % Core.DebParams.getFormatFlagsNameList())
        deb.Trace('TypeFlags:   %s' % Core.DebParams.getTypeFlagsNameList())
        deb.Trace('ModuleFlags: %s' % Core.DebParams.getModuleFlagsNameList())

#------------------------------------------------------------------
#    DevGetDebugFlags command:
#
#    Description: Get the current acquired frame number
#    argout: DevVarDoubleArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def DevGetDebugFlags(self):
        deb.Trace('FormatFlags: %s' % DebParams.getFormatFlagsNameList())
        deb.Trace('TypeFlags:   %s' % DebParams.getTypeFlagsNameList())
        deb.Trace('ModuleFlags: %s' % DebParams.getModuleFlagsNameList())

        deb_flags = (((DebParams.getTypeFlags()    & 0xff)   << 16) |
                     ((DebParams.getModuleFlags()  & 0xffff) <<  0))
        deb_flags &= 0xffffffff
        deb.Return('Getting debug flags: 0x%08x' % deb_flags)
        return deb_flags


#------------------------------------------------------------------
#    DevGetCurrent command:
#
#    Description: Get the current acquired frame number
#    argout: DevVarDoubleArray    
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def __getFrameDim(self) :
        control = _control_ref()
        interface = control.hwInterface()
        bufferCtrl = interface.getHwCtrlObj(Core.HwCap.Buffer)
        frame_dim = bufferCtrl.getFrameDim()
        return frame_dim
#==================================================================
#
#    LimaTacoCCDsClass class definition
#
#==================================================================
class LimaTacoCCDsClass(PyTango.DeviceClass):

    #    Class Properties
    class_property_list = {
        }


    #    Device Properties
    device_property_list = {
        'ManualAsynchronousWrite' :
        [PyTango.DevString,
         "Flag for manual writting",[0]],
        }


    #    Command definitions
    cmd_list = {
        'TacoState':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, "taco state"]],
        'DevCcdStart':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdStop':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdRead':
            [[PyTango.DevVarLongArray, ""],
            [PyTango.DevVarCharArray, ""]],
        'DevCcdReadJpeg':
            [[PyTango.DevShort, "jpeg compression"],
            [PyTango.DevVarCharArray, "jpeg compressed image"]],
        'DevCcdWrite':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdSetExposure':
            [[PyTango.DevFloat, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdGetExposure':
            [[PyTango.DevVoid, ""],
            [PyTango.DevFloat, ""]],
        'DevCcdSetRoI':
            [[PyTango.DevVarLongArray, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdSetFilePar':
            [[PyTango.DevVarStringArray, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdHeader':
            [[PyTango.DevString, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdImageHeader':
            [[PyTango.DevVarStringArray, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdHeaderDelimiter':
            [[PyTango.DevVarStringArray, ""],
	    [PyTango.DevVoid,""]],
        'DevCcdGetFilePar':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVarStringArray, ""]],
        'DevCcdDepth':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, ""]],
        'DevCcdYSize':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, ""]],
        'DevCcdXSize':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, ""]],
        'DevCcdReset':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdSetMode':
            [[PyTango.DevLong, "mode"],
            [PyTango.DevVoid, ""]],
        'DevCcdGetMode':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, ""]],
        'DevCcdWriteFile':
            [[PyTango.DevLong, "frame to write"],
            [PyTango.DevVoid, ""]],
        'DevCcdGetBin':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVarLongArray, ""]],
        'DevCcdSetBin':
            [[PyTango.DevVarLongArray, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdSetFrames':
            [[PyTango.DevLong, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdGetFrames':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, ""]],
        'DevCcdSetTrigger':
            [[PyTango.DevLong, ""],
            [PyTango.DevVoid, ""]],
        'DevCcdGetTrigger':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, ""]],
        'DevCcdGetRoI':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVarLongArray, "region of interest"]],
        'DevReadValues':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVarDoubleArray, ""]],
        'DevReadSigValues':
            [[PyTango.DevVoid, ""],
            [PyTango.DevVarDoubleArray, ""]],
        'DevCcdGetLstErrMsg':
            [[PyTango.DevVoid, ""],
            [PyTango.DevString, ""]],
        'DevCcdGetCurrent':
            [[PyTango.DevVoid, ""],
            [PyTango.DevLong, ""]],
        'DevGetDebugFlags':
            [[PyTango.DevVoid, ""],
            [PyTango.DevULong, ""]],
        'DevSetDebugFlags':
            [[PyTango.DevULong, ""],
            [PyTango.DevVoid, ""]],
        }


    #    Attribute definitions
    attr_list = {
        }


#------------------------------------------------------------------
#    LimaTacoCCDsClass Constructor
#------------------------------------------------------------------
    def __init__(self, name):
        PyTango.DeviceClass.__init__(self, name)
        self.set_type(name);


_control_ref = None
def set_control_ref(ctrl) :
    global _control_ref
    _control_ref = ctrl

def get_tango_specific_class_n_device() :
    return LimaTacoCCDsClass,LimaTacoCCDs
