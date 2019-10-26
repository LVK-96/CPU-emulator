#pragma once

class Clock
{
    public:
        Clock(double freq);
        ~Clock() = default;
        Clock& operator= (Clock& other) = default;
        Clock(Clock& other) = default;
        void start();
        void stop();
        double get_freq() const;
        void set_freq(double value);

    private:
        bool running_;
        double freq_;
};
