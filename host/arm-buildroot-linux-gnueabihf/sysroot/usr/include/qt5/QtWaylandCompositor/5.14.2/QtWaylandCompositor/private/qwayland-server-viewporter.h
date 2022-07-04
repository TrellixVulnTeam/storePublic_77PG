#ifndef QT_WAYLAND_SERVER_VIEWPORTER
#define QT_WAYLAND_SERVER_VIEWPORTER

#include "wayland-server-core.h"
#include <QtWaylandCompositor/private/wayland-viewporter-server-protocol.h>
#include <QByteArray>
#include <QMultiMap>
#include <QString>

#ifndef WAYLAND_VERSION_CHECK
#define WAYLAND_VERSION_CHECK(major, minor, micro) \
    ((WAYLAND_VERSION_MAJOR > (major)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR > (minor)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR == (minor) && WAYLAND_VERSION_MICRO >= (micro)))
#endif

QT_BEGIN_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wmissing-field-initializers")
QT_WARNING_DISABLE_CLANG("-Wmissing-field-initializers")

#if !defined(Q_WAYLAND_SERVER_VIEWPORTER_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_VIEWPORTER_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_VIEWPORTER_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_VIEWPORTER_EXPORT wp_viewporter
    {
    public:
        wp_viewporter(struct ::wl_client *client, int id, int version);
        wp_viewporter(struct ::wl_display *display, int version);
        wp_viewporter(struct ::wl_resource *resource);
        wp_viewporter();

        virtual ~wp_viewporter();

        class Resource
        {
        public:
            Resource() : wp_viewporter_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wp_viewporter *wp_viewporter_object;
            wp_viewporter *object() { return wp_viewporter_object; } 
            struct ::wl_resource *handle;

            struct ::wl_client *client() const { return wl_resource_get_client(handle); }
            int version() const { return wl_resource_get_version(handle); }

            static Resource *fromResource(struct ::wl_resource *resource);
        };

        void init(struct ::wl_client *client, int id, int version);
        void init(struct ::wl_display *display, int version);
        void init(struct ::wl_resource *resource);

        Resource *add(struct ::wl_client *client, int version);
        Resource *add(struct ::wl_client *client, int id, int version);
        Resource *add(struct wl_list *resource_list, struct ::wl_client *client, int id, int version);

        Resource *resource() { return m_resource; }
        const Resource *resource() const { return m_resource; }

        QMultiMap<struct ::wl_client*, Resource*> resourceMap() { return m_resource_map; }
        const QMultiMap<struct ::wl_client*, Resource*> resourceMap() const { return m_resource_map; }

        bool isGlobal() const { return m_global != nullptr; }
        bool isResource() const { return m_resource != nullptr; }

        static const struct ::wl_interface *interface();
        static QByteArray interfaceName() { return interface()->name; }
        static int interfaceVersion() { return interface()->version; }


        enum error {
            error_viewport_exists = 0, // the surface already has a viewport object associated
        };

    protected:
        virtual Resource *wp_viewporter_allocate();

        virtual void wp_viewporter_bind_resource(Resource *resource);
        virtual void wp_viewporter_destroy_resource(Resource *resource);

        virtual void wp_viewporter_destroy(Resource *resource);
        virtual void wp_viewporter_get_viewport(Resource *resource, uint32_t id, struct ::wl_resource *surface);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wp_viewporter_interface m_wp_viewporter_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_get_viewport(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *surface);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wp_viewporter *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_VIEWPORTER_EXPORT wp_viewport
    {
    public:
        wp_viewport(struct ::wl_client *client, int id, int version);
        wp_viewport(struct ::wl_display *display, int version);
        wp_viewport(struct ::wl_resource *resource);
        wp_viewport();

        virtual ~wp_viewport();

        class Resource
        {
        public:
            Resource() : wp_viewport_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wp_viewport *wp_viewport_object;
            wp_viewport *object() { return wp_viewport_object; } 
            struct ::wl_resource *handle;

            struct ::wl_client *client() const { return wl_resource_get_client(handle); }
            int version() const { return wl_resource_get_version(handle); }

            static Resource *fromResource(struct ::wl_resource *resource);
        };

        void init(struct ::wl_client *client, int id, int version);
        void init(struct ::wl_display *display, int version);
        void init(struct ::wl_resource *resource);

        Resource *add(struct ::wl_client *client, int version);
        Resource *add(struct ::wl_client *client, int id, int version);
        Resource *add(struct wl_list *resource_list, struct ::wl_client *client, int id, int version);

        Resource *resource() { return m_resource; }
        const Resource *resource() const { return m_resource; }

        QMultiMap<struct ::wl_client*, Resource*> resourceMap() { return m_resource_map; }
        const QMultiMap<struct ::wl_client*, Resource*> resourceMap() const { return m_resource_map; }

        bool isGlobal() const { return m_global != nullptr; }
        bool isResource() const { return m_resource != nullptr; }

        static const struct ::wl_interface *interface();
        static QByteArray interfaceName() { return interface()->name; }
        static int interfaceVersion() { return interface()->version; }


        enum error {
            error_bad_value = 0, // negative or zero values in width or height
            error_bad_size = 1, // destination size is not integer
            error_out_of_buffer = 2, // source rectangle extends outside of the content area
            error_no_surface = 3, // the wl_surface was destroyed
        };

    protected:
        virtual Resource *wp_viewport_allocate();

        virtual void wp_viewport_bind_resource(Resource *resource);
        virtual void wp_viewport_destroy_resource(Resource *resource);

        virtual void wp_viewport_destroy(Resource *resource);
        virtual void wp_viewport_set_source(Resource *resource, wl_fixed_t x, wl_fixed_t y, wl_fixed_t width, wl_fixed_t height);
        virtual void wp_viewport_set_destination(Resource *resource, int32_t width, int32_t height);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wp_viewport_interface m_wp_viewport_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_source(
            ::wl_client *client,
            struct wl_resource *resource,
            wl_fixed_t x,
            wl_fixed_t y,
            wl_fixed_t width,
            wl_fixed_t height);
        static void handle_set_destination(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t width,
            int32_t height);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wp_viewport *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
