#include "pbv/Rules.hpp"

namespace pbv::details {

void BasicRule::updateResults( ValidationResult &result, int evaluated ) {
    m_evaluated += evaluated;
    m_success += result.result;
    m_traces += result.traces;
}

} // namespace pbv::details.
