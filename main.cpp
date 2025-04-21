#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool isSafeState(int processes, int resources,
                 std::vector<std::vector<int>> &allocation,
                 std::vector<std::vector<int>> &maxNeed,
                 std::vector<std::vector<int>> &need,
                 std::vector<int> &available,
                 std::vector<int> &safeSequence)
{

    std::vector<bool> finished(processes, false);
    std::vector<int> work = available;
    int count = 0;

    while (count < processes)
    {
        bool found = false;

        for (int i = 0; i < processes; i++)
        {
            if (!finished[i])
            {
                bool canAllocate = true;

                for (int j = 0; j < resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int ii = 0; ii < resources; ii++)
                    {
                        work[ii] += allocation[i][ii];
                    }

                    finished[i] = true;
                    safeSequence[count] = i;
                    count++;
                    found = true;
                }
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::ifstream inputFile("fail_banker_input.txt");

    if (!inputFile)
    {
        std::cerr << "Error: Unable to open input file" << std::endl;
        return 1;
    }

    int processes, resources;
    inputFile >> processes >> resources;

    // Read available resources
    std::vector<int> available(resources);
    for (int i = 0; i < resources; i++)
    {
        inputFile >> available[i];
    }

    // read allocation matrix
    std::vector<std::vector<int>> allocation(processes, std::vector<int>(resources));
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            inputFile >> allocation[i][j];
        }
    }

    // read max need matrix
    std::vector<std::vector<int>> maxNeed(processes, std::vector<int>(resources));
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            inputFile >> maxNeed[i][j];
        }
    }

    // calculate need matrix
    std::vector<std::vector<int>> need(processes, std::vector<int>(resources));
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }

    std::cout << "System State:" << std::endl;
    std::cout << "Available Resources: ";
    for (int i = 0; i < resources; i++)
    {
        std::cout << available[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Allocation Matrix:" << std::endl;
    for (int i = 0; i < processes; i++)
    {
        std::cout << "P" << i << ": ";
        for (int j = 0; j < resources; j++)
        {
            std::cout << allocation[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Max Need Matrix:" << std::endl;
    for (int i = 0; i < processes; i++)
    {
        std::cout << "P" << i << ": ";
        for (int j = 0; j < resources; j++)
        {
            std::cout << maxNeed[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Need Matrix:" << std::endl;
    for (int i = 0; i < processes; i++)
    {
        std::cout << "P" << i << ": ";
        for (int j = 0; j < resources; j++)
        {
            std::cout << need[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> safeSequence(processes);
    bool safe = isSafeState(processes, resources, allocation, maxNeed, need, available, safeSequence);

    if (safe)
    {
        std::cout << "The system is in a safe state." << std::endl;
        std::cout << "Safe Sequence: ";
        for (int i = 0; i < processes; i++)
        {
            std::cout << "P" << safeSequence[i];
            if (i != processes - 1)
            {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "The system is not in a safe state." << std::endl;
    }

    inputFile.close();
    return 0;
}