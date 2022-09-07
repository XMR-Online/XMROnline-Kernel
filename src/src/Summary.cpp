/* XMRig
 * Copyright (c) 2018-2022 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2022 XMRig       <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cinttypes>
#include <cstdio>
#include <uv.h>


#include "backend/cpu/Cpu.h"
#include "base/io/log/Log.h"
#include "base/net/stratum/Pool.h"
#include "core/config/Config.h"
#include "core/Controller.h"
#include "crypto/common/Assembly.h"
#include "crypto/common/VirtualMemory.h"
#include "Summary.h"
#include "version.h"


#ifdef XMRIG_FEATURE_DMI
#   include "hw/dmi/DmiReader.h"
#endif


#ifdef XMRIG_ALGO_RANDOMX
#   include "crypto/rx/RxConfig.h"
#endif


namespace xmrig {


#ifdef XMRIG_OS_WIN
static constexpr const char *kHugepagesSupported = "permission granted";
#else
static constexpr const char *kHugepagesSupported = "supported";
#endif


#ifdef XMRIG_FEATURE_ASM
static const char *coloredAsmNames[] = {
    RED_BOLD("none"),
    "auto",
    GREEN_BOLD("intel"),
    GREEN_BOLD("ryzen"),
    GREEN_BOLD("bulldozer")
};


inline static const char *asmName(Assembly::Id assembly)
{
    return coloredAsmNames[assembly];
}
#endif


static void print_pages(const Config *config)
{
    Log::print("%s %s",
               "HUGE PAGES", config->cpu().isHugePages() ? (VirtualMemory::isHugepagesAvailable() ? kHugepagesSupported : "unavailable") : "disabled");
}


static void print_cpu(const Config *)
{
    const auto info = Cpu::info();

    Log::print("%s %s (%zu) %s %sAES%s",
               "CPU",
               info->brand(),
               info->packages(),
               ICpuInfo::is64bit()    ? "64-bit" : "32-bit",
               info->hasAES()         ? "" : "-",
               info->isVM()           ? " VM" : ""
               );
}


static void print_memory(const Config *config)
{
    constexpr size_t oneGiB = 1024U * 1024U * 1024U;
    const auto freeMem      = static_cast<double>(uv_get_free_memory());
    const auto totalMem     = static_cast<double>(uv_get_total_memory());

    const double percent = freeMem > 0 ? ((totalMem - freeMem) / totalMem * 100.0) : 100.0;

    Log::print("%s %.1f/%.1f GB (%.0f%%)",
               "MEMORY",
               (totalMem - freeMem) / oneGiB,
               totalMem / oneGiB,
               percent
               );
}


static void print_threads(const Config *config)
{
#   ifdef XMRIG_FEATURE_ASM
    if (config->cpu().assembly() == Assembly::AUTO) {
        const Assembly assembly = Cpu::info()->assembly();

        Log::print("ASSEMBLY auto:%s", asmName(assembly));
    }
    else {
        Log::print("ASSEMBLY %s", asmName(config->cpu().assembly()));
    }
#   endif
}


static void print_commands(Config *)
{
}


} // namespace xmrig


void xmrig::Summary::print(Controller *controller)
{
    const auto config = controller->config();
    print_pages(config);
    print_cpu(config);
    print_memory(config);
    print_threads(config);
}



