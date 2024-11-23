#include "client.h"
#include "crypto.h"
#include "server.h"
#include <random>
using namespace std;

Client::Client(std::string id, const Server &server) : id(id), server(&server)
{
    crypto::generate_key(public_key, private_key);
}
std::string Client::sign(std::string txt) const
{
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}
double Client::get_wallet() const
{
    return server->get_wallet(id);
}

bool Client::transfer_money(std::string receiver, double value)
{
    string trx = id + "-" + receiver + "-" + to_string(value);
    std::string signature = crypto::signMessage(private_key, trx);
    return server->add_pending_trx(trx, signature);
}

size_t Client::generate_nonce() const
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, SIZE_MAX);
    return distribution(generator);
}