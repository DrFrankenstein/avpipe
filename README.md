# avpipe
_"I have no clue what I'm doing."_

This project aims to become a GUI-based tool for basic editing of audio and
video files and streams: (re-)encoding, (re-)muxing, cutting, splicing, basic
mixing/compositing, filtering…

The name "avpipe" comes from ffmpeg filtergraphs forming a series of pipes that
the streams go through. At some point, we might have a visual graph editor for
this.

## History
I started this for two reasons: modern NLEs require absurd amounts of resources
and are overkill for most of the tasks I need them for, and building a ffmpeg
command/script is time-consuming and sometimes an experience in frustration,
especially for someone who doesn't do it on a frequent basis.

This started out as an idea for a GUI for building ffmpeg commands, but quickly
became its own program to allow for useful features like live previewing.

A long-term goal (or pipe dream) would be feature-parity with ffmpeg.

## Building
You'll need:
- GCC 10, or
- clang 7, or
- CL 19.26 (Visual Studio 2019 v. 16.6)

Install the dev packages for Qt 5 and ffmpeg, then 
`mkdir out && cd out && cmake .. && cmake --build .`

This is being developed on Windows, but should also run on Linux/BSD/macOS.
