/*!
 \file converter.h

 This file contains functions for converting Modbus registers and bits to int,
 float, bool, etc. data types and back.

  */
#ifndef CONVERTER_H
#define CONVERTER_H

#include <array>

#include <QtGlobal>
#include <QDebug>
#include <QException>


union Buf {
    float fvalue;
    quint8 i8[4];
    quint16 i16[2];
    quint32 i32;
};


using namespace std;

class Converter
{
public:
    enum Order {
        Lsw,	//!< Младший регистр
        Msw		//!< Старший регистр
    };

    Converter();
    static float toFloat(quint8 item0, quint8 item1, quint8 item2, quint8 item3);
    static float toFloat(quint16 item0, quint16 item1);
    static float toFloat(quint16 item[2]);
    static float toFloat(std::array<quint16, 2> buf, bool &ok);

    static quint16 getRegFromFloat(Order order, float value);

private:
    static Buf s_buf;
};

#endif // CONVERTER_H
