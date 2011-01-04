//
// mgui/author/ffmpeg.h
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

#ifndef __MGUI_AUTHOR_FFMPEG_H__
#define __MGUI_AUTHOR_FFMPEG_H__

#include <mgui/sdk/ioblock.h>

#include <mdemux/trackbuf.h>

#include <string>

namespace Project {

struct DVDTransData;

struct AutoDVDTransData
{
     bool  is4_3;
    Point  srcAspect;
      int  audioNum; // для <= 1 ffmpeg сам решит

    AutoDVDTransData(bool is4_3_);
};

std::string FFmpegToDVDArgs(const std::string& out_fname, const AutoDVDTransData& atd,
                            bool is_pal, const DVDTransData& td);
std::string FFmpegToDVDArgs(const std::string& out_fname, bool is_4_3, bool is_pal);
// для меню
std::string FFmpegPostArgs(const std::string& out_fname, bool is_4_3, bool is_pal, 
                           const std::string& a_fname = std::string(), double a_shift = 0.);

// полная команда для транскодирования
std::string FFmpegToDVDTranscode(const std::string& src_fname, const std::string& dst_fname,
                                 const AutoDVDTransData& atd, bool is_pal, const DVDTransData& td);

struct FFmpegCloser
{
                GPid  pid;
                 int  inFd;
            ExitData& ed;
ptr::one<OutErrBlock> oeb;

     FFmpegCloser(ExitData& ed_): pid(NO_HNDL), inFd(NO_HNDL), ed(ed_) {}
    ~FFmpegCloser();
};

struct PPMWriter
{
         int  inFd;
    TrackBuf  pipeBuf;

    PPMWriter(int in_fd);
    void Write(RefPtr<Gdk::Pixbuf> img);
};

// :TRICKY: в sys/sysmacros.h (glibc) определены нижеуказанные макросы, например,
// при установленном __GNUC__ => __GLIBC_HAVE_LONG_LONG (полная х**та)!!
// Дискуссия здесь (нормально чинить не хотят): https://bugzilla.redhat.com/show_bug.cgi?id=130601 
#undef major
#undef minor

struct TripleVersion
{
    int major;
    int minor;
    int micro;

    TripleVersion(int maj=0, int min=0, int mic=0)
        : major(maj), minor(min), micro(mic) {}
};

struct FFmpegVersion
{
    TripleVersion avfilter;
};

// conts - вывод ffmpeg -formats
FFmpegVersion TestFFmpegForDVDEncoding(const std::string& conts);
// проверка возможности кодировать совместимый с DVD материал с помощью ffmpeg
FFmpegVersion CheckFFDVDEncoding();

} // namespace Project

#endif // #ifndef __MGUI_AUTHOR_FFMPEG_H__

