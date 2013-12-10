#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file PyPoint2dConsoleOut.py
 @brief ModuleDescription
 @date $Date$


"""
import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
pypoint2dconsoleout_spec = ["implementation_id", "PyPoint2dConsoleOut", 
		 "type_name",         "PyPoint2dConsoleOut", 
		 "description",       "ModuleDescription", 
		 "version",           "1.0.0", 
		 "vendor",            "VenderName", 
		 "category",          "Category", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 ""]
# </rtc-template>

##
# @class PyPoint2dConsoleOut
# @brief ModuleDescription
# 
# 
class PyPoint2dConsoleOut(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		self._d_data = RTC.TimedPoint2D(RTC.Time(0,0),RTC.Point2D)
		"""
		"""
		self._dataIn = OpenRTM_aist.InPort("data", self._d_data)


		


		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		
		# </rtc-template>


		 
	##
	#
	# The initialize action (on CREATED->ALIVE transition)
	# formaer rtc_init_entry() 
	# 
	# @return RTC::ReturnCode_t
	# 
	#
	def onInitialize(self):
		# Bind variables and configuration variable
		
		# Set InPort buffers
		self.addInPort("data",self._dataIn)
		
		# Set OutPort buffers
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		
		# Set CORBA Service Ports
		
		return RTC.RTC_OK
	


	def onActivated(self, ec_id):
	
		return RTC.RTC_OK
	

	def onDeactivated(self, ec_id):
	
		return RTC.RTC_OK
	

	def onExecute(self, ec_id):
		if self._dataIn.isNew():
			self._d_data = self._dataIn.read()
			print self._d_data
	
		return RTC.RTC_OK
	


def PyPoint2dConsoleOutInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=pypoint2dconsoleout_spec)
    manager.registerFactory(profile,
                            PyPoint2dConsoleOut,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    PyPoint2dConsoleOutInit(manager)

    # Create a component
    comp = manager.createComponent("PyPoint2dConsoleOut")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

