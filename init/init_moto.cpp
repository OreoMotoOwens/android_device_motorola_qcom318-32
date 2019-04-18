/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void vendor_load_properties()
{
    std::string platform = android::base::GetProperty("ro.board.platform", ""));
    if (platform != ANDROID_TARGET)
        return;

    std::string sku = android::base::GetProperty("ro.boot.hardware.sku", ""));
    android::init::property_set("ro.product.model", sku.c_str());

    // rmt_storage
    std::string device = android::base::GetProperty("ro.boot.device", ""));
    std::string radio = android::base::GetProperty("ro.boot.radio", ""));
    android::init::property_set("ro.hw.device", device.c_str());
    android::init::property_set("ro.hw.radio", radio.c_str());

    if (device == "owens") {
        if (radio == "US") {
            std::string carrier = android::base::GetProperty("ro.boot.carrier");
            if (carrier == "sprint") {
                android::init::property_set("ro.build.description","owens_sprint-user 7.1.1 NCR26.58-44 28 release-keys");
                android::init::property_set("ro.build.fingerprint","motorola/owens_sprint/owens:7.1.1/NCR26.58-44/28:user/release-keys");
                android::init::property_set("ro.mot.build.oem.product","owens_sprint");
                android::init::property_set("ro.mot.build.customerid ","sprint");
                android::init::property_set("persist.rcs.supported","1");
                android::init::property_set("persist.vt.supported","1");
                android::init::property_set("persist.eab.supported","1");
                android::init::property_set("persist.radio.videopause.mode","1");
                android::init::property_set("net.tethering.noprovisioning", "true");
                android::init::property_set("tether_dun_required", "0");
            } else {
                android::init::property_set("ro.carrier", "retus");
                android::init::property_set("ro.mot.build.oem.product","owens");
                android::init::property_set("ro.mot.build.customerid","retail");
                android::init::property_set("persist.ims.volte","true");
                android::init::property_set("persist.ims.vt","false");
                android::init::property_set("persist.ims.vt.epdg","false");
                android::init::property_set("persist.ims.rcs","false");
                android::init::property_set("persist.radio.videopause.mode","0");
                android::init::property_set("persist.vt.supported","0");
                android::init::property_set("persist.eab.supported","0");
                android::init::property_set("persist.rcs.supported","0");
            }
            android::init::property_set("ro.radio.imei.sv", "2");
        }
    }
}