#include "server.h"
#include "client.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <sstream>
#include <crypto.h>
using namespace std;

std::vector<std::string> pending_trxs;

void show_wallets(const Server &server)
{
    std::cout << std::string(20, '*') << std::endl;
    for (const auto &client : server.clients)
        std::cout << client.first->get_id() << " : " << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (auto pair : clients)
    {
        shared_ptr<Client> client = pair.first;
        if (client)
        {
            if (id == client->get_id())
            {
                return client;
            }
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    auto client = get_client(id);
    if (!client)
    {
        throw runtime_error("");
    }
    return clients.at(client);
}
string generateRandomNumber(int n)
{
    string ret;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 9);
    while (n--)
    {
        char number = distribution(generator);
        ret += '0' + number;
    }
    return ret;
}
std::shared_ptr<Client> Server::add_client(std::string id)
{
    string originalId = id;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 9);
    while (get_client(id))
    {
        id = originalId;
        int addDigit = 4;
        for (int i = 0; i < addDigit; i++)
        {
            char number = distribution(generator);
            id += '0' + number;
        }
    }

    auto ret = make_shared<Client>(id, *this);
    clients[ret] = 5;
    return ret;
}

// Function to split a string using a delimiter
std::vector<std::string> splitString(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

bool Server::parse_trx(const std::string &trx, std::string &sender, std::string &receiver, double &value)
{
    vector<string> tokens = splitString(trx, '-');
    if (tokens.size() != 3)
    {
        throw runtime_error("");
    }
    sender = tokens[0];
    receiver = tokens[1];
    value = stod(tokens[2]);
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    string sender, receiver;
    double value;
    parse_trx(trx, sender, receiver, value);
    auto client = get_client(sender);
    if (client)
    {
        if(!get_client(receiver)) {
            return false;
        }
        if (get_wallet(sender) < value)
        {
            return false;
        }
        bool authentic = crypto::verifySignature(client->get_publickey(), trx, signature);
        if(!authentic) {
            return false;
        }
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}

size_t Server::mine() {
    
    string mempool;
    for_each(pending_trxs.begin(), pending_trxs.end(), [&mempool](const string& s) {
        mempool += s;
    });
    if(clients.size() == 0) {
        return 0;
    }
    while(true) {
        for(auto& pair : clients) {
            auto client = pair.first;
            size_t nonce = client->generate_nonce();
            string hashResult = crypto::sha256(mempool + to_string(nonce));
            if(hashResult.substr(0, 3) == "000") {
                pair.second += 6.25;
                for(auto& trx : pending_trxs){
                    string sender, receiver;
                    double value;
                    parse_trx(trx, sender, receiver, value);
                    clients[get_client(sender)] -= value;
                    clients[get_client(receiver)] += value;
                }
                return nonce;
            }
        }
    }
    return 0;
}