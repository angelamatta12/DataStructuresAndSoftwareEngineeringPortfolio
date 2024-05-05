// Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
#include "P2random.h"
#include <string>
#include <getopt.h>
#include <limits.h>
#include <utility>
#include <iostream>
#include <sstream>
#include <deque>
#include <queue>

// zombie struct section
// note: since we are using ptrs, need a destructor!!!
struct zombie
{
    std::string name;
    uint32_t distance;
    uint32_t speed;
    uint32_t health;
    // to start
    uint32_t roundLasted = 1;
    bool dead = false;
};

// ETA calc for priority queue section
std::uint32_t ETAcalc(zombie &z)
{
    uint32_t ETA = (z.distance) / (z.speed);
    return ETA;
}

// move zombie function
void moveZombie(zombie &z, bool print)
{
    if (!z.dead)
        z.distance -= std::min(z.distance, z.speed);

    if (print && !z.dead)
    {
        std::cout << "Moved: " << z.name << " (distance: " << z.distance << ", speed: " << z.speed << ", health: " << z.health << ")\n";
    }
}

// update round lasted
void updateZombieRound(zombie &z)
{
    if (!z.dead)
        z.roundLasted++;
}

void randomGenZombie(zombie &z, bool print)
{
    z.name = P2random::getNextZombieName();
    z.distance = P2random::getNextZombieDistance();
    z.speed = P2random::getNextZombieSpeed();
    z.health = P2random::getNextZombieHealth();
    if (print)
    {
        std::cout << "Created: " << z.name << " (distance: " << z.distance << ", speed: " << z.speed << ", health: " << z.health << ")\n";
    }
}

void namedGenZombie(zombie &z, std::string name, uint32_t dist,
                    uint32_t speed, uint32_t health, bool print)
{
    z.name = name;
    z.distance = dist;
    z.speed = speed;
    z.health = health;
    if (print)
    {
        std::cout << "Created: " << z.name << " (distance: " << z.distance << ", speed: " << z.speed << ", health: " << z.health << ")\n";
    }
}

class zombie_comparator_class_PQ_attack
{
public:
    // comparator
    // double check
    bool operator()(zombie *o1, zombie *o2)
    {
        // want to grab the one with
        // lowest ETA
        uint32_t ETACalcz1 = ETAcalc((*o1));
        uint32_t ETACalcz2 = ETAcalc((*o2));
        // lowest ETA
        // if second zombie is lower, it takes priority
        // first zombie is typically the one already in the PQ
        if (ETACalcz2 < ETACalcz1)
        {
            return true;
        }
        // equal ETA, lowest health
        else if (ETACalcz2 == ETACalcz1 && o2->health < o1->health)
        {
            return true;
        }
        // equal ETA, equal health, who comes first alphabetically
        else if (ETACalcz2 == ETACalcz1 && o2->health == o1->health)
        {
            return o2->name < o1->name;
        }

        return false;
    }
};

class zombie_comparator_class_most_active
{
public:
    // comparator
    // double check
    bool operator()(zombie *o1, zombie *o2)
    {
        if (o2->roundLasted > o1->roundLasted)
            return true;

        else if (o2->roundLasted == o1->roundLasted)
            return o2->name < o1->name;

        return false;
    }
};

class zombie_comparator_class_least_active
{
public:
    // comparator
    // double check
    bool operator()(zombie *o1, zombie *o2)
    {
        if (o2->roundLasted < o1->roundLasted)
            return true;

        else if (o2->roundLasted == o1->roundLasted)
            return o2->name < o1->name;

        return false;
    }
};
class zombie_comparator_class_least_active_dble_ptr
{
public:
    // comparator
    // double check
    bool operator()(zombie **o1, zombie **o2)
    {
        if ((**o2).roundLasted < (**o1).roundLasted)
            return true;

        else if ((**o2).roundLasted == (**o1).roundLasted)
            return (**o2).name < (**o1).name;

        return false;
    }
};

int main(int argc, char *argv[])
{

    // validate cmd line
    bool verboseFlag = false;
    bool statFlag = false;
    bool medianFlag = false;

    struct option longOpts[] = {
        {"verbose", no_argument, NULL, 'v'},
        {"median", no_argument, NULL, 'm'},
        {"statistics", required_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {nullptr, 0, nullptr, '\0'},
    };

    opterr = false;

    // use for saving the output type if specified
    char *outputArg = nullptr;
    int opt = 0, index = 0;

    while ((opt = getopt_long(argc, argv, "vs:mh", longOpts, &index)) != -1)
    {
        switch (opt)
        {
            // verbose
        case 'v':
            verboseFlag = true;
            break;

            // stats
        case 's':
            statFlag = true;
            outputArg = optarg;
            break;

            // median
        case 'm':
            medianFlag = true;
            break;

        case 'h':
            std::cout << "Valid cmds to make game output\n";
            std::cout << "--statistics -s \n";
            std::cout << "--verbose -v \n";
            std::cout << "--median -m \n";
            std::cout << "--help -h to display this help message";
            exit(0);
            break;

        default:
            // throw an error
            std::cerr << "Error: Unknown option";
            exit(1);
        } // switch
    }     // while

    std::stringstream ss;

    uint32_t quiverCapacity;
    uint32_t randSeed;
    uint32_t maxRandDist;
    uint32_t maxRandSpeed;
    uint32_t maxRandHealth;
    bool stopPop = true;

    char placeholder;
    std::string tempBuild;
    std::string junk;
    std::string line;

    while (stopPop && std::cin >> placeholder)
    {
        if (placeholder == '#')
        {
            getline(std::cin, junk);
            continue;
        }
        tempBuild += placeholder;

        if (tempBuild == "quiver-capacity:")
        {
            tempBuild = "";
            // grab the num and have it stored
           std::cin >> quiverCapacity;
        }
        else if (tempBuild == "random-seed:")
        {
            tempBuild = "";
            // grab the num and have it stored
          
            std::cin >> randSeed;
     
        }
        else if (tempBuild == "max-rand-distance:")
        {
            tempBuild = "";
            std::cin >> maxRandDist;
        }
        else if (tempBuild == "max-rand-speed:")
        {
            tempBuild = "";
            // grab the num and have it stored

            std::cin >> maxRandSpeed;

        }
        else if (tempBuild == "max-rand-health:")
        {
            tempBuild = "";
            // grab the num and have it stored
 
            std::cin >> maxRandHealth;

            stopPop = false;
        }
        else
        {
            continue;
        }
    }

    // init the rand zombie gen section
    P2random::initialize(randSeed, maxRandDist, maxRandSpeed, maxRandHealth);

    // flags and other necesary vars to be altered in loop
    // flag for run next round/grab next round
    bool flagNotDead = true;
    bool grabRound = true;
    size_t count = 1;
    uint32_t quiver;

    // need to see if order is based on earlier rounds first or later rounds first
    std::deque<zombie> masterlist;
    // for printing out zombies, first N zombies, last N zombies, able to traverse both directions, pushback for updating
    std::deque<zombie *> deadZombie;

    // attack order pq again
    std::priority_queue<zombie *, std::vector<zombie *>, zombie_comparator_class_PQ_attack> pqAttack;

    stopPop = true;
    uint32_t roundNumber;
    size_t randZombieTotNumber;
    size_t namedZombieTotNumber;

    zombie ztempKiller;

    // while loop to run the check list/rounds/game, stop if dead
    while (flagNotDead)
    {
        if (grabRound)
        {
            while (stopPop && std::cin >> placeholder)
            {
                tempBuild += placeholder;
                if (tempBuild == "---")
                {
                    tempBuild = "";
                    continue;
                }
                if (tempBuild == "round:")
                {
                    tempBuild = "";
                    // grab the num and have it stored
                    (getline(std::cin, line));
                    ss << line;
                    ss >> roundNumber;
                    ss.clear();
                    ss.str("");
                }
                else if (tempBuild == "random-zombies:")
                {
                    tempBuild = "";
                    // grab the num and have it stored
                    getline(std::cin, line);
                    ss << line;
                    ss >> randZombieTotNumber;
                    ss.clear();
                    ss.str("");
                }
                else if (tempBuild == "named-zombies:")
                {
                    tempBuild = "";
                    // grab the num and have it stored
                    getline(std::cin, line);
                    ss << line;
                    ss >> namedZombieTotNumber;
                    ss.clear();
                    ss.str("");
                    stopPop = false;
                }
                else
                {
                    continue;
                }
            }
            grabRound = false;
            stopPop = true;
        }

        // print the round for verbose
        if (verboseFlag)
        {
            std::cout << "Round: " << count << "\n";
        }

        // refill quiver
        quiver = quiverCapacity;

        // check if zombies are present
        if (masterlist.size() != 0)
        {
            bool grabbedZombieKiller = false;
            // move zombies, update zombies(rounds alive), if any attack/dist = 0, then save the first one for printing
            // concerned that this might be inefficient for runtime, just use it for now
            for (size_t i = 0; i < masterlist.size(); i++)
            {
                if (!masterlist[i].dead)
                {
                    // move
                    moveZombie(masterlist[i], verboseFlag);
                    // update rounds
                    updateZombieRound(masterlist[i]);
                }
                // check if zombie reached player, and use a flag so that you dont grab multiple, just one
                if (!masterlist[i].dead && !grabbedZombieKiller && masterlist[i].distance == 0)
                {
                    // note need to program assignment operator
                    ztempKiller = masterlist[i];
                    flagNotDead = false;
                    grabbedZombieKiller = true;
                }
            }
        }

        // gen zombies
        // if round not skipped aka have a counter starting, if counter == the round number we grabbed
        // then gen zombies or if cin.fail()-> yes then dont gen zombies
        // set flag to true in here
        if (count == roundNumber)
        {

            grabRound = true;

            for (uint32_t i = 0; i < randZombieTotNumber; i++)
            {
                zombie z;
                randomGenZombie(z, verboseFlag);
                masterlist.push_back(z);
                zombie *zptr = &masterlist.back();
                pqAttack.push(zptr);
            }
            for (uint32_t i = 0; i < namedZombieTotNumber; i++)
            {
                std::string zomName;
                std::string junk;
                uint32_t distanceZ;
                uint32_t speedZ;
                uint32_t healthZ;
                std::cin >> zomName >> junk >> distanceZ >> junk >> speedZ >> junk >> healthZ;
                zombie z;
                namedGenZombie(z, zomName, distanceZ, speedZ, healthZ, verboseFlag);
                masterlist.push_back(z);
                zombie *zptr = &masterlist.back();
                pqAttack.push(zptr);
            }
        }

        // attack
        // check if we are dead
        if (!flagNotDead)
        {
            break;
        }
        else
        {

            // no then do the following:
            // pop the pq
            // 1 arrow = 1 damage
            // Prioritize shooting the zombie with the lowest ETA. You may shoot the same zombie with several arrows during a round, but do not continue to shoot a zombie that has been destroyed (i.e. after its health has reached zero).

            // grab the first item in priority queue
            //  run a loop based on number of arrows in quiver
            while (quiver != 0 && !pqAttack.empty())
            {
                // while loop runs, shoot at zombie until zombie health = 0 or until out of arrows
                // if zombie health = 0, mark as dead in data, push back into list of dead zombies
                // pop the front of pq if zombie is dead, have continue statement after pop so it will grab the next zombie and start the cycle all over
                if (pqAttack.top()->health > quiver)
                {
                    (pqAttack.top()->health) -= quiver;
                    quiver = 0;
                }

                else if (pqAttack.top()->health <= quiver)
                {
                    quiver -= pqAttack.top()->health;
                    pqAttack.top()->health = 0;
                }

                if (pqAttack.top()->health == 0)
                {
                    pqAttack.top()->dead = true;
                    if (verboseFlag)
                    {
                        std::cout << "Destroyed: " << pqAttack.top()->name << " (distance: " << pqAttack.top()->distance << ", speed: " << pqAttack.top()->speed << ", health: " << pqAttack.top()->health << ")\n";
                    }
                    deadZombie.push_back((pqAttack.top()));
                    pqAttack.pop();
                    continue;
                }
            }
        }

        if (medianFlag)
        {
            if (deadZombie.size() != 0)
            {

                std::priority_queue<zombie *, std::vector<zombie *>, zombie_comparator_class_least_active> pqLeastMedian;
                // populate least median
                for (size_t i = 0; i < deadZombie.size(); i++)
                {
                    pqLeastMedian.push(deadZombie[i]);
                }

                // counter
                uint32_t countMedian = 0;
                // initial PQ size
                size_t initPQSize = pqLeastMedian.size();
                uint32_t tempMed;
                // check if 1
                if (pqLeastMedian.size() == 1)
                {
                    tempMed = pqLeastMedian.top()->roundLasted;
                }
                else if (deadZombie.size() % 2 == 0)
                {
                    // if even, pop until first (size/2) -1 then (size/2)
                    uint32_t z1RoundLasted;
                    uint32_t z2RoundLasted;
                    while (countMedian < ((initPQSize / 2) - 1))
                    {
                        pqLeastMedian.pop();
                        countMedian++;
                    }

                    z1RoundLasted = pqLeastMedian.top()->roundLasted;
                    pqLeastMedian.pop();
                    z2RoundLasted = pqLeastMedian.top()->roundLasted;
                    tempMed = (z1RoundLasted + z2RoundLasted) / 2;
                }
                else
                {
                    // if odd, pop until size/2
                    while (countMedian < ((initPQSize / 2)))
                    {
                        pqLeastMedian.pop();
                        countMedian++;
                    }
                    tempMed = pqLeastMedian.top()->roundLasted;
                }
                std::cout << "At the end of round " << count << ", the median zombie lifetime is " << tempMed << "\n";
            }
        }

        // note need to check if I won and that there are no more zombies to gen
        if (std::cin.eof() && pqAttack.empty())
        {
            break;
        }
        count++;
    }

    // output for winning/losing section

    if (flagNotDead)
    {
        std::cout << "VICTORY IN ROUND " << count << "! " << (deadZombie[(deadZombie.size() - 1)]->name) << " was the last zombie.\n";
    }
    else
    {
        std::cout << "DEFEAT IN ROUND " << (count) << "! " << ztempKiller.name << " ate your brains!\n";
    }

    if (statFlag)
    {

        std::cout << "Zombies still active: " << (pqAttack.size()) << "\n";

        // least active vs. most active, need to see if this is  both alive/dead zombies
        std::priority_queue<zombie *, std::vector<zombie *>, zombie_comparator_class_most_active> pqMost;

        // pq for this one, 2 sorts for this, one used to pop it with most active, one for least active

        std::priority_queue<zombie *, std::vector<zombie *>, zombie_comparator_class_least_active> pqLeast;

        for (size_t i = 0; i < masterlist.size(); i++)
        {
            zombie *z = &masterlist[i];
            pqLeast.push(z);
            pqMost.push(z);
        }

        // check if N exceeds the number of zombies in either container
        if (static_cast<uint32_t>(atoi(outputArg)) >= deadZombie.size())
        {
            // yes then print all zombies in each

            // ie, print from front for first zombies dead
            std::cout << "First zombies killed:\n";
            for (size_t i = 0; i < deadZombie.size(); i++)
            {
                size_t order = i + 1;
                std::cout << deadZombie[i]->name << " " << order << "\n";
            }
            std::cout << "Last zombies killed:\n";
            // print from back for last zombies dead
            size_t count = deadZombie.size() - 1;
            size_t countOrder;
            while (count != SIZE_MAX)
            {
                countOrder = count + 1;
                std::cout << deadZombie[count]->name << " " << countOrder << "\n";
                if (count == 0)
                {
                    break;
                }
                count--;
            }
        }

        else
        {
            // no then
            // print the first N zombies dead
            std::cout << "First zombies killed:\n";
            for (size_t i = 0; i < static_cast<uint32_t>(atoi(outputArg)); i++)
            {
                size_t order = i + 1;
                std::cout << deadZombie[i]->name << " " << order << "\n";
            }

            // print the last N zombies dead
            std::cout << "Last zombies killed:\n";
            // print from back for last zombies dead
            size_t count = deadZombie.size() - 1;
            size_t countLoop = 0;
            int countOrder = atoi(outputArg);
            while (countLoop < static_cast<uint32_t>(atoi(outputArg)))
            {

                std::cout << deadZombie[count]->name << " " << countOrder << "\n";

                if (count == 0)
                {
                    break;
                }
                count--;
                countLoop++;
                countOrder--;
            }
        }

        // need to check separately

        if (static_cast<uint32_t>(atoi(outputArg)) >= masterlist.size())
        {

            std::cout << "Most active zombies:\n";
            while (!pqMost.empty())
            {
                std::cout << pqMost.top()->name << " " << pqMost.top()->roundLasted << "\n";
                pqMost.pop();
            }
            std::cout << "Least active zombies:\n";
            while (!pqLeast.empty())
            {
                std::cout << pqLeast.top()->name << " " << pqLeast.top()->roundLasted << "\n";
                pqLeast.pop();
            }
        }

        else
        {

            std::cout << "Most active zombies:\n";
            for (size_t i = 0; i < static_cast<uint32_t>(atoi(outputArg)); i++)
            {
                std::cout << pqMost.top()->name << " " << pqMost.top()->roundLasted << "\n";
                pqMost.pop();
            }
            std::cout << "Least active zombies:\n";
            for (size_t i = 0; i < static_cast<uint32_t>(atoi(outputArg)); i++)
            {
                std::cout << pqLeast.top()->name << " " << pqLeast.top()->roundLasted << "\n";
                pqLeast.pop();
            }
        }
    }

    return 0;
}