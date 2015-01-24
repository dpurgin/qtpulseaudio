# qtpulseaudio

This library is a Qt wrapper for PulseAudio client API. Not usable for practical purposes yet.

Milestones are:

1. Wrap basic introspection of cards, sinks and sources;
2. Wrap streams.

Currently implemented:

1. Connection to PulseAudio server;
2. Quering for available Cards (indices and names only);
3. Quering for available sinks (indices and names only).

Use with caution. No thread synchronization implemented yet.

Licensed under LGPL v3.0
