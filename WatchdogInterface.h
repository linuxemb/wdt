
#ifndef WatchdogInterface_H_
#define WatchdogInterface_H_


#include "../../../OS/OAL/UdpDevice.h"
#include <iostream>
#include  <cstdint>
#include <sys/syscall.h>
#include <unistd.h>


         static const string LOCAL_HOST = "127.0.0.1";
         static const string PING = "0";
         static const string REGISTER = "1";
         static const string UNREGISTER = "2";
         class WatchdogInterface {

            enum {
               LOCAL_PORT = 6800, REMOTE_PORT = 9999,
            };
         public:
            /*!
             * \fn     WatchdogInterface.class constructor
             * \brief  setup interface for talk to Watchdog Daemon
             *
             */
            explicit WatchdogInterface(UdpDevice *dev);
            /*!
             * \fn     WatchdogInterface.class destructor
             * \brief  setup interface for talk to Watchdog Daemon
             *
             */
            virtual ~WatchdogInterface();

            // Copy constructor for LDRA rules
            WatchdogInterface(const WatchdogInterface &obj);

            // Assignment constructor for LDRA rules
            WatchdogInterface & operator =(WatchdogInterface & obju);
            /*!
             * \fn      pingWatchdog
             * \brief   API to send heartbeat of task
             * \param   id: task Id ( for process = pid) (for thread = tid)
             * \param   pid:  process id
             * \param   taskname: process/thread name
             * \param   freq: indacate priority of signal, how many time of
             *  missing heart beat willbe count as dead
             *
             */
            bool pingWatchdog(uint64_t id, uint64_t pid, string taskname,
                  uint32_t freq);
            /*!
             * \fn     registerWatchdog
             * \bref   API to register task  to watchdogdaemon
             * \param   id: task Id ( for process = pid) (for thread = tid)
             * \param   pid:  process id
             * \param   taskname: process/thread name
             * \param   freq: indacate priority of signal, how many time of
             *  missing heart beat willbe count as dead
             *
             */
            bool registerWatchdog(uint64_t id, uint64_t pid, string taskname,
                  uint32_t freq);

            /*!
             * \fn     unregisterWatchdog
             * \brief  API to send unregister command to watchdog daemon to cancel moinotring
             * \param   id: task Id ( for process = pid) (for thread = tid)
             * \param   pid:  process id
             * \param   taskname: process/thread name
             * \param   freq: indacate priority of signal, how many time of
             *  missing heart beat willbe count as dead
             *
             */
            void unregisterWatchdog(uint64_t id, uint64_t pid, string taskname,
                  uint32_t freq);

            uint64_t getTaskId();

         private:
            uint64_t mPid;
            uint64_t mTid;

            uint64_t mId;
            string mTaskName;
            uint32_t mFreq;

            string mRmpIp;
            uint16_t mRmtPort;
            UdpDevice * mWdtDaemon;

         };
   

