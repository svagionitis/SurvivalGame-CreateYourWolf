#include <pthread.h>
#include "control.h"
#include "header.h"

extern window_settings_t win_set;

void *control()
{
    while(win_set.c != 'q')
    {
        // Get keyboard input non-blocking
        win_set.c = getch();
        if (win_set.c == ERR)
            continue;
        else if (win_set.c == 'q')
            break;
        else
            win_set.last_char = win_set.c;


        switch(win_set.c)
        {
            case '+':
                win_set.speed += 100;

                break;
            case '-':
                win_set.speed -= 100;

                break;
            case '*':
                win_set.speed *= 10;

                break;
            case '/':
                win_set.speed /= 10;

                if (win_set.speed < 1)
                    win_set.speed = 1;

                break;
            case 'b':
                if (win_set.set_border)
                    win_set.set_border = FALSE;
                else
                    win_set.set_border = TRUE;

                break;
        }

    }

    pthread_exit(0);
}

