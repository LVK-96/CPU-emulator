#include "alu.hpp"

ALU::ALU(Register* A, Register* B, Bus* dataBus): A_(A), B_(B), 
dataBus_(dataBus), data_(0), substract_(false), add_(false), out_(false) {}

void ALU::stepClock()
{
    if (out_) {
        dataBus_->set_data(get_data());
    } else if (substract_) {
        set_data(A_->get_data() - B_->get_data());
    } else if (add_) {
        set_data(A_->get_data() + B_->get_data());
    }
}

void ALU::set_substract() 
{
    add_ = false;
    substract_ = true;
}

void ALU::set_add() 
{
    substract_ = false;
    add_ = true;
}


void ALU::set_out()
{
    substract_ = false;
    out_ = true;
}

void ALU::set_data(int data)
{
    data_ = data;
}

int ALU::get_data() const
{
    return data_;
}

void ALU::reset_flags()
{
    add_ = false;
    substract_ = false;
    out_ = false;
}