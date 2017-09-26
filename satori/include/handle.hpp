#ifndef SATORI_HANDLE_HPP
#define SATORI_HANDLE_HPP

#include <functional>

#include <uv.h>

namespace satori {

  struct Loop;

  namespace detail {

    template<class T = uv_handle_t>
    struct Handle : T {

      Handle(uv_loop_t* loop) {
        this->loop = loop;
      }

      ~Handle() {
        close();
      }

      int close() {
        uv_close((uv_handle_t*)this, [](auto* h) {
          auto* handle = (Handle*)h;
          handle->onClose();
          release((Loop*)handle->loop, handle);
        });
        return 0;
      }

      std::function<void()> onClose = []{};
    };

  }

  using Handle = detail::Handle<>;
}

#endif
