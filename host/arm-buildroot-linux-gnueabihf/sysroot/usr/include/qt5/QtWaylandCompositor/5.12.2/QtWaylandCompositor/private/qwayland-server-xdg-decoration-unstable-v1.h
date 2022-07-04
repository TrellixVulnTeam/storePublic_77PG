#ifndef QT_WAYLAND_SERVER_XDG_DECORATION_UNSTABLE_V1
#define QT_WAYLAND_SERVER_XDG_DECORATION_UNSTABLE_V1

#include "wayland-server.h"
#include <QtWaylandCompositor/private/wayland-xdg-decoration-unstable-v1-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_XDG_DECORATION_UNSTABLE_V1_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_XDG_DECORATION_UNSTABLE_V1_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_XDG_DECORATION_UNSTABLE_V1_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_XDG_DECORATION_UNSTABLE_V1_EXPORT zxdg_decoration_manager_v1
    {
    public:
        zxdg_decoration_manager_v1(struct ::wl_client *client, int id, int version);
        zxdg_decoration_manager_v1(struct ::wl_display *display, int version);
        zxdg_decoration_manager_v1(struct ::wl_resource *resource);
        zxdg_decoration_manager_v1();

        virtual ~zxdg_decoration_manager_v1();

        class Resource
        {
        public:
            Resource() : zxdg_decoration_manager_v1_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            zxdg_decoration_manager_v1 *zxdg_decoration_manager_v1_object;
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


    protected:
        virtual Resource *zxdg_decoration_manager_v1_allocate();

        virtual void zxdg_decoration_manager_v1_bind_resource(Resource *resource);
        virtual void zxdg_decoration_manager_v1_destroy_resource(Resource *resource);

        virtual void zxdg_decoration_manager_v1_destroy(Resource *resource);
        virtual void zxdg_decoration_manager_v1_get_toplevel_decoration(Resource *resource, uint32_t id, struct ::wl_resource *toplevel);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::zxdg_decoration_manager_v1_interface m_zxdg_decoration_manager_v1_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_get_toplevel_decoration(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *toplevel);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            zxdg_decoration_manager_v1 *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_XDG_DECORATION_UNSTABLE_V1_EXPORT zxdg_toplevel_decoration_v1
    {
    public:
        zxdg_toplevel_decoration_v1(struct ::wl_client *client, int id, int version);
        zxdg_toplevel_decoration_v1(struct ::wl_display *display, int version);
        zxdg_toplevel_decoration_v1(struct ::wl_resource *resource);
        zxdg_toplevel_decoration_v1();

        virtual ~zxdg_toplevel_decoration_v1();

        class Resource
        {
        public:
            Resource() : zxdg_toplevel_decoration_v1_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1_object;
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
            error_unconfigured_buffer = 0, // xdg_toplevel has a buffer attached before configure
            error_already_constructed = 1, // xdg_toplevel already has a decoration object
            error_orphaned = 2 // xdg_toplevel destroyed before the decoration object
        };

        enum mode {
            mode_client_side = 1, // no server-side window decoration
            mode_server_side = 2 // server-side window decoration
        };

        void send_configure(uint32_t mode);
        void send_configure(struct ::wl_resource *resource, uint32_t mode);

    protected:
        virtual Resource *zxdg_toplevel_decoration_v1_allocate();

        virtual void zxdg_toplevel_decoration_v1_bind_resource(Resource *resource);
        virtual void zxdg_toplevel_decoration_v1_destroy_resource(Resource *resource);

        virtual void zxdg_toplevel_decoration_v1_destroy(Resource *resource);
        virtual void zxdg_toplevel_decoration_v1_set_mode(Resource *resource, uint32_t mode);
        virtual void zxdg_toplevel_decoration_v1_unset_mode(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::zxdg_toplevel_decoration_v1_interface m_zxdg_toplevel_decoration_v1_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_mode(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t mode);
        static void handle_unset_mode(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            zxdg_toplevel_decoration_v1 *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
