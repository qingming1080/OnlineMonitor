#############################################################################
# Makefile for building: qml
# Generated by qmake (3.1) (Qt 5.15.2)
# Project:  qml.pro
# Template: app
# Command: E:\qt5.15\5.15.2\msvc2019_64\bin\qmake.exe -o Makefile qml.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug"
#############################################################################

MAKEFILE      = Makefile

EQ            = =

first: debug
install: debug-install
uninstall: debug-uninstall
QMAKE         = E:\qt5.15\5.15.2\msvc2019_64\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR   = xcopy /s /q /y /i
QINSTALL      = E:\qt5.15\5.15.2\msvc2019_64\bin\qmake.exe -install qinstall
QINSTALL_PROGRAM = E:\qt5.15\5.15.2\msvc2019_64\bin\qmake.exe -install qinstall -exe
DEL_FILE      = del
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = move
IDC           = idc
IDL           = midl
ZIP           = zip -r -9
DEF_FILE      = 
RES_FILE      = 
SED           = $(QMAKE) -install sed
MOVE          = move
SUBTARGETS    =  \
		debug \
		release


debug: $(MAKEFILE) FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: $(MAKEFILE) FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: qml.pro E:\qt5.15\5.15.2\msvc2019_64\mkspecs\win32-msvc\qmake.conf E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\spec_pre.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\angle.conf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\windows-desktop.conf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\windows_vulkan_sdk.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\windows-vulkan.conf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\msvc-desktop.conf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\qconfig.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3danimation.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3danimation_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dcore.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dcore_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dextras.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dextras_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dinput.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dinput_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dlogic.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dlogic_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquick.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquick_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickanimation.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickanimation_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickextras.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickextras_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickinput.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickinput_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickrender.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickrender_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickscene2d.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickscene2d_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3drender.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3drender_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_accessibility_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axbase.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axbase_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axcontainer.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axcontainer_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axserver.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axserver_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bluetooth.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bluetooth_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bodymovin_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bootstrap_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_charts.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_charts_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_concurrent.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_concurrent_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_core.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_core_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_datavisualization.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_datavisualization_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_dbus.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_dbus_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_designer.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_designer_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_designercomponents_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_devicediscovery_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_edid_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_egl_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_eventdispatcher_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_fb_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_fontdatabase_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gamepad.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gamepad_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gui.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gui_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_help.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_help_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_location.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_location_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimedia.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimedia_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimediawidgets.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimediawidgets_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_network.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_network_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_networkauth.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_networkauth_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_nfc.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_nfc_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_opengl.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_opengl_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_openglextensions.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_openglextensions_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_packetprotocol_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_platformcompositor_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioning.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioning_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioningquick.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioningquick_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_printsupport.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_printsupport_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_purchasing.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_purchasing_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qml.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qml_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmldebug_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmldevtools_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlmodels.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlmodels_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmltest.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmltest_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlworkerscript.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlworkerscript_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3d.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3d_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dassetimport.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dassetimport_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3drender.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3drender_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3druntimerender.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3druntimerender_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dutils.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dutils_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickcontrols2.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickcontrols2_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickparticles_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickshapes_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quicktemplates2.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quicktemplates2_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickwidgets.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickwidgets_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_remoteobjects.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_remoteobjects_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_repparser.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_repparser_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_script.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_script_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scripttools.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scripttools_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scxml.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scxml_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sensors.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sensors_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialbus.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialbus_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialport.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialport_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sql.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sql_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_svg.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_svg_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_testlib.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_testlib_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_texttospeech.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_texttospeech_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_theme_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_uiplugin.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_uitools.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_uitools_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_virtualkeyboard.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_virtualkeyboard_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_vulkan_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webchannel.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webchannel_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webengine.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webengine_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginecore.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginecore_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginecoreheaders_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginewidgets.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginewidgets_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_websockets.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_websockets_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webview.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webview_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_widgets.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_widgets_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_windowsuiautomation_support_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_winextras.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_winextras_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xml.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xml_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xmlpatterns.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xmlpatterns_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_zlib_private.pri \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qt_functions.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qt_config.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\win32-msvc\qmake.conf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\spec_post.prf \
		.qmake.stash \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\exclusive_builds.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\msvc-version.conf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\toolchain.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\default_pre.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\default_pre.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\resolve_config.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\exclusive_builds_post.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\default_post.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qml_debug.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\precompile_header.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\warn_on.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qt.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\resources_functions.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\resources.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\moc.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\opengl.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\uic.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qmake_use.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\file_copies.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\windows.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\testcase_targets.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\exceptions.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\yacc.prf \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\lex.prf \
		qml.pro \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5VirtualKeyboard.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Quick.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Charts.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Widgets.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Gui.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5QmlModels.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Qml.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Network.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Core.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\qtmain.prl \
		E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\build_pass.prf \
		qml.qrc \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5VirtualKeyboardd.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Quickd.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Chartsd.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Widgetsd.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Guid.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5QmlModelsd.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Qmld.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Networkd.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Cored.prl \
		E:\qt5.15\5.15.2\msvc2019_64\lib\qtmaind.prl
	$(QMAKE) -o Makefile qml.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug"
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\spec_pre.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\angle.conf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\windows-desktop.conf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\windows_vulkan_sdk.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\windows-vulkan.conf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\msvc-desktop.conf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\qconfig.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3danimation.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3danimation_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dcore.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dcore_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dextras.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dextras_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dinput.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dinput_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dlogic.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dlogic_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquick.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquick_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickanimation.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickanimation_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickextras.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickextras_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickinput.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickinput_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickrender.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickrender_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickscene2d.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3dquickscene2d_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3drender.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_3drender_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_accessibility_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axbase.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axbase_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axcontainer.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axcontainer_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axserver.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_axserver_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bluetooth.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bluetooth_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bodymovin_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_bootstrap_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_charts.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_charts_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_concurrent.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_concurrent_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_core.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_core_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_datavisualization.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_datavisualization_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_dbus.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_dbus_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_designer.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_designer_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_designercomponents_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_devicediscovery_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_edid_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_egl_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_eventdispatcher_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_fb_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_fontdatabase_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gamepad.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gamepad_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gui.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_gui_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_help.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_help_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_location.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_location_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimedia.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimedia_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimediawidgets.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_multimediawidgets_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_network.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_network_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_networkauth.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_networkauth_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_nfc.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_nfc_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_opengl.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_opengl_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_openglextensions.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_openglextensions_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_packetprotocol_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_platformcompositor_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioning.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioning_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioningquick.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_positioningquick_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_printsupport.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_printsupport_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_purchasing.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_purchasing_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qml.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qml_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmldebug_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmldevtools_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlmodels.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlmodels_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmltest.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmltest_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlworkerscript.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qmlworkerscript_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3d.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3d_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dassetimport.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dassetimport_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3drender.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3drender_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3druntimerender.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3druntimerender_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dutils.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick3dutils_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quick_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickcontrols2.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickcontrols2_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickparticles_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickshapes_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quicktemplates2.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quicktemplates2_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickwidgets.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_quickwidgets_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_remoteobjects.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_remoteobjects_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_repparser.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_repparser_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_script.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_script_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scripttools.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scripttools_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scxml.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_scxml_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sensors.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sensors_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialbus.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialbus_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialport.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_serialport_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sql.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_sql_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_svg.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_svg_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_testlib.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_testlib_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_texttospeech.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_texttospeech_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_theme_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_uiplugin.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_uitools.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_uitools_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_virtualkeyboard.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_virtualkeyboard_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_vulkan_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webchannel.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webchannel_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webengine.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webengine_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginecore.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginecore_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginecoreheaders_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginewidgets.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webenginewidgets_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_websockets.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_websockets_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webview.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_webview_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_widgets.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_widgets_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_windowsuiautomation_support_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_winextras.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_winextras_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xml.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xml_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xmlpatterns.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_xmlpatterns_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\modules\qt_lib_zlib_private.pri:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qt_functions.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qt_config.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\win32-msvc\qmake.conf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\spec_post.prf:
.qmake.stash:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\exclusive_builds.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\common\msvc-version.conf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\toolchain.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\default_pre.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\default_pre.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\resolve_config.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\exclusive_builds_post.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\default_post.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qml_debug.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\precompile_header.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\warn_on.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qt.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\resources_functions.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\resources.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\moc.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\opengl.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\uic.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\qmake_use.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\file_copies.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\win32\windows.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\testcase_targets.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\exceptions.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\yacc.prf:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\lex.prf:
qml.pro:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5VirtualKeyboard.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Quick.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Charts.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Widgets.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Gui.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5QmlModels.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Qml.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Network.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Core.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\qtmain.prl:
E:\qt5.15\5.15.2\msvc2019_64\mkspecs\features\build_pass.prf:
qml.qrc:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5VirtualKeyboardd.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Quickd.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Chartsd.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Widgetsd.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Guid.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5QmlModelsd.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Qmld.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Networkd.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\Qt5Cored.prl:
E:\qt5.15\5.15.2\msvc2019_64\lib\qtmaind.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile qml.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug"

qmake_all: FORCE

make_first: debug-make_first release-make_first  FORCE
all: debug-all release-all  FORCE
clean: debug-clean release-clean  FORCE
	-$(DEL_FILE) qml.vc.pdb
	-$(DEL_FILE) qml.ilk
	-$(DEL_FILE) qml.idb
distclean: debug-distclean release-distclean  FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) .qmake.stash qml.pdb

debug-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocclean
release-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocclean
mocclean: debug-mocclean release-mocclean

debug-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocables
release-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocables
mocables: debug-mocables release-mocables

check: first

benchmark: first
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile