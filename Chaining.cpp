#include "Chaining.h"
#include <iostream>
using namespace std;

Chaining::Chaining()
{
    size = 0;
    bankStorage2d.resize(100003);
}

void Chaining::createAccount(std::string id, int count)
{
    Account acc;
    acc.id = id;
    acc.balance = count;
    int index = hash(id);
    if (doesExist(id) == false)
    {
        bankStorage2d[index].push_back(acc);
        size++;

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
                for (int i = 0; i<topK.size()-1;i++){
                    if (acc.balance>=topK[i].balance && acc.balance<= topK[i+1].balance){
                        topK.insert(topK.begin()+i+1,acc);
                        break;
                    }
                }
            }
        }
    }
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> Chaining::getTopK(int k)
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

int Chaining::getBalance(std::string id)
{
    int key = hash(id);
    for (int i = 0; i < bankStorage2d[key].size(); i++)
    {
        if (bankStorage2d[key][i].id == id)
        {
            return bankStorage2d[key][i].balance;
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count)
{
    if (doesExist(id) == true)
    {
        int key = hash(id);

        for (int j = 0; j < bankStorage2d[key].size(); j++)
        {
            if (bankStorage2d[key][j].id == id)
            {
                for (int i = 0; i<topK.size();i++){
                    if (topK[i].id==id){
                        topK.erase(topK.begin()+i);
                        break;
                    }
                }
                int a = bankStorage2d[key][j].balance;
                bankStorage2d[key].erase(bankStorage2d[key].begin() + j);
                
                createAccount(id, a + count);
                size--;
                break;
            }
        }
    }
    
    else
    {
        createAccount(id, count);
    }
    // IMPLEMENT YOUR CODE HERE
}

bool Chaining::doesExist(std::string id)
{
    int key = hash(id);
    for (int i = 0; i < bankStorage2d[key].size(); i++)
    {
        if (bankStorage2d[key][i].id == id)
        {
            return true;
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id)
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
        for (int i = 0; i < bankStorage2d[key].size(); i++)
        {
            if (bankStorage2d[key][i].id == id)
            {
                bankStorage2d[key].erase(bankStorage2d[key].begin() + i);
                size--;
                return true;
            }
        }
    }

    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int Chaining::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id)
{
    int key;
    int s;
    s = 0;
    for (int i = 0; i < 4; i++)
    {
        s += int(id[i]);
    }
    key = s % 1000003;
    return key;
};
