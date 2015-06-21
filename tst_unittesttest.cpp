#include <QtTest>
#include <QString>

#include "../clockwidget/udpclient.h"
#include "../clockwidget/udpserver.h"

class UnittestTest : public QObject
{
    Q_OBJECT

public:
    UnittestTest();

private Q_SLOTS:
    void checkCLientPortListing();
    void CheckClientDecodeDigData();
    void CheckClientDecodeAnaData();
    void CheckClientDisconnect();
    void checkServerSendData();

};

UnittestTest::UnittestTest()
{
}


// Checks if the port is properly bound to the client
void UnittestTest::checkCLientPortListing()
{
    UdpClient client;

    QCOMPARE(client.initSocket(3000), QAbstractSocket::BoundState);
    QCOMPARE(client.initSocket(-1), QAbstractSocket::UnconnectedState); // failed because -1 isn't a valid Port, program can't catch it and crashes
}

// The decodeInput expects messages with the format "$DIG,%d" where %d should be a value between 0-100
// it also can distinguishes between DIG and ANA (digital and analog) messages
// The function extracts the value in the string and returns it. If the format is wrong the function
// will return 0.
void UnittestTest::CheckClientDecodeDigData()
{
    UdpClient client;
    client.initSocket(3000);

    QCOMPARE(client.decodeInput("$DIG,1"), 1);
    QCOMPARE(client.decodeInput("$DIG%3"), 3);
    QCOMPARE(client.decodeInput("$PIP,2"), 0);
}


// The decodeInput expects messages with the format "$ANA,%d" where %d should be a value between 0-100
// it also can distinguishes between DIG and ANA (digital and analog) messages
// The function extracts the value in the string and returns it. If the format is wrong the function
// will return 0.
void UnittestTest::CheckClientDecodeAnaData()
{
    UdpClient client;
    client.initSocket(3000);

    QCOMPARE(client.decodeInput("$ANA,1"), 1);
    QCOMPARE(client.decodeInput("$ANA&3"), 3);
    QCOMPARE(client.decodeInput("$SAG,2"), 0);
    QCOMPARE(client.decodeInput("$PANA,2"), 0);
}

// The disconnent funtion checks, if the socket is properly disconnected from the client
void UnittestTest::CheckClientDisconnect()
{
    UdpClient client;
    client.initSocket(3000);
    client.disconnect();

    QCOMPARE(client.disconnect(), QAbstractSocket::UnconnectedState);

}

// This function compares the size of the string that will be send and the actual string size
// The max. size of an datagram is 512 Bytes.
void UnittestTest::checkServerSendData()
{
    UdpServer server;
    server.initSocket();

    // empty string
    QString case1 = "";
    // one Byte
    QString case2 = "$";
    // random byte number between 0 - 512
    QString case3 = "ghalksjgasdkjvnakjfnbakjfgnbgagfgggf//7823873283874845934adfkj";
    // 512 Bytes
    QString case4 = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012";
    // 513 Bytes
    QString case5 = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123";

    QCOMPARE(server.sendDatagramm(case1,QHostAddress("127.0.0.1"), 3000),case1.size());
    QCOMPARE(server.sendDatagramm(case2,QHostAddress("127.0.0.1"), 3000),case2.size());
    QCOMPARE(server.sendDatagramm(case3,QHostAddress("127.0.0.1"), 3000),case3.size());
    QCOMPARE(server.sendDatagramm(case4,QHostAddress("127.0.0.1"), 3000),case4.size());
    QCOMPARE(server.sendDatagramm(case5,QHostAddress("127.0.0.1"), 3000),case5.size());
}


QTEST_APPLESS_MAIN(UnittestTest)

#include "tst_unittesttest.moc"
