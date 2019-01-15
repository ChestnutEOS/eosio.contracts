#include <hello/hello.hpp>

namespace eosio {

void hello::hi( name user ) {
    print( user , "\n");
}

} /// namespace eosio

EOSIO_DISPATCH( eosio::hello, (hi) )
