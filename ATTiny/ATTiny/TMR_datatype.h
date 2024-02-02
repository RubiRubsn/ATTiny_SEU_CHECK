#pragma once
#include <avr/io.h>

class TMRuint8_t
{
private:
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t TMR()
    {
        if ((A == B) && (B == C))
        {
            return A;
        }
        else
        {
            if (A == B)
            {
                C = A;
            }
            else if (A == C)
            {
                B = A;
            }
            else
            {
                A = B;
            }
        }
        return A;
    };

public:
    TMRuint8_t(uint8_t val)
    {
        A = val;
        B = val;
        C = val;
    }
    TMRuint8_t()
    {
        A = 0;
        B = 0;
        C = 0;
    }
    TMRuint8_t &operator=(const uint8_t &value)
    {
        A = value;
        B = value;
        C = value;
        return *this;
    }

    bool operator==(const uint8_t &value)
    {
        TMR();

        return (A == value);
    }
    bool operator!=(const uint8_t &value)
    {
        TMR();

        return (A != value);
    }
    bool operator!=(const unsigned short &value)
    {
        TMR();

        return (A != value);
    }
    bool operator<(const uint8_t &value)
    {
        TMR();

        return (A < value);
    }
    bool operator<=(const uint8_t &value)
    {
        TMR();

        return (A <= value);
    }
    bool operator>(const uint8_t &value)
    {
        TMR();

        return (A > value);
    }
    bool operator>=(const uint8_t &value)
    {
        TMR();

        return (A >= value);
    }
    uint8_t operator++(int)
    {
        uint8_t help = TMR();
        A++;
        B++;
        C++;
        return help;
    }
    uint8_t operator++()
    {
        A++;
        B++;
        C++;
        return TMR();
    }
    uint8_t operator--(int)
    {
        uint8_t help = TMR();
        A--;
        B--;
        C--;
        return help;
    }
    uint8_t operator--()
    {
        A--;
        B--;
        C--;
        return TMR();
    }

    uint8_t operator()()
    {

        return TMR();
    }
    operator uint8_t()
    {
        return operator()();
    }
};

class TMRuint16_t
{
private:
    uint16_t A;
    uint16_t B;
    uint16_t C;
    uint16_t TMR()
    {
        if ((A == B) && (B == C))
        {
            return A;
        }
        else
        {
            if (A == B)
            {
                C = A;
            }
            else if (A == C)
            {
                B = A;
            }
            else
            {
                A = B;
            }
        }
        return A;
    };

public:
    TMRuint16_t(uint16_t val)
    {
        A = val;
        B = val;
        C = val;
    }
    TMRuint16_t()
    {
        A = 0;
        B = 0;
        C = 0;
    }
    TMRuint16_t &operator=(const uint16_t &value)
    {
        A = value;
        B = value;
        C = value;
        return *this;
    }
    bool operator==(const uint16_t &value)
    {
        TMR();

        return (A == value);
    }
    bool operator!=(const uint16_t &value)
    {
        TMR();

        return (A != value);
    }
    bool operator<(const uint16_t &value)
    {
        TMR();

        return (A < value);
    }
    bool operator<=(const uint16_t &value)
    {
        TMR();

        return (A <= value);
    }
    bool operator>(const uint16_t &value)
    {
        TMR();

        return (A > value);
    }
    bool operator>=(const uint16_t &value)
    {
        TMR();

        return (A >= value);
    }
    uint16_t operator++(int)
    {
        uint16_t help = TMR();
        A++;
        B++;
        C++;
        return help;
    }
    uint16_t operator++()
    {
        A++;
        B++;
        C++;
        return TMR();
    }
    uint16_t operator--(int)
    {
        uint16_t help = TMR();
        A--;
        B--;
        C--;
        return help;
    }
    uint16_t operator--()
    {
        A--;
        B--;
        C--;
        return TMR();
    }

    uint16_t operator()()
    {

        return TMR();
    }
    operator uint16_t()
    {
        return operator()();
    }
};
