QT.multimedia_private.VERSION = 5.14.2
QT.multimedia_private.name = QtMultimedia
QT.multimedia_private.module =
QT.multimedia_private.libs = $$QT_MODULE_LIB_BASE
QT.multimedia_private.includes = $$QT_MODULE_INCLUDE_BASE/QtMultimedia/5.14.2 $$QT_MODULE_INCLUDE_BASE/QtMultimedia/5.14.2/QtMultimedia
QT.multimedia_private.frameworks =
QT.multimedia_private.depends = core_private gui_private multimedia
QT.multimedia_private.uses =
QT.multimedia_private.module_config = v2 internal_module
QT.multimedia_private.enabled_features = alsa gstreamer_1_0 gstreamer gstreamer_app gstreamer_encodingprofiles gstreamer_photography linux_v4l
QT.multimedia_private.disabled_features = directshow evr gpu_vivante gstreamer_0_10 gstreamer_gl gstreamer_imxcommon openal pulseaudio resourcepolicy wasapi wmf wmsdk wshellitem
QMAKE_INCDIR_GSTREAMER = /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/gstreamer-1.0 /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/glib-2.0 /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/glib-2.0/include
QMAKE_DEPENDS_GSTREAMER_APP_CC = GSTREAMER
QMAKE_DEPENDS_GSTREAMER_APP_LD = GSTREAMER
QMAKE_DEPENDS_GSTREAMER_PHOTOGRAPHY_CC = GSTREAMER
QMAKE_DEPENDS_GSTREAMER_PHOTOGRAPHY_LD = GSTREAMER
QMAKE_LIBS_ALSA = -lasound
QMAKE_LIBS_GSTREAMER = -L/home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib -lgstaudio-1.0 -lgstvideo-1.0 -lgstbase-1.0 -lgstpbutils-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0
QMAKE_LIBS_GSTREAMER_APP = -lgstapp-1.0
QMAKE_LIBS_GSTREAMER_PHOTOGRAPHY = -lgstphotography-1.0
