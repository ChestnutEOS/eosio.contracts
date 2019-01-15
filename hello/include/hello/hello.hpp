#pragma once

#include <eosiolib/eosio.hpp>

namespace eosio {

class [[eosio::contract("hello")]] hello : public contract {
   public:
      using contract::contract;

      [[eosio::action]]
      void hi( name user );

};

} /// namespace eosio
