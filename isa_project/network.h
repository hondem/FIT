//
// Created by Jan Demel on 18/10/2019.
//

#ifndef ISA_PROJECT_NETWORK_H
#define ISA_PROJECT_NETWORK_H

#include <string>
#include <vector>

using namespace std;

/**
 * Record of interface
 */
struct interface {
    string name;
    string address;
};

/**
 * Class for handling network connections, utilities etc..
 */
class network {
public:
    /**
     * List all relevant interfaces IPv6 address
     * @return
     */
    static vector<string> *getTargetInterfaces(const string&);
};


#endif //ISA_PROJECT_NETWORK_H
