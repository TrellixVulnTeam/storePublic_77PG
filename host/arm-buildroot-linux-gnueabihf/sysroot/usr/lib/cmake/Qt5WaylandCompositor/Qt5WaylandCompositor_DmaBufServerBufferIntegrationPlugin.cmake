
add_library(Qt5::DmaBufServerBufferIntegrationPlugin MODULE IMPORTED)


_populate_WaylandCompositor_plugin_properties(DmaBufServerBufferIntegrationPlugin RELEASE "wayland-graphics-integration-server/libdmabuf-server.so" FALSE)

list(APPEND Qt5WaylandCompositor_PLUGINS Qt5::DmaBufServerBufferIntegrationPlugin)
set_property(TARGET Qt5::WaylandCompositor APPEND PROPERTY QT_ALL_PLUGINS_wayland_graphics_integration_server Qt5::DmaBufServerBufferIntegrationPlugin)
set_property(TARGET Qt5::DmaBufServerBufferIntegrationPlugin PROPERTY QT_PLUGIN_TYPE "wayland-graphics-integration-server")
set_property(TARGET Qt5::DmaBufServerBufferIntegrationPlugin PROPERTY QT_PLUGIN_EXTENDS "")
