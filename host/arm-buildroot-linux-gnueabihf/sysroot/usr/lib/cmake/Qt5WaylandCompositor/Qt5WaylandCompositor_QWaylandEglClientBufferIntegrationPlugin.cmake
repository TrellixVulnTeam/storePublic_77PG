
add_library(Qt5::QWaylandEglClientBufferIntegrationPlugin MODULE IMPORTED)


_populate_WaylandCompositor_plugin_properties(QWaylandEglClientBufferIntegrationPlugin RELEASE "wayland-graphics-integration-server/libqt-plugin-wayland-egl.so" FALSE)

list(APPEND Qt5WaylandCompositor_PLUGINS Qt5::QWaylandEglClientBufferIntegrationPlugin)
set_property(TARGET Qt5::WaylandCompositor APPEND PROPERTY QT_ALL_PLUGINS_wayland_graphics_integration_server Qt5::QWaylandEglClientBufferIntegrationPlugin)
set_property(TARGET Qt5::QWaylandEglClientBufferIntegrationPlugin PROPERTY QT_PLUGIN_TYPE "wayland-graphics-integration-server")
set_property(TARGET Qt5::QWaylandEglClientBufferIntegrationPlugin PROPERTY QT_PLUGIN_EXTENDS "")
