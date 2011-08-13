//
// mgui/project/video.h
// This file is part of Bombono DVD project.
//
// Copyright (c) 2010 Ilya Murav'jov
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// 

#ifndef __MGUI_PROJECT_VIDEO_H__
#define __MGUI_PROJECT_VIDEO_H__

#include <mbase/project/media.h>
#include <mlib/range/any_range.h>

namespace Project
{

fe::range<VideoItem> AllVideos();
// список видео "IsTransVideo() == true"
fe::range<VideoItem> AllTransVideos();

// vi && RequireTranscoding(vi)
bool IsTransVideo(VideoItem vi);

// расчет параметров транскодирования автоматом
DVDTransData GetRealTransData(VideoItem vi);
DVDTransData DVDDims2TDAuto(DVDDims dd);

Point DVDDimension(DVDDims dd);
DVDDims CalcDimsAuto(VideoItem vi);
//
int OutAudioNum(int i_anum);

// кэш для расчетов по транскодированию и т.д.
struct RTCache
{
      bool  isCalced;

      bool  reqTrans;
    double  duration;
     Point  vidSz;
     Point  dar;
       int  audioNum; // число аудиоканалов

    RTCache(): isCalced(false) {}
};

RTCache& GetRTC(VideoItem vi);
io::pos CalcTransSize(RTCache& rtc, int vrate);

Point GetStillImageDimensions(StorageItem still_img);

} // namespace Project

// kbit/s 
// 448 - умолчание в ffmpeg для -target *-dvd
// выбор возможен из ff_ac3_bitrate_tab
const int TRANS_AUDIO_BITRATE = 320;

#endif // #ifndef __MGUI_PROJECT_VIDEO_H__

