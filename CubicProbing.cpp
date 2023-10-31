#include "CubicProbing.h"
using namespace std;
CubicProbing::CubicProbing()
{
    size = 0;
    
    bankStorage1d.resize(100003);
};
void CubicProbing::createAccount(std::string id, int count)
{
    Account acc;
    acc.id = id;
    acc.balance = count;
    int index = hash(id);



    int i = 1;
    while (bankStorage1d[index].id != "")
    {
        index = (index + i*i*i) % 100003;
        i++;
    }
    bankStorage1d[index].id = id;
    bankStorage1d[index].balance = count;

    if (topK.empty())
    {
        topK.push_back(acc);
    }
    else
    {
        if (acc.balance <= topK[0].balance)
        {
            topK.insert(topK.begin(), acc);
        }
        else if (acc.balance >= topK[topK.size() - 1].balance)
        {
            topK.push_back(acc);
        }
        else
        {
            for (int i = 0; i < topK.size() - 1; i++)
            {
                if (acc.balance >= topK[i].balance && acc.balance <= topK[i + 1].balance)
                {
                    topK.insert(topK.begin() + i + 1, acc);
                    break;
                }
            }
        }
    }

    size++;
}

std::vector<int> CubicProbing::getTopK(int k)
{
    vector<int> v1;
    for (int i = 0; i < k; i++)
    {
        v1.push_back(topK[topK.size() - 1 - i].balance);
    }
    // IMPLEMENT YOUR CODE HERE
    // Placeholder return value
    return v1;
}

int CubicProbing::getBalance(std::string id)
{
    int key = hash(id);
    if (doesExist(id) == true)
    {
        int i =1;
        while (key < bankStorage1d.size())
        {
            if (bankStorage1d[key].id == id)
            {
                return bankStorage1d[key].balance;
            }
            key = (key+i*i*i)%100003;
            i++;
        }
    }
    // IMPLEMENT YOUR CODE HERE
    else
    {
        return -1;
    }; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count)
{
    if (doesExist(id))
    {
        int key = hash(id);
        int a;
        for (int i = 0; i < topK.size(); i++)
        {
            if (topK[i].id == id)
            {
                a = topK[i].balance;
                topK.erase(topK.begin() + i);
                break;
            }
        }

        deleteAccount(id);
        createAccount(id, a + count);
    }

    else
    {
        createAccount(id, count);
    }
    // IMPLEMENT YOUR CODE HERE
}

bool CubicProbing::doesExist(std::string id)
{
    int key = hash(id);
    int i = 0;
    while (i < bankStorage1d.size())
    {
        if (bankStorage1d[i].id == id)
        {
            return true;
        }
        i++;

        // IMPLEMENT YOUR CODE HERE

        // Placeholder return value
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id)
{
    if (doesExist(id) == true)
    {
        int key = hash(id);
        for (int i = 0; i < topK.size(); i++)
        {
            if (topK[i].id == id)
            {
                topK.erase(topK.begin() + i);
                break;
            }
        }
        int i =1;
        while (key < bankStorage1d.size())
        {
            if (bankStorage1d[key].id == id)
            {
                bankStorage1d[key]=init;
            }
            key = (key+i*i*i)%100003;
            i++;
        }
        size--;
        
        return true;
    }
    else
    {
        // IMPLEMENT YOUR CODE HERE
        return false;
    } // Placeholder return value
}
int CubicProbing::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int CubicProbing::hash(std::string id)
{
    int key;
    int s;
    s = 0;
    for (int i = 0; i < 4; i++)
    {
        s = s + int(id[i]);
    }
    key = s % 100003;
    
    // IMPLEMENT YOUR CODE HERE
    return key; // Placeholder return value
};
