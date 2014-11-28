#ifndef _GAME_TIMER_H_
#define _GAME_TIMER_H_

namespace dngine{
    class Timer {
        private:
            int startTicks;
            int pausedTicks;

            bool started;
            bool paused;

        public:
            Timer();

            void start();
            void pause();
            void unpause();
            void stop();

            int get_ticks();

            bool is_started();
            bool is_paused();
    };
}

#endif
