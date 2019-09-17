#include <boost/test/unit_test.hpp>
#include <eosio/chain/contract_table_objects.hpp>
#include <eosio/chain/global_property_object.hpp>
#include <eosio/chain/resource_limits.hpp>
#include <eosio/chain/wast_to_wasm.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fc/log/logger.hpp>
#include <eosio/chain/exceptions.hpp>
#include <Runtime/Runtime.h>

#include "eosio.system_tester.hpp"

using namespace eosio_system;

BOOST_AUTO_TEST_SUITE(eosio_wps_tests)

class eosio_wps_tester : public eosio_system_tester {
public:
    action_result regcommittee(name sender, name committeeman, const string& category, bool is_oversight) {
        return push_action(
            sender,
            N(regcommittee),
            mvo()
            ("committeeman", committeeman)
            ("category", category)
            ("is_oversight", is_oversight)
        );
    }
    
    action_result edcommittee(name sender, name committeeman, const string& category, bool is_oversight) {
        return push_action(
             sender,
             N(edcommittee),
             mvo()
             ("committeeman", committeeman )
             ("category", category )
             ("is_oversight", is_oversight )
        );
    }
    
    action_result rmvcommittee(name sender, name committeeman, const string& category, bool is_oversight) {
        return push_action(
             sender,
             N(rmvcommittee),
             mvo()
             ("committeeman", committeeman)
             ("category", category)
             ("is_oversight", is_oversight)
        );
    }
    
    fc::variant get_committee(const account_name& act) {
        vector<char> data = get_row_by_account(config::system_account_name, config::system_account_name, N(committees), act);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("committee", data, abi_serializer_max_time);
    }
};

BOOST_FIXTURE_TEST_CASE(committee_reg_edit_rmv, eosio_wps_tester) try {
    BOOST_REQUIRE_EQUAL(error("missing authority of eosio"), regcommittee(N(alice1111111), N(alice1111111), "categoryX", true));
    BOOST_REQUIRE_EQUAL(success(), regcommittee(config::system_account_name, N(alice1111111), "categoryX", true));
    BOOST_REQUIRE_EQUAL(wasm_assert_msg("This account has already been registered as a committee"), regcommittee(config::system_account_name, N(alice1111111), "categoryX", true));

    auto committee = get_committee(N(alice1111111));
    BOOST_REQUIRE_EQUAL(committee["category"], "categoryX");
    
    BOOST_REQUIRE_EQUAL(error("missing authority of eosio"), edcommittee(N(alice1111111), N(alice1111111), "categoryZ", true));
    edcommittee(config::system_account_name, N(alice1111111), "categoryY", true);
    committee = get_committee(N(alice1111111));  
    BOOST_REQUIRE_EQUAL(committee["category"], "categoryY");
    
    // TODO test rmvcommittee
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
