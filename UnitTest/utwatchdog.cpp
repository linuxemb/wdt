
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include "../../../../OS/OAL/UdpDevice.h"
#include "../WatchdogInterface.h"
#include "utwatchdog.h"
//[Boost Dynamic Library Defines
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE WatchdogAPI_TM
 // must be define before "unit_test
#include <boost/test/unit_test.hpp>

using namespace Tyco::System::Oal;
using namespace Tyco::Lib::Watchdog;
using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;
enum {
   DEFAULT_FREQ = 5,
};

struct MyFixture {
   MyFixture() {
      int port = rand() % 30 + 6500;
      cout << "port" << port << endl;
//     UdpDevice *daemon = new UdpDevice(LOCAL_HOST, port);
//      WatchdogInterface *wdtLib = new WatchdogInterface(daemon);

   }
   ~ MyFixture() {
      delete daemon;
      delete wdtLib;
   }

   int* i;
   UdpDevice *daemon;
   WatchdogInterface *wdtLib;
};

//BOOST_GLOBAL_FIXTURE(MyFixture);
BOOST_AUTO_TEST_SUITE (WatchdogAPI_TS)

BOOST_AUTO_TEST_CASE(register_watchdog)
{
   BOOST_TEST_MESSAGE("Test watchdogAPI register...");

   MyFixture f;
   if((f.daemon != nullptr) && (f.wdtLib != nullptr))
   {
      uint64_t id = f.wdtLib->getTaskId();
      uint64_t pid = getpid();
      uint32_t ret = f.wdtLib->registerWatchdog(id, pid, "WatchdogLib", DEFAULT_FREQ);
      boost::this_thread::sleep(boost::posix_time::milliseconds(10));
      BOOST_CHECK(ret != 0);
   }

   else
   {
      BOOST_TEST_MESSAGE(" error");
   }

   if(f.wdtLib != nullptr)
   {
      delete f.daemon;
   }

   if(f.daemon != nullptr)
   {
      delete f.daemon;
   }
   else
   {
      std::cout<<"watchdog api register done"<<endl;
   }

}

BOOST_AUTO_TEST_CASE(ping_watchdog)
{
   BOOST_TEST_MESSAGE("Test watchdogAPI ping...");
   int port = rand() % 30 + 6500;
   cout <<"port" <<port <<endl;
   UdpDevice *daemon = new UdpDevice(LOCAL_HOST, port);
   WatchdogInterface *wdtLib = new WatchdogInterface(daemon);
   uint64_t id = wdtLib->getTaskId();
   uint64_t pid = getpid();
   uint32_t ret = wdtLib-> pingWatchdog(id, pid, "WatchdogLib", DEFAULT_FREQ);
   BOOST_CHECK(ret == 0);
}

BOOST_AUTO_TEST_CASE(unregister_watchdog)
{
   BOOST_TEST_MESSAGE("Test watchdogAPI unregister...");

   int port = rand() % 30 + 6500;
   cout <<"port" <<port <<endl;
   UdpDevice *daemon = new UdpDevice(LOCAL_HOST, port);
   WatchdogInterface *wdtLib = new WatchdogInterface(daemon);
   uint64_t id = wdtLib->getTaskId();
   uint64_t pid = getpid();

   wdtLib->unregisterWatchdog(id, pid, "WatchdogLib", DEFAULT_FREQ);

}

BOOST_AUTO_TEST_SUITE_END();

