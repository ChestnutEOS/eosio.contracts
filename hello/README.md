# hello

## 1. Actions:
The naming convention is codeaccount::actionname followed by a list of parameters.

Execute a transaction while bypassing regular authorization checks (requires authorization of eosio.wrap which needs to be a privileged account).

### eosio.wrap::exec    executer trx
   - **executer** account executing the transaction
   - **trx** transaction to execute

   Deferred transaction RAM usage is billed to 'executer'


## 2. Installing the eosio.wrap contract


This guide will be using cleos to carry out the process.

### 2.1 Create the eosio.wrap account

#### 2.1.1 Generate the transaction to create the eosio.wrap account
