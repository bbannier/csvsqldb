//
//  time_measurement.h
//  csvsqldb
//
//  BSD 3-Clause License
//  Copyright (c) 2015, Lars-Christian Fürstenberg
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without modification, are permitted
//  provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//  conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice, this list of
//  conditions and the following disclaimer in the documentation and/or other materials provided
//  with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors may be used to
//  endorse or promote products derived from this software without specific prior written
//  permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
//  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//

#ifndef csvsqldb_time_measurement_h
#define csvsqldb_time_measurement_h

#include "libcsvsqldb/inc.h"

#include "exception.h"
#include "types.h"

#include <cstdint>
#include <ctime>
#include <chrono>
#include <ostream>
#include <ratio>

#ifndef _MSC_VER
#include <sys/times.h>
#include <unistd.h>
#endif


namespace csvsqldb
{
    /**
     * Time measurement handling stuff
     */
    namespace chrono
    {
        // TODO LCF: move to detail
        inline long tickFactor()
        {
            static long factor = 0;
#ifndef _MSC_VER    // TODO LCF: find an adequat implementation for Windows
            if(!factor) {
                if((factor = ::sysconf(_SC_CLK_TCK)) <= 0) {
                    factor = -1;
                } else {
                    factor = 1000l / factor;
                    if(!factor) {
                        factor = -1;
                    }
                }
            }
#endif
            return factor;
        }

        struct CSVSQLDB_EXPORT ProcessTimeDuration {
            long _real;
            long _user;
            long _system;
        };

        struct CSVSQLDB_EXPORT ProcessTimePoint {
            long _real;
            long _user;
            long _system;

            friend CSVSQLDB_EXPORT ProcessTimeDuration operator-(const ProcessTimePoint& lhs, const ProcessTimePoint& rhs);
        };

        CSVSQLDB_EXPORT ProcessTimeDuration operator-(const ProcessTimePoint& lhs, const ProcessTimePoint& rhs);

        /**
         * A clock for the retrieval of real, user and system time. Can be used to measure runtimes.
         */
        class CSVSQLDB_EXPORT ProcessTimeClock : noncopyable
        {
        public:
            // TODO LCF: move implementation to detail
            static ProcessTimePoint now();
        };
    }
}

namespace std
{
    CSVSQLDB_EXPORT std::ostream& operator<<(std::ostream& out, const csvsqldb::chrono::ProcessTimeDuration& duration);
}

#endif
