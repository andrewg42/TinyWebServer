#pragma once

#include <net/Reactor.h>

#include <utils/Singleton.h>

namespace webserver {

class Webserver: webserver::utils::Singleton<Webserver> {

    Webserver() {

    }

    ~Webserver() {

    }


};

}