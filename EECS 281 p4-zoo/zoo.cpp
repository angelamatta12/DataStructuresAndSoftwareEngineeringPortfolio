// project id: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
#include <getopt.h>
#include <limits.h>
#include <utility>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <cstring>
#include <numeric>

double calcDist(int firstCoord, int secCoord, const std::vector<std::pair<int32_t, int32_t>> &coord)
{

    double xsubtraction = (coord[static_cast<size_t>(firstCoord)].first - coord[static_cast<size_t>(secCoord)].first);
    double xmultiplication = xsubtraction * xsubtraction;
    double ysubtraction = (coord[static_cast<size_t>(firstCoord)].second - coord[static_cast<size_t>(secCoord)].second);
    double ymultiplication = ysubtraction * ysubtraction;
    return sqrt((xmultiplication + ymultiplication));
}

double calcDistPromisingEstimate(int firstCoord, int secCoord, const std::vector<std::pair<int32_t, int32_t>> &coord, const std::vector<std::pair<int32_t, int32_t>> &MSTcoord)
{

    double xsubtraction = (coord[static_cast<size_t>(firstCoord)].first - MSTcoord[static_cast<size_t>(secCoord)].first);
    double xmultiplication = xsubtraction * xsubtraction;
    double ysubtraction = (coord[static_cast<size_t>(firstCoord)].second - MSTcoord[static_cast<size_t>(secCoord)].second);
    double ymultiplication = ysubtraction * ysubtraction;
    return sqrt((xmultiplication + ymultiplication));
}

struct Prim
{
    double edgeWeight;
    int32_t endPtPartner;
    bool isMST;
    Prim()
        : edgeWeight{std::numeric_limits<double>::infinity()}, endPtPartner{-1}, isMST{false} {}
};

int32_t smallestVertex(std::vector<Prim> &primMST)
{
    // Initialize min value
    double minWeight = INT_MAX;
    int32_t smallestVertex = 0;

    for (int vertex = 0; vertex < static_cast<int32_t>(primMST.size()); vertex++)
        if (!primMST[static_cast<size_t>(vertex)].isMST && primMST[static_cast<size_t>(vertex)].edgeWeight < minWeight)
            minWeight = primMST[static_cast<size_t>(vertex)].edgeWeight, smallestVertex = vertex;

    return smallestVertex;
}

std::vector<Prim> primMST(size_t start, bool flagPTA, const std::vector<std::pair<int32_t, int32_t>> &coord)
{
    // 2 initialize Prim table (which stores k, d, and p for each vertex v)
    std::vector<Prim> primMST(coord.size());
    std::fill(primMST.begin(), primMST.end(), Prim());
    // 3 set d of starting vertex to 0
    primMST[start].edgeWeight = 0;

    // 4 for each vertex v in graph:
    int32_t indexSmallestVertex;

    for (int i = 0; i < static_cast<int32_t>(primMST.size()); i++)
    {

        // 5 find vertex v_min with smallest d value among vertices whose k is false
        indexSmallestVertex = smallestVertex(primMST);
        // 6 set k of vertex v_min to true
        primMST[static_cast<size_t>(indexSmallestVertex)].isMST = true;

        // 7 for each neighbor n of vertex v_min in graph:
        for (int adjacentVertex = 0; adjacentVertex < static_cast<int32_t>(coord.size()); adjacentVertex++)
        {

            // graph[u][v] is non zero only for adjacent
            // vertices of m mstSet[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (adjacentVertex == indexSmallestVertex)
            {
                continue;
            }

            if (flagPTA)
            {
                // check to make sure that no wild-> safe pair here

                // neighbor is wild and endPtPartner is safe
                if (coord[static_cast<size_t>(indexSmallestVertex)].first < 0 && coord[static_cast<size_t>(indexSmallestVertex)].second < 0 &&
                    ((coord[static_cast<size_t>(adjacentVertex)].first > 0 && coord[static_cast<size_t>(adjacentVertex)].second > 0) ||
                     (coord[static_cast<size_t>(adjacentVertex)].first > 0 && coord[static_cast<size_t>(adjacentVertex)].second < 0) ||
                     (coord[static_cast<size_t>(adjacentVertex)].first < 0 && coord[static_cast<size_t>(adjacentVertex)].second > 0) ||
                     (coord[static_cast<size_t>(adjacentVertex)].first > 0 && coord[static_cast<size_t>(adjacentVertex)].second == 0) ||
                     (coord[static_cast<size_t>(adjacentVertex)].first == 0 && coord[static_cast<size_t>(adjacentVertex)].second > 0)))
                {
                    continue;
                }
                // neighbor is safe and endPtPartner is wild
                if (coord[static_cast<size_t>(adjacentVertex)].first < 0 && coord[static_cast<size_t>(adjacentVertex)].second < 0 &&
                    ((coord[static_cast<size_t>(indexSmallestVertex)].first > 0 && coord[static_cast<size_t>(indexSmallestVertex)].second > 0) ||
                     (coord[static_cast<size_t>(indexSmallestVertex)].first > 0 && coord[static_cast<size_t>(indexSmallestVertex)].second < 0) ||
                     (coord[static_cast<size_t>(indexSmallestVertex)].first < 0 && coord[static_cast<size_t>(indexSmallestVertex)].second > 0) ||
                     (coord[static_cast<size_t>(indexSmallestVertex)].first > 0 && coord[static_cast<size_t>(indexSmallestVertex)].second == 0) ||
                     (coord[static_cast<size_t>(indexSmallestVertex)].first == 0 && coord[static_cast<size_t>(indexSmallestVertex)].second > 0)))
                {
                    continue;
                }
            }

            // 8 if k of vertex n is false and edge weight between n and v_min < d of n:
            // 9 set d of vertex n to weight of edge between n and v_min
            // 10 set p of vertex n to index of v_min
            double minDist = calcDist(indexSmallestVertex, adjacentVertex, coord);

            if (!primMST[static_cast<size_t>(adjacentVertex)].isMST && minDist < primMST[static_cast<size_t>(adjacentVertex)].edgeWeight)
            {
                primMST[static_cast<size_t>(adjacentVertex)].endPtPartner = indexSmallestVertex, primMST[static_cast<size_t>(adjacentVertex)].edgeWeight = minDist;
            }
        }
    }

    return primMST;
} // prim_heap()

// part C portion

bool promising(std::vector<int32_t> &path, size_t perm_length, double &upperBound, const std::vector<std::pair<int32_t, int32_t>> &coord, double &soFar)
{
    // implement running sum

    if (path.size() - perm_length < 5)
    {
        return true;
    } // if

    // estimate lower bound and compare with upper bound

    double estimate = 0.0;

    // In summary, to obtain a lower bound for the TSP problem, you can sum of the following four weights:
    // 1. The cost of the current partial solution aka calculate the overall weight of graph

   
    estimate += soFar;
    //  2. The cost of the MST connecting the remaining points not in the partial solution, aka pass in a vector with the same amount of space as the number of nodes left to MST algorithm
    //  then calculate the total weight of the graph

    // make sure correct starting point!!
    //incorrect subset of nodes, must populate using path instead, but need to get the values of each coordinate 
    //this is the subset of indices in path that are not a part of the solution yet 
    std::vector MSTsubsetIndices(path.begin() + static_cast<int>(perm_length), path.end());
    //now grab each coordinate pair in that subset and save it in the 
    std::vector<std::pair<int32_t, int32_t>>MSTsubsetCoord;
    MSTsubsetCoord.reserve(MSTsubsetIndices.size());
    for(int i = 0; i<static_cast<int>(MSTsubsetIndices.size());i++ ){

        MSTsubsetCoord.push_back(coord[static_cast<size_t>(MSTsubsetIndices[static_cast<size_t>(i)])]);

    }
    std::vector<Prim> MSTEdges = primMST(0, false, MSTsubsetCoord);
    //FOR DEBUGGING
    double totalWeightMST= 0.0;

    for (int i = 1; i < static_cast<int>(MSTEdges.size()); i++)
    {
        totalWeightMST += MSTEdges[static_cast<size_t>(i)].edgeWeight;
    }

    // grab the first node in the partial solution, calculate its dist from all points in the MST, put in min PQ, grab top
    // 3. The cost of connecting one end of the partial solution with its closest point in the MST.

    // ERROR: grabs the same point for both, as in what is stored at path[0] and path[perm_length-1] could be a part of indices that i goes through.
    // looping the way we are doing does not actually get the correct point that i is supposed to be!!
    double minWeightFirst = std::numeric_limits<double>::infinity();
    double minWeightLast = std::numeric_limits<double>::infinity();

    for (int i = 0; i < static_cast<int>(MSTsubsetCoord.size()); i++)
    {

        double weight = calcDistPromisingEstimate(path[0], i, coord, MSTsubsetCoord);
        if (weight < minWeightFirst)
        {
            minWeightFirst = weight;
        }
    }

    // grab the last node in the partial solution, calculate its dist from all points in the MST, put in min PQ, grab top
    //  4. The cost of connecting the other end of the partial solution with its closest point in the MST

    for (int i = 0; i < static_cast<int>(MSTsubsetCoord.size()); i++)
    {
        //double check if need this after the change, seriously why is it 0 when there is only 1 node in the partial solution
        // if(perm_length - 1 ==0 && i ==0){
        //     continue;
        // }
        double weight = calcDistPromisingEstimate(path[(perm_length - 1)], i, coord, MSTsubsetCoord);
        if (weight < minWeightLast)
        {
            minWeightLast = weight;
        }
    }

    estimate += (minWeightLast + minWeightFirst+ totalWeightMST);

    // add all these together if < upper then continue aka return true

    // FOR DEBUGGING
//     for (size_t i = 0; i < path.size(); ++i)
//         std::cerr << std::setw(2) << path[i] << ' ';
//    std::cerr << std::setw(4) << perm_length << std::setw(10) << soFar;
//    std::cerr << std::setw(10) << minWeightFirst << std::setw(10) << minWeightLast;
//    std::cerr << std::setw(10) << totalWeightMST << std::setw(10) << estimate << "  " << (estimate < upperBound) << '\n';

    // other wise return false

    return estimate < upperBound;

} // promising()

// pass in the current partial solution  length and the current partial solution
void genPerms(std::vector<int32_t> &solution, std::vector<int32_t> &path, size_t permLength, double &upperBound, const std::vector<std::pair<int32_t, int32_t>> &coord, double &soFar)
{
    if (permLength == path.size())
    {
        // Do something with the path
        // Base case, this gets hit if you fully explore a path without ever pruning it.
        // This means the path currently stored in the vector may be an optimal solution,
        // does comparing solely mean the total weight??
        // so compare it with the best solution known so far and update the upper bound if needed.

        // calc the upper bound of the solution, compare the value to the current upper bound
        // if > then it is not the best/optimal solution since we are trying to find a min weight overall for the distance
        // if < then its one possible best/optimal solution, update current saved path for solution printing and update current upper bound
        // updating current path is not necessary, just ensure that upper bound gets updated

        double totalWeight = 0.0;
        // for (int i = 0; i < static_cast<int>(path.size() - 1); i++)
        // {
        //     totalWeight += calcDist(path[static_cast<size_t>(i)], path[static_cast<size_t>(i + 1)], coord);
        // }
        totalWeight += soFar;

        totalWeight += calcDist(path[static_cast<size_t>(0)], path[path.size() - 1], coord);

        if (totalWeight < upperBound)
        {
            upperBound = totalWeight;
            solution = path;
        }

        return;
    } // if ..complete path

    if (!promising(path, permLength, upperBound, coord, soFar))
    {
        return;
    } // if ..not promising

    for (size_t i = permLength; i < path.size(); ++i)
    {
        // soFarWeight is not properly updating, overflows everytime
        std::swap(path[permLength], path[i]);
        soFar += calcDist(path[static_cast<size_t>(permLength - 1)], path[static_cast<size_t>(permLength)], coord);
        genPerms(solution, path, permLength + 1, upperBound, coord, soFar);
        soFar -= calcDist(path[static_cast<size_t>(permLength - 1)], path[static_cast<size_t>(permLength)], coord);
        std::swap(path[permLength], path[i]);
    } // for ..unpermuted elements

}; // genPerms()

// Part B class

void calcTSPHeuristic(double &totalWeight, std::vector<int32_t> &path, const std::vector<std::pair<int32_t, int32_t>> &coord)
{
    // starting with a randomly chosen vertex, in this case 0
    path.push_back(0);
    path.push_back(1);
    path.push_back(2);
    // after each node is inserted, this needs to be empty, question: how will this affect runtime ??
    // have  a vector of nodes, each node that is next to each other is adjacent!
    totalWeight += calcDist(path[static_cast<size_t>(0)], path[static_cast<size_t>(1)], coord) +
                   calcDist(path[static_cast<size_t>(1)], path[static_cast<size_t>(2)], coord) +
                   calcDist(path[static_cast<size_t>(2)], path[static_cast<size_t>(0)], coord);
    // every single node that is not in the solution yet
    // possibly start at 3, push, 0,1,2 instead to start
    double firstAdd = 0.0;
    double secondAdd = 0.0;
    double subtract = 0.0;
    double KEEPfirstAdd = 0.0;
    double KEEPsecondAdd = 0.0;
    double KEEPsubtract = 0.0;
    for (int i = 3; i < static_cast<int>(coord.size()); i++)
    {
        double minWeight = std::numeric_limits<double>::infinity();

        int leftCity;

        // every node that is in the solution
        //  grab all the possible pairs and calc the following: for each cik+ckj−cij meaning the distance between each letter that is not c
        for (int k = 0; k < static_cast<int>(path.size() - 1); k++)
        {
            int firstCity = k;
            int secondCity = k + 1;

            firstAdd = calcDist(path[static_cast<size_t>(firstCity)], i, coord);
            secondAdd = calcDist(i, path[static_cast<size_t>(secondCity)], coord);
            subtract = calcDist(path[static_cast<size_t>(firstCity)], path[static_cast<size_t>(secondCity)], coord);
            double calcWeight = firstAdd + secondAdd - subtract;
            if (calcWeight < minWeight)
            {
                minWeight = calcWeight;
                leftCity = secondCity;
                KEEPfirstAdd = firstAdd;
                KEEPsecondAdd = secondAdd;
                KEEPsubtract = subtract;
            }
        }

        firstAdd = calcDist(path[0], i, coord);
        secondAdd = calcDist(i, path[path.size() - 1], coord);
        subtract = calcDist(path[0], path[path.size() - 1], coord);
        double calcWeightForLastPair = firstAdd + secondAdd - subtract;
        if (calcWeightForLastPair < minWeight)
        {

            totalWeight += firstAdd;
            totalWeight += secondAdd;
            totalWeight -= subtract;

            path.push_back(i);
            continue;
        }

        // insert i in between left and right city
        path.insert(path.begin() + leftCity, i);
        totalWeight += KEEPfirstAdd;
        totalWeight += KEEPsecondAdd;
        totalWeight -= KEEPsubtract;
    }
}


int main(int argc, char *argv[])
{
    // TODO UNCOMMENT THIS !!
     std::cout << std::setprecision(2); // Always show 2 decimal places
     std::cout << std::fixed;           // Disable scientific notation for large numbers
    // std::cerr << std::fixed << std::showpoint << std::setprecision(2) << std::boolalpha;

    // validate cmd line
    bool MSTFlag = false;
    bool TSPFlag = false;
    bool TSPOPTFlag = false;

    struct option longOpts[] = {
        {"mode", required_argument, NULL, 'm'},
        {"help", no_argument, NULL, 'h'},
        {nullptr, 0, nullptr, '\0'},
    };

    opterr = false;

    // use for saving the output type if specified
    int opt = 0, index = 0;

    while ((opt = getopt_long(argc, argv, "m:h", longOpts, &index)) != -1)
    {
        switch (opt)
        {

            // stats
        case 'm':
            if (strcmp(optarg, "MST") == 0)
                MSTFlag = true;
            else if (strcmp(optarg, "FASTTSP") == 0)
                TSPFlag = true;
            else if (strcmp(optarg, "OPTTSP") == 0)
                TSPOPTFlag = true;
            else
            {
                std::cerr << "Error: Unknown option";
                exit(1);
            }

            break;

        case 'h':
            std::cout << "Valid cmds to make game output\n";
            std::cout << "--mode -m with MST, FASTTSP, or OPTTSP to activate certain modes  \n";
            std::cout << "--help -h to display this help message";
            exit(0);
            break;

        default:
            // throw an error
            std::cerr << "Error: Unknown option";
            exit(1);
        } // switch
    }     // while

    if (MSTFlag)
    {

        double totalWeight = 0.0;
        int32_t xCoor;
        int32_t yCoor;
        int32_t numPairs;
        std::vector<std::pair<int32_t, int32_t>> coord;
        std::cin >> numPairs;
        coord.reserve(static_cast<size_t>(numPairs));
        bool isWild = false;
        bool isWall = false;
        bool isSafe = false;
        // collect all possible coordinates,

        while (std::cin >> xCoor >> yCoor)
        {
            if (xCoor < 0 && yCoor < 0)
            {
                isWild = true;
            }
            // origin counts
            else if ((xCoor <= 0 && yCoor == 0) || (xCoor == 0 && yCoor <= 0))
            {
                isWall = true;
            }
            else
            {
                isSafe = true;
            }
            coord.push_back(std::make_pair(xCoor, yCoor));
        }

        // if both wild and wall are present continue
        if (isWild && isSafe)
        {
            // if there is no wall then this will be true
            if (!isWall)
            {
                std::cerr << "Cannot construct MST";
                exit(1);
            }
        }

        // who each node is paired possibly, key reps position in vector
        // for the last vertex in the possible coord, no combinations are generated and all combinations are in ascending order

        // idk if the should start at 0
        std::vector<Prim> MSTEdges = primMST(0, true, coord);

        // print out each
        for (size_t i = 0; i < MSTEdges.size(); i++)
        {
            totalWeight += MSTEdges[i].edgeWeight;
        }
        std::cout << totalWeight << "\n";
        // note: check what is going on with trying to find start's partner, it is not being set correctly/not at all, like everything is offset by 1... or it is supposed to not do it that way

        for (size_t i = 1; i < MSTEdges.size(); i++)
        {
            std::cout << std::min(static_cast<int>(i), MSTEdges[(i)].endPtPartner) << " " << std::max(static_cast<int>(i), MSTEdges[(i)].endPtPartner) << "\n";
        }
        // note:
        // some things that may need to be checked for
        // 1. dist calc, may have some overflow...
        // for some reason everything is offset by one aka, the ones slot has what 0's partner should be etc.
    }
    else if (TSPFlag)
    {

        // arbitrary insertion rec
        // 1. Initialize a partial tour with a vertex i, chosen arbitrarily (you can just start with the first vertex available).
        // 2. Choose another arbitrary vertex j and set the initial partial tour to i → j → i.
        // 3. Arbitrarily select a vertex k that is currently not in the partial tour.
        // 4. Find the best place to insert vertex k into the partial tour to minimize cost. To do this, first identify the edge (i, j) in the partial path
        // such that dist i,k +dist k,j −dist i,j is minimal , and then insert k between i and j.
        // 5. Once all the vertices have been added to the path, the algorithm completes. Otherwise, repeat steps 3-5 until all vertices have been added.

        // // grab all the vertices
        double totalWeight = 0.0;
        int32_t xCoor;
        int32_t yCoor;
        int32_t numPairs;
        /// list of all vertices in the graph, in order of read in
        std::vector<std::pair<int32_t, int32_t>> coord;
        std::cin >> numPairs;
        coord.reserve(static_cast<size_t>(numPairs));

        while (std::cin >> xCoor >> yCoor)
        {

            coord.push_back(std::make_pair(xCoor, yCoor));
        }

        // separate vector for the path
        std::vector<int32_t> path;
        calcTSPHeuristic(totalWeight, path, coord);
        std::cout << totalWeight << "\n";

        // note: see if there is a way to speed this up..
        //  print the actual path
        for (size_t i = 0; i < path.size(); i++)
        {
            std::cout << path[i] << " ";
        }
    }
    else if (TSPOPTFlag)
    {

        //   // // grab all the vertices
        int32_t xCoor;
        int32_t yCoor;
        int32_t numPairs;
        /// list of all vertices in the graph, in order of read in
        std::vector<std::pair<int32_t, int32_t>> coord;
        std::cin >> numPairs;
        coord.reserve(static_cast<size_t>(numPairs));

        while (std::cin >> xCoor >> yCoor)
        {
            coord.push_back(std::make_pair(xCoor, yCoor));
        }

        // separate vector for the path
        std::vector<int32_t> path;
        // separate vector for actually storing the solution
        std::vector<int32_t> solution;

        double placeholder;

        // pass in a heuristic solution aka call part B for setting up path
        calcTSPHeuristic(placeholder, path, coord);
        placeholder = 0.0;

        double upperBound = std::numeric_limits<double>::infinity();
        // call gen perms on path vector
        // TODO
        genPerms(solution, path, 1, upperBound, coord, placeholder);
        std::cout << upperBound << "\n";

        // print the actual path
        for (size_t i = 0; i < solution.size(); i++)
        {
            std::cout << solution[i] << " ";
        }
    }
}