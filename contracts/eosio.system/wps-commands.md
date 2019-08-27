# WPS Test Commands

Below are the `cleos` commands to test the core actions of the WAX Worker Proposal System.

```
./testeos.sh push action eosio setwpsenv '[5, 30, 180, 6]' -p eosio

./testeos.sh push action eosio regcommittee '["testertester", "General", 1]' -p eosio

./testeos.sh push action eosio regreviewer '["testertester", "testtesttest", "Jae", "Chung"]' -p testertester

./testeos.sh push action eosio regproposer '["testproposer", "h", "c", "h", "c", "h", "cdfhsfh", "h", "c"]' -p testproposer

./testeos.sh push action eosio regproposal '["testproposer", "testertester", "1", "hi", "hi", "hi", "hi", "hi", 30, ["Jae"], "100.00000000 WAX", 6]' -p testproposer

./testeos.sh push action eosio acceptprop '["testtesttest", "testproposer"]' -p testtesttest

./testeos.sh push action eosio voteproposal '["testertester", ["testproposer"]]' -p testertester

./testeos.sh push action eosio claimfunds '["testproposer", "testproposer"]' -p testproposer

./testeos.sh push action eosio rmvproposal '["testproposer"]' -p testproposer
```
