#ifndef _INTERNAL_REPLAY_H
#define _INTERNAL_REPLAY_H

namespace Osu
{
    struct replay_t
    {
        ~replay_t();
        bool FromFile(const char* path);
    };
}
#endif
