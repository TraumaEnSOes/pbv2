#include "pbv/AsyncSupport.hpp"

namespace pbv::details {

AsyncManager &AsyncManager::singleton( ) noexcept {
    AsyncManager instance;

    return instance;
}

} // namespace pbv::details.
