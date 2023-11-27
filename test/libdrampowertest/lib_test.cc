/*
 * Copyright (c) 2014, TU Delft, TU Eindhoven and TU Kaiserslautern
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Matthias Jung, Omar Naji, Felipe S. Prado
 *
 */

#include <iostream>
#include <string>
#include "libdrampower/LibDRAMPower.h"

using namespace std;
using namespace Data;

static void ConfigMem (MemorySpecification& memSpec)
{
  memSpec.memoryType = MemoryType::DDR2;

  memSpec.memArchSpec.width = 16;
  memSpec.memArchSpec.nbrOfBanks = 8;
  memSpec.memArchSpec.nbrOfRanks = 1;
  memSpec.memArchSpec.nbrOfColumns = 1024;
  memSpec.memArchSpec.nbrOfRows = 8192;
  memSpec.memArchSpec.dataRate = 2;
  memSpec.memArchSpec.burstLength = 8;

  memSpec.memTimingSpec.clkMhz = 533;
  memSpec.memTimingSpec.REFI = 3120;
  memSpec.memTimingSpec.RFC = 68;
  //memSpec.memTimingSpec.CL = 7;
  memSpec.memTimingSpec.FAW = 24;
  memSpec.memTimingSpec.RRD = 6;
  memSpec.memTimingSpec.CCD = 2;
  memSpec.memTimingSpec.WTR = 4;
  memSpec.memTimingSpec.CKE = 3;
  memSpec.memTimingSpec.CKESR = 4;
  memSpec.memTimingSpec.RC = 31;
  memSpec.memTimingSpec.RCD = 7;
  memSpec.memTimingSpec.RL = 7;
  memSpec.memTimingSpec.RP = 7;
  memSpec.memTimingSpec.RAS = 24;
  memSpec.memTimingSpec.WL = 6;
  memSpec.memTimingSpec.AL = 0;
  memSpec.memTimingSpec.DQSCK = 0;
  memSpec.memTimingSpec.RTP = 4;
  memSpec.memTimingSpec.WR = 8;
  memSpec.memTimingSpec.XP = 3;
  memSpec.memTimingSpec.XPDLL = 10;
  memSpec.memTimingSpec.XS = 74;
  memSpec.memTimingSpec.XSDLL = 200;

  memSpec.memPowerSpec.idd0 = 90.0;
  memSpec.memPowerSpec.idd2p0 = 7.0;
  memSpec.memPowerSpec.idd2p1 = 7.0;
  memSpec.memPowerSpec.idd2n = 36.0;
  memSpec.memPowerSpec.idd3p0 = 10.0;
  memSpec.memPowerSpec.idd3p1 = 23.0;
  memSpec.memPowerSpec.idd3n = 42.0;
  memSpec.memPowerSpec.idd4w = 185.0;
  memSpec.memPowerSpec.idd4r = 180.0;
  memSpec.memPowerSpec.idd5 = 160.0;
  memSpec.memPowerSpec.idd6 = 7.0;
  memSpec.memPowerSpec.vdd = 1.8;
}

int main()
{
  MemorySpecification memSpec;
  ConfigMem(memSpec);
  libDRAMPower test = libDRAMPower(memSpec, 0);

  ifstream memDataFile ("memData.txt");
  int listSize = 0;
  while (memDataFile >> listSize)
  {
    //cout << listSize << endl;

    bool lastupdate;
    memDataFile >> lastupdate;
    //cout << lastupdate << endl;

    int64_t Timestamp;
    memDataFile >> Timestamp;
    //cout << Timestamp << endl;

    for (int i = 0; i < listSize; i++)
    {
      int type;
      unsigned bank = 0;
      int64_t timestamp = 0L;
      
      memDataFile >> type;
      memDataFile >> bank;
      memDataFile >> timestamp;
      test.doCommand(static_cast<MemCommand::cmds>(type), bank, timestamp);
    }

    test.updateCounters(lastupdate, Timestamp);
  }  

  

  return 0;
}