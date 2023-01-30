#ifndef BEEP_HPP
#define BEEP_HPP
/*
 * *************************************************************************************************
 * TTU-SG
 * Copyright (C) 2022 Friendcom
 * 
 * @file         : beep.hpp
 * @author       : ekko
 * @version      : V0.1
 * @date         : 2023-01-30
 * @brief        : 
 * @details      : 
 * @attention    : 
 * 
 * Change History : 
 * 
 * 
 * 
 * *************************************************************************************************
 */
#include <stddef.h>

#include <errno.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fcntl.h>

#include <linux/input.h>

#include <string>
#include <iostream>

class Beep
{
public:
    Beep(std::string dev = "/dev/input/by-path/platform-pcspkr-event-spkr")
    {
        dev_name = dev;
    }
    ~Beep()
    {

    }

    bool open()
    {
        fd = ::open(dev_name.c_str(), O_WRONLY);
        if (fd == -1) {
            printf("could not open(2) %s: %s\n",
                        dev_name.c_str(), strerror(errno));
            return false;
        }
        printf("%s open success\n",dev_name.c_str());
        return true;
    }

    void close()
    {
        ::close(fd);
    }

    bool set_freq(int freq)
    {
        struct input_event e;

        memset(&e, 0, sizeof(e));
        e.type = EV_SND;
        e.code = SND_TONE;
        e.value = 0;

        if (sizeof(e) != write(fd, &e, sizeof(e))) {
            return true;
        }

        return false;
    }
    
private:
    std::string dev_name;
    int fd = -1;
};

#endif /* BEEP_HPP */
