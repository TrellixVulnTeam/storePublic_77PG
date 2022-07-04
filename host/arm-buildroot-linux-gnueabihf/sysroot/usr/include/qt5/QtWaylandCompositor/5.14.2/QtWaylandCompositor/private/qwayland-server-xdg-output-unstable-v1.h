#ifndef QT_WAYLAND_SERVER_XDG_OUTPUT_UNSTABLE_V1
#define QT_WAYLAND_SERVER_XDG_OUTPUT_UNSTABLE_V1

#include "wayland-server-core.h"
#include <QtWaylandCompositor/private/wayland-xdg-output-unstable-v1-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_XDG_OUTPUT_UNSTABLE_V1_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_XDG_OUTPUT_UNSTABLE_V1_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_XDG_OUTPUT_UNSTABLE_V1_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_XDG_OUTPUT_UNSTABLE_V1_EXPORT zxdg_output_manager_v1
    {
    public:
        zxdg_output_manager_v1(struct ::wl_client *client, int id, int version);
        zxdg_output_manager_v1(struct ::wl_display *display, int version);
        zxdg_output_manager_v1(struct ::wl_resource *resource);
        zxdg_output_manager_v1();

        virtual ~zxdg_output_manager_v1();

        class Resource
        {
        public:
            Resource() : zxdg_output_manager_v1_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            zxdg_output_manager_v1 *zxdg_output_manager_v1_object;
            zxdg_output_manager_v1 *object() { return zxdg_output_manager_v1_object; } 
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
        virtual Resource *zxdg_output_manager_v1_allocate();

        virtual void zxdg_output_manager_v1_bind_resource(Resource *resource);
        virtual void zxdg_output_manager_v1_destroy_resource(Resource *resource);

        virtual void zxdg_output_manager_v1_destroy(Resource *resource);
        virtual void zxdg_output_manager_v1_get_xdg_output(Resource *resource, uint32_t id, struct ::wl_resource *output);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::zxdg_output_manager_v1_interface m_zxdg_output_manager_v1_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_get_xdg_output(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *output);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            zxdg_output_manager_v1 *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_XDG_OUTPUT_UNSTABLE_V1_EXPORT zxdg_output_v1
    {
    public:
        zxdg_output_v1(struct ::wl_client *client, int id, int version);
        zxdg_output_v1(struct ::wl_display *display, int version);
        zxdg_output_v1(struct ::wl_resource *resource);
        zxdg_output_v1();

        virtual ~zxdg_output_v1();

        class Resource
        {
        public:
            Resource() : zxdg_output_v1_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            zxdg_output_v1 *zxdg_output_v1_object;
            zxdg_output_v1 *object() { return zxdg_output_v1_object; } 
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


        void send_logical_position(int32_t x, int32_t y);
        void send_logical_position(struct ::wl_resource *resource, int32_t x, int32_t y);
        void send_logical_size(int32_t width, int32_t height);
        void send_logical_size(struct ::wl_resource *resource, int32_t width, int32_t height);
        void send_done();
        void send_done(struct ::wl_resource *resource);
        void send_name(const QString &name);
        void send_name(struct ::wl_resource *resource, const QString &name);
        void send_description(const QString &description);
        void send_description(struct ::wl_resource *resource, const QString &description);

    protected:
        virtual Resource *zxdg_output_v1_allocate();

        virtual void zxdg_output_v1_bind_resource(Resource *resource);
        virtual void zxdg_output_v1_destroy_resource(Resource *resource);

        virtual void zxdg_output_v1_destroy(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::zxdg_output_v1_interface m_zxdg_output_v1_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            zxdg_output_v1 *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
