#ifndef QT_WAYLAND_SERVER_WAYLAND
#define QT_WAYLAND_SERVER_WAYLAND

#include "wayland-server-core.h"
#include <QtWaylandCompositor/private/wayland-wayland-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_WAYLAND_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_WAYLAND_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_WAYLAND_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_callback
    {
    public:
        wl_callback(struct ::wl_client *client, int id, int version);
        wl_callback(struct ::wl_display *display, int version);
        wl_callback(struct ::wl_resource *resource);
        wl_callback();

        virtual ~wl_callback();

        class Resource
        {
        public:
            Resource() : callback_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_callback *callback_object;
            wl_callback *object() { return callback_object; } 
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


        void send_done(uint32_t callback_data);
        void send_done(struct ::wl_resource *resource, uint32_t callback_data);

    protected:
        virtual Resource *callback_allocate();

        virtual void callback_bind_resource(Resource *resource);
        virtual void callback_destroy_resource(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_callback *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_compositor
    {
    public:
        wl_compositor(struct ::wl_client *client, int id, int version);
        wl_compositor(struct ::wl_display *display, int version);
        wl_compositor(struct ::wl_resource *resource);
        wl_compositor();

        virtual ~wl_compositor();

        class Resource
        {
        public:
            Resource() : compositor_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_compositor *compositor_object;
            wl_compositor *object() { return compositor_object; } 
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
        virtual Resource *compositor_allocate();

        virtual void compositor_bind_resource(Resource *resource);
        virtual void compositor_destroy_resource(Resource *resource);

        virtual void compositor_create_surface(Resource *resource, uint32_t id);
        virtual void compositor_create_region(Resource *resource, uint32_t id);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_compositor_interface m_wl_compositor_interface;

        static void handle_create_surface(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id);
        static void handle_create_region(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_compositor *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_shm_pool
    {
    public:
        wl_shm_pool(struct ::wl_client *client, int id, int version);
        wl_shm_pool(struct ::wl_display *display, int version);
        wl_shm_pool(struct ::wl_resource *resource);
        wl_shm_pool();

        virtual ~wl_shm_pool();

        class Resource
        {
        public:
            Resource() : shm_pool_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_shm_pool *shm_pool_object;
            wl_shm_pool *object() { return shm_pool_object; } 
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
        virtual Resource *shm_pool_allocate();

        virtual void shm_pool_bind_resource(Resource *resource);
        virtual void shm_pool_destroy_resource(Resource *resource);

        virtual void shm_pool_create_buffer(Resource *resource, uint32_t id, int32_t offset, int32_t width, int32_t height, int32_t stride, uint32_t format);
        virtual void shm_pool_destroy(Resource *resource);
        virtual void shm_pool_resize(Resource *resource, int32_t size);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_shm_pool_interface m_wl_shm_pool_interface;

        static void handle_create_buffer(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            int32_t offset,
            int32_t width,
            int32_t height,
            int32_t stride,
            uint32_t format);
        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_resize(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t size);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_shm_pool *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_shm
    {
    public:
        wl_shm(struct ::wl_client *client, int id, int version);
        wl_shm(struct ::wl_display *display, int version);
        wl_shm(struct ::wl_resource *resource);
        wl_shm();

        virtual ~wl_shm();

        class Resource
        {
        public:
            Resource() : shm_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_shm *shm_object;
            wl_shm *object() { return shm_object; } 
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
            error_invalid_format = 0, // buffer format is not known
            error_invalid_stride = 1, // invalid size or stride during pool or buffer creation
            error_invalid_fd = 2, // mmapping the file descriptor failed
        };

        enum format {
            format_argb8888 = 0, // 32-bit ARGB format, [31:0] A:R:G:B 8:8:8:8 little endian
            format_xrgb8888 = 1, // 32-bit RGB format, [31:0] x:R:G:B 8:8:8:8 little endian
            format_c8 = 0x20203843, // 8-bit color index format, [7:0] C
            format_rgb332 = 0x38424752, // 8-bit RGB format, [7:0] R:G:B 3:3:2
            format_bgr233 = 0x38524742, // 8-bit BGR format, [7:0] B:G:R 2:3:3
            format_xrgb4444 = 0x32315258, // 16-bit xRGB format, [15:0] x:R:G:B 4:4:4:4 little endian
            format_xbgr4444 = 0x32314258, // 16-bit xBGR format, [15:0] x:B:G:R 4:4:4:4 little endian
            format_rgbx4444 = 0x32315852, // 16-bit RGBx format, [15:0] R:G:B:x 4:4:4:4 little endian
            format_bgrx4444 = 0x32315842, // 16-bit BGRx format, [15:0] B:G:R:x 4:4:4:4 little endian
            format_argb4444 = 0x32315241, // 16-bit ARGB format, [15:0] A:R:G:B 4:4:4:4 little endian
            format_abgr4444 = 0x32314241, // 16-bit ABGR format, [15:0] A:B:G:R 4:4:4:4 little endian
            format_rgba4444 = 0x32314152, // 16-bit RBGA format, [15:0] R:G:B:A 4:4:4:4 little endian
            format_bgra4444 = 0x32314142, // 16-bit BGRA format, [15:0] B:G:R:A 4:4:4:4 little endian
            format_xrgb1555 = 0x35315258, // 16-bit xRGB format, [15:0] x:R:G:B 1:5:5:5 little endian
            format_xbgr1555 = 0x35314258, // 16-bit xBGR 1555 format, [15:0] x:B:G:R 1:5:5:5 little endian
            format_rgbx5551 = 0x35315852, // 16-bit RGBx 5551 format, [15:0] R:G:B:x 5:5:5:1 little endian
            format_bgrx5551 = 0x35315842, // 16-bit BGRx 5551 format, [15:0] B:G:R:x 5:5:5:1 little endian
            format_argb1555 = 0x35315241, // 16-bit ARGB 1555 format, [15:0] A:R:G:B 1:5:5:5 little endian
            format_abgr1555 = 0x35314241, // 16-bit ABGR 1555 format, [15:0] A:B:G:R 1:5:5:5 little endian
            format_rgba5551 = 0x35314152, // 16-bit RGBA 5551 format, [15:0] R:G:B:A 5:5:5:1 little endian
            format_bgra5551 = 0x35314142, // 16-bit BGRA 5551 format, [15:0] B:G:R:A 5:5:5:1 little endian
            format_rgb565 = 0x36314752, // 16-bit RGB 565 format, [15:0] R:G:B 5:6:5 little endian
            format_bgr565 = 0x36314742, // 16-bit BGR 565 format, [15:0] B:G:R 5:6:5 little endian
            format_rgb888 = 0x34324752, // 24-bit RGB format, [23:0] R:G:B little endian
            format_bgr888 = 0x34324742, // 24-bit BGR format, [23:0] B:G:R little endian
            format_xbgr8888 = 0x34324258, // 32-bit xBGR format, [31:0] x:B:G:R 8:8:8:8 little endian
            format_rgbx8888 = 0x34325852, // 32-bit RGBx format, [31:0] R:G:B:x 8:8:8:8 little endian
            format_bgrx8888 = 0x34325842, // 32-bit BGRx format, [31:0] B:G:R:x 8:8:8:8 little endian
            format_abgr8888 = 0x34324241, // 32-bit ABGR format, [31:0] A:B:G:R 8:8:8:8 little endian
            format_rgba8888 = 0x34324152, // 32-bit RGBA format, [31:0] R:G:B:A 8:8:8:8 little endian
            format_bgra8888 = 0x34324142, // 32-bit BGRA format, [31:0] B:G:R:A 8:8:8:8 little endian
            format_xrgb2101010 = 0x30335258, // 32-bit xRGB format, [31:0] x:R:G:B 2:10:10:10 little endian
            format_xbgr2101010 = 0x30334258, // 32-bit xBGR format, [31:0] x:B:G:R 2:10:10:10 little endian
            format_rgbx1010102 = 0x30335852, // 32-bit RGBx format, [31:0] R:G:B:x 10:10:10:2 little endian
            format_bgrx1010102 = 0x30335842, // 32-bit BGRx format, [31:0] B:G:R:x 10:10:10:2 little endian
            format_argb2101010 = 0x30335241, // 32-bit ARGB format, [31:0] A:R:G:B 2:10:10:10 little endian
            format_abgr2101010 = 0x30334241, // 32-bit ABGR format, [31:0] A:B:G:R 2:10:10:10 little endian
            format_rgba1010102 = 0x30334152, // 32-bit RGBA format, [31:0] R:G:B:A 10:10:10:2 little endian
            format_bgra1010102 = 0x30334142, // 32-bit BGRA format, [31:0] B:G:R:A 10:10:10:2 little endian
            format_yuyv = 0x56595559, // packed YCbCr format, [31:0] Cr0:Y1:Cb0:Y0 8:8:8:8 little endian
            format_yvyu = 0x55595659, // packed YCbCr format, [31:0] Cb0:Y1:Cr0:Y0 8:8:8:8 little endian
            format_uyvy = 0x59565955, // packed YCbCr format, [31:0] Y1:Cr0:Y0:Cb0 8:8:8:8 little endian
            format_vyuy = 0x59555956, // packed YCbCr format, [31:0] Y1:Cb0:Y0:Cr0 8:8:8:8 little endian
            format_ayuv = 0x56555941, // packed AYCbCr format, [31:0] A:Y:Cb:Cr 8:8:8:8 little endian
            format_nv12 = 0x3231564e, // 2 plane YCbCr Cr:Cb format, 2x2 subsampled Cr:Cb plane
            format_nv21 = 0x3132564e, // 2 plane YCbCr Cb:Cr format, 2x2 subsampled Cb:Cr plane
            format_nv16 = 0x3631564e, // 2 plane YCbCr Cr:Cb format, 2x1 subsampled Cr:Cb plane
            format_nv61 = 0x3136564e, // 2 plane YCbCr Cb:Cr format, 2x1 subsampled Cb:Cr plane
            format_yuv410 = 0x39565559, // 3 plane YCbCr format, 4x4 subsampled Cb (1) and Cr (2) planes
            format_yvu410 = 0x39555659, // 3 plane YCbCr format, 4x4 subsampled Cr (1) and Cb (2) planes
            format_yuv411 = 0x31315559, // 3 plane YCbCr format, 4x1 subsampled Cb (1) and Cr (2) planes
            format_yvu411 = 0x31315659, // 3 plane YCbCr format, 4x1 subsampled Cr (1) and Cb (2) planes
            format_yuv420 = 0x32315559, // 3 plane YCbCr format, 2x2 subsampled Cb (1) and Cr (2) planes
            format_yvu420 = 0x32315659, // 3 plane YCbCr format, 2x2 subsampled Cr (1) and Cb (2) planes
            format_yuv422 = 0x36315559, // 3 plane YCbCr format, 2x1 subsampled Cb (1) and Cr (2) planes
            format_yvu422 = 0x36315659, // 3 plane YCbCr format, 2x1 subsampled Cr (1) and Cb (2) planes
            format_yuv444 = 0x34325559, // 3 plane YCbCr format, non-subsampled Cb (1) and Cr (2) planes
            format_yvu444 = 0x34325659, // 3 plane YCbCr format, non-subsampled Cr (1) and Cb (2) planes
        };

        void send_format(uint32_t format);
        void send_format(struct ::wl_resource *resource, uint32_t format);

    protected:
        virtual Resource *shm_allocate();

        virtual void shm_bind_resource(Resource *resource);
        virtual void shm_destroy_resource(Resource *resource);

        virtual void shm_create_pool(Resource *resource, uint32_t id, int32_t fd, int32_t size);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_shm_interface m_wl_shm_interface;

        static void handle_create_pool(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            int32_t fd,
            int32_t size);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_shm *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_buffer
    {
    public:
        wl_buffer(struct ::wl_client *client, int id, int version);
        wl_buffer(struct ::wl_display *display, int version);
        wl_buffer(struct ::wl_resource *resource);
        wl_buffer();

        virtual ~wl_buffer();

        class Resource
        {
        public:
            Resource() : buffer_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_buffer *buffer_object;
            wl_buffer *object() { return buffer_object; } 
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


        void send_release();
        void send_release(struct ::wl_resource *resource);

    protected:
        virtual Resource *buffer_allocate();

        virtual void buffer_bind_resource(Resource *resource);
        virtual void buffer_destroy_resource(Resource *resource);

        virtual void buffer_destroy(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_buffer_interface m_wl_buffer_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_buffer *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_data_offer
    {
    public:
        wl_data_offer(struct ::wl_client *client, int id, int version);
        wl_data_offer(struct ::wl_display *display, int version);
        wl_data_offer(struct ::wl_resource *resource);
        wl_data_offer();

        virtual ~wl_data_offer();

        class Resource
        {
        public:
            Resource() : data_offer_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_data_offer *data_offer_object;
            wl_data_offer *object() { return data_offer_object; } 
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
            error_invalid_finish = 0, // finish request was called untimely
            error_invalid_action_mask = 1, // action mask contains invalid values
            error_invalid_action = 2, // action argument has an invalid value
            error_invalid_offer = 3, // offer doesn't accept this request
        };

        void send_offer(const QString &mime_type);
        void send_offer(struct ::wl_resource *resource, const QString &mime_type);
        void send_source_actions(uint32_t source_actions);
        void send_source_actions(struct ::wl_resource *resource, uint32_t source_actions);
        void send_action(uint32_t dnd_action);
        void send_action(struct ::wl_resource *resource, uint32_t dnd_action);

    protected:
        virtual Resource *data_offer_allocate();

        virtual void data_offer_bind_resource(Resource *resource);
        virtual void data_offer_destroy_resource(Resource *resource);

        virtual void data_offer_accept(Resource *resource, uint32_t serial, const QString &mime_type);
        virtual void data_offer_receive(Resource *resource, const QString &mime_type, int32_t fd);
        virtual void data_offer_destroy(Resource *resource);
        virtual void data_offer_finish(Resource *resource);
        virtual void data_offer_set_actions(Resource *resource, uint32_t dnd_actions, uint32_t preferred_action);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_data_offer_interface m_wl_data_offer_interface;

        static void handle_accept(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            const char *mime_type);
        static void handle_receive(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *mime_type,
            int32_t fd);
        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_finish(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_actions(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t dnd_actions,
            uint32_t preferred_action);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_data_offer *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_data_source
    {
    public:
        wl_data_source(struct ::wl_client *client, int id, int version);
        wl_data_source(struct ::wl_display *display, int version);
        wl_data_source(struct ::wl_resource *resource);
        wl_data_source();

        virtual ~wl_data_source();

        class Resource
        {
        public:
            Resource() : data_source_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_data_source *data_source_object;
            wl_data_source *object() { return data_source_object; } 
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
            error_invalid_action_mask = 0, // action mask contains invalid values
            error_invalid_source = 1, // source doesn't accept this request
        };

        void send_target(const QString &mime_type);
        void send_target(struct ::wl_resource *resource, const QString &mime_type);
        void send_send(const QString &mime_type, int32_t fd);
        void send_send(struct ::wl_resource *resource, const QString &mime_type, int32_t fd);
        void send_cancelled();
        void send_cancelled(struct ::wl_resource *resource);
        void send_dnd_drop_performed();
        void send_dnd_drop_performed(struct ::wl_resource *resource);
        void send_dnd_finished();
        void send_dnd_finished(struct ::wl_resource *resource);
        void send_action(uint32_t dnd_action);
        void send_action(struct ::wl_resource *resource, uint32_t dnd_action);

    protected:
        virtual Resource *data_source_allocate();

        virtual void data_source_bind_resource(Resource *resource);
        virtual void data_source_destroy_resource(Resource *resource);

        virtual void data_source_offer(Resource *resource, const QString &mime_type);
        virtual void data_source_destroy(Resource *resource);
        virtual void data_source_set_actions(Resource *resource, uint32_t dnd_actions);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_data_source_interface m_wl_data_source_interface;

        static void handle_offer(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *mime_type);
        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_actions(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t dnd_actions);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_data_source *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_data_device
    {
    public:
        wl_data_device(struct ::wl_client *client, int id, int version);
        wl_data_device(struct ::wl_display *display, int version);
        wl_data_device(struct ::wl_resource *resource);
        wl_data_device();

        virtual ~wl_data_device();

        class Resource
        {
        public:
            Resource() : data_device_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_data_device *data_device_object;
            wl_data_device *object() { return data_device_object; } 
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
            error_role = 0, // given wl_surface has another role
        };

        void send_data_offer(struct ::wl_resource *id);
        void send_data_offer(struct ::wl_resource *resource, struct ::wl_resource *id);
        void send_enter(uint32_t serial, struct ::wl_resource *surface, wl_fixed_t x, wl_fixed_t y, struct ::wl_resource *id);
        void send_enter(struct ::wl_resource *resource, uint32_t serial, struct ::wl_resource *surface, wl_fixed_t x, wl_fixed_t y, struct ::wl_resource *id);
        void send_leave();
        void send_leave(struct ::wl_resource *resource);
        void send_motion(uint32_t time, wl_fixed_t x, wl_fixed_t y);
        void send_motion(struct ::wl_resource *resource, uint32_t time, wl_fixed_t x, wl_fixed_t y);
        void send_drop();
        void send_drop(struct ::wl_resource *resource);
        void send_selection(struct ::wl_resource *id);
        void send_selection(struct ::wl_resource *resource, struct ::wl_resource *id);

    protected:
        virtual Resource *data_device_allocate();

        virtual void data_device_bind_resource(Resource *resource);
        virtual void data_device_destroy_resource(Resource *resource);

        virtual void data_device_start_drag(Resource *resource, struct ::wl_resource *source, struct ::wl_resource *origin, struct ::wl_resource *icon, uint32_t serial);
        virtual void data_device_set_selection(Resource *resource, struct ::wl_resource *source, uint32_t serial);
        virtual void data_device_release(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_data_device_interface m_wl_data_device_interface;

        static void handle_start_drag(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *source,
            struct ::wl_resource *origin,
            struct ::wl_resource *icon,
            uint32_t serial);
        static void handle_set_selection(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *source,
            uint32_t serial);
        static void handle_release(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_data_device *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_data_device_manager
    {
    public:
        wl_data_device_manager(struct ::wl_client *client, int id, int version);
        wl_data_device_manager(struct ::wl_display *display, int version);
        wl_data_device_manager(struct ::wl_resource *resource);
        wl_data_device_manager();

        virtual ~wl_data_device_manager();

        class Resource
        {
        public:
            Resource() : data_device_manager_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_data_device_manager *data_device_manager_object;
            wl_data_device_manager *object() { return data_device_manager_object; } 
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


        enum dnd_action {
            dnd_action_none = 0, // no action
            dnd_action_copy = 1, // copy action
            dnd_action_move = 2, // move action
            dnd_action_ask = 4, // ask action
        };

    protected:
        virtual Resource *data_device_manager_allocate();

        virtual void data_device_manager_bind_resource(Resource *resource);
        virtual void data_device_manager_destroy_resource(Resource *resource);

        virtual void data_device_manager_create_data_source(Resource *resource, uint32_t id);
        virtual void data_device_manager_get_data_device(Resource *resource, uint32_t id, struct ::wl_resource *seat);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_data_device_manager_interface m_wl_data_device_manager_interface;

        static void handle_create_data_source(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id);
        static void handle_get_data_device(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *seat);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_data_device_manager *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_shell
    {
    public:
        wl_shell(struct ::wl_client *client, int id, int version);
        wl_shell(struct ::wl_display *display, int version);
        wl_shell(struct ::wl_resource *resource);
        wl_shell();

        virtual ~wl_shell();

        class Resource
        {
        public:
            Resource() : shell_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_shell *shell_object;
            wl_shell *object() { return shell_object; } 
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
            error_role = 0, // given wl_surface has another role
        };

    protected:
        virtual Resource *shell_allocate();

        virtual void shell_bind_resource(Resource *resource);
        virtual void shell_destroy_resource(Resource *resource);

        virtual void shell_get_shell_surface(Resource *resource, uint32_t id, struct ::wl_resource *surface);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_shell_interface m_wl_shell_interface;

        static void handle_get_shell_surface(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *surface);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_shell *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_shell_surface
    {
    public:
        wl_shell_surface(struct ::wl_client *client, int id, int version);
        wl_shell_surface(struct ::wl_display *display, int version);
        wl_shell_surface(struct ::wl_resource *resource);
        wl_shell_surface();

        virtual ~wl_shell_surface();

        class Resource
        {
        public:
            Resource() : shell_surface_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_shell_surface *shell_surface_object;
            wl_shell_surface *object() { return shell_surface_object; } 
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


        enum resize {
            resize_none = 0, // no edge
            resize_top = 1, // top edge
            resize_bottom = 2, // bottom edge
            resize_left = 4, // left edge
            resize_top_left = 5, // top and left edges
            resize_bottom_left = 6, // bottom and left edges
            resize_right = 8, // right edge
            resize_top_right = 9, // top and right edges
            resize_bottom_right = 10, // bottom and right edges
        };

        enum transient {
            transient_inactive = 0x1, // do not set keyboard focus
        };

        enum fullscreen_method {
            fullscreen_method_default = 0, // no preference, apply default policy
            fullscreen_method_scale = 1, // scale, preserve the surface's aspect ratio and center on output
            fullscreen_method_driver = 2, // switch output mode to the smallest mode that can fit the surface, add black borders to compensate size mismatch
            fullscreen_method_fill = 3, // no upscaling, center on output and add black borders to compensate size mismatch
        };

        void send_ping(uint32_t serial);
        void send_ping(struct ::wl_resource *resource, uint32_t serial);
        void send_configure(uint32_t edges, int32_t width, int32_t height);
        void send_configure(struct ::wl_resource *resource, uint32_t edges, int32_t width, int32_t height);
        void send_popup_done();
        void send_popup_done(struct ::wl_resource *resource);

    protected:
        virtual Resource *shell_surface_allocate();

        virtual void shell_surface_bind_resource(Resource *resource);
        virtual void shell_surface_destroy_resource(Resource *resource);

        virtual void shell_surface_pong(Resource *resource, uint32_t serial);
        virtual void shell_surface_move(Resource *resource, struct ::wl_resource *seat, uint32_t serial);
        virtual void shell_surface_resize(Resource *resource, struct ::wl_resource *seat, uint32_t serial, uint32_t edges);
        virtual void shell_surface_set_toplevel(Resource *resource);
        virtual void shell_surface_set_transient(Resource *resource, struct ::wl_resource *parent, int32_t x, int32_t y, uint32_t flags);
        virtual void shell_surface_set_fullscreen(Resource *resource, uint32_t method, uint32_t framerate, struct ::wl_resource *output);
        virtual void shell_surface_set_popup(Resource *resource, struct ::wl_resource *seat, uint32_t serial, struct ::wl_resource *parent, int32_t x, int32_t y, uint32_t flags);
        virtual void shell_surface_set_maximized(Resource *resource, struct ::wl_resource *output);
        virtual void shell_surface_set_title(Resource *resource, const QString &title);
        virtual void shell_surface_set_class(Resource *resource, const QString &class_);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_shell_surface_interface m_wl_shell_surface_interface;

        static void handle_pong(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial);
        static void handle_move(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *seat,
            uint32_t serial);
        static void handle_resize(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *seat,
            uint32_t serial,
            uint32_t edges);
        static void handle_set_toplevel(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_transient(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *parent,
            int32_t x,
            int32_t y,
            uint32_t flags);
        static void handle_set_fullscreen(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t method,
            uint32_t framerate,
            struct ::wl_resource *output);
        static void handle_set_popup(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *seat,
            uint32_t serial,
            struct ::wl_resource *parent,
            int32_t x,
            int32_t y,
            uint32_t flags);
        static void handle_set_maximized(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *output);
        static void handle_set_title(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *title);
        static void handle_set_class(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *class_);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_shell_surface *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_surface
    {
    public:
        wl_surface(struct ::wl_client *client, int id, int version);
        wl_surface(struct ::wl_display *display, int version);
        wl_surface(struct ::wl_resource *resource);
        wl_surface();

        virtual ~wl_surface();

        class Resource
        {
        public:
            Resource() : surface_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_surface *surface_object;
            wl_surface *object() { return surface_object; } 
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
            error_invalid_scale = 0, // buffer scale value is invalid
            error_invalid_transform = 1, // buffer transform value is invalid
        };

        void send_enter(struct ::wl_resource *output);
        void send_enter(struct ::wl_resource *resource, struct ::wl_resource *output);
        void send_leave(struct ::wl_resource *output);
        void send_leave(struct ::wl_resource *resource, struct ::wl_resource *output);

    protected:
        virtual Resource *surface_allocate();

        virtual void surface_bind_resource(Resource *resource);
        virtual void surface_destroy_resource(Resource *resource);

        virtual void surface_destroy(Resource *resource);
        virtual void surface_attach(Resource *resource, struct ::wl_resource *buffer, int32_t x, int32_t y);
        virtual void surface_damage(Resource *resource, int32_t x, int32_t y, int32_t width, int32_t height);
        virtual void surface_frame(Resource *resource, uint32_t callback);
        virtual void surface_set_opaque_region(Resource *resource, struct ::wl_resource *region);
        virtual void surface_set_input_region(Resource *resource, struct ::wl_resource *region);
        virtual void surface_commit(Resource *resource);
        virtual void surface_set_buffer_transform(Resource *resource, int32_t transform);
        virtual void surface_set_buffer_scale(Resource *resource, int32_t scale);
        virtual void surface_damage_buffer(Resource *resource, int32_t x, int32_t y, int32_t width, int32_t height);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_surface_interface m_wl_surface_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_attach(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *buffer,
            int32_t x,
            int32_t y);
        static void handle_damage(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t x,
            int32_t y,
            int32_t width,
            int32_t height);
        static void handle_frame(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t callback);
        static void handle_set_opaque_region(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *region);
        static void handle_set_input_region(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *region);
        static void handle_commit(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_buffer_transform(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t transform);
        static void handle_set_buffer_scale(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t scale);
        static void handle_damage_buffer(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t x,
            int32_t y,
            int32_t width,
            int32_t height);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_surface *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_seat
    {
    public:
        wl_seat(struct ::wl_client *client, int id, int version);
        wl_seat(struct ::wl_display *display, int version);
        wl_seat(struct ::wl_resource *resource);
        wl_seat();

        virtual ~wl_seat();

        class Resource
        {
        public:
            Resource() : seat_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_seat *seat_object;
            wl_seat *object() { return seat_object; } 
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


        enum capability {
            capability_pointer = 1, // the seat has pointer devices
            capability_keyboard = 2, // the seat has one or more keyboards
            capability_touch = 4, // the seat has touch devices
        };

        void send_capabilities(uint32_t capabilities);
        void send_capabilities(struct ::wl_resource *resource, uint32_t capabilities);
        void send_name(const QString &name);
        void send_name(struct ::wl_resource *resource, const QString &name);

    protected:
        virtual Resource *seat_allocate();

        virtual void seat_bind_resource(Resource *resource);
        virtual void seat_destroy_resource(Resource *resource);

        virtual void seat_get_pointer(Resource *resource, uint32_t id);
        virtual void seat_get_keyboard(Resource *resource, uint32_t id);
        virtual void seat_get_touch(Resource *resource, uint32_t id);
        virtual void seat_release(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_seat_interface m_wl_seat_interface;

        static void handle_get_pointer(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id);
        static void handle_get_keyboard(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id);
        static void handle_get_touch(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id);
        static void handle_release(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_seat *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_pointer
    {
    public:
        wl_pointer(struct ::wl_client *client, int id, int version);
        wl_pointer(struct ::wl_display *display, int version);
        wl_pointer(struct ::wl_resource *resource);
        wl_pointer();

        virtual ~wl_pointer();

        class Resource
        {
        public:
            Resource() : pointer_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_pointer *pointer_object;
            wl_pointer *object() { return pointer_object; } 
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
            error_role = 0, // given wl_surface has another role
        };

        enum button_state {
            button_state_released = 0, // the button is not pressed
            button_state_pressed = 1, // the button is pressed
        };

        enum axis {
            axis_vertical_scroll = 0, // vertical axis
            axis_horizontal_scroll = 1, // horizontal axis
        };

        enum axis_source {
            axis_source_wheel = 0, // a physical wheel rotation
            axis_source_finger = 1, // finger on a touch surface
            axis_source_continuous = 2, // continuous coordinate space
            axis_source_wheel_tilt = 3, // a physical wheel tilt
        };

        void send_enter(uint32_t serial, struct ::wl_resource *surface, wl_fixed_t surface_x, wl_fixed_t surface_y);
        void send_enter(struct ::wl_resource *resource, uint32_t serial, struct ::wl_resource *surface, wl_fixed_t surface_x, wl_fixed_t surface_y);
        void send_leave(uint32_t serial, struct ::wl_resource *surface);
        void send_leave(struct ::wl_resource *resource, uint32_t serial, struct ::wl_resource *surface);
        void send_motion(uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y);
        void send_motion(struct ::wl_resource *resource, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y);
        void send_button(uint32_t serial, uint32_t time, uint32_t button, uint32_t state);
        void send_button(struct ::wl_resource *resource, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);
        void send_axis(uint32_t time, uint32_t axis, wl_fixed_t value);
        void send_axis(struct ::wl_resource *resource, uint32_t time, uint32_t axis, wl_fixed_t value);
        void send_frame();
        void send_frame(struct ::wl_resource *resource);
        void send_axis_source(uint32_t axis_source);
        void send_axis_source(struct ::wl_resource *resource, uint32_t axis_source);
        void send_axis_stop(uint32_t time, uint32_t axis);
        void send_axis_stop(struct ::wl_resource *resource, uint32_t time, uint32_t axis);
        void send_axis_discrete(uint32_t axis, int32_t discrete);
        void send_axis_discrete(struct ::wl_resource *resource, uint32_t axis, int32_t discrete);

    protected:
        virtual Resource *pointer_allocate();

        virtual void pointer_bind_resource(Resource *resource);
        virtual void pointer_destroy_resource(Resource *resource);

        virtual void pointer_set_cursor(Resource *resource, uint32_t serial, struct ::wl_resource *surface, int32_t hotspot_x, int32_t hotspot_y);
        virtual void pointer_release(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_pointer_interface m_wl_pointer_interface;

        static void handle_set_cursor(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            struct ::wl_resource *surface,
            int32_t hotspot_x,
            int32_t hotspot_y);
        static void handle_release(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_pointer *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_keyboard
    {
    public:
        wl_keyboard(struct ::wl_client *client, int id, int version);
        wl_keyboard(struct ::wl_display *display, int version);
        wl_keyboard(struct ::wl_resource *resource);
        wl_keyboard();

        virtual ~wl_keyboard();

        class Resource
        {
        public:
            Resource() : keyboard_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_keyboard *keyboard_object;
            wl_keyboard *object() { return keyboard_object; } 
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


        enum keymap_format {
            keymap_format_no_keymap = 0, // no keymap; client must understand how to interpret the raw keycode
            keymap_format_xkb_v1 = 1, // libxkbcommon compatible; to determine the xkb keycode, clients must add 8 to the key event keycode
        };

        enum key_state {
            key_state_released = 0, // key is not pressed
            key_state_pressed = 1, // key is pressed
        };

        void send_keymap(uint32_t format, int32_t fd, uint32_t size);
        void send_keymap(struct ::wl_resource *resource, uint32_t format, int32_t fd, uint32_t size);
        void send_enter(uint32_t serial, struct ::wl_resource *surface, const QByteArray &keys);
        void send_enter(struct ::wl_resource *resource, uint32_t serial, struct ::wl_resource *surface, const QByteArray &keys);
        void send_leave(uint32_t serial, struct ::wl_resource *surface);
        void send_leave(struct ::wl_resource *resource, uint32_t serial, struct ::wl_resource *surface);
        void send_key(uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
        void send_key(struct ::wl_resource *resource, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
        void send_modifiers(uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
        void send_modifiers(struct ::wl_resource *resource, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
        void send_repeat_info(int32_t rate, int32_t delay);
        void send_repeat_info(struct ::wl_resource *resource, int32_t rate, int32_t delay);

    protected:
        virtual Resource *keyboard_allocate();

        virtual void keyboard_bind_resource(Resource *resource);
        virtual void keyboard_destroy_resource(Resource *resource);

        virtual void keyboard_release(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_keyboard_interface m_wl_keyboard_interface;

        static void handle_release(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_keyboard *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_touch
    {
    public:
        wl_touch(struct ::wl_client *client, int id, int version);
        wl_touch(struct ::wl_display *display, int version);
        wl_touch(struct ::wl_resource *resource);
        wl_touch();

        virtual ~wl_touch();

        class Resource
        {
        public:
            Resource() : touch_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_touch *touch_object;
            wl_touch *object() { return touch_object; } 
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


        void send_down(uint32_t serial, uint32_t time, struct ::wl_resource *surface, int32_t id, wl_fixed_t x, wl_fixed_t y);
        void send_down(struct ::wl_resource *resource, uint32_t serial, uint32_t time, struct ::wl_resource *surface, int32_t id, wl_fixed_t x, wl_fixed_t y);
        void send_up(uint32_t serial, uint32_t time, int32_t id);
        void send_up(struct ::wl_resource *resource, uint32_t serial, uint32_t time, int32_t id);
        void send_motion(uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y);
        void send_motion(struct ::wl_resource *resource, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y);
        void send_frame();
        void send_frame(struct ::wl_resource *resource);
        void send_cancel();
        void send_cancel(struct ::wl_resource *resource);
        void send_shape(int32_t id, wl_fixed_t major, wl_fixed_t minor);
        void send_shape(struct ::wl_resource *resource, int32_t id, wl_fixed_t major, wl_fixed_t minor);
        void send_orientation(int32_t id, wl_fixed_t orientation);
        void send_orientation(struct ::wl_resource *resource, int32_t id, wl_fixed_t orientation);

    protected:
        virtual Resource *touch_allocate();

        virtual void touch_bind_resource(Resource *resource);
        virtual void touch_destroy_resource(Resource *resource);

        virtual void touch_release(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_touch_interface m_wl_touch_interface;

        static void handle_release(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_touch *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_output
    {
    public:
        wl_output(struct ::wl_client *client, int id, int version);
        wl_output(struct ::wl_display *display, int version);
        wl_output(struct ::wl_resource *resource);
        wl_output();

        virtual ~wl_output();

        class Resource
        {
        public:
            Resource() : output_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_output *output_object;
            wl_output *object() { return output_object; } 
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


        enum subpixel {
            subpixel_unknown = 0, // unknown geometry
            subpixel_none = 1, // no geometry
            subpixel_horizontal_rgb = 2, // horizontal RGB
            subpixel_horizontal_bgr = 3, // horizontal BGR
            subpixel_vertical_rgb = 4, // vertical RGB
            subpixel_vertical_bgr = 5, // vertical BGR
        };

        enum transform {
            transform_normal = 0, // no transform
            transform_90 = 1, // 90 degrees counter-clockwise
            transform_180 = 2, // 180 degrees counter-clockwise
            transform_270 = 3, // 270 degrees counter-clockwise
            transform_flipped = 4, // 180 degree flip around a vertical axis
            transform_flipped_90 = 5, // flip and rotate 90 degrees counter-clockwise
            transform_flipped_180 = 6, // flip and rotate 180 degrees counter-clockwise
            transform_flipped_270 = 7, // flip and rotate 270 degrees counter-clockwise
        };

        enum mode {
            mode_current = 0x1, // indicates this is the current mode
            mode_preferred = 0x2, // indicates this is the preferred mode
        };

        void send_geometry(int32_t x, int32_t y, int32_t physical_width, int32_t physical_height, int32_t subpixel, const QString &make, const QString &model, int32_t transform);
        void send_geometry(struct ::wl_resource *resource, int32_t x, int32_t y, int32_t physical_width, int32_t physical_height, int32_t subpixel, const QString &make, const QString &model, int32_t transform);
        void send_mode(uint32_t flags, int32_t width, int32_t height, int32_t refresh);
        void send_mode(struct ::wl_resource *resource, uint32_t flags, int32_t width, int32_t height, int32_t refresh);
        void send_done();
        void send_done(struct ::wl_resource *resource);
        void send_scale(int32_t factor);
        void send_scale(struct ::wl_resource *resource, int32_t factor);

    protected:
        virtual Resource *output_allocate();

        virtual void output_bind_resource(Resource *resource);
        virtual void output_destroy_resource(Resource *resource);

        virtual void output_release(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_output_interface m_wl_output_interface;

        static void handle_release(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_output *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_region
    {
    public:
        wl_region(struct ::wl_client *client, int id, int version);
        wl_region(struct ::wl_display *display, int version);
        wl_region(struct ::wl_resource *resource);
        wl_region();

        virtual ~wl_region();

        class Resource
        {
        public:
            Resource() : region_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_region *region_object;
            wl_region *object() { return region_object; } 
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
        virtual Resource *region_allocate();

        virtual void region_bind_resource(Resource *resource);
        virtual void region_destroy_resource(Resource *resource);

        virtual void region_destroy(Resource *resource);
        virtual void region_add(Resource *resource, int32_t x, int32_t y, int32_t width, int32_t height);
        virtual void region_subtract(Resource *resource, int32_t x, int32_t y, int32_t width, int32_t height);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_region_interface m_wl_region_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_add(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t x,
            int32_t y,
            int32_t width,
            int32_t height);
        static void handle_subtract(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t x,
            int32_t y,
            int32_t width,
            int32_t height);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_region *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_subcompositor
    {
    public:
        wl_subcompositor(struct ::wl_client *client, int id, int version);
        wl_subcompositor(struct ::wl_display *display, int version);
        wl_subcompositor(struct ::wl_resource *resource);
        wl_subcompositor();

        virtual ~wl_subcompositor();

        class Resource
        {
        public:
            Resource() : subcompositor_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_subcompositor *subcompositor_object;
            wl_subcompositor *object() { return subcompositor_object; } 
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
            error_bad_surface = 0, // the to-be sub-surface is invalid
        };

    protected:
        virtual Resource *subcompositor_allocate();

        virtual void subcompositor_bind_resource(Resource *resource);
        virtual void subcompositor_destroy_resource(Resource *resource);

        virtual void subcompositor_destroy(Resource *resource);
        virtual void subcompositor_get_subsurface(Resource *resource, uint32_t id, struct ::wl_resource *surface, struct ::wl_resource *parent);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_subcompositor_interface m_wl_subcompositor_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_get_subsurface(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *surface,
            struct ::wl_resource *parent);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_subcompositor *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };

    class Q_WAYLAND_SERVER_WAYLAND_EXPORT wl_subsurface
    {
    public:
        wl_subsurface(struct ::wl_client *client, int id, int version);
        wl_subsurface(struct ::wl_display *display, int version);
        wl_subsurface(struct ::wl_resource *resource);
        wl_subsurface();

        virtual ~wl_subsurface();

        class Resource
        {
        public:
            Resource() : subsurface_object(nullptr), handle(nullptr) {}
            virtual ~Resource() {}

            wl_subsurface *subsurface_object;
            wl_subsurface *object() { return subsurface_object; } 
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
            error_bad_surface = 0, // wl_surface is not a sibling or the parent
        };

    protected:
        virtual Resource *subsurface_allocate();

        virtual void subsurface_bind_resource(Resource *resource);
        virtual void subsurface_destroy_resource(Resource *resource);

        virtual void subsurface_destroy(Resource *resource);
        virtual void subsurface_set_position(Resource *resource, int32_t x, int32_t y);
        virtual void subsurface_place_above(Resource *resource, struct ::wl_resource *sibling);
        virtual void subsurface_place_below(Resource *resource, struct ::wl_resource *sibling);
        virtual void subsurface_set_sync(Resource *resource);
        virtual void subsurface_set_desync(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);
        static void display_destroy_func(struct ::wl_listener *listener, void *data);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::wl_subsurface_interface m_wl_subsurface_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_position(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t x,
            int32_t y);
        static void handle_place_above(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *sibling);
        static void handle_place_below(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *sibling);
        static void handle_set_sync(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_desync(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
        struct DisplayDestroyedListener : ::wl_listener {
            wl_subsurface *parent;
        };
        DisplayDestroyedListener m_displayDestroyedListener;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
