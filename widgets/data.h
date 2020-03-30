#ifndef DATA_H
#define DATA_H

#include <QMetaType>
#include <QTime>
#include <QVariant>

#include <chrono>


namespace MbData
{
enum class Quality {
    Undef = 0,  		///< Undefined
    Good  = 1,          ///< Good
    NotRun = 2,         ///< Driver doesn't run
    NoConnect = 3,      ///< Not connection to remote device
    BadParameter = 4    ///< Remote device doesn't have parameter
};

//enum class Type {
//    BOOL,
//    INT,
//    UINT,
//    DINT,
//    REAL,
//};


struct Register
{
    // When driver has acsess to Register, it check
    // if it has "w". If it's true driver will send request
    // to remote devece and update register, set "r".
    enum Direction {
        w,  ///< data writen to send to driver
        r   ///< data is ready for reading from driver
    };

    quint16 value = 0;
    MbData::Quality qulity = MbData::Quality::Undef;
    QTime time = QTime(0, 0, 0);
    Direction direct = Direction::r;
};

using MbRegisterMap = QVector<Register>;

} // end namespace MbData

//Q_DECLARE_METATYPE(MbData::Type)
//Q_DECLARE_METATYPE(MbData::Register)

#endif // DATA_H
