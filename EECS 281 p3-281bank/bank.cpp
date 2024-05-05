
// Project ID:292F24D17A4455C1B5133EDD8C7CEAA0C9570A98
#include <getopt.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits>

struct user
{
    // member variables
    uint64_t timestamp;
    std::string userID;
    uint32_t pinNumber;
    uint32_t balance;

    // store all transaction IDs that user was involved in both receiving and sending
    std::vector<int> incomingTransactions;
    std::vector<int> outgoingTransactions;
    // keep track of whether or not user is logged in and at what IPs for placing transactions and logging out
    std::vector<std::string> IPAddresses;
    bool loggedIn = false;

    // constructor
    user(uint64_t t, std::string ID, uint32_t p, uint32_t b) : timestamp(t), userID(ID), pinNumber(p), balance(b)
    {
    }
    // default constructor
    user()
    {
    }
};

struct transaction
{
    int transactionID;
    uint64_t timestampTransation;
    std::string IPAddress;
    std::string senderID;
    std::string receiveID;
    uint32_t amount;
    uint64_t exeDateTransaction;
    char feeType;
    uint32_t feeAmount;

    transaction(int t1, uint64_t t, std::string ip, std::string sID, std::string rID, uint32_t a,
                uint64_t exe, char fType, uint32_t fAmount) : transactionID(t1), timestampTransation(t),
                                                              IPAddress(ip), senderID(sID), receiveID(rID),
                                                              amount(a), exeDateTransaction(exe), feeType(fType), feeAmount(fAmount)
    {
    }

    transaction() {}
};

// transaction comparator
// second one is always the one inserted into pq

// comparator
// double check
// if the timestamp of the new transaction is >= exe date for the top transaction in PQ then all transactions in PQ must be processed before new one is inserted
bool transactionComeBefore(transaction t1, transaction &t2)
{
    return t2.timestampTransation >= t1.exeDateTransaction;
}

class transactionPQOrder
{
public:
    // comparator
    // double check
    // min PQ, smallest Exe date on top
    bool operator()(transaction *t1, transaction *t2)
    {
        // otherwise
        if ((*t2).exeDateTransaction == (*t1).exeDateTransaction)
        {
            return (*t2).transactionID < (*t1).transactionID;
        }
        // min PQ for time, lower time = further up the PQ/needs to be processed first
        // if the new transaction happens earlier than the top most transaction then it needs to be placed first
        return (*t2).exeDateTransaction < (*t1).exeDateTransaction;
    }
};

bool processTransaction(transaction t1, bool print,
                        std::vector<std::pair<uint64_t, int>> &exeDatePairs, uint32_t sendBalance, uint32_t receiveBalance, std::map<std::string, user> &uList)
{

    // one check which type
    // shared
    if (t1.feeType == 's')
    {
        uint32_t sendAmount;
        uint32_t receiveAmount;

        if (t1.feeAmount % 2 == 1)
        {
            // TODO check the math down here
            sendAmount = (t1.amount + (static_cast<uint32_t>(t1.feeAmount / 2) + 1));
            receiveAmount = static_cast<uint32_t>(t1.feeAmount / 2);

            if (sendAmount > sendBalance || receiveAmount > receiveBalance)
            {

                if (print)
                {
                    std::cout << "Insufficient funds to process transaction " << t1.transactionID << ".\n";
                }
                return false;
            }
        }

        else
        {
            sendAmount = static_cast<uint32_t>(t1.amount + (t1.feeAmount / 2));
            receiveAmount = static_cast<uint32_t>(t1.feeAmount / 2);

            if (sendAmount > sendBalance || receiveAmount > receiveBalance)
            {

                if (print)
                {
                    std::cout << "Insufficient funds to process transaction " << t1.transactionID << ".\n";
                }
                return false;
            }
        }

        // checked if able to, yes now process
        // success section
        uList[t1.senderID].balance -= sendAmount;
        uList[t1.receiveID].balance -= receiveAmount;
        uList[t1.receiveID].balance += t1.amount;
        uList[t1.receiveID].incomingTransactions.push_back(t1.transactionID);
        uList[t1.senderID].outgoingTransactions.push_back(t1.transactionID);

        if (print)
        {

            std::cout << "Transaction executed at " << t1.exeDateTransaction << ": $" << t1.amount << " from " << t1.senderID << " to " << t1.receiveID << ".\n";
        }
    }
    else
    {
        // sender only

        if ((t1.feeAmount + t1.amount) > sendBalance)
        {
            if (print)
            {
                std::cout << "Insufficient funds to process transaction " << t1.transactionID << ".\n";
            }
            return false;
        }

        uList[t1.senderID].balance -= (t1.feeAmount + t1.amount);
        uList[t1.receiveID].balance += t1.amount;
        uList[t1.receiveID].incomingTransactions.push_back(t1.transactionID);
        uList[t1.senderID].outgoingTransactions.push_back(t1.transactionID);

        if (print)
        {
            std::cout << "Transaction executed at " << t1.exeDateTransaction << ": $" << t1.amount << " from " << t1.senderID << " to " << t1.receiveID << ".\n";
        }
    }
    exeDatePairs.push_back(std::make_pair(t1.exeDateTransaction, t1.transactionID));

    return true;
}

void processTransactionsInsert(transaction &t1, std::priority_queue<transaction *, std::vector<transaction *>, transactionPQOrder> &pq,
                               bool print,
                               std::vector<std::pair<uint64_t, int>> &exeDatePairs, uint32_t &senderBalance, uint32_t &receiveBalance, std::map<std::string, user> &userList)
{

    for (size_t i = 0; i < pq.size(); i++)
    {
        // process transaction
        processTransaction(*pq.top(), print, exeDatePairs, senderBalance, receiveBalance, userList);
        // no matter if it is a valid/invalid exe we pop after trying to process
        pq.pop();
        // check if transaction comes sooner than top transaction
        if (pq.empty() || !transactionComeBefore(*pq.top(), t1))
        {
            pq.push(&t1);
            break;
        }
    }
};

int main(int argc, char *argv[])
{

    // validate cmd line
    bool verboseFlag = false;

    struct option longOpts[] = {
        {"verbose", no_argument, NULL, 'v'},
        {"file", required_argument, NULL, 'f'},
        {"help", no_argument, NULL, 'h'},
        {nullptr, 0, nullptr, '\0'},
    };

    opterr = false;

    // use for saving the output type if specified
    char *outputArg = nullptr;
    int opt = 0, index = 0;

    while ((opt = getopt_long(argc, argv, "vf:h", longOpts, &index)) != -1)
    {
        switch (opt)
        {
            // verbose
        case 'v':
            verboseFlag = true;
            break;

            // stats
        case 'f':
            outputArg = optarg;
            break;

        case 'h':
            std::cout << "Valid cmds to make  output\n";
            std::cout << "--file -f requires  argument(file name) \n";
            std::cout << "--verbose -v \n";
            std::cout << "--help -h to display this help message";
            exit(0);
            break;

        default:
            // throw an error
            std::cerr << "Error: Unknown option";
            exit(1);
        } // switch
    }     // while

    // read in the registration data and save it

    // open file
    std::ifstream inFile;
    inFile.open(outputArg);

    // line for the next portion
    std::string line = "hello, I am a tst to see if getline is working ";

    // user ID
    std::string userID;

    // pin
    uint32_t pinNumber;

    // container for users, each user will be listed via their userID
    std::map<std::string, user> userList;

    // note need to check if this reads correctly
    while (!inFile.eof())
    {
        // get timeStamp
        getline(inFile, line, '|');
        // remove all instances of : before stoi
        line.erase(remove(line.begin(), line.end(), ':'), line.end());
        uint64_t timeStampAccountOpen = (std::stoull(line));
        line = "";

        // get user ID
        getline(inFile, userID, '|');

        // get pin
        getline(inFile, line, '|');
        pinNumber = static_cast<uint32_t>(std::stoll(line));
        line = "";

        // get balance
        getline(inFile, line);
        uint32_t balance = static_cast<uint32_t>(std::stoll(line));
        line = "";

        // add the user to the list of users
        user u(timeStampAccountOpen, userID, pinNumber, balance);

        userList[userID] = u;

        inFile.peek();
    }

    inFile.close();

    // PQ for transactions
    // need to make a custom comparator and the transactions class

    // using cin
    // this is for reading in data and tossing comments
    std::string placeholder;
    std::string tempBuild;
    std::string junk;
    std::string IPaddress;

    // for transactions

    int transactionID = 0;
    std::string senderID;
    std::string receiveID;
    uint64_t timestampTransation;
    uint64_t timestampPREVTransation = 0;
    uint64_t exeDateTransaction;
    std::string IPTransaction;
    uint32_t amountTransaction;
    char feeSettings;

    // for temp store, for exe and time stamps for transactions
    std::string tempTimeTransaction;
    std::string tempExeDateTransaction;

    // priority queue for transactions
    std::priority_queue<transaction *, std::vector<transaction *>, transactionPQOrder> transactionList;

    // masterlist for transactions
    std::map<int, transaction> masterTransactionList;

    // 1 vectors for query data results exedate, transaction ID pair
    std::vector<std::pair<uint64_t, int>> exeDatePairs;

    // combining query and command section, reading from only one file for both thus it makes sense
    while (std::cin >> placeholder)
    {
        // next reading in the commands

        // tossing comments
        if (placeholder.find("#") != std::string::npos)
        {
            getline(std::cin, junk);
            continue;
        }
        if (placeholder.find("$") != std::string::npos)
        {
            getline(std::cin, junk);
            tempBuild = "";
            break;
        }
        tempBuild += placeholder;
        // login
        if (tempBuild == "login")
        {
            tempBuild = "";
            // grab the passed in userID, pin Number, and IP address
            std::cin >> userID >> pinNumber >> IPaddress;
            // check if userID is apart of map
            if (userList.find(userID) != userList.end())
            {
                //they could try to login to the IP Address twice while they are already logged into said IP Address
                //don't check if they are already logged in b/c can be logged in but at multiple IP
                if (userList[userID].pinNumber == pinNumber  )
                {
                    // set logged in to true for keeping track and add the IP address to the list for keeping track
                    userList[userID].loggedIn = true;
                    userList[userID].IPAddresses.push_back(IPaddress);

                    // printing section
                    if (verboseFlag)
                    {
                        std::cout << "User " << userID << " logged in.\n";
                    }
                }

                else
                {
                    if (verboseFlag)
                    {
                        std::cout << "Failed to log in " << userID << ".\n";
                    }
                }
            }
            else
            {
                if (verboseFlag)
                {
                    std::cout << "Failed to log in " << userID << ".\n";
                }
            }
        }
        // logout
        else if (tempBuild == "out")
        {
            tempBuild = "";
            // grab the userID and the IP address
            std::cin >> userID >> IPaddress;
            // start by checking if the user is even in the map
            if (userList.find(userID) != userList.end())
            {
                // set logged in to true for keeping track and add the IP address to the list for keeping track
                // check if IP address is apart of valid IPs
                // note: check this section, may need to split into 2 if statements and only print if IP address not found
                auto it = std::find(userList[userID].IPAddresses.begin(), userList[userID].IPAddresses.end(), IPaddress);
                if (userList[userID].loggedIn && it != userList[userID].IPAddresses.end())
                {
                    // yes then log out and remove the IP
                    // only state that they are logged out if there are no more IP Addresses, if still there are IPs then they are still logged in
                    // just not at that IP Address
                    userList[userID].IPAddresses.erase(it);
                    if (userList[userID].IPAddresses.empty())
                    {
                        userList[userID].loggedIn = false;
                    }

                    // printing section
                    if (verboseFlag)
                    {
                        std::cout << "User " << userID << " logged out.\n";
                    }
                }
                else
                {
                    if (verboseFlag)
                    {
                        std::cout << "Failed to log out " << userID << ".\n";
                    }
                }

                // print section
            }

            else
            {
                if (verboseFlag)
                {
                    std::cout << "Failed to log out " << userID << ".\n";
                }
            }
        }
        // transactions
        else if (tempBuild == "place")
        {
            tempBuild = "";

            // get the following

            // timestamp for transaction IP Sender ID recipient ID amount exec date transaction fee coverage

            // o if sender only, s if both sender and reciepient, if odd then sender pays more

            // fee calc(actually save that for exe time)

            std::cin >> tempTimeTransaction >> IPTransaction >>
                senderID >> receiveID >> amountTransaction >> tempExeDateTransaction >> feeSettings;

            tempTimeTransaction.erase(remove(tempTimeTransaction.begin(), tempTimeTransaction.end(), ':'), tempTimeTransaction.end());
            timestampTransation = ((std::stoull(tempTimeTransaction)));

            tempExeDateTransaction.erase(remove(tempExeDateTransaction.begin(), tempExeDateTransaction.end(), ':'), tempExeDateTransaction.end());
            exeDateTransaction = ((std::stoull(tempExeDateTransaction)));

            // prechecks that must be done before the main checklist
            //  A place command with a timestamp earlier than the previous place.
            //  A place command which contains an execution date before its own timestamp.
            if (timestampTransation < timestampPREVTransation)
            {

                std::cerr << "Invalid decreasing timestamp in 'place' command.";
                exit(1);
            }

            if (exeDateTransaction < timestampTransation)
            {
                std::cerr << "You cannot have an execution date before the current timestamp.";
                exit(1);
            }

            // checks that must be done

            // exe date - time stamp <= 3
            if (exeDateTransaction - timestampTransation <= 3000000ULL)
            {
                // sender and recipient exists based on registration data
                //  by ID first

                if (userList.find(senderID) != userList.end())
                {
                    if (userList.find(receiveID) != userList.end())
                    {

                        if (exeDateTransaction > userList[senderID].timestamp && exeDateTransaction > userList[receiveID].timestamp)
                        {
                            if (userList[senderID].loggedIn)
                            {
                                if (std::find(userList[senderID].IPAddresses.begin(), userList[senderID].IPAddresses.end(), IPTransaction) != userList[senderID].IPAddresses.end())
                                {
                                    // create a transaction object
                                    uint32_t feeAmount = amountTransaction / 100;

                                    // then correct it
                                    if (feeAmount < 10)
                                    {
                                        feeAmount = 10;
                                    }
                                    if (feeAmount > 450)
                                    {
                                        feeAmount = 450;
                                    }

                                    // next check if there is a discount
                                    // TO DO check if this is correct
                                    //changed order so that overflow not done 5000000000000ULL
                                    if (exeDateTransaction  > (50000000000ULL + (userList[senderID]).timestamp))
                                    {
                                        feeAmount = (feeAmount * 3) / 4;
                                    }

                                    // need to change this constructor line

                                    transaction t = {transactionID, timestampTransation, IPTransaction, senderID, receiveID, amountTransaction, exeDateTransaction, feeSettings, feeAmount};
                                    masterTransactionList[transactionID] = t;

                                    // need to also check if able to process the transaction aka if there is enough funds for the fee and the amount being sent

                                    // check if comes earlier/later than top
                                    if (!transactionList.empty() && transactionComeBefore(*transactionList.top(), t))
                                    {
                                        // if yes then process transactions until it doesnt
                                        // then put transaction in PQ
                                        // grab balance for both users
                                        uint32_t balanceSender = userList[senderID].balance;
                                        uint32_t balanceReceive = userList[receiveID].balance;

                                        processTransactionsInsert(masterTransactionList[transactionID], transactionList, verboseFlag, exeDatePairs, balanceSender, balanceReceive, userList);
                                    }

                                    else
                                    {
                                        // if no then just create object and put in PQ
                                        transactionList.push(&masterTransactionList[transactionID]);
                                    }

                                    // successful queue message
                                    if (verboseFlag)
                                    {
                                        std::cout << "Transaction placed at " << timestampTransation << ": $" << amountTransaction << " from " << senderID << " to " << receiveID << " at " << exeDateTransaction << ".\n";
                                    }

                                    timestampPREVTransation = timestampTransation;
                                    transactionID++;
                                }
                                else
                                {
                                    // failed IP check, fraud section
                                    if (verboseFlag)
                                    {
                                        std::cout << "Fraudulent transaction detected, aborting request.\n";
                                    }
                                }
                            }
                            else
                            {
                                // sender not logged in
                                if (verboseFlag)
                                {
                                    std::cout << "Sender " + senderID + " is not logged in.\n";
                                }
                            }
                        }
                        else
                        {
                            // exe time before either recipient or sender registered
                            if (verboseFlag)
                            {
                                std::cout << "At the time of execution, sender and/or recipient have not registered.\n";
                            }
                        }
                    }
                    else
                    {
                        // recipient doesnt exist by ID
                        if (verboseFlag)
                        {
                            std::cout << "Recipient " + receiveID + " does not exist.\n";
                        }
                    }
                }
                else
                {
                    // sender ID doesnt exist
                    if (verboseFlag)
                    {
                        std::cout << "Sender " + senderID + " does not exist.\n";
                    }
                }
            }
            else
            {
                // failed the exe - time stamp check
                if (verboseFlag)
                {
                    std::cout << "Select a time less than three days in the future.\n";
                }
            }
        }
    }

    // note splitting the queries and the commands up
    // start with immediately reading since the above took care of the line with the $$

    while (!transactionList.empty())
    {
        uint32_t balanceSender = userList[transactionList.top()->senderID].balance;
        uint32_t balanceReceive = userList[transactionList.top()->receiveID].balance;
        processTransaction(*transactionList.top(), verboseFlag, exeDatePairs, balanceSender, balanceReceive, userList);
        transactionList.pop();
    }

    // TODO sort by exeDate, make it increasing!!
    // sort exeDatePairs, not guaranteed to be nondecreasing like timestamps

    // reading in queries
    // try making pairs transaction ID, time it took place,
    // then see if able to grab an upper and lower bound using STL or custom stuffs

    // then use in loop

    // need seperate thing for the execution times like this since it is not guaranteed to be nondecreasing(list transactions section, summarize day)

    // timestamps are guaranteed to be non decreasing so could just use upper and lower bound on transaction map(bank revenue, fees are calced at place time )
    uint64_t tempTimeStamp1;
    uint64_t tempTimeStamp2;
    // use tempBuild for getting userID
    std::vector<std::pair<uint64_t, int>>::iterator lower, upper;

    while (std::cin >> placeholder)
    {
        if (placeholder == "l")
        {
            // grab both exe times for the search
            // note they are given with the colons so need to do something about that
            // see what is up with using upper and lower bound to identify the portion of the vector to iterate over

            // this is to avoid iterating over the map and make this portion a bit faster, no need to look through all the data when I
            // have it isolated already :)

            // after isolating it, perform upper bound on y so it does not include it
            //  perfrom lower bound on x, check if lower bound-1 position is equal to x then start there or just start at the position given by lower bound

            std::cin >> line;
            // remove :
            line.erase(remove(line.begin(), line.end(), ':'), line.end());
            tempTimeStamp1 = (std::stoull(line));
            // timestamp for next day
            std::cin >> line;
            line.erase(remove(line.begin(), line.end(), ':'), line.end());
            tempTimeStamp2 = (std::stoull(line));

            // perform upperbound on tempTimeStamp2
            // perform lowerbound on tempTimeStamp1, check if previous location == x aka tempTimeStamp1

            // problem: I need a garbage element for the pair.

            // then just iterate over the map using iterator

            // note may need to switch these comparators, if pair1 is already in the vector and pair2 is the value we are looking for
            // gets the first value that is >= tempTimeStamp1
            lower = std::lower_bound(exeDatePairs.begin(), exeDatePairs.end(), std::make_pair(tempTimeStamp1, std::numeric_limits<int>::min()));

            // loop starting with lower bound, check if first value is >= tempTimeStamp2
            // yes then stop your done.
            upper = std::lower_bound(exeDatePairs.begin(), exeDatePairs.end(), std::make_pair(tempTimeStamp2, std::numeric_limits<int>::min()));
            int totalNumOfTransactions = 0;
            while (lower != (upper))
            {
                std::string result = (((masterTransactionList[((*lower)).second])).amount > 1) ? " dollars to " : " dollar to ";

                std::cout << (*lower).second << ": " << ((masterTransactionList[((*lower)).second])).senderID << " sent " << ((masterTransactionList[((*lower)).second])).amount
                          << result << ((masterTransactionList[((*lower)).second])).receiveID << " at " << ((masterTransactionList[((*lower)).second])).exeDateTransaction << ".\n";
                totalNumOfTransactions++;
                ++lower;
            }
            std::string result = (totalNumOfTransactions > 1 || totalNumOfTransactions == 0) ? " transactions " : " transaction ";
            std::string result2 = (totalNumOfTransactions > 1 || totalNumOfTransactions == 0) ? " were " : " was ";

            std::cout << "There" << result2 << totalNumOfTransactions << result << "that"<<result2<< "placed between time " << tempTimeStamp1 << " to " << tempTimeStamp2 << ".\n";
        }
        else if (placeholder == "r")
        {
            // grab both time stamps
            // after isolating it, perform upper bound on y so it does not include it
            // perfrom lower bound on x, check if lower bound-1 position is equal to x then start there or just start at the position given by lower bound

            // to do fix
            // grab the time stamps for the
            std::cin >> line;
            // remove :
            line.erase(remove(line.begin(), line.end(), ':'), line.end());
            tempTimeStamp1 = (std::stoull(line));
            // timestamp for next day
            std::cin >> line;
            line.erase(remove(line.begin(), line.end(), ':'), line.end());
            tempTimeStamp2 = (std::stoull(line));

            // perform upperbound on tempTimeStamp2
            // perform lowerbound on tempTimeStamp1, check if previous location == x aka tempTimeStamp1

            // problem: I need a garbage element for the pair.

            // then just iterate over the map using iterator

            // note may need to switch these comparators, if pair1 is already in the vector and pair2 is the value we are looking for
            // gets the first value that is >= tempTimeStamp1
            lower = std::lower_bound(exeDatePairs.begin(), exeDatePairs.end(), std::make_pair(tempTimeStamp1, std::numeric_limits<int>::min()));

            // loop starting with lower bound, check if first value is >= tempTimeStamp2
            // yes then stop your done.
            upper = std::lower_bound(exeDatePairs.begin(), exeDatePairs.end(), std::make_pair(tempTimeStamp2, std::numeric_limits<int>::min()));

            uint64_t feeTotal = 0;
            while (lower != (upper))
            {
                feeTotal += ((masterTransactionList[((*lower)).second])).feeAmount;
                ++lower;
            }

            std::string result;
            // grab years
            result += ((tempTimeStamp2 - tempTimeStamp1) % 1000000000000ULL / 10000000000ULL > 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 1000000000000ULL / 10000000000ULL)) + " years " : ((tempTimeStamp2 - tempTimeStamp1) % 1000000000000ULL / 10000000000ULL == 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 1000000000000ULL / 10000000000ULL)) + " year "
                                                                                                                                                                                                                                                                                       : "";
            // months
            result += ((tempTimeStamp2 - tempTimeStamp1) % 10000000000ULL / 100000000ULL > 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 10000000000ULL / 100000000ULL)) + " months " : ((tempTimeStamp2 - tempTimeStamp1) % 10000000000ULL / 100000000ULL == 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 100000000ULL / 1000000ULL)) + " month "
                                                                                                                                                                                                                                                                            : "";
            // days
            result += ((tempTimeStamp2 - tempTimeStamp1) % 100000000ULL / 1000000ULL > 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 100000000ULL / 1000000ULL)) + " days " : ((tempTimeStamp2 - tempTimeStamp1) % 100000000ULL / 1000000ULL == 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 100000000ULL / 1000000ULL)) + " day "
                                                                                                                                                                                                                                                              : "";
            // hours
            // timestamp % 1000000ull / 10000ull
            result += ((tempTimeStamp2 - tempTimeStamp1) % 1000000ull / 10000ull > 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 1000000ull / 10000ull)) + " hours " : ((tempTimeStamp2 - tempTimeStamp1) % 1000000ULL / 10000ULL == 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 1000000ULL / 10000ULL)) + " hour "
                                                                                                                                                                                                                                                   : "";
            // minutes % 10000ull / 100ull
            result += ((tempTimeStamp2 - tempTimeStamp1) % 10000ull / 100ull > 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 10000ull / 100ull)) + " minutes " : ((tempTimeStamp2 - tempTimeStamp1) % 10000ull / 100ull == 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 10000ull / 100ull)) + " minute "
                                                                                                                                                                                                                                         : "";
            // seconds
            result += ((tempTimeStamp2 - tempTimeStamp1) % 100ull > 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 100ull)) + " seconds" : ((tempTimeStamp2 - tempTimeStamp1) % 100ull == 1) ? std::to_string(((tempTimeStamp2 - tempTimeStamp1) % 100ull)) + " second"
                                                                                                                                                                                                       : "";

            std::cout << "281Bank has collected " << feeTotal << " dollars in fees over " << result << ".\n";
        }

        else if (placeholder == "h")
        {
            std::string userID;
            std::cin >> userID;
            // only user ID
            /// look up user in user list then iterate over the transaction vector in user data
            // then do look up in transactions, need to print out all incoming and outgoing transactions

            // problem, only stores transactions all together no difference
            // solution, split the data into incoming and outgoing, dont forget that a user can send money to themself so always check both for each user

            // then just iterate over both vectors and print

            if (userList.find(userID) != userList.end())
            {
                std::cout << "Customer " << userID << " account summary:\n";
                std::cout << "Balance: $" << userList[userID].balance << "\n";
                std::cout << "Total # of transactions: " << (userList[userID].incomingTransactions.size() + userList[userID].outgoingTransactions.size()) << "\n";

                size_t startPosIncoming;
                size_t startPosOutgoing;

                if (userList[userID].incomingTransactions.size() <= 10)
                {
                    startPosIncoming = 0;
                }
                else
                {
                    startPosIncoming = userList[userID].incomingTransactions.size() - 10;
                }
                if (userList[userID].outgoingTransactions.size() <= 10)
                {
                    startPosOutgoing = 0;
                }
                else
                {
                    startPosOutgoing = userList[userID].outgoingTransactions.size() - 10;
                }

                std::cout << "Incoming " << userList[userID].incomingTransactions.size() << ":\n";
                if (!userList[userID].incomingTransactions.empty())
                {
                    while (startPosIncoming != userList[userID].incomingTransactions.size())
                    {
                        // 2: hjgarcia sent 27 dollars to paoletti at 30001.
                        std::cout << (masterTransactionList[userList[userID].incomingTransactions[startPosIncoming]]).transactionID << ": "
                                  << (masterTransactionList[userList[userID].incomingTransactions[startPosIncoming]]).senderID << " sent " << (masterTransactionList[userList[userID].incomingTransactions[startPosIncoming]]).amount << (((masterTransactionList[userList[userID].incomingTransactions[startPosIncoming]]).amount > 1) ? " dollars to " : " dollar to ") << (masterTransactionList[userList[userID].incomingTransactions[startPosIncoming]]).receiveID << " at " << (masterTransactionList[userList[userID].incomingTransactions[startPosIncoming]]).exeDateTransaction << ".\n";
                        ++startPosIncoming;
                    }
                }

                std::cout << "Outgoing " << userList[userID].outgoingTransactions.size() << ":\n";

                if (!userList[userID].outgoingTransactions.empty())
                {

                    // note: goes out of bounds
                    while (startPosOutgoing != userList[userID].outgoingTransactions.size())
                    {
                        // 2: hjgarcia sent 27 dollars to paoletti at 30001.
                        std::cout << (masterTransactionList[userList[userID].outgoingTransactions[startPosOutgoing]]).transactionID << ": "
                                  << (masterTransactionList[userList[userID].outgoingTransactions[startPosOutgoing]]).senderID
                                  << " sent " << (masterTransactionList[userList[userID].outgoingTransactions[startPosOutgoing]]).amount
                                  << (((masterTransactionList[userList[userID].outgoingTransactions[startPosOutgoing]]).amount > 1) ? " dollars to " : " dollar to ")
                                  << (masterTransactionList[userList[userID].outgoingTransactions[startPosOutgoing]]).receiveID << " at " << (masterTransactionList[userList[userID].outgoingTransactions[startPosOutgoing]]).exeDateTransaction << ".\n";
                        ++startPosOutgoing;
                    }
                }
            }
            else
            {
                std::cout << "User " << userID << " does not exist.\n";
            }
        }

        // note: need to double check if grabbing the right info, it says timestamp in the spec
        else if (placeholder == "s")
        {
            // to do fix
            // grab the time stamps for the
            std::cin >> line;
            uint64_t tempPlaceHolder = 0;
            // remove :
            line.erase(remove(line.begin(), line.end(), ':'), line.end());

            // need to isolate parts of the number real quick then set equal to that
            tempPlaceHolder = (std::stoull(line));
            // years % 1000000000000ULL / 10000000000ULL
            tempTimeStamp1 = (tempPlaceHolder % 1000000000000ULL / 10000000000ULL) * 10000000000ULL;
            // months % 10000000000ULL / 100000000ULL
            tempTimeStamp1 += (tempPlaceHolder % 10000000000ULL / 100000000ULL) * 100000000ULL;
            // days % 100000000ULL / 1000000ULL
            tempTimeStamp1 += (tempPlaceHolder % 100000000ULL / 1000000ULL) * 1000000ULL;
            // timestamp for next day
            tempTimeStamp2 = (tempTimeStamp1 + 1000000ULL);

            // perform upperbound on tempTimeStamp2
            // perform lowerbound on tempTimeStamp1, check if previous location == x aka tempTimeStamp1

            // problem: I need a garbage element for the pair.

            // then just iterate over the map using iterator

            // note may need to switch these comparators, if pair1 is already in the vector and pair2 is the value we are looking for
            // gets the first value that is >= tempTimeStamp1
            lower = std::lower_bound(exeDatePairs.begin(), exeDatePairs.end(), std::make_pair(tempTimeStamp1, std::numeric_limits<int>::min()));
            // loop starting with lower bound, check if first value is >= tempTimeStamp2
            // yes then stop your done.
            upper = std::lower_bound(exeDatePairs.begin(), exeDatePairs.end(), std::make_pair(tempTimeStamp2, std::numeric_limits<int>::min()),
            [](std::pair<uint64_t,int> pair1,std::pair<uint64_t,int> pair2){return pair1.first <= pair2.first;});

            uint64_t feeTotal = 0;
            int totalNumOfTransactions = 0;

            std::cout << "Summary of [" << tempTimeStamp1 << ", " << tempTimeStamp2 << "):\n";
            while (lower != (upper))
            {
                std::string result = ((masterTransactionList[(*lower).second]).amount > 1) ? " dollars to " : " dollar to ";

                std::cout << (*lower).second << ": " << (masterTransactionList[(*lower).second]).senderID << " sent " << (masterTransactionList[(*lower).second]).amount
                          << result << (masterTransactionList[(*lower).second]).receiveID << " at " << (masterTransactionList[(*lower).second]).exeDateTransaction << ".\n";
                          feeTotal += (masterTransactionList[(*lower).second]).feeAmount;
                totalNumOfTransactions++;
                ++lower;
                
            }
      
            
            std::string result = (totalNumOfTransactions > 1 || totalNumOfTransactions == 0) ? " transactions" : " transaction";
            std::string result2 = (totalNumOfTransactions > 1 || totalNumOfTransactions == 0) ? "were" : "was";

            std::cout << "There " << result2 << " a total of " << totalNumOfTransactions << result << ", 281Bank has collected " << feeTotal << " dollars in fees.\n";
        }
    }
    return 0;
}
