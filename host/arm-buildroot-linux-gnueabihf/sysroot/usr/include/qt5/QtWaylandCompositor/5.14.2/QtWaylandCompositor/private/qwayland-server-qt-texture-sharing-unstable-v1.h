#ifndef QT_WAYLAND_SERVER_QT_TEXTURE_SHARING_UNSTABLE_V1
#define QT_WAYLAND_SERVER_QT_TEXTURE_SHARING_UNSTABLE_V1

#include "wayland-server-core.h"
#include <QtWaylandCompositor/private/wayland-qt-texture-sharing-unstable-v1-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_QT_TEXTURE_SHARING_UNSTABLE_V1_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_QT_TEXTURE_SHARING_UNSTABLE_V1_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_QT_TEXTURE_SHARING_UNSTABLE_V1_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_QT_TEXTURE_SHARING_UNSTABLE_V1_EXPORT zqt_texture_sharing_v1
    {
    public:
        zqt_texture_sharing_v1(struct ::wl_client *client, int id, int version);
        zqt_texture_sharing_v1(struct ::wl_display *display, int version);
        zqt_texture_sharing_v1(struct ::wl_resource *resource);
        zqt_texture_sharing_v1();

        virtual ~zqt_texture_sharing_v1();

        class Resource
        {
        public:
            Resource() : zqt_texture_sharing_v1_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            zqt_texture_sharing_v1 *zqt_texture_sharing_v1_object;
            zqt_texture_sharing_v1 *object() { return zqt_texture_sharing_v1_object; } 
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


        void send_image_failed(const QString &key, const QString &error_message);
        void send_image_failed(struct ::wl_resource *resource, const QString &key, const QString &error_message);
        void send_provide_buffer(struct ::wl_resource *buffer, const QString &key);
        void send_provide_buffer(struct ::wl_resource *resource, struct ::wl_resource *buffer, const QString &key);

    protected:
        virtual Resource *zqt_texture_sharing_v1_allocate();

        virtual void zqt_texture_sharing_v1_bind_resource(Resource *resource);
        virtual void zqt_texture_sharing_v1_destroy_resource(Resource *resource);

        virtual void zqt_texture_sharing_v1_request_image(Resource *resource, const QString &key);
        virtual void zqt_texture_sharing_v1_abandon_image(Resource *resource, const QString &key);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::zqt_texture_sharing_v1_interface m_zqt_texture_sharing_v1_interface;

        static void handle_request_image(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *key);
        static void handle_abandon_image(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *key);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            zqt_texture_sharing_v1 *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
