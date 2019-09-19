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
    
    action_result rmvcommittee(name sender, name committeeman) {
        return push_action(
             sender,
             N(rmvcommittee),
             mvo()
             ("committeeman", committeeman)
        );
    }

    action_result regreviewer(name sender, name committee, name reviewer, const string& first_name, const string& last_name) {
        return push_action(
                sender,
                N(regreviewer),
                mvo()
                ("committee", committee)
                ("reviewer", reviewer)
                ("first_name", first_name)
                ("last_name", last_name)

        );
    }

    action_result editreviewer(name sender, name committee, name reviewer, const string& first_name, const string& last_name) {
        return push_action(
                sender,
                N(editreviewer),
                mvo()
                ("committee", committee)
                ("reviewer", reviewer)
                ("first_name", first_name)
                ("last_name", last_name)

        );
    }

    action_result rmvreviewer(name sender, name committee, name reviewer) {
        return push_action(
                sender,
                N(rmvreviewer),
                mvo()
                        ("committee", committee)
                        ("reviewer", reviewer)

        );
    }

    action_result regproposer(name sender,
                              name account,
                              const string& first_name,
                              const string& last_name,
                              const string& img_url,
                              const string& bio,
                              const string& country,
                              const string& telegram,
                              const string& website,
                              const string& linkedin) {
        return push_action(
                sender,
                N(regproposer),
                mvo()
                        ("account", account)
                        ("first_name", first_name)
                        ("last_name", last_name)
                        ("img_url", img_url)
                        ("bio", bio)
                        ("country", country)
                        ("telegram", telegram)
                        ("website", website)
                        ("linkedin", linkedin)
        );
    }

    action_result editproposer(name sender,
                              name account,
                              const string& first_name,
                              const string& last_name,
                              const string& img_url,
                              const string& bio,
                              const string& country,
                              const string& telegram,
                              const string& website,
                              const string& linkedin) {
        return push_action(
                sender,
                N(editproposer),
                mvo()
                        ("account", account)
                        ("first_name", first_name)
                        ("last_name", last_name)
                        ("img_url", img_url)
                        ("bio", bio)
                        ("country", country)
                        ("telegram", telegram)
                        ("website", website)
                        ("linkedin", linkedin)
        );
    }

    action_result rmvproposer(name sender,
                              name account) {
        return push_action(
                sender,
                N(rmvproposer),
                mvo()
                        ("account", account)
        );
    }

    action_result regproposal(name sender,
                              name proposer,
                              name committee,
                              uint16_t subcategory,
                              const string& title,
                              const string& summary,
                              const string& project_img_url,
                              const string& description,
                              const string& roadmap,
                              uint64_t duration,
                              const vector<string>& members,
                              const asset& funding_goal,
                              uint32_t total_iterations) {
        return push_action(
                sender,
                N(regproposal),
                mvo()
                        ("proposer", proposer)
                        ("committee", committee)
                        ("subcategory", subcategory)
                        ("title", title)
                        ("summary", summary)
                        ("project_img_url", project_img_url)
                        ("description", description)
                        ("roadmap", roadmap)
                        ("duration", duration)
                        ("members", members)
                        ("funding_goal", funding_goal)
                        ("total_iterations", total_iterations)
        );
    }

    action_result editproposal(name sender,
                              name proposer,
                              name committee,
                              uint16_t subcategory,
                              const string& title,
                              const string& summary,
                              const string& project_img_url,
                              const string& description,
                              const string& roadmap,
                              const vector<string>& members,
                              const asset& funding_goal,
                              uint32_t total_iterations) {
        return push_action(
                sender,
                N(editproposal),
                mvo()
                        ("proposer", proposer)
                        ("committee", committee)
                        ("subcategory", subcategory)
                        ("title", title)
                        ("summary", summary)
                        ("project_img_url", project_img_url)
                        ("description", description)
                        ("roadmap", roadmap)
                        ("members", members)
                        ("funding_goal", funding_goal)
                        ("total_iterations", total_iterations)
        );
    }

    action_result rmvproposal(name sender,
                              name proposer) {
        return push_action(
                sender,
                N(rmvproposal),
                mvo()
                        ("proposer", proposer)
        );
    }

    action_result setwpsenv(name sender, uint32_t total_voting_percent, uint32_t duration_of_voting,
                            uint32_t max_duration_of_funding, uint32_t total_iteration_of_funding) {
        return push_action(
                sender,
                N(setwpsenv),
                mvo()
                        ("total_voting_percent", total_voting_percent)
                        ("duration_of_voting", duration_of_voting)
                        ("max_duration_of_funding", max_duration_of_funding)
                        ("total_iteration_of_funding", total_iteration_of_funding)
        );
    }

    action_result acceptprop(name sender, name reviewer, name proposer) {
        return push_action(
                sender,
                N(acceptprop),
                mvo()
                        ("reviewer", reviewer)
                        ("proposer", proposer)

        );
    }

    action_result rejectprop(name sender, name reviewer, name proposer, const string& reason) {
        return push_action(
                sender,
                N(rejectprop),
                mvo()
                        ("reviewer", reviewer)
                        ("proposer", proposer)
                        ("reason", reason)

        );
    }

    action_result voteproposal(name sender, name voter_name, const std::vector<name>& proposals) {
        return push_action(
                sender,
                N(voteproposal),
                mvo()
                        ("voter_name", voter_name)
                        ("proposals", proposals)
        );
    }

    action_result approve(name sender, name reviewer, name proposer) {
        return push_action(
                sender,
                N(claimfunds),
                mvo()
                        ("reviewer", reviewer)
                        ("proposer", proposer)
        );
    }

    action_result claimfunds(name sender, name account) {
        return push_action(
                sender,
                N(claimfunds),
                mvo()
                        ("account", account)
        );
    }
    
    fc::variant get_committee(const account_name& act) {
        vector<char> data = get_row_by_account(config::system_account_name, config::system_account_name, N(committees), act);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("committee", data, abi_serializer_max_time);
    }

    fc::variant get_reviewer(const account_name& act) {
        vector<char> data = get_row_by_account(config::system_account_name, config::system_account_name, N(reviewers), act);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("reviewer", data, abi_serializer_max_time);
    }

    fc::variant get_proposer(const account_name& act) {
        vector<char> data = get_row_by_account(config::system_account_name, config::system_account_name, N(proposers), act);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("proposer", data, abi_serializer_max_time);
    }

    fc::variant get_proposal(const account_name& act) {
        vector<char> data = get_row_by_account(config::system_account_name, config::system_account_name, N(proposals), act);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("proposal", data, abi_serializer_max_time);
    }
};

BOOST_FIXTURE_TEST_CASE(wpsenv_set, eosio_wps_tester) try {

    BOOST_REQUIRE_EQUAL(error("missing authority of eosio"), setwpsenv(N(alice1111111), 5, 30, 500, 6));
    BOOST_REQUIRE_EQUAL(success(), setwpsenv(config::system_account_name, 5, 30, 500, 6));
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(committee_reg_edit_rmv, eosio_wps_tester) try {

    create_account_with_resources(N(alice1111111), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));

    setwpsenv(config::system_account_name, 5, 30, 500, 6);

    BOOST_REQUIRE_EQUAL(error("missing authority of eosio"), regcommittee(N(alice1111111), N(alice1111111), "categoryX", true));
    BOOST_REQUIRE_EQUAL(success(), regcommittee(config::system_account_name, N(alice1111111), "categoryX", true));
    BOOST_REQUIRE_EQUAL(wasm_assert_msg("This account has already been registered as a committee"), regcommittee(config::system_account_name, N(alice1111111), "categoryX", true));


    produce_blocks(1);
    auto committee = get_committee(N(alice1111111));
    BOOST_REQUIRE_EQUAL(committee["category"], "categoryX");
    
    BOOST_REQUIRE_EQUAL(error("missing authority of eosio"), edcommittee(N(alice1111111), N(alice1111111), "categoryZ", true));
    edcommittee(config::system_account_name, N(alice1111111), "categoryY", true);

    produce_blocks(1);

    committee = get_committee(N(alice1111111));  
    BOOST_REQUIRE_EQUAL(committee["category"], "categoryY");

    BOOST_REQUIRE_EQUAL(error("missing authority of eosio"), rmvcommittee(N(alice1111111), N(alice1111111)));
    BOOST_REQUIRE_EQUAL(success(), rmvcommittee(config::system_account_name, N(alice1111111)));

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(reviewer_reg_edit_rmv, eosio_wps_tester) try {

    create_account_with_resources(N(alice1111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
    create_account_with_resources(N(bob111111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));

    setwpsenv(config::system_account_name, 5, 30, 500, 6);
    regcommittee(config::system_account_name, N(alice1111111), "categoryX", true);

    BOOST_REQUIRE_EQUAL(error("missing authority of alice1111111"),
        regreviewer(N(bob111111111), N(alice1111111), N(bob111111111), "bob", "bob"));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in committee table"),
            regreviewer(N(bob111111111), N(bob111111111), N(bob111111111), "bob", "bob"));

    BOOST_REQUIRE_EQUAL(success(), regreviewer(N(alice1111111), N(alice1111111), N(bob111111111), "bob", "bob"));

    produce_blocks(1);

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("This account has already been registered as a reviewer"),
            regreviewer(N(alice1111111), N(alice1111111), N(bob111111111), "bob", "bob"));

    auto reviewer = get_reviewer(N(bob111111111));
    BOOST_REQUIRE_EQUAL(reviewer["last_name"], "bob");

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in committee table"),
        editreviewer(N(bob111111111), N(bob111111111), N(bob111111111), "bob", "bob"));

    editreviewer(N(alice1111111), N(alice1111111), N(bob111111111), "bob", "smith");

    produce_blocks(1);

    reviewer = get_reviewer(N(bob111111111));
    BOOST_REQUIRE_EQUAL(reviewer["last_name"], "smith");

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in committee table"),
        rmvreviewer(N(bob111111111), N(bob111111111), N(bob111111111)));

    BOOST_REQUIRE_EQUAL(success(), rmvreviewer(N(alice1111111), N(alice1111111), N(bob111111111)));

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(proposer_reg_edit_rmv, eosio_wps_tester) try {

create_account_with_resources(N(user11111111), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
create_account_with_resources(N(user22222222), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));

setwpsenv(config::system_account_name, 5, 30, 500, 6);

BOOST_REQUIRE_EQUAL(error("missing authority of user11111111"),
        regproposer(N(user22222222), N(user11111111), "user", "one", "img_url", "bio", "country", "telegram", "website", "linkedin"));

BOOST_REQUIRE_EQUAL(success(),
        regproposer(N(user11111111), N(user11111111), "user", "one", "img_url", "bio", "country", "telegram", "website", "linkedin"));

BOOST_REQUIRE_EQUAL(wasm_assert_msg("This account has already been registered as a proposer"),
        regproposer(N(user11111111), N(user11111111), "user", "one", "img_url", "bio", "country", "telegram", "website", "linkedin"));

produce_blocks(1);

auto proposer = get_proposer(N(user11111111));

BOOST_REQUIRE_EQUAL(proposer["first_name"], "user");

editproposer(N(user11111111), N(user11111111), "proposer", "one", "img_url", "bio", "country", "telegram", "website", "linkedin");

produce_blocks(1);

proposer = get_proposer(N(user11111111));

BOOST_REQUIRE_EQUAL(proposer["first_name"], "proposer");

BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in proposer table"),
    rmvproposer(N(user22222222), N(user22222222)));

BOOST_REQUIRE_EQUAL(success(), rmvproposer(N(user11111111), N(user11111111)));

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(proposal_reg_edit_rmv, eosio_wps_tester) try {

    create_account_with_resources(N(alice1111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
    create_account_with_resources(N(bob111111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
    create_account_with_resources(N(user11111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
    create_account_with_resources(N(user22222222), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));

setwpsenv(config::system_account_name, 5, 30, 500, 6);
regcommittee(config::system_account_name, N(alice1111111), "categoryX", true);
regreviewer(N(bob111111111), N(alice1111111), N(bob111111111), "bob", "bob");
regproposer(N(user11111111), N(user11111111), "user", "one", "img_url", "bio", "country", "telegram", "website", "linkedin"));

BOOST_REQUIRE_EQUAL(error("missing authority of user11111111"),
        regproposal(N(user22222222), N(user11111111), N(alice1111111), 1, "title", "summary", "project_img_url",
                    "description", "roadmap", 30, {"user"}, core_sym::from_string("9000.0000"), 3));

BOOST_REQUIRE_EQUAL(success(),
        regproposal(N(user11111111), N(user11111111), N(alice1111111), 1, "title", "summary", "project_img_url",
                    "description", "roadmap", 30, {"user"}, core_sym::from_string("9000.0000"), 3));

produce_blocks(1);

BOOST_REQUIRE_EQUAL(wasm_assert_msg("This account has already registered a proposal"),
        regproposal(N(user11111111), N(user11111111), N(alice1111111), 1, "title", "summary", "project_img_url",
                    "description", "roadmap", 30, {"user"}, core_sym::from_string("9000.0000"), 3));

auto proposal = get_proposal(N(user11111111));

BOOST_REQUIRE_EQUAL(proposal["title"], "title");

editproposal(N(user11111111), N(user11111111), N(alice1111111), 1, "First proposal", "summary", "project_img_url",
"description", "roadmap", {"user"}, core_sym::from_string("9000.0000"), 3);

produce_blocks(1);

proposal = get_proposal(N(user11111111));

BOOST_REQUIRE_EQUAL(proposal["title"], "First proposal");

BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in proposal table"), rmvproposal(N(user22222222), N(user22222222)));

BOOST_REQUIRE_EQUAL(success(), rmvproposal(N(user11111111), N(user11111111)));

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(reviewer_accept_reject, eosio_wps_tester) try {

create_account_with_resources(N(alice1111111), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
create_account_with_resources(N(bob111111111), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
create_account_with_resources(N(user11111111), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
create_account_with_resources(N(user22222222), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));

setwpsenv(config::system_account_name, 5, 30, 500, 6);
regcommittee(config::system_account_name, N(alice1111111), "categoryX", true);
regreviewer(N(bob111111111), N(alice1111111), N(bob111111111), "bob", "bob");
regproposer(N(user11111111), N(user11111111), "user", "one", "img_url", "bio", "country", "telegram", "website", "linkedin"));
regproposal(N(user11111111), N(user11111111), N(alice1111111), 1, "title", "summary", "project_img_url",
"description", "roadmap", 30, {"user"}, core_sym::from_string("9000.0000"), 3);

BOOST_REQUIRE_EQUAL(error("missing authority of bob111111111"),
        acceptprop(N(user11111111), N(bob111111111), N(user11111111)));

BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in reviewers table"),
        acceptprop(N(user11111111), N(user11111111), N(user11111111)));

BOOST_REQUIRE_EQUAL(error("missing authority of bob111111111"),
        rejectprop(N(user11111111), N(bob111111111), N(user11111111), "reason"));

BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in reviewers table"),
        rejectprop(N(user11111111), N(user11111111), N(user11111111), "reason"));

BOOST_REQUIRE_EQUAL(success(),
        rejectprop(N(bob111111111), N(bob111111111), N(user11111111), "reason"));

produce_blocks(1);

auto proposal = get_proposal(N(user11111111));

BOOST_REQUIRE_EQUAL(proposal["status"], 2);

BOOST_REQUIRE_EQUAL(success(), rmvproposal(N(user11111111), N(user11111111)));

produce_blocks(1);

regproposal(N(user11111111), N(user11111111), N(alice1111111), 1, "title", "summary", "project_img_url",
"description", "roadmap", 30, {"user"}, core_sym::from_string("9000.0000"), 3);

produce_blocks(1);

BOOST_REQUIRE_EQUAL(success(), acceptprop(N(user11111111), N(user11111111)));

produce_blocks(1);

proposal = get_proposal(N(user11111111));

BOOST_REQUIRE_EQUAL(proposal["status"], 3);

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(proposal_vote_claim, eosio_wps_tester) try {

    create_account_with_resources(N(alice1111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
    create_account_with_resources(N(bob111111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
    create_account_with_resources(N(user11111111), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));
    create_account_with_resources(N(user22222222), config::system_account_name, core_sym::from_string("100.0000"), false,
    core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));

    cross_15_percent_threshold();

    setwpsenv(config::system_account_name, 5, 30, 500, 6);
    regcommittee(config::system_account_name, N(alice1111111), "categoryX", true);
    regreviewer(N(bob111111111), N(alice1111111), N(bob111111111), "bob", "bob");
    regproposer(N(user11111111), N(user11111111), "user", "one", "img_url", "bio", "country", "telegram", "website", "linkedin"));
    regproposal(N(user11111111), N(user11111111), N(alice1111111), 1, "title", "summary", "project_img_url",
    "description", "roadmap", 30, {"user"}, core_sym::from_string("9000.0000"), 3);
    acceptprop(N(user11111111), N(user11111111));


    create_account_with_resources(N(smallvoter11), config::system_account_name, core_sym::from_string("100.0000"), false,
core_sym::from_string("10.0000"), core_sym::from_string("10.0000"));

    create_account_with_resources(N(bigvoter1111), config::system_account_name, core_sym::from_string("10000.0000"), false,
core_sym::from_string("50000000.0000"), core_sym::from_string("50000000.0000"));

    produce_blocks(1);

    BOOST_REQUIRE_EQUAL(error("missing authority of smallvoter11"), voteproposal(N(user11111111), N(smallvoter11), {N(user11111111)}));

    BOOST_REQUIRE_EQUAL(success(), voteproposal(N(smallvoter11), N(smallvoter11), {N(user11111111)}));

    produce_blocks(1);

    auto proposal = get_proposal(N(user11111111));

    BOOST_REQUIRE_EQUAL(proposal["status"], 3);

    BOOST_REQUIRE_EQUAL(success(), voteproposal(N(bigvoter1111), N(bigvoter1111), {N(user11111111)}));

    produce_blocks(1);

    proposal = get_proposal(N(user11111111));

    BOOST_REQUIRE_EQUAL(proposal["status"], 4);

    BOOST_REQUIRE_EQUAL(error("missing authority of bob111111111"),
        approve(N(user11111111), N(bob111111111), N(user11111111)));

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Account not found in reviewers table"),
        approve(N(user11111111), N(user11111111), N(user11111111)));

    BOOST_REQUIRE_EQUAL(success(),
        approve(N(bob111111111), N(bob111111111), N(user11111111), "reason"));

    produce_blocks(1);

    proposal = get_proposal(N(user11111111));

    BOOST_REQUIRE_EQUAL(proposal["status"], 5);

    produce_blocks(1);

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Please wait until the end of this interval to claim funding"), claimfunds(N(user11111111), N(user11111111)));

    produce_block( fc::days(10) );

    BOOST_REQUIRE_EQUAL(error("missing authority of user11111111"), claimfunds(N(user22222222), N(user11111111)));

    BOOST_REQUIRE_EQUAL(success(), claimfunds(N(user11111111), N(user11111111)));

    produce_blocks(1);

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Please wait until the end of this interval to claim funding"), claimfunds(N(user11111111), N(user11111111)));

    produce_block( fc::days(10) );

    BOOST_REQUIRE_EQUAL(success(), claimfunds(N(user11111111), N(user11111111)));

    produce_blocks(1);

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Please wait until the end of this interval to claim funding"), claimfunds(N(user11111111), N(user11111111)));

    produce_block( fc::days(10) );

    BOOST_REQUIRE_EQUAL(success(), claimfunds(N(user11111111), N(user11111111)));

    produce_blocks(1);

    proposal = get_proposal(N(user11111111));

    BOOST_REQUIRE_EQUAL(proposal["status"], 6);

    BOOST_REQUIRE_EQUAL(wasm_assert_msg("Proposal::status is not PROPOSAL_STATUS::APPROVED"), claimfunds(N(user11111111), N(user11111111)));

} FC_LOG_AND_RETHROW()


BOOST_AUTO_TEST_SUITE_END()
