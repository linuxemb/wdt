
// test file for watchdog lib

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include "../../../OS/OAL/UdpDevice.h"
#include "../../../../Library/Tyco_lib/watchdogAPI/WatchdogInterface.h"
#include "WatchdogLib.h"
//[Boost Dynamic Library Defines
//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE WatchdogAPI_TM
//// must be define before "unit_test
//#include <boost/test/unit_test.hpp>

using namespace Tyco::System::Oal;
using namespace Tyco::Lib::Watchdog;
//using boost::unit_test_framework::test_suite;
//using boost::unit_test_framework::test_case;
enum {
   DEFAULT_FREQ = 5,
};

//BOOST_GLOBAL_FIXTURE(MyFixture);

 int  main() {

   int port = rand() % 30 + 6500;
   std::cout <<"port" <<port <<endl;
   UdpDevice *daemon = new UdpDevice("127.0.0.1", port);
   WatchdogInterface *wdtLib = new WatchdogInterface(daemon);
   uint64_t id = wdtLib->getTaskId();
   uint64_t pid = getpid();

   wdtLib->registerWatchdog(id, pid, "WatchdogLib", DEFAULT_FREQ);
while(true)
{
   uint32_t ret = wdtLib-> pingWatchdog(id, pid, "WatchdogLib", DEFAULT_FREQ);
   sleep(2);
}


return 0;
}


