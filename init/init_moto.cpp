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

void gsm_properties(bool msim);
void cdma_properties();

void vendor_load_properties()
{
    std::string platform = property_get("ro.board.platform");
    if (platform != ANDROID_TARGET)
        return;

    std::string sku = property_get("ro.boot.hardware.sku");
    property_set("ro.product.model", sku.c_str());

    // rmt_storage
    std::string device = property_get("ro.boot.device");
    std::string radio = property_get("ro.boot.radio");
    property_set("ro.hw.device", device.c_str());
    property_set("ro.hw.radio", radio.c_str());

    //CDMA TESTING
    if (radio == "US") {
        std::string carrier = property_get("ro.boot.carrier");
        std::string fsg = property_get("ro.boot.fsg-id"); //This seems to be useless unless specifically set in the oem
        cdma_properties();
        if (carrier == "sprint") {
            if (fsg == "boost") {
	            property_set("ro.cdma.home.operator.alpha", "Boost Mobile");
	            property_set("ro.cdma.home.operator.numeric", "311870");
            }
            property_set("ro.carrier", "sprint");
            property_set("ro.mot.build.customerid ","sprint");
        } else {
            property_set("ro.telephony.get_imsi_from_sim", "true");
            property_set("ro.cdma.data_retry_config", "max_retries=infinite,0,0,10000,10000,100000,10000,10000,10000,10000,140000,540000,960000");
            property_set("ro.mot.build.customerid", "retus");
        }
        property_set("ro.cdma.international.eri", "2,74,124,125,126,157,158,159,193,194,195,196,197,198,228,229,230,231,232,233,234,235");
    }
}

void cdma_properties()
{
    property_set("DEVICE_PROVISIONED","1");
    property_set("gsm.sim.operator.iso-country", "US");
    property_set("gsm.operator.iso-country", "US");
    property_set("ril.subscription.types","NV,RUIM");
    property_set("ro.telephony.default_cdma_sub", "0");
    property_set("ro.product.locale.region", "US");
    property_set("ro.telephony.default_network", "8");
    property_set("telephony.lteOnCdmaDevice", "1");
}

void gsm_properties(bool msim)
{
    property_set("telephony.lteOnGsmDevice", "1");
    property_set("ro.telephony.default_network", "9");
    if (msim) {
        property_set("persist.radio.dont_use_dsd", "true");
        property_set("persist.radio.multisim.config", "dsds");
        property_set("persist.radio.plmn_name_cmp", "1");
        property_set("ro.telephony.ril.config", "simactivation");
    }
}