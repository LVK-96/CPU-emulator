#pragma once

class Register {
    public:
        Register();
        void stepClock();
        int get_data() const;
        void set_data();
        void reset();
        
    private:
        int data_;
        bool in_;
        bool out_;
};