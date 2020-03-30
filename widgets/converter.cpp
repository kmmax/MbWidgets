#include "converter.h"

Buf Converter::s_buf;


Converter::Converter()
{
}


/**
 * @brief Makes float value from 4 bytes
 * @param[in] item0
 * @param[in] item1
 * @param[in] item2
 * @param[in] item3
 * @return float value which is represented these bytes
 */
float Converter::toFloat(quint8 item0, quint8 item1, quint8 item2, quint8 item3)
{
    Converter::s_buf.i8[0] = item0;
    Converter::s_buf.i8[1] = item1;
    Converter::s_buf.i8[2] = item2;
    Converter::s_buf.i8[3] = item3;
    return s_buf.fvalue;
}


/**
 * @brief Makes float value from 2 registers
 * @param[in] item0 - first register.
 * @param[in] item1 - second register.
 * @return float value which is represented these registers
 */
float Converter::toFloat(quint16 item0, quint16 item1)
{
    s_buf.i16[0] = item0;
    s_buf.i16[1] = item1;
    return s_buf.fvalue;
}


/**
 * @briefMakes float value from 2 first registers of array.
 * @param[in] item - array of registers
 * @return float value
 */
float Converter::toFloat(quint16 item[])
{
    qDebug() << "toFloat(quint16 item[])";
    s_buf.i16[0] = item[0];
    s_buf.i16[1] = item[1];
//    quint16 temp = item[2];
    return s_buf.fvalue;
}


/**
 * @brief
 * @param[in] buf - two bytes for float number representation
 * @param[in-out] ok - successful
 * @return float number
 */
float Converter::toFloat(std::array<quint16, 2> buf, bool &ok)
{
    int size = buf.size();
    if (size <2) {
        return 0.0;
        ok = false;
    }
    s_buf.i16[0] = buf[0];
    s_buf.i16[1] = buf[1];
    return s_buf.fvalue;
}


/**
 * @brief returns register from float representation
 * @param[in] order - the parameter points which register is needed.
 * @param[in] value - initial value inself.
 * @return value of register.
 */
quint16 Converter::getRegFromFloat(Converter::Order order, float value)
{
    s_buf.fvalue = value;
    quint16 res = 0;
    switch (order) {
    case Lsw:
        res = s_buf.i16[0];
        break;
    case Msw:
        res = s_buf.i16[1];
        break;
    default:
        break;
    }

    return  res;
}


