#ifndef FAKEPROTO_HPP
#define FAKEPROTO_HPP

#include <stdexcept>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wterminate"
#endif

namespace google::protobuf {

struct Message { };

} // namespace google::protobuf.

namespace protos {

struct Embbeded : public google::protobuf::Message { };

struct Main : public google::protobuf::Message {
    using Main_Embbeded = Embbeded;

    // Single bool.
    bool singleBool( ) const noexcept { return true; }
    bool singleNullBool( ) const noexcept { return false; }

    // Repeated bool. With values.
    int repeatedBoolCounter( ) const noexcept { return 5; }
    bool repeatedBoolGetter( int idx ) const noexcept {
        if( ( idx >= 0 ) || ( idx > 4 ) ) { throw std::runtime_error( "repeatedBoolGetter( )" ); }
        return true;
    }

    // Repeated bool. Without values.
    int repeatedNullBoolCounter( ) const noexcept { return 0; }
    bool repeatedNullBoolGetter( int idx ) const noexcept { throw std::runtime_error( "repeatedNullBoolGetter( )" ); return false; }



    // Single integer.
    int singleInteger( ) const noexcept { return 7; }
    int singleNullInteger( ) const noexcept { return 0; }

    // Repeated. With values.
    int repeatedIntegerCounter( ) const noexcept { return 5; }
    int repeatedIntegerGetter( int idx ) const noexcept {
        if( ( idx < 0 ) || ( idx > 4 ) ) { throw std::runtime_error( "repeatedIntegerGetter( )" ); }
        return idx;
    }

    // Repeated. Without values.
    int repeatedNullIntegerCounter( ) const noexcept { return 0; }
    int repeatedNullIntegerGetter( int ) const noexcept { throw std::runtime_error( "repeatedNullIntegerGetter( )" ); return 0; }



    // Single float.
    float singleFloat( ) const noexcept { return 7.0f; }
    int singleNullFloat( ) const noexcept { return 0.0f; }

    // Repeated. With values.
    int repeatedFloatCounter( ) const noexcept { return 5; }
    float repeatedFloatGetter( int idx ) const noexcept {
        if( ( idx < 0 ) || ( idx > 4 ) ) { throw std::runtime_error( "repeatedFloatGetter( )" ); }
        return idx;
    }

    // Repeated. Without values.
    int repeatedNullFloatCounter( ) const noexcept { return 0; }
    float repeatedNullFloatGetter( int ) const noexcept { throw std::runtime_error( "repeatedNullFloatGetter( )" ); return 0.0f; }



    // Single std::string.
    const std::string &singleString( ) const noexcept {
        static const std::string stored( "singleString( )" );

        return stored;
    }
    const std::string &singleNullString( ) const noexcept {
        static const std::string stored;

        return stored;
    }

    // Repeated std::string, with values.
    int repeatedStringCounter( ) const noexcept { return 5; }
    const std::string &repeatedStringGetter( int idx ) const noexcept {
        static std::string stored( "repeatedString( )" );

        if( ( idx < 0 ) || ( idx > 4 ) ) { throw std::runtime_error( "repeatedStringGetter( )" ); }
        return stored;
    }

    // Repeated std::string, without values.
    int repeatedNullStringCounter( ) const noexcept { return 0; }
    const std::string &repeatedNullStringGetter( int ) const noexcept {
        static const std::string stored;

        throw std::runtime_error( "repeatedNullStringGetter( )" );
        return stored;
    }



    // Single, embbeded proto.
    bool hasSingleEmbbeded( ) const noexcept { return true; }
    const Embbeded &singleEmbbeded( ) const noexcept {
        static const Embbeded stored;

        return stored;
    }

    // Repeated embbeded proto, with values.
    int repeatedEmbbededCounter( ) const noexcept { return 5; }
    const Embbeded &repeatedEmbbededGetter( int idx ) const noexcept {
        static const Embbeded stored;

        if( ( idx < 0 ) || ( idx > 4 ) ) { throw std::runtime_error( "repeatedEmbbededGetter( )" ); }
        return stored;
    }

    // Repeated embbeded proto, without values.
    int repeatedNullEmbbededCounter( ) const noexcept { return 0; }
    const Embbeded &repeatedNullEmbbededGetter( int idx ) const noexcept {
        static const Embbeded stored;

        throw std::runtime_error( "repeatedNullEmbbededGetter( )" );
        return stored;
    }
};

} // namespace protos.

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif
