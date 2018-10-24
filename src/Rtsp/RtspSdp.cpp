﻿#include "RtspSdp.h"
#include "Common/Factory.h"

void Sdp::createRtpEncoder(uint32_t ssrc, int mtu) {
    _encoder = Factory::getRtpEncoderById(getCodecId(),
                                          ssrc,
                                          mtu,
                                          _sample_rate,
                                          _playload_type,
                                          getTrackType() * 2);
}

void RtspMaker::addTrack(const Track::Ptr &track, uint32_t ssrc, int mtu) {
    if (track->getCodecId() == CodecInvalid) {
        addTrack(std::make_shared<TitleSdp>(), ssrc, mtu);
    } else {
        Sdp::Ptr sdp = Factory::getSdpByTrack(track);
        if (sdp) {
            addTrack(sdp, ssrc, mtu);
        }
    }
}