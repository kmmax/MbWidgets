#include "oiserver.h"
#include "led.h"

#include <QtTest>
#include <QPair>
#include <QSet>
#include <QApplication>
#include <QtCore/QDebug>



// add necessary includes here

#if 0
// Enabling this section disables all debug output from non-Qt code.
    #define QT_NO_DEBUG_OUTPUT
#endif


void noMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{}

class Test_OIServer : public QObject
{
    Q_OBJECT

public:
    Test_OIServer();
    ~Test_OIServer();

private slots:
//    void initTestCase_data();
    void initTestCase();
//    void cleanupTestCase();

    void test_ranges();
};


Test_OIServer::Test_OIServer()
{
}


Test_OIServer::~Test_OIServer()
{
}


void Test_OIServer::initTestCase()
{
#ifdef QT_NO_DEBUG_OUTPUT
    qInstallMessageHandler(noMessageOutput);
#endif
}


// --- Tests ---


void Test_OIServer::test_ranges()
{
    // type this modbus address of widgets (input datas)
    QSet<int> addr = {
        10, 20, 21, 20, // Range 10..21
        3121, 3200      // Range 3121..3200
    };
    // type regions (return datas)
    QSet<OIServer::Range> rng = {{10, 21}, {3121, 3200}};

    // Preparing
    QVector<int> addresses = addr.toList().toVector();
    QVector<OIServer::Range> results = rng.toList().toVector();

    OIServer srv;
    for (auto address: addresses) {
        auto wgt = new Led();
        wgt->setRegAddr(address);
        srv.addMbWidget(wgt);
    }

    // Checking
    auto ranges = srv.ranges();
    for (auto range: ranges) {
        QVERIFY(rng.contains(range));
        qDebug() << '{' << range.first << ", " << range.second << '}';
    }
    QCOMPARE(true, true);
}

//QTEST_APPLESS_MAIN(Test_OIServer)
// QTEST_MAIN for Classes which use QApplication
QTEST_MAIN(Test_OIServer)

#include "tst_test_oiserver.moc"
