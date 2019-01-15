#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include "eosio.system_tester.hpp"

#include "Runtime/Runtime.h"

#include <fc/variant_object.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

class hello_tester : public tester {
public:

   hello_tester() {
      produce_blocks( 2 );

      /* Create test accoutnt */
      create_accounts( { N(alice), N(bob), N(carol), N(hello) } );
      produce_blocks( 2 );

      /* Set code and abi */
      set_code( N(hello), contracts::hello_wasm() );
      set_abi( N(hello), contracts::hello_abi().data() );

      produce_blocks();

      /* Set abi */
      const auto& accnt = control->db().get<account_object,by_name>( N(hello) );
      abi_def abi;
      BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
      abi_ser.set_abi(abi, abi_serializer_max_time);
   }

   /* Define push_action */
   action_result push_action( const account_name& signer, const action_name &name, const variant_object &data ) {
      string action_type_name = abi_ser.get_action_type(name);

      action act;
      act.account = N(hello);
      act.name    = name;
      act.data    = abi_ser.variant_to_binary( action_type_name, data,abi_serializer_max_time );

      return base_tester::push_action( std::move(act), uint64_t(signer));
   }

/****************************************************************************/
/*                                T A B L E S                               */
/****************************************************************************/



/****************************************************************************/
/*                              A C T I O N S                               */
/****************************************************************************/

   action_result hi( account_name user) {

      return push_action( N(hello), N(hi), mvo()
           ( "user", user)
      );
   }

   abi_serializer abi_ser;
};


BOOST_AUTO_TEST_SUITE(hello_tests)

/****************************************************************************/
/*                        S T A R T  T E S T  C A S E S                     */
/****************************************************************************/

BOOST_FIXTURE_TEST_CASE( hi_tests, hello_tester ) try {

   BOOST_REQUIRE_EQUAL( success(), hi( N(alice) ) );
   produce_blocks(1);

} FC_LOG_AND_RETHROW()

/****************************************************************************/
/*                            E N D  T E S T  C A S E S                     */
/****************************************************************************/

BOOST_AUTO_TEST_SUITE_END()

