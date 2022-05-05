#include "pbv/TracesStore.hpp"

namespace pbv {

void TracesStore::errors2Warnings( ) noexcept {
    if( !m_traces.empty( ) ) {
        for( auto &trace : m_traces ) {
            if( trace.level == TraceLevel::ERROR ) {
                trace.level = TraceLevel::WARNING;
            }
        }
    }
}

} // namespace pbv.
