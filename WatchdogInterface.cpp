
#include "WatchdogInterface.h"
#include  <string>
#include <boost/log/trivial.hpp>


         WatchdogInterface::WatchdogInterface(UdpDevice *dev) :
               mPid(0), mRmpIp(LOCAL_HOST), mRmtPort(REMOTE_PORT) {

            mWdtDaemon = dev;
         }

         WatchdogInterface::~WatchdogInterface() {

         }
         //  Register to  watchdog daemon to request been monitored

         bool WatchdogInterface::registerWatchdog(uint64_t id, uint64_t pid,
               string taskname, uint32_t freq) {

            cout << "registing....." << endl;
            string mid = boost::to_string(static_cast<uint32_t>(id));
            string mpid = boost::to_string(static_cast<uint32_t>(pid));
            string msgpkt = REGISTER + "," + taskname;
            string msgptkSend = msgpkt + "," + mid + "," + mpid + ","
                  + boost::to_string(freq);

            boost::shared_ptr<std::string> pPkt(new std::string(msgptkSend));
            mWdtDaemon->sendMessage(pPkt, LOCAL_HOST, REMOTE_PORT);
            return 0;
         }

         //  Send watchdog daemon heart beat signal

         bool WatchdogInterface::pingWatchdog(uint64_t id, uint64_t pid,
               string taskname, uint32_t freq) {

            string mid = boost::to_string(static_cast<uint32_t>(id));

            string mpid = boost::to_string(static_cast<uint32_t>(pid));

            string msgpkt = PING + "," + taskname;
            string msgptkSend = msgpkt + "," + mid + "," + mpid + ","
                  + boost::to_string(freq);

            boost::shared_ptr<std::string> pPkt(new std::string(msgptkSend));

            mWdtDaemon->sendMessage(pPkt, LOCAL_HOST, REMOTE_PORT);
            return 0;
         }

         void WatchdogInterface::unregisterWatchdog(uint64_t id, uint64_t pid,
               string taskname, uint32_t freq) {
            std::string idstr = boost::to_string(static_cast<uint32_t>(id));

            std::string mid = boost::to_string(static_cast<uint32_t>(id));
            string mpid = boost::to_string(static_cast<uint32_t>(pid));

            std::string msgpkt = UNREGISTER + "," + taskname;
            string msgptkSend = msgpkt + "," + mid + "," + mpid + ","
                  + boost::to_string(freq);
            boost::shared_ptr<std::string> pPkt(new std::string(msgptkSend));
            mWdtDaemon->sendMessage(pPkt, LOCAL_HOST, REMOTE_PORT);
         }

// helper funciton Regeive task id

         uint64_t WatchdogInterface::getTaskId() {

            uint64_t tid = syscall(SYS_gettid);
            cout << "tid=" << tid;
            uint64_t pid = getpid();

            if (tid == pid) {
               return pid;
            } else {
               return tid;
            }
        
