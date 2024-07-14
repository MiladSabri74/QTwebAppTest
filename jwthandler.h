#ifndef JWTHANDLER_H
#define JWTHANDLER_H


class JWT {
public:
    static QByteArray generateJWT(const QString& username);

    static bool checkTokenValidation(const QString& token);

    static bool checkJsonValidation(const QByteArray& body,const QString& param1,QString* value1);
    static bool checkJsonValidation(const QByteArray& body,const QString& param1,QString* value1,const QString& param2,QString* value2);

};
#endif // JWTHANDLER_H
