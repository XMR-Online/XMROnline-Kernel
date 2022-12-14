/* XMRig
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
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


#include "base/io/log/Tags.h"
#include "base/io/log/Log.h"


const char *xmrig::Tags::config()
{
	static const char *tag = "[config]-"; 

    return tag;
}


const char *xmrig::Tags::network()
{
	static const char *tag = "[net]-"; 

    return tag;
}


const char* xmrig::Tags::origin()
{
	static const char* tag = "[origin]-"; 

    return tag;
}


const char *xmrig::Tags::signal()
{
	static const char *tag = "[signal]-"; 

    return tag;
}


#ifdef XMRIG_MINER_PROJECT
const char *xmrig::Tags::cpu()
{
	static const char *tag = "[cpu]-"; 

    return tag;
}


const char *xmrig::Tags::miner()
{
	static const char *tag = "[work]-"; 

    return tag;
}


#ifdef XMRIG_ALGO_RANDOMX
const char *xmrig::Tags::randomx()
{
	static const char *tag = "[randomx]-"; 

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_BENCHMARK
const char *xmrig::Tags::bench()
{
	static const char *tag = "[bench]-"; 

    return tag;
}
#endif
#endif


#ifdef XMRIG_PROXY_PROJECT
const char *xmrig::Tags::proxy()
{
	static const char *tag = "[proxy]-"; 

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_CUDA
const char *xmrig::Tags::nvidia()
{
	static const char *tag = "[nvidia]-"; 

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_OPENCL
const char *xmrig::Tags::opencl()
{
	static const char *tag = "[opencl]-"; 

    return tag;
}
#endif


#ifdef XMRIG_FEATURE_MO_BENCHMARK
const char *xmrig::Tags::benchmark()
{
    static const char *tag = BRIGHT_BLACK_BG(CYAN_BOLD_S " benchmk ");

    return tag;
}
#endif

#ifdef XMRIG_FEATURE_PROFILING
const char* xmrig::Tags::profiler()
{
	static const char* tag = "[profile]-"; 

    return tag;
}
#endif
